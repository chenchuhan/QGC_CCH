/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/
#include "GenericMapProvider.h"

static const QString StatkartMapUrl = QStringLiteral("http://opencache.statkart.no/gatekeeper/gk/gk.open_gmaps?layers=topo4&zoom=%1&x=%2&y=%3");

QString StatkartMapProvider::_getURL(const int x, const int y, const int zoom, QNetworkAccessManager* networkManager) {
    Q_UNUSED(networkManager)
    return StatkartMapUrl.arg(zoom).arg(x).arg(y);
}

static const QString EniroMapUrl = QStringLiteral("http://map.eniro.com/geowebcache/service/tms1.0.0/map/%1/%2/%3.png");

QString EniroMapProvider::_getURL(const int x, const int y, const int zoom, QNetworkAccessManager* networkManager) {
    Q_UNUSED(networkManager)
    return EniroMapUrl.arg(zoom).arg(x).arg((1 << zoom) - 1 - y);
}

static const QString MapQuestMapUrl = QStringLiteral("http://otile%1.mqcdn.com/tiles/1.0.0/map/%2/%3/%4.jpg");

QString MapQuestMapMapProvider::_getURL(const int x, const int y, const int zoom, QNetworkAccessManager* networkManager) {
    Q_UNUSED(networkManager)
    return MapQuestMapUrl.arg(_getServerNum(x, y, 4)).arg(zoom).arg(x).arg(y);
}

static const QString MapQuestSatUrl = QStringLiteral("http://otile%1.mqcdn.com/tiles/1.0.0/sat/%2/%3/%4.jpg");

QString MapQuestSatMapProvider::_getURL(const int x, const int y, const int zoom, QNetworkAccessManager* networkManager) {
    Q_UNUSED(networkManager)
    return MapQuestSatUrl.arg(_getServerNum(x, y, 4)).arg(zoom).arg(x).arg(y);
}

QString VWorldStreetMapProvider::_getURL(const int x, const int y, const int zoom, QNetworkAccessManager* networkManager) {
    Q_UNUSED(networkManager)
    const int gap   = zoom - 6;
    const int x_min = int(53 * pow(2, gap));
    const int x_max = int(55 * pow(2, gap) + (2 * gap - 1));
    const int y_min = int(22 * pow(2, gap));
    const int y_max = int(26 * pow(2, gap) + (2 * gap - 1));

    if (zoom > 19) {
        return QString();
    } else if (zoom > 5 && x >= x_min && x <= x_max && y >= y_min && y <= y_max) {
        return QString(QStringLiteral("http://xdworld.vworld.kr:8080/2d/Base/service/%1/%2/%3.png")).arg(zoom, x, y);
    } else {
        const QString key = _tileXYToQuadKey(x, y, zoom);
        return QString(QStringLiteral("http://ecn.t%1.tiles.virtualearth.net/tiles/r%2.png?g=%3&mkt=%4"))
            .arg(_getServerNum(x, y, 4)).arg(key, _versionBingMaps, _language);
    }
}

QString VWorldSatMapProvider::_getURL(const int x, const int y, const int zoom, QNetworkAccessManager* networkManager) {
    Q_UNUSED(networkManager)
    const int gap   = zoom - 6;
    const int x_min = int(53 * pow(2, gap));
    const int x_max = int(55 * pow(2, gap) + (2 * gap - 1));
    const int y_min = int(22 * pow(2, gap));
    const int y_max = int(26 * pow(2, gap) + (2 * gap - 1));

    if (zoom > 19) {
        return QString();
    } else if (zoom > 5 && x >= x_min && x <= x_max && y >= y_min && y <= y_max) {
        return QString("http://xdworld.vworld.kr:8080/2d/Satellite/service/%1/%2/%3.jpeg").arg(zoom, x, y);
    } else {
        const QString key = _tileXYToQuadKey(x, y, zoom);
        return QString("http://ecn.t%1.tiles.virtualearth.net/tiles/a%2.jpeg?g=%3&mkt=%4")
            .arg(_getServerNum(x, y, 4)).arg(key, _versionBingMaps, _language);
    }
}

//start_cch_xx_20210129
//1: 高德卫星地图
QString GaodeSatMapProvider::_getURL(const int x, const int y, const int zoom, QNetworkAccessManager* networkManager) {
    Q_UNUSED(networkManager)

      return QStringLiteral("http://webst01.is.autonavi.com/appmaptile?style=6&x=%1&y=%2&z=%3").arg(x).arg(y).arg(zoom);   //高德影像 OK
}

//start_cch_xx_20210129
//1: 高德卫星地图
QString GaodeNewSatMapProvider::_getURL(const int x, const int y, const int zoom, QNetworkAccessManager* networkManager) {
    Q_UNUSED(networkManager)

      return QStringLiteral("http://wprd01.is.autonavi.com/appmaptile?x=%1&y=%2&z=%3&lang=zh_cn&size=1&scl=1&style=6").arg(x).arg(y).arg(zoom);   //高德影像 OK
}

//2: 天地图 需要key
static const QString SatteliteMapUrl = QStringLiteral("http://t0.tianditu.gov.cn/img_w/wmts?SERVICE=WMTS&REQUEST=GetTile&VERSION=1.0.0&LAYER=img&STYLE=default&TILEMATRIXSET=w&FORMAT=tiles&TILEMATRIX=%1&TILEROW=%2&TILECOL=%3&tk=%4");
QString TiandiSatMapProvider::_getURL(const int x, const int y, const int zoom, QNetworkAccessManager* networkManager) {
    Q_UNUSED(networkManager)

//    const QString key = _tileXYToQuadKey(x, y, zoom);
    return SatteliteMapUrl.arg(zoom).arg(y).arg(x).arg(QStringLiteral("3a351e098b778e937c05a85f4bdc2e4e"));   //网页版密钥
}

