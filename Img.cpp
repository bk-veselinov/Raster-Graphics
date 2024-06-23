#include "Img.h"

Img::Img(const MyString& _name, unsigned w, unsigned h, const States& state, const MyString& fileType): name(_name), width(w), height(h), currState(state), fileType(fileType)
{
}

int Img::GetRotationsCount() const
{
    return rotationsCount;
}
const States& Img::GetState() const
{
    return currState;
}


const MyString& Img::GetImgType() const
{
    return fileType;
}

const unsigned Img::GetWidth() const
{
    return width;
}

void Img::SetWidth(unsigned w)
{
    width = w;
}

const unsigned Img::GetHeight() const
{
    return height;
}

void Img::SetHeight(unsigned h)
{
    height = h;
}

const MyString& Img::GetName() const
{
    return name;
}

void Img::SetName(const MyString& _name)
{
    name = _name;
}

void Img::addModification(const Modifications& currMod)
{
    //if curr satet || pending satate are mono -> cannot change to grayscale
    //change the casting

    if (currMod == Modifications::rotation){
        rotationsCount++;
    }
    else if (currMod == Modifications::negative) {
        pendingNegativeModificationsCount++;
    }
    else if (currMod == Modifications::monochrome) {
        PendingState = States::monochrome;
        pendingStatesModifications.push(currMod);
    }
    else if (currMod == Modifications::grayscale) {

        if ((int)currState<=(int)currMod)
        {
            return;
        }

        PendingState = States::grayscale;
        pendingStatesModifications.push(currMod);
    }
    
    else
    {
        std::cout << "unknwn modification in img.cpp ";
    }
}

void Img::undo(const Modifications& lastModificationType)
{
    //TODO: if last mod != pendingStatesModifications.peek do not change
    if (lastModificationType == Modifications::rotation)
    {
        if (!(rotationsCount > 0))
        {
            return;
        }
        rotationsCount--;
    }
    else if (lastModificationType == Modifications::negative )
    {
        if (!(pendingNegativeModificationsCount > 0))
        {
            return;
        }
        pendingNegativeModificationsCount--;
    }
    else if ((lastModificationType == Modifications::monochrome || lastModificationType == Modifications::grayscale)
               &&!pendingStatesModifications.isEmpty() && pendingStatesModifications.peek() == lastModificationType)
    {
        pendingStatesModifications.pop();
        PendingState = ConvertModificationToState(pendingStatesModifications.peek());
    }
    
}

void Img::save()
{
    pendingStatesModifications.clear();

    if (PendingState != States::defaultState)
    {
        currState = PendingState;
        PendingState = States::defaultState;
    }

    if (rotationsCount % 2 != 0)
    {
        std::swap(width, height);
    }
    rotationsCount = 0;

    if (pendingNegativeModificationsCount % 2 != 0)
    {
        isNegative = !isNegative;
    }
    pendingNegativeModificationsCount = 0;
}


bool Img::isSizeCompatableWith(const Img* other) const
{
    //check for rotations
    if (rotationsCount%2==0 && other->rotationsCount%2==0)
    {
        return (width==other->width && height == other->height);
    }
    return (width == other->height && height == other->width);

}


