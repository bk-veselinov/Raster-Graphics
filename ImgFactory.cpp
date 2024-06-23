#include "ImgFactory.h"

const MyString& ImgFactory::getFileType(const MyString& img) const
{
	return img.SubString(img.getLength()-3);
}

Img* ImgFactory::createCollage(const MyString& name, const Img* img1, const Img* img2, bool isVertical)
{
	if (img1->GetImgType() != img2->GetImgType())
	{
		throw std::exception(("Cannot create collage with images with different types(" + img1->GetImgType() + " " + img2->GetImgType() + ")\n").c_str());
	}
	if (!img1->isSizeCompatableWith(img2))
	{
		throw std::exception("Images width and height does not match\n");
	}

	return new ImgCollage(name, img1, img2, isVertical);

}

Img* ImgFactory::createImg(const MyString& img) const
{
	MyString type = getFileType(img);
	unsigned w;
	unsigned h;
	std::ifstream in((char*)&w, std::ios::binary);
	std::ifstream in((char*)&h, std::ios::binary);
	if (type == "ppm")
	{
		return createPPM(img, w, h);
	}
	if (type == "pgm")
	{
		return createPGM(img, w, h);
	}
	if (type == "pbm")
	{
		return createPBM(img, w, h);
	}
	return nullptr;
}

Img* ImgFactory::createPPM(const MyString& img, unsigned w, unsigned h) const
{
	return new ImgPPM(img, w, h);

}

Img* ImgFactory::createPGM(const MyString& img, unsigned w, unsigned h) const
{
	return new ImgPGM(img, w, h);

}

Img* ImgFactory::createPBM(const MyString& img, unsigned w, unsigned h) const
{
	return new ImgPBM(img, w,h);
}
