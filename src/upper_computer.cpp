#include"SocketMatTransmissionServer.h"
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

#define MAXLINE 1024
int main()
{
    int fd=fork();
    if(fd==0)   //父进程
    {
 		char *servInetAddr = "127.0.0.1";
		char commond[10]; 	
		int socketfd;
 		struct sockaddr_in sockaddr;
 		char recvline[MAXLINE], sendline[MAXLINE];
 		int n;
 
 		socketfd = socket(AF_INET,SOCK_STREAM,0);
 		memset(&sockaddr,0,sizeof(sockaddr));
 		sockaddr.sin_family = AF_INET;
 		sockaddr.sin_port = htons(10004);
 		inet_pton(AF_INET,servInetAddr,&sockaddr.sin_addr);
 		if((connect(socketfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr))) < 0 )
 		{
 			printf("connect error %s errno: %d\n",strerror(errno),errno);
 			exit(0);
 		}

 		printf("send message to server\n");

 	//fgets(sendline,1024,stdin);
 		strcpy(sendline,"1");
 		if((send(socketfd,sendline,strlen(sendline),0)) < 0)
 		{
	 		printf("send mes error: %s errno : %d",strerror(errno),errno);
 			exit(0);
 		}	
 		close(socketfd);
 	//怎么关？
	}
	else if(fd>0){
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
}

