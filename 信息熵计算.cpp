//读取图片并显示
#include<cstdio>
#include<iostream> 
#include<fstream>
# include "time.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

double solve2(string s) {
	Mat img = imread(s);
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	img.convertTo(img, CV_64F);
	cv::Mat imgEntropyMap = cv::Mat::zeros(256, 256, CV_64F);// 256 * 256 entropy map
	//calculate the mean value of K=8 neighborhood
	cv::Mat meanKernal(3, 3, CV_16S);
	short mean[]{ 1,1,1,
				1,0,1,
				1,1,1 };
	meanKernal.data = (unsigned char*)mean;
	cv::Mat meanMap;
	cv::filter2D(img, meanMap, -1, meanKernal, cv::Point(-1, -1), 0.0, cv::BORDER_REFLECT_101);
	meanMap /= 8;

	//calculate the (intensity, mean intensity of the K=8 neighborhood) two-tuples of the image
	img.convertTo(img, CV_8UC1);
	meanMap.convertTo(meanMap, CV_8UC1);
	for (int i=0; i < meanMap.rows; ++i)
		for (int j=0; j < meanMap.cols; ++j) {
			imgEntropyMap.at<double>(img.at<uchar>(i, j), meanMap.at<uchar>(i, j))++;
		}
	//calculate the two dimensional entropy of the image
	 int S = (int)img.rows * img.cols;
	imgEntropyMap /= (S);
	cv::Mat logMap;
	cv::log(imgEntropyMap + 1e-7, logMap);//add delta=1e-7 to avoid overflow
	imgEntropyMap = imgEntropyMap.mul(logMap);
	double ans = -cv::sum(imgEntropyMap)[0];
	return ans;
}
string o0 = "C:\\Users\\Mr_cold\\Desktop\\less\\";
string o1 = "C:\\Users\\Mr_cold\\Desktop\\normal\\";
int num = 0;
void OUT(string s, int flag) {
	Mat img = imread(s);
	num++;
   if(flag==0)imwrite(o0+ to_string(num)+".jpg", img);
	else imwrite(o1 + to_string(num) + ".jpg", img);
}
string o10 = "C:\\Users\\Mr_cold\\Desktop\\less_1\\";
string o11 = "C:\\Users\\Mr_cold\\Desktop\\normal_1\\";
int num1 = 0;
void OUT1(string s, int flag) {
	Mat img = imread(s);
	num1++;
	if (flag == 0)imwrite(o10 + to_string(num1) + ".jpg", img);
	else imwrite(o11 + to_string(num1) + ".jpg", img);
}

double solve1(string s) {
	Mat img = imread(s);
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	vector<double>cnt(256);
	img.convertTo(img, CV_8UC1);
	for (int i = 0; i < img.rows; ++i)
		for (int j = 0; j < img.cols; ++j) {
			cnt[img.at<uchar>(i, j)] += 1;
		}
	//calculate the two dimensional entropy of the image
	int S = (int)img.rows * img.cols;
	double sum = 0;
	for (auto x : cnt) {
		x += 1e-7;
		x /= S;
		x = x * log(1/x);
		sum += x;
	}
	return sum;
}
string o20 = "C:\\Users\\Mr_cold\\Desktop\\less_2\\";
string o21 = "C:\\Users\\Mr_cold\\Desktop\\normal_2\\";
int num2 = 0;
void OUT2(string s, int flag) {
	Mat img = imread(s);
	num2++;
	if (flag == 0)imwrite(o20 + to_string(num2) + ".jpg", img);
	else imwrite(o21 + to_string(num2) + ".jpg", img);
}
int main(){
	clock_t start_time, end_time;
	start_time = clock();   //获取开始执行时间

	ifstream fin("C:\\Users\\Mr_cold\\Desktop\\in.txt");
	string s;
	while (fin>>s) {
		double tmp=solve2(s);
		cout << tmp << endl;

		double tep = solve1(s);
		cout << tep << endl;
		
		if (tmp >= 2.35 && tep >= 2.0) OUT2(s, 1);
		else if (tmp >= 2.2 && tep >= 2.1) OUT2(s, 1);
		else OUT2(s, 0);
		cout << endl;
	}
	end_time = clock();     //获取结束时间
	float Times = (end_time - start_time) / CLOCKS_PER_SEC;
	printf("%f seconds\n", Times);
}