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
// private sound
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

LESound * LEMoon::soundGet(uint32_t id)
{
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

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public sound
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::soundCreate(uint32_t id)
{
  int result = LE_NO_ERROR;
  LESound * pNew = this->soundGet(id);

  if(pNew == nullptr)
  {
    if(this->pSoundHead == nullptr)
    {
      this->pSoundHead = new LESound;
      this->pSoundHead->pLeft = this->pSoundHead;
      this->pSoundHead->pRight = this->pSoundHead;
    }

    pNew = new LESound;
    pNew->pLeft = this->pSoundHead->pLeft;
    pNew->pRight = this->pSoundHead;
    this->pSoundHead->pLeft->pRight = pNew;
    this->pSoundHead->pLeft = pNew;
    pNew->id = id;
    pNew->lock = LE_FALSE;
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

  return result;
}

int LEMoon::soundDelete(uint32_t id)
{
  int result = LE_NO_ERROR;
  LESound * pSound = this->soundGet(id);

  if(pSound != nullptr)
  {
    pSound->pLeft->pRight = pSound->pRight;
    pSound->pRight->pLeft = pSound->pLeft;

    if(pSound->pSample != nullptr)
      {Mix_FreeChunk(pSound->pSample);}

    delete pSound;

    if(this->pSoundHead->pLeft == this->pSoundHead && this->pSoundHead->pRight == this->pSoundHead)
    {
      delete this->pSoundHead;
      this->pSoundHead = nullptr;
    }
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
  int result = LE_NO_ERROR;
  LESound * pSound = this->soundGet(id);

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
  Mix_Volume(-1, volume);
}

int LEMoon::soundPlay(uint32_t id, int loops)
{
  int result = LE_NO_ERROR;
  LESound * pSound = this->soundGet(id);

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
  int result = LE_NO_ERROR;
  LESound * pSound = this->soundGet(id);

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

  return result;
}

int LEMoon::soundFadeIn(uint32_t id, int ms)
{
  int result = LE_NO_ERROR;
  LESound * pSound = this->soundGet(id);

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
  Mix_FadeOutChannel(-1, ms);
}

void LEMoon::soundPause()
{
  Mix_HaltChannel(-1);
}