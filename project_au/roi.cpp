
using namespace std;

double showHistogram(bool show_roi, IplImage* image, CvPoint point, int x_l, int y_l) {

    IplImage* copy_img = cvCloneImage(image);
    
    // create an image with only onee color channel
    IplImage* img_grayscale = cvCreateImage(cvGetSize(copy_img), copy_img->depth, 1);
    IplImage* roi = cvCreateImage(cvGetSize(copy_img), copy_img->depth, 1);
    IplImage* res = cvCreateImage(cvGetSize(copy_img), copy_img->depth, 1);

    cvCvtColor(copy_img, img_grayscale, CV_RGB2GRAY);

    int radius = 0;
    if(x_l > y_l) radius = x_l;
    else radius = y_l;
    if( (point.x-radius) >= image->width || (point.y-radius) >= image->height
      ||
      (point.x-radius) <= 0 || (point.y-radius) <= 0
    ) {
      cout << "--------- WARNING: OUT OF BOUNDS FOR ROI" << endl;
      return 0.0;
    }

    cvZero(roi);
    
    cvCircle(
        roi,
        point,
        radius,
        CV_RGB(255, 255, 255),
        -1, 8, 0
    );

    /* extract subimage */
    cvAnd(img_grayscale, img_grayscale, res, roi);
    
    cvSetImageROI(res, cvRect(point.x-radius, point.y-radius,radius*2,radius*2));

    int histSize = 256;

    /// Set the ranges ( for B,G,R) )
    float range[] = { 0, 256 } ;
    float* histRange[] = { range };

    bool uniform = true; bool accumulate = false;

    CvHistogram* img_hist;

    img_hist =  cvCreateHist(1, &histSize, CV_HIST_ARRAY, histRange, 1);
    
    cvCalcHist( &res, img_hist, accumulate, NULL );

    double mean_brightness = cvMean(res);
    
    cout << "Having mean of grayscale values of: " << mean_brightness << endl;

    char mean_brightness_string[256];
    sprintf(mean_brightness_string, "Brightness: %f", mean_brightness);
    
    CvFont font;
    cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5);
    
    if(show_roi) {
     cvPutText(
        image, 
        mean_brightness_string, 
        point,
        &font, 
        cvScalar(127,255,0) // green
      );
      cvShowImage("ROI",res);
    }

    //free memory. otherwise program will crash after some time with memory hole
    cvReleaseImage(&img_grayscale);
    cvReleaseImage(&res);
    cvReleaseImage(&roi);
    cvReleaseImage(&copy_img);

    return mean_brightness;
    
}

double createROI(bool show_roi, IplImage* image, Camera cam, Pose current_pose,  float p1_x, float p1_y, float p1_z, float p2_x, float p2_y, float p2_z) {

    // create a reactangle by using a point in the center of the marker and a point exactly one marker length to the left and one to the top
    CvPoint3D32f corner_top_left_x = cvPoint3D32f(p1_x, p1_y, p1_z);
    CvPoint3D32f corner_bottom_right = cvPoint3D32f(p2_x, p2_y, p2_z);

    CvPoint2D32f corner_top_left_x_2d;
    CvPoint2D32f corner_bottom_right_2d;

    cam.ProjectPoint(corner_top_left_x, &current_pose, corner_top_left_x_2d);
    cam.ProjectPoint(corner_bottom_right, &current_pose, corner_bottom_right_2d);

    CvPoint corner_top_left_x_2d_projected = cvPointFrom32f(corner_top_left_x_2d);
    CvPoint corner_bottom_right_2d_projected = cvPointFrom32f(corner_bottom_right_2d);
   
    
    return showHistogram(
      show_roi, 
      image, 
      corner_top_left_x_2d_projected, 
      abs(corner_top_left_x_2d_projected.x-corner_bottom_right_2d_projected.x), //width
      abs(corner_top_left_x_2d_projected.y-corner_bottom_right_2d_projected.y) //height
    );

}