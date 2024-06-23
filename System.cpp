#include "System.h"

const Img* System::readImg() const
{

	return nullptr;
}

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
	int sessionNum;
	std::cin >> sessionNum;
	//TODO check if out of range or session closed

	activeSession = sessionNum;
}

void System::add()
{
	MyString imgName;
	std::cin >> imgName;
	int imgIdx = findImg(imgName);
	if (imgIdx == -1)
	{
		images.add(factory.createImg(imgName));
		sessions[activeSession].addImg(factory.createImg(imgName));
		return;
	}
	//Check if it uses the same pic or new. Make it so that session add creates a copy
	sessions[activeSession].addImg(&images[imgIdx]);
}

void System::help() const
{
}

void System::save()
{
	//must save in public img arr
	sessions[activeSession].save();
}

void System::saveAs()
{
	//check if pic with this name exsits
	MyString newFileName;
	std::cin >> newFileName;
	if (findImg(newFileName)!=-1)
	{
		std::cout << "An image with whis photo already exist\n";
		return;
	}
	sessions[activeSession].saveAs(newFileName);

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
	//add if exsits

	int newSesionNum;
	std::cin >> newSesionNum;
	activeSession = newSesionNum;
}

void System::createCollage()
{
	//change session create collage. must copy the collage 159
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
	sessions[activeSession].createCollage(collageName, img1, img2, diraction == "vertical");
	images.add(newCollage);
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
	sessions[activeSession].addModification(Modifications::rotation);

}

void System::undo()
{
	sessions[activeSession].undo();
}
