/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Visual Studio 2015 Community, g++ Compiler
  date:               12.04.2018
  updated:            12.04.2018

  NOTES:              bufferHead muss beim mergen auch komplett zerlegt und auf nullptr gesetzt werden, pLast muss auch auf nullptr gesetzt werden
*/

#include "../include/le_moon.h"

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// private point
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::pointDraw(LEPoint * pPoint)
{
  int result = LE_NO_ERROR;
  #ifdef LE_DEBUG
    char * pErrorString = nullptr;
  #endif

  // draw points

  if(pPoint->visible)
  {
    // choose right color

    if(SDL_SetRenderDrawColor(this->pRenderer, pPoint->color.r, pPoint->color.g, pPoint->color.b, pPoint->color.a))
    {
      #ifdef LE_DEBUG
        pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::pointDraw(%d)\n\n", pPoint->id);
        this->printErrorDialog(LE_SDL_DRAW_COLOR, pErrorString);
        delete [] pErrorString;
      #endif

      result = LE_SDL_DRAW_COLOR;
    }

    // blend mode

    if(!result)
    {
      if(SDL_SetRenderDrawBlendMode(this->pRenderer, SDL_BLENDMODE_BLEND))
      {
        #ifdef LE_DEBUG
          pErrorString = new char[256 + 1];
          sprintf(pErrorString, "LEMoon::pointDraw(%d)\n\n", pPoint->id);
          this->printErrorDialog(LE_DRAW_BLEND_MODE, pErrorString);
          delete [] pErrorString;
        #endif
      
        result = LE_DRAW_BLEND_MODE;
      }
    }

    // draw point

    if(!result)
    {
      if(SDL_RenderDrawPoint(this->pRenderer, pPoint->pointBuffer.x, pPoint->pointBuffer.y))
      {
        #ifdef LE_DEBUG
          pErrorString = new char[256 + 1];
          sprintf(pErrorString, "LEMoon::pointDraw(%d)\n\n", pPoint->id);
          this->printErrorDialog(LE_DRAW_POINT, pErrorString);
          delete [] pErrorString;
        #endif
      
        result = LE_DRAW_POINT;
      }
    }
  }

  return result;
}

LEPoint * LEMoon::pointGet(uint32_t id)
{
  LEPoint * pRet = nullptr;
  LEPoint * pCurrent = nullptr;

  if(this->pPointHead != nullptr)
  {
    if(this->memory.pLastPoint != nullptr && this->memory.pLastPoint->id == id)
      {pRet = this->memory.pLastPoint;}
    else
    {
      pCurrent = this->pPointHead->pRight;

      while(pCurrent != this->pPointHead)
      {
        if(pCurrent->id == id)
        {
          pRet = pCurrent;
          this->memory.pLastPoint = pRet;
          break;
        }

        pCurrent = pCurrent->pRight;
      }
    }
  }

  return pRet;
}

LinkedVec2 * LEMoon::pointGetDirection(LEPoint * pPoint, uint32_t idDirection)
{
  LinkedVec2 * pRet = nullptr;
  LinkedVec2 * pCurrent = nullptr;

  if(pPoint->pDirectionHead != nullptr)
  {
    pCurrent = pPoint->pDirectionHead->pRight;

    while(pCurrent != pPoint->pDirectionHead)
    {
      if(pCurrent->id == idDirection)
      {
        pRet = pCurrent;
        break;
      }

      pCurrent = pCurrent->pRight;
    }
  }

  return pRet;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public point
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::pointCreate(uint32_t id)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint == nullptr)
  {
    if(this->pPointHead == nullptr)
    {
      this->pPointHead = new LEPoint;
      this->pPointHead->pLeft = this->pPointHead;
      this->pPointHead->pRight = this->pPointHead;
    }

    pPoint = new LEPoint;
    pPoint->pLeft = this->pPointHead->pLeft;
    pPoint->pRight = this->pPointHead;
    this->pPointHead->pLeft->pRight = pPoint;
    this->pPointHead->pLeft = pPoint;
    pPoint->id = id;
    pPoint->currentDegree = 0.0f;
    pPoint->visible = LE_TRUE;
    pPoint->pDirectionHead = nullptr;
    pPoint->posX = 0.0f;
    pPoint->posY = 0.0f;
    pPoint->point = {0, 0};
    pPoint->pointBuffer = {0, 0};
    pPoint->zindex = 1;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointCreate(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_EXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_EXIST;
  }

  return result;
}

