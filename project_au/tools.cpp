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

  CvMat *euler_matrix = cvCreateMat(3, 1, CV_64FC1);
  p.GetEuler(euler_matrix);

  sp.alpha = cvmGet(euler_matrix,0,0);
  sp.beta = cvmGet(euler_matrix,1,0);
  sp.gamma = cvmGet(euler_matrix,2,0);

  return sp;

}

bool isPencilMarker(int id) {

  if(id == 68 || id == 79 || id == 176 || id == 187 || id == 255 ) return true;
  else return false;
}