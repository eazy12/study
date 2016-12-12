// найти контуры

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/aruco/dictionary.hpp>

#include <iostream>
#include <vector>

using namespace std;

int main()
{
        cv::Mat src = cv::imread("board2.JPG");
        cv::Mat srcCopy;
        src.copyTo(srcCopy);
        if (!src.data){
		std::cout << "?" << std::endl;
                return -1;
	}
	cv::namedWindow("src",cv::WINDOW_NORMAL);
	cv::namedWindow("binary",cv::WINDOW_NORMAL);
	cv::namedWindow("srcCopy",cv::WINDOW_NORMAL);   
	cv::imshow("src", src);

        // Create binary image from source image
        cv::Mat binaryImage;
        cv::cvtColor(src, binaryImage, CV_BGR2GRAY);
        cv::GaussianBlur(binaryImage,binaryImage,cv::Size(21,21),5);
	cv::adaptiveThreshold(binaryImage, binaryImage, 175, cv::ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 25, 0);
	//cv::threshold(binaryImage, binaryImage, 105,255,CV_THRESH_BINARY);
        cv::imshow("binary", binaryImage);

	std::vector<int> ids;
        std::vector<std::vector<cv::Point2f> > corners;
        
        cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_ARUCO_ORIGINAL);

        cv::aruco::detectMarkers(binaryImage, dictionary, corners, ids);
        cv::aruco::drawDetectedMarkers(srcCopy, corners, ids );    
        //CvDrawingUtils::draw3dCube(inputImageCopy,marker, TheCameraParameters);
        
        cout << ids.size() << endl;
        
        for( int i = 0; i < ids.size(); i++)
        	cout << ids[i] << " " << corners[i] << endl;  
       	
       	
       	//cout << corners[0][0] ;//corners[1] * corners[1] - corners[0] * corners[0] << endl;
        double res = cv::norm(corners[0][0] - corners[0][1] );	
        cout << res << " or " << res/5.0 << " pixels per cm" <<endl;
        cv::imshow("srcCopy", srcCopy);

        cv::waitKey(0);
        return 0;
}


