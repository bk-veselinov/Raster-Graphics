#include "ImgPGM.h"

ImgPGM::ImgPGM(const MyString& name, unsigned w, unsigned h) : Img(name, w, h, States::grayscale, "PGM")
{
}

Img* ImgPGM::Clone() const
{
	return new (std::nothrow)ImgPGM(*this);

}
