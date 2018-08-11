#include"detection.h"
#define length frame.cols/2
#define heighth frame.rows/2
#define tan_alfari tan(0.632)




/*void direction(Rect rect){
	Point2f coordinate;
	coordinate.x=rect.x + rect.width/2-length;

	coordinate.y=rect.y + rect.height /2 -heighth;
	
	double thita_x=atan(tan_alfari*coordinate.x / length);
	double thita_y=atan(tan_alfari*coordinate.y / heighth);
	//此处应该写把角度数据传出去的代码；//
	
	Scalar green(0,176,0);
	stringstream ss;
	string str;
	ss<<thita_x<<","<<thita_y<<endl;
	ss>>str;
	putText(frame,
			str,
			center,
			FONT_HERSHEY_SIMPLEX,
			16,
			green,
			1,
			8);	
}*/
void direction(Point2f center){
	Point2f coordinate;
	if(3*3.14*pow(radius,2)>=(frame.cols*frame.rows)){
		cout<<"STOP!!Its been closed!!"<<endl;//或者别的行为方式。
	}else{	
	coordinate.x=center.x-length;
	coordinate.y=-(center.y-heighth);
	
	double thita_x=atan(tan_alfari*coordinate.x / length);
	double thita_y=atan(tan_alfari*coordinate.y / heighth);
	Scalar green(0,176,0);
	stringstream ss;
	string str;
	ss<<thita_x<<","<<thita_y<<endl;
	ss>>str;
//	cout<<str<<endl;
	putText(frame,
			str,
			center,
			FONT_HERSHEY_COMPLEX,
			0.8,
			green,
			2,
			8,
			0);	
	}

}
