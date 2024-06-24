#pragma once
#include "MyString.h"
#include <exception>
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

const MyString ModificationToString(const Modifications& mod);

const Modifications& stringToModiification(const MyString& str);

const States& ConvertModificationToState(const Modifications& mod);