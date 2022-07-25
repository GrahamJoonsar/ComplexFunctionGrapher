#include "tigr.h"
#include <complex>

const std::complex<double> i(0, 1);

#define c(a, b) std::complex<double>((double)(a), (double)(b))

std::complex<double> function(std::complex<double> z){
    return (z*z);
}

inline int clamp(int x){
    if (x < 0) return 0;
    if (x > 255) return 255;
    return x;
}

constexpr int width = 1000;
constexpr int height = 1000;

int main(void){
    int density = 1;
    Tigr* screen = tigrWindow(width, height, "Complex Grapher", 0);
    //tigrClear(screen, tigrRGB(10, 10, 20));
    //tigrLine(screen, 300, 0, 300, 600, tigrRGB(255, 255, 255));
    //tigrLine(screen, 0, 300, 600, 300, tigrRGB(255, 255, 255));
    
    for (int y = density; y < height; y += density){
        for (int x = density; x < width; x += density){
            int truex =  (x-width/2)/density;
            int truey = -(y-height/2)/density;
            std::complex<double> n(truex, truey);
            std::complex<double> res = function(n);
            int endx =  res.real()*density + width;
            int endy = -res.imag()*density + height;
            float theta = atan2(endy-y, endx-x);
            screen->pix[y*screen->w + x] = tigrRGB(256*cos(abs(res)), 256*cos(abs(res)+120), 256*cos(abs(res)-120));
            //tigrLine(screen, x, y, x + density*cos(theta), y + density*sin(theta), tigrRGB(256*cos(abs(res)), 256*cos(abs(res)+120), 256*cos(abs(res)-120)));
        }
    }
    while (!tigrClosed(screen)) {
        tigrUpdate(screen);
    }
}