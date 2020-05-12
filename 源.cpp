#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int cnt = 1;
int num = 1;
char   temp_file[5];
string filename;
string path;
int main()
{
	vector<Mat> subImages;  //等分后的各子图
	int subImageNum = 3;    // 给原图分9块
	Mat src;
	src = imread("./test1.jpg", -1);
	imshow("123", src);
	waitKey(0);
	subImages.clear();
	int srcHeight, srcWidth, subHeight, subWidth;
	srcHeight = src.rows;  
	srcWidth = src.cols;
	subHeight = srcHeight / subImageNum;
	subWidth = srcWidth / subImageNum;
	for (int j = 0; j < subImageNum; j++)

	{
		for (int i = 0; i < subImageNum; i++)
		{
			if (j < subImageNum - 1 && i < subImageNum - 1) {
				cv::Mat temImage(subHeight, subWidth, CV_8UC3, cv::Scalar(0, 0, 0));
				cv::Mat imageROI = src(cv::Rect(i * subWidth, j * subHeight, temImage.cols, temImage.rows));
				cv::addWeighted(temImage, 1.0, imageROI, 1.0, 0., temImage);
				subImages.push_back(temImage);
			}
			else {
				cv::Mat temImage(srcHeight - (subImageNum - 1) * subHeight, srcWidth - (subImageNum - 1) * subWidth, CV_8UC3, cv::Scalar(0, 0, 0));
				cv::Mat imageROI = src(cv::Rect(i * subWidth, j * subHeight, temImage.cols, temImage.rows));
				cv::addWeighted(temImage, 1.0, imageROI, 1.0, 0., temImage);
				subImages.push_back(temImage);
			}
		}
		std::cout << subImages[0] << std::endl;   //测试语句，打印出子图矩阵	
		int n = 0;
		vector<Mat>::iterator it = subImages.begin();
		while (it != subImages.end())
		{
			Mat tmp = *it;
			stringstream ss;
			ss << n;
			n++;
			imwrite(ss.str() + ".jpg", tmp);
			it++;
			waitKey(10);
		}	
	}
	system("pause");
	return 0;
}