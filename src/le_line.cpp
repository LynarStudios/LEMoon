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
// private line
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::lineDraw(LELine * pLine)
{
  int result = LE_NO_ERROR;
  #ifdef LE_DEBUG
    char * pErrorString = nullptr;
  #endif

  if(pLine->visible)
  {
    if(SDL_SetRenderDrawColor(this->pRenderer, pLine->color.r, pLine->color.g, pLine->color.b, pLine->color.a))
    {
      result = LE_SDL_DRAW_COLOR;

      #ifdef LE_DEBUG
        pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::lineDraw(%d)\n\n", pLine->id);
        this->printErrorDialog(result, pErrorString);
        delete [] pErrorString;
      #endif
    }

    if(!result)
    {
      if(SDL_RenderDrawLine(this->pRenderer, pLine->line.pointA.x, pLine->line.pointA.y, pLine->line.pointB.x, pLine->line.pointB.y))
      {
        result = LE_SDL_DRAW_LINE;

        #ifdef LE_DEBUG
          pErrorString = new char[256 + 1];
          sprintf(pErrorString, "LEMoon::lineDraw(%d)\n\n", pLine->id);
          this->printErrorDialog(result, pErrorString);
          delete [] pErrorString;
        #endif
      }
    }
  }

  return result;
}

LELine * LEMoon::lineGet(uint32_t id)
{
  LELine * pRet = nullptr;
  LELine * pCurrent = nullptr;

  if(this->pLineHead != nullptr)
  {
    if(this->memory.pLastLine != nullptr && this->memory.pLastLine->id == id)
      {pRet = this->memory.pLastLine;}
    else
    {
      pCurrent = this->pLineHead->pRight;

      while(pCurrent != this->pLineHead)
      {
        if(pCurrent->id == id)
        {
          pRet = pCurrent;
          this->memory.pLastLine = pCurrent;
          break;
        }

        pCurrent = pCurrent->pRight;
      }
    }
  }

  return pRet;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public line
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::lineCreate(uint32_t id)
{
  int result = LE_NO_ERROR;
  LELine * pNew = this->lineGet(id);

  if(pNew == nullptr)
  {
    if(this->pLineHead == nullptr)
    {
      this->pLineHead = new LELine;
      this->pLineHead->pLeft = this->pLineHead;
      this->pLineHead->pRight = this->pLineHead;
      this->pLineHead->zindex = 0;
    }

    pNew = new LELine;
    pNew->pRight = this->pLineHead;
    pNew->pLeft = this->pLineHead->pLeft;
    this->pLineHead->pLeft->pRight = pNew;
    this->pLineHead->pLeft = pNew;
    pNew->id = id;
    pNew->line.pointA = {0, 0};
    pNew->line.pointB = {0, 0};
    pNew->zindex = 0;
    pNew->color = {255, 255, 255, 255};
    pNew->visible = LE_TRUE;
  }
  else
  {
    result = LE_LINE_EXIST;

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::lineCreate(%u)\n\n", id);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return result;
}

int LEMoon::lineDelete(uint32_t id)
{
  int result = LE_NO_ERROR;
  LELine * pLine = this->lineGet(id);

  if(pLine != nullptr)
  {
    pLine->pLeft->pRight = pLine->pRight;
    pLine->pRight->pLeft = pLine->pLeft;
    delete pLine;

    if(this->pLineHead->pLeft == this->pLineHead && this->pLineHead->pRight == this->pLineHead)
    {
      delete this->pLineHead;
      this->pLineHead = nullptr;
    }
  }
  else
  {
    result = LE_LINE_NOEXIST;

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::lineDelete(%u)\n\n", id);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return result;
}

int LEMoon::lineSet(uint32_t id, int x1, int y1, int x2, int y2)
{
  int result = LE_NO_ERROR;
  LELine * pLine = this->lineGet(id);

  if(pLine != nullptr)
  {
    pLine->line.pointA.x = x1;
    pLine->line.pointA.y = y1;
    pLine->line.pointB.x = x2;
    pLine->line.pointB.y = y2;
  }
  else
  {
    result = LE_LINE_NOEXIST;

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::lineSet(%u)\n\n", id);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return result;
}

int LEMoon::lineSetColor(uint32_t id, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  int result = LE_NO_ERROR;
  LELine * pLine = this->lineGet(id);

  if(pLine != nullptr)
  {
    pLine->color.r = r;
    pLine->color.g = g;
    pLine->color.b = b;
    pLine->color.a = a;
  }
  else
  {
    result = LE_LINE_NOEXIST;

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::lineSetColor(%u)\n\n", id);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return result;
}

int LEMoon::lineSetVisible(uint32_t id, bool visible)
{
  int result = LE_NO_ERROR;
  LELine * pLine = this->lineGet(id);

  if(pLine != nullptr)
    {pLine->visible = visible;}

  return result;
}

int LEMoon::lineSetZindex(uint32_t id, uint32_t zindex)
{
  int result = LE_NO_ERROR;
  LELine * pLine = this->lineGet(id);
  LELine * pCurrent = nullptr;
  bool moreThanOneElement = this->pLineHead->pLeft->id != this->pLineHead->pRight->id;

  if(zindex == 0)
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::lineSetZindex(%u, %u)\n\n", id, zindex);
      this->printErrorDialog(LE_INVALID_ZINDEX, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_INVALID_ZINDEX;
  }

  if(moreThanOneElement)
  {
    if(!result && pLine != nullptr)
    {
      pLine->zindex = zindex;
    
      // exclude from list
    
      pLine->pLeft->pRight = pLine->pRight;
      pLine->pRight->pLeft = pLine->pLeft;
    
      // search right place for zindex
    
      pCurrent = this->pLineHead->pRight;
    
      while(pLine->zindex > pCurrent->zindex && pCurrent != this->pLineHead)
        {pCurrent = pCurrent->pRight;}
    
      // include at right postion
    
      pLine->pLeft = pCurrent->pLeft;
      pLine->pRight = pCurrent;
      pCurrent->pLeft->pRight = pLine;
      pCurrent->pLeft = pLine;
    }
    else
    {
      result = LE_LINE_NOEXIST;
    
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::lineSetZindex(%u)\n\n", id);
        this->printErrorDialog(result, pErrorString);
        delete [] pErrorString;
      #endif
    }
  }

  return result;
}