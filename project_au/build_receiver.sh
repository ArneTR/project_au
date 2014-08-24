#!/bin/bash

#sudo echo "/home/roboto/alvar-master/build" > /etc/ld.so.conf.d/myapp.conf

#sudo ldconfig

#export LD_LIBRARY_PATH=/home/roboto/alvar-master/build/libalvar200.so:/home/roboto/alvar-master/build/libalvarplatform200.so

#c++ draw_pencil.cpp -I/home/roboto/alvar-master/sample -I/home/roboto/alvar-master/build/src -I/home/roboto/alvar-master/src/platform -I/usr/include/opencv -I/home/roboto/alvar-master/src -L/opt/lib -L/home/roboto/alvar-master/build/src -L/home/roboto/alvar-master/build/src/platform -lalvar200 -lalvarplatform200 -L/home/roboto/alvar-master/build/capture_plugin_highgui-lalvarcapturepluginhighgui200 `pkg-config --cflags --libs opencv` -o draw_pencil

g++ receiver.cpp -fpermissive -I/home/roboto/alvar-master/sample -I/home/roboto/alvar-master/build/src -I/usr/include/opencv -I/home/roboto/alvar-master/src/platform -I/home/roboto/alvar-master/src -rdynamic /usr/local/lib/libopencv_calib3d.so.2.4.9 /usr/local/lib/libopencv_core.so.2.4.9 /usr/local/lib/libopencv_features2d.so.2.4.9 /usr/local/lib/libopencv_flann.so.2.4.9 /usr/local/lib/libopencv_highgui.so.2.4.9 /usr/local/lib/libopencv_imgproc.so.2.4.9 /usr/local/lib/libopencv_legacy.so.2.4.9 /usr/local/lib/libopencv_ml.so.2.4.9 /usr/local/lib/libopencv_video.so.2.4.9 ../build/libalvar200.so /usr/local/lib/libopencv_calib3d.so.2.4.9 /usr/local/lib/libopencv_core.so.2.4.9 /usr/local/lib/libopencv_features2d.so.2.4.9 /usr/local/lib/libopencv_flann.so.2.4.9 /usr/local/lib/libopencv_highgui.so.2.4.9 /usr/local/lib/libopencv_imgproc.so.2.4.9 /usr/local/lib/libopencv_legacy.so.2.4.9 /usr/local/lib/libopencv_ml.so.2.4.9 /usr/local/lib/libopencv_video.so.2.4.9 ../build/3rdparty/libTinyXML.a ../build/libalvarplatform200.so ../build/sample/libSharedSamples.a ../build/sample/libSharedGlutViewer.a /usr/local/lib/libopencv_legacy.so.2.4.9 /usr/local/lib/libopencv_calib3d.so.2.4.9 /usr/local/lib/libopencv_features2d.so.2.4.9 /usr/local/lib/libopencv_flann.so.2.4.9 /usr/local/lib/libopencv_highgui.so.2.4.9 /usr/local/lib/libopencv_ml.so.2.4.9 /usr/local/lib/libopencv_video.so.2.4.9 /usr/local/lib/libopencv_imgproc.so.2.4.9 /usr/local/lib/libopencv_core.so.2.4.9 -lGLU -lGL -lSM -lICE -lX11 -lXext -lglut -Wl,-rpath,/usr/local/lib:/home/roboto/alvar-master/build/src:/home/roboto/alvar-master/build/src/platform -o receiver


# then run
#  sudo bash build.sh && ./draw_pencil live intrinsics.yml 0.2

