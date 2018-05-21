/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Visual Studio 2015 Community, g++ Compiler
  date:               12.04.2018
  updated:            21.05.2018
*/

#include "../include/le_moon.h"

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// private model
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::modelDraw(LEModel * pModel)
{
  int result = LE_NO_ERROR;

  if(pModel->visible)
    {result = pModel->pModel->mdlDrawActiveTexture(this->pRenderer);}

  if(result)
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelDraw(%u)\n\n", pModel->id);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return result;
}

LEModel * LEMoon::modelGet(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxModel.originalList);
  LEModel * pRet = nullptr;
  LEModel * pCurrent = nullptr;

  if(this->pModelHead != nullptr)
  {
    if(this->memory.pLastModel != nullptr && this->memory.pLastModel->id == id)
      {pRet = this->memory.pLastModel;}
    else
    {
      pCurrent = this->pModelHead->pRight;

      while(pCurrent != this->pModelHead)
      {
        if(pCurrent->id == id)
        {
          pRet = pCurrent;
          this->memory.pLastModel = pCurrent;
          break;
        }

        pCurrent = pCurrent->pRight;
      }
    }
  }

  return pRet;
}

LEModel * LEMoon::modelGetFromBuffer(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxModel.bufferList);
  LEModel * pRet = nullptr;
  LEModel * pCurrent = nullptr;

  if(this->pModelHeadBuffer != nullptr)
  {
    if(this->memory.pLastModel != nullptr && this->memory.pLastModel->id == id)
      {pRet = this->memory.pLastModel;}
    else
    {
      pCurrent = this->pModelHeadBuffer->pRight;

      while(pCurrent != this->pModelHeadBuffer)
      {
        if(pCurrent->id == id)
        {
          pRet = pCurrent;
          this->memory.pLastModel = pCurrent;
          break;
        }

        pCurrent = pCurrent->pRight;
      }
    }
  }

  return pRet;
}

uint32_t LEMoon::modelGetAmount()
{
  uint32_t amount = 0;
  LEModel * pCurrent = nullptr;

  if(this->pModelHead != nullptr)
  {
    pCurrent = this->pModelHead->pRight;

    while(pCurrent != this->pModelHead)
    {
      amount++;
      pCurrent = pCurrent->pRight;
    }
  }

  return amount;
}

bool LEMoon::modelCheckFrameBoxCollision(LEModel * pModel, LEModel * pForeignModel)
{
  return mathRectIntersection(pModel->pModel->mdlGetFrameBox(), pForeignModel->pModel->mdlGetFrameBox());
}

bool LEMoon::modelCheckCollision(LEModel * pModel, LEModel * pForeignModel)
{
  bool collided = LE_FALSE;
  CollisionRect * pModelCollisionRect = nullptr;
  CollisionRect * pForeignModelCollisionRect = nullptr;

  if(mathRectIntersection(pModel->pModel->mdlGetFrameBox(), pForeignModel->pModel->mdlGetFrameBox()))
  {
    pModelCollisionRect = pModel->pModel->pCollisionRectHead->pRight;
    pForeignModelCollisionRect = pForeignModel->pModel->pCollisionRectHead->pRight;

    while(pModelCollisionRect != pModel->pModel->pCollisionRectHead && pForeignModelCollisionRect != pForeignModel->pModel->pCollisionRectHead)
    {
      if(mathRectIntersection(pModelCollisionRect->collRectBuffer, pForeignModelCollisionRect->collRectBuffer))
      {
        collided = LE_TRUE;
        break;
      }

      pModelCollisionRect = pModelCollisionRect->pRight;
      pForeignModelCollisionRect = pForeignModelCollisionRect->pRight;
    }
  }

  return collided;
}

void LEMoon::modelCleanList()
{
  LEModel * pCurrent = nullptr;
  LEModel * pNext = nullptr;

  if(this->pModelHead != nullptr)
  {
    pCurrent = this->pModelHead->pRight;

    while(pCurrent != this->pModelHead)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->markedAsDelete && pCurrent->pModel->mdlFinishedAllMutexes())
      {
        pCurrent->pRight->pLeft = pCurrent->pLeft;
        pCurrent->pLeft->pRight = pCurrent->pRight;
        delete pCurrent->pModel;
        delete pCurrent;
      }

      pCurrent = pNext;
    }
  }
}

