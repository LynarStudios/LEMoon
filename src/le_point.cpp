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
  this->mtxPoint.originalList.lock();
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

  this->mtxPoint.originalList.unlock();
  return pRet;
}

LEPoint * LEMoon::pointGetFromBuffer(uint32_t id)
{
  this->mtxPoint.bufferList.lock();
  LEPoint * pRet = nullptr;
  LEPoint * pCurrent = nullptr;

  if(this->pPointHeadBuffer != nullptr)
  {
    if(this->memory.pLastPoint != nullptr && this->memory.pLastPoint->id == id)
      {pRet = this->memory.pLastPoint;}
    else
    {
      pCurrent = this->pPointHeadBuffer->pRight;

      while(pCurrent != this->pPointHeadBuffer)
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

  this->mtxPoint.bufferList.unlock();
  return pRet;
}

LinkedVec2 * LEMoon::pointGetDirection(LEPoint * pPoint, uint32_t idDirection)
{
  pPoint->direction.lock();
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

  pPoint->direction.unlock();
  return pRet;
}

void LEMoon::pointCleanList()
{
  LEPoint * pCurrent = nullptr;
  LEPoint * pNext = nullptr;
  LinkedVec2 * pCurrentDirection = nullptr;
  LinkedVec2 * pNextDirection = nullptr;

  if(this->pPointHead != nullptr)
  {
    pCurrent = this->pPointHead->pRight;

    while(pCurrent != this->pPointHead)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->markedAsDelete && this->pointFinishedAllMutexes(pCurrent))
      {
        pCurrent->pRight->pLeft = pCurrent->pLeft;
        pCurrent->pLeft->pRight = pCurrent->pRight;

        pCurrentDirection = pCurrent->pDirectionHead->pRight;

        while(pCurrentDirection != pCurrent->pDirectionHead)
        {
          pNextDirection = pCurrentDirection->pRight;
          delete pCurrentDirection;
          pCurrentDirection = pNextDirection;
        }

        delete pCurrent->pDirectionHead;
        pCurrent->pDirectionHead = nullptr;
        delete pCurrent;
      }

      pCurrent = pNext;
    }
  }
}

void LEMoon::pointCleanBufferList()
{
  LEPoint * pCurrent = nullptr;
  LEPoint * pNext = nullptr;
  LinkedVec2 * pCurrentDirection = nullptr;
  LinkedVec2 * pNextDirection = nullptr;

  if(this->pPointHeadBuffer != nullptr)
  {
    pCurrent = this->pPointHeadBuffer->pRight;

    while(pCurrent != this->pPointHeadBuffer)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->markedAsDelete && this->pointFinishedAllMutexes(pCurrent))
      {
        pCurrent->pRight->pLeft = pCurrent->pLeft;
        pCurrent->pLeft->pRight = pCurrent->pRight;

        pCurrentDirection = pCurrent->pDirectionHead->pRight;

        while(pCurrentDirection != pCurrent->pDirectionHead)
        {
          pNextDirection = pCurrentDirection->pRight;
          delete pCurrentDirection;
          pCurrentDirection = pNextDirection;
        }

        delete pCurrent->pDirectionHead;
        pCurrent->pDirectionHead = nullptr;
        delete pCurrent;
      }

      pCurrent = pNext;
    }
  }
}

void LEMoon::pointConstructor()
{
  this->pPointHead = nullptr;
  this->pPointHeadBuffer = nullptr;

  this->notifyPoint.notifyByEngine = LE_FALSE;
  this->notifyPoint.notifyByUser = LE_FALSE;

  this->mtxPoint.pointCreateLockedByMerge = LE_FALSE;
  this->mtxPoint.pointDeleteLockedByMerge = LE_FALSE;
  this->mtxPoint.pointSetZindexLockedByMerge = LE_FALSE;

  this->mtxPoint.originalLockedBySetZindex = LE_FALSE;
  this->mtxPoint.bufferLockedBySetZindex = LE_FALSE;
}

void LEMoon::pointDeleteOriginalList()
{
  if(this->pPointHead->pLeft == this->pPointHead && this->pPointHead->pRight == this->pPointHead)
  {
    delete this->pPointHead;
    this->pPointHead = nullptr;
  }
}

