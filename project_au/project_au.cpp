#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  #include <winsock2.h>
  #pragma comment( lib, "ws2_32.lib" )
#else
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/un.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
#endif

#include "CvTestbed.h"
#include "MarkerDetector.h"
#include "GlutViewer.h"
#include "Shared.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cctype>
#include <cstdlib>
#include <stdio.h>
#include <errno.h>

using namespace alvar;
using namespace std;


bool initial_calibrate = true; // will load calibration XML file

bool activate_glutviewer = true; // will open two additional windows showing detected markers in cartesian space

bool show_single_pose = true;

bool send_pose = false;

bool show_average_pose = false;

bool create_roi_rene = true;

bool create_roi_puya = true;

const double marker_size= 46.0;

const double pencil_length = 50.0; // should be 146.0 later on

bool marker_detected = false;

Camera cam;
Drawable d[32];
std::stringstream calibrationFilename;

/* Stuff for sock connection*/
int sock2=-1;
unsigned int socket_port = 11113;

#define X 0
#define Y 1
#define Z 2

typedef struct POS{
  unsigned int type;//1=single Pos//2=Spline Active//3 =Spline Inactive
  int translation[3];
  int quaternion[4];
}POS;
/* Stuff end*/

void createsocket() {

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

  //Socket erstellen
  static bool socketsStarted = false;

  if (! socketsStarted)
  {
      socketsStarted = true;

      WSADATA wsaData;
      const WORD wVersionRequested = MAKEWORD (2, 2); // current possible highest ist 2,2
      WSAStartup (wVersionRequested, &wsaData); // initalize socket usage for program
  }
#endif


  // warum hier statt 0 nicht einfach IPPROTO_TCP
  int sockfd = socket (AF_INET, SOCK_STREAM, 0);          //Rückgabewert sockfd ist die Nummer des Sockets
  if (sockfd == -1) {
    perror ("socket()");
  } else {
    cout << "Socket erstellt\n";
  } 

  //Port und Verbindungsparameter festlegen
  sockaddr_in my_addr;
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(socket_port);                    // hier ist der benutzte Port definiert
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  //Socket mit Port assoziieren (Bind)
  if (bind(sockfd, (sockaddr *)&my_addr, sizeof(sockaddr)) == -1)  {
    perror ("bind()");
  } else {
    cout << "Bind to port " << socket_port << " successful. Waiting for client ..." << endl;
  }
        
  //Auf eingehende Verbindung warten
  if (listen (sockfd, 5) == -1) { //maximal 5 Verbindungsanfragen in Warteschlange, falls gerade keine Verbindung angenommen werden kann
    perror ("listen()");
  } else {  
    cout << "Warte auf Client...";
  }       
  #ifndef socklen_t
    typedef int socklen_t;
  #endif
  //Verbindung annehmen (accept)
  socklen_t sin_size = sizeof (sockaddr_in);
  sockaddr_in remote_host;
  
  sock2 = accept (sockfd, (sockaddr *) &remote_host, &sin_size); //sock2: Socket des Clients
  if (sock2 == -1) {
    perror ("accept()");
  } else {
    cout << "Client verbunden\n";
  }  
  
  // Ende Server einrichten und auf Client warten   */
}

void sendPos2Mobile(int sockfd, POS aktpos) {        
      
  int *stream_buffer = new int[sizeof(POS)];
  stream_buffer[0]=htonl(aktpos.type);
  for(int i = 0;i<3;i++)
  stream_buffer[i+1] = htonl(aktpos.translation[i]);

  for(int i = 0;i<4;i++) {
    
    stream_buffer[i+4] = htonl(aktpos.quaternion[i]);
    cout << "Streambuffer quaternion is" << stream_buffer[i+4] << endl;
  }
  if (send (sock2, (char*) stream_buffer, sizeof(POS), 0) == -1) {
    perror ("send()");
  }
  else { 
    std::cout << "  Daten gesendet:" << stream_buffer << std::endl; 
  }
  delete [] stream_buffer;
  
}



void calibrate(IplImage *image) {
    static IplImage *rgba;
    cout<<"Loading calibration: "<<calibrationFilename.str();
    if (cam.SetCalib(calibrationFilename.str().c_str(), image->width, image->height)) {
        cout<<" [Ok]"<<endl;
    } else {
        cam.SetRes(image->width, image->height);
        cout<<" [Fail]"<<endl;
    }
    double p[16];
    cam.GetOpenglProjectionMatrix(p,image->width,image->height);
    if(activate_glutviewer) GlutViewer::SetGlProjectionMatrix(p);
    for (int i=0; i<32; i++) {
        d[i].SetScale((int)marker_size);
    }

    rgba = CvTestbed::Instance().CreateImageWithProto("RGBA", image, 0, 4);

    initial_calibrate = false;
}

