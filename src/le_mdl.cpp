/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Ubuntu 16.04, g++ Compiler
  date:               29.05.2017
  updated:            26.04.2018
*/

#include "../include/le_mdl.h"

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// private
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

CollisionRect * LEMdl::collisionRectGet(uint32_t idCollRect)
{
  this->mtxCollisionRect.lock();
  CollisionRect * pRet = nullptr;
  CollisionRect * pCurrent = nullptr;

  if(this->pCollisionRectHead != nullptr)
  {
    pCurrent = this->pCollisionRectHead->pRight;

    while(pCurrent != this->pCollisionRectHead)
    {
      if(pCurrent->id == idCollRect)
      {
        pRet = pCurrent;
        break;
      }

      pCurrent = pCurrent->pRight;
    }
  }

  this->mtxCollisionRect.unlock();
  return pRet;
}

Clone * LEMdl::cloneGet(uint32_t idClone)
{
  this->mtxClone.lock();
  Clone * pRet = nullptr;
  Clone * pCurrent = nullptr;

  if(this->pCloneHead != nullptr)
  {
    pCurrent = this->pCloneHead->pRight;

    while(pCurrent != this->pCloneHead)
    {
      if(pCurrent->id == idClone)
      {
        pRet = pCurrent;
        break;
      }

      pCurrent = pCurrent->pRight;
    }
  }

  this->mtxClone.unlock();
  return pRet;
}

Texture * LEMdl::textureGet(uint32_t idTexture)
{
  this->mtxTexture.lock();
  Texture * pRet = nullptr;
  Texture * pCurrent = nullptr;

  if(this->pTextureHead != nullptr)
  {
    pCurrent = this->pTextureHead->pRight;

    while(pCurrent != this->pTextureHead)
    {
      if(pCurrent->id == idTexture)
      {
        pRet = pCurrent;
        break;
      }

      pCurrent = pCurrent->pRight;
    }
  }

  this->mtxTexture.unlock();
  return pRet;
}

SourceRect * LEMdl::sourceRectGet(Texture * pTexture, uint32_t idSrcRect)
{
  this->mtxSourceRectList.lock();
  SourceRect * pRet = nullptr;
  SourceRect * pCurrent = nullptr;

  if(pTexture->pSrcRectHead != nullptr)
  {
    pCurrent = pTexture->pSrcRectHead->pRight;

    while(pCurrent != pTexture->pSrcRectHead)
    {
      if(pCurrent->id == idSrcRect)
      {
        pRet = pCurrent;
        break;
      }

      pCurrent = pCurrent->pRight;
    }
  }

  this->mtxSourceRectList.unlock();
  return pRet;
}

uint32_t LEMdl::amountSourceRect(Texture * pTexture)
{
  uint32_t amount = 0;
  SourceRect * pCurrent = nullptr;

  if(pTexture->pSrcRectHead != nullptr)
  {
    pCurrent = pTexture->pSrcRectHead->pRight;

    while(pCurrent != pTexture->pSrcRectHead)
    {
      amount++;
      pCurrent = pCurrent->pRight;
    }
  }

  return amount;
}

LinkedVec2 * LEMdl::directionGet(uint32_t idDirection)
{
  this->mtxDirection.lock();
  LinkedVec2 * pRet = nullptr;
  LinkedVec2 * pCurrent = nullptr;

  if(this->pDirectionHead != nullptr)
  {
    pCurrent = this->pDirectionHead->pRight;

    while(pCurrent != this->pDirectionHead)
    {
      if(pCurrent->id == idDirection)
      {
        pRet = pCurrent;
        break;
      }

      pCurrent = pCurrent->pRight;
    }
  }

  this->mtxDirection.unlock();
  return pRet;
}

