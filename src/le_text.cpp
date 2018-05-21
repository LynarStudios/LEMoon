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
// private text
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::textDraw(LEText * pText)
{
  int result = LE_NO_ERROR;

  if(pText->visible && pText->alpha > 0.0f && pText->pTexture != nullptr)
  {
    if(SDL_RenderCopyEx(this->pRenderer, pText->pTexture, nullptr, &(pText->posSize), 0.0f, nullptr, SDL_FLIP_NONE))
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::textDraw(%u)\n\n", pText->id);
        this->printErrorDialog(LE_SDL_RENDER_COPY_EX, pErrorString);
        delete [] pErrorString;
      #endif

      result = LE_SDL_RENDER_COPY_EX;
    }
  }

  return result;
}

LEText * LEMoon::textGet(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxText.originalList);
  LEText * pRet = nullptr;
  LEText * pCurrent = nullptr;

  if(this->pTextHead != nullptr)
  {
    if(this->memory.pLastText != nullptr && this->memory.pLastText->id == id)
      {pRet = this->memory.pLastText;}
    else
    {
      pCurrent = this->pTextHead->pRight;

      while(pCurrent != this->pTextHead)
      {
        if(pCurrent->id == id)
        {
          pRet = pCurrent;
          this->memory.pLastText = pCurrent;
          break;
        }

        pCurrent = pCurrent->pRight;
      }
    }
  }

  return pRet;
}

LEText * LEMoon::textGetFromBuffer(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxText.bufferList);
  LEText * pRet = nullptr;
  LEText * pCurrent = nullptr;

  if(this->pTextHeadBuffer != nullptr)
  {
    if(this->memory.pLastText != nullptr && this->memory.pLastText->id == id)
      {pRet = this->memory.pLastText;}
    else
    {
      pCurrent = this->pTextHeadBuffer->pRight;

      while(pCurrent != this->pTextHeadBuffer)
      {
        if(pCurrent->id == id)
        {
          pRet = pCurrent;
          this->memory.pLastText = pCurrent;
          break;
        }

        pCurrent = pCurrent->pRight;
      }
    }
  }

  return pRet;
}

uint32_t LEMoon::textGetAmount()
{
  uint32_t amount = 0;
  LEText * pCurrent = nullptr;

  if(this->pTextHead != nullptr)
  {
    pCurrent = this->pTextHead->pRight;

    while(pCurrent != this->pTextHead)
    {
      amount++;
      pCurrent = pCurrent->pRight;
    }
  }

  return amount;
}

LinkedVec2 * LEMoon::textGetDirection(LEText * pText, uint32_t idDirection)
{
  lock_guard<mutex> lockA(pText->direction);
  LinkedVec2 * pRet = nullptr;
  LinkedVec2 * pCurrent = nullptr;

  if(pText->pDirectionHead != nullptr)
  {
    pCurrent = pText->pDirectionHead->pRight;

    while(pCurrent != pText->pDirectionHead)
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

void LEMoon::textCleanList()
{
  LEText * pCurrent = nullptr;
  LEText * pNext = nullptr;
  LinkedVec2 * pCurrentDirection = nullptr;
  LinkedVec2 * pNextDirection = nullptr;
  LELetter * pCurrentLetter = nullptr;
  LELetter * pNextLetter = nullptr;

  if(this->pTextHead != nullptr)
  {
    pCurrent = this->pTextHead->pRight;

    while(pCurrent != this->pTextHead)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->markedAsDelete && this->textFinishedAllMutexes(pCurrent))
      {
        // unlink

        pCurrent->pRight->pLeft = pCurrent->pLeft;
        pCurrent->pLeft->pRight = pCurrent->pRight;

        // delete directions

        if(pCurrent->pDirectionHead != nullptr)
        {
          pCurrentDirection = pCurrent->pDirectionHead->pRight;

          while(pCurrentDirection != pCurrent->pDirectionHead)
          {
            pNextDirection = pCurrentDirection->pRight;
            delete pCurrentDirection;
            pCurrentDirection = pNextDirection;
          }

          delete pCurrent->pDirectionHead;
          pCurrent->pDirectionHead = nullptr;
        }

        // delete letters

        if(pCurrent->pLetterHead != nullptr)
        {
          pCurrentLetter = pCurrent->pLetterHead->pRight;

          while(pCurrentLetter != pCurrent->pLetterHead)
          {
            pNextLetter = pCurrentLetter->pRight;
            delete pCurrentLetter;
            pCurrentLetter = pNextLetter;
          }

          delete pCurrent->pLetterHead;
          pCurrent->pLetterHead = nullptr;
        }

        // delete text

        if(pCurrent->pText != nullptr)
        {
          delete [] pCurrent->pText;
          pCurrent->pText = nullptr;
        }

        // delete texture

        if(pCurrent->pTexture != nullptr)
        {
          SDL_DestroyTexture(pCurrent->pTexture);
          pCurrent->pTexture = nullptr;
        }

        // delete whole element

        delete pCurrent;
      }

      pCurrent = pNext;
    }
  }
}

