#include "FeatureExtration.h"


FeatureExtration::FeatureExtration()
{
	this->Read_Config();
	this->Feature_Extration_Junction(*this->Image_Read(File_of_Extration_Path));
	this->Feature_Extration_Junction_Binarization();
	this->Image_Write(".\\data\\a_b_avg_rctheta.txt",save_file_path);
}


FeatureExtration::~FeatureExtration()
{
}

void FeatureExtration::Feature_Extration_Junction(Mat cvimage)
{

	ofstream out_1(".\\data\\r0ijr.txt");
	ofstream out_2(".\\data\\theta0.txt");
	ofstream out_3(".\\data\\c0ijr.txt");
	int m(cvimage.rows), n(cvimage.cols);
	float theta(0);
	float temp(0), temp_1(9999999), temp_theta(0), temp_3(0);
	MatrixXf *matrix = new MatrixXf(m, n);
	MatrixXf *r0ijr = new MatrixXf(m, n);
	MatrixXf *theta0 = new MatrixXf(m, n);
	MatrixXf *c0ijr = new MatrixXf(m, n);

	matrix = Mat_To_Matrix(cvimage);

	//for (int i = 0; i < m; ++i)
	//{
	//	for (int j = 0; j < n; ++j)
	//	{
	//		(*matrix)(i, j) = float(cvimage.at<unsigned char>(i, j));
	//	}
	//}




	for (int i = R / 2; i < m - R / 2; ++i)
	{
		for (int j = R / 2; j < n - R / 2; ++j)
		{
			for (theta = 0; theta < 180; theta+=STEP)
			{
				for (int k = -R / 2; k <= R / 2; ++k)
				{
					temp += (*matrix)((int)(i + k*cos(theta*PI / 180)), (int)(j + k*sin(theta*PI / 180)));

				}
				temp_3 += temp;
				if (temp < temp_1)
				{
					temp_1 = temp;
					temp_theta = theta;
				}
				temp = 0;
			}
			(*r0ijr)(i, j) = temp_1;
			(*theta0)(i, j) = temp_theta;
			(*c0ijr)(i, j) = fabs(temp_3 / (N/STEP) - temp_1);
			temp_1 = 9999999;
			temp_3 = 0;
		}
	}

	this->To_txt(out_1, r0ijr);
	this->To_txt(out_2, theta0);
	this->To_txt(out_3, c0ijr);


}

void FeatureExtration::To_txt(ofstream &out,MatrixXf *matrix)
{
	for (int i = 0; i < matrix->rows(); ++i)
	{
		for (int j = 0; j < matrix->cols(); j++)
		{
			if ((*matrix)(i, j)<-999999 || (*matrix)(i, j)>9999999)
			{
				out << 0 << " ";
				continue;
			}
			out << (*matrix)(i, j) << " ";
			
		}
		out << -1 << endl;
	}

}

