/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Visual Studio 2015 Community, g++ Compiler
  date:               12.04.2018
  updated:            03.05.2018
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
  this->mtxLine.originalList.lock();
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

  this->mtxLine.originalList.unlock();
  return pRet;
}

LELine * LEMoon::lineGetFromBuffer(uint32_t id)
{
  this->mtxLine.bufferList.lock();
  LELine * pRet = nullptr;
  LELine * pCurrent = nullptr;

  if(this->pLineHeadBuffer != nullptr)
  {
    if(this->memory.pLastLine != nullptr && this->memory.pLastLine->id == id)
      {pRet = this->memory.pLastLine;}
    else
    {
      pCurrent = this->pLineHeadBuffer->pRight;

      while(pCurrent != this->pLineHeadBuffer)
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

  this->mtxLine.bufferList.unlock();
  return pRet;
}

void LEMoon::lineCleanList()
{
  LELine * pCurrent = nullptr;
  LELine * pNext = nullptr;

  if(this->pLineHead != nullptr)
  {
    pCurrent = this->pLineHead->pRight;

    while(pCurrent != this->pLineHead)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->markedAsDelete)
      {
        pCurrent->pRight->pLeft = pCurrent->pLeft;
        pCurrent->pLeft->pRight = pCurrent->pRight;
        delete pCurrent;
      }

      pCurrent = pNext;
    }
  }
}

void LEMoon::lineCleanBufferList()
{
  LELine * pCurrent = nullptr;
  LELine * pNext = nullptr;

  if(this->pLineHeadBuffer != nullptr)
  {
    pCurrent = this->pLineHeadBuffer->pRight;

    while(pCurrent != this->pLineHeadBuffer)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->markedAsDelete)
      {
        pCurrent->pRight->pLeft = pCurrent->pLeft;
        pCurrent->pLeft->pRight = pCurrent->pRight;
        delete pCurrent;
      }

      pCurrent = pNext;
    }
  }
}

void LEMoon::lineConstructor()
{
  this->pLineHead = nullptr;
  this->pLineHeadBuffer = nullptr;

  this->notifyLine.notifyByEngine = LE_FALSE;
  this->notifyLine.notifyByUser = LE_FALSE;

  this->mtxLine.lineCreateLockedByMerge = LE_FALSE;
  this->mtxLine.lineDeleteLockedByMerge = LE_FALSE;
  this->mtxLine.lineSetZindexLockedByMerge = LE_FALSE;

  this->mtxLine.originalLockedBySetZindex = LE_FALSE;
  this->mtxLine.bufferLockedBySetZindex = LE_FALSE;
}

void LEMoon::lineDeleteOriginalList()
{
  if(this->pLineHead->pLeft == this->pLineHead && this->pLineHead->pRight == this->pLineHead)
  {
    delete this->pLineHead;
    this->pLineHead = nullptr;
  }
}

void LEMoon::lineDeleteBufferList()
{
  if(this->pLineHeadBuffer->pLeft == this->pLineHeadBuffer && this->pLineHeadBuffer->pRight == this->pLineHeadBuffer)
  {
    delete this->pLineHeadBuffer;
    this->pLineHeadBuffer = nullptr;
  }
}

void LEMoon::lineMergeLists()
{
  LELine * pCurrent = nullptr;
  LELine * pNext = nullptr;

  if(this->pLineHeadBuffer != nullptr)
  {
    pCurrent = this->pLineHeadBuffer->pRight;

    while(pCurrent != this->pLineHeadBuffer)
    {
      pNext = pCurrent->pRight;
      pCurrent->pLeft->pRight = pCurrent->pRight;
      pCurrent->pRight->pLeft = pCurrent->pLeft;
      pCurrent->pRight = this->pLineHead;
      pCurrent->pLeft = this->pLineHead->pLeft;
      this->pLineHead->pLeft->pRight = pCurrent;
      this->pLineHead->pLeft = pCurrent;
      pCurrent = pNext;
    }
  }
}

