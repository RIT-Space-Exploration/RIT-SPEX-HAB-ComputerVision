/* Author: Trevor Sherrard
 * Date: November 2017
 * Purpose: This program serves to supply horizon 
 *          detection and frame capture/save functionality
 *          to the RIT SPEX HAB system
 */

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "../include/detectLines.h"

using namespace cv;
using namespace std;

int VidIndexInt1 = 0;
int VidIndexInt2 = 1;

char* frameIndxCam1;
char* frameIndxCam2;

unsigned long frameCount = 0;

// usecase help message
void printHelpMessage()
{
    cout << "---------Program CLI commands---------" << endl;
    cout << "./RIT_SPEX_Horizon <camIndex1> <camIndex2>" << endl;
    cout << "" << endl;
    cout << "if no arguments are given, default camIndexes are 1 and 2." << endl;
}

int main(int argc, char** argv)
{
    // check for non-default indexes
    if(argc > 2)
    {
        char* VidIndex1 = argv[1];
        char* VidIndex2 = argv[2];
        VidIndexInt1 = atoi(VidIndex1);
        VidIndexInt2 = atoi(VidIndex2);
    }

    // Initialize Camera captures
    VideoCapture cap1(VidIndexInt1);
    VideoCapture cap2(VidIndexInt2);

    // make sure camera streams open independently
    if(!cap1.isOpened())
    {
        cout << "failed to open camera 1 stream !" << endl;
        printHelpMessage();
        return -1;
    }
    if(!cap2.isOpened())
    {
        cout << "failed to open camera 2 stream !" << endl;
        printHelpMessage();
        return -1;
    }
    
    while(true)
    {
        // Init capture matricies.
        Mat curFrameCam1;
        Mat curFrameCam2;

        vector<Vec4i> VecCam1;
        vector<Vec4i> VecCam2;

        // try to capture a frame
        bool successCam1 = cap1.read(curFrameCam1);
        bool successCam2 = cap2.read(curFrameCam2);
        frameCount++;

        sprintf(frameIndxCam1, "../../images/Cam1_frameIndex%lu.png", frameCount);
        sprintf(frameIndxCam2, "../../images/Cam2_frameIndex%lu.png", frameCount);

        // save off captures if sucessful
        if(successCam1)
        {
            imwrite(frameIndxCam1, curFrameCam1);
        }
        if(successCam2)
        {
            imwrite(frameIndxCam2, curFrameCam2);
        }

        // Init matricies for detected horizon
        Mat destFrameCam1;
        Mat destFrameCam2;

        // attempt to find horizons
        VecCam1 = houghLinesAndDraw(curFrameCam1, destFrameCam1);
        VecCam2 = houghLinesAndDraw(curFrameCam2, destFrameCam2);

        // Save off frame with detected lines drawn on.
        if(VecCam1.size() != 0)
        {
            sprintf(frameIndxCam1, "../../images/LinesCam1_frameIndex%lu.png", frameCount);
            imwrite(frameIndxCam1, destFrameCam1);
        }
        if(VecCam2.size() != 0)
        {
            sprintf(frameIndxCam2, "../../images/LinesCam2_frameIndex%lu.png", frameCount);
            imwrite(frameIndxCam2, destFrameCam2);
        }

        // wait two seconds before looping again
        char keyStroke = (char) waitKey(2000);
        
        // break out if escape is pressed
        if(keyStroke == 27)
        {
            break;
        }
    }
}
