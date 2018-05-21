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
// private time event
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

LETimeEvent * LEMoon::timeEventGet(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxTimeEvent.originalList);
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

LETimeEvent * LEMoon::timeEventGetFromBuffer(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxTimeEvent.bufferList);
  LETimeEvent * pRet = nullptr;
  LETimeEvent * pCurrent = nullptr;

  if(this->pTimeEventHeadBuffer != nullptr)
  {
    if(this->memory.pLastTimeEvent != nullptr && this->memory.pLastTimeEvent->id == id)
      {pRet = this->memory.pLastTimeEvent;}
    else
    {
      pCurrent = this->pTimeEventHeadBuffer->pRight;

      while(pCurrent != this->pTimeEventHeadBuffer)
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

void LEMoon::timeEventCleanList()
{
  LETimeEvent * pCurrent = nullptr;
  LETimeEvent * pNext = nullptr;

  if(this->pTimeEventHead != nullptr)
  {
    pCurrent = this->pTimeEventHead->pRight;

    while(pCurrent != this->pTimeEventHead)
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

void LEMoon::timeEventCleanBufferList()
{
  LETimeEvent * pCurrent = nullptr;
  LETimeEvent * pNext = nullptr;

  if(this->pTimeEventHeadBuffer != nullptr)
  {
    pCurrent = this->pTimeEventHeadBuffer->pRight;

    while(pCurrent != this->pTimeEventHeadBuffer)
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

void LEMoon::timeEventConstructor()
{
  this->pTimeEventHead = nullptr;
  this->pTimeEventHeadBuffer = nullptr;

  this->notifyTimeEvent.notifyByEngine = LE_FALSE;
  this->notifyTimeEvent.notifyByUser = LE_FALSE;

  this->mtxTimeEvent.timeEventCreateLockedByMerge = LE_FALSE;
  this->mtxTimeEvent.timeEventDeleteLockedByMerge = LE_FALSE;
}

void LEMoon::timeEventDeleteBufferList()
{
  if(this->pTimeEventHeadBuffer != nullptr)
  {
    if(this->pTimeEventHeadBuffer->pLeft == this->pTimeEventHeadBuffer && this->pTimeEventHeadBuffer->pRight == this->pTimeEventHeadBuffer)
    {
      delete this->pTimeEventHeadBuffer;
      this->pTimeEventHeadBuffer = nullptr;
    }
  }
}

void LEMoon::timeEventDeleteOriginalList()
{
  if(this->pTimeEventHead != nullptr)
  {
    if(this->pTimeEventHead->pLeft == this->pTimeEventHead && this->pTimeEventHead->pRight == this->pTimeEventHead)
    {
      delete this->pTimeEventHead;
      this->pTimeEventHead = nullptr;
    }
  }
}

void LEMoon::timeEventMergeLists()
{
  LETimeEvent * pCurrent = nullptr;
  LETimeEvent * pNext = nullptr;

  if(this->pTimeEventHeadBuffer != nullptr)
  {
    pCurrent = this->pTimeEventHeadBuffer->pRight;

    while(pCurrent != this->pTimeEventHeadBuffer)
    {
      pNext = pCurrent->pRight;
      pCurrent->pLeft->pRight = pCurrent->pRight;
      pCurrent->pRight->pLeft = pCurrent->pLeft;
      pCurrent->pRight = this->pTimeEventHead;
      pCurrent->pLeft = this->pTimeEventHead->pLeft;
      this->pTimeEventHead->pLeft->pRight = pCurrent;
      this->pTimeEventHead->pLeft = pCurrent;
      pCurrent = pNext;
    }
  }
}

int LEMoon::timeEventMerge()
{
  int result = LE_NO_ERROR;
  bool lockedAll = LE_FALSE;

  if(this->notifyTimeEvent.notifyByEngine && !this->notifyTimeEvent.notifyByUser)
  {
    // lock all

    if(this->mtxTimeEvent.timeEventCreate.try_lock())
      {this->mtxTimeEvent.timeEventCreateLockedByMerge = LE_TRUE;}
    if(this->mtxTimeEvent.timeEventDelete.try_lock())
      {this->mtxTimeEvent.timeEventDeleteLockedByMerge = LE_TRUE;}

    lockedAll = this->mtxTimeEvent.timeEventCreateLockedByMerge && this->mtxTimeEvent.timeEventDeleteLockedByMerge;

    // delete (from both list), merge(buffer to original) and delete buffer

    if(lockedAll)
    {
      this->timeEventCleanList();
      this->timeEventCleanBufferList();
      this->timeEventMergeLists();
      this->timeEventDeleteBufferList();
      this->timeEventDeleteOriginalList();
      this->memory.pLastTimeEvent = nullptr;
      this->notifyTimeEvent.notifyByEngine = LE_FALSE;
    }

    // unlock all

    if(this->mtxTimeEvent.timeEventCreateLockedByMerge)
      {this->mtxTimeEvent.timeEventCreate.unlock();}
    if(this->mtxTimeEvent.timeEventDeleteLockedByMerge)
      {this->mtxTimeEvent.timeEventDelete.unlock();}

    this->mtxTimeEvent.timeEventCreateLockedByMerge = LE_FALSE;
    this->mtxTimeEvent.timeEventDeleteLockedByMerge = LE_FALSE;
  }

  return result;
}

uint32_t LEMoon::timeEventGenerateIDFromOriginalList()
{
  lock_guard<mutex> lockA(this->mtxTimeEvent.originalList);
  uint32_t id = 0;
  LETimeEvent * pStart = nullptr;
  LETimeEvent * pCurrent = nullptr;
  bool idNotFound = LE_FALSE;

  if(this->pTimeEventHead != nullptr)
  {
    pStart = this->pTimeEventHead->pRight;

    while(pStart != this->pTimeEventHead)
    {
      id = pStart->id + 1;
      pCurrent = this->pTimeEventHead->pRight;

      while(pCurrent != this->pTimeEventHead)
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

uint32_t LEMoon::timeEventGenerateIDFromBufferList()
{
  lock_guard<mutex> lockA(this->mtxTimeEvent.bufferList);
  uint32_t id = 0;
  LETimeEvent * pStart = nullptr;
  LETimeEvent * pCurrent = nullptr;
  bool idNotFound = LE_FALSE;

  if(this->pTimeEventHeadBuffer != nullptr)
  {
    pStart = this->pTimeEventHeadBuffer->pRight;

    while(pStart != this->pTimeEventHeadBuffer)
    {
      id = pStart->id + 1;
      pCurrent = this->pTimeEventHeadBuffer->pRight;

      while(pCurrent != this->pTimeEventHeadBuffer)
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

uint32_t LEMoon::timeEventGenerateID()
{
  uint32_t id;
  id = this->timeEventGenerateIDFromOriginalList();

  if(id == 0)
    {id = this->timeEventGenerateIDFromBufferList();}
  if(id == 0)
    {id = 1;}

  return id;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public time event
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::timeEventCreate(uint32_t id, uint32_t ntimestamp)
{
  lock_guard<mutex> lockA(this->mtxTimeEvent.timeEventCreate);
  int result = LE_NO_ERROR;
  LETimeEvent * pNew = this->timeEventGet(id);

  if(pNew == nullptr)
    {pNew = this->timeEventGetFromBuffer(id);}

  if(pNew == nullptr)
  {
    lock_guard<mutex> lockB(this->mtxTimeEvent.originalList);

    if(this->pTimeEventHead == nullptr)
    {
      this->pTimeEventHead = new LETimeEvent;
      this->pTimeEventHead->pLeft = this->pTimeEventHead;
      this->pTimeEventHead->pRight = this->pTimeEventHead;
      this->pTimeEventHead->id = 1989;
    }

    lock_guard<mutex> lockC(this->mtxTimeEvent.bufferList);

    if(this->pTimeEventHeadBuffer == nullptr)
    {
      this->pTimeEventHeadBuffer = new LETimeEvent;
      this->pTimeEventHeadBuffer->pLeft = this->pTimeEventHeadBuffer;
      this->pTimeEventHeadBuffer->pRight = this->pTimeEventHeadBuffer;
      this->pTimeEventHeadBuffer->id = 28092017;
    }

    pNew = new LETimeEvent;
    pNew->pRight = this->pTimeEventHeadBuffer;
    pNew->pLeft = this->pTimeEventHeadBuffer->pLeft;
    this->pTimeEventHeadBuffer->pLeft->pRight = pNew;
    this->pTimeEventHeadBuffer->pLeft = pNew;
    pNew->id = id;
    pNew->timestamp = ntimestamp;
    pNew->reached = LE_FALSE;
    pNew->markedAsDelete = LE_FALSE;
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

  if(!result)
    {this->notifyTimeEvent.notifyByEngine = LE_TRUE;}

  return result;
}

uint32_t LEMoon::timeEventCreate(uint32_t ntimestamp)
{
  lock_guard<mutex> lockA(this->mtxTimeEvent.timeEventCreate);
  uint32_t generatedID = this->timeEventGenerateID();
  LETimeEvent * pNew = nullptr;

  lock_guard<mutex> lockB(this->mtxTimeEvent.originalList);

  if(this->pTimeEventHead == nullptr)
  {
    this->pTimeEventHead = new LETimeEvent;
    this->pTimeEventHead->pLeft = this->pTimeEventHead;
    this->pTimeEventHead->pRight = this->pTimeEventHead;
    this->pTimeEventHead->id = 1989;
  }

  lock_guard<mutex> lockC(this->mtxTimeEvent.bufferList);

  if(this->pTimeEventHeadBuffer == nullptr)
  {
    this->pTimeEventHeadBuffer = new LETimeEvent;
    this->pTimeEventHeadBuffer->pLeft = this->pTimeEventHeadBuffer;
    this->pTimeEventHeadBuffer->pRight = this->pTimeEventHeadBuffer;
    this->pTimeEventHeadBuffer->id = 28092017;
  }

  pNew = new LETimeEvent;
  pNew->pRight = this->pTimeEventHeadBuffer;
  pNew->pLeft = this->pTimeEventHeadBuffer->pLeft;
  this->pTimeEventHeadBuffer->pLeft->pRight = pNew;
  this->pTimeEventHeadBuffer->pLeft = pNew;
  pNew->id = generatedID;
  pNew->timestamp = ntimestamp;
  pNew->reached = LE_FALSE;
  pNew->markedAsDelete = LE_FALSE;

  return generatedID;
}

int LEMoon::timeEventDelete(uint32_t id)
{
  lock_guard<mutex> lockA(this->mtxTimeEvent.timeEventDelete);
  int result = LE_NO_ERROR;
  LETimeEvent * pElem = this->timeEventGet(id);

  if(pElem == nullptr)
    {pElem = this->timeEventGetFromBuffer(id);}

  if(pElem != nullptr)
  {
    pElem->markedAsDelete = LE_TRUE;
    this->notifyTimeEvent.notifyByEngine = LE_TRUE;
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
  lock_guard<mutex> lockA(this->mtxTimeEvent.timeEventReached);
  LETimeEvent * pElem = this->timeEventGet(id);

  if(pElem == nullptr)
    {pElem = this->timeEventGetFromBuffer(id);}

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
  lock_guard<mutex> lockA(this->mtxTimeEvent.timeEventReset);
  int result = LE_NO_ERROR;
  LETimeEvent * pElem = this->timeEventGet(id);

  if(pElem == nullptr)
    {pElem = this->timeEventGetFromBuffer(id);}

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
  lock_guard<mutex> lockA(this->mtxTimeEvent.timeEventUpdate);
  int result = LE_NO_ERROR;
  LETimeEvent * pElem = this->timeEventGet(id);

  if(pElem == nullptr)
    {pElem = this->timeEventGetFromBuffer(id);}

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
  lock_guard<mutex> lockA(this->mtxTimeEvent.timeEventUpdateValidALL);
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
  lock_guard<mutex> lockA(this->mtxTimeEvent.timeEventGetStamp);
  uint32_t ts = 0;
  LETimeEvent * pElem = this->timeEventGet(id);

  if(pElem == nullptr)
    {pElem = this->timeEventGetFromBuffer(id);}

  if(pElem != nullptr)
    {ts = pElem->timestamp;}

  return ts;
}

void LEMoon::timeEventUsingThread(bool flag)
{
  lock_guard<mutex> lockA(this->mtxTimeEvent.timeEventUsingThread);
  this->notifyTimeEvent.notifyByUser = flag;
}

void LEMoon::timeEventPrintList()
{
  lock_guard<mutex> lockA(this->mtxTimeEvent.timeEventPrintList);
  lock_guard<mutex> lockB(this->mtxTimeEvent.originalList);
  LETimeEvent * pCurrent = nullptr;

  if(this->pTimeEventHead != nullptr)
  {
    pCurrent = this->pTimeEventHead->pRight;

    if(pCurrent != nullptr)
    {
      printf("ORIGINAL: Head (Time Event): %u", this->pTimeEventHead->id);

      while(pCurrent != this->pTimeEventHead)
      {
        printf(" <-> %u", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head (Time Event): %u\n\n", this->pTimeEventHead->id);
    }
  }
}

void LEMoon::timeEventPrintBufferList()
{
  lock_guard<mutex> lockA(this->mtxTimeEvent.timeEventPrintBufferList);
  lock_guard<mutex> lockB(this->mtxTimeEvent.bufferList);
  LETimeEvent * pCurrent = nullptr;

  if(this->pTimeEventHeadBuffer != nullptr)
  {
    pCurrent = this->pTimeEventHeadBuffer->pRight;

    if(pCurrent != nullptr)
    {
      printf("BUFFER: Head (Time Event): %u", this->pTimeEventHeadBuffer->id);

      while(pCurrent != this->pTimeEventHeadBuffer)
      {
        printf(" <-> %u", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head (Time Event): %u\n\n", this->pTimeEventHeadBuffer->id);
    }
  }
}
