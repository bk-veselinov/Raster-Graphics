#pragma once
#include "Session.h"
#include "ImgFactory.h"
#include <sstream>
constexpr unsigned BUFFER_SIZE = 1024;

class System
{
	size_t idGenerator = 0;
	Vector<Session> sessions;
	polymorphic_container<Img> images;
	int activeSession = -1;
	ImgFactory factory;
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

