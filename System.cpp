#include "System.h"


int System::findImg(const MyString& name)
{
	for (size_t i = 0; i < images.getPtrsCount(); i++)
	{
		//std::cout << images[i].GetName()<<"\n";

		if (name == images[i].GetName())
		{
			return i;
		}
	}
	return -1;
}

void System::run()
{
	char* buffCommand = new char[BUFFER_SIZE + 1];
	MyString command;


	while (true)
	{
		std::cout << "Enter command: ";
		std::cin >> buffCommand;
		std::cout << '\n';
		command = buffCommand;
		if (command == "help")
		{
			help();
			std::cout << "Enter command: ";

			continue;
		}
		else if (command == "load") {
			load();
			continue;
		}
		else if (command == "exit") {
			delete[] buffCommand;
			return;
		}
		if (activeSession == -1)
		{
			std::cout << "There is no active session\n";

			continue;
		}
		if (command == "add") {
			add();
		}
		else if (command == "collage") {
			createCollage();
		}
		else if (command == "switch") {
			switchSession();
		}
		else if (command == "sessionInfo") {
			sessinInfo();
		}
		else if (command == "close") {
			close();
		}
		else if (command == "saveAs") {
			saveAs();
		}
		else if (command == "save") {
			save();
		}
		else if (command == "grayscale") {
			grayscale();
		}
		else if (command == "monochrome") {
			monochrome();
		}
		else if (command == "undo") {
			undo();
		}
		else if (command == "rotate") {
			rotate();
		}
		else if (command == "negative") {
			negative();
		}
		else
		{
			std::cout << "invalud command\n";
		}
		

	}
}

void System::load()
{
	char* buffer = new char[BUFFER_SIZE];
	std::cin.getline(buffer, BUFFER_SIZE);
	std::stringstream ss(buffer);
	Session newSesion(sessions.getSize());
	MyString currImg;
	while (ss>> buffer)
	{
		currImg = buffer;
		int currImgidx = findImg(currImg);
		if (currImgidx ==-1)
		{
			Img* img = factory.createImg(currImg);
			newSesion.addImg(img);
			images.add(img->Clone());
		}
		else
		{
			newSesion.addImg(images[currImgidx].Clone());
		}
		std::cout << "Image " << currImg << " added succesfuly\n";

		
		//delete img;
	}
	delete[] buffer;

	activeSession = newSesion.GetId();
	sessions.pushBack(newSesion);

}

void System::add()
{
	MyString imgName;
	std::cin.ignore();
	std::cin >> imgName;
	int imgIdx = findImg(imgName);
	if (imgIdx == -1)
	{
		Img* img = factory.createImg(imgName);
		images.add(img);
		sessions[activeSession].addImg(img);
		std::cout << "Image " << imgName << " added to the current active session\n";
		//delete img;

		return;
	}
	sessions[activeSession].addImg(&images[imgIdx]);
	std::cout << "Image " << imgName << " added to the current active session\n";

}

void System::help() const
{
	std::cout << "This is console raster graphic app that uses commands in order to modify images\n";
	std::cout << "Main commands:\n load <images separated by sapce>\n close\n save\n save as <new name>\n help\n exit\n";
	std::cout << "Commands for modification:\n";
	std::cout << " grayscale\n monochrome\n negative\n rotate <direction>\n undo\n add <image>,\n session info\n";
	std::cout << " switch <session>\n collage <direction> <image1> <image2> <outimage>\n";
}

void System::save()
{
	sessions[activeSession].save();
	const polymorphic_container<Img>& activeSessionImages = sessions[activeSession].GetImages();

	for (size_t i = 0; i < activeSessionImages.getPtrsCount(); i++)
	{
		int imgIdx = findImg(activeSessionImages[i].GetName());
		if (imgIdx==-1)
		{
			std::cout << "Image not found\n";
			continue;
		}
		images[imgIdx] = activeSessionImages[i];
	}
}

void System::saveAs()
{
	MyString newFileName;
	std::cin.ignore();
	std::cin >> newFileName;
	if (findImg(newFileName)!=-1)
	{
		std::cout << "An image with whis photo already exist\n";
		return;
	}
	const polymorphic_container<Img>& activeSessionImages = sessions[activeSession].GetImages();
	MyString firstImgInitialName = activeSessionImages[0].GetName();

	sessions[activeSession].saveAs(newFileName);

	int imgIdx = findImg(firstImgInitialName);
	if (imgIdx == -1)
	{
		std::cout << "Image not found\n";
	}
	else
	{
		images[imgIdx] = activeSessionImages[0];
	}

	for (size_t i = 1; i < activeSessionImages.getPtrsCount(); i++)
	{
		imgIdx = findImg(activeSessionImages[i].GetName());
		if (imgIdx == -1)
		{
			std::cout << "Image not found\n";
			continue;
		}
		images[imgIdx] = activeSessionImages[i];
	}
}

void System::close()
{
	sessions[activeSession].close();
	activeSession = -1;
}

void System::sessinInfo() const
{
	sessions[activeSession].printInfo();
}

void System::switchSession()
{

	int newSesionNum;
	std::cin >> newSesionNum;
	if (newSesionNum >= sessions.getSize())
	{
		std::cout << "There is no nession with id " << newSesionNum;
		return;
	}
	if (sessions[newSesionNum].GetId() == -1)
	{
		std::cout << "The session with that ID was closed - id " << newSesionNum;
		return;
	}
	activeSession = newSesionNum;
	std::cout << "You switch to session with id " << newSesionNum<<"\n";
	sessions[activeSession].printInfo();

}

void System::createCollage()
{
	MyString direction;
	MyString img1;
	MyString img2;
	MyString collageName;
	char* buff = new char[BUFFER_SIZE];
	
	std::cin.ignore();
	std::cin >> buff;
	direction = buff;
	
	std::cin.ignore();
	std::cin >> buff;
	img1 = buff;

	std::cin.ignore();
	std::cin >> buff;
	img2 = buff;

	std::cin.ignore();
	std::cin >> buff;
	collageName = buff;

	if (findImg(collageName)!=-1)
	{
		std::cout << "Image with name " << collageName << " already exsits\n";
		return;
	}
	int firstImgIdx = findImg(img1);
	int secondImgIdx = findImg(img2);

	if (firstImgIdx==-1 || secondImgIdx==-1)
	{
		std::cout << "The images could not be found\n";
		return; 
	}
	
	try {
		Img* newCollage = factory.createCollage(collageName, &sessions[activeSession].GetImages()[firstImgIdx], &sessions[activeSession].GetImages()[secondImgIdx], direction == "vertical");
		sessions[activeSession].createCollage(newCollage, img1, img2);
		images.add(newCollage->Clone());
		std::cout << "New collage added(" << collageName << ")\n";
		//delete newCollage;

	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}

void System::grayscale()
{
	sessions[activeSession].addModification(Modifications::grayscale);
}

void System::monochrome()
{
	sessions[activeSession].addModification(Modifications::monochrome);

}

void System::negative()
{
	sessions[activeSession].addModification(Modifications::negative);

}

void System::rotate()
{
	MyString direction;
	std::cin.ignore();
	std::cin >> direction;

	if (direction == "left")
	{
		sessions[activeSession].addModification(Modifications::rotationLeft);
		return;
	}
	if (direction == "right")
	{
		sessions[activeSession].addModification(Modifications::rotationRight);
		return;
	}

	std::cout << "Invalid direction\n";

}

void System::undo()
{
	sessions[activeSession].undo();
}
