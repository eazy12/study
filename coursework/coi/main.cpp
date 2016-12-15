// найти контуры

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/aruco/dictionary.hpp>

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
        cv::Mat src = cv::imread("board2.JPG");
        cv::Mat binaryImage;
        cv::Mat srcCopy;
        cv::Mat srcAnotherCopy;
        
        src.copyTo(srcCopy);
        src.copyTo(srcAnotherCopy);
        
        if (!src.data){
		std::cout << "?" << std::endl;
                return -1;
	}
	
	cv::namedWindow("src",cv::WINDOW_NORMAL);
	cv::namedWindow("binary",cv::WINDOW_NORMAL);
	cv::namedWindow("srcCopy",cv::WINDOW_NORMAL);
	cv::namedWindow("srcAnotherCopy",cv::WINDOW_NORMAL);   
	cv::namedWindow("drawing",cv::WINDOW_NORMAL);  
	//cv::namedWindow("bi2",cv::WINDOW_NORMAL);  
	
	cv::imshow("src", src);
        
        cv::cvtColor(src, binaryImage, CV_BGR2GRAY);
        cv::GaussianBlur(binaryImage, binaryImage,cv::Size(101,101),3);
	       //cv::adaptiveThreshold(binaryImage, binaryImage, 175, cv::ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 125, 0);
	      cv::threshold(binaryImage, binaryImage, 105,255,CV_THRESH_BINARY);
        cv::imshow("binary", binaryImage);

	std::vector<int> ids;
        std::vector<std::vector<cv::Point2f> > corners;
        vector<vector<cv::Point> > contours;
        vector<cv::Vec4i> hierarchy;
        cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_ARUCO_ORIGINAL);

        cv::aruco::detectMarkers(binaryImage, dictionary, corners, ids);
        cv::aruco::drawDetectedMarkers(srcCopy, corners, ids );    
        
        cout << "Количество маркеров: " << ids.size() << endl;
        
        for( int i = 0; i < ids.size(); i++)
        	cout << ids[i] << endl << corners[i] << endl;
       	
       	int radius = 1;
       	
  	//vector<cv::Vec2f> lines;
  	//cv::Mat binaryImage2 = cv::Mat(binaryImage.size(), CV_8UC1, cvScalar(255,255,255));
       	//cv::HoughLines(binaryImage, lines , 30 ,0.3,0);
       	//cout << src.lines().width << endl << src.lines().height<< endl;
       	
	// for(size_t i = 0; i < lines.size(); i++ )
	// {
	// 	float rho = lines[i][0], theta = lines[i][1];
	// 	cv::Point pt1, pt2;
	// 	double a = cos(theta), b = sin(theta);
	// 	double x0 = a*rho, y0 = b*rho;
	// 	pt1.x = cvRound(x0 + 1000*(-b));
	// 	pt1.y = cvRound(y0 + 1000*(a));
	// 	pt2.x = cvRound(x0 - 1000*(-b));
	// 	pt2.y = cvRound(y0 - 1000*(a));
	// 	cv::line( binaryImage2, pt1, pt2, cv::Scalar(0,0,255), 3, cv::LINE_AA);
	// }
       	//for (int j= 0; j < lines.
	//cv::Mat Kern = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(405,405));
	//cv::morphologyEx(binaryImage, binaryImage,CV_MOP_OPEN, Kern);
	cv::findContours(binaryImage, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	
	vector<cv::Rect> boundRect( contours.size() );
	vector<vector<cv::Point> > contours_poly( contours.size() );
	
	for( int i = 0; i < contours.size(); i++ )
		{	
			cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
			boundRect[i] = cv::boundingRect(cv::Mat(contours_poly[i]) );
		}

	cv::Mat drawing = cv::Mat(binaryImage.size(), CV_8UC3, cvScalar(255,255,255));
	int maxiX=0;
  int maxiY=0;
  int maxX=0;
  int maxY=0;
  cv::Scalar color = cv::Scalar( 0,0,0 );
	for( int i = 0; i< contours.size(); i++ )
	{
		
		cv::drawContours( drawing, contours_poly, i, color, 1, 8, vector<cv::Vec4i>(), 0, cv::Point() );
    std::cout <<boundRect[i].area() << "\t" << boundRect[i].br()<< "\t" << (boundRect[i].br() - boundRect[i].tl()).x <<std::endl;
    if((boundRect[i].br() - boundRect[i].tl()).x > maxX)
      { maxiX=i; maxX = (boundRect[i].br() - boundRect[i].tl()).x ;}
      
    if((boundRect[i].br() - boundRect[i].tl()).y > maxY )
    { maxiY=i;maxY = (boundRect[i].br() - boundRect[i].tl()).y ;}
		//rectangle( srcAnotherCopy, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
	}
  cout << maxiX << "\t"<<maxiY << endl;
  rectangle( srcAnotherCopy, boundRect[maxiY].tl(), boundRect[maxiY].br(), color, 2, 8, 0 );
  rectangle( srcAnotherCopy, boundRect[maxiX].tl(), boundRect[maxiX].br(), color, 2, 8, 0 );

	double res = cv::norm(corners[0][0] - corners[0][1] );	
	cout << res << " or " << res/5.0 << " pixels per cm" <<endl;
	cv::imshow("srcCopy", srcCopy);
	cv::imshow("srcAnotherCopy", srcAnotherCopy);
	cv::imshow("drawing", drawing);
	//cv::imshow("bi2", binaryImage2);

	cv::waitKey(0);
	return 0;
}


