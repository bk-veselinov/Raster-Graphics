#include "ImgCollage.h"

ImgCollage::ImgCollage(const MyString& name, const Img* _img1, const Img* _img2, bool isVertical):img1(_img1->Clone()), img2(_img2->Clone())
{
	SetName(name);
	//MUST check rotations

	if (isVertical)
	{
		SetWidth(img1->GetWidth());
		SetHeight(img1->GetHeight() * 2);
	}
	else
	{
		SetWidth(img1->GetWidth() * 2);
		SetHeight(img1->GetHeight());
	}
	fileType = img1->GetImgType();
	currState = _img1->GetState();
	
}
