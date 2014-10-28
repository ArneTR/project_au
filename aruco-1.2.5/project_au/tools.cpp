#include "tools.hpp"


SIMPLE_POSE getSimplePose(aruco::Marker m) {
  
  
  SIMPLE_POSE sp;


  
  sp.x = m.Tvec.at<float>(0,0);  
  sp.y = m.Tvec.at<float>(1,0);
  sp.z = m.Tvec.at<float>(2,0);


  double *quat = new double[4];
  double *mat9 = new double[9];
  double *eul = new double[3];

  RodToMat9(m.Rvec, mat9);
  
  Mat9ToQuat(mat9, quat);

  QuatToEul(quat, eul);

  sp.R = quat[0];
  sp.i1 = quat[1];
  sp.i2 = quat[2];
  sp.i3 = quat[3];


  sp.alpha = eul[0];  
  sp.beta = eul[1];  
  sp.gamma = eul[2];  

  return sp;

  

}

SIMPLE_POSE getSimplePose(cv::Mat m) {
  
  
  SIMPLE_POSE sp;


  
  sp.x = m.at<float>(0,3);  
  sp.y = m.at<float>(1,3);
  sp.z = m.at<float>(2,3);


  cv::Mat rvec( 3,1,CV_32FC1 ); 
  cv::Mat rod = cv::Mat::eye( 3,3,CV_32FC1 ); 

  rod.at<float>(0,0) = m.at<float>(0,0);
  rod.at<float>(0,1) = m.at<float>(0,1);
  rod.at<float>(0,2) = m.at<float>(0,2);
  rod.at<float>(1,0) = m.at<float>(1,0);
  rod.at<float>(1,1) = m.at<float>(1,1);
  rod.at<float>(1,2) = m.at<float>(1,2);
  rod.at<float>(2,0) = m.at<float>(2,0);
  rod.at<float>(2,1) = m.at<float>(2,1);
  rod.at<float>(2,2) = m.at<float>(2,2);

  cv::Rodrigues(rod, rvec);


  double *quat = new double[4];
  double *mat9 = new double[9];
  double *eul = new double[3];

  RodToMat9(rvec, mat9);
  
  Mat9ToQuat(mat9, quat);

  QuatToEul(quat, eul);

  sp.R = quat[0];
  sp.i1 = quat[1];
  sp.i2 = quat[2];
  sp.i3 = quat[3];


  sp.alpha = eul[0];  
  sp.beta = eul[1];  
  sp.gamma = eul[2];  

  return sp;

  

}

bool isPencilMarker(int id) {

  if(id == 150 || id == 100 ) return true;
  else return false;
}

void QuatNorm(double *q)
{
  double l = sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3] );
  
  if(l != 0)
    for(unsigned i = 0; i < 4; ++i)
      q[i] = q[i] / l;
}

int Sign(const double v)
{
  return (v<0?-1:1);
}

void RodToMat9(cv::Mat Rvec, double *mat9)
{
  cv::Mat Rot(3,3,CV_32FC1);
  cv::Rodrigues(Rvec, Rot);

  mat9[0] = Rot.at<float>(0,0);
  mat9[1] = Rot.at<float>(0,1);
  mat9[2] = Rot.at<float>(0,2);
  mat9[3] = Rot.at<float>(1,0);
  mat9[4] = Rot.at<float>(1,1);
  mat9[5] = Rot.at<float>(1,2);
  mat9[6] = Rot.at<float>(2,0);
  mat9[7] = Rot.at<float>(2,1);
  mat9[8] = Rot.at<float>(2,2);


}

void QuatToEul(const double *q, double *eul)
{
  double qw = q[0];
  double qx = q[1];
  double qy = q[2];
  double qz = q[3];

  double heading = 0, bank = 0, attitude = 0;

  if ((2*qx*qy + 2*qz*qw) == 1.0)
  {
    heading = 2 * atan2(qx,qw);
    bank = 0;
  }
  else if ((2*qx*qy + 2*qz*qw) == -1.0)
  {
    heading = -2 * atan2(qx,qw);
    bank = 0;
  }
  else
  {
    heading = atan2(2*qy*qw-2*qx*qz , 1 - 2*qy*qy - 2*qz*qz);
    bank    = atan2(2*qx*qw-2*qy*qz , 1 - 2*qx*qx - 2*qz*qz);
  }

  attitude = asin(2*qx*qy + 2*qz*qw);

  heading  = 180.0 * heading  / M_PI;
  attitude = 180.0 * attitude / M_PI;
  bank     = 180.0 * bank     / M_PI;

  eul[0] = heading;
  eul[1] = attitude;
  eul[2] = bank;
}

void Mat9ToQuat(const double *mat, double *quat)
{

  quat[0] = sqrt(max(0., 1 + mat[0] + mat[4] + mat[8])) / 2.0;  // w
  quat[1] = sqrt(max(0., 1 + mat[0] - mat[4] - mat[8])) / 2.0;  // x
  quat[2] = sqrt(max(0., 1 - mat[0] + mat[4] - mat[8])) / 2.0;  // y
  quat[3] = sqrt(max(0., 1 - mat[0] - mat[4] + mat[8])) / 2.0;  // z

  quat[1] = quat[1]*Sign(mat[7] - mat[5]); // x
  quat[2] = quat[2]*Sign(mat[2] - mat[6]); // y
  quat[3] = quat[3]*Sign(mat[3] - mat[1]); // z

  QuatNorm(quat);

}