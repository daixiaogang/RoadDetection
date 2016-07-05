#include "GaussPyramid.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

GaussPyramid::GaussPyramid()
{
	this->Read_Config();
	Mat *mat = (this->Image_Read(this->File_Name));
	//gausspyramid.Pyramid_Reduce_Expand(*mat,0);
	vector<Mat *> *vec;
	vec = this->Pyramid_Reduce_Expand_Build(mat, this->Layer_of_Pyramid, this->Flags_Reduce_Expand);
	this->Pyramid_Image_Save(vec);
}


GaussPyramid::~GaussPyramid()
{
}

Mat * GaussPyramid::Pyramid_Reduce_Expand(const Mat &mat, int flags)
{
	Mat *temp_mat=new Mat();
	if (flags==0)
	{
	//temp_mat.create((mat.rows+1)/2, (mat.cols+1)/2, CV_8UC1);
	pyrDown(mat, *temp_mat, Size((mat.cols+1) / 2, (mat.rows+1) / 2));
	return temp_mat;
	}
	else
	{
		//temp_mat.create(mat.rows * 2, mat.cols  * 2, CV_8UC1);
		pyrUp(mat, *temp_mat, Size(mat.cols * 2, mat.rows * 2));
	
		return temp_mat;
	}
	
}

vector<Mat *> * GaussPyramid::Pyramid_Reduce_Expand_Build(Mat *mat,int layer,int flags)
{
	vector<Mat *> *vec=new vector<Mat *>;
	(*vec).push_back(mat);
	Mat *temp_1 = new Mat();
	Mat *temp_2 = new Mat();
	temp_1 = mat;
	if (flags==0)
	{
		for (int i(0); i != layer; ++i)
		{
			temp_2 = this->Pyramid_Reduce_Expand(*temp_1, 0);
			(*vec).push_back(temp_2);
			temp_1 = temp_2;
		}
	}
	else
	{
		for (int i(0); i != layer; ++i)
		{
			temp_2 = this->Pyramid_Reduce_Expand(*temp_1, 1);
			(*vec).push_back(temp_2);
			temp_1 = temp_2;
		}
	}


	return vec;

}              //the use of return vector
	// vec = gausspyramid.Pyramid_Reduce_Expand_Build(mat, 5, 0);

	//    for (iter = (*vec).begin(); iter != (*vec).end(); ++iter)
	 // {
	//         imshow("aaa", **iter);
	//         waitKey(0);
	// }
void GaussPyramid::Pyramid_Image_Save(vector<Mat *> *vec)
{
	vector<Mat *>::iterator iter;
	stringstream ss;
	int i(0);
	
	for (iter = (*vec).begin(); iter != (*vec).end();++iter,++i)
	{
		ss << i;
		imwrite(".\\imagedata\\PyramidImage\\Image" + ss.str()+".bmp", **iter);
	}
}

void GaussPyramid::Read_Config()
{
	string temp;

	ifstream infile(".\\config\\gauss_pyramid_config.txt", ios::in);
	infile >> temp;
	infile >> temp;
	this->File_Name = temp;
	infile >> temp;
	infile >> temp;
	this->Layer_of_Pyramid = atoi(temp.c_str());
	infile >> temp;
	infile >> temp;
	this->Flags_Reduce_Expand = atoi(temp.c_str());
	
}