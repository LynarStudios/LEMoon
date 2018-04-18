/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Visual Studio 2015 Community, g++ Compiler
  date:               11.04.2018
  updated:            18.04.2018

  NOTES:              bufferHead muss beim mergen auch komplett zerlegt und auf nullptr gesetzt werden, pLast muss auch auf nullptr gesetzt werden
*/

#include "../include/le_moon.h"

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// private font
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

LEFont * LEMoon::fontGet(uint32_t id)
{
  this->mtxFont.originalList.lock();
  LEFont * pRet = nullptr;
  LEFont * pCurrent = nullptr;

  // try original font list

  if(this->pFontHead != nullptr)
  {
    if(this->memory.pLastFont != nullptr && this->memory.pLastFont->id == id)
      {pRet = this->memory.pLastFont;}
    else
    {
      pCurrent = this->pFontHead->pRight;

      while(pCurrent != this->pFontHead)
      {
        if(pCurrent->id == id)
        {
          pRet = pCurrent;
          this->memory.pLastFont = pCurrent;
          break;
        }

        pCurrent = pCurrent->pRight;
      }
    }
  }

  this->mtxFont.originalList.unlock();
  return pRet;
}

LEFont * LEMoon::fontGetFromBuffer(uint32_t id)
{
  this->mtxFont.bufferList.lock();
  LEFont * pRet = nullptr;
  LEFont * pCurrent = nullptr;

  // try buffer font list
  
  if(this->pFontHeadBuffer != nullptr)
  {
    if(this->memory.pLastFont != nullptr && this->memory.pLastFont->id == id)
      {pRet = this->memory.pLastFont;}
    else
    {
      pCurrent = this->pFontHeadBuffer->pRight;

      while(pCurrent != this->pFontHeadBuffer)
      {
        if(pCurrent->id == id)
        {
          pRet = pCurrent;
          this->memory.pLastFont = pCurrent;
          break;
        }

        pCurrent = pCurrent->pRight;
      }
    }
  }

  this->mtxFont.bufferList.unlock();
  return pRet;
}

void LEMoon::fontCleanList()
{
  LEFont * pCurrent = nullptr;
  LEFont * pNext = nullptr;

  if(this->pFontHead != nullptr)
  {
    pCurrent = this->pFontHead->pRight;

    while(pCurrent != this->pFontHead)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->markedAsDelete)
      {
        pCurrent->pRight->pLeft = pCurrent->pLeft;
        pCurrent->pLeft->pRight = pCurrent->pRight;

        if(pCurrent->pFont != nullptr)
          {TTF_CloseFont(pCurrent->pFont);}

        delete pCurrent;
      }

      pCurrent = pNext;
    }
  }
}

void LEMoon::fontCleanBufferList()
{
  LEFont * pCurrent = nullptr;
  LEFont * pNext = nullptr;

  if(this->pFontHeadBuffer != nullptr)
  {
    pCurrent = this->pFontHeadBuffer->pRight;

    while(pCurrent != this->pFontHeadBuffer)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->markedAsDelete)
      {
        pCurrent->pRight->pLeft = pCurrent->pLeft;
        pCurrent->pLeft->pRight = pCurrent->pRight;

        if(pCurrent->pFont != nullptr)
          {TTF_CloseFont(pCurrent->pFont);}

        delete pCurrent;
      }

      pCurrent = pNext;
    }
  }
}

void LEMoon::fontDeleteBufferList()
{
  if(this->pFontHeadBuffer != nullptr)
  {
    this->pFontHeadBuffer->pLeft = this->pFontHeadBuffer;
    this->pFontHeadBuffer->pRight = this->pFontHeadBuffer;
    delete this->pFontHeadBuffer;
    this->pFontHeadBuffer = nullptr;
  }
}

int LEMoon::fontMerge()
{
  int result = LE_NO_ERROR;
  bool lockedAll = LE_FALSE;

  if(this->notifyFont.notifyByEngine && !this->notifyFont.notifyByUser)
  {
    // lock all

    if(this->mtxFont.fontCreateTTF.try_lock())
      {this->mtxFont.fontCreateTTFLockedByMerge = LE_TRUE;}
    if(this->mtxFont.fontDelete.try_lock())
      {this->mtxFont.fontDeleteLockedByMerge = LE_TRUE;}

    lockedAll = this->mtxFont.fontCreateTTFLockedByMerge && this->mtxFont.fontDeleteLockedByMerge;

    // delete (from both list), merge(buffer to original) and delete buffer

    if(lockedAll)
    {
      this->fontCleanList();
      this->fontCleanBufferList();
      this->fontMergeLists();
      this->fontDeleteBufferList();
      this->memory.pLastFont = nullptr;
      this->notifyFont.notifyByEngine = LE_FALSE;
    }

    // unlock all

    if(this->mtxFont.fontCreateTTFLockedByMerge)
      {this->mtxFont.fontCreateTTF.unlock();}
    if(this->mtxFont.fontDeleteLockedByMerge)
      {this->mtxFont.fontDelete.unlock();}

    this->mtxFont.fontCreateTTFLockedByMerge = LE_FALSE;
    this->mtxFont.fontDeleteLockedByMerge = LE_FALSE;
  }

  return result;
}

void LEMoon::fontConstructor()
{
  this->pFontHead = nullptr;
  this->pFontHeadBuffer = nullptr;

  this->notifyFont.notifyByEngine = LE_FALSE;
  this->notifyFont.notifyByUser = LE_FALSE;

  this->mtxFont.fontCreateTTFLockedByMerge = LE_FALSE;
  this->mtxFont.fontDeleteLockedByMerge = LE_FALSE;
}

