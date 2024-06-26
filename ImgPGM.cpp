#include "ImgPGM.h"

ImgPGM::ImgPGM(const MyString& name, unsigned w, unsigned h) : Img(name, w, h, States::grayscale, "PGM")
{
}

Img* ImgPGM::Clone() const
{
	if (rotationsCount % 2 == 0)
	{
		return new (std::nothrow)ImgPGM(name, width, height);
	}
	return new (std::nothrow)ImgPGM(name, height, width);

}
