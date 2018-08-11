#include"detection.h"
#include"SocketMatTransmissionClient.h"

using namespace std;
using namespace cv;
Mat frame,dst,kernel;//必要全局变量
Point2f center;
float radius;
Rect rect;
  


int main()
{
    SocketMatTransmissionClient socketMat;  //声明类
//	if(socketMat.socketConnect("10.0.0.6",6666)<0){
// 	return 0;
//	}

    VideoCapture capture; 
    capture.open(0);//开启摄像头
    if(!capture.isOpened())
    {
        printf("can not open video file   \n");
        return -1;
    }
    //开操作处理
//    kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

    namedWindow("input", CV_WINDOW_AUTOSIZE);//设立窗口
//    namedWindow("output", CV_WINDOW_AUTOSIZE);
    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hireachy;
	Size size(IMG_WIDTH,IMG_HEIGHT);
    while (capture.read(frame))
    {   
		resize(frame,frame,size);
//    	Rect rect;
		cvtColor(frame,frame,COLOR_BGR2HSV);
        //blur(frame, dst, Size(5,5));
        inRange(frame, Scalar(153,43,46), Scalar(180,255,255), dst);//确定识别颜色范围(参数：H,S,V)
        //开操作
//        morphologyEx(dst,dst,MORPH_OPEN,kernel);
        //获取边界
        findContours(dst, contours, hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0,0));
        //框选面积最大的边界
        double maxArea=0;
        if (contours.size() > 0)
        {
            for (unsigned int i = 0; i < contours.size(); i++)
            {
                double area = contourArea(contours[static_cast<int>(i)]);
                if (area > maxArea)
                {
                    maxArea = area;
//                    rect = boundingRect(contours[static_cast<int>(i)]);
                    minEnclosingCircle(contours[static_cast<int>(i)], center, radius);
                }
            }
        }
		
        //矩形框
//		if(40*rect.x*rect.y>=frame.cols*frame.rows){
//        	rectangle(frame,rect, Scalar(0,255,0),2);
//        }
		//圆形框
//		if(40*radius*radius*3.1415>=frame.cols*frame.rows)
       	circle(frame, Point(center.x,center.y), (int)radius, Scalar(0,255,0), 2);//画圆
    	direction(center);
		imshow("input", frame);//显示图像
        waitKey(30);
//		socketMat.transmit(frame);//编码并传输图像

    }

    capture.release();
    return 0;
}

