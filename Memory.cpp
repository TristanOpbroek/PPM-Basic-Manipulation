/** *********************************************************************
 * @file
 *
 * @brief   Memory allocation / free operations.
 ***********************************************************************/
#include "netpbm.h"

 /** *********************************************************************
  * @author Tristan Opbroek
  *
  * @par Description: This function takes a 2d, and allocates 2 arrays
  * based on the cols and rows of an image. It will throw a warning message and terminate safely if it fails.
  *
  *
  * @param[out] ptr[][] - a 2d array of points
  * @param[in] int cols - cols of 2d array
  * @param [in] int rows - rows of 2d array
  g
  * @par Example:
	@verbatim
  * pixel** cPtr;
  * int rows = 3
  * int cols = 3
  * createArray(cPtr, cols, rows);
  * cPtr[2][2] // created 3x3 array.
	@endverbatim
  ***********************************************************************/
void createArray(pixel**& ptr, int cols, int rows)
{
	//Allocated number of rows
	ptr = new (nothrow) pixel * [rows];
	if (ptr == nullptr)
	{
		cout << "Memory Allocation Error" << endl;
		exit(0);
	}

	//------------------------------------------------------- plz


	//Allocate each row it's own columns
	for (int i = 0; i < rows; i++)
	{
		ptr[i] = new (nothrow) pixel[cols];
		if (ptr[i] == nullptr)
		{
			cout << "Memory Allocation Error" << endl;
			exit(0);
		}
	}
}