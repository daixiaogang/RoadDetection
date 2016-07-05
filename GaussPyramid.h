#ifndef GAUSSPYRAMID_h
#define GAUSSPYRAMID_h


#include "ImageRead.h"

class GaussPyramid:public ImageRead
{
public:
	GaussPyramid();
	~GaussPyramid();
	Mat * Pyramid_Reduce_Expand(const Mat &mat,int flags);//flags==0 reduce
	vector<Mat *> * Pyramid_Reduce_Expand_Build(Mat *mat,int layer,int flags);
	void Pyramid_Image_Save(vector<Mat *> *vec);
	string File_Name;
	int Layer_of_Pyramid;
	int Flags_Reduce_Expand;
	void Read_Config();
};
#endif   //GAUSSPYRAMID_h