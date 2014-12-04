

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
  #define WATCHER_SOCKET_PORT 11115

  #define PENCIL_LENGTH 235.0 // should be 146.0 later on

  // always use marker sizes in edge_length consisting of white inner pixels + black margin
  #define MARKER_SIZE 45.0 // mm  32 vs. 45
  
  #define MARKER_RESOLUTION 5
  #define MARKER_BLACK_MARGIN_RESOLUTION 1.0
  #define MARKER_BLACK_MARGIN 6.5

  #define MARKER_WHITE_MARGIN_RESOLUTION 1.0
  #define MARKER_WHITE_MARGIN 6.0

  #define ROBOT_MARKER 0
  #define ROBOT_MARKER_SIZE 62.0 // mm
  

  #define TIME_AVERAGE_POSES 5.0

  #define BRIGHTNESS_MARGIN 70
#endif

SIMPLE_POSE getSimplePose(Pose p);