#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "../include/detectLines.h"

using namespace cv;
using namespace std;

vector<Vec4i> houghLinesAndDraw(Mat src, Mat &dest)
{
    Mat cdest;
    Canny(src, cdest, 50, 200, 3);
    cvtColor(cdest, cdest, COLOR_GRAY2BGR);

    vector<Vec4i> lines;
    HoughLinesP(cdest, lines, 1, CV_PI/180, 50, 50, 10);
    for(int i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];
        line(dest, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
    }
    return lines;
}