void LEMoon::modelCleanBufferList()
{
  LEModel * pCurrent = nullptr;
  LEModel * pNext = nullptr;

  if(this->pModelHeadBuffer != nullptr)
  {
    pCurrent = this->pModelHeadBuffer->pRight;

    while(pCurrent != this->pModelHeadBuffer)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->markedAsDelete && pCurrent->pModel->mdlFinishedAllMutexes())
      {
        pCurrent->pRight->pLeft = pCurrent->pLeft;
        pCurrent->pLeft->pRight = pCurrent->pRight;
        delete pCurrent->pModel;
        delete pCurrent;
      }

      pCurrent = pNext;
    }
  }
}

void LEMoon::modelConstructor()
{
  this->pModelHead = nullptr;
  this->pModelHeadBuffer = nullptr;

  this->notifyModel.notifyByEngine = LE_FALSE;
  this->notifyModel.notifyByUser = LE_FALSE;

  this->mtxModel.modelCreateLockedByMerge = LE_FALSE;
  this->mtxModel.modelDeleteLockedByMerge = LE_FALSE;
  this->mtxModel.modelSetZindexLockedByMerge = LE_FALSE;
}

void LEMoon::modelDeleteOriginalList()
{
  if(this->pModelHead != nullptr)
  {
    if(this->pModelHead->pLeft == this->pModelHead && this->pModelHead->pRight == this->pModelHead)
    {
      delete this->pModelHead;
      this->pModelHead = nullptr;
    }
  }
}

void LEMoon::modelDeleteBufferList()
{
  if(this->pModelHeadBuffer != nullptr)
  {
    if(this->pModelHeadBuffer->pLeft == this->pModelHeadBuffer && this->pModelHeadBuffer->pRight == this->pModelHeadBuffer)
    {
      delete this->pModelHeadBuffer;
      this->pModelHeadBuffer = nullptr;
    }
  }
}

void LEMoon::modelMergeLists()
{
  LEModel * pCurrent = nullptr;
  LEModel * pNext = nullptr;

  if(this->pModelHeadBuffer != nullptr)
  {
    pCurrent = this->pModelHeadBuffer->pRight;

    while(pCurrent != this->pModelHeadBuffer)
    {
      pNext = pCurrent->pRight;
      pCurrent->pLeft->pRight = pCurrent->pRight;
      pCurrent->pRight->pLeft = pCurrent->pLeft;
      pCurrent->pRight = this->pModelHead;
      pCurrent->pLeft = this->pModelHead->pLeft;
      this->pModelHead->pLeft->pRight = pCurrent;
      this->pModelHead->pLeft = pCurrent;
      pCurrent = pNext;
    }
  }
}

int LEMoon::modelMerge()
{
  int result = LE_NO_ERROR;
  bool lockedAll = LE_FALSE;

  if(this->notifyModel.notifyByEngine && !this->notifyModel.notifyByUser)
  {
    // lock all

    if(this->mtxModel.modelCreate.try_lock())
      {this->mtxModel.modelCreateLockedByMerge = LE_TRUE;}
    if(this->mtxModel.modelDelete.try_lock())
      {this->mtxModel.modelDeleteLockedByMerge = LE_TRUE;}
    if(this->mtxModel.modelSetZindex.try_lock())
      {this->mtxModel.modelSetZindexLockedByMerge = LE_TRUE;}

    lockedAll = this->mtxModel.modelCreateLockedByMerge && this->mtxModel.modelDeleteLockedByMerge && this->mtxModel.modelSetZindexLockedByMerge;

    // delete (from both list), merge(buffer to original) and delete buffer

    if(lockedAll)
    {
      this->modelCleanList();
      this->modelCleanBufferList();
      this->modelMergeLists();
      this->modelDeleteBufferList();
      this->modelDeleteOriginalList();
      this->modelSortZindex();
      this->memory.pLastModel = nullptr;
      this->notifyModel.notifyByEngine = LE_FALSE;
    }

    // unlock all

    if(this->mtxModel.modelCreateLockedByMerge)
      {this->mtxModel.modelCreate.unlock();}
    if(this->mtxModel.modelDeleteLockedByMerge)
      {this->mtxModel.modelDelete.unlock();}
    if(this->mtxModel.modelSetZindexLockedByMerge)
      {this->mtxModel.modelSetZindex.unlock();}

    this->mtxModel.modelCreateLockedByMerge = LE_FALSE;
    this->mtxModel.modelDeleteLockedByMerge = LE_FALSE;
    this->mtxModel.modelSetZindexLockedByMerge = LE_FALSE;
  }

  return result;
}

