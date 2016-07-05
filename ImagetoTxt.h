#ifndef IMAGETOTXT
#define IMAGETOTXT

#include "ImageRead.h"

class ImagetoTxt:public ImageRead
{
public:
	ImagetoTxt();
	~ImagetoTxt();
	
private:
	Mat *mat;
	string file_name;
	string write_txt;
	void Read_Config();
	void mat_to_txt();
};

#endif   //IMAGETOTXT