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
// private sound
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

LESound * LEMoon::soundGet(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxSound.originalList);
  LESound * pRet = nullptr;
  LESound * pCurrent = nullptr;

  if(this->pSoundHead != nullptr)
  {
    if(this->memory.pLastSound != nullptr && this->memory.pLastSound->id == id)
      {pRet = this->memory.pLastSound;}
    else
    {
      pCurrent = this->pSoundHead->pRight;

      while(pCurrent != this->pSoundHead)
      {
        if(pCurrent->id == id)
        {
          pRet = pCurrent;
          this->memory.pLastSound = pCurrent;
          break;
        }

        pCurrent = pCurrent->pRight;
      }
    }
  }

  return pRet;
}

LESound * LEMoon::soundGetFromBuffer(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxSound.bufferList);
  LESound * pRet = nullptr;
  LESound * pCurrent = nullptr;

  if(this->pSoundHeadBuffer != nullptr)
  {
    if(this->memory.pLastSound != nullptr && this->memory.pLastSound->id == id)
      {pRet = this->memory.pLastSound;}
    else
    {
      pCurrent = this->pSoundHeadBuffer->pRight;

      while(pCurrent != this->pSoundHeadBuffer)
      {
        if(pCurrent->id == id)
        {
          pRet = pCurrent;
          this->memory.pLastSound = pCurrent;
          break;
        }

        pCurrent = pCurrent->pRight;
      }
    }
  }

  return pRet;
}

int LEMoon::soundMerge()
{
  int result = LE_NO_ERROR;
  bool lockedAll = LE_FALSE;

  if(this->notifySound.notifyByEngine && !this->notifySound.notifyByUser)
  {
    // lock all

    if(this->mtxSound.soundCreate.try_lock())
      {this->mtxSound.soundCreateLockedByMerge = LE_TRUE;}
    if(this->mtxSound.soundDelete.try_lock())
      {this->mtxSound.soundDeleteLockedByMerge = LE_TRUE;}

    lockedAll = this->mtxSound.soundCreateLockedByMerge && this->mtxSound.soundDeleteLockedByMerge;

    // delete (from both list), merge(buffer to original) and delete buffer

    if(lockedAll)
    {
      this->soundCleanList();
      this->soundCleanBufferList();
      this->soundMergeLists();
      this->soundDeleteBufferList();
      this->soundDeleteOriginalList();
      this->memory.pLastSound = nullptr;
      this->notifySound.notifyByEngine = LE_FALSE;
    }

    // unlock all

    if(this->mtxSound.soundCreateLockedByMerge)
      {this->mtxSound.soundCreate.unlock();}
    if(this->mtxSound.soundDeleteLockedByMerge)
      {this->mtxSound.soundDelete.unlock();}

    this->mtxSound.soundCreateLockedByMerge = LE_FALSE;
    this->mtxSound.soundDeleteLockedByMerge = LE_FALSE;
  }

  return result;
}

void LEMoon::soundConstructor()
{
  this->pSoundHead = nullptr;
  this->pSoundHeadBuffer = nullptr;

  this->notifySound.notifyByEngine = LE_FALSE;
  this->notifySound.notifyByUser = LE_FALSE;

  this->mtxSound.soundCreateLockedByMerge = LE_FALSE;
  this->mtxSound.soundDeleteLockedByMerge = LE_FALSE;
}

void LEMoon::soundMergeLists()
{
  LESound * pCurrent = nullptr;
  LESound * pNext = nullptr;

  if(this->pSoundHeadBuffer != nullptr)
  {
    pCurrent = this->pSoundHeadBuffer->pRight;

    while(pCurrent != this->pSoundHeadBuffer)
    {
      pNext = pCurrent->pRight;
      pCurrent->pLeft->pRight = pCurrent->pRight;
      pCurrent->pRight->pLeft = pCurrent->pLeft;
      pCurrent->pRight = this->pSoundHead;
      pCurrent->pLeft = this->pSoundHead->pLeft;
      this->pSoundHead->pLeft->pRight = pCurrent;
      this->pSoundHead->pLeft = pCurrent;
      pCurrent = pNext;
    }
  }
}

