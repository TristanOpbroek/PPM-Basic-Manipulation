/** *********************************************************************
 * @file
 *
 * @brief   Image Operation Functions.
 ***********************************************************************/
#include "netPBM.h"

 /** *********************************************************************
  * @author Tristan Opbroek
  *
  * @par Description: This function takes a value and adds it to all values in the image, essentially "brightening" the image
  *
  *
  * @param[in, out] picture - struct containing image data
  * @param[in] briValue - amount to increase brightness of.
  *
  * @par Example:
  *  @verbatim
  * image picture = *some image*
  * brighten(5, picture); //Picture's pixel values increased by 5.
  *
  * @endverbatim
  ***********************************************************************/
void brighten(int briValue, image& picture)
{
	int temp;
	for (int i = 0; i < picture.rows; i++)
	{
		for (int j = 0; j < picture.cols; j++)
		{
			temp = ((int)picture.redgray[i][j]) + briValue;
			picture.redgray[i][j] = (pixel)clamp(temp);

			temp = (int)picture.green[i][j] + briValue;
			picture.green[i][j] = (pixel)clamp(temp);

			temp = (int)picture.blue[i][j] + briValue;
			picture.blue[i][j] = (pixel)clamp(temp);
		}
	}
}
/** *********************************************************************
 * @author Tristan Opbroek
 *
 * @par Description: This function negates an image, inverting all of the colors.
 *
 *
 * @param[in, out] picture - struct containing image data
 * @par Example:
 *  @verbatim
 * image picture = *some image*
 * negit(picture); //Picture's pixel values inverted.
 *
 * @endverbatim
 ***********************************************************************/
void negit(image& picture)
{
	for (int i = 0; i < picture.rows; i++)
	{
		for (int j = 0; j < picture.cols; j++)
		{
			picture.redgray[i][j] = (pixel)(255 - (int)picture.redgray[i][j]);
			picture.green[i][j] = (pixel)(255 - (int)picture.green[i][j]);
			picture.blue[i][j] = (pixel)(255 - (int)picture.blue[i][j]);
		}
	}
}
/** *********************************************************************
 * @author Tristan Opbroek
 *
 * @par Description: This function makes the image grayscale
 *
 *
 * @param[in, out] picture - struct containing image data
 *
 * @par Example:
 *  @verbatim
 * image picture = *some image*
 * gscale(picture); //Picture is now in grayscale
 *
 * @endverbatim
 ***********************************************************************/
void gScale(image& picture)
{
	double temp;
	for (int i = 0; i < picture.rows; i++)
	{
		for (int j = 0; j < picture.cols; j++)
		{
			temp = .3 * (int)picture.redgray[i][j] +
				.6 * (int)picture.green[i][j] +
				.1 * (int)picture.blue[i][j];
			picture.redgray[i][j] = (pixel)((int)round(temp));
		}
	}
}

/** *********************************************************************
 * @author Tristan Opbroek
 *
 * @par Description: This function contrasts the image, using the grayscale function.
 *
 *
 * @param[in, out] picture - struct containing image data
 *
 * @par Example:
 *  @verbatim
 * image picture = *some image*
 * contrast(picture); //Picture is now contrasted
 *
 * @endverbatim
 ***********************************************************************/
void contrast(image& picture)
{
	int min;
	int max;
	double scale;
	double temp;
	gScale(picture);
	min = (int)picture.redgray[0][0];
	max = (int)picture.redgray[0][0];
	for (int i = 0; i < picture.rows; i++)
	{
		for (int j = 0; j < picture.cols; j++)
		{
			if ((int)picture.redgray[i][j] < min)
			{
				min = (int)picture.redgray[i][j];
			}
			if ((int)picture.redgray[i][j] > max)
			{
				max = (int)picture.redgray[i][j];
			}
		}

	}
	scale = 255.0 / (max - min);
	for (int i = 0; i < picture.rows; i++)
	{
		for (int j = 0; j < picture.cols; j++)
		{
			temp = (scale * ((int)picture.redgray[i][j] - min));
			picture.redgray[i][j] = (pixel)((int)round(temp));
		}

	}

}

/** *********************************************************************
 * @author Tristan Opbroek
 *
 * @par Description: This function sharpens an image by comparing it's
 * neighbors.
 *
 *
 * @param[in, out] picture - struct containing image data
 *
 * @par Example:
 *  @verbatim
 * image picture = *some image*
 * sharpen(picture); //Picture has now been sharpened.
 *
 * @endverbatim
 ***********************************************************************/