void LEMoon::pointDeleteBufferList()
{
  if(this->pPointHeadBuffer->pLeft == this->pPointHeadBuffer && this->pPointHeadBuffer->pRight == this->pPointHeadBuffer)
  {
    delete this->pPointHeadBuffer;
    this->pPointHeadBuffer = nullptr;
  }
}

void LEMoon::pointMergeLists()
{
  LEPoint * pCurrent = nullptr;
  LEPoint * pNext = nullptr;

  if(this->pPointHeadBuffer != nullptr)
  {
    pCurrent = this->pPointHeadBuffer->pRight;

    while(pCurrent != this->pPointHeadBuffer)
    {
      pNext = pCurrent->pRight;
      pCurrent->pLeft->pRight = pCurrent->pRight;
      pCurrent->pRight->pLeft = pCurrent->pLeft;
      pCurrent->pRight = this->pPointHead;
      pCurrent->pLeft = this->pPointHead->pLeft;
      this->pPointHead->pLeft->pRight = pCurrent;
      this->pPointHead->pLeft = pCurrent;
      pCurrent = pNext;
    }
  }
}

int LEMoon::pointMerge()
{
  int result = LE_NO_ERROR;
  bool lockedAll = LE_FALSE;

  if(this->notifyPoint.notifyByEngine && !this->notifyPoint.notifyByUser)
  {
    // lock all

    if(this->mtxPoint.pointCreate.try_lock())
      {this->mtxPoint.pointCreateLockedByMerge = LE_TRUE;}
    if(this->mtxPoint.pointDelete.try_lock())
      {this->mtxPoint.pointDeleteLockedByMerge = LE_TRUE;}
    if(this->mtxPoint.pointSetZindex.try_lock())
      {this->mtxPoint.pointSetZindexLockedByMerge = LE_TRUE;}

    lockedAll = this->mtxPoint.pointCreateLockedByMerge && this->mtxPoint.pointDeleteLockedByMerge && this->mtxPoint.pointSetZindexLockedByMerge;

    // delete (from both list), merge(buffer to original) and delete buffer

    if(lockedAll)
    {
      this->pointCleanList();
      this->pointCleanBufferList();
      this->pointMergeLists();
      this->pointDeleteBufferList();
      this->pointDeleteOriginalList();
      this->pointSortZindex();
      this->memory.pLastPoint = nullptr;
      this->notifyPoint.notifyByEngine = LE_FALSE;
    }

    // unlock all

    if(this->mtxPoint.pointCreateLockedByMerge)
      {this->mtxPoint.pointCreate.unlock();}
    if(this->mtxPoint.pointDeleteLockedByMerge)
      {this->mtxPoint.pointDelete.unlock();}
    if(this->mtxPoint.pointSetZindexLockedByMerge)
      {this->mtxPoint.pointSetZindex.unlock();}

    this->mtxPoint.pointCreateLockedByMerge = LE_FALSE;
    this->mtxPoint.pointDeleteLockedByMerge = LE_FALSE;
    this->mtxPoint.pointSetZindexLockedByMerge = LE_FALSE;
  }

  return result;
}

void LEMoon::pointSortZindex()
{
  LEPoint * pCurrent = nullptr;
  LEPoint * pNext = nullptr;

  if(this->pPointHead != nullptr)
  {
    pCurrent = this->pPointHead->pRight;

    while(pCurrent != this->pPointHead)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->zindex > pNext->zindex && pNext != this->pPointHead)
      {
        // ausklinken

        pCurrent->pLeft->pRight = pCurrent->pRight;
        pCurrent->pRight->pLeft = pCurrent->pLeft;

        // richtig einsortieren

        while(pCurrent->zindex > pNext->zindex && pNext != this->pPointHead)
          {pNext = pNext->pRight;}

        pCurrent->pLeft = pNext->pLeft;
        pCurrent->pRight = pNext;
        pNext->pLeft->pRight = pCurrent;
        pNext->pLeft = pCurrent;

        // start again

        pCurrent = this->pPointHead->pRight;       
      }
      else
        {pCurrent = pNext;}
    }
  }
}

