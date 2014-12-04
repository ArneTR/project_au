#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  #include <winsock2.h>
  #pragma comment( lib, "ws2_32.lib" )
#endif

#include "CvTestbed.h"
#include "MarkerDetector.h"
#include "GlutViewer.h"
#include "Shared.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

// include stuff for sending the POSE via mobile and also for managing sockets
#include "network.hpp"
#include "network.cpp"

#include "roi.cpp"

#include "pose.cpp"

#include "tools.cpp"

#include <cctype>
#include <cstdlib>
#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <vector>



using namespace alvar;

/**
  Changeable attributes
*/

bool initial_calibrate = true; // will load calibration XML file

bool activate_glutviewer = true; // will open two additional windows showing detected markers in cartesian space

bool show_single_pose = true;

bool send_pose_to_app = false;

bool send_pose_to_watcher = false;

bool send_pose_to_robot = false;

bool show_average_pose = true;

bool show_roi = true;

/**
  NON-Changeable attributes. These are in-program set flags.

  DO NOT TAMPER!
*/

int current_brightness = 0;

int last_brightness = 0;

bool start_recording_poses = false;

/**
  Globally used containers and variables
*/

std::vector<SIMPLE_POSE> average_poses;

std::vector<SIMPLE_POSE> recored_poses;

Camera cam;

Drawable d[32];


SOCKET app_socket_handler = -1;
SOCKET app_socket = -1;

SOCKET robot_socket_handler = -1;
SOCKET robot_socket = -1;

SOCKET watcher_socket_handler = -1;
SOCKET watcher_socket = -1;

string calibrationFilename = "camera_calibration_microsoft_hd5000_highgui.xml";


