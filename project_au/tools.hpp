

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
#endif

SIMPLE_POSE getSimplePose(Pose p);