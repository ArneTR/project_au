/*****************************************************************************************
Copyright 2011 Rafael Muñoz Salinas. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY Rafael Muñoz Salinas ''AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Rafael Muñoz Salinas OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Rafael Muñoz Salinas.
********************************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <errno.h>
#include <stdio.h>
#include <vector>

#include "aruco.h"
#include "cvdrawingutils.h"
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <unistd.h>


// include stuff for sending the POSE via mobile and also for managing sockets
#include "network.hpp"
#include "network.cpp"
#include "roi.cpp"
#include "pose.cpp" 
#include "tools.cpp"

using namespace cv;
using namespace aruco;


string TheInputVideo;
string TheIntrinsicFile;
float TheMarkerSize=-1;
int ThePyrDownLevel;
MarkerDetector MDetector;
VideoCapture TheVideoCapturer;
vector<Marker> TheMarkers;
vector<Marker> PencilMarkers;
Mat TheInputImage;
Marker robot_marker;
CameraParameters TheCameraParameters;

bool readCameraParameters(string TheIntrinsicFile,CameraParameters &CP,Size size);

pair<double,double> AvrgTime(0,0) ;//determines the average time required for detection
double ThresParam1,ThresParam2;
int iThresParam1,iThresParam2;
int waitTime=0;

/**
  Changeable attributes
*/

bool show_single_pose = false; // will show a cartesian on a detected marker

bool send_pose_to_app = false;

bool send_pose_to_watcher = false;

bool send_pose_to_robot = false;

bool show_average_pose = false; // will show the average marker at the tip

bool show_roi = false;

bool draw_axis = false;

bool show_pose_coordinates = false;


/** Not changeable but globally used
*/



SOCKET app_socket_handler = -1;
SOCKET app_socket = -1;

SOCKET watcher_socket_handler = -1;
SOCKET watcher_socket = -1;

SOCKET robot_socket_handler = -1;
SOCKET robot_socket = -1;

/************************************
 *
 *
 *
 *
 ************************************/
bool readArguments ( int argc,char **argv )
{
    if (argc<2) {
        cerr<<"Invalid number of arguments"<<endl;
        cerr<<"Usage: (in.avi|live[:idx_cam=0]) [intrinsics.yml] [size] [--draw-axis] [--draw-pencil]"<<endl;
        return false;
    }
    TheInputVideo=argv[1];
     if (argc>=3)
         TheIntrinsicFile=argv[2];
    if (argc>=4)
        TheMarkerSize=atof(argv[3]);

    if (argc==3)
        cerr<<"NOTE: You need makersize to see 3d info!!!!"<<endl;
    return true;
}

int findParam ( std::string param,int argc, char *argv[] )
{
    for ( int i=0; i<argc; i++ )
        if ( string ( argv[i] ) ==param ) return i;

    return -1;

}
/************************************
 *
 *
 *
 *
 ************************************/