bool LEMoon::pointFinishedAllMutexes(LEPoint * pPoint)
{
  bool finished = LE_TRUE;
  bool directionLocked = LE_FALSE;

  // find out if locked

  if(pPoint->direction.try_lock())
  {
    directionLocked = LE_TRUE;
    finished = finished && LE_TRUE;
  }
  else
    {finished = finished && LE_FALSE;}

  // unlock

  if(directionLocked)
    {pPoint->direction.unlock();}

  return finished;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public point
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::pointCreate(uint32_t id)
{
  this->mtxPoint.pointCreate.lock();
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint == nullptr)
    {pPoint = this->pointGetFromBuffer(id);}

  if(pPoint == nullptr)
  {
    this->mtxPoint.originalList.lock();

    if(this->pPointHead == nullptr)
    {
      this->pPointHead = new LEPoint;
      this->pPointHead->pLeft = this->pPointHead;
      this->pPointHead->pRight = this->pPointHead;
      this->pPointHead->id = 1989;
      this->pPointHead->zindex = 0;
    }

    this->mtxPoint.originalList.unlock();
    this->mtxPoint.bufferList.lock();

    if(this->pPointHeadBuffer == nullptr)
    {
      this->pPointHeadBuffer = new LEPoint;
      this->pPointHeadBuffer->pLeft = this->pPointHeadBuffer;
      this->pPointHeadBuffer->pRight = this->pPointHeadBuffer;
      this->pPointHeadBuffer->id = 28092017;
      this->pPointHeadBuffer->zindex = 0;
    }

    pPoint = new LEPoint;
    pPoint->pLeft = this->pPointHeadBuffer->pLeft;
    pPoint->pRight = this->pPointHeadBuffer;
    this->pPointHeadBuffer->pLeft->pRight = pPoint;
    this->pPointHeadBuffer->pLeft = pPoint;
    pPoint->id = id;
    pPoint->currentDegree = 0.0f;
    pPoint->visible = LE_TRUE;
    pPoint->pDirectionHead = nullptr;
    pPoint->posX = 0.0f;
    pPoint->posY = 0.0f;
    pPoint->point = {0, 0};
    pPoint->pointBuffer = {0, 0};
    pPoint->zindex = 1;
    pPoint->markedAsDelete = LE_FALSE;

    this->mtxPoint.bufferList.unlock();
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

  if(!result)
    {this->notifyPoint.notifyByEngine = LE_TRUE;}

  this->mtxPoint.pointCreate.unlock();
  return result;
}

int LEMoon::pointDelete(uint32_t id)
{
  this->mtxPoint.pointDelete.lock();
  int result = LE_NO_ERROR;
  LinkedVec2 * pCurrentDirection = nullptr;
  LinkedVec2 * pNextDirection = nullptr;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint == nullptr)
    {pPoint = this->pointGetFromBuffer(id);}

  if(pPoint != nullptr)
    {pPoint->markedAsDelete = LE_TRUE;}
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

  this->mtxPoint.pointDelete.unlock();
  return result;
}

int LEMoon::pointSetColor(uint32_t id, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  this->mtxPoint.pointSetColor.lock();
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint == nullptr)
    {pPoint = this->pointGetFromBuffer(id);}

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

  this->mtxPoint.pointSetColor.unlock();
  return result;
}

int LEMoon::pointSetPosition(uint32_t id, int x, int y)
{
  this->mtxPoint.pointSetPosition.lock();
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint == nullptr)
    {pPoint = this->pointGetFromBuffer(id);}

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

  this->mtxPoint.pointSetPosition.unlock();
  return result;
}

Color LEMoon::pointGetColor(uint32_t id)
{
  this->mtxPoint.pointGetColor.lock();
  Color color;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint == nullptr)
    {pPoint = this->pointGetFromBuffer(id);}

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

  this->mtxPoint.pointGetColor.unlock();
  return color;
}

int LEMoon::pointFade(uint32_t id, double alphaPerSecond)
{
  this->mtxPoint.pointFade.lock();
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint == nullptr)
    {pPoint = this->pointGetFromBuffer(id);}

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

  this->mtxPoint.pointFade.unlock();
  return result;
}

int LEMoon::pointRotate(uint32_t id, double degreePerSecond, SDL_Point rotationPoint)
{
  this->mtxPoint.pointRotate.lock();
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint == nullptr)
    {pPoint = this->pointGetFromBuffer(id);}

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

  this->mtxPoint.pointRotate.unlock();
  return result;
}

int LEMoon::pointSetVisible(uint32_t id, bool visible)
{
  this->mtxPoint.pointSetVisible.lock();
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint == nullptr)
    {pPoint = this->pointGetFromBuffer(id);}

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

  this->mtxPoint.pointSetVisible.unlock();
  return result;
}

