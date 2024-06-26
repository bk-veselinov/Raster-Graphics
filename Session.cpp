#include "Session.h"

void Session::undoAcctionForImages(const Modifications& mod)
{
	for (size_t i = 0; i < images.getPtrsCount(); i++)
	{
		images[i].undo(mod);
	}
}

void Session::addModificationToImages(const Modifications& mod)
{
	for (size_t i = 0; i < images.getPtrsCount(); i++)
	{
		images[i].addModification(mod);
	}
}

void Session::saveAllImgs(bool isSaveas, const MyString fileName)
{
	int i = 0;
	if (isSaveas)
	{
		images[0].saveAs(fileName);
		i++;
	}
	for (; i < images.getPtrsCount(); i++)
	{
		images[i].save();
	}
}

int Session::getImgIdx(const MyString& name) const
{
	for (size_t i = 0; i < images.getPtrsCount(); i++)
	{
		if (images[i].GetName() == name)
		{
			return i;
		}
	}
	return -1;
}
void Session::printImagesNames() const
{
	std::cout << "Images in the session:\n";
	for (size_t i = 0; i < images.getPtrsCount(); i++)
	{
		std::cout << images[i].GetName() << " ";
	}
	std::cout << "\n";
}
void Session::printModifications() const
{
	std::cout << "Pending modifications:\n";
	MyStack<Modifications, MAX_MODIFICATIONS_STACK_COUNT> stackToPrint(modifications);
	while (!stackToPrint.isEmpty())
	{
		
		std::cout << ModificationToString(stackToPrint.peek())<< " ";
		stackToPrint.pop();
	}
	std::cout << '\n';
}
int Session::GetId() const
{
	return id;
}
//TODO DELETE IMG** from the func that passes it
Session::Session(unsigned id,  Img** const img, size_t imgCount):id(id)
{
	for (size_t i = 0; i < imgCount; i++)
	{
		images.add(img[i]);
	}
}

Session::Session(unsigned id):id(id)
{

}

const polymorphic_container<Img>& Session::GetImages() const
{
	return images;
}

void Session::createCollage(Img* collage, const MyString& img1, const MyString& img2)
{//TODO 1)change exception(should specify why cannot create eg. type mismach or h w) 
	//  2)create collage and add it to imgs
	size_t img1Idx = getImgIdx(img1);

	size_t img2Idx = getImgIdx(img2);
	
	if (img1Idx == -1 || img2Idx==-1)
	{
		throw std::exception("Could not find the images in the active session\n");
	}
	

	addImg(collage);
}

void Session::addImg(Img* newImg)
{
	images.add(newImg);
}

void Session::addModification(const Modifications& mod)
{
	modifications.push(mod);
	addModificationToImages(mod);
}

void Session::printInfo() const
{
	printImagesNames();
	printModifications();
}

void Session::undo()
{
	if (modifications.isEmpty())
	{
		return;
	}
	Modifications topMostMod = modifications.peek();
	undoAcctionForImages(topMostMod);
	modifications.pop();

}

void Session::save()
{
	saveAllImgs(false);
	modifications.clear();
}

void Session::saveAs(const MyString& newFileName)
{
	saveAllImgs(true, newFileName);
	modifications.clear();

}

void Session::close()
{
	id = -1;
	modifications.clear();
}
