#include "tigr.h"
#include <complex>

// sqrt(-1) constant
const std::complex<double> i(0, 1);

// To create a specific complex number, 
// you can use this instead of the normal verbose way
#define c(a, b) std::complex<double>((double)(a), (double)(b))

// This is the function you should change
std::complex<double> function(std::complex<double> z){
    return (z*z);
}

// width and height of the window, should probable remain equal
constexpr int width = 1000;
constexpr int height = 1000;

// density should be a shared factor of width and height
#define density 1

int main(void){
    // Creating the window
    Tigr* screen = tigrWindow(width, height, "Complex Grapher", 0);
    tigrClear(screen, tigrRGB(10, 10, 20));
    // draw the graph lines
    tigrLine(screen, width/2, 0, width/2, height, tigrRGB(255, 255, 255));
    tigrLine(screen, 0, height/2, width, height/2, tigrRGB(255, 255, 255));
    
    // Go through each point according to the density
    for (int y = density; y < height; y += density){
        for (int x = density; x < width; x += density){
            // Convert screen coordinates to complex number
            int truex =  (x-width/2)/density;
            int truey = -(y-height/2)/density;
            std::complex<double> n(truex, truey);
            // run the function
            std::complex<double> res = function(n);
            // draw a line pointing in the direction in the output of the function
            int endx =  res.real()*density + width;
            int endy = -res.imag()*density + height;
            float theta = atan2(endy-y, endx-x);
            #if (density == 1) // For performance
                screen->pix[y*screen->w + x] = tigrRGB(256*cos(abs(res)), 256*cos(abs(res)+120), 256*cos(abs(res)-120));
            #else
                tigrLine(screen, x, y, x + density*cos(theta), y + density*sin(theta), tigrRGB(256*cos(abs(res)), 256*cos(abs(res)+120), 256*cos(abs(res)-120)));
            #endif
        }
    }

    // Keeping the window open
    while (!tigrClosed(screen)) {
        tigrUpdate(screen);
    }
}
