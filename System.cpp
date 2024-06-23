#include "System.h"


int System::findImg(const MyString& name)
{
	for (size_t i = 0; i < images.getPtrsCount(); i++)
	{
		if (name == images[i].GetName())
		{
			return i;
		}
	}
	return -1;
}

void System::run()
{
	MyString command;
	std::cout << "Enter command: ";
	std::cin >> command;
	std::cout << '\n';

	while (true)
	{

		if (command == "help")
		{
			help();
		}
		else if (command == "load") {
			load();
		}
		else if (command == "exit") {
			return;
		}
		if (activeSession == -1)
		{
			std::cout << "There is no active session\n";
			std::cin >> command;

			continue;
		}
		if (command == "add") {
			add();
		}
		else if (command == "createCollage") {
			createCollage();
		}
		else if (command == "switchSession") {
			switchSession();
		}
		else if (command == "sessinInfo") {
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
		else
		{
			std::cout << "invalud command\n";
		}
		std::cin >> command;

	}
}

void System::load()
{
	char* buffer = new char[BUFFER_SIZE];
	std::cin.getline(buffer, BUFFER_SIZE);
	std::stringstream ss(buffer);
	Session newSesion(sessions.getSize());
	MyString currImg;
	while (ss>>currImg)
	{
		Img* img = factory.createImg(currImg);
		images.add(img);
		newSesion.addImg(img);
		std::cout << "Image " << currImg << "added succesfuly\n";
	}
	sessions.pushBack(newSesion);

}

void System::add()
{
	MyString imgName;
	std::cin >> imgName;
	int imgIdx = findImg(imgName);
	if (imgIdx == -1)
	{
		Img* img = factory.createImg(imgName);
		images.add(img);
		sessions[activeSession].addImg(img);
		std::cout << "Image " << imgName << "added to the current active session\n";

		return;
	}
	sessions[activeSession].addImg(&images[imgIdx]);
	std::cout << "Image " << imgName << "added to the current active session\n";

}

void System::help() const
{
	std::cout << "This is console raster graphic app that uses commands in order to modify images\n";
	std::cout << "Main commands:\nload <images separated by sapce>, close, save, save as <new name>, help, exit\n";
	std::cout << "Commands for modification:\n";
	std::cout << "grayscale,\n monochrome,\n negative,\n rotate <direction>,\n undo,\n add <image>,\n session info\n";
	std::cout << "switch <session>,\n collage <direction> <image1> <image2> <outimage>\n";
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
	MyString diraction;
	MyString img1;
	MyString img2;
	MyString collageName;

	std::cin >> diraction;
	std::cin >> img1;
	std::cin >> img2;
	std::cin >> collageName;

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

	Img* newCollage = factory.createCollage(collageName, &images[firstImgIdx], &images[secondImgIdx], diraction == "vertical");
	try {
		sessions[activeSession].createCollage(newCollage, img1, img2);
		images.add(newCollage);
		std::cout << "New collage added(" << collageName << ")\n";

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
