#include "tools.hpp"

SIMPLE_POSE getSimplePose(Pose p) {
  CvMat *current_translation = cvCreateMat(3, 1, CV_64FC1);

  SIMPLE_POSE sp;

  p.GetTranslation(current_translation);

  sp.x = cvmGet(current_translation,0,0);
  sp.y = cvmGet(current_translation,1,0);
  sp.z = cvmGet(current_translation,2,0);

  CvMat *quaternion = cvCreateMat(4, 1, CV_64FC1);
  p.GetQuaternion(quaternion);

  sp.R = cvmGet(quaternion,0,0);
  sp.i1 = cvmGet(quaternion,1,0);
  sp.i2 = cvmGet(quaternion,2,0);
  sp.i3 = cvmGet(quaternion,3,0);

  return sp;

}