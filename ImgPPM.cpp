#include "ImgPPM.h"

ImgPPM::ImgPPM(const MyString& name, unsigned w, unsigned h): Img(name, w, h , States::color, "PPM")
{
}

Img* ImgPPM::Clone() const
{
	return new (std::nothrow)ImgPPM(*this);
}