void LEMoon::soundCleanList()
{
  LESound * pCurrent = nullptr;
  LESound * pNext = nullptr;

  if(this->pSoundHead != nullptr)
  {
    pCurrent = this->pSoundHead->pRight;

    while(pCurrent != this->pSoundHead)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->markedAsDelete)
      {
        pCurrent->pRight->pLeft = pCurrent->pLeft;
        pCurrent->pLeft->pRight = pCurrent->pRight;

        if(pCurrent->pSample != nullptr)
          {Mix_FreeChunk(pCurrent->pSample);}

        delete pCurrent;
      }

      pCurrent = pNext;
    }
  }
}

void LEMoon::soundCleanBufferList()
{
  LESound * pCurrent = nullptr;
  LESound * pNext = nullptr;

  if(this->pSoundHeadBuffer != nullptr)
  {
    pCurrent = this->pSoundHeadBuffer->pRight;

    while(pCurrent != this->pSoundHeadBuffer)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->markedAsDelete)
      {
        pCurrent->pRight->pLeft = pCurrent->pLeft;
        pCurrent->pLeft->pRight = pCurrent->pRight;

        if(pCurrent->pSample != nullptr)
          {Mix_FreeChunk(pCurrent->pSample);}

        delete pCurrent;
      }

      pCurrent = pNext;
    }
  }
}

void LEMoon::soundDeleteOriginalList()
{
  if(this->pSoundHead != nullptr)
  {
    if(this->pSoundHead->pLeft == this->pSoundHead && this->pSoundHead->pRight == this->pSoundHead)
    {
      delete this->pSoundHead;
      this->pSoundHead = nullptr;
    }
  }
}

void LEMoon::soundDeleteBufferList()
{
  if(this->pSoundHeadBuffer != nullptr)
  {
    if(this->pSoundHeadBuffer->pLeft == this->pSoundHeadBuffer && this->pSoundHeadBuffer->pRight == this->pSoundHeadBuffer)
    {
      delete this->pSoundHeadBuffer;
      this->pSoundHeadBuffer = nullptr;
    }
  }
}

