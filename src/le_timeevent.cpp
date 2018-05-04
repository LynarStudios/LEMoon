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
// private time event
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

LETimeEvent * LEMoon::timeEventGet(uint32_t id)
{
  this->mtxTimeEvent.originalList.lock();
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

  this->mtxTimeEvent.originalList.unlock();
  return pRet;
}

LETimeEvent * LEMoon::timeEventGetFromBuffer(uint32_t id)
{
  this->mtxTimeEvent.bufferList.lock();
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

  this->mtxTimeEvent.bufferList.unlock();
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
  if(this->pTimeEventHeadBuffer->pLeft == this->pTimeEventHeadBuffer && this->pTimeEventHeadBuffer->pRight == this->pTimeEventHeadBuffer)
  {
    delete this->pTimeEventHeadBuffer;
    this->pTimeEventHeadBuffer = nullptr;
  }
}

void LEMoon::timeEventDeleteOriginalList()
{
  if(this->pTimeEventHead->pLeft == this->pTimeEventHead && this->pTimeEventHead->pRight == this->pTimeEventHead)
  {
    delete this->pTimeEventHead;
    this->pTimeEventHead = nullptr;
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

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public time event
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::timeEventCreate(uint32_t id, uint32_t ntimestamp)
{
  this->mtxTimeEvent.timeEventCreate.lock();
  int result = LE_NO_ERROR;
  LETimeEvent * pNew = this->timeEventGet(id);

  if(pNew == nullptr)
    {pNew = this->timeEventGetFromBuffer(id);}

  if(pNew == nullptr)
  {
    this->mtxTimeEvent.originalList.lock();

    if(this->pTimeEventHead == nullptr)
    {
      this->pTimeEventHead = new LETimeEvent;
      this->pTimeEventHead->pLeft = this->pTimeEventHead;
      this->pTimeEventHead->pRight = this->pTimeEventHead;
      this->pTimeEventHead->id = 1989;
    }

    this->mtxTimeEvent.originalList.unlock();
    this->mtxTimeEvent.bufferList.lock();

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

    this->mtxTimeEvent.bufferList.unlock();
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

  this->mtxTimeEvent.timeEventCreate.unlock();
  return result;
}

int LEMoon::timeEventDelete(uint32_t id)
{
  this->mtxTimeEvent.timeEventDelete.lock();
  int result = LE_NO_ERROR;
  LETimeEvent * pElem = this->timeEventGet(id);

  if(pElem == nullptr)
    {pElem = this->timeEventGetFromBuffer(id);}

  if(pElem != nullptr)
    {pElem->markedAsDelete = LE_TRUE;}
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

  this->mtxTimeEvent.timeEventDelete.unlock();
  return result;
}

bool LEMoon::timeEventReached(uint32_t id)
{
  this->mtxTimeEvent.timeEventReached.lock();
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

  this->mtxTimeEvent.timeEventReached.unlock();
  return pElem->reached;
}

int LEMoon::timeEventReset(uint32_t id, uint32_t ntimestamp)
{
  this->mtxTimeEvent.timeEventReset.lock();
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

  this->mtxTimeEvent.timeEventReset.unlock();
  return result;
}

int LEMoon::timeEventUpdate(uint32_t id, uint32_t milliseconds)
{
  this->mtxTimeEvent.timeEventUpdate.lock();
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

  this->mtxTimeEvent.timeEventUpdate.unlock();
  return result;
}

void LEMoon::timeEventUpdateValidALL(uint32_t milliseconds)
{
  this->mtxTimeEvent.timeEventUpdateValidALL.lock();
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

  this->mtxTimeEvent.timeEventUpdateValidALL.unlock();
}

uint32_t LEMoon::timeEventGetStamp(uint32_t id)
{
  this->mtxTimeEvent.timeEventGetStamp.lock();
  uint32_t ts = 0;
  LETimeEvent * pElem = this->timeEventGet(id);

  if(pElem == nullptr)
    {pElem = this->timeEventGetFromBuffer(id);}

  if(pElem != nullptr)
    {ts = pElem->timestamp;}

  this->mtxTimeEvent.timeEventGetStamp.unlock();
  return ts;
}

void LEMoon::timeEventUsingThread(bool flag)
{
  this->mtxTimeEvent.timeEventUsingThread.lock();
  this->notifyTimeEvent.notifyByUser = flag;
  this->mtxTimeEvent.timeEventUsingThread.unlock();
}

void LEMoon::timeEventPrintList()
{
  this->mtxTimeEvent.timeEventPrintList.lock();
  this->mtxTimeEvent.originalList.lock();
  LETimeEvent * pCurrent = nullptr;

  if(this->pTimeEventHead != nullptr)
  {
    pCurrent = this->pTimeEventHead->pRight;

    if(pCurrent != nullptr)
    {
      printf("ORIGINAL: Head: %d", this->pTimeEventHead->id);

      while(pCurrent != this->pTimeEventHead)
      {
        printf(" <-> %d", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head: %d\n", this->pTimeEventHead->id);
    }
  }

  this->mtxTimeEvent.originalList.unlock();
  this->mtxTimeEvent.timeEventPrintList.unlock();
}

void LEMoon::timeEventPrintBufferList()
{
  this->mtxTimeEvent.timeEventPrintBufferList.lock();
  this->mtxTimeEvent.bufferList.lock();
  LETimeEvent * pCurrent = nullptr;

  if(this->pTimeEventHeadBuffer != nullptr)
  {
    pCurrent = this->pTimeEventHeadBuffer->pRight;

    if(pCurrent != nullptr)
    {
      printf("BUFFER: Head: %d", this->pTimeEventHeadBuffer->id);

      while(pCurrent != this->pTimeEventHeadBuffer)
      {
        printf(" <-> %d", pCurrent->id);
        pCurrent = pCurrent->pRight;
      }

      printf(" <-> Head: %d\n", this->pTimeEventHeadBuffer->id);
    }
  }

  this->mtxTimeEvent.bufferList.unlock();
  this->mtxTimeEvent.timeEventPrintBufferList.unlock();
}