void FeatureExtration::Feature_Extration_Junction_Binarization()
{
;   
	  
	ofstream out_1(".\\data\\avg_c0ijr.txt");
	ofstream out_2(".\\data\\avg_theta0.txt");
	ofstream out_3(".\\data\\avg_r0ijr.txt");
	ofstream out_B1(".\\data\\b_avg_c0ijr.txt");
	ofstream out_B2(".\\data\\b_avg_theta0.txt");
	ofstream out_B3(".\\data\\b_avg_r0ijr.txt");
	ofstream out_A_B(".\\data\\a_b_avg_rctheta.txt");

	Mat *r0ijr = Image_Write(".\\data\\r0ijr.txt",save_file_path);
	Mat *c0ijr = Image_Write(".\\data\\c0ijr.txt",save_file_path);
	Mat *theta0 = Image_Write(".\\data\\theta0.txt",save_file_path);
	MatrixXf *avg_r0ijr = new MatrixXf(r0ijr->rows, r0ijr->cols);
	MatrixXf *avg_c0ijr = new MatrixXf(c0ijr->rows, c0ijr->cols); //build new dynamic array
	MatrixXf *avg_theta0 = new MatrixXf(theta0->rows, theta0->cols);
	MatrixXf *b_avg_r0ijr = new MatrixXf(r0ijr->rows, r0ijr->cols);
	MatrixXf *b_avg_c0ijr = new MatrixXf(c0ijr->rows, c0ijr->cols); //build new dynamic array
	MatrixXf *b_avg_theta0 = new MatrixXf(theta0->rows, theta0->cols);
	MatrixXf *a_b_rctheta = new MatrixXf(theta0->rows, theta0->cols);

	avg_r0ijr->setZero();  //set zero
	avg_c0ijr->setZero();
	avg_theta0->setZero();
	b_avg_r0ijr->setZero();  
	b_avg_c0ijr->setZero();
	b_avg_theta0->setZero();
	a_b_rctheta->setZero();

	avg_theta0 = this->Mat_Avg(*theta0, MM, NN);  
	avg_c0ijr = this->Mat_Avg(*c0ijr, MM, NN);
	avg_r0ijr = this->Mat_Avg(*r0ijr, MM, NN);
	b_avg_theta0 = this->FEJ_Binarization_Compare(*theta0, *avg_theta0,TH1,0);
	b_avg_r0ijr = this->FEJ_Binarization_Compare(*r0ijr, *avg_r0ijr, TH2, 1);
	b_avg_c0ijr = this->FEJ_Binarization_Compare(*c0ijr, *avg_c0ijr,TH3,1);

	a_b_rctheta = this->FEJB_And(*b_avg_c0ijr, *b_avg_r0ijr, *b_avg_theta0);

	this->To_txt(out_1, avg_c0ijr); //output to txt document
	this->To_txt(out_2, avg_theta0);
	this->To_txt(out_3, avg_r0ijr);
	this->To_txt(out_B1, b_avg_c0ijr); //output to txt document
	this->To_txt(out_B2, b_avg_theta0);
	this->To_txt(out_B3, b_avg_r0ijr);
	this->To_txt(out_A_B, a_b_rctheta);


}
MatrixXf * FeatureExtration::FEJ_Binarization_Compare(const Mat &mat, const MatrixXf &matrix,float TH,int flags)
{
	MatrixXf *matrix_temp = new MatrixXf(mat.rows, mat.cols);
	int rows(mat.rows), cols(mat.cols);
	if (flags==0)
	{
		for (int i(0); i != rows; ++i)
		{
			for (int j(0); j != cols; ++j)
			{

				if (fabs(mat.at<unsigned char>(i, j) - matrix(i, j)) > TH)				
					(*matrix_temp)(i, j) = 1;				
			}
		}
	}
	else
	{
		for (int i(0); i != rows; ++i)
		{
			for (int j(0); j != cols; ++j)
			{

				if (fabs(mat.at<unsigned char>(i, j)/matrix(i, j)) < TH)
					(*matrix_temp)(i, j) = 1;
			}
		}

	}
	return matrix_temp;

}

MatrixXf * FeatureExtration::FEJB_And(const MatrixXf &matrix_1, const MatrixXf &matrix_2, const MatrixXf &matrix_3)
{
	int rows(matrix_1.rows()), cols(matrix_1.cols());
	MatrixXf *matrix_temp = new MatrixXf(matrix_1.rows(), matrix_1.cols());
	for (int i(0); i != rows;++i)
	{
		for (int j(0); j != cols;++j)
		{
			if (matrix_1(i,j)==1&&matrix_2(i,j)==1&&matrix_3(i,j)==1)
			{
				(*matrix_temp)(i, j) = 250;
			}
		}
	}
	return matrix_temp;
}
MatrixXf * FeatureExtration::Mat_Avg(const Mat &mat, int M, int N) //compute average pixel of 
{                                                                //a rectangular with size of (2M+1)(2N+1)
	float temp(0);
	MatrixXf *temp_matrix = new MatrixXf(mat.rows,mat.cols);
	temp_matrix->setZero();
	int rows(mat.rows - M-1);
	int cols(mat.cols - N-1);
	try
	{
		for (int i(M); i != rows; ++i)
		{
			for (int j(N); j != cols; ++j)
			{
				for (int l(i - M); l != i + M + 1; ++l)
				{
					for (int k(j - N); k != j + N + 1; ++k)
					{
						temp += mat.at<unsigned char>(l, k);
					}
				}
				temp = temp / ((2 * M + 1)*(2 * N + 1));
				(*temp_matrix)(i, j) = temp;
				temp = 0;
			}
		}
		return temp_matrix;
	}
	catch (...)
	{
		printf("Avg_Mat Exception\n");
	}
}

void FeatureExtration::Read_Config()
{
	string temp;

	ifstream infile(".\\config\\featu_extra_config.txt", ios::in);
	infile >> temp;
	infile >> temp;
	this->R = atoi(temp.c_str());
	infile >> temp;
	infile >> temp;
	this->STEP = atoi(temp.c_str());
	infile >> temp;
	infile >> temp;
	this->TH1 = atof(temp.c_str());
	this->TH1 -= this->R / 5;
	infile >> temp;
	infile >> temp;
	this->TH2 = atof(temp.c_str());
	infile >> temp;
	infile >> temp;
	this->TH3 = atof(temp.c_str());
	infile >> temp;
	infile >> temp;
	this->MM = atoi(temp.c_str());
	infile >> temp;
	infile >> temp;
	this->NN = atoi(temp.c_str());
	infile >> temp;
	infile >> temp;
	File_of_Extration_Path = temp;
	infile >> temp;
	infile >> temp;
	save_file_path = temp;

	
}