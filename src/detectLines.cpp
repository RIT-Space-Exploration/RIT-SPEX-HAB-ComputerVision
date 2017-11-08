/* Author: Trevor Sherrard
 * Date: November 2017
 * Purpose: This file contains the implementation 
 *          of houghLinesAndDraw. This function detects 
 *          lines and draws detected lines onto the
 *          Mat dest.
 */

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "../include/detectLines.h"

using namespace cv;
using namespace std;

/* houghLinesAndDraw attempts to find lines
 * in Mat src. Any lines found in the image that meet
 * the threshold criteria are drawn onto Mat dest.
 * 
 * The vector of Vec4i containing endpoints of lines
 * detected is returned.
 */
bool houghLinesAndDraw(Mat src, Mat& dest)
{
    Mat cdest;
    int LThresh = 50;
    int HThresh = 100;
    int KernelSize = 3;
    int rhoRes = 1;
    double thetaRes = CV_PI/180;
    int IntersectThresh = 10;
    int minLineLen = 10;
    int maxLineGap = 10;
    bool detectedLines = false;

    // make empty vector of Vec4i for detected line endpoints.
    vector<Vec4i> lines;

    if(src.rows == 0 || src.cols == 0)
    {
        return detectedLines;
    }

    /* src -> source image
     * cdest -> canny image
     * LThresh -> Lower gradient threshold
     * HThresh -> Higher gradient threshold
     * KernelSize -> Internal Sobel filter kernel size
     */
    Canny(src, cdest, LThresh, HThresh, KernelSize);

    // Convert src to grayscale store in cdest
    //cvtColor(cdest, cdest, COLOR_BGR2GRAY);
    /* cdest -> image to dected lines in.
     * lines -> vector of Vec4i to store detected line endpoints.
     * rhoRes -> resolution of Rho in pixels.
     * thetaRes -> resolution of theta in radians.
     * IntersectThresh -> Aproximation line intersection threshold.
     * minLineLen -> Minimum line length needed for detection.
     * maxLineGap -> Max gap between two points on a line 
     *               to still be considered in the same line.
     */
    HoughLinesP(cdest, lines, rhoRes, thetaRes, IntersectThresh, 
        minLineLen, maxLineGap);

    // loop through detected lines and draw onto dest Mat
    for(int i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];
        line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
        detectedLines = true;
    }

    // set dest image as drawn over src image
    dest = src;

    // return bool indicating detected lines
    return detectedLines;
}
