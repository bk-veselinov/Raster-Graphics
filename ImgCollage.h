#pragma once
#include "Img.h"
#include "polymorphic_ptr.hpp"
class ImgCollage :
    public Img
{
    polymorphic_ptr<Img> img1;
    polymorphic_ptr<Img> img2;
public:
    ImgCollage(const MyString& name, const Img* img1, const Img* img2,  bool isVertical);
    Img* Clone()const override;
};