int LEMoon::lineMerge()
{
  int result = LE_NO_ERROR;
  bool lockedAll = LE_FALSE;

  if(this->notifyLine.notifyByEngine && !this->notifyLine.notifyByUser)
  {
    // lock all

    if(this->mtxLine.lineCreate.try_lock())
      {this->mtxLine.lineCreateLockedByMerge = LE_TRUE;}
    if(this->mtxLine.lineDelete.try_lock())
      {this->mtxLine.lineDeleteLockedByMerge = LE_TRUE;}
    if(this->mtxLine.lineSetZindex.try_lock())
      {this->mtxLine.lineSetZindexLockedByMerge = LE_TRUE;}

    lockedAll = this->mtxLine.lineCreateLockedByMerge && this->mtxLine.lineDeleteLockedByMerge && this->mtxLine.lineSetZindexLockedByMerge;

    // delete (from both list), merge(buffer to original) and delete buffer

    if(lockedAll)
    {
      this->lineCleanList();
      this->lineCleanBufferList();
      this->lineMergeLists();
      this->lineDeleteBufferList();
      this->lineDeleteOriginalList();
      this->lineSortZindex();
      this->memory.pLastLine = nullptr;
      this->notifyLine.notifyByEngine = LE_FALSE;
    }

    // unlock all

    if(this->mtxLine.lineCreateLockedByMerge)
      {this->mtxLine.lineCreate.unlock();}
    if(this->mtxLine.lineDeleteLockedByMerge)
      {this->mtxLine.lineDelete.unlock();}
    if(this->mtxLine.lineSetZindexLockedByMerge)
      {this->mtxLine.lineSetZindex.unlock();}

    this->mtxLine.lineCreateLockedByMerge = LE_FALSE;
    this->mtxLine.lineDeleteLockedByMerge = LE_FALSE;
    this->mtxLine.lineSetZindexLockedByMerge = LE_FALSE;
  }

  return result;
}

