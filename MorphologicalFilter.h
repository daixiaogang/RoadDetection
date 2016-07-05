#ifndef MORPHOLOGICALFILTER
#define MORPHOLOGICALFILTER

#include "ImageRead.h"

class MorphologicalFilter:public ImageRead
{
public:
	MorphologicalFilter();
	~MorphologicalFilter();
	Mat * Image_Erode();
	void Read_config();

private:
	string image_path;
	string save_file_path;
	int shape;
	int size;
	
};

#endif //MORPHOLOGICALFILTER