void LEMoon::textCleanBufferList()
{
  LEText * pCurrent = nullptr;
  LEText * pNext = nullptr;
  LinkedVec2 * pCurrentDirection = nullptr;
  LinkedVec2 * pNextDirection = nullptr;
  LELetter * pCurrentLetter = nullptr;
  LELetter * pNextLetter = nullptr;

  if(this->pTextHeadBuffer != nullptr)
  {
    pCurrent = this->pTextHeadBuffer->pRight;

    while(pCurrent != this->pTextHeadBuffer)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->markedAsDelete && this->textFinishedAllMutexes(pCurrent))
      {
        // unlink

        pCurrent->pRight->pLeft = pCurrent->pLeft;
        pCurrent->pLeft->pRight = pCurrent->pRight;

        // delete directions

        if(pCurrent->pDirectionHead != nullptr)
        {
          pCurrentDirection = pCurrent->pDirectionHead->pRight;

          while(pCurrentDirection != pCurrent->pDirectionHead)
          {
            pNextDirection = pCurrentDirection->pRight;
            delete pCurrentDirection;
            pCurrentDirection = pNextDirection;
          }

          delete pCurrent->pDirectionHead;
          pCurrent->pDirectionHead = nullptr;
        }

        // delete letters

        if(pCurrent->pLetterHead != nullptr)
        {
          pCurrentLetter = pCurrent->pLetterHead->pRight;

          while(pCurrentLetter != pCurrent->pLetterHead)
          {
            pNextLetter = pCurrentLetter->pRight;
            delete pCurrentLetter;
            pCurrentLetter = pNextLetter;
          }

          delete pCurrent->pLetterHead;
          pCurrent->pLetterHead = nullptr;
        }

        // delete text

        if(pCurrent->pText != nullptr)
        {
          delete [] pCurrent->pText;
          pCurrent->pText = nullptr;
        }

        // delete texture

        if(pCurrent->pTexture != nullptr)
        {
          SDL_DestroyTexture(pCurrent->pTexture);
          pCurrent->pTexture = nullptr;
        }

        // delete whole element

        delete pCurrent;
      }

      pCurrent = pNext;
    }
  }
}

void LEMoon::textConstructor()
{
  this->pTextHead = nullptr;
  this->pTextHeadBuffer = nullptr;

  this->notifyText.notifyByEngine = LE_FALSE;
  this->notifyText.notifyByUser = LE_FALSE;

  this->mtxText.textCreateLockedByMerge = LE_FALSE;
  this->mtxText.textDeleteLockedByMerge = LE_FALSE;
  this->mtxText.textSetZindexLockedByMerge = LE_FALSE;
}

void LEMoon::textDeleteOriginalList()
{
  if(this->pTextHead != nullptr)
  {
    if(this->pTextHead->pLeft == this->pTextHead && this->pTextHead->pRight == this->pTextHead)
    {
      delete this->pTextHead;
      this->pTextHead = nullptr;
    }
  }
}

void LEMoon::textDeleteBufferList()
{
  if(this->pTextHeadBuffer != nullptr)
  {
    if(this->pTextHeadBuffer->pLeft == this->pTextHeadBuffer && this->pTextHeadBuffer->pRight == this->pTextHeadBuffer)
    {
      delete this->pTextHeadBuffer;
      this->pTextHeadBuffer = nullptr;
    }
  }
}

void LEMoon::textMergeLists()
{
  LEText * pCurrent = nullptr;
  LEText * pNext = nullptr;

  if(this->pTextHeadBuffer != nullptr)
  {
    pCurrent = this->pTextHeadBuffer->pRight;

    while(pCurrent != this->pTextHeadBuffer)
    {
      pNext = pCurrent->pRight;
      pCurrent->pLeft->pRight = pCurrent->pRight;
      pCurrent->pRight->pLeft = pCurrent->pLeft;
      pCurrent->pRight = this->pTextHead;
      pCurrent->pLeft = this->pTextHead->pLeft;
      this->pTextHead->pLeft->pRight = pCurrent;
      this->pTextHead->pLeft = pCurrent;
      pCurrent = pNext;
    }
  }
}

