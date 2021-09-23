#include "PixelSumNaive.h"
#include "Helpers.h"
#include <iostream>
#include <vector>


PixelSumNaive::PixelSumNaive(const unsigned char* buffer, int xWidth, int yHeight) : xWidth(xWidth), yHeight(yHeight)
{
    int size = xWidth * yHeight;

    // Create copy of source data
    copyData(sourceData, buffer, size);

    // Create integral image table 
    integralImage = new unsigned int[size];


    // taken form https://www.ipol.im/pub/art/2014/57/article_lr.pdf (Integral Images for Block Matching)
    integralImage[0] = sourceData[0];


    for (int x = 1; x < xWidth; x++)
    {
        integralImage[x] = integralImage[x - 1] + sourceData[x];

    }
    for (int y = 1; y < yHeight; y++)
    {
        unsigned int sum = sourceData[0 + y * xWidth];

        integralImage[0 + y * xWidth] = integralImage[0 + (y - 1) * xWidth] + sum;

        for (int x = 1; x < xWidth; x++)
        {
            sum += sourceData[x + y * xWidth];

            integralImage[x + y * xWidth] = integralImage[x + (y - 1) * xWidth] + sum;

        }
    }


}

PixelSumNaive::~PixelSumNaive()
{
    delete[] sourceData;
    delete[] integralImage;

}

PixelSumNaive::PixelSumNaive(const PixelSumNaive& otherPixelSum)
{
    // Create and store a copy of otherPixelSum's data
    xWidth = otherPixelSum.xWidth;
    yHeight = otherPixelSum.yHeight;
    int size = xWidth * yHeight;

    // Create copy of source data
    copyData(sourceData, otherPixelSum.sourceData, size);
    // Create copy of integral image
    copyData(integralImage, otherPixelSum.integralImage, size);



}

PixelSumNaive& PixelSumNaive::operator=(const PixelSumNaive& otherPixelSum)
{
    // Check if the same object
    if (this == &otherPixelSum)
    {
        return *this;
    }

    // Create and store a copy of otherPixelSum's data
    xWidth = otherPixelSum.xWidth;
    yHeight = otherPixelSum.yHeight;
    int size = xWidth * yHeight;

    // Create copy of source data
    copyData(sourceData, otherPixelSum.sourceData, size);
    // Create copy of integral image
    copyData(integralImage, otherPixelSum.integralImage, size);


    return *this; // return a reference to self
}

unsigned int PixelSumNaive::getPixelSum(int x0, int y0, int x1, int y1) const
{


    // Swap if needed
    checkSwap(x0, y0, x1, y1);

    // Check if completely out of borders
    if (checkOutOfBorders(x0, y0, x1, y1))
    {
        return 0;
    }

    // Clamp if needed (if out of borders)
    clampBorders(x0, y0, x1, y1);

    // Calculate
    auto pixelSum = getSumOfSearchWindow(integralImage, x0, y0, x1, y1);

    return pixelSum;
}

double PixelSumNaive::getPixelAverage(int x0, int y0, int x1, int y1) const
{
    // Calculate
    unsigned int sum = getPixelSum(x0, y0, x1, y1);

    // Result
    int width = std::abs(x1 - x0) + 1;
    int height = std::abs(y1 - y0) + 1;

    return double(sum) / double(width * height);
}



template<typename T>
void PixelSumNaive::copyData(T*& dst, const T* src, int size)
{
    delete[] dst; // should be no memory leak
    dst = new T[size];
    for (int i = 0; i < size; ++i)
    {
        dst[i] = src[i];
    }
}

template<typename T>
T PixelSumNaive::getSumOfSearchWindow(const T* src, int x0, int y0, int x1, int y1) const
{
    // Calculate
    unsigned int sum = 0;
    unsigned char* searchWindowCurrentPixel = nullptr;
    unsigned char* searchWindowTopLeftPixel = sourceData + (y0 * xWidth + x0);
    
    
    for (int y = y0; y <= y1; ++y)

        searchWindowCurrentPixel = searchWindowTopLeftPixel + (y * xWidth);
        for (int x = x0; x <= x1; ++x)
        {
            //TODO::
            sum += *searchWindowCurrentPixel;
            searchWindowCurrentPixel++;
        }


    return sum;
}

bool PixelSumNaive::checkOutOfBorders(int& x0, int& y0, int& x1, int& y1) const
{
    if (x0 >= xWidth || x1 < 0)
    {
        return true;
    }

    if (y0 >= yHeight || y1 < 0)
    {
        return true;
    }

    return false;
}

void PixelSumNaive::clampBorders(int& x0, int& y0, int& x1, int& y1) const
{
    // Check if values too large
    x0 = (x0 >= xWidth) ? xWidth - 1 : x0;
    y0 = (y0 >= yHeight) ? yHeight - 1 : y0;
    x1 = (x1 >= xWidth) ? xWidth - 1 : x1;
    y1 = (y1 >= yHeight) ? yHeight - 1 : y1;

    // Check if negative
    x0 = (x0 < 0) ? 0 : x0;
    y0 = (y0 < 0) ? 0 : y0;
    x1 = (x1 < 0) ? 0 : x1;
    y1 = (y1 < 0) ? 0 : y1;
}

void PixelSumNaive::checkSwap(int& x0, int& y0, int& x1, int& y1) const
{
    if (x0 > x1) std::swap(x0, x1);
    if (y0 > y1) std::swap(y0, y1);
}


