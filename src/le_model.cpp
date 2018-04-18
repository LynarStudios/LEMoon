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
      sprintf(pErrorString, "LEMoon::modelDraw(%d)\n\n", pModel->id);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return result;
}

LEModel * LEMoon::modelGet(uint32_t id)
{
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

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public model
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::modelCreate(uint32_t id)
{
  int result = LE_NO_ERROR;
  LEModel * pNew = this->modelGet(id);

  // element already exist?

  if(pNew == nullptr)
  {
    if(this->pModelHead == nullptr)
    {
      this->pModelHead = new LEModel;
      this->pModelHead->pLeft = this->pModelHead;
      this->pModelHead->pRight = this->pModelHead;
      this->pModelHead->pModel = nullptr;
      this->pModelHead->id = 1989;
      this->pModelHead->zindex = 0;
    }

    pNew = new LEModel;
    pNew->pLeft = this->pModelHead;
    pNew->pRight = this->pModelHead->pRight;
    this->pModelHead->pRight->pLeft = pNew;
    this->pModelHead->pRight = pNew;
    pNew->id = id;
    pNew->zindex = 1;
    pNew->visible = LE_TRUE;
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

  return result;
}

int LEMoon::modelDelete(uint32_t id)
{
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem != nullptr)
  {
    pElem->pLeft->pRight = pElem->pRight;
    pElem->pRight->pLeft = pElem->pLeft;
    delete pElem->pModel;
    pElem->pModel = nullptr;
    delete pElem;
    pElem = nullptr;

    if(this->pModelHead->pLeft == this->pModelHead && this->pModelHead->pRight == this->pModelHead)
    {
      delete this->pModelHead;
      this->pModelHead = nullptr;
    }
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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  double factor = 0.0f;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);
  LEModel * pCurrent = nullptr;
  bool moreThanOneElement = this->pModelHead->pLeft->id != this->pModelHead->pRight->id;

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

  if(moreThanOneElement)
  {
    if(!result && pElem != nullptr)
    {
      pElem->zindex = zindex;
    
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
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::modelSetZindex(%u)\n\n", id);
        this->printErrorDialog(LE_MDL_NOEXIST, pErrorString);
        delete [] pErrorString;
      #endif
    
      result = LE_MDL_NOEXIST;
    }
  }

  return result;
}

int LEMoon::modelSetTextureZindex(uint32_t id, uint32_t idTexture, uint32_t zindex)
{
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  SDL_Point size;
  size.x = 0;
  size.y = 0;
  LEModel * pElem = this->modelGet(id);

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
  SDL_Point position;
  position.x = 0;
  position.y = 0;
  LEModel * pElem = this->modelGet(id);

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
  glm::vec2 position;
  LEModel * pElem = this->modelGet(id);

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
  double alpha = 0;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  double sizeFactor = 0.0f;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  SDL_Surface * pSurface = nullptr;
  LEModel * pElem = this->modelGet(id);

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
  LEModel * pElem = this->modelGet(id);
  Color pixel;

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
  glm::vec2 direction = {0.0f, 0.0f};
  LEModel * pElem = this->modelGet(id);

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
  LECollBox_d frameBox;
  LEModel * pElem = this->modelGet(id);

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
  LECollBox_d collisionBox;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

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
  bool collided = LE_FALSE;
  LEModel * pModel = this->modelGet(idModel);
  LEModel * pForeignModel = this->modelGet(idForeignModel);

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
  bool collided = LE_FALSE;
  LEModel * pModel = this->modelGet(idModel);
  LEModel * pForeignModel = this->modelGet(idForeignModel);

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
  uint32_t amount = 0;
  LEModel * pModel = this->modelGet(id);

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
  uint32_t amount = 0;
  LEModel * pModel = this->modelGet(id);

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
  uint32_t zindex = 0;
  LEModel * pModel = this->modelGet(id);

  if(pModel != nullptr)
    {zindex = pModel->zindex;}

  return zindex;
}

bool LEMoon::modelTextureExists(uint32_t id, uint32_t idTexture)
{
  bool textureExist = LE_FALSE;
  LEModel * pModel = this->modelGet(id);

  if(pModel != nullptr)
    {textureExist = pModel->pModel->mdlTextureExist(idTexture);}

  return textureExist;
}

bool LEMoon::modelGetVisible(uint32_t id)
{
  bool visible = LE_FALSE;
  LEModel * pModel = this->modelGet(id);

  if(pModel != nullptr)
    {visible = pModel->visible;}

  return visible;
}