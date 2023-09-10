/** *********************************************************************
 * @file
 *
 * @brief This program takes an .ppm file and can perform operations on it
 * (Negate, Brighten, Sharpen, Smooth, Grayscale, or Contrast), and then output the file to a
 * specified file in either ascii or binary
 ***********************************************************************/

 /** ********************************************************************
 *
 * @mainpage THPE1 - Image Manipulation
 *
 * @section CSC 215 M02
 *
 * @authors Tristan Opbroek
 *
 * @date October 17th, 2022
 *
 * @par Instructor:
 *         Roger Schrader
 *
 * @par Course:
 *         CSC 215 - Section 2 - 1:00 pm
 *
 * @par Location:
 *         Classroom Building - Room 205
 *
 * @section program_section Program Information
 *
 * @details This program takes an .ppm file and can perform operations on it
 * (Negate, Brighten, Sharpen, Smooth, Grayscale, or Contrast), and then output the file to a
 * specified file in either ascii or binary.
 * The program checks if the provided arugments are valid, and then proceeds with the operations.
 * It starts with opening and reading from the given input file into memory, consisting of 3 color arrays.
 * After all the data has been sucessfully extracted, the program looks to the user's input for direction.
 * If the user specifies no operation, the program simply outputs to the directed output file with the specified
 * format, otherwise, the function proceeds to look for the user's operation request. Based on the provided argument,
 * the program runs the data through algorithms to manipulate the image (ie. Brighten, Contrast). Once it
 * is finished the program outputs the data to the specified file in the specified type as requested.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
 *  @verbatim
 *  minimal run:
 *  c:\> thpe01.exe --outputtype basename image.ppm
 *
 *   normal run:
 *   c:\> thpe01.exe[option] --outputtype basename image.ppm
 *
 * where --outputtype can be "--ascii" or "binary", and
 * [option] can be "--negate", "--brighten #", "sharpen", "smooth", "grayscale", "contrast"
 *
 * basename is the name of the file to output (without extension)
 * image.ppm is the source image.
 *
 *  @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug  The program doesn't handle the brighten argument well, and if the user doesn't supply a number bad things happen.
 * @bug  Some operations (namely Smooth and Sharpen) REQUIRE at least a 3x3 image, as any less will cause us to overstep the
 * bounds of our array, or not perform any operations at all.
 * @bug smooth function doesn't work.
 * @todo Fix issues with Brighten arguments
 * @todo fix smooth function.
 *
 *
 * @par Modifications and Development Timeline:
 *  Gitlab commit log, <a href = "https://gitlab.cse.sdsmt.edu/101078202/csc215f22programs/-/commits/main">
 *
 ***********************************************************************/
#define CATCH_CONFIG_RUNNER
#include "..\\catch.hpp"
#include "netpbm.h"
const bool runcatch = false;

/** *********************************************************************
 * @author Tristan Opbroek
 *
 * @par Description:
 * This is the starting point to the program.  Based on user input it calls the necessary functions to
 * get, store, process, and then output data.
 *
 *
 * @param[in] argc - the number of arguments from the command prompt.
 * @param[in] argv - a 2d array of characters containing the arguments.
 *
 * @returns 0 -- includes text output if anything failed
 *
 * @verbatim
   see usage statement above.
   @endverbatim
 *
 ***********************************************************************/