int main(int argc,char **argv)
{
    try
    {
        if (readArguments (argc,argv)==false) {
            return 0;
        }
        //parse arguments
        
        if( findParam("--show-single-pose", argc, argv) != -1 ) {
           show_single_pose = true; 
        }

        if( findParam("--show-average-pose", argc, argv) != -1 ) {
           show_average_pose = true; 
        }

        if( findParam("--send-pose-to-app", argc, argv) != -1 ) {
           send_pose_to_app = true; 
        }

        if( findParam("--send-pose-to-robot", argc, argv) != -1 ) {
           send_pose_to_robot = true; 
        }

        if( findParam("--show-roi", argc, argv) != -1 ) {
           show_roi = true;            
        }

        if( findParam("--draw-axis", argc, argv) != -1 ) {
           draw_axis = true;            
        }

        if( findParam("--show-pose-coordinates", argc, argv) != -1 ) {
           show_pose_coordinates = true;            
        }

        if( findParam("--send-pose-to-watcher", argc, argv) != -1 ) {
           send_pose_to_watcher = true;            
        }

        


        if(send_pose_to_app) {
          std::cout << "Trying to connect app ..." << std::endl;
          app_socket_handler = createsocket(APP_SOCKET_PORT);
          if(app_socket_handler == -1) exit(-1);
          app_socket = connectSocket(app_socket_handler);
        }

        if(send_pose_to_watcher) {
          std::cout << "Trying to connect watcher ..." << std::endl;
          watcher_socket_handler = createsocket(WATCHER_SOCKET_PORT);
          if(watcher_socket_handler == -1) exit(-1);
          watcher_socket = connectSocket(watcher_socket_handler);
        }

        if(send_pose_to_robot) {
          std::cout << "Trying to connect robot ..." << std::endl;
          robot_socket_handler = createsocket(ROBOT_SOCKET_PORT);
          if(robot_socket_handler == -1) exit(-1);
          robot_socket = connectSocket(robot_socket_handler);
        } 

        

 
        //read from camera or from  file
        if (TheInputVideo.find("live")!=string::npos) {
          int vIdx=0;
          //check if the :idx is here
          char cad[100];
          if (TheInputVideo.find(":")!=string::npos) {
            std::replace(TheInputVideo.begin(),TheInputVideo.end(),':',' ');
            sscanf(TheInputVideo.c_str(),"%s %d",cad,&vIdx);
          }
            
          cout<<"Opening camera index "<<vIdx<<endl;
            
          TheVideoCapturer.open(vIdx);
          waitTime=10;
        }
        else  {
          TheVideoCapturer.open(TheInputVideo);
        }
        //check video is open
        if (!TheVideoCapturer.isOpened()) {
            cerr<<"Could not open video"<<endl;
            return -1;
        }

        //read first image to get the dimensions
        TheVideoCapturer>>TheInputImage;

        //read camera parameters if passed
        if (TheIntrinsicFile!="") {
            TheCameraParameters.readFromXMLFile(TheIntrinsicFile);
            TheCameraParameters.resize(TheInputImage.size());
        }
        //Configure other parameters
        if (ThePyrDownLevel>0)
            MDetector.pyrDown(ThePyrDownLevel);


        //Create gui

        cv::namedWindow("in",1);
        if(show_roi) cv::namedWindow("roi",1);
        MDetector.getThresholdParams( ThresParam1,ThresParam2);       
        MDetector.setCornerRefinementMethod(MarkerDetector::SUBPIX);
        iThresParam1=ThresParam1;
        iThresParam2=ThresParam2;


        char key=0;
        int index=0;
        //capture until press ESC or until the end of the video

        cout << "Marker detection params dump:" <<endl;
        int met = MDetector.getCornerRefinementMethod();
        switch(met) {
            case 0: cout << "Corner refinement: NONE" << endl; break;
            case 1: cout << "Corner refinement: HARRIS" << endl; break;
            case 2: cout << "Corner refinement: SUBPIX" << endl; break;
            case 3: cout << "Corner refinement: LINES" << endl; break;
            default: cout << "Corner refinement: UNKNOWN" << endl; break;
        }

        MDetector.setMinMaxSize(0.000001, 1);
        float min = 0, max = 0;
        MDetector.getMinMaxSize(min, max);
        cout << "Contour size MIN: " << min << "; MAX: " << max << " ;" << endl;

        cout << "Current speed: " << MDetector.getDesiredSpeed() << endl; // 0-3 with 3 meaning the fastest but least precise
        // MDetector.setDesiredSpeed(0);

        MDetector.setWarpSize(56);
        cout << "Current warp size: " << MDetector.getWarpSize() << endl; // 10-Inf with Inf meaning lowest detection rate, but biggest canonical image
        
        /*
          Predefine the calculation matrices
        */
        cv::Mat cam2robot = cv::Mat::eye( 4,4,CV_32FC1 ); 
        cv::Mat robot2cam = cv::Mat::eye( 4,4,CV_32FC1 ); 
        cv::Mat cam2pencil = cv::Mat::eye( 4,4,CV_32FC1 ); 
        cv::Mat robot2pencil  = cv::Mat::eye( 4,4,CV_32FC1 ); 

        bool robot_marker_detected = false;
        bool marker_detected = false;                            

        int current_brightness = 0;
        int last_brightness = 0;

        bool start_recording_poses = true;

        std::vector<SIMPLE_POSE> average_poses;
        std::vector<SIMPLE_POSE> recored_poses;


        do 
        {

            /**
              * Reset these variables for every loop iteration
              */
            robot_marker_detected = false;
            marker_detected = false;
            robot_marker = Marker(); // invalidate Marker
            Marker avg_marker = Marker(); // invalidate avg_marker
            PencilMarkers.clear(); // clear all found markers
            SIMPLE_POSE avg_pose;

            TheVideoCapturer.retrieve( TheInputImage);
            
            index++; //number of images captured
            double tick = (double)getTickCount();//for checking the speed

            std::cout << "Marker Size" << TheMarkerSize << std::endl;
            MDetector.detect(TheInputImage,TheMarkers,TheCameraParameters,TheMarkerSize); //Detection of markers in the image passed
            
            AvrgTime.first+=((double)getTickCount()-tick)/getTickFrequency(); //check the speed by calculating the mean speed of all iterations
            AvrgTime.second++;
            cout<<"\rTime detection="<<1000*AvrgTime.first/AvrgTime.second<<" milliseconds nmarkers="<<TheMarkers.size()<< std::endl << std::flush;

            
            
            /**
              * show a red circle in the top right corner, which indicates we are recording poses
              */
            if(start_recording_poses) cv::circle(TheInputImage, cv::Point(630, 10), 3, RGB_RED, 10);

            /**
              * Create a histogram on the original image
              */

            if(show_roi) {
              char mean_brightness_string[256];
              sprintf(mean_brightness_string, "Brightness: %f", showHistogram(TheInputImage, cv::Point(0,0), TheInputImage.cols, TheInputImage.rows));
              putText(TheInputImage,
                mean_brightness_string, 
                cv::Point(0,15),FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0,0,255,255),2);
              ;
            }


            
            if (  TheCameraParameters.isValid()) {
                for (unsigned int i=0;i<TheMarkers.size();i++) {
                    
                    // skip all markers that are not relevant. In the current setup, where we only use relevant
                    // markers this means usually only that we omit misdetections
                    if(TheMarkers[i].id != ROBOT_MARKER && !isPencilMarker(TheMarkers[i].id)) {
                      std::cout << "Skipping" << TheMarkers[i].id << std::endl;
                       continue;
                    } else {

                      // this call will also debug to console
                      TheMarkers[i].calculateExtrinsics(TheMarkerSize,TheCameraParameters, false);
                    
                      if(show_single_pose) TheMarkers[i].draw(TheInputImage,Scalar(0,0,255),1); // draw rectangle around marker
                      //if(show_pose_coordinates) showPoseCoordinates(TheInputImage, TheCameraParameters, TheMarkers[i], TheMarkers[i].Tvec.at<float>(0,0), TheMarkers[i].Tvec.at<float>(1,0), TheMarkers[i].Tvec.at<float>(0,0)); // show av2r coords but ON average pose!!!

            
                    }

                    if(draw_axis) CvDrawingUtils::draw3dAxis(TheInputImage,TheMarkers[i],TheCameraParameters);


                    if(isPencilMarker(TheMarkers[i].id)) {
                      
                      PencilMarkers.insert( PencilMarkers.begin(), TheMarkers[i] ); // insert newest element at top
                      
/*
                      current_brightness = createROI(
                        TheInputImage
                        , cam
                        , current_pose
                        , MARKER_SIZE/2 + MARKER_WHITE_MARGIN // p1_x
                        , MARKER_SIZE/2 + MARKER_WHITE_MARGIN // p1_y
                        , 0 // p1_z
                        , -(MARKER_SIZE)/2 - MARKER_WHITE_MARGIN // p2_x
                        , MARKER_SIZE + MARKER_WHITE_MARGIN // p2_y
                        ,0 //p2_z
                      );

                      */
                      

                      marker_detected = true;
                      //std::cout << "First marker detected. AVG pose of marker "<< TheMarkers[i].id <<" in relation to cam is (X,Y,Z) (alpha, beta, gamma): (" << simple_avg_pose.x << ", " << simple_avg_pose.y << ", " << simple_avg_pose.z << ") (" << simple_avg_pose.alpha <<", " << simple_avg_pose.beta <<" "<< simple_avg_pose.gamma <<")" << std::endl;
                    
                      
                    } else {
                      std::cout << "Detected ROBOT_MARKER (id:" << ROBOT_MARKER << ")!" << std::endl;
                      
                      robot_marker_detected = true;
                      robot_marker = TheMarkers[i];
                      
                    }

                    

                } //endfor
            } //endif
            //DONE! Easy, right?
            //show input with augmented information and  the thresholded image

            if(marker_detected) { // handle multi-marker averaging and time averaging

              // first we create the average homography for all detected pencil markers

              
              avg_marker.Tvec.at<float>(0,0) = 0;
              avg_marker.Tvec.at<float>(1,0) = 0;
              avg_marker.Tvec.at<float>(2,0) = 0;
              
              int detected_pencil_markers = PencilMarkers.size();
              for(int i = 0; i < detected_pencil_markers; i++) {
                Marker temp = calculateTipPose(PencilMarkers[0], TheCameraParameters);
                avg_marker.Tvec.at<float>(0,0) += temp.Tvec.at<float>(0,0);
                avg_marker.Tvec.at<float>(1,0) += temp.Tvec.at<float>(1,0);
                avg_marker.Tvec.at<float>(2,0) += temp.Tvec.at<float>(2,0);
              }

              avg_marker.Tvec.at<float>(0,0) /= detected_pencil_markers;
              avg_marker.Tvec.at<float>(1,0) /= detected_pencil_markers;
              avg_marker.Tvec.at<float>(2,0) /= detected_pencil_markers;
              
              avg_pose = getSimplePose(avg_marker);

              // DONE: Multi-Marker Averaging

              if(TIME_AVERAGE_POSES > 1) { // we average over time!
                double queue_size = average_poses.size();

                std::cout << "Current TIME_AVERAGE_POSES queue has" << queue_size << " elements" << std::endl;

                //calculate time_average_pose
                for(int i = (int) queue_size; i > 0; i--) {
                  avg_pose.x = avg_pose.x + average_poses[i-1].x;
                  avg_pose.y = avg_pose.y + average_poses[i-1].y;
                  avg_pose.z = avg_pose.z + average_poses[i-1].z;
                  avg_pose.alpha = avg_pose.alpha + average_poses[i-1].alpha;
                  avg_pose.beta = avg_pose.beta + average_poses[i-1].beta;
                  avg_pose.gamma = avg_pose.gamma + average_poses[i-1].gamma;
                }

                // we need to divide by queue size + current element
                avg_pose.x = avg_pose.x / (queue_size+1.0);
                avg_pose.y = avg_pose.y / (queue_size+1.0);
                avg_pose.z = avg_pose.z / (queue_size+1.0);
                avg_pose.alpha = avg_pose.alpha / (queue_size+1.0);
                avg_pose.beta = avg_pose.beta / (queue_size+1.0);
                avg_pose.gamma = avg_pose.gamma / (queue_size+1.0);

                // set to real avg pose
                avg_marker.Tvec.at<float>(0,0) = avg_pose.x;
                avg_marker.Tvec.at<float>(1,0) = avg_pose.y;
                avg_marker.Tvec.at<float>(2,0) = avg_pose.z;

                // TODO: Set Rvec

                std::cout << "Current Translation of TIME-AVG-marker in relation to cam is (X,Y,Z): (" << avg_pose.x << ", " << avg_pose.y << ", " << avg_pose.z << ")" << std::endl;
                
                // we add the current element to the queue and remove the last
                average_poses.insert( average_poses.begin(), avg_pose ); // insert newest element at top
                
                if(queue_size >= TIME_AVERAGE_POSES) { // remove the last element if queue is exceeded
                  average_poses.pop_back();  
                }
              }


            }

          

            if(robot_marker_detected && marker_detected) { // handle transformation

              
              
              // now we got an average marker ready to use


              // first we need to calculate the transformation Matrix to get from the zero_marker to the pencil_tip
              // logic is: Cam1->ZeroMarker * ZeroMarker->PencilTip = Cam1->PencilTip
              // => (Cam1->ZeroMarker)^-1 * Cam1->PencilTip = ZeroMarker->PencilTip
            

              cam2pencil = TheCameraParameters.getRTMatrix(avg_marker.Rvec, avg_marker.Tvec, -1); 
              cam2robot = TheCameraParameters.getRTMatrix(robot_marker.Rvec, robot_marker.Tvec, -1); 

              robot2cam = cam2robot.inv(); 

              robot2pencil = robot2cam * cam2pencil;

              std::cout << "The relative shift of the markers to another is " << robot2pencil.at<float>(0,3) << "|" << robot2pencil.at<float>(1,3) << "|" << robot2pencil.at<float>(2,3) << ";" << std::endl;

                  
              SIMPLE_POSE aktpos = getSimplePose(robot2pencil);
                  
              std::cout << "Current Translation of robot pose is (X,Y,Z): (" << aktpos.x << ", " << aktpos.y << ", " << aktpos.z << ")" << std::endl;
              std::cout << "Current Quaternion of robot marker in relation to cam is (R, i1, i2, i3) : (" << (aktpos.R ) << ", " << aktpos.i1 << ", " << aktpos.i2 << ", " << aktpos.i3 << ")" << std::endl;
              
              //if(show_pose_coordinates) showPoseCoordinates(TheInputImage, TheCameraParameters, avg_marker, aktpos.x, aktpos.y, aktpos.z); // show av2r coords but ON average pose!!!


              aktpos.type = 1;

              SIMPLE_POSE avg_simple_pose = getSimplePose(avg_marker);

              showPoseCoordinates(TheInputImage, TheCameraParameters, avg_marker, aktpos.x, aktpos.y, aktpos.z); // show av2r coords but ON average pose!!!


              if(start_recording_poses == true) {
                recored_poses.insert(recored_poses.begin(), aktpos);
                
                if(send_pose_to_app == true) {
                  std::cout << "Sending pose to app" << std::endl; 
                
                  if(sendPos(app_socket, aktpos) == 32) { // 32 == broken_pipe
                    std::cout << "Connection lost. Reconnecting client...";
                    app_socket = connectSocket(app_socket_handler);
                  }
                  
                }
                if(send_pose_to_watcher == true) {
                  std::cout << "Sending pose to watcher" << std::endl; 
                
                  if(sendPos(watcher_socket, aktpos) == 32) { // 32 == broken_pipe
                    std::cout << "Connection lost. Reconnecting client...";
                    watcher_socket = connectSocket(watcher_socket_handler);
                  }
                  
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

            if(show_average_pose && marker_detected) {


              markTip(TheInputImage, TheCameraParameters, avg_marker);

       
            }
            
            cv::imshow("in",TheInputImage);
            
            key=cv::waitKey(waitTime);//wait for key to be pressed
        }while(key!=27 && TheVideoCapturer.grab());

    } catch (std::exception &ex)

    {
        cout<<"Exception :"<<ex.what()<<endl;
    }

}
