#ifndef IMAGEREAD_H
#define IMAGEREAD_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <Eigen>
#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace cv;
using namespace Eigen;

class ImageRead
{
public:
	ImageRead();
	~ImageRead();
	Mat * Image_Read(const string &filename);  //��ȡͼƬ��mat_read
	Mat * Image_Write(const string &filename,const string &savepath);  //��txt�ĵ���д��bmpͼƬ
	Mat * Matrix_To_Mat(const MatrixXf &matrix);
	MatrixXf * Mat_To_Matrix(const Mat &mat);
private:
	Mat *mat_read;
	Mat *mat;
	MatrixXf *matrix;
};
#endif // !IMAGEREAD_H