void LEMdl::memoryClearDirections()
{
  this->mtxDirection.lock();
  LinkedVec2 * pCurrent = nullptr;
  LinkedVec2 * pNext = nullptr;

  if(this->pDirectionHead != nullptr)
  {
    pCurrent = this->pDirectionHead->pRight;

    while(pCurrent != this->pDirectionHead)
    {
      pNext = pCurrent->pRight;
      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pDirectionHead;
    this->pDirectionHead = nullptr;
  }

  this->mtxDirection.unlock();
}

void LEMdl::memoryClearTextures()
{
  this->mtxTexture.lock();
  Texture * pCurrent = nullptr;
  Texture * pNext = nullptr;
  SourceRect * pCurrentSrcRect = nullptr;
  SourceRect * pNextSrcRect = nullptr;

  if(this->pTextureHead != nullptr)
  {
    pCurrent = this->pTextureHead->pRight;

    while(pCurrent != this->pTextureHead)
    {
      pNext = pCurrent->pRight;

      // loesche Surface

      if(pCurrent->pSurface != nullptr)
        {SDL_FreeSurface(pCurrent->pSurface);}

      // loesche Textur

      if(pCurrent->pTexture != nullptr)
        {SDL_DestroyTexture(pCurrent->pTexture);}

      // loesche Zeichenbereiche der Textur

      if(pCurrent->pSrcRectHead != nullptr)
      {
        pCurrentSrcRect = pCurrent->pSrcRectHead->pRight;

        while(pCurrentSrcRect != pCurrent->pSrcRectHead)
        {
          pNextSrcRect = pCurrentSrcRect->pRight;
          delete pCurrentSrcRect;
          pCurrentSrcRect = pNextSrcRect;
        }

        delete pCurrent->pSrcRectHead;
        pCurrent->pSrcRectHead = nullptr;
      }

      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pTextureHead;
    this->pTextureHead = nullptr;
  }

  this->mtxTexture.unlock();
}

void LEMdl::memoryClearClones()
{
  this->mtxClone.lock();
  Clone * pCurrent = nullptr;
  Clone * pNext = nullptr;

  if(this->pCloneHead != nullptr)
  {
    pCurrent = this->pCloneHead->pRight;

    while(pCurrent != this->pCloneHead)
    {
      pNext = pCurrent->pRight;
      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pCloneHead;
    this->pCloneHead = nullptr;
  }

  this->mtxClone.unlock();
}

void LEMdl::memoryClearCollisionRects()
{
  this->mtxCollisionRect.lock();
  CollisionRect * pCurrent = nullptr;
  CollisionRect * pNext = nullptr;

  if(this->pCollisionRectHead != nullptr)
  {
    pCurrent = this->pCollisionRectHead->pRight;

    while(pCurrent != this->pCollisionRectHead)
    {
      pNext = pCurrent->pRight;
      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pCollisionRectHead;
    this->pCollisionRectHead = nullptr;
  }

  this->mtxCollisionRect.unlock();
}

void LEMdl::updateFrameBox()
{
  SDL_Point size = this->mdlGetSize();
  this->frameBox.lineLeft.p1.x   = this->position.x;
  this->frameBox.lineLeft.p1.y   = this->position.y;
  this->frameBox.lineLeft.p2.x   = this->position.x;
  this->frameBox.lineLeft.p2.y   = this->position.y + size.y;
  this->frameBox.lineTop.p1.x    = this->position.x;
  this->frameBox.lineTop.p1.y    = this->position.y;
  this->frameBox.lineTop.p2.x    = this->position.x + size.x;
  this->frameBox.lineTop.p2.y    = this->position.y;
  this->frameBox.lineRight.p1.x  = this->position.x + size.x;
  this->frameBox.lineRight.p1.y  = this->position.y;
  this->frameBox.lineRight.p2.x  = this->position.x + size.x;
  this->frameBox.lineRight.p2.y  = this->position.y + size.y;
  this->frameBox.lineBottom.p1.x = this->position.x;
  this->frameBox.lineBottom.p1.y = this->position.y + size.y;
  this->frameBox.lineBottom.p2.x = this->position.x + size.x;
  this->frameBox.lineBottom.p2.y = this->position.y + size.y;
  this->frameBox.center.x = this->position.x + (size.x * 0.5f);
  this->frameBox.center.y = this->position.y + (size.y * 0.5f);

  // rotate collision box

  this->bufferFrameBox = this->rotateCollisionBox(this->frameBox);
}

void LEMdl::updateCollisionBox(CollisionRect * pCollRect)
{
  SDL_Point size = this->mdlGetSize();
  pCollRect->collRectBuffer.lineLeft.p1.x = this->position.x + pCollRect->collRect.x;
  pCollRect->collRectBuffer.lineLeft.p1.y = this->position.y + pCollRect->collRect.y;
  pCollRect->collRectBuffer.lineLeft.p2.x = this->position.x + pCollRect->collRect.x;
  pCollRect->collRectBuffer.lineLeft.p2.y = this->position.y + pCollRect->collRect.y + pCollRect->collRect.h;
//printf("LineLeft: (%1.2f | %1.2f) (%1.2f | %1.2f)\n", pCollRect->collRectBuffer.lineLeft.p1.x, pCollRect->collRectBuffer.lineLeft.p1.y, pCollRect->collRectBuffer.lineLeft.p2.x, pCollRect->collRectBuffer.lineLeft.p2.y);
  pCollRect->collRectBuffer.lineTop.p1.x = this->position.x + pCollRect->collRect.x;
  pCollRect->collRectBuffer.lineTop.p1.y = this->position.y + pCollRect->collRect.y;
  pCollRect->collRectBuffer.lineTop.p2.x = this->position.x + pCollRect->collRect.x + pCollRect->collRect.w;
  pCollRect->collRectBuffer.lineTop.p2.y = this->position.y + pCollRect->collRect.y;
//printf("LineTop: (%1.2f | %1.2f) (%1.2f | %1.2f)\n", pCollRect->collRectBuffer.lineTop.p1.x, pCollRect->collRectBuffer.lineTop.p1.y, pCollRect->collRectBuffer.lineTop.p2.x, pCollRect->collRectBuffer.lineTop.p2.y);
  pCollRect->collRectBuffer.lineRight.p1.x = this->position.x + pCollRect->collRect.x + pCollRect->collRect.w;
  pCollRect->collRectBuffer.lineRight.p1.y = this->position.y + pCollRect->collRect.y;
  pCollRect->collRectBuffer.lineRight.p2.x = this->position.x + pCollRect->collRect.x + pCollRect->collRect.w;
  pCollRect->collRectBuffer.lineRight.p2.y = this->position.y + pCollRect->collRect.y + pCollRect->collRect.h;
//printf("LineRight: (%1.2f | %1.2f) (%1.2f | %1.2f)\n", pCollRect->collRectBuffer.lineRight.p1.x, pCollRect->collRectBuffer.lineRight.p1.y, pCollRect->collRectBuffer.lineRight.p2.x, pCollRect->collRectBuffer.lineRight.p2.y);
  pCollRect->collRectBuffer.lineBottom.p1.x = this->position.x + pCollRect->collRect.x;
  pCollRect->collRectBuffer.lineBottom.p1.y = this->position.y + pCollRect->collRect.y + pCollRect->collRect.h;
  pCollRect->collRectBuffer.lineBottom.p2.x = this->position.x + pCollRect->collRect.x + pCollRect->collRect.w;
  pCollRect->collRectBuffer.lineBottom.p2.y = this->position.y + pCollRect->collRect.y + pCollRect->collRect.h;
//printf("LineBottom: (%1.2f | %1.2f) (%1.2f | %1.2f)\n", pCollRect->collRectBuffer.lineBottom.p1.x, pCollRect->collRectBuffer.lineBottom.p1.y, pCollRect->collRectBuffer.lineBottom.p2.x, pCollRect->collRectBuffer.lineBottom.p2.y);
//printf("------------------------------------\n");

  // center

  pCollRect->collRectBuffer.center.x = this->position.x + (size.x * 0.5f);
  pCollRect->collRectBuffer.center.y = this->position.y + (size.y * 0.5f);

  // rotate

  pCollRect->collRectBuffer = this->rotateCollisionBox(pCollRect->collRectBuffer);
}

LECollBox_d LEMdl::rotateCollisionBox(LECollBox_d collBox)
{
  LECollBox_d retCollBox;

  retCollBox.lineLeft.p1 = mathRotatePoint(collBox.lineLeft.p1, collBox.center, this->currentDegree);
  retCollBox.lineLeft.p2 = mathRotatePoint(collBox.lineLeft.p2, collBox.center, this->currentDegree);
  retCollBox.lineRight.p1 = mathRotatePoint(collBox.lineRight.p1, collBox.center, this->currentDegree);
  retCollBox.lineRight.p2 = mathRotatePoint(collBox.lineRight.p2, collBox.center, this->currentDegree);
  retCollBox.lineTop.p1 = mathRotatePoint(collBox.lineTop.p1, collBox.center, this->currentDegree);
  retCollBox.lineTop.p2 = mathRotatePoint(collBox.lineTop.p2, collBox.center, this->currentDegree);
  retCollBox.lineBottom.p1 = mathRotatePoint(collBox.lineBottom.p1, collBox.center, this->currentDegree);
  retCollBox.lineBottom.p2 = mathRotatePoint(collBox.lineBottom.p2, collBox.center, this->currentDegree);

  return retCollBox;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

LEMdl::LEMdl():
sizeFactor(1.0f),
currentDegree(0.0f)
{
  this->pTextureHead = nullptr;
  this->rectPosSize.x = 0;
  this->rectPosSize.y = 0;
  this->rectPosSize.w = 0;
  this->rectPosSize.h = 0;
  this->position.x = 0.0f;
  this->position.y = 0.0f;
  this->pDirectionHead = nullptr;
  this->pCloneHead = nullptr;
  this->pCollisionRectHead = new CollisionRect;
  this->pCollisionRectHead->pLeft = this->pCollisionRectHead;
  this->pCollisionRectHead->pRight = this->pCollisionRectHead;
}

LEMdl::~LEMdl()
{
  // loesche Texturen

  this->memoryClearTextures();

  // loesche Bewegungsrichtungen

  this->memoryClearDirections();

  // loesche Clones

  this->memoryClearClones();

  // loesche Kollisionsbereiche

  this->memoryClearCollisionRects();
}

int LEMdl::mdlCreateTexture(uint32_t idTexture, const char * pFile, SDL_Renderer * pRenderer)
{
  int result = LE_NO_ERROR;
  SDL_Surface * pSurface = nullptr;
  Texture * pNew = this->textureGet(idTexture);

  if(pNew == nullptr)
  {
    this->mtxTexture.lock();

    if(this->pTextureHead == nullptr)
    {
      this->pTextureHead = new Texture;
      this->pTextureHead->pLeft = this->pTextureHead;
      this->pTextureHead->pRight = this->pTextureHead;
      this->pTextureHead->zindex = 0;
    }

    pNew = new Texture;
    pNew->pLeft = this->pTextureHead;
    pNew->pRight = this->pTextureHead->pRight;
    this->pTextureHead->pRight->pLeft = pNew;
    this->pTextureHead->pRight = pNew;
    pNew->id = idTexture;
    pNew->active = LE_TRUE;
    pNew->pTexture = nullptr;
    pNew->pSourceRect = nullptr;
    pNew->idStep = 0.0f;
    pNew->startSet = LE_FALSE;
    pNew->animationEnd = LE_FALSE;
    pNew->zindex = 0;
    pNew->alpha = 255.0f;
    pNew->pSurface = nullptr;
    pNew->pSrcRectHead = nullptr;

    pSurface = IMG_Load(pFile);

    if(pSurface != nullptr)
    {
      this->rectPosSize.w = pSurface->w;
      this->rectPosSize.h = pSurface->h;
      this->updateFrameBox();

      if(SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl"))
      {
        pNew->pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);

        if(pNew->pTexture == nullptr)
          {result = LE_SDL_TEXTURE_LOAD;}

        SDL_FreeSurface(pSurface);

        if(!result)
        {
          if(SDL_SetTextureBlendMode(pNew->pTexture, SDL_BLENDMODE_BLEND))
            {result = LE_SDL_BLENDMODE;}
        }
      }
      else
        {result = LE_SDL_HINT;}
    }
    else
      {result = LE_IMG_LOAD;}

    this->mtxTexture.unlock();
  }
  else
    {result = LE_TEXTURE_EXIST;}

  return result;
}

int LEMdl::mdlDrawActiveTexture(SDL_Renderer * pRenderer)
{
  int result = LE_NO_ERROR;
  Texture * pElem = nullptr;
  SDL_Rect * pSourceRect = nullptr;
  SDL_Rect posSizeBuffer;
  posSizeBuffer.w = this->rectPosSize.w * (int)this->sizeFactor;
  posSizeBuffer.h = this->rectPosSize.h * (int)this->sizeFactor;
  posSizeBuffer.x = this->rectPosSize.x;
  posSizeBuffer.y = this->rectPosSize.y;
  Clone * pClone = nullptr;

  this->mtxTexture.lock();
  this->mtxClone.lock();

  if(this->pTextureHead != nullptr)
  {
    pElem = this->pTextureHead->pRight;

    // draw original
    
    while(pElem != this->pTextureHead)
    {
      if(pElem->active && pElem->pTexture != nullptr && pElem->alpha > 0.0f)
      {
        if(pElem->pSourceRect != nullptr)
          {pSourceRect = &(pElem->pSourceRect->srcRect);}
    
        if(SDL_RenderCopyEx(pRenderer, pElem->pTexture, pSourceRect, &posSizeBuffer, this->currentDegree, nullptr, SDL_FLIP_NONE))
        {
          result = LE_SDL_RENDER_COPY_EX;
          break;
        }
      }
    
      pElem = pElem->pRight;
    }
    
    // draw clones
    
    if(this->pCloneHead != nullptr)
    {
      pElem = this->pTextureHead->pRight;
    
      while(pElem != this->pTextureHead)
      {
        if(pElem->active && pElem->pTexture != nullptr && pElem->alpha > 0.0f)
        {
          pClone = this->pCloneHead->pRight;
    
          while(pClone != this->pCloneHead)
          {
            posSizeBuffer.x = (int)pClone->position.x;
            posSizeBuffer.y = (int)pClone->position.y;
    
            if(pElem->pSourceRect != nullptr)
              {pSourceRect = &(pElem->pSourceRect->srcRect);}
    
            if(pClone->visible)
            {
              if(SDL_RenderCopyEx(pRenderer, pElem->pTexture, pSourceRect, &posSizeBuffer, this->currentDegree, nullptr, SDL_FLIP_NONE))
              {
                result = LE_SDL_RENDER_COPY_EX;
                break;
              }
            }
    
            pClone = pClone->pRight;
          }
    
          if(result)
            {break;}
        }
    
        pElem = pElem->pRight;
      }
    }
  }

  this->mtxClone.unlock();
  this->mtxTexture.unlock();

  return result;
}

int LEMdl::mdlAddTextureSourceRect(uint32_t idTexture, uint32_t idSrcRect, int x, int y, int w, int h)
{
  int result = LE_NO_ERROR;
  Texture * pTexture = this->textureGet(idTexture);
  SourceRect * pNew = nullptr;

  this->mtxTexture.lock();

  if(pTexture != nullptr)
  {
    pNew = this->sourceRectGet(pTexture, idSrcRect);

    if(pNew == nullptr)
    {
      this->mtxSourceRectList.lock();

      if(pTexture->pSrcRectHead == nullptr)
      {
        pTexture->pSrcRectHead = new SourceRect;
        pTexture->pSrcRectHead->pLeft = pTexture->pSrcRectHead;
        pTexture->pSrcRectHead->pRight = pTexture->pSrcRectHead;
      }

      pNew = new SourceRect;
      pNew->pRight = pTexture->pSrcRectHead;
      pNew->pLeft = pTexture->pSrcRectHead->pLeft;
      pTexture->pSrcRectHead->pLeft->pRight = pNew;
      pTexture->pSrcRectHead->pLeft = pNew;
      pNew->id = idSrcRect;
      pNew->srcRect.x = x;
      pNew->srcRect.y = y;
      pNew->srcRect.w = w;
      pNew->srcRect.h = h;

      this->mtxSourceRectList.unlock();
    }
    else
      {result = LE_SOURCE_RECT_EXIST;}
  }
  else
    {result = LE_TEXTURE_NOEXIST;}

  this->mtxTexture.unlock();

  return result;
}

int LEMdl::mdlFocusTextureSourceRect(uint32_t idTexture, uint32_t idSrcRect)
{
  int result = LE_NO_ERROR;
  Texture * pTexture = this->textureGet(idTexture);
  SourceRect * pSrcRect = nullptr;

  if(pTexture != nullptr)
  {
    pSrcRect = this->sourceRectGet(pTexture, idSrcRect);

    if(pSrcRect != nullptr)
      {pTexture->pSourceRect = pSrcRect;}
    else
      {result = LE_SOURCE_RECT_NOEXIST;}
  }
  else
    {result = LE_TEXTURE_NOEXIST;}

  return result;
}

void LEMdl::mdlSetSize(int w, int h)
{
  CollisionRect * pCurrentCollRect = nullptr;

  if(w >= 0 && h >= 0)
  {
    this->rectPosSize.w = w;
    this->rectPosSize.h = h;
    this->updateFrameBox();

    this->mtxCollisionRect.lock();

    pCurrentCollRect = this->pCollisionRectHead->pRight;

    while(pCurrentCollRect != this->pCollisionRectHead)
    {
      this->updateCollisionBox(pCurrentCollRect);
      pCurrentCollRect = pCurrentCollRect->pRight;
    }

    this->mtxCollisionRect.unlock();
  }
}

double LEMdl::mdlSetSize(double percent, int screenWidth)
{
  CollisionRect * pCurrentCollRect = nullptr;
  double factor = percent / (((double) this->rectPosSize.w / (double) screenWidth) * 100.0f);

  this->rectPosSize.w *= (int)factor;
  this->rectPosSize.h *= (int)factor;
  this->updateFrameBox();

  this->mtxCollisionRect.lock();

  pCurrentCollRect = this->pCollisionRectHead->pRight;

  while(pCurrentCollRect != this->pCollisionRectHead)
  {
    this->updateCollisionBox(pCurrentCollRect);
    pCurrentCollRect = pCurrentCollRect->pRight;
  }

  this->mtxCollisionRect.unlock();

  return factor;
}

int LEMdl::mdlSetTextureZindex(uint32_t idTexture, uint32_t zindex)
{
  int result = LE_NO_ERROR;
  Texture * pElem = this->textureGet(idTexture);
  Texture * pCurrent = nullptr;

  if(pElem != nullptr)
  {
    this->mtxTexture.lock();

    // exclude texture from list

    pElem->pLeft->pRight = pElem->pRight;
    pElem->pRight->pLeft = pElem->pLeft;
    pElem->zindex = zindex;

    // find right place

    pCurrent = this->pTextureHead->pRight;

    while(pElem->zindex > pCurrent->zindex && pCurrent != this->pTextureHead)
      {pCurrent = pCurrent->pRight;}

    // include at right position

    pElem->pLeft = pCurrent->pLeft;
    pElem->pRight = pCurrent;
    pCurrent->pLeft->pRight = pElem;
    pCurrent->pLeft = pElem;

    this->mtxTexture.unlock();
  }
  else
    {result = LE_TEXTURE_NOEXIST;}

  return result;
}

int LEMdl::mdlSetTextureActive(uint32_t idTexture, bool active)
{
  int result = LE_NO_ERROR;
  Texture * pElem = this->textureGet(idTexture);

  if(pElem != nullptr)
    {pElem->active = active;}
  else
    {result = LE_TEXTURE_NOEXIST;}

  return result;
}

void LEMdl::mdlSetPosition(double x, double y)
{
  CollisionRect * pCurrentCollRect = nullptr;
  this->position.x = (float)x;
  this->position.y = (float)y;
  this->rectPosSize.x = (int)x;
  this->rectPosSize.y = (int)y;
  this->updateFrameBox();

  this->mtxCollisionRect.lock();

  pCurrentCollRect = this->pCollisionRectHead->pRight;

  while(pCurrentCollRect != this->pCollisionRectHead)
  {
    this->updateCollisionBox(pCurrentCollRect);
    pCurrentCollRect = pCurrentCollRect->pRight;
  }

  this->mtxCollisionRect.unlock();
}

int LEMdl::mdlAddDirection(uint32_t idDirection, glm::vec2 direction)
{
  int result = LE_NO_ERROR;
  LinkedVec2 * pNew = this->directionGet(idDirection);

  if(pNew == nullptr)
  {
    this->mtxDirection.lock();

    if(this->pDirectionHead == nullptr)
    {
      this->pDirectionHead = new LinkedVec2;
      this->pDirectionHead->pLeft = this->pDirectionHead;
      this->pDirectionHead->pRight = this->pDirectionHead;
    }

    pNew = new LinkedVec2;
    pNew->pLeft = this->pDirectionHead->pLeft;
    pNew->pRight = this->pDirectionHead;
    this->pDirectionHead->pLeft->pRight = pNew;
    this->pDirectionHead->pLeft = pNew;
    pNew->id = idDirection;
    pNew->data = direction;
    pNew->currentDegree = 0.0f;

    this->mtxDirection.unlock();
  }
  else
    {result = LE_DIRECTION_EXIST;}

  return result;
}

int LEMdl::mdlMoveDirection(uint32_t idDirection, double timestep)
{
  int result = LE_NO_ERROR;
  CollisionRect * pCurrentCollRect = nullptr;
  LinkedVec2 * pDirection = this->directionGet(idDirection);

  if(pDirection != nullptr)
  {
    this->position.x += pDirection->data.x * (float)timestep;
    this->position.y += pDirection->data.y * (float)timestep;
    this->rectPosSize.x = (int)this->position.x;
    this->rectPosSize.y = (int)this->position.y;
    this->updateFrameBox();

    this->mtxCollisionRect.lock();

    pCurrentCollRect = this->pCollisionRectHead->pRight;

    while(pCurrentCollRect != this->pCollisionRectHead)
    {
      this->updateCollisionBox(pCurrentCollRect);
      pCurrentCollRect = pCurrentCollRect->pRight;
    }

    this->mtxCollisionRect.unlock();
  }
  else
    {result = LE_DIRECTION_NOEXIST;}

  return result;
}

void LEMdl::mdlRotate(double ndegree, double timestep)
{
  CollisionRect * pCurrentCollRect = nullptr;
  this->currentDegree = mathMod((this->currentDegree + ndegree * timestep), 360.0f);
  this->updateFrameBox();

  this->mtxCollisionRect.lock();

  pCurrentCollRect = this->pCollisionRectHead->pRight;

  while(pCurrentCollRect != this->pCollisionRectHead)
  {
    this->updateCollisionBox(pCurrentCollRect);
    pCurrentCollRect = pCurrentCollRect->pRight;
  }

  this->mtxCollisionRect.unlock();
}

void LEMdl::mdlRotateOnce(double ndegree)
{
  CollisionRect * pCurrentCollRect = nullptr;
  this->currentDegree += ndegree;
  this->updateFrameBox();

  this->mtxCollisionRect.lock();

  pCurrentCollRect = this->pCollisionRectHead->pRight;

  while(pCurrentCollRect != this->pCollisionRectHead)
  {
    this->updateCollisionBox(pCurrentCollRect);
    pCurrentCollRect = pCurrentCollRect->pRight;
  }

  this->mtxCollisionRect.unlock();
}

int LEMdl::mdlSetTextureAlpha(uint32_t idTexture, uint8_t alpha)
{
  int result = LE_NO_ERROR;
  Texture * pElem = this->textureGet(idTexture);

  if(pElem != nullptr)
  {
    pElem->alpha = (double) alpha;

    if(SDL_SetTextureAlphaMod(pElem->pTexture, (uint8_t) pElem->alpha))
      {result = LE_ALPHA_MOD;}
  }
  else
    {result = LE_TEXTURE_NOEXIST;}

  return result;
}

int LEMdl::mdlFadeTexture(uint32_t idTexture, double alphaPerSecond, double timestep)
{
  int result = LE_NO_ERROR;
  Texture * pElem = this->textureGet(idTexture);

  if(pElem != nullptr)
  {
    pElem->alpha += (alphaPerSecond * timestep);

    if(pElem->alpha <= 0.0f)
      {pElem->alpha = 0.0f;}

    if(pElem->alpha >= 255.0f)
      {pElem->alpha = 255.0f;}

    if(SDL_SetTextureAlphaMod(pElem->pTexture, (uint8_t) pElem->alpha))
      {result = LE_ALPHA_MOD;}
  }
  else
    {result = LE_TEXTURE_NOEXIST;}

  return result;
}

int LEMdl::mdlRotateDir(uint32_t idDirection, double degree, double timestep)
{
  int result = LE_NO_ERROR;
  LinkedVec2 * pDirection = this->directionGet(idDirection);

  if(pDirection != nullptr)
  {
    pDirection->currentDegree += degree * timestep;
    pDirection->data = glm::rotate(pDirection->data, (float)pDirection->currentDegree);
  }
  else
    {result = LE_DIRECTION_NOEXIST;}

  return result;
}

SDL_Point LEMdl::mdlGetSize()
{
  SDL_Point size;
  size.x = (int)this->sizeFactor * this->rectPosSize.w;
  size.y = (int)this->sizeFactor * this->rectPosSize.h;

  return size;
}

SDL_Point LEMdl::mdlGetPosition()
{
  SDL_Point position;
  position.x = this->rectPosSize.x;
  position.y = this->rectPosSize.y;

  return position;
}

glm::vec2 LEMdl::mdlGetPositionD()
{
  return this->position;
}

double LEMdl::mdlGetTextureAlpha(uint32_t idTexture)
{
  double alpha = 0;
  Texture * pElem = this->textureGet(idTexture);

  if(pElem != nullptr)
    {alpha = pElem->alpha;}

  return alpha;
}

double LEMdl::mdlGetSizeFactor()
{
  return this->sizeFactor;
}

void LEMdl::mdlSetSizeFactor(double nsizeFactor)
{
  CollisionRect * pCurrentCollRect = nullptr;

  if(nsizeFactor > 0.0f)
  {
    this->sizeFactor = nsizeFactor;
    this->updateFrameBox();

    this->mtxCollisionRect.lock();

    pCurrentCollRect = this->pCollisionRectHead->pRight;

    while(pCurrentCollRect != this->pCollisionRectHead)
    {
      this->updateCollisionBox(pCurrentCollRect);
      pCurrentCollRect = pCurrentCollRect->pRight;
    }

    this->mtxCollisionRect.unlock();
  }
}

int LEMdl::mdlCreateSurface(uint32_t idTexture, const char * pFile)
{
  int result = LE_NO_ERROR;
  Texture * pElem = this->textureGet(idTexture);

  if(pElem != nullptr)
  {
    if(pElem->pSurface == nullptr)
    {
      pElem->pSurface = IMG_Load(pFile);

      if(pElem->pSurface == nullptr)
        {result = LE_IMG_LOAD;}   
    } 
  }
  else
    {result = LE_TEXTURE_NOEXIST;}

  return result;
}

int LEMdl::mdlDeleteSurface(uint32_t idTexture)
{
  int result = LE_NO_ERROR;
  Texture * pElem = this->textureGet(idTexture);

  if(pElem != nullptr)
  {
    if(pElem->pSurface != nullptr)
    {
      SDL_FreeSurface(pElem->pSurface);
      pElem->pSurface = nullptr;
    } 
  }
  else
    {result = LE_TEXTURE_NOEXIST;}

  return result;
}

SDL_Surface * LEMdl::mdlGetSurface(uint32_t idTexture)
{
  SDL_Surface * pSurface = nullptr;
  Texture * pElem = this->textureGet(idTexture);

  if(pElem != nullptr)
    {pSurface = pElem->pSurface;}

  return pSurface;
}

Color LEMdl::mdlGetPixelRGBA(uint32_t idTexture, uint32_t x, uint32_t y)
{
  Color pixel;
  Texture * pElem = this->textureGet(idTexture);
  uint8_t * pPixel = nullptr;
  uint32_t startIndex = 0;

  if(pElem != nullptr)
  {
    if(pElem->pSurface != nullptr)
    {
      pPixel = (uint8_t*) pElem->pSurface->pixels;
      startIndex = x * 4 + y * pElem->pSurface->w * 4;
      pixel.r = pPixel[startIndex];
      pixel.g = pPixel[startIndex + 1];
      pixel.b = pPixel[startIndex + 2];
      pixel.a = pPixel[startIndex + 3];
    } 
  }

  return pixel;
}

glm::vec2 LEMdl::mdlGetDirection(uint32_t idDirection)
{
  glm::vec2 direction = {0.0f, 0.0f};
  LinkedVec2 * pDirection = this->directionGet(idDirection);

  if(pDirection != nullptr)
    {direction = pDirection->data;}

  return direction;
}

int LEMdl::mdlChangeDirection(uint32_t idDirection, glm::vec2 dir)
{
  int result = LE_NO_ERROR;
  LinkedVec2 * pDirection = this->directionGet(idDirection);

  if(pDirection != nullptr)
    {pDirection->data = dir;}
  else
    {result = LE_DIRECTION_NOEXIST;}

  return result;
}

int LEMdl::mdlCreateClone(uint32_t idClone)
{
  int result = LE_NO_ERROR;
  Clone * pClone = this->cloneGet(idClone);

  if(pClone == nullptr)
  {
    this->mtxClone.lock();

    if(this->pCloneHead == nullptr)
    {
      this->pCloneHead = new Clone;
      this->pCloneHead->pLeft = this->pCloneHead;
      this->pCloneHead->pRight = this->pCloneHead;
      this->pCloneHead->id = 0;
    }

    pClone = new Clone;
    pClone->pRight = this->pCloneHead;
    pClone->pLeft = this->pCloneHead->pLeft;
    this->pCloneHead->pLeft->pRight = pClone;
    this->pCloneHead->pLeft = pClone;
    pClone->id = idClone;
    pClone->position = {0.0f, 0.0f};
    pClone->visible = LE_TRUE;

    this->mtxClone.unlock();
  }
  else
    {result = LE_MDL_CLONE_EXIST;}

  return result;
}

int LEMdl::mdlSetClonePosition(uint32_t idClone, glm::vec2 position)
{
  int result = LE_NO_ERROR;
  Clone * pClone = this->cloneGet(idClone);

  if(pClone != nullptr)
    {pClone->position = position;}
  else
    {result = LE_MDL_CLONE_NOEXIST;}

  return result;
}

void LEMdl::mdlClearClones()
{
  this->memoryClearClones();
}

int LEMdl::mdlSetCloneVisible(uint32_t idClone, bool visible)
{
  int result = LE_NO_ERROR;
  Clone * pClone = this->cloneGet(idClone);

  if(pClone != nullptr)
    {pClone->visible = visible;}
  else
    {result = LE_MDL_CLONE_NOEXIST;}

  return result;
}

int LEMdl::mdlAddCollisionRect(uint32_t idCollRect, SDL_Rect collRect)
{
  int result = LE_NO_ERROR;
  CollisionRect * pCollRect = this->collisionRectGet(idCollRect);

  if(pCollRect == nullptr)
  {
    this->mtxCollisionRect.lock();

    pCollRect = new CollisionRect;
    pCollRect->pRight = this->pCollisionRectHead;
    pCollRect->pLeft = this->pCollisionRectHead->pLeft;
    this->pCollisionRectHead->pLeft->pRight = pCollRect;
    this->pCollisionRectHead->pLeft = pCollRect;
    pCollRect->id = idCollRect;
    pCollRect->collRect = collRect;
    this->updateCollisionBox(pCollRect);

    this->mtxCollisionRect.unlock();
  }
  else
    {result = LE_MDL_COLL_RECT_EXIST;}

  return result;
}

double LEMdl::mdlGetCurrentDegree()
{
  return this->currentDegree;
}

LECollBox_d LEMdl::mdlGetFrameBox()
{
  return this->bufferFrameBox;
}

LECollBox_d LEMdl::mdlGetCollisionBox(uint32_t idCollRect)
{
  LECollBox_d collisionBox;
  CollisionRect * pCollRect = this->collisionRectGet(idCollRect);

  if(pCollRect != nullptr)
    {collisionBox = pCollRect->collRectBuffer;}

  return collisionBox;
}

uint32_t LEMdl::mdlGetAmountOfCollisionBoxes()
{
  this->mtxCollisionRect.lock();
  uint32_t amount = 0;
  CollisionRect * pCurrent = this->pCollisionRectHead->pRight;

  while(pCurrent != this->pCollisionRectHead)
  {
    amount++;
    pCurrent = pCurrent->pRight;
  }

  this->mtxCollisionRect.unlock();
  return amount;
}

uint32_t LEMdl::mdlGetAmountOfTextureSourceRectangles(uint32_t idTexture)
{
  uint32_t amount = 0;
  Texture * pTexture = this->textureGet(idTexture);
  SourceRect * pCurrent;

  if(pTexture != nullptr)
  {
    this->mtxSourceRectList.lock();

    pCurrent = pTexture->pSrcRectHead->pRight;

    while(pCurrent != pTexture->pSrcRectHead)
    {
      amount++;
      pCurrent = pCurrent->pRight;
    }

    this->mtxSourceRectList.unlock();
  }

  return amount;
}

bool LEMdl::mdlTextureExist(uint32_t idTexture)
{
  bool textureExist = LE_FALSE;
  Texture * pTexture = this->textureGet(idTexture);

  if(pTexture != nullptr)
    {textureExist = LE_TRUE;}

  return textureExist;
}

bool LEMdl::mdlFinishedAllMutexes()
{
  bool finished = LE_TRUE;
  bool cloneLocked = LE_FALSE;
  bool collisionRectLocked = LE_FALSE;
  bool directionLocked = LE_FALSE;
  bool srcRectLocked = LE_FALSE;
  bool textureLocked = LE_FALSE;

  // clone

  if(this->mtxClone.try_lock())
  {
    finished = finished && LE_TRUE;
    cloneLocked = LE_TRUE;
  }
  else
    {finished = finished && LE_FALSE;}

  // collision rect

  if(this->mtxCollisionRect.try_lock())
  {
    finished = finished && LE_TRUE;
    collisionRectLocked = LE_TRUE;
  }
  else
    {finished = finished && LE_FALSE;}

  // direction

  if(this->mtxDirection.try_lock())
  {
    finished = finished && LE_TRUE;
    directionLocked = LE_TRUE;
  }
  else
    {finished = finished && LE_FALSE;}

  // source rectangle

  if(this->mtxSourceRectList.try_lock())
  {
    finished = finished && LE_TRUE;
    srcRectLocked = LE_TRUE;
  }
  else
    {finished = finished && LE_FALSE;}

  // texture

  if(this->mtxTexture.try_lock())
  {
    finished = finished && LE_TRUE;
    textureLocked = LE_TRUE;
  }
  else
    {finished = finished && LE_FALSE;}

  // unlock if necessary

  if(cloneLocked)
    {this->mtxClone.unlock();}
  if(collisionRectLocked)
    {this->mtxCollisionRect.unlock();}
  if(directionLocked)
    {this->mtxDirection.unlock();}
  if(srcRectLocked)
    {this->mtxSourceRectList.unlock();}
  if(textureLocked)
    {this->mtxTexture.unlock();}

  return finished;
}