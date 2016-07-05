#include "ImageRead.h"

ImageRead::ImageRead()
{
}


ImageRead::~ImageRead()
{
	
}

Mat * ImageRead::Image_Read(const string &filename)
{
    mat_read = new Mat();
	try
	{
		*mat_read = imread(filename, 0);//".\\imagedata\\image_read.bmp"
		return mat_read;
	}
	catch (...)
	{
		cout << "Image Read Exception\n" << endl;
	}
  
	
}


Mat * ImageRead::Image_Write(const string &filename,const string &savepath)
{ 

	int temp(0), i(0), j(0),k(0);
	
	string temp_1;
	ifstream infile(filename,ios::in);

	try{
		while (!infile.eof())
		{
			infile >> temp_1;
			temp = atoi(temp_1.c_str());
			if (temp == -1)
			{
				++i;
				if (k < j) k = j;
				j = 0;
				continue;
			}
			else
			{
				++j;
			}
		}
		infile.close();
		infile.clear();
		infile.open(filename, ios::in);
		Mat *image_write = new Mat();
		image_write->create(i - 1, k, CV_8UC1);
		i = 0;
		j = 0;

		while (!infile.eof())
		{
			infile >> temp_1;
			temp = atoi(temp_1.c_str());

			if (temp == -1)
			{
				++i;
				j = 0;
				continue;
			}
			else
			{
				image_write->at<unsigned char>(i, j) = temp;
				++j;
			}
		}
		imwrite(savepath, *image_write);//".\\imagedata\\image_write.bmp"
		return image_write;
	}
	catch (...)
	{
		printf("Image Write Exception");
	}
}

Mat * ImageRead::Matrix_To_Mat(const MatrixXf &matrix)
{
	try
	{
		mat = new Mat();
		mat->create(matrix.rows(), matrix.cols(), CV_8UC1);
		int rows(matrix.rows());
		int cols(matrix.cols());
		for (int i(0); i != rows; ++i)
		{
			for (int j(0); j != cols; ++j)
			{
				mat->at<unsigned char>(i, j) = matrix(i, j);
			}
		}
		return mat;
	}
	catch (...)
	{
		cout << "ImageRead::Matrix_To_Mat Exception" << endl;
	}

	
}

MatrixXf * ImageRead::Mat_To_Matrix(const Mat &mat)
{
	try
	{
		matrix = new MatrixXf(mat.rows, mat.cols);
		int rows(mat.rows);
		int cols(mat.cols);
		for (int i(0); i != rows; ++i)
		{
			for (int j(0); j != cols; ++j)
			{
				(*matrix)(i, j) = (float)mat.at<unsigned char>(i, j);
			}
		}
		return matrix;
	}
	catch (...)
	{
		cout << "ImageRead::Mat_To_Matrix Exception" << endl;
	}

}