// Project_Raster.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "System.h"

void createFile(const MyString& fileName, unsigned w, unsigned h) {
    std::ofstream out(fileName.c_str(), std::ios::binary);

    out.write((const char*)&w, sizeof(w));
    out.write((const char*)&h, sizeof(w));
}

int main()
{
    createFile("img3.ppm", 15, 10);
    createFile("img4.pgm", 10, 15);
    
    System s;
    s.run();


    

    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
