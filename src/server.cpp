#include "SocketMatTransmissionServer.h"
   
   int main()
   {
       SocketMatTransmissionServer socketMat;//建立类
       if (socketMat.socketConnect(6666) < 0)//创建接口
       {
           return 0;
       }
   
      cv::Mat image;
      while (1)
      {
          if(socketMat.receive(image) > 0)//接收并显示图像
          {
              cv::imshow("output",image);
              cv::waitKey(30);
          }
      }
   
      socketMat.socketDisconnect();  
      return 0;
  }

