#include "ImgPBM.h"

ImgPBM::ImgPBM(const MyString& name, unsigned w, unsigned h) : Img(name, w, h, States::monochrome, "PBM")
{
}

Img* ImgPBM::Clone() const
{
	return new (std::nothrow)ImgPBM(*this);
}
