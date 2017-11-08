/* Author: Trevor Sherrard
 * Date: November 2017
 * Purpose: This file contains the prototype of
 *          houghLinesAndDraw. 
 */

#ifndef LINE_DETECT_H
#define LINE_DETECT_H

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

bool houghLinesAndDraw(Mat src, Mat& dest);
#endif
