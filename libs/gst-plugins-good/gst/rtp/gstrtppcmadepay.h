/* GStreamer
 * Copyright (C) <2005> Edgard Lima <edgard.lima@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more 
 */
 
#ifndef __GST_RTP_PCMA_DEPAY_H__
#define __GST_RTP_PCMA_DEPAY_H__

#include <gst/gst.h>
#include <gst/rtp/gstrtpbasedepayload.h>

G_BEGIN_DECLS

typedef struct _GstRtpPcmaDepay GstRtpPcmaDepay;
typedef struct _GstRtpPcmaDepayClass GstRtpPcmaDepayClass;

#define GST_TYPE_RTP_PCMA_DEPAY \
  (gst_rtp_pcma_depay_get_type())
#define GST_RTP_PCMA_DEPAY(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_RTP_PCMA_DEPAY,GstRtpPcmaDepay))
#define GST_RTP_PCMA_DEPAY_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_RTP_PCMA_DEPAY,GstRtpPcmaDepayClass))
#define GST_IS_RTP_PCMA_DEPAY(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_RTP_PCMA_DEPAY))
#define GST_IS_RTP_PCMA_DEPAY_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_RTP_PCMA_DEPAY))

struct _GstRtpPcmaDepay
{
  GstRTPBaseDepayload depayload;
};

struct _GstRtpPcmaDepayClass
{
  GstRTPBaseDepayloadClass parent_class;
};

GType gst_rtp_pcma_depay_get_type (void);

gboolean gst_rtp_pcma_depay_plugin_init (GstPlugin * plugin);

G_END_DECLS

#endif /* __GST_RTP_PCMA_DEPAY_H__ */
