//gcc -o Rtsp RtspToFrame.c `pkg-config --cflags --libs gstreamer-1.0` ->run C file
//first install gstreamer on your machine


#include <gst/gst.h>
#include<stdio.h>

GstElement *pipeline,*pipe2;
GstBus *bus;
GstMessage *msg;


void break_RtspStream_Into_Frame()
{
		
    pipeline = gst_parse_launch("rtspsrc location=rtsp://admin:Sr2128shubh@10.0.2.15:7001/1?pos=2018-06-20T10:37 ! decodebin ! queue ! autovideoconvert ! pngenc ! multifilesink location=frame%d.png",NULL); 
    gst_element_set_state (pipeline, GST_STATE_PLAYING); //for play
    bus = gst_element_get_bus(pipeline); //wait for EOS
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,GST_MESSAGE_ERROR | GST_MESSAGE_EOS);
  
    if (msg != NULL) // release resource
    gst_message_unref (msg);
    gst_object_unref (bus);
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
}

int main (int argc, char *argv[])
{
  gst_init (&argc, &argv); // initiliaze gstreamer 
  break_RtspStream_Into_Frame(); //method call
  return 0;			   
}



//gst-launch-1.0 playbin uri=rtsp://admin:Sr2128shubh@10.0.2.15:7001/1?pos=2018-06-20T10:37&resolution=240p -> launch rtsp

//gst-launch-1.0 rtspsrc location=rtsp://admin:Sr2128shubh@10.0.2.15:7001/2?pos=2018-09-28T11:51 ! queue ! rtph264depay ! h264parse ! mp4mux ! filesink location=result3.mp4 -> download rtsp

//gst-launch-1.0 --gst-debug-level=3 filesrc location=result3.mp4 ! decodebin ! queue ! videoconvert ! pngenc ! multifilesink location="frame%d.png" -> convert it into frame rtsp (from local storage)

//gst-launch-1.0 --gst-debug-level=3 rtspsrc location=rtsp://admin:Sr2128shubh@10.0.2.15:7001/1?pos=2018-06-20T10:37 ! decodebin ! queue ! autovideoconvert ! pngenc ! multifilesink location=frame%d.png -> download rtsp + convert it into frame rtsp

//gst-launch-1.0 -e multifilesrc location="frame%d.png" caps="image/png,framerate=30/1" ! pngdec ! videoconvert ! queue ! x264enc ! queue !   mp4mux ! filesink location=image.mp4  -> convert frame into video stream

//gst-launch-1.0 rtspsrc location=rtsp://admin:Sr2128shubh@10.0.2.15:7001/1?pos=2018-06-20T10:37 ! decodebin ! queue !   autovideoconvert ! videorate ! video/x-raw,framerate=10/1 ! pngenc ! multifilesink location=framed/frame%d.png  ->according framerate







