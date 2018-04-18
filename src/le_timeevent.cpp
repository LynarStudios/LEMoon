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
// private time event
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

LETimeEvent * LEMoon::timeEventGet(uint32_t id)
{
  LETimeEvent * pRet = nullptr;
  LETimeEvent * pCurrent = nullptr;

  if(this->pTimeEventHead != nullptr)
  {
    if(this->memory.pLastTimeEvent != nullptr && this->memory.pLastTimeEvent->id == id)
      {pRet = this->memory.pLastTimeEvent;}
    else
    {
      pCurrent = this->pTimeEventHead->pRight;

      while(pCurrent != this->pTimeEventHead)
      {
        if(pCurrent->id == id)
        {
          pRet = pCurrent;
          this->memory.pLastTimeEvent = pCurrent;
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
// public time event
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::timeEventCreate(uint32_t id, uint32_t ntimestamp)
{
  int result = LE_NO_ERROR;
  LETimeEvent * pNew = this->timeEventGet(id);

  if(pNew == nullptr)
  {
    if(this->pTimeEventHead == nullptr)
    {
      this->pTimeEventHead = new LETimeEvent;
      this->pTimeEventHead->pLeft = this->pTimeEventHead;
      this->pTimeEventHead->pRight = this->pTimeEventHead;
    }

    pNew = new LETimeEvent;
    pNew->pRight = this->pTimeEventHead;
    pNew->pLeft = this->pTimeEventHead->pLeft;
    this->pTimeEventHead->pLeft->pRight = pNew;
    this->pTimeEventHead->pLeft = pNew;
    pNew->id = id;
    pNew->timestamp = ntimestamp;
    pNew->reached = LE_FALSE;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::timeEventCreate(%u)\n\n", id);
      this->printErrorDialog(LE_TIMEEVENT_EXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TIMEEVENT_EXIST;
  }

  return result;
}

int LEMoon::timeEventDelete(uint32_t id)
{
  int result = LE_NO_ERROR;
  LETimeEvent * pElem = this->timeEventGet(id);

  if(pElem != nullptr)
  {
    pElem->pLeft->pRight = pElem->pRight;
    pElem->pRight->pLeft = pElem->pLeft;
    delete pElem;

    if(this->pTimeEventHead->pLeft == this->pTimeEventHead && this->pTimeEventHead->pRight == this->pTimeEventHead)
    {
      delete this->pTimeEventHead;
      this->pTimeEventHead = nullptr;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::timeEventDelete(%u)\n\n", id);
      this->printErrorDialog(LE_TIMEEVENT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TIMEEVENT_NOEXIST;
  }

  return result;
}

bool LEMoon::timeEventReached(uint32_t id)
{
  LETimeEvent * pElem = this->timeEventGet(id);

  if(pElem != nullptr)
  {
    if(pElem->timestamp <= this->timestamp)
      {pElem->reached = LE_TRUE;}
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::timeEventReached(%u)\n\n", id);
      this->printErrorDialog(LE_TIMEEVENT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return pElem->reached;
}

int LEMoon::timeEventReset(uint32_t id, uint32_t ntimestamp)
{
  int result = LE_NO_ERROR;
  LETimeEvent * pElem = this->timeEventGet(id);

  if(pElem != nullptr)
  {
    pElem->timestamp = ntimestamp;
    pElem->reached = LE_FALSE;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::timeEventReset(%u)\n\n", id);
      this->printErrorDialog(LE_TIMEEVENT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TIMEEVENT_NOEXIST;
  }

  return result;
}

int LEMoon::timeEventUpdate(uint32_t id, uint32_t milliseconds)
{
  int result = LE_NO_ERROR;
  LETimeEvent * pElem = this->timeEventGet(id);

  if(pElem != nullptr)
    {pElem->timestamp += milliseconds;}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::timeEventUpdate(%u)\n\n", id);
      this->printErrorDialog(LE_TIMEEVENT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_TIMEEVENT_NOEXIST;
  }

  return result;
}

void LEMoon::timeEventUpdateValidALL(uint32_t milliseconds)
{
  LETimeEvent * pCurrent = nullptr;

  if(this->pTimeEventHead != nullptr)
  {
    pCurrent = this->pTimeEventHead->pRight;

    while(pCurrent != this->pTimeEventHead)
    {
      if(!(pCurrent->reached))
        {pCurrent->timestamp += milliseconds;}

      pCurrent = pCurrent->pRight;
    }
  }
}

uint32_t LEMoon::timeEventGetStamp(uint32_t id)
{
  uint32_t ts = 0;
  LETimeEvent * pElem = this->timeEventGet(id);

  if(pElem != nullptr)
    {ts = pElem->timestamp;}

  return ts;
}
