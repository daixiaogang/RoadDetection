#include "ImagetoTxt.h"


ImagetoTxt::ImagetoTxt()
{
	this->Read_Config();
	mat = this->Image_Read(file_name);
	this->mat_to_txt();
	
}


ImagetoTxt::~ImagetoTxt()
{

}
void ImagetoTxt::Read_Config()
{
	try
	{
		string temp;
		ifstream infile(".\\config\\imagetotxt_config.txt", ios::in);
		infile >> temp;
		infile >> temp;
		this->file_name = temp;
		infile >> temp;
		infile >> temp;
		this->write_txt = temp;
	}
	catch (...)
	{
		cout << "ImagetoTxt Read_Config Exception" << endl;
		return;
	}
	
}
void ImagetoTxt::mat_to_txt()
{
	try
	{
		ofstream out_stream(write_txt);
		for (int i(0); i != mat->rows; ++i)
		{
			for (int j(0); j != mat->cols; ++j)
			{
				out_stream << (int)(*mat).at<unsigned char>(i, j) << " ";
			}
			out_stream << endl;
		}
	}
	catch (...)
	{
		cout << "ImagetoTxt mat_to_txt Exception" << endl;
		return;
	}
}
