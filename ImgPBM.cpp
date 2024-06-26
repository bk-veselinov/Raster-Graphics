#include "ImgPBM.h"

ImgPBM::ImgPBM(const MyString& name, unsigned w, unsigned h) : Img(name, w, h, States::monochrome, "PBM")
{
}

Img* ImgPBM::Clone() const
{
	if (rotationsCount%2==0)
	{
		return new (std::nothrow)ImgPBM(name, width, height);
	}
	return new (std::nothrow)ImgPBM(name, height, width);

}