void LEMoon::lineSortZindex()
{
  LELine * pCurrent = nullptr;
  LELine * pNext = nullptr;

  if(this->pLineHead != nullptr)
  {
    pCurrent = this->pLineHead->pRight;

    while(pCurrent != this->pLineHead)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->zindex > pNext->zindex && pNext != this->pLineHead)
      {
        // ausklinken

        pCurrent->pLeft->pRight = pCurrent->pRight;
        pCurrent->pRight->pLeft = pCurrent->pLeft;

        // richtig einsortieren

        while(pCurrent->zindex > pNext->zindex && pNext != this->pLineHead)
          {pNext = pNext->pRight;}

        pCurrent->pLeft = pNext->pLeft;
        pCurrent->pRight = pNext;
        pNext->pLeft->pRight = pCurrent;
        pNext->pLeft = pCurrent;

        // start again

        pCurrent = this->pLineHead->pRight;       
      }
      else
        {pCurrent = pNext;}
    }
  }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public line
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::lineCreate(uint32_t id)
{
  this->mtxLine.lineCreate.lock();
  int result = LE_NO_ERROR;
  LELine * pNew = this->lineGet(id);

  if(pNew == nullptr)
    {pNew = this->lineGetFromBuffer(id);}

  if(pNew == nullptr)
  {
    this->mtxLine.originalList.lock();

    if(this->pLineHead == nullptr)
    {
      this->pLineHead = new LELine;
      this->pLineHead->pLeft = this->pLineHead;
      this->pLineHead->pRight = this->pLineHead;
      this->pLineHead->id = 1989;
      this->pLineHead->zindex = 0;
    }

    this->mtxLine.originalList.unlock();
    this->mtxLine.bufferList.lock();

    if(this->pLineHeadBuffer == nullptr)
    {
      this->pLineHeadBuffer = new LELine;
      this->pLineHeadBuffer->pLeft = this->pLineHeadBuffer;
      this->pLineHeadBuffer->pRight = this->pLineHeadBuffer;
      this->pLineHeadBuffer->id = 28092017;
      this->pLineHeadBuffer->zindex = 0;
    }

    pNew = new LELine;
    pNew->pRight = this->pLineHeadBuffer;
    pNew->pLeft = this->pLineHeadBuffer->pLeft;
    this->pLineHeadBuffer->pLeft->pRight = pNew;
    this->pLineHeadBuffer->pLeft = pNew;
    pNew->id = id;
    pNew->line.pointA = {0, 0};
    pNew->line.pointB = {0, 0};
    pNew->zindex = 0;
    pNew->color = {255, 255, 255, 255};
    pNew->visible = LE_TRUE;
    pNew->markedAsDelete = LE_FALSE;

    this->mtxLine.bufferList.unlock();
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

  if(!result)
    {this->notifyLine.notifyByEngine = LE_TRUE;}

  this->mtxLine.lineCreate.unlock();
  return result;
}

int LEMoon::lineDelete(uint32_t id)
{
  this->mtxLine.lineDelete.lock();
  int result = LE_NO_ERROR;
  LELine * pLine = this->lineGet(id);

  if(pLine == nullptr)
    {pLine = this->lineGetFromBuffer(id);}

  if(pLine != nullptr)
    {pLine->markedAsDelete = LE_TRUE;}
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

  this->mtxLine.lineDelete.unlock();
  return result;
}

void LEMoon::linePrintList()
{
  this->mtxLine.linePrintList.lock();
  this->mtxLine.originalList.lock();
  LELine * pCurrent = nullptr;

  if(this->pLineHead != nullptr)
  {
    pCurrent = this->pLineHead->pRight;

    if(pCurrent != nullptr)
    {
      printf("ORIGINAL: Head: %d", this->pLineHead->id);

      while(pCurrent != this->pLineHead)
      {
        printf(" <-> %d", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head: %d\n", this->pLineHead->id);
    }
  }

  this->mtxLine.originalList.unlock();
  this->mtxLine.linePrintList.unlock();
}

void LEMoon::linePrintBufferList()
{
  this->mtxLine.linePrintBufferList.lock();
  this->mtxLine.bufferList.lock();
  LELine * pCurrent = nullptr;

  if(this->pLineHeadBuffer != nullptr)
  {
    pCurrent = this->pLineHeadBuffer->pRight;

    if(pCurrent != nullptr)
    {
      printf("BUFFER: Head: %d", this->pLineHeadBuffer->id);

      while(pCurrent != this->pLineHeadBuffer)
      {
        printf(" <-> %d", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head: %d\n", this->pLineHeadBuffer->id);
    }
  }

  this->mtxLine.bufferList.unlock();
  this->mtxLine.linePrintBufferList.unlock();
}

int LEMoon::lineSet(uint32_t id, int x1, int y1, int x2, int y2)
{
  this->mtxLine.lineSet.lock();
  int result = LE_NO_ERROR;
  LELine * pLine = this->lineGet(id);

  if(pLine == nullptr)
    {pLine = this->lineGetFromBuffer(id);}

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

  this->mtxLine.lineSet.unlock();
  return result;
}

int LEMoon::lineSetColor(uint32_t id, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  this->mtxLine.lineSetColor.lock();
  int result = LE_NO_ERROR;
  LELine * pLine = this->lineGet(id);

  if(pLine == nullptr)
    {pLine = this->lineGetFromBuffer(id);}

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

  this->mtxLine.lineSetColor.unlock();
  return result;
}

int LEMoon::lineSetVisible(uint32_t id, bool visible)
{
  this->mtxLine.lineSetVisible.lock();
  int result = LE_NO_ERROR;
  LELine * pLine = this->lineGet(id);

  if(pLine == nullptr)
    {pLine = this->lineGetFromBuffer(id);}

  if(pLine != nullptr)
    {pLine->visible = visible;}

  this->mtxLine.lineSetVisible.unlock();
  return result;
}

int LEMoon::lineSetZindex(uint32_t id, uint32_t zindex)
{
  this->mtxLine.lineSetZindex.lock();
  int result = LE_NO_ERROR;
  LELine * pCurrent = nullptr;
  bool moreThanOneElement = this->pLineHead->pLeft->id != this->pLineHead->pRight->id;
  LELine * pLine = this->lineGet(id);

  if(pLine == nullptr)
  {
    pLine = this->lineGetFromBuffer(id);

    if(pLine != nullptr)
      {this->mtxLine.bufferLockedBySetZindex = LE_TRUE;}
  }
  else
    {this->mtxLine.originalLockedBySetZindex = LE_TRUE;}

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

      if(this->mtxLine.originalLockedBySetZindex)
        {this->mtxLine.originalList.lock();}
      if(this->mtxLine.bufferLockedBySetZindex)
        {this->mtxLine.bufferList.lock();}

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

      if(this->mtxLine.originalLockedBySetZindex)
      {
        this->mtxLine.originalList.unlock();
        this->mtxLine.originalLockedBySetZindex = LE_FALSE;
      }

      if(this->mtxLine.bufferLockedBySetZindex)
      {
        this->mtxLine.bufferList.unlock();
        this->mtxLine.bufferLockedBySetZindex = LE_FALSE;
      }
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

  this->mtxLine.lineSetZindex.unlock();
  return result;
}

void LEMoon::lineUsingThread(bool flag)
{
  this->mtxLine.lineUsingThread.lock();
  this->notifyLine.notifyByUser = flag;
  this->mtxLine.lineUsingThread.unlock();
}