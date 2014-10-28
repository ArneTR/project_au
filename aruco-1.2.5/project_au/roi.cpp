
double showHistogram(cv::Mat image, cv::Point point, int x_l, int y_l) {

    int histSize = 256;

    /// Set the ranges ( for B,G,R) )
    float range[] = { 0, 256 } ;
    float* histRange[] = { range };
    int channels[] = {0, 1};

    bool uniform = true; 
    bool accumulate = false;
   
    cv::Mat img_grayscale = image.clone();
    
    cv::cvtColor(image, img_grayscale, CV_RGB2GRAY);

    if( (point.x) >= image.cols || (point.y) >= image.rows) {
      std::cout << "--------- WARNING: OUT OF BOUNDS FOR ROI" << endl;
      return 0.0;
    }

    if(x_l == 0 || y_l == 0) return 0.0;


    std::cout << "Setting roi to " << point.x << ":" << point.y << " with length " << x_l << ":" << y_l << " in image " << image.cols << ":" << image.rows << endl;
    cv::Rect region_of_interest = cv::Rect(point.x, point.y, x_l, y_l);
    cv::Mat image_roi(img_grayscale, region_of_interest);
    
/* Real histogram not needed for now
    Mat img_hist;

    cv::calcHist( &img_grayscale, 1, channels, 
      Mat(), // do not use mask
      img_hist, // output Mat (image)
      2,  // dimensions
      histSize, 
      histRange,
      uniform, // the histogram is uniform
      accumulate 
    );
*/

    cv::Scalar mean_brightness = cv::mean(img_grayscale);

    std::cout << "Having mean of grayscale values of: " << mean_brightness[0] << std::endl;

    return mean_brightness[0];
}

/*
double createROI(Mat image, Camera cam, Pose current_pose,  float p1_x, float p1_y, float p1_z, float p2_x, float p2_y, float p2_z) {

    // create a reactangle by using a point in the center of the marker and a point exactly one marker length to the left and one to the top
    CvPoint3D32f corner_top_left_x = cvPoint3D32f(p1_x, p1_y, p1_z);
    CvPoint3D32f corner_bottom_right = cvPoint3D32f(p2_x, p2_y, p2_z);

    CvPoint2D32f corner_top_left_x_2d;
    CvPoint2D32f corner_bottom_right_2d;

    cam.ProjectPoint(corner_top_left_x, &current_pose, corner_top_left_x_2d);
    cam.ProjectPoint(corner_bottom_right, &current_pose, corner_bottom_right_2d);

    CvPoint corner_top_left_x_2d_projected = cvPointFrom32f(corner_top_left_x_2d);
    CvPoint corner_bottom_right_2d_projected = cvPointFrom32f(corner_bottom_right_2d);
    
    if(show_roi) cvRectangle(image,corner_top_left_x_2d_projected, corner_bottom_right_2d_projected, CV_RGB(255,255,0));

   
    
    return showHistogram(
      image, 
      corner_top_left_x_2d_projected, 
      abs(corner_top_left_x_2d_projected.x-corner_bottom_right_2d_projected.x), //width
      abs(corner_top_left_x_2d_projected.y-corner_bottom_right_2d_projected.y) //height
    );

}

*/