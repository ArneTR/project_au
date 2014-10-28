#include <math.h>
#include <cmath>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#ifndef TOOLS_H_
#define TOOLS_H_

  typedef struct SIMPLE_POSE{
    int type;
    double x;
    double y;
    double z;
    double R;
    double i1;
    double i2;
    double i3;
    double phi;
    double alpha;
    double beta;
    double gamma;
  }SIMPLE_POSE;

  #define RGB_RED cv::Scalar(0,0,255,255)
  #define RGB_GREEN cv::Scalar(0,255,0,255)
  #define RGB_BLUE cv::Scalar(255,0,0,255)

  #define DISTANCE_CUBE_CORE_PENCIL_TIP 0.08

  #define X 0
  #define Y 1
  #define Z 2


  #define APP_SOCKET_PORT 11113
  #define ROBOT_SOCKET_PORT 11114
  #define WATCHER_SOCKET_PORT 11115

  #define PENCIL_LENGTH 146.0 // should be 146.0 later on

  #define MARKER_SIZE 44.8 // mm
  #define MARKER
  #define MARKER_RESOLUTION 5
  #define MARKER_BLACK_MARGIN_RESOLUTION 1.0
  #define MARKER_BLACK_MARGIN 6.0

  #define MARKER_WHITE_MARGIN_RESOLUTION 1.0
  #define MARKER_WHITE_MARGIN 6.0

  #define ROBOT_MARKER 0
  #define ROBOT_MARKER_SIZE 124.0

  #define TIME_AVERAGE_POSES 5.0

  #define BRIGHTNESS_MARGIN 40
#endif

SIMPLE_POSE getSimplePose(aruco::Marker m);

SIMPLE_POSE getSimplePose(cv::Mat m);


void QuatNorm(double *q);

int Sign(const double v);

void RodToMat9(cv::Mat Rvec, double *mat9);

void QuatToEul(const double *q, double *eul);

void Mat9ToQuat(const double *mat, double *quat);