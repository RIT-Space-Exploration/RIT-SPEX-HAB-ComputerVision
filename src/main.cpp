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

void printHelpMessage()
{
    cout << "---------Program CLI commands---------" << endl;
    cout << "./executable <camIndex1> <camIndex2>" << endl;
    cout << "" << endl;
    cout << "if no arguments are given, default camIndexes are 1 and 2." << endl;
}

int main(int argc, char** argv)
{
    if(argc > 2)
    {
        char* VidIndex1 = argv[1];
        char* VidIndex2 = argv[2];
        VidIndexInt1 = atoi(VidIndex1);
        VidIndexInt2 = atoi(VidIndex2);
    }

    VideoCapture cap1(VidIndexInt1);
    VideoCapture cap2(VidIndexInt2);

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
        Mat curFrameCam1;
        Mat curFrameCam2;

        vector<Vec4i> VecCam1;
        vector<Vec4i> VecCam2;
        bool successCam1 = cap1.read(curFrameCam1);
        bool successCam2 = cap2.read(curFrameCam2);
        frameCount++;

        sprintf(frameIndxCam1, "../../images/Cam1_frameIndex%lu", frameCount);
        sprintf(frameIndxCam2, "../../images/Cam2_frameIndex%lu", frameCount);

        if(successCam1)
        {
            imwrite(frameIndxCam1, curFrameCam1);
        }
        if(successCam2)
        {
            imwrite(frameIndxCam2, curFrameCam2);
        }

        Mat destFrameCam1;
        Mat destFrameCam2;

        VecCam1 = houghLinesAndDraw(curFrameCam1, destFrameCam1);
        VecCam2 = houghLinesAndDraw(curFrameCam2, destFrameCam2);

        if(VecCam1.size() != 0)
        {
            sprintf(frameIndxCam1, "../../images/LinesCam1_frameIndex%lu", frameCount);
            imwrite(frameIndxCam1, destFrameCam1);
        }
        if(VecCam2.size() != 0)
        {
            sprintf(frameIndxCam2, "../../images/LinesCam2_frameIndex%lu", frameCount);
            imwrite(frameIndxCam2, destFrameCam2);
        }

        char keyStroke = (char) waitKey(1000);
        if(keyStroke == 27)
        {
            break;
        }
    }
}