int LEMoon::textMerge()
{
  int result = LE_NO_ERROR;
  bool lockedAll = LE_FALSE;

  if(this->notifyText.notifyByEngine && !this->notifyText.notifyByUser)
  {
    // lock all

    if(this->mtxText.textCreate.try_lock())
      {this->mtxText.textCreateLockedByMerge = LE_TRUE;}
    if(this->mtxText.textDelete.try_lock())
      {this->mtxText.textDeleteLockedByMerge = LE_TRUE;}
    if(this->mtxText.textSetZindex.try_lock())
      {this->mtxText.textSetZindexLockedByMerge = LE_TRUE;}

    lockedAll = this->mtxText.textCreateLockedByMerge && this->mtxText.textDeleteLockedByMerge && this->mtxText.textSetZindexLockedByMerge;

    // delete (from both list), merge(buffer to original) and delete buffer

    if(lockedAll)
    {
      this->textCleanList();
      this->textCleanBufferList();
      this->textMergeLists();
      this->textDeleteBufferList();
      this->textDeleteOriginalList();
      this->textSortZindex();
      this->memory.pLastText = nullptr;
      this->notifyText.notifyByEngine = LE_FALSE;
    }

    // unlock all

    if(this->mtxText.textCreateLockedByMerge)
      {this->mtxText.textCreate.unlock();}
    if(this->mtxText.textDeleteLockedByMerge)
      {this->mtxText.textDelete.unlock();}
    if(this->mtxText.textSetZindexLockedByMerge)
      {this->mtxText.textSetZindex.unlock();}

    this->mtxText.textCreateLockedByMerge = LE_FALSE;
    this->mtxText.textDeleteLockedByMerge = LE_FALSE;
    this->mtxText.textSetZindexLockedByMerge = LE_FALSE;
  }

  return result;
}

void LEMoon::textSortZindex()
{
  LEText * pCurrent = nullptr;
  LEText * pNext = nullptr;

  if(this->pTextHead != nullptr)
  {
    pCurrent = this->pTextHead->pRight;

    while(pCurrent != this->pTextHead)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->zindex > pNext->zindex && pNext != this->pTextHead)
      {
        // ausklinken

        pCurrent->pLeft->pRight = pCurrent->pRight;
        pCurrent->pRight->pLeft = pCurrent->pLeft;

        // richtig einsortieren

        while(pCurrent->zindex > pNext->zindex && pNext != this->pTextHead)
          {pNext = pNext->pRight;}

        pCurrent->pLeft = pNext->pLeft;
        pCurrent->pRight = pNext;
        pNext->pLeft->pRight = pCurrent;
        pNext->pLeft = pCurrent;

        // start again

        pCurrent = this->pTextHead->pRight;       
      }
      else
        {pCurrent = pNext;}
    }
  }
}

bool LEMoon::textFinishedAllMutexes(LEText * pText)
{
  bool finished = LE_TRUE;
  bool directionLocked = LE_FALSE;
  bool letterLocked = LE_FALSE;

  // find out if locked

  if(pText->direction.try_lock())
  {
    directionLocked = LE_TRUE;
    finished = finished && LE_TRUE;
  }
  else
    {finished = finished && LE_FALSE;}

  if(pText->letter.try_lock())
  {
    letterLocked = LE_TRUE;
    finished = finished && LE_TRUE;
  }
  else
    {finished = finished && LE_FALSE;}

  // unlock

  if(directionLocked)
    {pText->direction.unlock();}
  if(letterLocked)
    {pText->letter.unlock();}

  return finished;
}

