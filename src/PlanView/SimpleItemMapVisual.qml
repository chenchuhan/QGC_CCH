/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick          2.3
import QtQuick.Controls 1.2
import QtLocation       5.3
import QtPositioning    5.3

import QGroundControl               1.0
import QGroundControl.ScreenTools   1.0
import QGroundControl.Palette       1.0
import QGroundControl.Controls      1.0
import QGroundControl.FlightMap     1.0

/// Simple Mission Item visuals
Item {
    id: _root

    property var map        ///< Map control to place item in
    property var vehicle    ///< Vehicle associated with this item

    property var    _missionItem:       object
    property var    _itemVisual
    property var    _dragArea
    property bool   _itemVisualShowing: false
    property bool   _dragAreaShowing:   false

    //start_cch_20210321 loiterRaduis-1
    //定义变量
    property var    _circle
    property var    _radiusLabel
    property bool   _circleShowing:   false

    signal clicked(int sequenceNumber)

    function hideItemVisuals() {
        if (_itemVisualShowing) {
            _itemVisual.destroy()
            _itemVisualShowing = false
        }
    }

    function showItemVisuals() {
        if (!_itemVisualShowing) {
            _itemVisual = indicatorComponent.createObject(map)
            map.addMapItem(_itemVisual)
            _itemVisualShowing = true
        }
    }

    function hideDragArea() {
        if (_dragAreaShowing) {
            _dragArea.destroy()
            _dragAreaShowing = false
        }
    }

    function showDragArea() {
        if (!_dragAreaShowing && _missionItem.specifiesCoordinate) {
            _dragArea = dragAreaComponent.createObject(map)
            _dragAreaShowing = true
        }
    }

    //start_cch_20210321 loiterRaduis-2
    //隐藏半径圈和数字
    function hideCircle() {
        if (_circleShowing) {
            _circle.destroy()
            _radiusLabel.destroy()
            _circleShowing = false
        }
    }

    //start_cch_20210321 loiterRaduis-3
    //显示半径圈和数字
    function showCircle() {
        if (!_circleShowing) {
            _circle = circleComponent.createObject(map)
            _radiusLabel = radiusLabelComponent.createObject(map)
            map.addMapItem(_circle)
            map.addMapItem(_radiusLabel)
            _circleShowing = true
        }
    }

    //start_cch_20210321 loiterRaduis-4
    //显示半径圈的组件
    Component {
        id: circleComponent

        MapCircle {
            color:          Qt.rgba(0,0,0,0)
            border.color:   "red"
            border.width:   3
            center:         _missionItem.coordinate
            radius:         _missionItem.loiterRaduis ? _missionItem.loiterRaduis : 0
            visible:        _missionItem.category === "Loiter"
        }
    }

    //start_cch_20210321 loiterRaduis-4
    //显示半径数值的控件
    Component {
        id: radiusLabelComponent

        MapQuickItem{
            visible: _missionItem.category === "Loiter" && _missionItem.loiterRaduis !== 0
            sourceItem: Rectangle {
                width: 14
                height: 14
                radius: 7
                color: "white"
                border.width: 2
                border.color: "red"
                Rectangle{
                    anchors.left: parent.right
                    anchors.top: parent.bottom
                    width: item_text.width+5+5
                    height: item_text.height+10
                    border.color: "gray"
                    Text {
                        id: item_text
                        x: 5
                        anchors.verticalCenter: parent.verticalCenter
                        text: String(_missionItem.loiterRaduis ? _missionItem.loiterRaduis : 0)
                    }
                }
            }

            //定位方法一： 地球半径对比
//            coordinate{
//                latitude: _missionItem.coordinate.latitude + (360/40076000)*(_missionItem.loiterRaduis ? _missionItem.loiterRaduis : 0)
//                longitude: _missionItem.coordinate.longitude
//            }
            //定位方法二：利用现有的函数
            coordinate : _missionItem.coordinate.atDistanceAndAzimuth((_missionItem.loiterRaduis ? _missionItem.loiterRaduis : 0),90)
            anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
        }
    }


    Component.onCompleted: {
        showItemVisuals()
        if (_missionItem.isCurrentItem && map.planView) {
            showDragArea()
        }
        //start_cch_20210321 loiterRaduis-5
        //初始化，类似于构造函数
        showCircle()
    }

    Component.onDestruction: {
        hideDragArea()
        hideItemVisuals()
        //start_cch_20210321 loiterRaduis-6
        //类似于析构函数
        hideCircle()
    }


    Connections {
        target: _missionItem

        onIsCurrentItemChanged: {
            if (_missionItem.isCurrentItem && map.planView) {
                showDragArea()
            } else {
                hideDragArea()
            }
        }
    }

    // Control which is used to drag items
    Component {
        id: dragAreaComponent

        MissionItemIndicatorDrag {
            mapControl:     _root.map
            itemIndicator:  _itemVisual
            itemCoordinate: _missionItem.coordinate

            onItemCoordinateChanged: _missionItem.coordinate = itemCoordinate
        }
    }

    Component {
        id: indicatorComponent

        MissionItemIndicator {
            coordinate:     _missionItem.coordinate
            visible:        _missionItem.specifiesCoordinate
            z:              QGroundControl.zOrderMapItems
            missionItem:    _missionItem
            sequenceNumber: _missionItem.sequenceNumber
            onClicked:      _root.clicked(_missionItem.sequenceNumber)
        }
    }
}