void showLine(IplImage *image, Pose p) {
    CvPoint3D32f point_from_3d = cvPoint3D32f(0.0,0.0,-marker_size/2); // move one half marker size to the center of the cube
    CvPoint3D32f point_to_3d = cvPoint3D32f(0.0,146.0,-marker_size/2); // move from the center of the cube to the pencil tip

    CvPoint2D32f point_from_2d;
    CvPoint2D32f point_to_2d;

    cam.ProjectPoint(point_from_3d, &p, point_from_2d);
    cam.ProjectPoint(point_to_3d, &p, point_to_2d);

    CvPoint from = cvPointFrom32f(point_from_2d);
    CvPoint to = cvPointFrom32f(point_to_2d);

    cvLine(image, from, to, CV_RGB(255,255,0)); // draw a line from the cube center to the pencil tip
}

void showPose(int number, int id, Pose p) {
    
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
    
    tip_pose.SetTranslation( 
      0, 
      pencil_length,
      -marker_size/2
    );

    CvMat *current_matrix = cvCreateMat(4, 4, CV_64FC1);
    p.GetMatrix(current_matrix);

    CvMat *tip_matrix = cvCreateMat(4, 4, CV_64FC1);
    tip_pose.GetMatrix(tip_matrix);

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

    cvmSet(euler_matrix, 2, 0, cvmGet(euler_matrix,2,0) - 90.0);

    //cout << "Shifted euler:" << cvmGet(euler_matrix,0,0) << " ; " << cvmGet(euler_matrix,1,0) << " ; " << cvmGet(euler_matrix,2,0) << endl; 


    tip_pose.SetEuler(euler_matrix);

    return tip_pose;
}


void showHistogram(char* name, IplImage* image, bool roi = false, int x = 0, int y = 0, int x_l = 0, int y_l = 0) {

    IplImage* copy_img = cvCloneImage(image);
    
    // create an image with only onee color channel
    IplImage* img_grayscale = cvCreateImage(cvSize(copy_img->width,copy_img->height), copy_img->depth, 1);

    cvCvtColor(copy_img, img_grayscale, CV_RGB2GRAY);

    if(roi) {
      cout << "Setting roi to " << x << ":" << y << " with length " << x_l << ":" << y_l << endl;
      cvSetImageROI(img_grayscale, cvRect(x, y, x_l, y_l));
    }
    int histSize = 256;

    /// Set the ranges ( for B,G,R) )
    float range[] = { 0, 256 } ;
    float* histRange[] = { range };

    bool uniform = true; bool accumulate = false;

    CvHistogram* img_hist;

    img_hist =  cvCreateHist(1, &histSize, CV_HIST_ARRAY, histRange, 1);
    
    cvCalcHist( &img_grayscale, img_hist, accumulate, NULL );
    
    cout << "Having mean of grayscale values for " << name << ": " << cvMean(img_grayscale) << endl;

}