uint32_t LEMoon::soundGenerateIDFromOriginalList()
{
  lock_guard<mutex> lockA(this->mtxSound.originalList);
  uint32_t id = 0;
  LESound * pStart = nullptr;
  LESound * pCurrent = nullptr;
  bool idNotFound = LE_FALSE;

  if(this->pSoundHead != nullptr)
  {
    pStart = this->pSoundHead->pRight;

    while(pStart != this->pSoundHead)
    {
      id = pStart->id + 1;
      pCurrent = this->pSoundHead->pRight;

      while(pCurrent != this->pSoundHead)
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

uint32_t LEMoon::soundGenerateIDFromBufferList()
{
  lock_guard<mutex> lockA(this->mtxSound.bufferList);
  uint32_t id = 0;
  LESound * pStart = nullptr;
  LESound * pCurrent = nullptr;
  bool idNotFound = LE_FALSE;

  if(this->pSoundHeadBuffer != nullptr)
  {
    pStart = this->pSoundHeadBuffer->pRight;

    while(pStart != this->pSoundHeadBuffer)
    {
      id = pStart->id + 1;
      pCurrent = this->pSoundHeadBuffer->pRight;

      while(pCurrent != this->pSoundHeadBuffer)
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

uint32_t LEMoon::soundGenerateID()
{
  uint32_t id;
  id = this->soundGenerateIDFromOriginalList();

  if(id == 0)
    {id = this->soundGenerateIDFromBufferList();}
  if(id == 0)
    {id = 1;}

  return id;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public sound
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::soundCreate(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxSound.soundCreate);
  int result = LE_NO_ERROR;
  LESound * pNew = this->soundGet(id);

  if(pNew == nullptr)
    {pNew = this->soundGetFromBuffer(id);}

  if(pNew == nullptr)
  {
    lock_guard<mutex> lockB(this->mtxSound.originalList);

    if(this->pSoundHead == nullptr)
    {
      this->pSoundHead = new LESound;
      this->pSoundHead->pLeft = this->pSoundHead;
      this->pSoundHead->pRight = this->pSoundHead;
      this->pSoundHead->id = 1989;
    }

    lock_guard<mutex> lockC(this->mtxSound.bufferList);

    if(this->pSoundHeadBuffer == nullptr)
    {
      this->pSoundHeadBuffer = new LESound;
      this->pSoundHeadBuffer->pLeft = this->pSoundHeadBuffer;
      this->pSoundHeadBuffer->pRight = this->pSoundHeadBuffer;
      this->pSoundHeadBuffer->id = 28092017;
    }

    pNew = new LESound;
    pNew->pLeft = this->pSoundHeadBuffer->pLeft;
    pNew->pRight = this->pSoundHeadBuffer;
    this->pSoundHeadBuffer->pLeft->pRight = pNew;
    this->pSoundHeadBuffer->pLeft = pNew;
    pNew->id = id;
    pNew->lock = LE_FALSE;
    pNew->markedAsDelete = LE_FALSE;
    pNew->pSample = nullptr;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::soundCreate(%u)\n\n", id);
      this->printErrorDialog(LE_SOUND_EXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_SOUND_EXIST;
  }

  if(!result)
    {this->notifySound.notifyByEngine = LE_TRUE;}

  return result;
}

uint32_t LEMoon::soundCreate()
{
  lock_guard<mutex> lockA(this->mtxSound.soundCreate);
  uint32_t generatedID = this->soundGenerateID();
  LESound * pNew = nullptr;

  lock_guard<mutex> lockB(this->mtxSound.originalList);

  if(this->pSoundHead == nullptr)
  {
    this->pSoundHead = new LESound;
    this->pSoundHead->pLeft = this->pSoundHead;
    this->pSoundHead->pRight = this->pSoundHead;
    this->pSoundHead->id = 1989;
  }

  lock_guard<mutex> lockC(this->mtxSound.bufferList);

  if(this->pSoundHeadBuffer == nullptr)
  {
    this->pSoundHeadBuffer = new LESound;
    this->pSoundHeadBuffer->pLeft = this->pSoundHeadBuffer;
    this->pSoundHeadBuffer->pRight = this->pSoundHeadBuffer;
    this->pSoundHeadBuffer->id = 28092017;
  }

  pNew = new LESound;
  pNew->pLeft = this->pSoundHeadBuffer->pLeft;
  pNew->pRight = this->pSoundHeadBuffer;
  this->pSoundHeadBuffer->pLeft->pRight = pNew;
  this->pSoundHeadBuffer->pLeft = pNew;
  pNew->id = generatedID;
  pNew->lock = LE_FALSE;
  pNew->markedAsDelete = LE_FALSE;
  pNew->pSample = nullptr;

  return generatedID;
}

int LEMoon::soundDelete(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxSound.soundDelete);
  int result = LE_NO_ERROR;
  LESound * pSound = this->soundGet(id);

  if(pSound == nullptr)
    {pSound = this->soundGetFromBuffer(id);}

  if(pSound != nullptr)
  {
    pSound->markedAsDelete = LE_TRUE;
    this->notifySound.notifyByEngine = LE_TRUE;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::soundDelete(%u)\n\n", id);
      this->printErrorDialog(LE_SOUND_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_SOUND_NOEXIST;
  }

  return result;
}

int LEMoon::soundLoadWAV(uint32_t id, const char * pFile)
{
  lock_guard<mutex> lockA(this->mtxSound.soundLoadWAV);
  int result = LE_NO_ERROR;
  LESound * pSound = this->soundGet(id);

  if(pSound == nullptr)
    {pSound = this->soundGetFromBuffer(id);}

  if(pSound != nullptr)
  {
    if(pSound->pSample == nullptr)
    {
      pSound->pSample = Mix_LoadWAV(pFile);

      if(pSound->pSample == nullptr)
      {
        #ifdef LE_DEBUG
          char * pErrorString = new char[256 + 1];
          sprintf(pErrorString, "LEMoon::soundLoadWAV(%u, %s)\n\n", id, pFile);
          this->printErrorDialog(LE_LOAD_WAV, pErrorString);
          delete [] pErrorString;
        #endif

        result = LE_LOAD_WAV; 
      }
    }
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::soundLoadWAV(%u)\n\n", id);
      this->printErrorDialog(LE_SOUND_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_SOUND_NOEXIST;
  }

  return result;
}

void LEMoon::soundSetVolume(uint8_t volume)
{
  lock_guard<mutex> lockA(this->mtxSound.soundSetVolume);
  Mix_Volume(-1, volume);
}

int LEMoon::soundPlay(uint32_t id, int loops)
{
  lock_guard<mutex> lockA(this->mtxSound.soundPlay);
  int result = LE_NO_ERROR;
  LESound * pSound = this->soundGet(id);

  if(pSound == nullptr)
    {pSound = this->soundGetFromBuffer(id);}

  if(pSound != nullptr)
  {
    if(!(pSound->lock))
    {
      if(Mix_PlayChannel(-1, pSound->pSample, loops) == -1)
      {
        #ifdef LE_DEBUG
          char * pErrorString = new char[256 + 1];
          sprintf(pErrorString, "LEMoon::soundPlay(%u, %d)\n\n", id, loops);
          this->printErrorDialog(LE_PLAY_CHANNEL, pErrorString);
          delete [] pErrorString;
        #endif

        result = LE_PLAY_CHANNEL;
      }
    }
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::soundPlay(%u)\n\n", id);
      this->printErrorDialog(LE_SOUND_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_SOUND_NOEXIST;
  }

  return result;
}

int LEMoon::soundLock(uint32_t id, bool lock)
{
  lock_guard<mutex> lockA(this->mtxSound.soundLock);
  int result = LE_NO_ERROR;
  LESound * pSound = this->soundGet(id);

  if(pSound == nullptr)
    {pSound = this->soundGetFromBuffer(id);}

  if(pSound != nullptr)
    {pSound->lock = lock;}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::soundLock(%u)\n\n", id);
      this->printErrorDialog(LE_SOUND_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_SOUND_NOEXIST;
  }

  return result;
}

int LEMoon::soundFadeIn(uint32_t id, int ms)
{
  lock_guard<mutex> lockA(this->mtxSound.soundFadeIn);
  int result = LE_NO_ERROR;
  LESound * pSound = this->soundGet(id);

  if(pSound == nullptr)
    {pSound = this->soundGetFromBuffer(id);}

  if(pSound != nullptr)
    {Mix_FadeInChannel(-1, pSound->pSample, -1, ms);}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::soundFadeIn(%u)\n\n", id);
      this->printErrorDialog(LE_SOUND_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_SOUND_NOEXIST;
  }

  return result;
}

void LEMoon::soundFadeOut(int ms)
{
  lock_guard<mutex> lockA(this->mtxSound.soundFadeOut);
  Mix_FadeOutChannel(-1, ms);
}

void LEMoon::soundPause()
{
  lock_guard<mutex> lockA(this->mtxSound.soundPause);
  Mix_HaltChannel(-1);
}

void LEMoon::soundPrintList()
{
  lock_guard<mutex> lockA(this->mtxSound.soundPrintList);
  lock_guard<mutex> lockB(this->mtxSound.originalList);
  LESound * pCurrent = nullptr;

  if(this->pSoundHead != nullptr)
  {
    pCurrent = this->pSoundHead->pRight;

    if(pCurrent != nullptr)
    {
      printf("ORIGINAL: Head (Sound): %u", this->pSoundHead->id);

      while(pCurrent != this->pSoundHead)
      {
        printf(" <-> %u", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head (Sound): %u\n\n", this->pSoundHead->id);
    }
  }
}

void LEMoon::soundPrintBufferList()
{
  lock_guard<mutex> lockA(this->mtxSound.soundPrintBufferList);
  lock_guard<mutex> lockB(this->mtxSound.bufferList);
  LESound * pCurrent = nullptr;

  if(this->pSoundHeadBuffer != nullptr)
  {
    pCurrent = this->pSoundHeadBuffer->pRight;

    if(pCurrent != nullptr)
    {
      printf("BUFFER: Head (Sound): %u", this->pSoundHeadBuffer->id);

      while(pCurrent != this->pSoundHeadBuffer)
      {
        printf(" <-> %u", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head (Sound): %u\n\n", this->pSoundHeadBuffer->id);
    }
  }
}

void LEMoon::soundUsingThread(bool flag)
{
  lock_guard<mutex> lockA(this->mtxSound.soundUsingThread);
  this->notifySound.notifyByUser = flag;
}