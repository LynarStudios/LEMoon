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
        sprintf(pErrorString, "LEMoon::textDraw(%d)\n\n", pText->id);
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

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public text
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::textCreate(uint32_t id)
{
  int result = LE_NO_ERROR;
  LEText * pNew = this->textGet(id);

  if(pNew == nullptr)
  {
    if(this->pTextHead == nullptr)
    {
      this->pTextHead = new LEText;
      this->pTextHead->pLeft = this->pTextHead;
      this->pTextHead->pRight = this->pTextHead;
      this->pTextHead->zindex = 0;
      this->pTextHead->id = 1989;
    }

    pNew = new LEText;
    pNew->pRight = this->pTextHead;
    pNew->pLeft = this->pTextHead->pLeft;
    this->pTextHead->pLeft->pRight = pNew;
    this->pTextHead->pLeft = pNew;
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

  return result;
}

int LEMoon::textDelete(uint32_t id)
{
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);
  LinkedVec2 * pCurrentDirection = nullptr;
  LinkedVec2 * pNextDirection = nullptr;
  LELetter * pCurrentLetter = nullptr;
  LELetter * pNextLetter = nullptr;

  if(pText != nullptr)
  {
    pText->pLeft->pRight = pText->pRight;
    pText->pRight->pLeft = pText->pLeft;

    // loesche Bewegungsrichtungen

    if(pText->pDirectionHead != nullptr)
    {
      pCurrentDirection = pText->pDirectionHead->pRight;

      while(pCurrentDirection != pText->pDirectionHead)
      {
        pNextDirection = pCurrentDirection->pRight;
        delete pCurrentDirection;
        pCurrentDirection = pNextDirection;
      }

      delete pText->pDirectionHead;
      pText->pDirectionHead = nullptr;
    }

    // loesche Buchstaben

    if(pText->pLetterHead != nullptr)
    {
      pCurrentLetter = pText->pLetterHead->pRight;

      while(pCurrentLetter != pText->pLetterHead)
      {
        pNextLetter = pCurrentLetter->pRight;
        delete pCurrentLetter;
        pCurrentLetter = pNextLetter;
      }

      delete pText->pLetterHead;
      pText->pLetterHead = nullptr;
    }

    // loesche Text

    if(pText->pText != nullptr)
    {
      delete [] pText->pText;
      pText->pText = nullptr;
    }

    // loesche Textur

    if(pText->pTexture != nullptr)
    {
      SDL_DestroyTexture(pText->pTexture);
      pText->pTexture = nullptr;
    }

    delete pText;

    if(this->pTextHead->pLeft == this->pTextHead && this->pTextHead->pRight == this->pTextHead)
    {
      delete this->pTextHead;
      this->pTextHead = nullptr;
    }
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
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);
  LELetter * pLetter = nullptr;

  if(pText != nullptr)
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
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);
  uint32_t index = 0;
  LELetter * pLetter = nullptr;

  if(pText != nullptr)
  {
    // erstelle einen Textbuffer

    if(pText->pText != nullptr)
    {
      delete [] pText->pText;
      pText->pText = nullptr;
    }

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
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);

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
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);

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
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);
  LEText * pCurrent = nullptr;
  bool moreThanOneElement = this->pTextHead->pLeft->id != this->pTextHead->pRight->id;

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

  if(moreThanOneElement)
  {
    if(!result && pText != nullptr)
    {
      // auskoppeln
    
      pText->pLeft->pRight = pText->pRight;
      pText->pRight->pLeft = pText->pLeft;
      pText->zindex = zindex;
    
      // neu einordnen
    
      pCurrent = this->pTextHead->pRight;
    
      while(pCurrent != this->pTextHead)
      {
        if(pText->zindex >= pCurrent->zindex)
        {
          // dahinter einfuegen
    
          pText->pLeft = pCurrent;
          pText->pRight = pCurrent->pRight;
          pCurrent->pRight->pLeft = pText;
          pCurrent->pRight = pText;
          break;
        }
    
        pCurrent = pCurrent->pRight;
      }
    }
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

  return result;
}

int LEMoon::textRelateFont(uint32_t id, uint32_t idFont)
{
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);
  LEFont * pFont = this->fontGet(idFont);

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
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);
  SDL_Surface * pSurface = nullptr;
  SDL_Color color;

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
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);

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
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);
  uint32_t index = 0;
  LELetter * pLetter = nullptr;

  if(pText != nullptr)
  {
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
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);

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
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);

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
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);
  LELetter * pLetter = nullptr;
  LELetter * pNextLetter = nullptr;

  if(pText != nullptr)
  {
    // loesche Text

    if(pText->pText != nullptr)
    {
      delete [] pText->pText;
      pText->pText = nullptr;
    }

    // loesche Buchstaben

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
  LEText * pText = this->textGet(id);
  double alpha = 0.0f;

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
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);
  LinkedVec2 * pNew = nullptr;

  if(pText != nullptr)
  {
    pNew = this->textGetDirection(pText, idDirection);

    if(pNew == nullptr)
    {
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
  int result = LE_NO_ERROR;
  LEText * pText = this->textGet(id);
  LinkedVec2 * pDirection = nullptr;

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
  SDL_Point pos;
  LEText * pText = this->textGet(id);

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
  SDL_Point size;
  LEText * pText = this->textGet(id);

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
  bool visible = LE_FALSE;
  LEText * pText = this->textGet(id);

  if(pText != nullptr)
    {visible = pText->visible;}

  return visible;
}