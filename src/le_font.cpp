/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Visual Studio 2015 Community, g++ Compiler
  date:               11.04.2018
  updated:            21.05.2018
*/

#include "../include/le_moon.h"

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// private font
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

LEFont * LEMoon::fontGet(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxFont.originalList);
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

  return pRet;
}

LEFont * LEMoon::fontGetFromBuffer(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxFont.bufferList);
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
    if(this->pFontHeadBuffer->pLeft == this->pFontHeadBuffer && this->pFontHeadBuffer->pRight == this->pFontHeadBuffer)
    {
      delete this->pFontHeadBuffer;
      this->pFontHeadBuffer = nullptr;
    }
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
      this->fontDeleteOriginalList();
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
      pCurrent->pLeft->pRight = pCurrent->pRight;
      pCurrent->pRight->pLeft = pCurrent->pLeft;
      pCurrent->pRight = this->pFontHead;
      pCurrent->pLeft = this->pFontHead->pLeft;
      this->pFontHead->pLeft->pRight = pCurrent;
      this->pFontHead->pLeft = pCurrent;
      pCurrent = pNext;
    }
  }
}

void LEMoon::fontDeleteOriginalList()
{
  if(this->pFontHead != nullptr)
  {
    if(this->pFontHead->pLeft == this->pFontHead && this->pFontHead->pRight == this->pFontHead)
    {
      delete this->pFontHead;
      this->pFontHead = nullptr;
    }
  }
}

uint32_t LEMoon::fontGenerateIDFromOriginalList()
{
  lock_guard<mutex> lockA(this->mtxFont.originalList);
  uint32_t id = 0;
  LEFont * pStart = nullptr;
  LEFont * pCurrent = nullptr;
  bool idNotFound = LE_FALSE;

  if(this->pFontHead != nullptr)
  {
    pStart = this->pFontHead->pRight;

    while(pStart != this->pFontHead)
    {
      id = pStart->id + 1;
      pCurrent = this->pFontHead->pRight;

      while(pCurrent != this->pFontHead)
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

uint32_t LEMoon::fontGenerateIDFromBufferList()
{
  lock_guard<mutex> lockA(this->mtxFont.bufferList);
  uint32_t id = 0;
  LEFont * pStart = nullptr;
  LEFont * pCurrent = nullptr;
  bool idNotFound = LE_FALSE;

  if(this->pFontHeadBuffer != nullptr)
  {
    pStart = this->pFontHeadBuffer->pRight;

    while(pStart != this->pFontHeadBuffer)
    {
      id = pStart->id + 1;
      pCurrent = this->pFontHeadBuffer->pRight;

      while(pCurrent != this->pFontHeadBuffer)
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

uint32_t LEMoon::fontGenerateID()
{
  uint32_t id;
  id = this->fontGenerateIDFromOriginalList();

  if(id == 0)
    {id = this->fontGenerateIDFromBufferList();}
  if(id == 0)
    {id = 1;}

  return id;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public font
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::fontCreateTTF(uint32_t id, const char * pFile, int fontSize)
{
  lock_guard<mutex> lockA(this->mtxFont.fontCreateTTF);
  int result = LE_NO_ERROR;
  LEFont * pNew = this->fontGet(id);

  if(pNew == nullptr)
    {pNew = this->fontGetFromBuffer(id);}

  if(pNew == nullptr)
  {
    lock_guard<mutex> lockB(this->mtxFont.originalList);

    if(this->pFontHead == nullptr)
    {
      this->pFontHead = new LEFont;
      this->pFontHead->pLeft = this->pFontHead;
      this->pFontHead->pRight = this->pFontHead;
      this->pFontHead->id = 1989;
    }

    lock_guard<mutex> lockC(this->mtxFont.bufferList);

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

  return result;
}

uint32_t LEMoon::fontCreateTTF(const char * pFile, int fontSize)
{
  lock_guard<mutex> lockA(this->mtxFont.fontCreateTTF);
  uint32_t generatedID = this->fontGenerateID();
  LEFont * pNew = nullptr;

  lock_guard<mutex> lockB(this->mtxFont.originalList);

  if(this->pFontHead == nullptr)
  {
    this->pFontHead = new LEFont;
    this->pFontHead->pLeft = this->pFontHead;
    this->pFontHead->pRight = this->pFontHead;
    this->pFontHead->id = 1989;
  }

  lock_guard<mutex> lockC(this->mtxFont.bufferList);

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
  pNew->id = generatedID;
  pNew->markedAsDelete = LE_FALSE;
  pNew->pFont = TTF_OpenFont(pFile, fontSize);

  if(pNew->pFont == nullptr)
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::fontCreateTTF(%s, %d)\n\n", pFile, fontSize);
      this->printErrorDialog(LE_OPEN_FONT, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return generatedID;
}

int LEMoon::fontDelete(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxFont.fontDelete);
  int result = LE_NO_ERROR;
  LEFont * pFont = this->fontGet(id);

  if(pFont == nullptr)
    {pFont = this->fontGetFromBuffer(id);}

  if(pFont != nullptr)
  {
    pFont->markedAsDelete = LE_TRUE;
    this->notifyFont.notifyByEngine = LE_TRUE;
  }
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

  return result;
}

void LEMoon::fontPrintList()
{
  lock_guard<mutex> lockA(this->mtxFont.fontPrintList);
  lock_guard<mutex> lockB(this->mtxFont.originalList);
  LEFont * pCurrent = nullptr;

  if(this->pFontHead != nullptr)
  {
    pCurrent = this->pFontHead->pRight;

    if(pCurrent != nullptr)
    {
      printf("ORIGINAL: Head (Font): %u", this->pFontHead->id);

      while(pCurrent != this->pFontHead)
      {
        printf(" <-> %u", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head (Font): %u\n\n", this->pFontHead->id);
    }
  }
}

void LEMoon::fontPrintBufferList()
{
  lock_guard<mutex> lockA(this->mtxFont.fontPrintBufferList);
  lock_guard<mutex> lockB(this->mtxFont.bufferList);
  LEFont * pCurrent = nullptr;

  if(this->pFontHeadBuffer != nullptr)
  {
    pCurrent = this->pFontHeadBuffer->pRight;

    if(pCurrent != nullptr)
    {
      printf("BUFFER: Head (Font): %u", this->pFontHeadBuffer->id);

      while(pCurrent != this->pFontHeadBuffer)
      {
        printf(" <-> %u", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head (Font): %u\n\n", this->pFontHeadBuffer->id);
    }
  }
}

int LEMoon::fontSetStyle(uint32_t id, int style)
{
  lock_guard<mutex> lockA(this->mtxFont.fontSetStyle);
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

  return result;
}

void LEMoon::fontUsingThread(bool flag)
{
  lock_guard<mutex> lockA(this->mtxFont.fontUsingThread);
  this->notifyFont.notifyByUser = flag;
}
