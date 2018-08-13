#include"detection.h"
#include"SocketMatTransmissionClient.h"
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#define MAXLINE 1024

using namespace std;
using namespace cv; 

Mat frame,dst,kernel;//必要全局变量
Point2f center;
float radius;
Rect rect;



int main()
{
	int fifod;
	int sig=0;//图像传输开关，默认为关
	int temp;
	unlink("fifo");
	mkfifo("fifo",0666);
	if(fork()>0){                                     //child,listen
		fifod=open("fifo",O_RDONLY);
//		read(fifod,&temp,sizeof(temp));
//		close(fifod);

//		if(sig!=temp) sig=temp;         //如何获取信号。

		SocketMatTransmissionClient socketMat;  //声明类
	
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
    	std::vector<std::vector<Point> > contours;
    	std::vector<Vec4i> hireachy;
		Size size(IMG_WIDTH,IMG_HEIGHT);
   		while (1)
   		{   	
				capture>>frame;
				resize(frame,frame,size);
    			Rect rect;
				cvtColor(frame,frame,COLOR_BGR2HSV);
        		//blur(frame, dst, Size(5,5));
        		inRange(frame, Scalar(153,43,46), Scalar(180,255,255), dst);//确定识别颜色范围(参数：H,S,V)
        		//开操作
//      	  	morphologyEx(dst,dst,MORPH_OPEN,kernel);
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
//              		      rect = boundingRect(contours[static_cast<int>(i)]);
                		    minEnclosingCircle(contours[static_cast<int>(i)], center, radius);
                		}
            		}	
        		}	
		
       			circle(frame, Point(center.x,center.y), (int)radius, Scalar(0,255,0), 2);//画圆
    			direction(center);
				imshow("input", frame);//显示图像
        		waitKey(30);
 	

				while(read(fifod,&temp,sizeof(sig))>0){
					if(sig!=temp)//收到触发信号
						sig=temp;
						if(temp==1)
							socketMat.socketConnect("10.0.0.6",6666);
					close(fifod);
				}
				if(sig==1)
					socketMat.transmit(frame);//编码并传输图像

    		}

	}
	

	else{                                        //parents

		int signal=0;
 		
		
		int listenfd,connfd;
 		struct sockaddr_in sockaddr;
 		char buff[MAXLINE];
 		int n;
 
 		memset(&sockaddr,0,sizeof(sockaddr));
 
 		sockaddr.sin_family = AF_INET;
 		sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 		sockaddr.sin_port = htons(10004);
 
 		listenfd = socket(AF_INET,SOCK_STREAM,0);
 
 		bind(listenfd,(struct sockaddr *) &sockaddr,sizeof(sockaddr));
 
 		listen(listenfd,1024);

 
 		printf("Please wait for the client information\n");
		fifod=open("fifo",O_WRONLY); 
 		for(;;)
 		{
 			if((connfd = accept(listenfd,(struct sockaddr*)NULL,NULL))==-1)		{
 			printf("accpet socket error: %s errno :%d\n",strerror(errno),errno);
 			continue;
 			}
 			n = recv(connfd,buff,MAXLINE,0);
 			//printf("n=%d.\n",n);
 			buff[n] = '\0';
 			printf("recv msg from client:%s.\n",buff);
 			close(connfd);
 			
			if(strcmp(buff,"1")==0){

				printf("open.\n");
				
				//打开图像接口的信号
				signal=1;
				write(fifod,&signal,sizeof(signal));
				close(fifod);
				break;
    		}
			else if(strcmp(buff,"0")==0){
				printf("close.\n");
				signal=0;
				fifod=open("fifo",O_WRONLY);
				write(fifod,&signal,sizeof(signal));
				//关闭图像接口的信号
				break;
			}
 		}
 		close(listenfd);
	}
}	



