#pragma once
#include "Img.h"
#include "ImgPBM.h"
#include "ImgPGM.h"
#include "ImgPPM.h"
#include "ImgCollage.h"
#include <fstream>
class ImgFactory
{
	//string view or string stream
	//it is possible to have . in the name
	const MyString getFileType(const MyString& img)const;
public:
	Img* createCollage(const MyString& name, const Img* img1, const Img* img2, bool isVertical);
	Img* createImg(const MyString& img)const;
	Img* createPPM(const MyString& img, unsigned w, unsigned h)const;
	Img* createPGM(const MyString& img, unsigned w, unsigned h)const;
	Img* createPBM(const MyString& img, unsigned w, unsigned h)const;
};