void LEMoon::fontMergeLists()
{
  LEFont * pCurrent = nullptr;
  LEFont * pNext = nullptr;

  if(this->pFontHeadBuffer != nullptr)
  {
    pCurrent = this->pFontHeadBuffer->pRight;

    while(pCurrent != this->pFontHeadBuffer)
    {
      pNext = pCurrent->pRight;
      pCurrent->pRight = this->pFontHead;
      pCurrent->pLeft = this->pFontHead->pLeft;
      this->pFontHead->pLeft->pRight = pCurrent;
      this->pFontHead->pLeft = pCurrent;
      pCurrent = pNext;
    }
  }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public font
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::fontCreateTTF(uint32_t id, const char * pFile, int fontSize)
{
  this->mtxFont.fontCreateTTF.lock();
  int result = LE_NO_ERROR;
  LEFont * pNew = this->fontGet(id);

  if(pNew == nullptr)
    {pNew = this->fontGetFromBuffer(id);}

  if(pNew == nullptr)
  {
    this->mtxFont.originalList.lock();

    if(this->pFontHead == nullptr)
    {
      this->pFontHead = new LEFont;
      this->pFontHead->pLeft = this->pFontHead;
      this->pFontHead->pRight = this->pFontHead;
      this->pFontHead->id = 1989;
    }

    this->mtxFont.originalList.unlock();
    this->mtxFont.bufferList.lock();

    if(this->pFontHeadBuffer == nullptr)
    {
      this->pFontHeadBuffer = new LEFont;
      this->pFontHeadBuffer->pLeft = this->pFontHeadBuffer;
      this->pFontHeadBuffer->pRight = this->pFontHeadBuffer;
      this->pFontHeadBuffer->id = 28092017;
    }

    pNew = new LEFont;
    pNew->pLeft = this->pFontHeadBuffer->pLeft;
    pNew->pRight = this->pFontHeadBuffer;
    this->pFontHeadBuffer->pLeft->pRight = pNew;
    this->pFontHeadBuffer->pLeft = pNew;
    pNew->id = id;
    pNew->markedAsDelete = LE_FALSE;
    pNew->pFont = TTF_OpenFont(pFile, fontSize);

    if(pNew->pFont == nullptr)
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::fontCreateTTF(%u, %s, %d)\n\n", id, pFile, fontSize);
        this->printErrorDialog(LE_OPEN_FONT, pErrorString);
        delete [] pErrorString;
      #endif

      result = LE_OPEN_FONT;
    }

    this->mtxFont.bufferList.unlock();
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::fontCreateTTF(%u)\n\n", id);
      this->printErrorDialog(LE_FONT_EXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_FONT_EXIST;
  }

  if(!result)
    {this->notifyFont.notifyByEngine = LE_TRUE;}

  this->mtxFont.fontCreateTTF.unlock();
  return result;
}

int LEMoon::fontDelete(uint32_t id)
{
  this->mtxFont.fontDelete.lock();
  int result = LE_NO_ERROR;
  LEFont * pFont = this->fontGet(id);

  if(pFont == nullptr)
    {pFont = this->fontGetFromBuffer(id);}

  if(pFont != nullptr)
    {pFont->markedAsDelete = LE_TRUE;}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::fontDelete(%u)\n\n", id);
      this->printErrorDialog(LE_FONT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_FONT_NOEXIST;
  }

  if(!result)
    {this->notifyFont.notifyByEngine = LE_TRUE;}

  this->mtxFont.fontDelete.unlock();
  return result;
}

void LEMoon::fontPrintList()
{
  this->mtxFont.fontPrintList.lock();
  this->mtxFont.originalList.lock();
  LEFont * pCurrent = nullptr;

  if(this->pFontHead != nullptr)
  {
    pCurrent = this->pFontHead->pRight;

    if(pCurrent != nullptr)
    {
      printf("ORIGINAL: Head: %d", this->pFontHead->id);

      while(pCurrent != this->pFontHead)
      {
        printf(" <-> %d", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head: %d\n", this->pFontHead->id);
    }
  }

  this->mtxFont.originalList.unlock();
  this->mtxFont.fontPrintList.unlock();
}

void LEMoon::fontPrintBufferList()
{
  this->mtxFont.fontPrintBufferList.lock();
  this->mtxFont.bufferList.lock();
  LEFont * pCurrent = nullptr;

  if(this->pFontHeadBuffer != nullptr)
  {
    pCurrent = this->pFontHeadBuffer->pRight;

    if(pCurrent != nullptr)
    {
      printf("BUFFER: Head: %d", this->pFontHeadBuffer->id);

      while(pCurrent != this->pFontHeadBuffer)
      {
        printf(" <-> %d", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head: %d\n", this->pFontHeadBuffer->id);
    }
  }

  this->mtxFont.bufferList.unlock();
  this->mtxFont.fontPrintBufferList.unlock();
}

int LEMoon::fontSetStyle(uint32_t id, int style)
{
  this->mtxFont.fontSetStyle.lock();
  int result = LE_NO_ERROR;
  LEFont * pFont = this->fontGet(id);

  if(pFont == nullptr)
    {pFont = this->fontGetFromBuffer(id);}

  if(pFont != nullptr)
  {
    if(pFont->pFont != nullptr)
      {TTF_SetFontStyle(pFont->pFont, style);}
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::fontSetStyle(%u)\n\n", id);
      this->printErrorDialog(LE_FONT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_FONT_NOEXIST;
  }

  this->mtxFont.fontSetStyle.unlock();
  return result;
}

void LEMoon::fontUsingThread(bool flag)
{
  this->mtxFont.fontUsingThread.lock();
  this->notifyFont.notifyByUser = flag;
  this->mtxFont.fontUsingThread.unlock();
}