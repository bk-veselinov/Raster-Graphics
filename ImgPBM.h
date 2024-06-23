#pragma once
#include "Img.h"
class ImgPBM :
    public Img
{
public:
    ImgPBM(const MyString& name, unsigned w, unsigned h);
    Img* Clone()const override;

};

