/* GStreamer
 * (c) 2005 Ronald S. Bultje <rbultje@ronald.bitfreak.net>
 * (c) 2006 Jan Schmidt <thaytan@noraisin.net>
 * (c) 2008 Stefan Kost <ensonic@users.sf.net>
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

/**
 * SECTION:element-autoaudiosrc
 * @title: autoaudiosrc
 * @see_also: autovideosrc, alsasrc, osssrc
 *
 * autoaudiosrc is an audio source that automatically detects an appropriate
 * audio source to use.  It does so by scanning the registry for all elements
 * that have "Source" and "Audio" in the class field
 * of their element information, and also have a non-zero autoplugging rank.
 *
 * ## Example launch line
 * |[
 * gst-launch-1.0 -v -m autoaudiosrc ! audioconvert ! audioresample ! autoaudiosink
 * ]|
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "gstautoaudiosrc.h"

G_DEFINE_TYPE (GstAutoAudioSrc, gst_auto_audio_src, GST_TYPE_AUTO_DETECT);

static GstStaticPadTemplate src_template = GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS_ANY);

static GstElement *
gst_auto_audio_src_create_fake_element (GstAutoDetect * autodetect)
{
  GstElement *fake;

  fake = gst_element_factory_make ("audiotestsrc", "fake-auto-audio-src");
  if (fake != NULL) {
    g_object_set (fake, "is-live", TRUE, NULL);
    gst_util_set_object_arg (G_OBJECT (fake), "wave", "silence");
  } else {
    GST_ELEMENT_ERROR (autodetect, RESOURCE, NOT_FOUND,
        ("Failed to find usable audio source element."),
        ("Failed to find a usable audio source and couldn't create an audio"
            "testsrc as fallback either, check your GStreamer installation."));
    /* This will error out with not-negotiated.. */
    fake = gst_element_factory_make ("fakesrc", "fake-auto-audio-src");
  }
  return fake;
}

static void
gst_auto_audio_src_class_init (GstAutoAudioSrcClass * klass)
{
  GstAutoDetectClass *autoclass = GST_AUTO_DETECT_CLASS (klass);
  GstElementClass *eklass = GST_ELEMENT_CLASS (klass);

  gst_element_class_add_static_pad_template (eklass, &src_template);
  gst_element_class_set_static_metadata (eklass, "Auto audio source",
      "Source/Audio",
      "Wrapper audio source for automatically detected audio source",
      "Jan Schmidt <thaytan@noraisin.net>, "
      "Stefan Kost <ensonic@users.sf.net>");

  autoclass->create_fake_element = gst_auto_audio_src_create_fake_element;
}

static void
gst_auto_audio_src_init (GstAutoAudioSrc * src)
{
  GstAutoDetect *autodetect = GST_AUTO_DETECT (src);

  autodetect->media_klass = "Audio";
  autodetect->flag = GST_ELEMENT_FLAG_SOURCE;
}
