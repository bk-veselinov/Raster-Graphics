#include "ImgPPM.h"

ImgPPM::ImgPPM(const MyString& name, unsigned w, unsigned h): Img(name, w, h , States::color, "PPM")
{
}

Img* ImgPPM::Clone() const
{
	if (rotationsCount % 2 == 0)
	{
		return new (std::nothrow)ImgPPM(name, width, height);
	}
	return new (std::nothrow)ImgPPM(name, height, width);
}
