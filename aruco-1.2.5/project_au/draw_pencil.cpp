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
#include "aruco.h"
#include "cvdrawingutils.h"
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>


#define RGB_RED Scalar(0,0,255,255)
#define RGB_GREEN Scalar(0,255,0,255)
#define RGB_BLUE Scalar(255,0,0,255)

#define DISTANCE_CUBE_CORE_PENCIL_TIP 0.08

#define X 0
#define Y 1
#define Z 2

using namespace cv;
using namespace aruco;


string TheInputVideo;
string TheIntrinsicFile;
float TheMarkerSize=-1;
int ThePyrDownLevel;
MarkerDetector MDetector;
VideoCapture TheVideoCapturer;
vector<Marker> TheMarkers;
Mat TheInputImage,TheInputImageCopy;
CameraParameters TheCameraParameters;

bool readCameraParameters(string TheIntrinsicFile,CameraParameters &CP,Size size);

pair<double,double> AvrgTime(0,0) ;//determines the average time required for detection
double ThresParam1,ThresParam2;
int iThresParam1,iThresParam2;
int waitTime=0;

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
        bool draw_axis = false;
        if( findParam("--draw-axis", argc, argv) != -1 ) {
           draw_axis = true; 
        }

        bool draw_pencil = false;
        if( findParam("--draw-pencil", argc, argv) != -1 ) {
           draw_pencil = true; 
        }

        bool draw_rotation_indicator = false;
        if( findParam("--draw-rotation-indicator", argc, argv) != -1 ) {
           draw_rotation_indicator = true; 
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

        cv::namedWindow("thres",1);
        cv::namedWindow("in",1);
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
        


        do 
        {
            TheVideoCapturer.retrieve( TheInputImage);
            //copy image

            index++; //number of images captured
            double tick = (double)getTickCount();//for checking the speed
            //Detection of markers in the image passed
            MDetector.detect(TheInputImage,TheMarkers,TheCameraParameters,TheMarkerSize);
            //chekc the speed by calculating the mean speed of all iterations
            AvrgTime.first+=((double)getTickCount()-tick)/getTickFrequency();
            AvrgTime.second++;
            cout<<"\rTime detection="<<1000*AvrgTime.first/AvrgTime.second<<" milliseconds nmarkers="<<TheMarkers.size()<< std::flush;

            //print marker info and draw the markers in image
            TheInputImage.copyTo(TheInputImageCopy);
	    

            for (unsigned int i=0;i<TheMarkers.size();i++) {
                cout<<endl<<TheMarkers[i]; // output marker info to console
                TheMarkers[i].draw(TheInputImageCopy,Scalar(0,0,255),1); // draw rectangle around marker
            }
            if (TheMarkers.size()!=0)  cout<<endl;
            

            
            //draw a 3d cube in each marker if there is 3d info
            if (  TheCameraParameters.isValid()) {
                for (unsigned int i=0;i<TheMarkers.size();i++) {
                    //CvDrawingUtils::draw3dCube(TheInputImageCopy,TheMarkers[i],TheCameraParameters);
                        
                    float size=TheMarkers[i].ssize*0.5; // half side length of the cube
                    
                    Mat objectPoints (6,3,CV_32FC1); // we define five 3D-Points 
                    // P1 = Center of the marker plane. Relative to each marker
                    // P2 = Center of the cube the markers are place on. Absolute.
                    // P3, P4 = Tip of the pencil. Relative to each marker.
                    // P5,P6 = Off center point to show that the rotation of the pencil tip is known. Absolute.
                    
                    // define a by giving length on axis

                    // P1
                    objectPoints.at<float>(0,X)=0; // point 0, pos x
                    objectPoints.at<float>(0,Y)=0; // point 0, pos y
                    objectPoints.at<float>(0,Z)=0; // point 0, pos z
                    
                    // 
                    objectPoints.at<float>(1,X)=0;      // point 1, pos x
                    objectPoints.at<float>(1,Y)=0;      // point 1, pos y
                    objectPoints.at<float>(1,Z)=-size;  // point 1, pos z

                    objectPoints.at<float>(2,X)= 0;                                 // point 2, pos x
                    objectPoints.at<float>(2,Y)= DISTANCE_CUBE_CORE_PENCIL_TIP;    // point 2, pos y
                    objectPoints.at<float>(2,Z)= -size;                             // point 2, pos z
                    
                    objectPoints.at<float>(3,X)= 0;                                 // point 3, pos x
                    objectPoints.at<float>(3,Y)= 0;     // point 3, pos y
                    objectPoints.at<float>(3,Z)= -size - DISTANCE_CUBE_CORE_PENCIL_TIP; // point 3, pos z
                                            
                    objectPoints.at<float>(4,X)= size;                                 // point 2, pos x
                    objectPoints.at<float>(4,Y)= DISTANCE_CUBE_CORE_PENCIL_TIP;    // point 2, pos y
                    objectPoints.at<float>(4,Z)= -size;                             // point 2, pos z
                    
                    objectPoints.at<float>(5,X)= size;                                  // point 3, pos x
                    objectPoints.at<float>(5,Y)= 0;                                     // point 3, pos y
                    objectPoints.at<float>(5,Z)= -size - DISTANCE_CUBE_CORE_PENCIL_TIP; // point 3, pos z
                    
                    vector<Point2f> imagePoints;
                    cv::projectPoints( objectPoints, TheMarkers[i].Rvec,TheMarkers[i].Tvec, TheCameraParameters.CameraMatrix,TheCameraParameters.Distorsion,   imagePoints);
                    
                    if(draw_pencil) {
                        
                        switch(TheMarkers[i].id) {
                            case 114:
                                cv::line(TheInputImageCopy,imagePoints[1],imagePoints[2],RGB_RED ,1,CV_AA); // draw the tip
                                if(draw_rotation_indicator) cv::line(TheInputImageCopy,imagePoints[2],imagePoints[4],RGB_RED ,1,CV_AA); // draw the off center line                                
                            break;
                            case 328:
                                cv::line(TheInputImageCopy,imagePoints[1],imagePoints[3],RGB_RED ,1,CV_AA); // draw the tip
                                if(draw_rotation_indicator) cv::line(TheInputImageCopy,imagePoints[3],imagePoints[5],RGB_RED ,1,CV_AA); // draw the off center line                                
                            default:
                              printf("Unexpected marker detected %d\n",TheMarkers[i].id);
                            break;
                        }

                        cv::line(TheInputImageCopy,imagePoints[0],imagePoints[1],RGB_RED ,1,CV_AA); // draw the line to the center
                        putText(TheInputImageCopy,"x", imagePoints[1],FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0,0,255,255),2);
                     }

                    if(draw_axis) {
                        CvDrawingUtils::draw3dAxis(TheInputImageCopy,TheMarkers[i],TheCameraParameters);
                    }
                } //endfor
            } //endif
            //DONE! Easy, right?
            //show input with augmented information and  the thresholded image
            cv::imshow("in",TheInputImageCopy);
            
            //cv::imshow("thres",MDetector.getThresholdedImage()); // not really needed

            key=cv::waitKey(waitTime);//wait for key to be pressed
        }while(key!=27 && TheVideoCapturer.grab());

    } catch (std::exception &ex)

    {
        cout<<"Exception :"<<ex.what()<<endl;
    }

}
