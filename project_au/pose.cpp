#include "CvTestbed.h"
#include "MarkerDetector.h"
#include "GlutViewer.h"
#include "Shared.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "tools.hpp"



void showPose(int number, int id, Pose p, Drawable* d) {
    
    p.GetMatrixGL(d[number].gl_mat); // set the projection matrix to the drawable

      
    double r = 1.0 - double(id+1)/32.0;
    double g = 1.0 - double(id*3%32+1)/32.0;
    double b = 1.0 - double(id*7%32+1)/32.0;
    
    d[number].SetColor(r, g, b);

    GlutViewer::DrawableAdd(&(d[number]));

}

Pose calculateTipPose(Pose p) {
    
    Pose tip_pose = p; // makes a copy
    
    tip_pose.Reset();
    
    tip_pose.SetTranslation( // set the target translation (only valid for side-markers)
      0, 
      PENCIL_LENGTH,
      -MARKER_SIZE/2
    );

    CvMat *current_matrix = cvCreateMat(4, 4, CV_64FC1);
    p.GetMatrix(current_matrix); // load current rotation in empty matrix

    CvMat *tip_matrix = cvCreateMat(4, 4, CV_64FC1);
    tip_pose.GetMatrix(tip_matrix); // get current tip matrix (should be empty after reset)

    CvMat *result = cvCreateMat(4,4, CV_64FC1);

    // note that sequence of multiplication matters
    // If you multiply current with tip, then the movement of the tip done earlier will be assumend
    // in the markers inherent coordinate system
    //
    // if you multiply tip with current then the translation will be done in reference to the camera
    cvMatMul(current_matrix, tip_matrix, result);

    tip_pose.SetMatrix(result);

    // now we rotate the marker 90 degrees
    CvMat *euler_matrix = cvCreateMat(3, 1, CV_64FC1);
    tip_pose.GetEuler(euler_matrix);

    //cout << "Current euler:" << cvmGet(euler_matrix,0,0) << " ; " << cvmGet(euler_matrix,1,0) << " ; " << cvmGet(euler_matrix,2,0) << endl; 

    cvmSet(euler_matrix, 2, 0, cvmGet(euler_matrix,2,0) - 90.0); // rotate 90 degrees (only valid for side markers)

    //cout << "Shifted euler:" << cvmGet(euler_matrix,0,0) << " ; " << cvmGet(euler_matrix,1,0) << " ; " << cvmGet(euler_matrix,2,0) << endl; 


    tip_pose.SetEuler(euler_matrix);

    return tip_pose;
}

Pose calculatePoseRelativeToRobotMarker(Pose robot_marker_pose, Pose p) {
    
    Pose pose = p; // makes a copy, just in case
    
    CvMat *robot_marker_matrix = cvCreateMat(4, 4, CV_64FC1);
    CvMat *inv_robot_marker_matrix = cvCreateMat(4, 4, CV_64FC1);
    robot_marker_pose.GetMatrix(robot_marker_matrix); // load current rotation in empty matrix

    CvMat *pose_matrix = cvCreateMat(4, 4, CV_64FC1);
    pose.GetMatrix(pose_matrix); 

    CvMat *result = cvCreateMat(4,4, CV_64FC1);

    // Calculate inverse to get 0->Cam1 from Cam1->0
    cvInv(robot_marker_matrix, inv_robot_marker_matrix, CV_LU);


    // now calcualte 0->Cam1 * C1->M = 0->M
    cvMatMul(inv_robot_marker_matrix, pose_matrix, result);

    pose.SetMatrix(result);

    return pose;
}

Pose transformPoseRelativeToCam(Pose robot_marker_pose, Pose p) {
    
    Pose transformation_pose = p; // makes a copy, just in case
    
    CvMat *robot_marker_matrix = cvCreateMat(4, 4, CV_64FC1);
    robot_marker_pose.GetMatrix(robot_marker_matrix); // load current rotation in empty matrix

    CvMat *transformation_pose_matrix = cvCreateMat(4, 4, CV_64FC1);
    transformation_pose.GetMatrix(transformation_pose_matrix); 

    CvMat *result = cvCreateMat(4,4, CV_64FC1);

    // now calcualte Cam2->0 * 0->M = Cam2->M
    cvMatMul(robot_marker_matrix, transformation_pose_matrix, result);

    transformation_pose.SetMatrix(result);

    return transformation_pose;
}


void markTip(IplImage *image, Camera cam, Pose avg_pose) {
  CvPoint3D32f point_3d = cvPoint3D32f(0.0,0.0,0); // move one half marker size to the center of the cube

  CvPoint2D32f point_2d;

  cam.ProjectPoint(point_3d, &avg_pose, point_2d);

  CvPoint projected_point = cvPointFrom32f(point_2d);

  CvPoint3D32f point_from_3d = cvPoint3D32f(0.0,0.0,0); // move one half marker size to the center of the cube
  CvPoint3D32f point_to_3d = cvPoint3D32f(0.0,0.0,10.0); // move from the center of the cube to the pencil tip

  CvPoint2D32f point_from_2d;
  CvPoint2D32f point_to_2d;

  cam.ProjectPoint(point_from_3d, &avg_pose, point_from_2d);
  cam.ProjectPoint(point_to_3d, &avg_pose, point_to_2d);

  CvPoint from = cvPointFrom32f(point_from_2d);
  CvPoint to = cvPointFrom32f(point_to_2d);

  cvLine(image, from, to, CV_RGB(255,255,0)); // draw a line from the cube center to the pencil tip

  // draw a circle at (100,100) with a radius of 20. Use green lines of width 1
  cvCircle(image, projected_point, 5, cvScalar(0,255,0), 1);
}

void showPoseCoordinates(IplImage* image, Camera cam, Pose current_pose, SIMPLE_POSE aktpos) {
  CvPoint3D32f point = cvPoint3D32f(aktpos.x, aktpos.y, aktpos.z);
    
  CvPoint2D32f point_2d;

  cam.ProjectPoint(point, &current_pose, point_2d);

  CvPoint point_2d_projected = cvPointFrom32f(point_2d);

  char text[256];
  sprintf(text, "Pos: %d, %d, %d", (int) aktpos.x, (int) aktpos.y, (int) aktpos.z);

  CvFont font;
  cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5);

  cvPutText(
    image, 
    text, 
    point_2d_projected,
    &font, 
    cvScalar(127,255,0) // green
  );

  cvCircle(image, point_2d_projected, 5, cvScalar(0,255,0), 1);
}