int LEMoon::pointDelete(uint32_t id)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);
  LinkedVec2 * pCurrentDirection = nullptr;
  LinkedVec2 * pNextDirection = nullptr;

  if(pPoint != nullptr)
  {
    pPoint->pLeft->pRight = pPoint->pRight;
    pPoint->pRight->pLeft = pPoint->pLeft;

    // loesche Bewegungsrichtungen

    if(pPoint->pDirectionHead != nullptr)
    {
      pCurrentDirection = pPoint->pDirectionHead->pRight;

      while(pCurrentDirection != pPoint->pDirectionHead)
      {
        pNextDirection = pCurrentDirection->pRight;
        delete pCurrentDirection;
        pCurrentDirection = pNextDirection;
      }

      delete pPoint->pDirectionHead;
      pPoint->pDirectionHead = nullptr;
    }

    delete pPoint;

    if(this->pPointHead->pLeft == this->pPointHead && this->pPointHead->pRight == this->pPointHead)
    {
      delete this->pPointHead;
      this->pPointHead = nullptr;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointDelete(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  return result;
}

int LEMoon::pointSetColor(uint32_t id, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint != nullptr)
  {
    pPoint->color.r = r;
    pPoint->color.g = g;
    pPoint->color.b = b;
    pPoint->color.a = a;
    pPoint->currentAlpha = (uint8_t) a;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointSetColor(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  return result;
}

int LEMoon::pointSetPosition(uint32_t id, int x, int y)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint != nullptr)
  {
    pPoint->point.x = x;
    pPoint->point.y = y;
    pPoint->pointBuffer.x = x;
    pPoint->pointBuffer.y = y;
    pPoint->posX = x;
    pPoint->posY = y;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointSetPosition(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  return result;
}

Color LEMoon::pointGetColor(uint32_t id)
{
  LEPoint * pPoint = this->pointGet(id);
  Color color;

  if(pPoint != nullptr)
    {color = pPoint->color;}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointGetColor(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return color;
}

int LEMoon::pointFade(uint32_t id, double alphaPerSecond)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint != nullptr)
  {
    pPoint->currentAlpha += (alphaPerSecond * this->timestep);

    if(pPoint->currentAlpha > 255.0f)
      {pPoint->currentAlpha = 255.0f;}

    if(pPoint->currentAlpha < 0.0f)
      {pPoint->currentAlpha = 0.0f;}

    pPoint->color.a = (uint8_t) pPoint->currentAlpha;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointFade(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  return result;
}

int LEMoon::pointRotate(uint32_t id, double degreePerSecond, SDL_Point rotationPoint)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint != nullptr)
  {
    pPoint->currentDegree += degreePerSecond * this->timestep;
    pPoint->currentDegree = mathMod(pPoint->currentDegree, 360.0f); 
    pPoint->pointBuffer = mathRotatePoint(pPoint->point, rotationPoint, pPoint->currentDegree);
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointRotate(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  return result;
}

int LEMoon::pointSetVisible(uint32_t id, bool visible)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint != nullptr)
    {pPoint->visible = visible;}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointSetVisible(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  return result;
}

int LEMoon::pointAddDirection(uint32_t id, uint32_t idDirection, glm::vec2 direction)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);
  LinkedVec2 * pDirection = nullptr;

  if(pPoint != nullptr)
  {
    pDirection = this->pointGetDirection(pPoint, idDirection);

    if(pDirection == nullptr)
    {
      // wurde schon einmal eine Bewegungsrichtung hinzugefuegt? Wenn nicht: fuege Kopf hinzu

      if(pPoint->pDirectionHead == nullptr)
      {
        pPoint->pDirectionHead = new LinkedVec2;
        pPoint->pDirectionHead->pLeft = pPoint->pDirectionHead;
        pPoint->pDirectionHead->pRight = pPoint->pDirectionHead;
      }

      // fuege neue Bewegungsrichtung hinzu

      pDirection = new LinkedVec2;
      pDirection->pRight = pPoint->pDirectionHead;
      pDirection->pLeft = pPoint->pDirectionHead->pLeft;
      pPoint->pDirectionHead->pLeft->pRight = pDirection;
      pPoint->pDirectionHead->pLeft = pDirection;
      pDirection->id = idDirection;
      pDirection->data = direction;
      pDirection->currentDegree = 0.0f;
    }
    else
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::pointAddDirection(%u, %u, glm::vec2(%1.2f, %1.2f))\n\n", id, idDirection, direction.x, direction.y);
        this->printErrorDialog(LE_DIRECTION_EXIST, pErrorString);
        delete [] pErrorString;
      #endif

      result = LE_DIRECTION_EXIST;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointAddDirection(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  return result;
}

int LEMoon::pointMoveDirection(uint32_t id, uint32_t idDirection)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);
  LinkedVec2 * pDirection = nullptr;

  if(pPoint != nullptr)
  {
    pDirection = this->pointGetDirection(pPoint, idDirection);

    if(pDirection != nullptr)
    {
      pPoint->posX += this->timestep * pDirection->data.x;
      pPoint->posY += this->timestep * pDirection->data.y;
      pPoint->pointBuffer.x = (int) pPoint->posX;
      pPoint->pointBuffer.y = (int) pPoint->posY;
    }
    else
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::pointMoveDirection(%u, %u)\n\n", id, idDirection);
        this->printErrorDialog(LE_DIRECTION_NOEXIST, pErrorString);
        delete [] pErrorString;
      #endif

      result = LE_DIRECTION_NOEXIST;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointMoveDirection(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  return result;
}

SDL_Point LEMoon::pointGetPosition(uint32_t id)
{
  LEPoint * pPoint = this->pointGet(id);
  SDL_Point position;

  if(pPoint != nullptr)
  {
    position.x = pPoint->pointBuffer.x;
    position.y = pPoint->pointBuffer.y;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointGetPosition(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return position;
}

int LEMoon::pointSetZindex(uint32_t id, uint32_t zindex)
{
  int result = LE_NO_ERROR;
  LEPoint * pElem = this->pointGet(id);
  LEPoint * pCurrent = nullptr;
  bool moreThanOneElement = this->pPointHead->pLeft->id != this->pPointHead->pRight->id;

  if(zindex == 0)
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointSetZindex(%u, %u)\n\n", id, zindex);
      this->printErrorDialog(LE_INVALID_ZINDEX, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_INVALID_ZINDEX;
  }

  if(moreThanOneElement)
  {
    if(!result && pElem != nullptr)
    {
      pElem->zindex = zindex;
    
      // exclude from list
    
      pElem->pLeft->pRight = pElem->pRight;
      pElem->pRight->pLeft = pElem->pLeft;
    
      // search right place for zindex
    
      pCurrent = this->pPointHead->pRight;
    
      while(pElem->zindex > pCurrent->zindex && pCurrent != this->pPointHead)
        {pCurrent = pCurrent->pRight;}
    
      // include at right postion
    
      pElem->pLeft = pCurrent->pLeft;
      pElem->pRight = pCurrent;
      pCurrent->pLeft->pRight = pElem;
      pCurrent->pLeft = pElem;
    }
    else
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::pointSetZindex(%u)\n\n", id);
        this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
        delete [] pErrorString;
      #endif
    
      result = LE_POINT_NOEXIST;
    }
  }

  return result;
}