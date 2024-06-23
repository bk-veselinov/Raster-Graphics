#pragma once
#include "Session.h"
#include "ImgFactory.h"
class System
{
	size_t idGenerator = 0;
	// vector does not work must allow holes
	//add Factory
	//check if it has active session
	//add logger
	Vector<Session> sessions;
	polymorphic_container<Img> images;
	int activeSession = -1;
	ImgFactory factory;
	const Img* readImg()const;
	int findImg(const MyString& name);
public:
	void run();
	void load();
	void add();
	void help()const;
	void save();
	void saveAs();
	void close();
	void sessinInfo() const;
	void switchSession();
	void createCollage();
	void grayscale();
	void monochrome();
	void negative();
	void rotate();
	void undo();

};

