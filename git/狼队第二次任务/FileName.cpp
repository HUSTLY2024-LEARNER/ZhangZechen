#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
#include <opencv2/opencv.hpp>
void RGB2HSV(cv::Mat img_rgb, cv::Mat& img_hsv) {
    img_hsv = cv::Mat::zeros(img_rgb.size(), CV_8UC3);

    for (int i = 0; i < img_rgb.rows; i++) {
        for (int j = 0; j < img_rgb.cols; j++) {
            cv::Vec3b rgb = img_rgb.at<cv::Vec3b>(i, j);

            float B = rgb[0] / 255.0;
            float G = rgb[1] / 255.0;
            float R = rgb[2] / 255.0;

            float V = std::max({ B, G, R });
            float vmin = std::min({ B, G, R });
            float diff = V - vmin;

            float S, H;
            S = diff / (V + FLT_EPSILON);
            diff = 60.0 / (diff + FLT_EPSILON);

            if (V == B)
                H = 240.0 + (R - G) * diff;
            else if (V == G)
                H = 120.0 + (B - R) * diff;
            else if (V == R)
                H = (G - B) * diff;

            H = (H < 0.0) ? (H + 360.0) : H;

            cv::Vec3b hsv;
            hsv[0] = H / 2;
            hsv[1] = S * 255;
            hsv[2] = V * 255;

            img_hsv.at<cv::Vec3b>(i, j) = hsv;
        }
    }
}
int main() {
    cv::Mat colorImage = cv::imread("C:\\Users\\liu-yun\\Pictures\\Screenshots\\R-C.png");
    // 将彩色图像转换为灰度图像
    cv::Mat grayImage(colorImage.rows, colorImage.cols, CV_8UC1);
    for (int i = 0; i < colorImage.rows; i++) {
        for (int j = 0; j < colorImage.cols; j++) {
            // 获取bgr三个通道的像素值
            int blue = colorImage.at<cv::Vec3b>(i, j)[0];
            int green = colorImage.at<cv::Vec3b>(i, j)[1];
            int red = colorImage.at<cv::Vec3b>(i, j)[2];

            // 根据公式将彩色像素转换为灰度像素
            int gray = 0.299 * red + 0.587 * green + 0.114 * blue;

            // 将灰度像素值写入灰度图像
            grayImage.at<uchar>(i, j) = gray;
        }
    }
    // 将彩色图像转换为HSV图像
    cv::Mat hsvImage;
    RGB2HSV(colorImage, hsvImage);
    cv::namedWindow("Color Image", cv::WINDOW_FREERATIO);
    cv::namedWindow("Gray Image", cv::WINDOW_FREERATIO);
    cv::namedWindow("HSV Image", cv::WINDOW_FREERATIO);
    cv::imshow("Color Image", colorImage);
    cv::imshow("Gray Image", grayImage);
    cv::imshow("HSV Image", hsvImage);
    cv::waitKey(0);

    return 0;
}
