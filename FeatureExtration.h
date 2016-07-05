#ifndef FEATUREEXTRATION_H
#define FEATUREEXTRATION_H

#if _MSC_VER >= 1600  
#pragma execution_character_set("utf-8") 
#endif
#define PI 3.1415926

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <Eigen>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>

#include "ImageRead.h"

using namespace std;
using namespace cv;
using namespace Eigen;


#pragma comment(lib, "Shell32.lib")

class FeatureExtration:public ImageRead
{
public:
	FeatureExtration();
	~FeatureExtration();
	void Feature_Extration_Junction(Mat mat);
	void Feature_Extration_Junction_Binarization();
	MatrixXf * FEJ_Binarization_Compare(const Mat &mat,const MatrixXf &matrix, float TH,int flags);
	MatrixXf * FEJB_And(const MatrixXf &matrix_1, const MatrixXf &matrix_2, const MatrixXf &matrix_3);
	void To_txt(ofstream &out,MatrixXf *matrix);
	void Read_Config();
	MatrixXf * Mat_Avg(const Mat &mat, int M, int N);
	int R = 10;
	int N = 180;
	float STEP = 3, TH1 = 12, TH2 = 0.92, TH3 = 0.92; // theta step and threshold
	int MM = 3, NN = 3;   // area of (2M+1)*(2N+1) pixel
	string File_of_Extration_Path;
	string save_file_path;

};

#endif //FEATUREEXTRATION_H