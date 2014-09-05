#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

  #include <winsock2.h>
  #pragma comment( lib, "ws2_32.lib" )
#endif
#define APP_SOCKET_PORT 11113
#define SERVER_IP "127.0.0.1"

#define PENCIL_LENGTH 50.0 // should be 146.0 later on

#define MARKER_SIZE 46.0 // mm
#define MARKER
#define MARKER_RESOLUTION 5
#define MARKER_BLACK_MARGIN_RESOLUTION 1.0
#define MARKER_BLACK_MARGIN 6.0

#define MARKER_WHITE_MARGIN_RESOLUTION 1.0
#define MARKER_WHITE_MARGIN 6.0

#define ROBOT_MARKER 0

#include "CvTestbed.h"
#include "MarkerDetector.h"
#include "GlutViewer.h"
#include "Shared.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

// include stuff for sending the POSE via mobile and also for managing sockets
#include "network.hpp"
#include "network.cpp"
<
#include "pose.cpp"

#include "tools.cpp"

#include <cctype>
#include <cstdlib>
#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>




using namespace alvar;
using namespace std;



bool initial_calibrate = true; // will load calibration XML file

bool activate_glutviewer = true; // will open two additional windows showing detected markers in cartesian space

bool show_single_pose = true;

bool send_pose = true;

bool show_average_pose = true;

bool create_roi_rene = false;

bool create_roi_puya = false;

bool calculate_robot_pose = true;

bool avg_pose_relative_to_robot_calculated = false;

bool marker_detected = false;

int counter = 1 ;

Pose avg_pose_relative_to_robot;

Camera cam;

Drawable d[32];

std::stringstream calibrationFilename;

SOCKET server_socket = -1;

 


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
        d[i].SetScale((int) MARKER_SIZE);
    }

    rgba = CvTestbed::Instance().CreateImageWithProto("RGBA", image, 0, 4);

    initial_calibrate = false;
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
    marker_detector.SetMarkerSize(MARKER_SIZE, MARKER_RESOLUTION, MARKER_BLACK_MARGIN_RESOLUTION);

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


    // Start the marker detection loop
    for (size_t i=0; i<marker_detector.markers->size(); i++) {

        if (i >= 32) break; // limit detection to 32 markers
        
        int id = (*(marker_detector.markers))[i].GetId();
        
        if(id == ROBOT_MARKER) { // we detected the 0 marker. Now we try to ready from the stream

          Pose zero_marker_pose = (*(marker_detector.markers))[i].pose; // get pose

          showPose(i, id, zero_marker_pose, d);

          //cout << "Current Translation of ZERO marker " << id << " in relation to cam is (X,Y,Z): (" << sp.x << ", " << sp.y << ", " << sp.z << ")" << endl;
          //cout << "Current Quaternion of ZERO marker " << id <<  " in relation to cam is (R, i1, i2, i3) : (" << sp.R << ", " << sp.i1 << ", " << sp.i2 << ", " << sp.i3 << ")" << endl;

          cout << "Checking stream for tip pose" << endl;
          int stream_buffer_size = sizeof(int)*8;
          char *stream_buffer = new char[stream_buffer_size];
          int n = recv(server_socket, stream_buffer,stream_buffer_size, 0);


          if (n < 0) cout << "ERROR reading from socket" << endl;
          else cout << "Read " << n << "bytes from socket" << endl;
          // cast the buffer to int
          int* stream_data = (int *)stream_buffer;


          //rebuild pose
          SIMPLE_POSE aktpos;
          aktpos.type = (int) ntohl(stream_data[0]);
    
          aktpos.x = ((int) ntohl(stream_data[1])) / 1000.0;
          aktpos.y = ((int) ntohl(stream_data[2])) / 1000.0;
          aktpos.z = ((int) ntohl(stream_data[3])) / 1000.0;
          aktpos.R = ((int) ntohl(stream_data[4])) / 1000.0;
          aktpos.i1 = ((int) ntohl(stream_data[5])) / 1000.0;
          aktpos.i2 = ((int) ntohl(stream_data[6])) / 1000.0;
          aktpos.i3 = ((int) ntohl(stream_data[7])) / 1000.0;

          printf("Received: X %f\n", aktpos.x);
          printf("Received: Y %f\n", aktpos.y);
          printf("Received: Z %f\n", aktpos.z);
          printf("Received: X0 %f\n", aktpos.R);
          printf("Received: X1 %f\n", aktpos.i1);
          printf("Received: X2 %f\n", aktpos.i2);
          printf("Received: X3 %f\n", aktpos.i3);

          Pose tip_pose;
          tip_pose.Reset();

          tip_pose.SetTranslation( 
            aktpos.x, 
            aktpos.y,
            aktpos.z
          );

          CvMat *quaternion_matrix = cvCreateMat(4, 1, CV_64FC1);
          cvmSet(quaternion_matrix, 0, 0, aktpos.R);
          cvmSet(quaternion_matrix, 1, 0, aktpos.i1);
          cvmSet(quaternion_matrix, 2, 0, aktpos.i2);
          cvmSet(quaternion_matrix, 3, 0, aktpos.i3);
           
          tip_pose.SetQuaternion(quaternion_matrix);

          tip_pose = transformPoseRelativeToCam(zero_marker_pose, tip_pose);
          

          showPoseCoordinates(image, cam, tip_pose, aktpos);

          showPose(2, 33, tip_pose, d);
      /*
          tip_pose.Reset();

          tip_pose = calculateInverseRobotPose(zero_marker_pose, tip_pose);
          tip_pose.SetTranslation( // set the target translation (only valid for side-markers)
            aktpos.x, 
            aktpos.y,
            aktpos.z
          );

          showPoseCoordinates(image, cam, zero_marker_pose, aktpos);

          showPose(3, 66, tip_pose, d);
      */
        }


    } // end loop markers

  

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
        std::cout << "Project AU Receiver!" << std::endl;
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


        //connect to server
        struct sockaddr_in serv_addr;
        struct hostent *server;
        
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        
        cout << "Connecting to " << SERVER_IP << endl;
        server = gethostbyname(SERVER_IP);
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
        
        memset((char *) &serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
    memmove( (char *)&serv_addr.sin_addr.s_addr,
            (char *)server->h_addr, 
      server->h_length);
        serv_addr.sin_port = htons(APP_SOCKET_PORT);
      
        if (connect(server_socket,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
          #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
            cout << "Error with WSA " << WSAGetLastError() << endl;
          #endif
          perror("Error connecting");
          return 0;
        } else {
          cout << "Connect Succesful" << endl;
        }

    
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
