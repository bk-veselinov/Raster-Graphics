#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include "Stack.hpp"
#include <exception>

constexpr unsigned MAX_MODIFICATIONS_STACK_COUNT = 64;

enum States {
	monochrome,
	grayscale,
	color,
	defaultState
};

enum class Modifications
{
	monochrome,
	grayscale,
	negative,
	rotationLeft,
	rotationRight

};

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


class Img
{
	//TODO
	//saveas
	//save in file
	//corect errors for collage creation
protected:
	MyString fileType;
	MyString name = "Unknown";
	unsigned width = 0;
	unsigned height = 0;
	bool isNegative = false;
	States currState = defaultState;

	States PendingState = States::defaultState;
	int rotationsCount = 0;
	unsigned pendingNegativeModificationsCount = 0;

	MyStack<Modifications, MAX_MODIFICATIONS_STACK_COUNT> pendingStatesModifications;


public:
	int GetRotationsCount()const;
	const States& GetState()const;

	bool isSizeCompatableWith(const Img* other) const;
	
	const MyString& GetImgType()const;

	Img() = default;
	Img(const MyString& _name, unsigned w, unsigned h, const States& state, const MyString& fileType);

	const unsigned GetWidth() const;
	void SetWidth(unsigned w);

	const unsigned GetHeight() const;
	void SetHeight(unsigned h);

	const MyString& GetName() const;
	void SetName(const MyString& _name);

	void addModification(const Modifications& mod);
	void undo(const Modifications& lastModificationType);

	void save();
	void saveAs(const MyString& newFileName);


	virtual Img* Clone() const = 0;

	virtual ~Img() = default;
};

