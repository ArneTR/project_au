
using namespace std;

void showHistogram(const char* name, IplImage* image, CvPoint point, int x_l, int y_l) {

    IplImage* copy_img = cvCloneImage(image);
    
    // create an image with only onee color channel
    IplImage* img_grayscale = cvCreateImage(cvSize(copy_img->width,copy_img->height), copy_img->depth, 1);

    cvCvtColor(copy_img, img_grayscale, CV_RGB2GRAY);

    if( (point.x) >= image->width || (point.y) >= image->height) {
      cout << "--------- WARNING: OUT OF BOUNDS FOR ROI" << endl;
      return;
    }

    if(x_l != 0 && y_l != 0) {
      cout << "Setting roi to " << point.x << ":" << point.y << " with length " << x_l << ":" << y_l << " in image " << image->width << ":" << image->height << endl;
      cvSetImageROI(img_grayscale, cvRect(point.x, point.y, x_l, y_l));
    }

    int histSize = 256;

    /// Set the ranges ( for B,G,R) )
    float range[] = { 0, 256 } ;
    float* histRange[] = { range };

    bool uniform = true; bool accumulate = false;

    CvHistogram* img_hist;

    img_hist =  cvCreateHist(1, &histSize, CV_HIST_ARRAY, histRange, 1);
    
    cvCalcHist( &img_grayscale, img_hist, accumulate, NULL );

  double mean_brightness = cvMean(img_grayscale);
    
    cout << "Having mean of grayscale values for " << name << ": " << mean_brightness << endl;

  char mean_brightness_string[256];
  sprintf(mean_brightness_string, "Brightness: %f", mean_brightness);
  
  CvFont font;
  cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5);
  
  cvPutText(
    image, 
    mean_brightness_string, 
    point,
    &font, 
    cvScalar(127,255,0) // green
  );
  

  //free memory. otherwise program will crash after some time with memory hole
  cvReleaseImage(&img_grayscale);
  cvReleaseImage(&copy_img);
  
}

void createROI(const char* name, IplImage* image, Camera cam, Pose current_pose,  float p1_x, float p1_y, float p1_z, float p2_x, float p2_y, float p2_z) {

    // create a reactangle by using a point in the center of the marker and a point exactly one marker length to the left and one to the top
    CvPoint3D32f corner_top_left_x = cvPoint3D32f(p1_x, p1_y, p1_z);
    CvPoint3D32f corner_bottom_right = cvPoint3D32f(p2_x, p2_y, p2_z);

    CvPoint2D32f corner_top_left_x_2d;
    CvPoint2D32f corner_bottom_right_2d;

    cam.ProjectPoint(corner_top_left_x, &current_pose, corner_top_left_x_2d);
    cam.ProjectPoint(corner_bottom_right, &current_pose, corner_bottom_right_2d);

    CvPoint corner_top_left_x_2d_projected = cvPointFrom32f(corner_top_left_x_2d);
    CvPoint corner_bottom_right_2d_projected = cvPointFrom32f(corner_bottom_right_2d);
    
    cvRectangle(image,corner_top_left_x_2d_projected, corner_bottom_right_2d_projected, CV_RGB(255,255,0));

   
    
    showHistogram(
      name, 
      image, 
      corner_top_left_x_2d_projected, 
      abs(corner_top_left_x_2d_projected.x-corner_bottom_right_2d_projected.x), //width
      abs(corner_top_left_x_2d_projected.y-corner_bottom_right_2d_projected.y) //height
    );

}