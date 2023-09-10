/** *********************************************************************
 * @file
 *
 * @brief  Prototypes
 ***********************************************************************/
#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

#ifndef __NETPBM__H__
#define __ NETPBM__H__
typedef unsigned char pixel;

/** *********************************************************************
 * @author Tristan Opbroek
 *
 * @par Description:
 * Image struct, that holds our Magic Number, Comments, rows and columns, and all of our pixel values for an image
 *
 *
 ***********************************************************************/
struct image 
{ 

    string magicNumber;
    string comment;
    int rows;
    int cols;
    pixel** redgray; 
    pixel** green;
    pixel** blue;
};

/************************************************************************
 *                         Function Prototypes
 ***********************************************************************/
void openInput(ifstream& fin, string file);
void openOutput(ofstream& fout, string file, string type);

void createArray(pixel**& ptr, int cols, int rows);

void getPixelsP6(image& picture, ifstream& fin);
void getPixelsP3(image& picture, ifstream& fin);

void writeFile(string type, ofstream& fout, image& picture);
void writeFileGray(string type, ofstream& fout, image& picture);

void brighten(int briValue, image& picture);
void negit(image& picture);
void gScale(image& picture);
void contrast(image& picture);
void sharpen(image& picture);
void smooth(image& picture);

int clamp(int number);

#endif