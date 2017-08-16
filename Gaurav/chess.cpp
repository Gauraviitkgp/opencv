#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

int i,j,t,p;

void displayimage(Mat image, String windowname){
    
    imshow(windowname, image);
}


Mat readimage(String filename)
{
    return imread(filename);
}

void createimg()
{
  Mat temp(800,800,CV_8UC3,255);
  int i,j,k;
  for(i=0;i<800;i++)
    {
      for(j=0;j<800;j++)
	{
	  if((((i/100)+(j/100))%2)==0)
	    {
	      for(k=0;k<=2;k++)
		temp.at<Vec3b>(i,j)[k]=255;
	      
	    }
	  else
	    {
	      for(k=0;k<=2;k++)
		temp.at<Vec3b>(i,j)[k]=0;
	    }
	}
    }
imshow("Chess",temp);
}

int main()
{
    createimg();   
   
    waitKey(0);
    return 0;
}
