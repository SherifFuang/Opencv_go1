////图像卷积操作
//图像卷积可以看成是一个窗口区域在另外一个大的图像上移动，对每个窗口覆盖的区域都进行点乘得到的值作为中心像素点的输出值。窗口的移动是从左到右，
//从上到下。窗口可以理解成一个指定大小的二维矩阵，里面有预先指定的值。
//
//相关API（C++）
//- blur(
//	InputArray 	src, // 输入
//	OutputArray 	dst, 输出
//	Size 	ksize, // 窗口大小
//	Point 	anchor = Point(-1, -1), // 默认值
//	int 	borderType = BORDER_DEFAULT // 默认值
//)
//Python版本
//dst = cv.blur(src, ksize[, dst[, anchor[, borderType]]])

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat src = imread("D:/vcprojects/images/lena.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	int h = src.rows;
	int w = src.cols;

	// 3x3 均值模糊，自定义版本实现
	Mat dst = src.clone();
	for (int row = 1; row < h-1; row++) {
		for (int col = 1; col < w-1; col++) {
			Vec3b p1 = src.at<Vec3b>(row-1, col-1);
			Vec3b p2 = src.at<Vec3b>(row-1, col);
			Vec3b p3 = src.at<Vec3b>(row-1, col+1);
			Vec3b p4 = src.at<Vec3b>(row, col-1);
			Vec3b p5 = src.at<Vec3b>(row, col);
			Vec3b p6 = src.at<Vec3b>(row, col+1);
			Vec3b p7 = src.at<Vec3b>(row+1, col-1);
			Vec3b p8 = src.at<Vec3b>(row+1, col);
			Vec3b p9 = src.at<Vec3b>(row+1, col+1);

			int b = p1[0] + p2[0] + p3[0] + p4[0] + p5[0] + p6[0] + p7[0] + p8[0] + p9[0];
			int g = p1[1] + p2[1] + p3[1] + p4[1] + p5[1] + p6[1] + p7[1] + p8[1] + p9[1];
			int r = p1[2] + p2[2] + p3[2] + p4[2] + p5[2] + p6[2] + p7[2] + p8[2] + p9[2];

			dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b / 9);
			dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g / 9);
			dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r / 9);
		}
	}
	imshow("blur", dst);
	imwrite("D:/result.png", dst);

	// OpenCV 均值模糊
	Mat result;
	blur(src, result, Size(15, 15), Point(-1, -1), 4);
	imshow("result", result);

	waitKey(0);
	return 0;
}