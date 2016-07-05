#include "MorphologicalFilter.h"


MorphologicalFilter::MorphologicalFilter()
{
	this->Read_config();
	this->Image_Erode();
}


MorphologicalFilter::~MorphologicalFilter()
{
}
void MorphologicalFilter::Read_config()
{
	string temp;
	ifstream infile(".\\config\\morphological_filter_config.txt", ios::in);
	infile >> temp;
	infile >> temp;
	this->image_path = temp;
	infile >> temp;
	infile >> temp;
	this->save_file_path = temp;
	infile >> temp;
	infile >> temp;
	this->shape = atoi(temp.c_str());
	infile >> temp;
	infile >> temp;
	this->size = atoi(temp.c_str());

}
Mat * MorphologicalFilter::Image_Erode()
{

	Mat *mat = this->Image_Read(image_path);
	Mat *temp_mat = new Mat();
	temp_mat->create(mat->rows, mat->cols, CV_8UC1);
	//Mat element1(2, 2, CV_8U, Scalar(1));
	//Mat element2(3, 3, CV_8U, Scalar(1));
	Mat *element1 = new Mat();
	Mat *element2 = new Mat();
	*element1 = getStructuringElement(this->shape, Size(this->size, this->size));
	*element2 = getStructuringElement(this->shape, Size(this->size, this->size));
	dilate(*mat, *temp_mat, *element1);
	erode(*temp_mat, *mat,*element2);
	imwrite(save_file_path, *mat);
	return mat;
}