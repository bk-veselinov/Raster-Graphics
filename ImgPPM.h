#pragma once
#include "Img.h"
class ImgPPM :
    public Img
{
public:
    ImgPPM(const MyString& name, unsigned w, unsigned h);
    Img* Clone()const override;
};