int LEMoon::pointAddDirection(uint32_t id, uint32_t idDirection, glm::vec2 direction)
{
  this->mtxPoint.pointAddDirection.lock();
  int result = LE_NO_ERROR;
  LinkedVec2 * pDirection = nullptr;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint == nullptr)
    {pPoint = this->pointGetFromBuffer(id);}

  if(pPoint != nullptr)
  {
    pDirection = this->pointGetDirection(pPoint, idDirection);

    if(pDirection == nullptr)
    {
      pPoint->direction.lock();

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
      pPoint->direction.unlock();
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

  this->mtxPoint.pointAddDirection.unlock();
  return result;
}

int LEMoon::pointMoveDirection(uint32_t id, uint32_t idDirection)
{
  this->mtxPoint.pointMoveDirection.lock();
  int result = LE_NO_ERROR;
  LinkedVec2 * pDirection = nullptr;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint == nullptr)
    {pPoint = this->pointGetFromBuffer(id);}

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

  this->mtxPoint.pointMoveDirection.unlock();
  return result;
}

SDL_Point LEMoon::pointGetPosition(uint32_t id)
{
  this->mtxPoint.pointGetPosition.lock();
  SDL_Point position;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint == nullptr)
    {pPoint = this->pointGetFromBuffer(id);}

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

  this->mtxPoint.pointGetPosition.unlock();
  return position;
}

int LEMoon::pointSetZindex(uint32_t id, uint32_t zindex)
{
  this->mtxPoint.pointSetZindex.lock();
  int result = LE_NO_ERROR;
  LEPoint * pCurrent = nullptr;
  bool moreThanOneElement = this->pPointHead->pLeft->id != this->pPointHead->pRight->id;
  LEPoint * pElem = this->pointGet(id);

  if(pElem == nullptr)
  {
    pElem = this->pointGetFromBuffer(id);

    if(pElem != nullptr)
      {this->mtxPoint.bufferLockedBySetZindex = LE_TRUE;}
  }
  else
    {this->mtxPoint.originalLockedBySetZindex = LE_TRUE;}

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

      if(this->mtxPoint.originalLockedBySetZindex)
        {this->mtxPoint.originalList.lock();}
      if(this->mtxPoint.bufferLockedBySetZindex)
        {this->mtxPoint.bufferList.lock();}

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

      if(this->mtxPoint.originalLockedBySetZindex)
      {
        this->mtxPoint.originalList.unlock();
        this->mtxPoint.originalLockedBySetZindex = LE_FALSE;
      }

      if(this->mtxPoint.bufferLockedBySetZindex)
      {
        this->mtxPoint.bufferList.unlock();
        this->mtxPoint.bufferLockedBySetZindex = LE_FALSE;
      }
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

  this->mtxPoint.pointSetZindex.unlock();
  return result;
}

void LEMoon::pointUsingThread(bool flag)
{
  this->mtxPoint.pointUsingThread.lock();
  this->notifyPoint.notifyByUser = flag;
  this->mtxPoint.pointUsingThread.unlock();
}

void LEMoon::pointPrintList()
{
  this->mtxPoint.pointPrintList.lock();
  this->mtxPoint.originalList.lock();
  LEPoint * pCurrent = nullptr;

  if(this->pPointHead != nullptr)
  {
    pCurrent = this->pPointHead->pRight;

    if(pCurrent != nullptr)
    {
      printf("ORIGINAL: Head: %d", this->pPointHead->id);

      while(pCurrent != this->pPointHead)
      {
        printf(" <-> %d", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head: %d\n", this->pPointHead->id);
    }
  }

  this->mtxPoint.originalList.unlock();
  this->mtxPoint.pointPrintList.unlock();
}

void LEMoon::pointPrintBufferList()
{
  this->mtxPoint.pointPrintBufferList.lock();
  this->mtxPoint.bufferList.lock();
  LEPoint * pCurrent = nullptr;

  if(this->pPointHeadBuffer != nullptr)
  {
    pCurrent = this->pPointHeadBuffer->pRight;

    if(pCurrent != nullptr)
    {
      printf("BUFFER: Head: %d", this->pPointHeadBuffer->id);

      while(pCurrent != this->pPointHeadBuffer)
      {
        printf(" <-> %d", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head: %d\n", this->pPointHeadBuffer->id);
    }
  }

  this->mtxPoint.bufferList.unlock();
  this->mtxPoint.pointPrintBufferList.unlock();
}