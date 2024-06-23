#pragma once
#include "polymorphic_container.hpp"
#include "Img.h"
#include "MyString.h"
#include "ImgCollage.h"

const Modifications& stringToModiification(const MyString& str) {
	if (str=="rotation left")
	{
		return Modifications::rotationLeft;
	}
	if (str == "rotation right")
	{
		return Modifications::rotationRight;
	}
	if (str == "monochrome")
	{
		return Modifications::monochrome;
	}
	if (str == "grayscale")
	{
		return Modifications::grayscale;
	}
	if (str == "negative")
	{
		return Modifications::negative;
	}
}

class Session
{
	//TODO add collage direction
	//print
	//add close command
	int id = -1;
	polymorphic_container<Img> images;
	MyStack<Modifications, MAX_MODIFICATIONS_STACK_COUNT> modifications;

	void undoAcctionForImages(const Modifications& mod);
	void addModificationToImages(const Modifications& mod);
	void saveAllImgs(bool isSaveas, const MyString = "");
	int getImgIdx(const MyString& name) const;
	void printImagesNames()const;
	void printModifications()const;
public:
	int GetId()const;
	Session(unsigned id,  Img** const img, size_t imgCount);
	Session(unsigned id);
	const polymorphic_container<Img>& GetImages()const;
	void createCollage(Img* collage, const MyString& img1, const MyString& img2);
	void addImg( Img* newImg);
	void addModification(const Modifications& mod);
	void printInfo()const;
	void undo();
	void save();
	void saveAs(const MyString& newFileName);
	void close();
};