void sharpen(image& picture)
{
	int temp;
	pixel b;
	pixel d;
	pixel f;
	pixel h;
	pixel** newRed;
	pixel** newGreen;
	pixel** newBlue;
	createArray(newRed, picture.cols, picture.rows);
	createArray(newGreen, picture.cols, picture.rows);
	createArray(newBlue, picture.cols, picture.rows);
	for (int i = 1; i < picture.rows - 1; i++)
	{
		for (int j = 1; j < picture.cols - 1; j++)
		{
			b = picture.redgray[i - 1][j];
			d = picture.redgray[i][j - 1];
			f = picture.redgray[i][j + 1];
			h = picture.redgray[i + 1][j];
			temp = 5 * (int)picture.redgray[i][j] - b - d - f - h;
			newRed[i][j] = pixel(clamp(temp));

			b = picture.green[i - 1][j];
			d = picture.green[i][j - 1];
			f = picture.green[i][j + 1];
			h = picture.green[i + 1][j];
			temp = 5 * (int)picture.green[i][j] - b - d - f - h;
			newGreen[i][j] = pixel(clamp(temp));

			b = picture.blue[i - 1][j];
			d = picture.blue[i][j - 1];
			f = picture.blue[i][j + 1];
			h = picture.blue[i + 1][j];
			temp = 5 * (int)picture.blue[i][j] - b - d - f - h;
			newBlue[i][j] = pixel(clamp(temp));
		}
	}
	for (int i = 0; i < picture.rows; i++)
	{
		newRed[i][0] = 0;
		newRed[i][picture.cols - 1] = 0;

		newBlue[i][0] = 0;
		newBlue[i][picture.cols - 1] = 0;

		newGreen[i][0] = 0;
		newGreen[i][picture.cols - 1] = 0;
	}

	for (int j = 0; j < picture.cols; j++)
	{
		newRed[0][j] = 0;
		newRed[picture.rows - 1][j] = 0;

		newBlue[0][j] = 0;
		newBlue[picture.rows - 1][j] = 0;

		newGreen[0][j] = 0;
		newGreen[picture.rows - 1][j] = 0;
	}
	picture.redgray = newRed;
	picture.green = newGreen;
	picture.blue = newBlue;

}
/** *********************************************************************
 * @author Tristan Opbroek
 *
 * @par Description: This function smooths an image by comparing it
 * to it's neighbors, and averaging all of their values.
 *
 *
 * @param[in, out] picture - struct containing image data
 *
 * @par Example:
 *  @verbatim
 * image picture = *some image*
 * smooth(picture); //Picture has now been smoothed.
 *
 * @endverbatim
 ***********************************************************************/
void smooth(image& picture)
{
	double temp;
	pixel a;
	pixel b;
	pixel c;
	pixel d;
	pixel f;
	pixel g;
	pixel h;
	pixel p;
	pixel** newRed;
	pixel** newGreen;
	pixel** newBlue;
	createArray(newRed, picture.cols, picture.rows);
	createArray(newGreen, picture.cols, picture.rows);
	createArray(newBlue, picture.cols, picture.rows);
	for (int i = 1; i < picture.rows - 1; i++)
	{
		for (int j = 1; j < picture.cols - 1; j++)
		{
			a = picture.redgray[i - 1][j - 1];
			b = picture.redgray[i - 1][j];
			c = picture.redgray[i - 1][j + 1];
			d = picture.redgray[i][j - 1];
			f = picture.redgray[i][j + 1];
			g = picture.redgray[i + 1][j - 1];
			h = picture.redgray[i + 1][j];
			p = picture.redgray[i + 1][j + 1];
			temp = (a + b + c + d + picture.redgray[i][j]
				+ f + g + h + p) / 9.0;
			newRed[i][j] = (pixel)round(temp);
			//---------------------------------------------------------
			a = picture.green[i - 1][j - 1];
			b = picture.green[i - 1][j];
			c = picture.green[i - 1][j + 1];
			d = picture.green[i][j - 1];
			f = picture.green[i][j + 1];
			g = picture.green[i + 1][j - 1];
			h = picture.green[i + 1][j];
			p = picture.green[i + 1][j + 1];
			temp = (a + b + c + d + picture.green[i][j]
				+ f + g + h + p) / 9.0;
			newGreen[i][j] = (pixel)round(temp);
			//---------------------------------------------------------
			a = picture.blue[i - 1][j - 1];
			b = picture.blue[i - 1][j];
			c = picture.blue[i - 1][j + 1];
			d = picture.blue[i][j - 1];
			f = picture.blue[i][j + 1];
			g = picture.blue[i + 1][j - 1];
			h = picture.blue[i + 1][j];
			p = picture.blue[i + 1][j + 1];
			temp = (a + b + c + d + picture.blue[i][j]
				+ f + g + h + p) / 9.0;
			newBlue[i][j] = (pixel)round(temp);
			//---------------------------------------------------------

		}

	}
	for (int i = 0; i < picture.rows; i++)
	{
		newRed[i][0] = 0;
		newRed[i][picture.cols - 1] = 0;

		newBlue[i][0] = 0;
		newBlue[i][picture.cols - 1] = 0;

		newGreen[i][0] = 0;
		newGreen[i][picture.cols - 1] = 0;
	}

	for (int j = 0; j < picture.cols; j++)
	{
		newRed[0][j] = 0;
		newRed[picture.rows - 1][j] = 0;

		newBlue[0][j] = 0;
		newBlue[picture.rows - 1][j] = 0;

		newGreen[0][j] = 0;
		newGreen[picture.rows - 1][j] = 0;
	}
	picture.redgray = newRed;
	picture.green = newGreen;
	picture.blue = newBlue;

}