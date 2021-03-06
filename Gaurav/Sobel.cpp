#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <math.h>

using namespace cv;
using namespace std;

int x;
int a[3][3]={{3,10,3},{0,0,0},{-3,-10,-3}},b[3][3]={{3,0,-3},{10,0,-10},{3,0,-3}};

void displayimage(Mat image, String windowname){
    
    imshow(windowname, image);
}


Mat readimage(String filename)
{
    return imread(filename);
}


Mat binary(int G[],Mat img)
{
  Mat img1(img.rows,img.cols,CV_8UC1);
  int i,j,y=0;
  for(i=0;i<img.rows;i++)
    {
      for(j=0;j<img.cols;j++)
	{
	  if(G[y++]<x)
	    {
	      img1.at<uchar>(i,j)=0;
	    }
	  else
	    {
	      img1.at<uchar>(i,j)=255;
	    }
	}
    }
  return img1;
}
  


Mat perwitt(Mat img)
{
  int i,j,k,l,sum[2]={0,0},p=0;
  int G[1000*1000];
  Mat img1(img.rows,img.cols,CV_8UC1);
  for(i=0;i<img.rows;i++)
    {
      for(j=0;j<img.cols;j++)
	{
	  for(k=-1;k<2;k++)
	    {
	      for(l=-1;l<2;l++)
		{
		  if(k+i>=0 && l+j>=0 && k+i<=img.rows && l+j<=img.cols)
		    {
		      sum[0]+=a[k+1][l+1]*img.at<uchar>(i+k,j+l);
		      sum[1]+=b[k+1][l+1]*img.at<uchar>(i+k,j+l);
		    }
		}
	    }
	  G[p++]=abs(sum[0])+abs(sum[1]);
	  sum[0]=sum[1]=0;
	}
    }
  return binary(G,img);
}




int main(int argc, char** argv)
{
  int i,j,k,l;
  Mat image=imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  Mat img2(image.rows,image.cols,CV_8UC1);
  namedWindow("Perwitt",WINDOW_NORMAL);
  createTrackbar("Intensity","Perwitt",&x,400);
  while(1)
      {
	img2=perwitt(image);
	for(i=0;i<image.rows;i++)
	  {
	    for(j=0;j<image.cols;j++)
	      {
		for(k=-1;k<2;k++)
		  {
		    for(l=-1;l<2;l++)
		      {
			if(img2.at<uchar>(i+k,j+l)==0)
			  img2.at<uchar>(i,j)=0;
			if(img2.at<uchar>(i+k,j+l)==255)
			  img2.at<uchar>(i,j)=255;
		      }
		  }
	      }
	  }
	imshow("Perwitt",img2);
	waitKey(10);
      }
    return 0;
}

