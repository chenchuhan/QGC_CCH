/* GStreamer
 * Copyright (C) 1999,2000 Erik Walthinsen <omega@cse.ogi.edu>
 *                    2000 Wim Taymans <wtay@chello.be>
 *
 * gstosssrc.h: 
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */


#ifndef __GST_OSS_SRC_H__
#define __GST_OSS_SRC_H__


#include <gst/gst.h>
#include <gst/audio/gstaudiosrc.h>

#include "gstosshelper.h"

G_BEGIN_DECLS

#define GST_TYPE_OSS_SRC           (gst_oss_src_get_type())
#define GST_OSS_SRC(obj)           (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_OSS_SRC,GstOssSrc))
#define GST_OSS_SRC_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_OSS_SRC,GstOssSrcClass))
#define GST_IS_OSS_SRC(obj)        (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_OSS_SRC))
#define GST_IS_OSS_SRC_CLASS(klas) (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_OSS_SRC))

typedef struct _GstOssSrc GstOssSrc;
typedef struct _GstOssSrcClass GstOssSrcClass;

struct _GstOssSrc {
  GstAudioSrc    src;

  gint fd;
  gint           bytes_per_sample;

  gchar *device;
  gchar *device_name;

  GstCaps       *probed_caps;
};

struct _GstOssSrcClass {
  GstAudioSrcClass parent_class;
};

GType gst_oss_src_get_type(void);

G_END_DECLS

#endif /* __GST_OSS_SRC_H__ */
