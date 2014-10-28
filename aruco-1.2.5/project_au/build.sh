#!/bin/bash

sudo echo "/opt/lib" > /etc/ld.so.conf.d/myapp.conf

sudo ldconfig

export LD_LIBRARY_PATH=/opt/lib/libaruco.so.1.2

g++ main.cpp -I/home/roboto/aruco-1.2.5/src -L/opt/lib -lopencv_highgui -lopencv_core -laruco -lopencv_calib3d -lopencv_imgproc -o project_au

# then run (Note: 0.2 is marker size in mm)
#  sudo bash build.sh && ./project_au live intrinsics_hd5000.yml 0.2
