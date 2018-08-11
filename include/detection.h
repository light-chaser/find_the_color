#include<iostream>
#include<cmath>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;


extern Mat frame,dst,kernel;
extern Point2f center;
extern float radius;
extern Rect rect;

void direction(Point2f center);
//void direction(Rect rect);