void videocallback(IplImage *image)
{
    
    bool flip_image = (image->origin?true:false);
    if (flip_image) {
        cvFlip(image);
        image->origin = !image->origin;
    }
    
    if(initial_calibrate) calibrate(image);
  
    static MarkerDetector<MarkerData> marker_detector;

    /** Set the default marker size to be used for all markers unless 
    * \param _edge_length Length of the marker's edge in whatever units you are using (e.g. cm)
    * \param _res The marker content resolution in pixels. By default we use 5x5 markers. If you use 0 with \e MarkerData, the marker resolution is detected automatically.
    * \param _margin The marker margin resolution in pixels (The actual captured marker image has pixel resolution of _margin+_res+_margin)
    *
    * \note The default marker content resolution (_res) of 5 can only detect marker ids from 0 to 255. For larger marker ids, you need to increase the marker content resolution accordingly.
    */
    marker_detector.SetMarkerSize(42.0 /*mm*/, 5, 1.0);

    // Here we try to use RGBA just to make sure that also it works...
    //cvCvtColor(image, rgba, CV_RGB2RGBA);
    /*
    int Detect(IplImage *image,
           Camera *cam,
           bool track=false,
           bool visualize=false,
           double max_new_marker_error=0.08,
           double max_track_error=0.2,
           LabelingMethod labeling_method=CVSEQ,
           bool update_pose=true); */
    marker_detector.Detect(image, &cam, true, false , 0.08, 0.2, CVSEQ, true );

    if(activate_glutviewer) GlutViewer::DrawableClear();

    Pose avg_pose;
    avg_pose.Reset(); // fresh start

    marker_detected = false;

    
    /*
      Create a histogram on the original image
    */
    showHistogram("Original image", image);


    // Start the marker detection loop
    for (size_t i=0; i<marker_detector.markers->size(); i++) {
        if (i >= 32) break; // limit detection to 32 markers

        

        int id = (*(marker_detector.markers))[i].GetId();
        

        Pose current_pose = (*(marker_detector.markers))[i].pose; // get pose
        
        if(show_single_pose) showPose(i, id, current_pose);

        CvMat *current_translation = cvCreateMat(3, 1, CV_64FC1);

        current_pose.GetTranslation(current_translation);

        double current_x = cvmGet(current_translation,0,0);
        double current_y = cvmGet(current_translation,1,0);
        double current_z = cvmGet(current_translation,2,0);

        CvMat *quaternion = cvCreateMat(4, 1, CV_64FC1);
        current_pose.GetQuaternion(quaternion);
            
        cout << id << "," << current_x << "," << current_y << "," << current_z<< endl;
        
        cout << "Current Translation of marker " << id << " in relation to cam is (X,Y,Z): (" << current_x << ", " << current_y << ", " << current_z << ")" << endl;
        cout << "Current Quaternion of marker " << id <<  " in relation to cam is (R, i1, i2, i3) : (" << cvmGet(quaternion,0,0) << ", " << cvmGet(quaternion,1,0) << ", " << cvmGet(quaternion,2,0) << ", " << cvmGet(quaternion,3,0) << ")" << endl;
        

        if(create_roi_rene) {

          // create a reactangle by using a point in the center of the marker and a point exactly one marker length to the left and one to the top
          CvPoint3D32f corner_top_left_x = cvPoint3D32f(marker_size/1.5,-marker_size/1.5,0);
          CvPoint3D32f corner_bottom_right = cvPoint3D32f(marker_size/4,-marker_size/4,0.0);

          CvPoint2D32f corner_top_left_x_2d;
          CvPoint2D32f corner_bottom_right_2d;

          cam.ProjectPoint(corner_top_left_x, &current_pose, corner_top_left_x_2d);
          cam.ProjectPoint(corner_bottom_right, &current_pose, corner_bottom_right_2d);

          CvPoint corner_top_left_x_2d_projected = cvPointFrom32f(corner_top_left_x_2d);
          CvPoint corner_bottom_right_2d_projected = cvPointFrom32f(corner_bottom_right_2d);
          
          cvRectangle(image,corner_top_left_x_2d_projected, corner_bottom_right_2d_projected, CV_RGB(255,255,0));

          showHistogram(
            "ROI Rene", 
            image, 
            true, 
            corner_top_left_x_2d_projected.x, 
            corner_top_left_x_2d_projected.y, 
            abs(corner_top_left_x_2d_projected.x-corner_bottom_right_2d_projected.x), //width
            abs(corner_top_left_x_2d_projected.y-corner_bottom_right_2d_projected.y) //height
          );

        }


        if(create_roi_puya) {

          // create a reactangle by using a point in the center of the marker and a point exactly one marker length to the left and one to the top
          CvPoint3D32f corner_top_left_x = cvPoint3D32f(marker_size/2 +2,marker_size/2 -4,0);
          CvPoint3D32f corner_bottom_right = cvPoint3D32f(-marker_size/2 +2,marker_size/2 + 14,0.0);

          CvPoint2D32f corner_top_left_x_2d;
          CvPoint2D32f corner_bottom_right_2d;

          cam.ProjectPoint(corner_top_left_x, &current_pose, corner_top_left_x_2d);
          cam.ProjectPoint(corner_bottom_right, &current_pose, corner_bottom_right_2d);

          CvPoint corner_top_left_x_2d_projected = cvPointFrom32f(corner_top_left_x_2d);
          CvPoint corner_bottom_right_2d_projected = cvPointFrom32f(corner_bottom_right_2d);
          
          cvRectangle(image,corner_top_left_x_2d_projected, corner_bottom_right_2d_projected, CV_RGB(255,255,0));

         
          
          showHistogram(
            "ROI Puya", 
            image, 
            true, 
            corner_top_left_x_2d_projected.x, 
            corner_top_left_x_2d_projected.y, 
            abs(corner_top_left_x_2d_projected.x-corner_bottom_right_2d_projected.x), //width
            abs(corner_top_left_x_2d_projected.y-corner_bottom_right_2d_projected.y) //height
          );

        }

        if(show_average_pose) { // average poses
          if(marker_detected) { // we found at least one marker before, so we must average
            Pose temp_pose = calculateTipPose(current_pose);
            
            CvMat *temp_translation = cvCreateMat(3, 1, CV_64FC1);
            CvMat *avg_translation = cvCreateMat(3, 1, CV_64FC1);

            avg_pose.GetTranslation(avg_translation);
            temp_pose.GetTranslation(temp_translation);


            avg_pose.SetTranslation( 
              (cvmGet(temp_translation,0,0) + cvmGet(avg_translation,0,0)) / 2,
              (cvmGet(temp_translation,1,0) + cvmGet(avg_translation,1,0)) / 2,
              (cvmGet(temp_translation,2,0) + cvmGet(avg_translation,2,0)) / 2 
            );

            
            
          } else { // first marker found. Just apply current pose and move to cube center
            avg_pose = calculateTipPose(current_pose);
          }
          
        }
        
        
        
        
        marker_detected = true; // first of many (or last) run finished. We set the flag.

    } // end loop markers

    CvMat *avg_translation = cvCreateMat(3, 1, CV_64FC1);

    avg_pose.GetTranslation(avg_translation);

    double avg_x = cvmGet(avg_translation,0,0);
    double avg_y = cvmGet(avg_translation,1,0);
    double avg_z = cvmGet(avg_translation,2,0);

    CvMat *avg_quaternion = cvCreateMat(4, 1, CV_64FC1);
    avg_pose.GetQuaternion(avg_quaternion);

    double avg_R = cvmGet(avg_quaternion,0,0);
    double avg_i1 = cvmGet(avg_quaternion,1,0);
    double avg_i2 = cvmGet(avg_quaternion,2,0);
    double avg_i3 = cvmGet(avg_quaternion,3,0);

    cout << "Current Translation of avg marker is (X,Y,Z): (" << avg_x << ", " << avg_y << ", " << avg_z << ")" << endl;
    cout << "Current Quaternion of avg marker in relation to cam is (R, i1, i2, i3) : (" << (avg_R ) << ", " << avg_i1 << ", " << avg_i2 << ", " << avg_i3 << ")" << endl;
    

    if(show_average_pose) {
      
      showPose(10, 0, avg_pose);

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

    // send the pose via network
    if(send_pose) {
      POS aktpos;
      aktpos.type=1;
      aktpos.translation[X]= (int) (avg_x*1000);
      aktpos.translation[Y]= (int) (avg_y*1000);
      aktpos.translation[Z]= (int) (avg_z*1000);
      aktpos.quaternion[0] = (int) (avg_R*1000);
      aktpos.quaternion[1] = (int) (avg_i1*1000);
      aktpos.quaternion[2] = (int) (avg_i2*1000);
      aktpos.quaternion[3] = (int) (avg_i3*1000);
      cout << "Quaterion 3 in POS is" << aktpos.quaternion[3] << endl;
      sendPos2Mobile(sock2, aktpos);
    }



    if (flip_image) {
        cvFlip(image);
        image->origin = !image->origin;
    }
}


int main(int argc, char *argv[])
{
    try {
        // Output usage message
        std::string filename(argv[0]);
        filename = filename.substr(filename.find_last_of('\\') + 1);
        std::cout << "Project AU 5" << std::endl;
        std::cout << "====================" << std::endl;
        std::cout << std::endl;
        std::cout << "Description:" << std::endl;
        std::cout << "  This is an example of how to detect 'MarkerData' markers using" << std::endl;
        std::cout << "  'MarkerDetector' and visualize them using 'GlutViewer'. In the" << std::endl;
        std::cout << "  SampleMarkerDetector window, various debug information is shown" << std::endl;
        std::cout << "  about the detected markers. The coordinate axes and a virtual cube" << std::endl;
        std::cout << "  are superimposed onto the markers to visualize the detected pose." << std::endl;
        std::cout << "  For each marker, a small image of the marker content is displayed" << std::endl;
        std::cout << "  at the origin and the marker number is displayed at one of the" << std::endl;
        std::cout << "  corners. At the opposing corner, the error estimation percentages" << std::endl;
        std::cout << "  'MARGIN_ERROR' and 'DECODE_ERROR' (red) or 'TRACK_ERROR' (dark red)" << std::endl;
        std::cout << "  are displayed." << std::endl;
        std::cout << std::endl;
        std::cout << "  In the AR window, squares are drawn over the marker positions using" << std::endl;
        std::cout << "  OpenGL. In the VR window, the squares are drawn with respect to the" << std::endl;
        std::cout << "  camera coordinate frame. The viewpoint can be modified by dragging" << std::endl;
        std::cout << "  with the left and right mouse buttons." << std::endl;
        std::cout << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << "  " << filename << " [device|filename]" << std::endl;
        std::cout << std::endl;
        std::cout << "    device    integer selecting device from enumeration list (default 0)" << std::endl;
        std::cout << "              highgui capture devices are prefered" << std::endl;
        std::cout << "    filename  string specifying a media file as input" << std::endl;
        std::cout << std::endl;
        std::cout << "Keyboard Shortcuts:" << std::endl;
        std::cout << "  q: quit" << std::endl;
        std::cout << std::endl;

        if(send_pose) createsocket();

        // Initialise GlutViewer and CvTestbed
        if(activate_glutviewer) GlutViewer::Start(argc, argv, 640, 480);
        
        CvTestbed::Instance().SetVideoCallback(videocallback);

        // Create capture object from camera (argv[1] is a number) or from file (argv[1] is a string)
        Capture *cap;
        std::string uniqueName;
        if ((argc > 1) && (!isdigit(argv[1][0]))) {
            // Manually create capture device and initialize capture object
            CaptureDevice device("file", argv[1]);
            cap = CaptureFactory::instance()->createCapture(device);
            uniqueName = "file";
        }
        else {    
            // Enumerate possible capture plugins
            CaptureFactory::CapturePluginVector plugins = CaptureFactory::instance()->enumeratePlugins();
            if (plugins.size() < 1) {
                std::cout << "Could not find any capture plugins." << std::endl;
                return 0;
            }

            // Display capture plugins
            std::cout << "Available Plugins: ";
            outputEnumeratedPlugins(plugins);
            std::cout << std::endl;

            // Enumerate possible capture devices
            CaptureFactory::CaptureDeviceVector devices = CaptureFactory::instance()->enumerateDevices();
            if (devices.size() < 1) {
                std::cout << "Could not find any capture devices." << std::endl;
                return 0;
            }

            // Check command line argument for which device to use
            int selectedDevice = defaultDevice(devices);
            if (argc > 1) {
                selectedDevice = atoi(argv[1]);
            }
            if (selectedDevice >= (int)devices.size()) {
                selectedDevice = defaultDevice(devices);
            }
            
            // Display capture devices
            std::cout << "Enumerated Capture Devices:" << std::endl;
            outputEnumeratedDevices(devices, selectedDevice);
            std::cout << std::endl;
            
            // Create capture object from camera
            cap = CaptureFactory::instance()->createCapture(devices[selectedDevice]);
            uniqueName = devices[selectedDevice].uniqueName();
        }

        // Handle capture lifecycle and start video capture
        // Note that loadSettings/saveSettings are not supported by all plugins
        if (cap) {
            std::stringstream settingsFilename;
            settingsFilename << "camera_settings_" << uniqueName << ".xml";
            calibrationFilename << "camera_calibration_" << uniqueName << ".xml";
            
            cap->start();
            cap->setResolution(640, 480);
            
            if (cap->loadSettings(settingsFilename.str())) {
                std::cout << "Loading settings: " << settingsFilename.str() << std::endl;
            }

            std::stringstream title;
            title << "SampleMarkerDetector (" << cap->captureDevice().captureType() << ")";

            CvTestbed::Instance().StartVideo(cap, title.str().c_str());

            if (cap->saveSettings(settingsFilename.str())) {
                std::cout << "Saving settings: " << settingsFilename.str() << std::endl;
            }

            cap->stop();
            delete cap;
        }
        else if (CvTestbed::Instance().StartVideo(0, argv[0])) { // call will block execution
        }
        else {
            std::cout << "Could not initialize the selected capture backend." << std::endl;
        }

        return 0;
    }
    catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << endl;
    }
    catch (...) {
        std::cout << "Exception: unknown" << std::endl;
    }
}
