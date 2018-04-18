/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Ubuntu 16.04, g++ Compiler
  date:               09.06.2017
  updated:            05.11.2017
*/

#ifndef H_LE_MATH
#define H_LE_MATH

#include <stdint.h>
#include "SDL.h"
#include <math.h>
#include "le_glb.h"

#define PI      3.14159

bool mathLineIntersection(Line_d, Line_d);
bool mathRectIntersection(LECollBox_d, LECollBox_d);
uint32_t mathMax(uint32_t, uint32_t);
uint32_t mathMin(uint32_t, uint32_t);
uint32_t mathMin(uint32_t*, uint32_t);
double mathMod(double, double);
SDL_Point mathRotatePoint(SDL_Point, SDL_Point, double);        // diese Funktion rotiert einen Punkt um einen Mittelpunkt anhand einer Gradzahl
Point_d mathRotatePoint(Point_d, Point_d, double);              // diese Funktion rotiert einen Punkt um einen Mittelpunkt anhand einer Gradzahl

#endif
