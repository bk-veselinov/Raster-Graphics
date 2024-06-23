#pragma once
#include "polymorphic_container.hpp"
#include "Img.h"
#include "MyString.h"
#include "ImgCollage.h"

const Modifications& stringToModiification(const char* str) {
	if (strcmp(str, "rotation")==0)
	{
		return Modifications::rotation;
	}
	if (strcmp(str, "monochrome") == 0)
	{
		return Modifications::monochrome;
	}
	if (strcmp(str, "grayscale") == 0)
	{
		return Modifications::grayscale;
	}
	if (strcmp(str, "negative") == 0)
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
	Session(unsigned id,  Img** const img, size_t imgCount);

	void createCollage(const MyString& name, const MyString& img1, const MyString& img2, bool isVertical);
	void addImg( Img* newImg);
	void addModification(const Modifications& mod);
	void printInfo()const;
	void undo();
	void save();
	void saveAs(const MyString& newFileName);
	void close();
};

