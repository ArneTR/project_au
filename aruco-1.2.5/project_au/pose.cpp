#include "tools.hpp"

aruco::Marker calculateTipPose(aruco::Marker m, aruco::CameraParameters TheCameraParameters) {

    ::aruco::Marker return_marker = aruco::Marker(m);
   
    cv::Mat t = cv::Mat::eye( 4,4,CV_32FC1 ); 


    /** 
     * Translation
    */
    if(m.id == 255) { // top_marker
      t.at<float>(2,3) = - (MARKER_WHITE_MARGIN) -(MARKER_SIZE/2) - (PENCIL_LENGTH);
    } else {
      t.at<float>(1,3) = PENCIL_LENGTH;
      t.at<float>(2,3) = -(MARKER_SIZE/2) - (MARKER_WHITE_MARGIN);
    }


    /**
     * Rotation
    */
    if(m.id == 255) {
      t.at<float>(0,0) = -1;
      t.at<float>(0,1) = 0;
      t.at<float>(0,2) = 3.58979e-09;
      t.at<float>(1,0) = 0;
      t.at<float>(1,1) = 1;
      t.at<float>(1,2) = 0;
      t.at<float>(2,0) = -3.58979e-09;
      t.at<float>(2,1) = 0;
      t.at<float>(2,2) = -1;
    } else if(m.id == 187) {
      t.at<float>(0,0) = 1.7949e-09;
      t.at<float>(0,1) = 1;
      t.at<float>(0,2) = -1.7949e-09;
      t.at<float>(1,0) = 5.55112e-17;
      t.at<float>(1,1) = 1.7949e-09;
      t.at<float>(1,2) = 1;
      t.at<float>(2,0) = 1;
      t.at<float>(2,1) = -1.7949e-09;
      t.at<float>(2,2) = 0;
    }/* else if(id == 176) {
      t.at<float>(0,0) = -1;
      t.at<float>(0,1) = 1.7949e-09;
      t.at<float>(0,2) = 1.7949e-09;
      t.at<float>(1,0) = -1;
      t.at<float>(1,1) = 1.7949e-09;
      t.at<float>(1,2) = 1.7949e-09;
      t.at<float>(2,0) = -1;
      t.at<float>(2,1) = 1.7949e-09;
      t.at<float>(2,2) = 1.7949e-09;
    } else if(id == 68) {
      t.at<float>(0,0) = -1;
      t.at<float>(0,1) = 1.7949e-09;
      t.at<float>(0,2) = 1.7949e-09;
      t.at<float>(1,0) = -1;CameraParameters
      t.at<float>(1,1) = 1.7949e-09;
      t.at<float>(1,2) = 1.7949e-09;
      t.at<float>(2,0) = -1;
      t.at<float>(2,1) = 1.7949e-09;
      t.at<float>(2,2) = 1.7949e-09;
    } else if(id == 79) {
      t.at<float>(0,0) = -1;
      t.at<float>(0,1) = 1.7949e-09;
      t.at<float>(0,2) = 1.7949e-09;
      t.at<float>(1,0) = -1;
      t.at<float>(1,1) = 1.7949e-09;
      t.at<float>(1,2) = 1.7949e-09;
      t.at<float>(2,0) = -1;
      t.at<float>(2,1) = 1.7949e-09;
      t.at<float>(2,2) = 1.7949e-09;
    }*/


    
    // note that sequence of multiplication matters
    // If you multiply current with tip, then the movement of the tip done earlier will be assumend
    // in the markers inherent coordinate system
    //
    // if you multiply tip with current then the translation will be done in reference to the camera
    cv::Mat transformed_matrix = TheCameraParameters.getRTMatrix(m.Rvec, m.Tvec, -1) * t;


    m.Tvec.at<float>(0,0) = transformed_matrix.at<float>(0,3);
    m.Tvec.at<float>(1,0) = transformed_matrix.at<float>(1,3);
    m.Tvec.at<float>(2,0) = transformed_matrix.at<float>(2,3);

    cv::Mat rod = cv::Mat::eye( 3,3,CV_32FC1 ); 

    rod.at<float>(0,0) = transformed_matrix.at<float>(0,0);
    rod.at<float>(0,1) = transformed_matrix.at<float>(0,1);
    rod.at<float>(0,2) = transformed_matrix.at<float>(0,2);
    rod.at<float>(1,0) = transformed_matrix.at<float>(1,0);
    rod.at<float>(1,1) = transformed_matrix.at<float>(1,1);
    rod.at<float>(1,2) = transformed_matrix.at<float>(1,2);
    rod.at<float>(2,0) = transformed_matrix.at<float>(2,0);
    rod.at<float>(2,1) = transformed_matrix.at<float>(2,1);
    rod.at<float>(2,2) = transformed_matrix.at<float>(2,2);

    cv::Rodrigues(rod, m.Rvec);

    return m;
}
/*


Pose transformPoseRelativeToCam(Pose robot_marker_pose, Pose p) {
    
    CvMat *robot_marker_matrix = cvCreateMat(4, 4, CV_64FC1);
    robot_marker_pose.GetMatrix(robot_marker_matrix); // load current rotation in empty matrix

    CvMat *transformation_pose_matrix = cvCreateMat(4, 4, CV_64FC1);
    p.GetMatrix(transformation_pose_matrix); 

    CvMat *result = cvCreateMat(4,4, CV_64FC1);

    // now calcualte Cam2->0 * 0->M = Cam2->M
    cvMatMul(robot_marker_matrix, transformation_pose_matrix, result);

    Pose transformation_pose;
    transformation_pose.Reset();

    transformation_pose.SetMatrix(result);

    return transformation_pose;
}

*/
void markTip(cv::Mat image, aruco::CameraParameters TheCameraParameters, aruco::Marker m) {
  

  cv::Mat objectPoints (2,3,CV_32FC1); // 
  objectPoints.at<float>(0,X)=0; // point 0, pos x
  objectPoints.at<float>(0,Y)=0; // point 0, pos y
  objectPoints.at<float>(0,Z)=0; // point 0, pos z

  objectPoints.at<float>(1,X)=0; // point 0, pos x
  objectPoints.at<float>(1,Y)=0; // point 0, pos y
  objectPoints.at<float>(1,Z)=10.0; // point 0, pos z

  vector<cv::Point2f> imagePoints; // resulting pints

  cv::projectPoints( objectPoints, m.Rvec,m.Tvec, TheCameraParameters.CameraMatrix,TheCameraParameters.Distorsion,   imagePoints);
  std::cout << "Resulting points: " << imagePoints << std::endl;          

  cv::line(image, imagePoints[0], imagePoints[1], RGB_RED ,1,CV_AA); // draw a line from the cube center to the pencil tip

  // draw a circle at (100,100) with a radius of 20. Use green lines of width 1
  cv::circle(image, imagePoints[0], 5, RGB_RED, 1);
}

void showPoseCoordinates(cv::Mat image, aruco::CameraParameters TheCameraParameters, aruco::Marker m, int x, int y, int z) {
  
  cv::Mat objectPoints (1,3,CV_32FC1); // 
  objectPoints.at<float>(0,X)=0; // point 0, pos x
  objectPoints.at<float>(0,Y)=0; // point 0, pos y
  objectPoints.at<float>(0,Z)=0; // point 0, pos z

  vector<cv::Point2f> imagePoints; // resulting pints

  cv::projectPoints( objectPoints, m.Rvec,m.Tvec, TheCameraParameters.CameraMatrix,TheCameraParameters.Distorsion,   imagePoints);
 

  char text[256];
  sprintf(text, "Pos: %d, %d, %d", x, y, z);

  cv::putText(image,
    text, 
    imagePoints[0],cv::FONT_HERSHEY_SIMPLEX, 0.6, RGB_GREEN,2);
  ;


  cv::circle(image, imagePoints[0], 5, RGB_GREEN, 1);
}
