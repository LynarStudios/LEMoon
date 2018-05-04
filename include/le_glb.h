/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Visual Studio 2015 Community, g++ Compiler
  date:               18.05.2017
  updated:            04.05.2018
*/

#include <SDL.h>
#include <iostream>
#include <mutex>
using namespace std;
//#include "theoraplay.h"
#include "glm/glm.hpp"

#ifndef H_LE_GLB
#define H_LE_GLB

// OS specific

//#define LE_ANDROID              102
#define LE_WINDOWS              103
//#define LE_LINUX                104

// LEMoon constants

#define LE_DEBUG                100
#define LE_TRUE                 1
#define LE_FALSE                0
#define LE_CURRENT_SRCRECT      -1
#define LE_FORWARD              1
#define LE_BACKWARD             2
#define LE_INACTIVE             0
#define LE_PRESSED              1
#define LE_RELEASED             2
//#define LE_THEORA               1

typedef struct sColor
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} Color;

struct LinkedVec2
{
  LinkedVec2 * pLeft;
  LinkedVec2 * pRight;
  uint32_t id;
  glm::vec2 data;
  double currentDegree;
};

typedef struct sLine
{
  SDL_Point pointA;
  SDL_Point pointB;
} Line;

typedef struct sLECollBox
{
  Line lineLeft;
  Line lineTop;
  Line lineRight;
  Line lineBottom;
  SDL_Point center;
} LECollBox;

typedef struct sPoint_d
{
  double x;
  double y;
} Point_d;

typedef struct sLine_d
{
  Point_d p1;
  Point_d p2;
} Line_d;

typedef struct sLECollBox_d
{
  Line_d lineLeft;
  Line_d lineTop;
  Line_d lineRight;
  Line_d lineBottom;
  Point_d center;
} LECollBox_d;

#ifdef LE_THEORA
typedef struct sAudioQueue 
{
  const THEORAPLAY_AudioPacket * pAudio;
  int offset;
  struct sAudioQueue * pNext;
} AudioQueue;
#endif

struct SourceRect
{
  SourceRect * pLeft;
  SourceRect * pRight;
  uint32_t id;
  SDL_Rect srcRect;
};

typedef struct SNotify
{
  bool notifyByEngine;
  bool notifyByUser;    // must be false to merge lists, otherwise the user is using lists at the current stage
} Notify;

#endif
