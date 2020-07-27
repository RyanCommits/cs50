#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

RGBTRIPLE calculateSepia(RGBTRIPLE pixel);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            int average = round((red + blue + green)/3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = calculateSepia(image[i][j]);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < round(width/2); j++) {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int red = 0;
            int blue = 0;
            int green = 0;
            float counter = 0;

            if (j == 0) {
                if (i != 0) {
                    red += image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed;
                    green += image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen;
                    blue += image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue;

                    counter += 2;
                }
                if (i != height - 1) {
                    red += image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed;
                    green += image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen;
                    blue += image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue;

                    counter += 2;
                }

                red += image[i][j].rgbtRed + image[i][j+1].rgbtRed;
                green += image[i][j].rgbtGreen + image[i][j+1].rgbtGreen;
                blue += image[i][j].rgbtBlue + image[i][j+1].rgbtBlue;

                counter += 2;
            } else if (j == width - 1) {
                if (i != 0) {
                    red += image[i-1][j].rgbtRed + image[i-1][j-1].rgbtRed;
                    green += image[i-1][j].rgbtGreen + image[i-1][j-1].rgbtGreen;
                    blue += image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue;

                    counter += 2;
                }
                if (i != height - 1) {
                    red += image[i+1][j].rgbtRed + image[i+1][j-1].rgbtRed;
                    green += image[i+1][j].rgbtGreen + image[i+1][j-1].rgbtGreen;
                    blue += image[i+1][j].rgbtBlue + image[i+1][j-1].rgbtBlue;

                    counter += 2;
                }

                red += image[i][j].rgbtRed + image[i][j-1].rgbtRed;
                green += image[i][j].rgbtGreen + image[i][j-1].rgbtGreen;
                blue += image[i][j].rgbtBlue + image[i][j-1].rgbtBlue;

                counter += 2;
            } else {
                if (i != 0) {
                    red += image[i-1][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j+1].rgbtRed;
                    green += image[i-1][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j+1].rgbtGreen;
                    blue += image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j+1].rgbtBlue;

                    counter += 3;
                }
                if (i != height - 1) {
                    red += image[i+1][j].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j+1].rgbtRed;
                    green += image[i+1][j].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j+1].rgbtGreen;
                    blue += image[i+1][j].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j+1].rgbtBlue;

                    counter += 3;
                }
                red += image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j+1].rgbtRed;
                green += image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j+1].rgbtGreen;
                blue += image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j+1].rgbtBlue;

                counter += 3;
            }

            copy[i][j].rgbtRed = round(red/counter);
            copy[i][j].rgbtGreen = round(green/counter);
            copy[i][j].rgbtBlue = round(blue/counter);
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = copy[i][j];
        }
    }
    return;
}

RGBTRIPLE calculateSepia(RGBTRIPLE pixel) {
    int sepiaRed = round(.393 * pixel.rgbtRed + .769 * pixel.rgbtGreen + .189 * pixel.rgbtBlue);
    int sepiaGreen = round(.349 * pixel.rgbtRed + .686 * pixel.rgbtGreen + .168 * pixel.rgbtBlue);
    int sepiaBlue = round(.272 * pixel.rgbtRed + .534 * pixel.rgbtGreen + .131 * pixel.rgbtBlue);

    if (sepiaRed > 255) {
        sepiaRed = 255;
    }
    if (sepiaGreen > 255) {
        sepiaGreen = 255;
    }
    if (sepiaBlue > 255) {
        sepiaBlue = 255;
    }

    RGBTRIPLE newRGBT;
    newRGBT.rgbtBlue = sepiaBlue;
    newRGBT.rgbtGreen = sepiaGreen;
    newRGBT.rgbtRed = sepiaRed;

    return newRGBT;
}