uint32_t LEMoon::textGenerateIDFromOriginalList()
{
  lock_guard<mutex> lockA(this->mtxText.originalList);
  uint32_t id = 0;
  LEText * pStart = nullptr;
  LEText * pCurrent = nullptr;
  bool idNotFound = LE_FALSE;

  if(this->pTextHead != nullptr)
  {
    pStart = this->pTextHead->pRight;

    while(pStart != this->pTextHead)
    {
      id = pStart->id + 1;
      pCurrent = this->pTextHead->pRight;

      while(pCurrent != this->pTextHead)
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

uint32_t LEMoon::textGenerateIDFromBufferList()
{
  lock_guard<mutex> lockA(this->mtxText.bufferList);
  uint32_t id = 0;
  LEText * pStart = nullptr;
  LEText * pCurrent = nullptr;
  bool idNotFound = LE_FALSE;

  if(this->pTextHeadBuffer != nullptr)
  {
    pStart = this->pTextHeadBuffer->pRight;

    while(pStart != this->pTextHeadBuffer)
    {
      id = pStart->id + 1;
      pCurrent = this->pTextHeadBuffer->pRight;

      while(pCurrent != this->pTextHeadBuffer)
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

uint32_t LEMoon::textGenerateID()
{
  uint32_t id;
  id = this->textGenerateIDFromOriginalList();

  if(id == 0)
    {id = this->textGenerateIDFromBufferList();}
  if(id == 0)
    {id = 1;}

  return id;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public text
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::textCreate(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxText.textCreate);
  int result = LE_NO_ERROR;
  LEText * pNew = this->textGet(id);

  if(pNew == nullptr)
    {pNew = this->textGetFromBuffer(id);}

  if(pNew == nullptr)
  {
    lock_guard<mutex> lockB(this->mtxText.originalList);

    if(this->pTextHead == nullptr)
    {
      this->pTextHead = new LEText;
      this->pTextHead->pLeft = this->pTextHead;
      this->pTextHead->pRight = this->pTextHead;
      this->pTextHead->zindex = 0;
      this->pTextHead->id = 1989;
    }

    lock_guard<mutex> lockC(this->mtxText.bufferList);

    if(this->pTextHeadBuffer == nullptr)
    {
      this->pTextHeadBuffer = new LEText;
      this->pTextHeadBuffer->pLeft = this->pTextHeadBuffer;
      this->pTextHeadBuffer->pRight = this->pTextHeadBuffer;
      this->pTextHeadBuffer->zindex = 0;
      this->pTextHeadBuffer->id = 28092017;
    }

    pNew = new LEText;
    pNew->pRight = this->pTextHeadBuffer;
    pNew->pLeft = this->pTextHeadBuffer->pLeft;
    this->pTextHeadBuffer->pLeft->pRight = pNew;
    this->pTextHeadBuffer->pLeft = pNew;
    pNew->id = id;
    pNew->pCurrentCursorPosition = nullptr;
    pNew->pText = nullptr;
    pNew->length = 0;
    pNew->color = {255, 255, 255, 255};
    pNew->zindex = 1;
    pNew->visible = LE_TRUE;
    pNew->pFont = nullptr;
    pNew->pTexture = nullptr;
    pNew->alpha = 255;
    pNew->pLetterHead = nullptr;
    pNew->pDirectionHead = nullptr;
    pNew->position = glm::vec2(0.0f, 0.0f);
    pNew->markedAsDelete = LE_FALSE;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textCreate(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_EXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TEXT_EXIST;
  }

  if(!result)
    {this->notifyText.notifyByEngine = LE_TRUE;}

  return result;
}

uint32_t LEMoon::textCreate()
{
  lock_guard<mutex> lockA(this->mtxText.textCreate);
  uint32_t generatedID = this->textGenerateID();
  LEText * pNew = nullptr;

  lock_guard<mutex> lockB(this->mtxText.originalList);

  if(this->pTextHead == nullptr)
  {
    this->pTextHead = new LEText;
    this->pTextHead->pLeft = this->pTextHead;
    this->pTextHead->pRight = this->pTextHead;
    this->pTextHead->id = 1989;
    this->pTextHead->zindex = 0;
  }

  lock_guard<mutex> lockC(this->mtxText.bufferList);

  if(this->pTextHeadBuffer == nullptr)
  {
    this->pTextHeadBuffer = new LEText;
    this->pTextHeadBuffer->pLeft = this->pTextHeadBuffer;
    this->pTextHeadBuffer->pRight = this->pTextHeadBuffer;
    this->pTextHeadBuffer->id = 28092017;
    this->pTextHeadBuffer->zindex = 0;
  }

  pNew = new LEText;
  pNew->pRight = this->pTextHeadBuffer;
  pNew->pLeft = this->pTextHeadBuffer->pLeft;
  this->pTextHeadBuffer->pLeft->pRight = pNew;
  this->pTextHeadBuffer->pLeft = pNew;
  pNew->id = generatedID;
  pNew->pCurrentCursorPosition = nullptr;
  pNew->pText = nullptr;
  pNew->length = 0;
  pNew->color = {255, 255, 255, 255};
  pNew->zindex = 1;
  pNew->visible = LE_TRUE;
  pNew->pFont = nullptr;
  pNew->pTexture = nullptr;
  pNew->alpha = 255;
  pNew->pLetterHead = nullptr;
  pNew->pDirectionHead = nullptr;
  pNew->position = glm::vec2(0.0f, 0.0f);
  pNew->markedAsDelete = LE_FALSE;

  return generatedID;
}

int LEMoon::textDelete(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxText.textDelete);
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
  {
    pText->markedAsDelete = LE_TRUE;
    this->notifyText.notifyByEngine = LE_TRUE;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textDelete(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TEXT_NOEXIST;
  }

  return result;
}

int LEMoon::textAddLetter(uint32_t id, uint8_t letter)
{
  lock_guard<mutex> lockA(this->mtxText.textAddLetter);
  int result = LE_NO_ERROR;
  LELetter * pLetter = nullptr;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
  {
    lock_guard<mutex> lockB(pText->letter);

    if(pText->pLetterHead == nullptr)
    {
      pText->pLetterHead = new LELetter;
      pText->pLetterHead->pLeft = pText->pLetterHead;
      pText->pLetterHead->pRight = pText->pLetterHead;
    }

    pLetter = new LELetter;
    pLetter->pRight = pText->pLetterHead;
    pLetter->pLeft = pText->pLetterHead->pLeft;
    pText->pLetterHead->pLeft->pRight = pLetter;
    pText->pLetterHead->pLeft = pLetter;
    pLetter->letter = letter;
    pText->length += 1;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textAddLetter(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TEXT_NOEXIST;	
  }

  return result;
}

int LEMoon::textSubmit(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxText.textSubmit);
  int result = LE_NO_ERROR;
  uint32_t index = 0;
  LELetter * pLetter = nullptr;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
  {
    // erstelle einen Textbuffer

    if(pText->pText != nullptr)
    {
      delete [] pText->pText;
      pText->pText = nullptr;
    }

    lock_guard<mutex> lockB(pText->letter);
    pText->pText = new unsigned char[pText->length + 1];
    pLetter = pText->pLetterHead->pRight;

    // fuelle das Textfeld

    while(pLetter != pText->pLetterHead)
    {
      pText->pText[index] = (unsigned char) pLetter->letter;
      index++;
      pLetter = pLetter->pRight;
    }

    // null terminieren!

    pText->pText[index] = '\0';
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textSubmit(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TEXT_NOEXIST;	
  }

  return result;
}

int LEMoon::textSetColor(uint32_t id, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  lock_guard<mutex> lockA(this->mtxText.textSetColor);
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
    {pText->color = {r, g, b, a};}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textSetColor(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TEXT_NOEXIST;	
  }

  return result;
}

int LEMoon::textSetVisible(uint32_t id, bool visible)
{
  lock_guard<mutex> lockA(this->mtxText.textSetVisible);
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
    {pText->visible = visible;}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textSetVisible(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TEXT_NOEXIST;	
  }

  return result;
}

int LEMoon::textSetZindex(uint32_t id, uint32_t zindex)
{
  lock_guard<mutex> lockA(this->mtxText.textSetZindex);
  int result = LE_NO_ERROR;
  LEText * pCurrent = nullptr;
  bool moreThanOneElement = LE_FALSE;
  LEText * pElem = this->textGet(id);

  // not in original list! in buffer list?

  if(pElem == nullptr)
  {
    pElem = this->textGetFromBuffer(id);

    if(pElem != nullptr)
      {pElem->zindex = zindex;}
    else
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::textSetZindex(%u)\n\n", id);
        this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
        delete [] pErrorString;
      #endif
      
      result = LE_TEXT_NOEXIST;
    }
  }
  else
  {
    // in original list! valid z-index?

    if(zindex == 0)
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::textSetZindex(%u, %u)\n\n", id, zindex);
        this->printErrorDialog(LE_INVALID_ZINDEX, pErrorString);
        delete [] pErrorString;
      #endif

      result = LE_INVALID_ZINDEX;
    }

    // text head not nullptr?

    if(!result && this->pTextHead != nullptr)
    {
      moreThanOneElement = this->pTextHead->pLeft->id != this->pTextHead->pRight->id;

      // more than one element in original list?

      if(moreThanOneElement)
      {
        pElem->zindex = zindex;
        lock_guard<mutex> lockB(this->mtxText.originalList);
        
        // exclude from list
        
        pElem->pLeft->pRight = pElem->pRight;
        pElem->pRight->pLeft = pElem->pLeft;
        
        // search right place for zindex
        
        pCurrent = this->pTextHead->pRight;
        
        while(pElem->zindex > pCurrent->zindex && pCurrent != this->pTextHead)
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

int LEMoon::textRelateFont(uint32_t id, uint32_t idFont)
{
  lock_guard<mutex> lockA(this->mtxText.textRelateFont);
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);
  LEFont * pFont = this->fontGet(idFont);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}
  if(pFont == nullptr)
    {pFont = this->fontGetFromBuffer(idFont);}

  if(pText != nullptr)
  {
    if(pFont != nullptr)
      {pText->pFont = pFont;}
    else
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::textRelateFont(%u, %u)\n\n", id, idFont);
        this->printErrorDialog(LE_FONT_NOEXIST, pErrorString);
        delete [] pErrorString;
      #endif

      result = LE_FONT_NOEXIST;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textRelateFont(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TEXT_NOEXIST;
  }

  return result;
}

int LEMoon::textPrepareForDrawing(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxText.textPrepareForDrawing);
  int result = LE_NO_ERROR;
  SDL_Surface * pSurface = nullptr;
  SDL_Color color;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
  {
    if(pText->pText != nullptr)
    {
      if(pText->pFont != nullptr)
      {
        color = {pText->color.r, pText->color.g, pText->color.b, pText->color.a};
        pSurface = TTF_RenderUTF8_Blended(pText->pFont->pFont, (const char*) pText->pText, color);

        if(pSurface != nullptr)
        {
          if(pText->pTexture != nullptr)
            {SDL_DestroyTexture(pText->pTexture);}

          if(SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl"))
          {
            pText->posSize.w = pSurface->w;
            pText->posSize.h = pSurface->h;
            pText->pTexture = SDL_CreateTextureFromSurface(this->pRenderer, pSurface);
            SDL_FreeSurface(pSurface);

            if(pText->pTexture != nullptr)
            {
              if(SDL_SetTextureBlendMode(pText->pTexture, SDL_BLENDMODE_BLEND))
              {
                #ifdef LE_DEBUG
                  char * pErrorString = new char[256 + 1];
                  sprintf(pErrorString, "LEMoon::textPrepareForDrawing(%u)\n\n", id);
                  this->printErrorDialog(LE_SDL_BLENDMODE, pErrorString);
                  delete [] pErrorString;
                #endif

                result = LE_SDL_BLENDMODE;
              }
            }
            else
            {
              #ifdef LE_DEBUG
                char * pErrorString = new char[256 + 1];
                sprintf(pErrorString, "LEMoon::textPrepareForDrawing(%u)\n\n", id);
                this->printErrorDialog(LE_SDL_TEXTURE_LOAD, pErrorString);
                delete [] pErrorString;
              #endif

              result = LE_SDL_TEXTURE_LOAD;
            }
          }
          else
          {
            #ifdef LE_DEBUG
              char * pErrorString = new char[256 + 1];
              sprintf(pErrorString, "LEMoon::textPrepareForDrawing(%u)\n\n", id);
              this->printErrorDialog(LE_SDL_HINT, pErrorString);
              delete [] pErrorString;
            #endif

            result = LE_SDL_HINT;
          }
        }
        else
        {
          #ifdef LE_DEBUG
            char * pErrorString = new char[256 + 1];
            sprintf(pErrorString, "LEMoon::textPrepareForDrawing(%u)\n\n", id);
            this->printErrorDialog(LE_RENDER_TEXT_BLENDED, pErrorString);
            delete [] pErrorString;
          #endif

          result = LE_RENDER_TEXT_BLENDED;
        }
      }
      else
      {
        #ifdef LE_DEBUG
          char * pErrorString = new char[256 + 1];
          sprintf(pErrorString, "LEMoon::textPrepareForDrawing(%u)\n\n", id);
          this->printErrorDialog(LE_TEXT_RELATE_FONT, pErrorString);
          delete [] pErrorString;
        #endif

        result = LE_TEXT_RELATE_FONT;
      }
    }
    else
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::textPrepareForDrawing(%u)\n\n", id);
        this->printErrorDialog(LE_TEXT_NOSUBMIT, pErrorString);
        delete [] pErrorString;
      #endif

      result = LE_TEXT_NOSUBMIT;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textPrepareForDrawing(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TEXT_NOEXIST;
  }

  return result;
}

int LEMoon::textSetPosition(uint32_t id, int x, int y)
{
  lock_guard<mutex> lockA(this->mtxText.textSetPosition);
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
  {
    pText->posSize.x = x;
    pText->posSize.y = y;
    pText->position.x = (float) x;
    pText->position.y = (float) y;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textSetPosition(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TEXT_NOEXIST;
  }

  return result;
}

int LEMoon::textAddString(uint32_t id, const char * pString)
{
  lock_guard<mutex> lockA(this->mtxText.textAddString);
  int result = LE_NO_ERROR;
  uint32_t index = 0;
  LELetter * pLetter = nullptr;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
  {
    lock_guard<mutex> lockB(pText->letter);

    while(pString[index] != '\0')
    {
      if(pText->pLetterHead == nullptr)
      {
        pText->pLetterHead = new LELetter;
        pText->pLetterHead->pLeft = pText->pLetterHead;
        pText->pLetterHead->pRight = pText->pLetterHead;
      }

      pLetter = new LELetter;
      pLetter->pRight = pText->pLetterHead;
      pLetter->pLeft = pText->pLetterHead->pLeft;
      pText->pLetterHead->pLeft->pRight = pLetter;
      pText->pLetterHead->pLeft = pLetter;
      pLetter->letter = pString[index];
      pText->length += 1;
      index++;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textAddString(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TEXT_NOEXIST;
  }

  return result;
}

int LEMoon::textSetAlpha(uint32_t id, uint8_t alpha)
{
  lock_guard<mutex> lockA(this->mtxText.textSetAlpha);
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
  {
    pText->alpha = (double) alpha;

    if(SDL_SetTextureAlphaMod(pText->pTexture, (uint8_t) pText->alpha))
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::textSetAlpha(%u, %u)\n\n", id, alpha);
        this->printErrorDialog(LE_ALPHA_MOD, pErrorString);
        delete [] pErrorString;
      #endif

      result = LE_ALPHA_MOD;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textSetAlpha(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TEXT_NOEXIST;
  }

  return result;
}

int LEMoon::textFade(uint32_t id, double alphaPerSecond)
{
  lock_guard<mutex> lockA(this->mtxText.textFade);
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
  {
    pText->alpha += (alphaPerSecond * this->timestep);

    if(pText->alpha <= 0.0f)
      {pText->alpha = 0.0f;}

    if(pText->alpha >= 255.0f)
      {pText->alpha = 255.0f;}

    if(SDL_SetTextureAlphaMod(pText->pTexture, (uint8_t) pText->alpha))
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::textFade(%u, %1.2f)\n\n", id, alphaPerSecond);
        this->printErrorDialog(LE_ALPHA_MOD, pErrorString);
        delete [] pErrorString;
      #endif

      result = LE_ALPHA_MOD;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textFade(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TEXT_NOEXIST;
  }

  return result;
}

int LEMoon::textClear(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxText.textClear);
  int result = LE_NO_ERROR;
  LELetter * pLetter = nullptr;
  LELetter * pNextLetter = nullptr;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
  {
    // loesche Text

    if(pText->pText != nullptr)
    {
      delete [] pText->pText;
      pText->pText = nullptr;
    }

    // loesche Buchstaben

    lock_guard<mutex> lockB(pText->letter);
    pLetter = pText->pLetterHead->pRight;

    while(pLetter != pText->pLetterHead)
    {
      pNextLetter = pLetter->pRight;
      delete pLetter;
      pLetter = pNextLetter;
    }

    pText->pLetterHead->pLeft = pText->pLetterHead;
    pText->pLetterHead->pRight = pText->pLetterHead;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textClear(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TEXT_NOEXIST;
  }

  return result;
}

double LEMoon::textGetAlpha(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxText.textGetAlpha);
  double alpha = 0.0f;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
    {alpha = pText->alpha;}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textGetAlpha(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return alpha;
}

int LEMoon::textAddDirection(uint32_t id, uint32_t idDirection, glm::vec2 direction)
{
  lock_guard<mutex> lockA(this->mtxText.textAddDirection);
  int result = LE_NO_ERROR;
  LinkedVec2 * pNew = nullptr;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
  {
    pNew = this->textGetDirection(pText, idDirection);

    if(pNew == nullptr)
    {
      lock_guard<mutex> lockB(pText->direction);

      if(pText->pDirectionHead == nullptr)
      {
        pText->pDirectionHead = new LinkedVec2;
        pText->pDirectionHead->pLeft = pText->pDirectionHead;
        pText->pDirectionHead->pRight = pText->pDirectionHead;
      }

      pNew = new LinkedVec2;
      pNew->pRight = pText->pDirectionHead;
      pNew->pLeft = pText->pDirectionHead->pLeft;
      pText->pDirectionHead->pLeft->pRight = pNew;
      pText->pDirectionHead->pLeft = pNew;
      pNew->id = idDirection;
      pNew->currentDegree = 0.0f;
      pNew->data = direction;
    }
    else
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::textAddDirection(%u, %u, glm::vec2(%1.2f, %1.2f))\n\n", id, idDirection, direction.x, direction.y);
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
      sprintf(pErrorString, "LEMoon::textAddDirection(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TEXT_NOEXIST;
  }

  return result;
}

int LEMoon::textMoveDirection(uint32_t id, uint32_t idDirection)
{
  lock_guard<mutex> lockA(this->mtxText.textMoveDirection);
  int result = LE_NO_ERROR;
  LinkedVec2 * pDirection = nullptr;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
  {
    pDirection = this->textGetDirection(pText, idDirection);

    if(pDirection != nullptr)
    {
      pText->position.x += (float)(pDirection->data.x * this->timestep);
      pText->position.y += (float)(pDirection->data.y * this->timestep);
      pText->posSize.x = (int) pText->position.x;
      pText->posSize.y = (int) pText->position.y;
    }
    else
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::textMoveDirection(%u, %u)\n\n", id, idDirection);
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
      sprintf(pErrorString, "LEMoon::textMoveDirection(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TEXT_NOEXIST;
  }

  return result;
}

SDL_Point LEMoon::textGetPosition(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxText.textGetPosition);
  SDL_Point pos;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
  {
    pos.x = pText->posSize.x;
    pos.y = pText->posSize.y;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textGetPosition(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return pos;
}

SDL_Point LEMoon::textGetSize(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxText.textGetSize);
  SDL_Point size;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
  {
    size.x = pText->posSize.w;
    size.y = pText->posSize.h;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::textGetSize(%u)\n\n", id);
      this->printErrorDialog(LE_TEXT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return size;
}

bool LEMoon::textGetVisible(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxText.textGetVisible);
  bool visible = LE_FALSE;
  LEText * pText = this->textGet(id);

  if(pText == nullptr)
    {pText = this->textGetFromBuffer(id);}

  if(pText != nullptr)
    {visible = pText->visible;}

  return visible;
}

void LEMoon::textUsingThread(bool flag)
{
  lock_guard<mutex> lockA(this->mtxText.textUsingThread);
  this->notifyText.notifyByUser = flag;
}

void LEMoon::textPrintList()
{
  lock_guard<mutex> lockA(this->mtxText.textPrintList);
  lock_guard<mutex> lockB(this->mtxText.originalList);
  LEText * pCurrent = nullptr;

  if(this->pTextHead != nullptr)
  {
    pCurrent = this->pTextHead->pRight;

    if(pCurrent != nullptr)
    {
      printf("ORIGINAL: Head (Text): %u", this->pTextHead->id);

      while(pCurrent != this->pTextHead)
      {
        printf(" <-> %u", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head (Text): %u\n\n", this->pTextHead->id);
    }
  }
}

void LEMoon::textPrintBufferList()
{
  lock_guard<mutex> lockA(this->mtxText.textPrintBufferList);
  lock_guard<mutex> lockB(this->mtxText.bufferList);
  LEText * pCurrent = nullptr;

  if(this->pTextHeadBuffer != nullptr)
  {
    pCurrent = this->pTextHeadBuffer->pRight;

    if(pCurrent != nullptr)
    {
      printf("BUFFER: Head (Text): %u", this->pTextHeadBuffer->id);

      while(pCurrent != this->pTextHeadBuffer)
      {
        printf(" <-> %u", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head (Text): %u\n\n", this->pTextHeadBuffer->id);
    }
  }
}