int main(int argc, char** argv)
{
    image picture;

    ifstream fin;
    ofstream fout;

    string tempString;

    int fileI;
    int fileO;
    int fileT;
    string fileEx;


    if (runcatch)
    {
        Catch::Session session;
        int returnCode;
        returnCode = session.run(argc, argv);
        if (returnCode != 0)
            cout << "A Test case failed" << endl;
        return 0;
    }
    //-------------------------------------------------------------------------------------------------------------

    //Improper Arguments hmm
    if (argc != 4 && argc != 5 && argc != 6)
    {
        //Invalid Startup -- Usage Statement
        if (argv[1] == "--binary" ||
            argv[1] == "--ascii" ||
            argv[2] == "--binary" ||
            argv[2] == "--ascii")
        {
            cout << "thpe01.exe [option] --outputtype basename image.ppm" << endl;
            cout << endl;
            cout << "Output Type" << endl;
            cout << "       --ascii  pixel values will be written in text form"
                << endl;
            cout << " --binary pixel values will be written in binary form"
                << endl;
            cout << endl;
            cout << "Option Code" << endl;
            cout << " --negate" << endl;
            cout << " --brighten #" << endl;
            cout << " --sharpen" << endl;
            cout << " --smooth" << endl;
            cout << " --grayscale" << endl;
            cout << " --contrast" << endl;
            return 0;
        }
        //---------------------------------------------------------------------------------------------------------
      //Invalid Option -- Usage Statement
        else
        {
            cout << "Invalid Startup" << endl;
            cout << "thpe01.exe [option] --outputtype basename image.ppm" << endl;
            cout << endl;
            cout << "Output Type" << endl;
            cout << "       --ascii  pixel values will be written in text form"
                << endl;
            cout << "       --binary pixel values will be written in binary form"
                << endl;
            cout << endl;
            cout << "Option Code" << endl;
            cout << "       --negate" << endl;
            cout << "       --brighten #" << endl;
            cout << "       --sharpen" << endl;
            cout << "       --smooth" << endl;
            cout << "       --grayscale" << endl;
            cout << "       --contrast" << endl;
            return 0;


        }
        //--------------------------------------------------------------------------------------------------------------
    }
    //-
    fileI = argc - 1;
    fileO = argc - 2;
    fileT = argc - 3;
    string type = argv[fileT];
    
    if (type != "--ascii" && type != "--binary")
    {
        cout << "Invalid Startup" << endl;
        cout << "thpe01.exe [option] --outputtype basename image.ppm" << endl;
        cout << endl;
        cout << "Output Type" << endl;
        cout << "       --ascii  pixel values will be written in text form"
            << endl;
        cout << "       --binary pixel values will be written in binary form"
            << endl;
        cout << endl;
        cout << "Option Code" << endl;
        cout << "       --negate" << endl;
        cout << "       --brighten #" << endl;
        cout << "       --sharpen" << endl;
        cout << "       --smooth" << endl;
        cout << "       --grayscale" << endl;
        cout << "       --contrast" << endl;
        return 0;
    }

    string operation = argv[1];
    if (argc == 5)
    {
        
        if (operation != "--negate" &&
            operation != "--grayscale" &&
            operation != "--contrast" &&
            operation != "--sharpen" &&
            operation != "--smooth")
        {
            cout << "Invalid Option" << endl;
            cout << "thpe01.exe [option] --outputtype basename image.ppm" << endl;
            cout << endl;
            cout << "Output Type" << endl;
            cout << "       --ascii  pixel values will be written in text form"
                << endl;
            cout << "       --binary pixel values will be written in binary form"
                << endl;
            cout << endl;
            cout << "Option Code" << endl;
            cout << "       --negate" << endl;
            cout << "       --brighten #" << endl;
            cout << "       --sharpen" << endl;
            cout << "       --smooth" << endl;
            cout << "       --grayscale" << endl;
            cout << "       --contrast" << endl;
            return 0;
        }
    }
    else if (argc == 6)
    {

        if (operation != "--brighten")
        {
            cout << "Invalid Option" << endl;
            cout << "thpe01.exe [option] --outputtype basename image.ppm" << endl;
            cout << endl;
            cout << "Output Type" << endl;
            cout << "       --ascii  pixel values will be written in text form"
                << endl;
            cout << "       --binary pixel values will be written in binary form"
                << endl;
            cout << endl;
            cout << "Option Code" << endl;
            cout << "       --negate" << endl;
            cout << "       --brighten #" << endl;
            cout << "       --sharpen" << endl;
            cout << "       --smooth" << endl;
            cout << "       --grayscale" << endl;
            cout << "       --contrast" << endl;
            return 0;
        }
    }


    openInput(fin, argv[fileI]);


    //Image header operations
    getline(fin, picture.magicNumber, '\n'); //Extract magicnumber
    while (fin.peek() == 35) //Extract Comments
    {
        getline(fin, tempString);
        picture.comment += tempString + '\n';
    }
    getline(fin, tempString, ' '); //Get cols, put in struct
    picture.cols = stoi(tempString);

    getline(fin, tempString, '\n'); //Get rows, put in struct
    picture.rows = stoi(tempString);

    getline(fin, tempString, '\n');

    //Allocate arrays for each color value
    createArray(picture.redgray, picture.cols, picture.rows);
    createArray(picture.green, picture.cols, picture.rows);
    createArray(picture.blue, picture.cols, picture.rows);

    if (picture.magicNumber == "P3")
    {
        getPixelsP3(picture, fin);
    }

    else if (picture.magicNumber == "P6")
    {
        getPixelsP6(picture, fin);
    }
    else
    {
        cout << "Invalid Image" << endl;
        return 0;
    }

    //we have valid memory here.

    if (argc == 4) //minimal run
    {
        fileEx = argv[fileO];
        fileEx += ".ppm";
        openOutput(fout, fileEx, argv[fileT]);
        writeFile(argv[fileT], fout, picture);
        fout.close();
        fin.close();
        delete [] picture.redgray;
        delete [] picture.green;
        delete [] picture.blue;
        return 0;
    }
    //-------------------------------------------------------------------------------------------------------------
    //"Normal" run of program
    if (argc == 5)
    {
        //string type = argv[1];
        if (type == "--negate")
        {
            negit(picture);
            fileEx = argv[fileO];
            fileEx += ".ppm";
            openOutput(fout, fileEx, argv[fileT]);
            writeFile(argv[fileT], fout, picture);
            delete [] picture.redgray;
            delete [] picture.green;
            delete [] picture.blue;
            return 0;
        }
        if (type == "--grayscale")
        {
            gScale(picture);
            fileEx = argv[fileO];
            fileEx += ".pgm";
            openOutput(fout, fileEx, argv[fileT]);
            writeFileGray(argv[fileT], fout, picture);
            delete [] picture.redgray;
            delete [] picture.green;
            delete [] picture.blue;
            return 0;
        }
        if (type == "--contrast")
        {
            contrast(picture);
            fileEx = argv[fileO];
            fileEx += ".pgm";
            openOutput(fout, fileEx, argv[fileT]);
            writeFileGray(argv[fileT], fout, picture);
            delete [] picture.redgray;
            delete [] picture.green;
            delete [] picture.blue;
            return 0;
        }
        if (type == "--sharpen")
        {
            sharpen(picture);
            fileEx = argv[fileO];
            fileEx += ".ppm";
            openOutput(fout, fileEx, argv[fileT]);
            writeFile(argv[fileT], fout, picture);
            delete [] picture.redgray;
            delete [] picture.green;
            delete [] picture.blue;
            return 0;
        }
        if (type == "--smooth")
        {
            smooth(picture);
            fileEx = argv[fileO];
            fileEx += ".ppm";
            openOutput(fout, fileEx, argv[fileT]);
            writeFile(argv[fileT], fout, picture);
            delete [] picture.redgray;
            delete [] picture.green;
            delete [] picture.blue;
            return 0;
        }
    }
    //-------------------------------------------------------------------------------------------------------------
    if (argc == 6) //"brighten" run of program
    {
        int bValue = stoi(argv[argc - 4]);
        brighten(bValue, picture);
        fileEx = argv[fileO];
        fileEx += ".ppm";
        openOutput(fout, fileEx, argv[fileT]);
        writeFile(argv[fileT], fout, picture);
        delete [] picture.redgray;
        delete [] picture.green;
        delete [] picture.blue;
        return 0;
    }


    //--------------------------------------------------------------------------------------------------------------
    writeFile(argv[fileT], fout, picture);
    delete [] picture.redgray;
    delete [] picture.green;
    delete [] picture.blue;
    return 0;



}

/** *********************************************************************
 * @author Tristan Opbroek
 *
 * @par Description: This function takes an integer, and "clamps" it between 0 and 255
 *
 *
 * @param[in,out] number - the number to clamp
 *
 * @returns an int
 * @par Example:
   @verbatim
   int a = 345;
   int b = -15;
   int c = 16;

   newA = clamp(a);
   newB = clamp(b);
   newC = clamp(c);
   cout << a << b << c << endl; //a = 255, b = 0
   @endverbatim
 ***********************************************************************/
int clamp(int number)
{
    if (number < 0)
    {
        number = 0;
        return number;
    }
    if (number > 255)
    {
        number = 255;
        return number;
    }
    return number;
}

