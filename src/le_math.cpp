/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Ubuntu 16.04, g++ Compiler
  date:               09.06.2017
  updated:            11.04.2018
*/

#include "../include/le_math.h"

double mathMod(double x, double range)
{
  while(x >= range)
    {x -= range;}

  return x;
}

uint32_t mathMax(uint32_t x, uint32_t y)
{
  uint32_t value = 0;

  if(x >= y)
    {value = x;}
  else
    {value = y;}

  return value;
}

uint32_t mathMin(uint32_t x, uint32_t y)
{
  uint32_t value = 0;

  if(x < y)
    {value = x;}
  else
    {value = y;}

  return value;
}

uint32_t mathMin(uint32_t * pArray, uint32_t amount)
{
  uint32_t value = 0;

  if(pArray != nullptr && amount != 0)
  {
    value = pArray[0];

    for(uint32_t i = 1 ; i < amount ; i++)
    {
      if(pArray[i] < value)
        {value = pArray[i];}
    }
  }

  return value;
}

SDL_Point mathRotatePoint(SDL_Point point, SDL_Point center, double degree)
{
  SDL_Point newPoint;
  double radiant = degree * (PI / 180.0f);
  newPoint.x = center.x + (point.x - center.x) * (int)cos(radiant) - (point.y - center.y) * (int)sin(radiant);
  newPoint.y = center.y + (point.x - center.x) * (int)sin(radiant) + (point.y - center.y) * (int)cos(radiant);

  return newPoint;
}

Point_d mathRotatePoint(Point_d point, Point_d center, double degree)
{
  Point_d newPoint;
  double radiant = degree * (PI / 180.0f);
  newPoint.x = center.x + (point.x - center.x) * cos(radiant) - (point.y - center.y) * sin(radiant);
  newPoint.y = center.y + (point.x - center.x) * sin(radiant) + (point.y - center.y) * cos(radiant);

  return newPoint;
}

bool mathLineIntersection(Line_d l1, Line_d l2)
{
  bool collided = LE_FALSE;
  double a = 0.0f;
  double b = 0.0f;
  double t = 0.0f;
  double r = 0.0f;
  Line_d buffer;
  Point_d m1 = {0.0f, 0.0f};
  Point_d m2 = {0.0f, 0.0f};
  Point_d sLeft = {0.0f, 0.0f};
  Point_d sRight = {0.0f, 0.0f};

  if(m1.x == 0.0f)
  {
    buffer = l1;
    l1 = l2;
    l2 = buffer;
  }

  // m1 und m2

  m1 = {(l1.p2.x - l1.p1.x), (l1.p2.y - l1.p1.y)};
  m2 = {(l2.p2.x - l2.p1.x), (l2.p2.y - l2.p1.y)};

  //printf("m1 (%1.2f , %1.2f)\nm2 (%1.2f , %1.2f)\n", m1.x, m1.y, m2.x, m2.y);

  // a, b, t, r

  a = (l2.p1.x - l1.p1.x) / m1.x; 
  //printf("a = (%1.2f - %1.2f) / %1.2f = %1.2f;\n", l2.p1.x, l1.p1.x, m1.x, a);

  b = m2.x / m1.x; 
  //printf("b = (%1.2f / %1.2f) = %1.2f\n", m2.x, m1.x, b);

  t = (l2.p1.y - (l1.p1.y + m1.y * a)) / (m1.y * b - m2.y); 
  //printf("t = (%1.2f - (%1.2f + %1.2f * %1.2f)) / (%1.2f * %1.2f - %1.2f) = %1.4f\n", l2.p1.y, l1.p1.y, m1.y, a, m1.y, b, m2.y, t);

  r = (l2.p1.x - l1.p1.x + m2.x * t) / m1.x; 
  //printf("r = (%1.2f - %1.2f - %1.2f * %1.2f) / %1.2f = %1.4f\n", l2.p1.x, l1.p1.x, m2.x, t, m1.x, r);

  sLeft.x = round((l1.p1.x + m1.x * r) * 100.0f) / 100.0f;
  sLeft.y = round((l1.p1.y + m1.y * r) * 100.0f) / 100.0f;
  sRight.x = round((l2.p1.x + m2.x * t) * 100.0f) / 100.0f;
  sRight.y = round((l2.p1.y + m2.y * t) * 100.0f) / 100.0f;

  collided = (sLeft.x == sRight.x) && (sLeft.y == sRight.y) && r >= 0.0f && r <= 1.0f && t >= 0.0f && t <= 1.0f;
  //printf("%1.2f = %1.2f\n%1.2f = %1.2f\n", sLeft.x, sRight.x, sLeft.y, sRight.y);
  //printf("collided: %d\n------------------------------------\n", collided);

  return collided;
}

bool mathRectIntersection(LECollBox_d frameBoxA, LECollBox_d frameBoxB)
{
  bool collided = LE_FALSE;

  collided = collided || mathLineIntersection(frameBoxA.lineLeft, frameBoxB.lineLeft);

  if(!collided)
    {collided = collided || mathLineIntersection(frameBoxA.lineLeft, frameBoxB.lineTop);}
  if(!collided)
    {collided = collided || mathLineIntersection(frameBoxA.lineLeft, frameBoxB.lineRight);}
  if(!collided)
    {collided = collided || mathLineIntersection(frameBoxA.lineLeft, frameBoxB.lineBottom);}

  if(!collided)
    {collided = collided || mathLineIntersection(frameBoxA.lineTop, frameBoxB.lineLeft);}
  if(!collided)
    {collided = collided || mathLineIntersection(frameBoxA.lineTop, frameBoxB.lineTop);}
  if(!collided)
    {collided = collided || mathLineIntersection(frameBoxA.lineTop, frameBoxB.lineRight);}
  if(!collided)
    {collided = collided || mathLineIntersection(frameBoxA.lineTop, frameBoxB.lineBottom);}

  if(!collided)
    {collided = collided || mathLineIntersection(frameBoxA.lineRight, frameBoxB.lineLeft);}
  if(!collided)
    {collided = collided || mathLineIntersection(frameBoxA.lineRight, frameBoxB.lineTop);}
  if(!collided)
    {collided = collided || mathLineIntersection(frameBoxA.lineRight, frameBoxB.lineRight);}
  if(!collided)
    {collided = collided || mathLineIntersection(frameBoxA.lineRight, frameBoxB.lineBottom);}

  if(!collided)
    {collided = collided || mathLineIntersection(frameBoxA.lineBottom, frameBoxB.lineLeft);}
  if(!collided)
    {collided = collided || mathLineIntersection(frameBoxA.lineBottom, frameBoxB.lineTop);}
  if(!collided)
    {collided = collided || mathLineIntersection(frameBoxA.lineBottom, frameBoxB.lineRight);}
  if(!collided)
    {collided = collided || mathLineIntersection(frameBoxA.lineBottom, frameBoxB.lineBottom);}

  return collided;
}
