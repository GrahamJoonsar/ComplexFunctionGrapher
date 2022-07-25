@echo off
cls
echo Build Start
g++ tigr.c main.cpp -O3 -o ComplexGrapher -lopengl32 -lgdi32 -lWinmm
echo Build End