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
// private sound
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

LESound * LEMoon::soundGet(uint32_t id)
{
  this->mtxSound.originalList.lock();
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

  this->mtxSound.originalList.unlock();
  return pRet;
}

LESound * LEMoon::soundGetFromBuffer(uint32_t id)
{
  this->mtxSound.bufferList.lock();
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

  this->mtxSound.bufferList.unlock();
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
  if(this->pSoundHead->pLeft == this->pSoundHead && this->pSoundHead->pRight == this->pSoundHead)
  {
    delete this->pSoundHead;
    this->pSoundHead = nullptr;
  }
}

void LEMoon::soundDeleteBufferList()
{
  if(this->pSoundHeadBuffer->pLeft == this->pSoundHeadBuffer && this->pSoundHeadBuffer->pRight == this->pSoundHeadBuffer)
  {
    delete this->pSoundHeadBuffer;
    this->pSoundHeadBuffer = nullptr;
  }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public sound
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::soundCreate(uint32_t id)
{
  this->mtxSound.soundCreate.lock();
  int result = LE_NO_ERROR;
  LESound * pNew = this->soundGet(id);

  if(pNew == nullptr)
    {pNew = this->soundGetFromBuffer(id);}

  if(pNew == nullptr)
  {
    this->mtxSound.originalList.lock();

    if(this->pSoundHead == nullptr)
    {
      this->pSoundHead = new LESound;
      this->pSoundHead->pLeft = this->pSoundHead;
      this->pSoundHead->pRight = this->pSoundHead;
      this->pSoundHead->id = 1989;
    }

    this->mtxSound.originalList.unlock();
    this->mtxSound.bufferList.lock();

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

    this->mtxSound.bufferList.unlock();
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

  this->mtxSound.soundCreate.unlock();
  return result;
}

int LEMoon::soundDelete(uint32_t id)
{
  this->mtxSound.soundDelete.lock();
  int result = LE_NO_ERROR;
  LESound * pSound = this->soundGet(id);

  if(pSound == nullptr)
    {pSound = this->soundGetFromBuffer(id);}

  if(pSound != nullptr)
    {pSound->markedAsDelete = LE_TRUE;}
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

  this->mtxSound.soundDelete.unlock();
  return result;
}

int LEMoon::soundLoadWAV(uint32_t id, const char * pFile)
{
  this->mtxSound.soundLoadWAV.lock();
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

  this->mtxSound.soundLoadWAV.unlock();
  return result;
}

void LEMoon::soundSetVolume(uint8_t volume)
{
  this->mtxSound.soundSetVolume.lock();
  Mix_Volume(-1, volume);
  this->mtxSound.soundSetVolume.unlock();
}

int LEMoon::soundPlay(uint32_t id, int loops)
{
  this->mtxSound.soundPlay.lock();
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

  this->mtxSound.soundPlay.unlock();
  return result;
}

int LEMoon::soundLock(uint32_t id, bool lock)
{
  this->mtxSound.soundLock.lock();
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
      sprintf(pErrorString, "LEMoon::soundLock(%d)\n\n", id);
      this->printErrorDialog(LE_SOUND_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_SOUND_NOEXIST;
  }

  this->mtxSound.soundLock.unlock();
  return result;
}

int LEMoon::soundFadeIn(uint32_t id, int ms)
{
  this->mtxSound.soundFadeIn.lock();
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

  this->mtxSound.soundFadeIn.unlock();
  return result;
}

void LEMoon::soundFadeOut(int ms)
{
  this->mtxSound.soundFadeOut.lock();
  Mix_FadeOutChannel(-1, ms);
  this->mtxSound.soundFadeOut.unlock();
}

void LEMoon::soundPause()
{
  this->mtxSound.soundPause.lock();
  Mix_HaltChannel(-1);
  this->mtxSound.soundPause.unlock();
}

void LEMoon::soundPrintList()
{
  this->mtxSound.soundPrintList.lock();
  this->mtxSound.originalList.lock();
  LESound * pCurrent = nullptr;

  if(this->pSoundHead != nullptr)
  {
    pCurrent = this->pSoundHead->pRight;

    if(pCurrent != nullptr)
    {
      printf("ORIGINAL: Head: %d", this->pSoundHead->id);

      while(pCurrent != this->pSoundHead)
      {
        printf(" <-> %d", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head: %d\n", this->pSoundHead->id);
    }
  }

  this->mtxSound.originalList.unlock();
  this->mtxSound.soundPrintList.unlock();
}

void LEMoon::soundPrintBufferList()
{
  this->mtxSound.soundPrintBufferList.lock();
  this->mtxSound.bufferList.lock();
  LESound * pCurrent = nullptr;

  if(this->pSoundHeadBuffer != nullptr)
  {
    pCurrent = this->pSoundHeadBuffer->pRight;

    if(pCurrent != nullptr)
    {
      printf("BUFFER: Head: %d", this->pSoundHeadBuffer->id);

      while(pCurrent != this->pSoundHeadBuffer)
      {
        printf(" <-> %d", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head: %d\n", this->pSoundHeadBuffer->id);
    }
  }

  this->mtxSound.bufferList.unlock();
  this->mtxSound.soundPrintBufferList.unlock();
}

void LEMoon::soundUsingThread(bool flag)
{
  this->mtxSound.soundUsingThread.lock();
  this->notifySound.notifyByUser = flag;
  this->mtxSound.soundUsingThread.unlock();
}