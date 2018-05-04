/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Visual Studio 2015 Community, g++ Compiler
  date:               12.04.2018
  updated:            12.04.2018
*/

#include "../include/le_moon.h"

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// private window
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void LEMoon::handleWindow()
{
  if(this->event.type = SDL_WINDOWEVENT)
  {
    switch(this->event.window.event)
    {
      case SDL_WINDOWEVENT_SHOWN:
      {

      } break;
      case SDL_WINDOWEVENT_HIDDEN:
      {

      } break;
      case SDL_WINDOWEVENT_EXPOSED:
      {

      } break;
      case SDL_WINDOWEVENT_MOVED:
      {

      } break;
      case SDL_WINDOWEVENT_RESIZED:
      {

      } break;
      case SDL_WINDOWEVENT_SIZE_CHANGED:
      {

      } break;
      case SDL_WINDOWEVENT_MINIMIZED:
      {

      } break;
      case SDL_WINDOWEVENT_MAXIMIZED:
      {

      } break;
      case SDL_WINDOWEVENT_RESTORED:
      {

      } break;
      case SDL_WINDOWEVENT_ENTER:
      {

      } break;
      case SDL_WINDOWEVENT_LEAVE:
      {

      } break;
      case SDL_WINDOWEVENT_FOCUS_GAINED:
      {
        this->window.focusGained = LE_TRUE;
      } break;
      case SDL_WINDOWEVENT_FOCUS_LOST:
      {
        this->window.focusGained = LE_FALSE;
      } break;
      case SDL_WINDOWEVENT_CLOSE:
      {

      } break;
      case SDL_WINDOWEVENT_TAKE_FOCUS:
      {

      } break;
      case SDL_WINDOWEVENT_HIT_TEST:
      {

      } break;
    };
  }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public window
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

bool LEMoon::windowFocused()
{
  return this->window.focusGained;
}