void LEMoon::modelSortZindex()
{
  LEModel * pCurrent = nullptr;
  LEModel * pNext = nullptr;

  if(this->pModelHead != nullptr)
  {
    pCurrent = this->pModelHead->pRight;

    while(pCurrent != this->pModelHead)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->zindex > pNext->zindex && pNext != this->pModelHead)
      {
        // ausklinken

        pCurrent->pLeft->pRight = pCurrent->pRight;
        pCurrent->pRight->pLeft = pCurrent->pLeft;

        // richtig einsortieren

        while(pCurrent->zindex > pNext->zindex && pNext != this->pModelHead)
          {pNext = pNext->pRight;}

        pCurrent->pLeft = pNext->pLeft;
        pCurrent->pRight = pNext;
        pNext->pLeft->pRight = pCurrent;
        pNext->pLeft = pCurrent;

        // start again

        pCurrent = this->pModelHead->pRight;       
      }
      else
        {pCurrent = pNext;}
    }
  }
}

uint32_t LEMoon::modelGenerateIDFromOriginalList()
{
  lock_guard<mutex> lockA(this->mtxModel.originalList);
  uint32_t id = 0;
  LEModel * pStart = nullptr;
  LEModel * pCurrent = nullptr;
  bool idNotFound = LE_FALSE;

  if(this->pModelHead != nullptr)
  {
    pStart = this->pModelHead->pRight;

    while(pStart != this->pModelHead)
    {
      id = pStart->id + 1;
      pCurrent = this->pModelHead->pRight;

      while(pCurrent != this->pModelHead)
      {
        if(id == pCurrent->id)
        {
          idNotFound = LE_TRUE;
          break;
        }

        pCurrent = pCurrent->pRight;
      }

      if(!idNotFound)
        {break;}
      else
        {idNotFound = LE_FALSE;}

      pStart = pStart->pRight;
    }
  }

  return id;
}

uint32_t LEMoon::modelGenerateIDFromBufferList()
{
  lock_guard<mutex> lockA(this->mtxModel.bufferList);

  uint32_t id = 0;
  LEModel * pStart = nullptr;
  LEModel * pCurrent = nullptr;
  bool idNotFound = LE_FALSE;

  if(this->pModelHeadBuffer != nullptr)
  {
    pStart = this->pModelHeadBuffer->pRight;

    while(pStart != this->pModelHeadBuffer)
    {
      id = pStart->id + 1;
      pCurrent = this->pModelHeadBuffer->pRight;

      while(pCurrent != this->pModelHeadBuffer)
      {
        if(id == pCurrent->id)
        {
          idNotFound = LE_TRUE;
          break;
        }

        pCurrent = pCurrent->pRight;
      }

      if(!idNotFound)
        {break;}
      else
        {idNotFound = LE_FALSE;}

      pStart = pStart->pRight;
    }
  }

  return id;
}

