#pragma once
#include "Img.h"

class ImgPGM:
	public Img
{
public:
	ImgPGM(const MyString& name, unsigned w, unsigned h);
	Img* Clone()const override;

};