void calibrate(IplImage *image) {
    static IplImage *rgba;
    
    std::cout << "Loading calibration: " << calibrationFilename;
    if (cam.SetCalib(calibrationFilename.c_str(), image->width, image->height)) {
        std::cout<<" [Ok]"<<std::endl;
    } else {
        cam.SetRes(image->width, image->height);
        std::cout<<" [Fail]"<<std::endl;
        exit(-1);
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

/** DEGBU CODE FOR ROTATION MATRICES
    Pose tip_pose;
    tip_pose.Reset();

    int id = 187;
    
    if(id == 255) { // top_marker
      tip_pose.SetTranslation( // set the target translation (only valid for side-markers)
        0, 
        0,
        - (MARKER_WHITE_MARGIN) -(MARKER_SIZE/2) - (PENCIL_LENGTH) 
      );
    } else {
      tip_pose.SetTranslation( // set the target translation (only valid for side-markers)
        0, 
        PENCIL_LENGTH,
        -(MARKER_SIZE/2) - (MARKER_WHITE_MARGIN)
      );
    }

    // now we rotate the marker 90 degrees
    CvMat *euler_matrix = cvCreateMat(3, 1, CV_64FC1);
    tip_pose.GetEuler(euler_matrix);

    //cout << "Current euler:" << cvmGet(euler_matrix,0,0) << " ; " << cvmGet(euler_matrix,1,0) << " ; " << cvmGet(euler_matrix,2,0) << endl; 

    if(id == 255) {
      cvmSet(euler_matrix, 0, 0, cvmGet(euler_matrix,0,0) + 180.0); // flip 180 degrees (only valid for top marker)
      cvmSet(euler_matrix, 1, 0, -cvmGet(euler_matrix,1,0)); // flip 180 degrees (only valid for top marker) // green y axis
      cvmSet(euler_matrix, 2, 0, -cvmGet(euler_matrix,2,0)); // flip 180 degrees (only valid for top marker)
    } else if(id == 187) {
      cvmSet(euler_matrix, 0, 0, cvmGet(euler_matrix,0,0) - 90.0); // rotate 90 degrees (only valid for side markers)
      cvmSet(euler_matrix, 2, 0, cvmGet(euler_matrix,2,0) - 90.0); // rotate 90 degrees (only valid for side markers)
    } else if(id == 176) {
      cvmSet(euler_matrix, 0, 0, cvmGet(euler_matrix,0,0) - 180.0); // rotate 90 degrees (only valid for side markers)
      cvmSet(euler_matrix, 2, 0, cvmGet(euler_matrix,2,0) - 90.0); // rotate 90 degrees (only valid for side markers)
    } else if(id == 68) {
      cvmSet(euler_matrix, 0, 0, cvmGet(euler_matrix,0,0) - 0.0); // rotate 90 degrees (only valid for side markers)
      cvmSet(euler_matrix, 2, 0, cvmGet(euler_matrix,2,0) - 90.0); // rotate 90 degrees (only valid for side markers)
    } else if(id == 79) {
      cvmSet(euler_matrix, 0, 0, cvmGet(euler_matrix,0,0) + 90.0); // rotate 90 degrees (only valid for side markers)
      cvmSet(euler_matrix, 2, 0, cvmGet(euler_matrix,2,0) - 90.0); // rotate 90 degrees (only valid for side markers)
    }

    //cout << "Shifted euler:" << cvmGet(euler_matrix,0,0) << " ; " << cvmGet(euler_matrix,1,0) << " ; " << cvmGet(euler_matrix,2,0) << endl; 


    tip_pose.SetEuler(euler_matrix);

    CvMat *tip_matrix = cvCreateMat(4, 4, CV_64FC1);
    tip_pose.GetMatrix(tip_matrix); // get current tip matrix (should be empty after reset)

    std::cout << cvmGet(tip_matrix,0,0) << " | " << cvmGet(tip_matrix,0,1) << " | " << cvmGet(tip_matrix,0,2) << " | " << cvmGet(tip_matrix,0,3) << std::endl;
    std::cout << cvmGet(tip_matrix,1,0) << " | " << cvmGet(tip_matrix,1,1) << " | " << cvmGet(tip_matrix,1,2) << " | " << cvmGet(tip_matrix,1,3) << std::endl;
    std::cout << cvmGet(tip_matrix,2,0) << " | " << cvmGet(tip_matrix,2,1) << " | " << cvmGet(tip_matrix,2,2) << " | " << cvmGet(tip_matrix,2,3) << std::endl;
    std::cout << cvmGet(tip_matrix,3,0) << " | " << cvmGet(tip_matrix,3,1) << " | " << cvmGet(tip_matrix,3,2) << " | " << cvmGet(tip_matrix,3,3) << std::endl;
    
    exit(-1);
    */

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
    marker_detector.SetMarkerSizeForId(0, ROBOT_MARKER_SIZE);

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

    Pose robot_marker_pose;
    robot_marker_pose.Reset();

    bool marker_detected = false;
    bool robot_marker_detected = false;

    if(start_recording_poses) cvCircle(image, cvPoint(630, 10), 3, cvScalar(0,0,255), 10);

    /*
      Create a histogram on the original image
    */
    if(show_roi) showHistogram(show_roi, image, cvPoint(0,15), 1, 1);
    

    // Start the marker detection loop
    for (size_t i=0; i<marker_detector.markers->size(); i++) {

      if (i >= 32) break; // limit detection to 32 markers

      int id = (*(marker_detector.markers))[i].GetId();

      // skip all markers that are not relevant. In the current setup, where we only use relevant
      // markers this means usually only that we omit misdetections
      if(id != ROBOT_MARKER && !isPencilMarker(id)) continue;

      Pose current_pose = (*(marker_detector.markers))[i].pose; // get pose
      if(show_single_pose) showPose(i, id, current_pose, d);

      SIMPLE_POSE sp = getSimplePose(current_pose);
          
      std::cout << "Current Translation of marker " << id << " in relation to cam is (X,Y,Z): (" << sp.x << ", " << sp.y << ", " << sp.z << ")" << std::endl;
      std::cout << "Current Quaternion of marker " << id <<  " in relation to cam is (R, i1, i2, i3) : (" << sp.R << ", " << sp.i1 << ", " << sp.i2 << ", " << sp.i3 << ")" << std::endl;

      if(isPencilMarker(id)) {
        
        current_brightness = createROI(
          show_roi // determine if value is written to image. Calculation is done always!
          , image
          , cam
          , current_pose
          , MARKER_SIZE/2 + MARKER_WHITE_MARGIN // p1_x
          , - MARKER_SIZE/2 - MARKER_WHITE_MARGIN // p1_y
          , 0 // p1_z
          , -(MARKER_SIZE)/2 - MARKER_WHITE_MARGIN // p2_x
          , - MARKER_SIZE - MARKER_WHITE_MARGIN // p2_y
          ,0 //p2_z
        );

        std::cout << "Current brightness: " << current_brightness << " last brightness " << last_brightness << std::endl;
        if(last_brightness > 0 && current_brightness > (last_brightness + BRIGHTNESS_MARGIN)) {
         if(start_recording_poses == true) { // it was true before, so we stop
           start_recording_poses = false;
         } else { // it was false before. So we clear the vector and start recording
           start_recording_poses = true;
         }
        }

        last_brightness = current_brightness;
      

        if(marker_detected) { // we found at least one marker before, so we must average. This is multi-marker averaging!
          
          SIMPLE_POSE simple_temp_pose = getSimplePose(calculateTipPose(current_pose, id));
          
          SIMPLE_POSE simple_avg_pose = getSimplePose(avg_pose);

          std::cout << "Current Translation of pre-AVG-marker "<< id <<" in relation to cam is (X,Y,Z): (" << simple_temp_pose.x << ", " << simple_temp_pose.y << ", " << simple_temp_pose.z << ")" << std::endl;
    
          avg_pose.SetTranslation( 
            (simple_avg_pose.x + simple_temp_pose.x )/ 2.0,
            (simple_avg_pose.y + simple_temp_pose.y )/ 2.0,
            (simple_avg_pose.z + simple_temp_pose.z )/ 2.0
          );

          CvMat *avg_euler_matrix = cvCreateMat(3, 1, CV_64FC1);
          avg_pose.GetEuler(avg_euler_matrix);


          cvmSet(avg_euler_matrix, 0, 0, (simple_avg_pose.alpha + simple_temp_pose.alpha) / 2.0 );
          cvmSet(avg_euler_matrix, 1, 0, (simple_avg_pose.beta + simple_temp_pose.beta) / 2.0 );
          cvmSet(avg_euler_matrix, 2, 0, (simple_avg_pose.gamma + simple_temp_pose.gamma) / 2.0 );
          
          avg_pose.SetEuler(avg_euler_matrix);
 
            
        } else { // first marker found. Just apply current pose and move to cube center
          marker_detected = true;
          avg_pose = calculateTipPose(current_pose, id);
          
          SIMPLE_POSE simple_avg_pose = getSimplePose(avg_pose);
          std::cout << "Current Translation of pre-AVG-marker "<< id <<" in relation to cam is (X,Y,Z): (" << simple_avg_pose.x << ", " << simple_avg_pose.y << ", " << simple_avg_pose.z << ")" << std::endl;
    
        }

      } else { // id == ROBOT_MARKER
        robot_marker_detected = true;
        robot_marker_pose = current_pose;
        std::cout << "Detected ROBOT_MARKER (id:" << ROBOT_MARKER << ")!" << std::endl;
      }
    } // end loop markers

 
    SIMPLE_POSE sp2 = getSimplePose(avg_pose);

    std::cout << "Current Translation of AVG-marker in relation to cam is (X,Y,Z): (" << sp2.x << ", " << sp2.y << ", " << sp2.z << ")" << std::endl;
    std::cout << "Current Quaternion of AVG-marker in relation to cam is (R, i1, i2, i3) : (" << sp2.R << ", " << sp2.i1 << ", " << sp2.i2 << ", " << sp2.i3 << ")" << std::endl;
    
    if(TIME_AVERAGE_POSES > 1 && marker_detected) { // we average over time!
      double queue_size = average_poses.size();

      std::cout << "Current TIME_AVERAGE_POSES queue has" << queue_size << " elements" << std::endl;

      //calculate time_average_pose
      for(int i = (int) queue_size; i > 0; i--) {
        sp2.x = sp2.x + average_poses[i-1].x;
        sp2.y = sp2.y + average_poses[i-1].y;
        sp2.z = sp2.z + average_poses[i-1].z;
        sp2.alpha = sp2.alpha + average_poses[i-1].alpha;
        sp2.beta = sp2.beta + average_poses[i-1].beta;
        sp2.gamma = sp2.gamma + average_poses[i-1].gamma;
      }

      // we need to divide by queue size + current element
      sp2.x = sp2.x / (queue_size+1.0);
      sp2.y = sp2.y / (queue_size+1.0);
      sp2.z = sp2.z / (queue_size+1.0);
      sp2.alpha = sp2.alpha / (queue_size+1.0);
      sp2.beta = sp2.beta / (queue_size+1.0);
      sp2.gamma = sp2.gamma / (queue_size+1.0);

      // set to real avg pose
      avg_pose.SetTranslation( 
        sp2.x,
        sp2.y,
        sp2.z
      );

      CvMat *euler_matrix = cvCreateMat(3, 1, CV_64FC1);
      
      cvmSet(euler_matrix, 0, 0, sp2.alpha);
      cvmSet(euler_matrix, 1, 0, sp2.beta);
      cvmSet(euler_matrix, 2, 0, sp2.gamma);
      
      avg_pose.SetEuler(euler_matrix);

      std::cout << "Current Translation of TIME-AVG-marker in relation to cam is (X,Y,Z): (" << sp2.x << ", " << sp2.y << ", " << sp2.z << ")" << std::endl;
      
      // we add the current element to the queue and remove the last
      average_poses.insert( average_poses.begin(), sp2 ); // insert newest element at top
      
      if(queue_size >= TIME_AVERAGE_POSES) { // remove the last element if queue is exceeded
        average_poses.pop_back();  
      }
    }

     SIMPLE_POSE avg_simple_pose;
    

    if(show_average_pose && marker_detected) {

      showPose(10, 0, avg_pose, d);

      markTip(image, cam, avg_pose);

      avg_simple_pose = getSimplePose(avg_pose);

      //showPoseCoordinates(image, cam, avg_pose, avg_simple_pose.x, avg_simple_pose.y, avg_simple_pose.z); // show av2r coords but ON average pose!!!


      

    }

    if(marker_detected && robot_marker_detected) {

      // first we need to calculate the transformation Matrix to get from the zero_marker to the pencil_tip
      // logic is: Cam1->ZeroMarker * ZeroMarker->PencilTip = Cam1->PencilTip
      // => (Cam1->ZeroMarker)^-1 * Cam1->PencilTip = ZeroMarker->PencilTip
      Pose avg_pose_relative_to_robot_marker;
      avg_pose_relative_to_robot_marker.Reset();

      avg_pose_relative_to_robot_marker = calculatePoseRelativeToRobotMarker(robot_marker_pose, avg_pose);   
          
      SIMPLE_POSE aktpos = getSimplePose(avg_pose_relative_to_robot_marker);
          
      std::cout << "Current Translation of robot pose is (X,Y,Z): (" << aktpos.x << ", " << aktpos.y << ", " << aktpos.z << ")" << std::endl;
      std::cout << "Current Quaternion of robot marker in relation to cam is (R, i1, i2, i3) : (" << (aktpos.R ) << ", " << aktpos.i1 << ", " << aktpos.i2 << ", " << aktpos.i3 << ")" << std::endl;
      
      showPoseCoordinates(image, cam, avg_pose, aktpos.x, aktpos.y, aktpos.z); // show av2r coords but ON average pose!!!

      aktpos.type = 1;

      if(start_recording_poses == true) {
        recored_poses.insert(recored_poses.begin(), aktpos);
        
        if(send_pose_to_app) {
          std::cout << "Sending pose to app" << std::endl; 
        
          if(sendPos(app_socket, aktpos) == 32) { // 32 == broken_pipe
            std::cout << "Connection lost. Reconnecting client...";
            app_socket = connectSocket(app_socket_handler);
          }
          
        }
      }

      if(send_pose_to_watcher) {
        std::cout << "Sending pose to watcher" << std::endl; 
      
        if(sendPos(watcher_socket, aktpos) == 32) { // 32 == broken_pipe
          std::cout << "Connection lost. Reconnecting client...";
          app_socket = connectSocket(watcher_socket_handler);
        }
        
      }
    }


    // loop is done and everything is sent. We check the socket for a response from marian
    // Note: We may NOT be currently recording
    if(start_recording_poses == false && send_pose_to_robot == true) {

      std::cout << "Checking socket for APP-response." << std::endl;

      int response = checkAppForOkNok(app_socket); // can be 0 || 1 || -1
      int recorded_poses_size = recored_poses.size();
      if(response == 0) { // discard line
        std::cout << recorded_poses_size << " Poses discarded. Waiting 5 sec!";
        recored_poses.clear();
        cvWaitKey(5000);
      } else if(response == 1) { // send line to robot
        std::cout << "Poses are ok. Sending " << recorded_poses_size << " poses to robot.";

        for(int i = 0; i < recorded_poses_size; i++) {
          if(i == (recorded_poses_size-1)) recored_poses[i].type = 0;
          if(sendPos(robot_socket, recored_poses[i]) == 32) { // 32 == broken_pipe
            std::cout << "Connection lost. Reconnecting client...";
            robot_socket = connectSocket(robot_socket_handler);
          }
        }
        std::cout << "Sending done. Clearing now!" << std::endl;
        recored_poses.clear();
        cvWaitKey(5000);
    
      }
    } else {
      std::cout << "Omitting socket check cause start_recording_poses is: " << start_recording_poses << std::endl;
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
        std::cout << "Project AU 02.09.2014" << std::endl;
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

        if(send_pose_to_app) {
          std::cout << "Trying to connect app ..." << std::endl;
          app_socket_handler = createsocket(APP_SOCKET_PORT);
          if(app_socket_handler == -1) exit(-1);
          app_socket = connectSocket(app_socket_handler);
        }
        if(send_pose_to_robot) {
          std::cout << "Trying to connect robot ..." << std::endl;
          robot_socket_handler = createsocket(ROBOT_SOCKET_PORT);
          if(robot_socket_handler == -1) exit(-1);
          robot_socket = connectSocket(robot_socket_handler);
        } 
        if(send_pose_to_watcher) {
          std::cout << "Trying to connect watcher ..." << std::endl;
          watcher_socket_handler = createsocket(WATCHER_SOCKET_PORT);
          if(watcher_socket_handler == -1) exit(-1);
          watcher_socket = connectSocket(watcher_socket_handler);
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
        std::cout << "Exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Exception: unknown" << std::endl;
    }
}
