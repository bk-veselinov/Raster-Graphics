#include "HelperFunctions.h"


const MyString ModificationToString(const Modifications& mod) {
	if (mod == Modifications::monochrome)
	{
		return "monochrome";
	}
	if (mod == Modifications::grayscale)
	{
		return "grayscale";
	}
	if (mod == Modifications::monochrome)
	{
		return "Monochrome";
	}
	if (mod == Modifications::negative)
	{
		return "negative";
	}if (mod == Modifications::rotationLeft)
	{
		return "rotation left";
	}if (mod == Modifications::rotationRight)
	{
		return "rotation right";
	}
	return "Unknown";
}

const Modifications& stringToModiification(const MyString& str) {
	if (str == "rotation left")
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

const States& ConvertModificationToState(const Modifications& mod) {
	switch (mod)
	{
	case Modifications::monochrome:
		return States::monochrome;
		break;

	case Modifications::grayscale:
		return States::grayscale;
		break;

	default:
		throw std::exception("Unknown state");
		break;
	}
}