uint32_t LEMoon::modelGenerateID()
{
  uint32_t id;
  id = this->modelGenerateIDFromOriginalList();

  if(id == 0)
    {id = this->modelGenerateIDFromBufferList();}
  if(id == 0)
    {id = 1;}

  return id;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public model
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::modelCreate(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxModel.modelCreate);
  int result = LE_NO_ERROR;
  LEModel * pNew = this->modelGet(id);

  if(pNew == nullptr)
    {pNew = this->modelGetFromBuffer(id);}

  // element already exist?

  if(pNew == nullptr)
  {
    lock_guard<mutex> lockB(this->mtxModel.originalList);

    if(this->pModelHead == nullptr)
    {
      this->pModelHead = new LEModel;
      this->pModelHead->pLeft = this->pModelHead;
      this->pModelHead->pRight = this->pModelHead;
      this->pModelHead->pModel = nullptr;
      this->pModelHead->id = 1989;
      this->pModelHead->zindex = 0;
    }

    lock_guard<mutex> lockC(this->mtxModel.bufferList);

    if(this->pModelHeadBuffer == nullptr)
    {
      this->pModelHeadBuffer = new LEModel;
      this->pModelHeadBuffer->pLeft = this->pModelHeadBuffer;
      this->pModelHeadBuffer->pRight = this->pModelHeadBuffer;
      this->pModelHeadBuffer->id = 28092017;
      this->pModelHeadBuffer->zindex = 0;
    }

    pNew = new LEModel;
    pNew->pLeft = this->pModelHeadBuffer;
    pNew->pRight = this->pModelHeadBuffer->pRight;
    this->pModelHeadBuffer->pRight->pLeft = pNew;
    this->pModelHeadBuffer->pRight = pNew;
    pNew->id = id;
    pNew->zindex = 1;
    pNew->visible = LE_TRUE;
    pNew->markedAsDelete = LE_FALSE;
    pNew->pModel = new LEMdl();
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelCreate(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_EXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_EXIST;
  }

  if(!result)
    {this->notifyModel.notifyByEngine = LE_TRUE;}

  return result;
}

uint32_t LEMoon::modelCreate()
{
  lock_guard<mutex> lockA(this->mtxModel.modelCreate);
  uint32_t generatedID = this->modelGenerateID();
  LEModel * pNew = nullptr;

  lock_guard<mutex> lockB(this->mtxModel.originalList);

  if(this->pModelHead == nullptr)
  {
    this->pModelHead = new LEModel;
    this->pModelHead->pLeft = this->pModelHead;
    this->pModelHead->pRight = this->pModelHead;
    this->pModelHead->pModel = nullptr;
    this->pModelHead->id = 1989;
    this->pModelHead->zindex = 0;
  }

  lock_guard<mutex> lockC(this->mtxModel.bufferList);

  if(this->pModelHeadBuffer == nullptr)
  {
    this->pModelHeadBuffer = new LEModel;
    this->pModelHeadBuffer->pLeft = this->pModelHeadBuffer;
    this->pModelHeadBuffer->pRight = this->pModelHeadBuffer;
    this->pModelHeadBuffer->id = 28092017;
    this->pModelHeadBuffer->zindex = 0;
  }

  pNew = new LEModel;
  pNew->pLeft = this->pModelHeadBuffer;
  pNew->pRight = this->pModelHeadBuffer->pRight;
  this->pModelHeadBuffer->pRight->pLeft = pNew;
  this->pModelHeadBuffer->pRight = pNew;
  pNew->id = generatedID;
  pNew->zindex = 1;
  pNew->visible = LE_TRUE;
  pNew->markedAsDelete = LE_FALSE;
  pNew->pModel = new LEMdl();
  this->notifyModel.notifyByEngine = LE_TRUE;

  return generatedID;
}

int LEMoon::modelDelete(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxModel.modelDelete);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    pElem->markedAsDelete = LE_TRUE;
    this->notifyModel.notifyByEngine = LE_TRUE;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelDelete(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelCreateTexture(uint32_t id, uint32_t idTexture, const char * pFile)
{
  lock_guard<mutex> lockA(this->mtxModel.modelCreateTexture);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  #ifdef LE_DEBUG
    char * pErrorString = nullptr;
  #endif

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlCreateTexture(idTexture, pFile, this->pRenderer);

    #ifdef LE_DEBUG
      pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelCreateTexture(%u, %u, %s)\n\n", id, idTexture, pFile);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelCreateTexture(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelAddTextureSourceRect(uint32_t id, uint32_t idTexture, uint32_t idSrcRect, int x, int y, int w, int h)
{
  lock_guard<mutex> lockA(this->mtxModel.modelAddTextureSourceRect);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  #ifdef LE_DEBUG
    char * pErrorString = nullptr;
  #endif

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlAddTextureSourceRect(idTexture, idSrcRect, x, y, w, h);

    #ifdef LE_DEBUG
      pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelAddTextureSourceRect(%u, %u, %u, %d, %d, %d, %d)\n\n", id, idTexture, idSrcRect, x, y, w, h);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelAddTextureSourceRect(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelFocusTextureSourceRect(uint32_t id, uint32_t idTexture, uint32_t idSrcRect)
{
  lock_guard<mutex> lockA(this->mtxModel.modelFocusTextureSourceRect);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  #ifdef LE_DEBUG
    char * pErrorString = new char[256 + 1];
  #endif

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlFocusTextureSourceRect(idTexture, idSrcRect);

    #ifdef LE_DEBUG
      sprintf(pErrorString, "LEMoon::modelFocusTextureSourceRect(%u, %u, %u)\n\n", id, idTexture, idSrcRect);
      this->printErrorDialog(result, pErrorString);
    #endif
  }
  else
  {
    result = LE_MDL_NOEXIST;

    #ifdef LE_DEBUG
      sprintf(pErrorString, "LEMoon::modelFocusTextureSourceRect(%u)\n\n", id);
      this->printErrorDialog(result, pErrorString);
    #endif
  }

  #ifdef LE_DEBUG
    delete [] pErrorString;
  #endif

  return result;
}

int LEMoon::modelSetSize(uint32_t id, int w, int h)
{
  lock_guard<mutex> lockA(this->mtxModel.modelSetSize);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {pElem->pModel->mdlSetSize(w, h);}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelSetSize(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

double LEMoon::modelSetSize(uint32_t id, double percent)
{
  lock_guard<mutex> lockA(this->mtxModel.modelSetSize);
  double factor = 0.0f;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {factor = pElem->pModel->mdlSetSize(percent, this->displayMode.w);}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelSetSize(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return factor;
}

int LEMoon::modelSetZindex(uint32_t id, uint32_t zindex)
{
  lock_guard<mutex> lockA(this->mtxModel.modelSetZindex);
  int result = LE_NO_ERROR;
  LEModel * pCurrent = nullptr;
  bool moreThanOneElement = LE_FALSE;
  LEModel * pElem = this->modelGet(id);

  // not in original list! in buffer list?

  if(pElem == nullptr)
  {
    pElem = this->modelGetFromBuffer(id);

    if(pElem != nullptr)
      {pElem->zindex = zindex;}
    else
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::modelSetZindex(%u)\n\n", id);
        this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
        delete [] pErrorString;
      #endif
      
      result = LE_MDL_NOEXIST;
    }
  }
  else
  {
    // in original list! valid z-index?

    if(zindex == 0)
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::modelSetZindex(%u, %u)\n\n", id, zindex);
        this->printErrorDialog(LE_INVALID_ZINDEX, pErrorString);
        delete [] pErrorString;
      #endif

      result = LE_INVALID_ZINDEX;
    }

    // model head not nullptr?

    if(!result && this->pModelHead != nullptr)
    {
      moreThanOneElement = this->pModelHead->pLeft->id != this->pModelHead->pRight->id;

      // more than one element in original list?

      if(moreThanOneElement)
      {
        pElem->zindex = zindex;
        lock_guard<mutex> lockB(this->mtxModel.originalList);
        
        // exclude from list
        
        pElem->pLeft->pRight = pElem->pRight;
        pElem->pRight->pLeft = pElem->pLeft;
        
        // search right place for zindex
        
        pCurrent = this->pModelHead->pRight;
        
        while(pElem->zindex > pCurrent->zindex && pCurrent != this->pModelHead)
          {pCurrent = pCurrent->pRight;}
        
        // include at right postion
        
        pElem->pLeft = pCurrent->pLeft;
        pElem->pRight = pCurrent;
        pCurrent->pLeft->pRight = pElem;
        pCurrent->pLeft = pElem;
      }
      else
      {
        if(pElem != nullptr)
          {pElem->zindex = zindex;}
      }
    }
  }

  return result;
}

int LEMoon::modelSetTextureZindex(uint32_t id, uint32_t idTexture, uint32_t zindex)
{
  lock_guard<mutex> lockA(this->mtxModel.modelSetTextureZindex);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlSetTextureZindex(idTexture, zindex);

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelSetTextureZindex(%u, %u, %u)\n\n", id, idTexture, zindex);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelSetTextureZindex(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelSetTextureActive(uint32_t id, uint32_t idTexture, bool active)
{
  lock_guard<mutex> lockA(this->mtxModel.modelSetTextureActive);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlSetTextureActive(idTexture, active);

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelSetTextureActive(%u, %u, %d)\n\n", id, idTexture, active);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelSetTextureActive(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelSetPosition(uint32_t id, double x, double y)
{
  lock_guard<mutex> lockA(this->mtxModel.modelSetPosition);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {pElem->pModel->mdlSetPosition(x, y);}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelSetPosition(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelAddDirection(uint32_t id, uint32_t idDirection, glm::vec2 direction)
{
  lock_guard<mutex> lockA(this->mtxModel.modelAddDirection);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlAddDirection(idDirection, direction);

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelAddDirection(%u, %u, glm::vec2(%1.2f, %1.2f))\n\n", id, idDirection, direction.x, direction.y);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelAddDirection(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelMoveDirection(uint32_t id, uint32_t idDirection)
{
  lock_guard<mutex> lockA(this->mtxModel.modelMoveDirection);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlMoveDirection(idDirection, this->timestep);

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelMoveDirection(%u, %u)\n\n", id, idDirection);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelMoveDirection(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelRotate(uint32_t id, double ndegree)
{
  lock_guard<mutex> lockA(this->mtxModel.modelRotate);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {pElem->pModel->mdlRotate(ndegree, this->timestep);}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelRotate(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelRotateOnce(uint32_t id, double ndegree)
{
  lock_guard<mutex> lockA(this->mtxModel.modelRotateOnce);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {pElem->pModel->mdlRotateOnce(ndegree);}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelRotateOnce(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelSetTextureAlpha(uint32_t id, uint32_t idTexture, uint8_t alpha)
{
  lock_guard<mutex> lockA(this->mtxModel.modelSetTextureAlpha);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlSetTextureAlpha(idTexture, alpha);

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelSetTextureAlpha(%u, %u, %u)\n\n", id, idTexture, alpha);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelSetTextureAlpha(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelFadeTexture(uint32_t id, uint32_t idTexture, double alphaPerSecond)
{
  lock_guard<mutex> lockA(this->mtxModel.modelFadeTexture);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlFadeTexture(idTexture, alphaPerSecond, this->timestep);

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelFadeTexture(%u, %u, %1.2f)\n\n", id, idTexture, alphaPerSecond);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelFadeTexture(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelRotateDir(uint32_t id, uint32_t idDirection, double degree)
{
  lock_guard<mutex> lockA(this->mtxModel.modelRotateDir);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlRotateDir(idDirection, degree, this->timestep);

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelRotateDir(%u, %u, %1.2f)\n\n", id, idDirection, degree);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelRotateDir(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

SDL_Point LEMoon::modelGetSize(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxModel.modelGetSize);
  SDL_Point size;
  size.x = 0;
  size.y = 0;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {size = pElem->pModel->mdlGetSize();}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelGetSize(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return size;
}

SDL_Point LEMoon::modelGetPosition(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxModel.modelGetPosition);
  SDL_Point position;
  position.x = 0;
  position.y = 0;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {position = pElem->pModel->mdlGetPosition();}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelGetPosition(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return position;
}

glm::vec2 LEMoon::modelGetPositionD(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxModel.modelGetPositionD);
  glm::vec2 position;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {position = pElem->pModel->mdlGetPositionD();}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelGetPositionD(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return position;
}

double LEMoon::modelGetTextureAlpha(uint32_t id, uint32_t idTexture)
{
  lock_guard<mutex> lockA(this->mtxModel.modelGetTextureAlpha);
  double alpha = 0;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {alpha = pElem->pModel->mdlGetTextureAlpha(idTexture);}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelGetTextureAlpha(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return alpha;
}

int LEMoon::modelSetSizeFactor(uint32_t id, double nsizeFactor)
{
  lock_guard<mutex> lockA(this->mtxModel.modelSetSizeFactor);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {pElem->pModel->mdlSetSizeFactor(nsizeFactor);}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelSetSizeFactor(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

double LEMoon::modelGetSizeFactor(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxModel.modelGetSizeFactor);
  double sizeFactor = 0.0f;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {sizeFactor = pElem->pModel->mdlGetSizeFactor();}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelGetSizeFactor(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return sizeFactor;
}

int LEMoon::modelCreateSurface(uint32_t id, uint32_t idTexture, const char * pFile)
{
  lock_guard<mutex> lockA(this->mtxModel.modelCreateSurface);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlCreateSurface(idTexture, pFile);

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelCreateSurface(%u, %u, %s)\n\n", id, idTexture, pFile);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelCreateSurface(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelDeleteSurface(uint32_t id, uint32_t idTexture)
{
  lock_guard<mutex> lockA(this->mtxModel.modelDeleteSurface);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlDeleteSurface(idTexture);

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelDeleteSurface(%u, %u)\n\n", id, idTexture);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelDeleteSurface(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

SDL_Surface * LEMoon::modelGetSurface(uint32_t id, uint32_t idTexture)
{
  lock_guard<mutex> lockA(this->mtxModel.modelGetSurface);
  SDL_Surface * pSurface = nullptr;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {pSurface = pElem->pModel->mdlGetSurface(idTexture);}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelGetSurface(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return pSurface;
}

Color LEMoon::modelGetPixelRGBA(uint32_t id, uint32_t idTexture, uint32_t x, uint32_t y)
{
  lock_guard<mutex> lockA(this->mtxModel.modelGetPixelRGBA);
  Color pixel;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {pixel = pElem->pModel->mdlGetPixelRGBA(idTexture, x, y);}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelGetPixelRGBA(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return pixel;
}

glm::vec2 LEMoon::modelGetDirection(uint32_t id, uint32_t idDirection)
{
  lock_guard<mutex> lockA(this->mtxModel.modelGetDirection);
  glm::vec2 direction = {0.0f, 0.0f};
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {direction = pElem->pModel->mdlGetDirection(idDirection);}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelGetDirection(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return direction;
}

LECollBox_d LEMoon::modelGetFrameBox(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxModel.modelGetFrameBox);
  LECollBox_d frameBox;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {frameBox = pElem->pModel->mdlGetFrameBox();}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelGetFrameBox(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return frameBox;
}

LECollBox_d LEMoon::modelGetCollisionBox(uint32_t id, uint32_t idCollRect)
{
  lock_guard<mutex> lockA(this->mtxModel.modelGetCollisionBox);
  LECollBox_d collisionBox;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {collisionBox = pElem->pModel->mdlGetCollisionBox(idCollRect);}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelGetCollisionBox(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return collisionBox;
}

int LEMoon::modelChangeDirection(uint32_t id, uint32_t idDirection, glm::vec2 dir)
{
  lock_guard<mutex> lockA(this->mtxModel.modelChangeDirection);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlChangeDirection(idDirection, dir);

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelChangeDirection(%u, %u, glm::vec2(%1.2f, %1.2f))\n\n", id, idDirection, dir.x, dir.y);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelChangeDirection(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelSetVisible(uint32_t id, bool visible)
{
  lock_guard<mutex> lockA(this->mtxModel.modelSetVisible);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {pElem->visible = visible;}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelSetVisible(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelCreateClone(uint32_t id, uint32_t idClone)
{
  lock_guard<mutex> lockA(this->mtxModel.modelCreateClone);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlCreateClone(idClone);

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelCreateClone(%u, %u)\n\n", id, idClone);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelCreateClone(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelSetClonePosition(uint32_t id, uint32_t idClone, glm::vec2 position)
{
  lock_guard<mutex> lockA(this->mtxModel.modelSetClonePosition);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlSetClonePosition(idClone, position);

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelSetClonePosition(%u, %u, glm::vec2(%1.2f, %1.2f))\n\n", id, idClone, position.x, position.y);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelSetClonePosition(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelClearClones(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxModel.modelClearClones);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
    {pElem->pModel->mdlClearClones();}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelClearClones(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelSetCloneVisible(uint32_t id, uint32_t idClone, bool visible)
{
  lock_guard<mutex> lockA(this->mtxModel.modelSetCloneVisible);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlSetCloneVisible(idClone, visible);

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelSetCloneVisible(%u, %u, %d)\n\n", id, idClone, visible);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelSetCloneVisible(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelAddCollisionRect(uint32_t id, uint32_t idCollRect, SDL_Rect collRect)
{
  lock_guard<mutex> lockA(this->mtxModel.modelAddCollisionRect);
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem == nullptr)
    {pElem = this->modelGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlAddCollisionRect(idCollRect, collRect);

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelAddCollisionRect(%u, %u, {%d, %d, %d, %d})\n\n", id, idCollRect, collRect.x, collRect.y, collRect.w, collRect.h);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelAddCollisionRect(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

bool LEMoon::modelCheckFrameBoxCollision(uint32_t idModel, uint32_t idForeignModel)
{
  lock_guard<mutex> lockA(this->mtxModel.modelCheckFrameBoxCollision);
  bool collided = LE_FALSE;
  LEModel * pModel = this->modelGet(idModel);
  LEModel * pForeignModel = this->modelGet(idForeignModel);

  if(pModel == nullptr)
    {pModel = this->modelGetFromBuffer(idModel);}
  if(pForeignModel == nullptr)
    {pForeignModel = this->modelGetFromBuffer(idForeignModel);}

  if(pModel != nullptr && pForeignModel != nullptr)
    {collided = this->modelCheckFrameBoxCollision(pModel, pForeignModel);}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelCheckFrameBoxCollision(%u, %u)\n\n", idModel, idForeignModel);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return collided;
}

bool LEMoon::modelCheckCollision(uint32_t idModel, uint32_t idForeignModel)
{
  lock_guard<mutex> lockA(this->mtxModel.modelCheckCollision);
  bool collided = LE_FALSE;
  LEModel * pModel = this->modelGet(idModel);
  LEModel * pForeignModel = this->modelGet(idForeignModel);

  if(pModel == nullptr)
    {pModel = this->modelGetFromBuffer(idModel);}
  if(pForeignModel == nullptr)
    {pForeignModel = this->modelGetFromBuffer(idForeignModel);}

  if(pModel != nullptr && pForeignModel != nullptr)
    {collided = this->modelCheckCollision(pModel, pForeignModel);}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelCheckCollision(%u, %u)\n\n", idModel, idForeignModel);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return collided;
}

uint32_t LEMoon::modelGetAmountOfCollisionBoxes(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxModel.modelGetAmountOfCollisionBoxes);
  uint32_t amount = 0;
  LEModel * pModel = this->modelGet(id);

  if(pModel == nullptr)
    {pModel = this->modelGetFromBuffer(id);}

  if(pModel != nullptr)
    {amount = pModel->pModel->mdlGetAmountOfCollisionBoxes();}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelGetAmountOfCollisionBoxes(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return amount;
}

uint32_t LEMoon::modelGetAmountOfTextureSourceRectangles(uint32_t id, uint32_t idTexture)
{
  lock_guard<mutex> lockA(this->mtxModel.modelGetAmountOfTextureSourceRectangles);
  uint32_t amount = 0;
  LEModel * pModel = this->modelGet(id);

  if(pModel == nullptr)
    {pModel = this->modelGetFromBuffer(id);}

  if(pModel != nullptr)
    {amount = pModel->pModel->mdlGetAmountOfTextureSourceRectangles(idTexture);}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::modelGetAmountOfTextureSourceRectangles(%u)\n\n", id);
      this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return amount;
}

uint32_t LEMoon::modelGetZindex(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxModel.modelGetZindex);
  uint32_t zindex = 0;
  LEModel * pModel = this->modelGet(id);

  if(pModel == nullptr)
    {pModel = this->modelGetFromBuffer(id);}

  if(pModel != nullptr)
    {zindex = pModel->zindex;}

  return zindex;
}

bool LEMoon::modelTextureExists(uint32_t id, uint32_t idTexture)
{
  lock_guard<mutex> lockA(this->mtxModel.modelTextureExists);
  bool textureExist = LE_FALSE;
  LEModel * pModel = this->modelGet(id);

  if(pModel == nullptr)
    {pModel = this->modelGetFromBuffer(id);}

  if(pModel != nullptr)
    {textureExist = pModel->pModel->mdlTextureExist(idTexture);}

  return textureExist;
}

bool LEMoon::modelGetVisible(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxModel.modelGetVisible);
  bool visible = LE_FALSE;
  LEModel * pModel = this->modelGet(id);

  if(pModel == nullptr)
    {pModel = this->modelGetFromBuffer(id);}

  if(pModel != nullptr)
    {visible = pModel->visible;}

  return visible;
}

void LEMoon::modelUsingThread(bool flag)
{
  lock_guard<mutex> lockA(this->mtxModel.modelUsingThread);
  this->notifyModel.notifyByUser = flag;
}

void LEMoon::modelPrintList()
{
  lock_guard<mutex> lockA(this->mtxModel.modelPrintList);
  lock_guard<mutex> lockB(this->mtxModel.originalList);
  LEModel * pCurrent = nullptr;

  if(this->pModelHead != nullptr)
  {
    pCurrent = this->pModelHead->pRight;

    if(pCurrent != nullptr)
    {
      printf("ORIGINAL: Head (Model): %u", this->pModelHead->id);

      while(pCurrent != this->pModelHead)
      {
        printf(" <-> %u", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head (Model): %u\n\n", this->pModelHead->id);
    }
  }
}

void LEMoon::modelPrintBufferList()
{
  lock_guard<mutex> lockA(this->mtxModel.modelPrintBufferList);
  lock_guard<mutex> lockB(this->mtxModel.bufferList);
  LEModel * pCurrent = nullptr;

  if(this->pModelHeadBuffer != nullptr)
  {
    pCurrent = this->pModelHeadBuffer->pRight;

    if(pCurrent != nullptr)
    {
      printf("BUFFER (Model): Head: %u", this->pModelHeadBuffer->id);

      while(pCurrent != this->pModelHeadBuffer)
      {
        printf(" <-> %u", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head (Model): %u\n\n", this->pModelHeadBuffer->id);
    }
  }
}