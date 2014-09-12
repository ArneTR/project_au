

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

  #define APP_SOCKET_PORT 11113
  #define ROBOT_SOCKET_PORT 11114

  #define PENCIL_LENGTH 146.0 // should be 146.0 later on

  #define MARKER_SIZE 46.0 // mm
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

SIMPLE_POSE getSimplePose(Pose p);