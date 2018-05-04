/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Visual Studio 2015 Community, g++ Compiler
  date:               18.05.2017
  updated:            04.05.2018
*/

#include "../include/le_moon.h"
#include "../include/le_glb.h"

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// private memory
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void LEMoon::memoryClearTimeEvents()
{
  LETimeEvent * pCurrent = nullptr;
  LETimeEvent * pNext = nullptr;

  if(this->pTimeEventHead != nullptr)
  {
    pCurrent = this->pTimeEventHead->pRight;

    while(pCurrent != this->pTimeEventHead)
    {
      pNext = pCurrent->pRight;
      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pTimeEventHead;
    this->pTimeEventHead = nullptr;
  }

  if(this->pTimeEventHeadBuffer != nullptr)
  {
    pCurrent = this->pTimeEventHeadBuffer->pRight;

    while(pCurrent != this->pTimeEventHeadBuffer)
    {
      pNext = pCurrent->pRight;
      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pTimeEventHeadBuffer;
    this->pTimeEventHeadBuffer = nullptr;
  }
}

void LEMoon::memoryClearFonts()
{
  LEFont * pCurrent = nullptr;
  LEFont * pNext = nullptr;

  // original

  if(this->pFontHead != nullptr)
  {
    pCurrent = this->pFontHead->pRight;

    while(pCurrent != this->pFontHead)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->pFont != nullptr)
        {TTF_CloseFont(pCurrent->pFont);}

      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pFontHead;
    this->pFontHead = nullptr;
  }

  // buffer

  if(this->pFontHeadBuffer != nullptr)
  {
    pCurrent = this->pFontHeadBuffer->pRight;

    while(pCurrent != this->pFontHeadBuffer)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->pFont != nullptr)
        {TTF_CloseFont(pCurrent->pFont);}

      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pFontHeadBuffer;
    this->pFontHeadBuffer = nullptr;
  }
}

void LEMoon::memoryClearSounds()
{
  LESound * pCurrent = nullptr;
  LESound * pNext = nullptr;

  if(this->pSoundHead != nullptr)
  {
    pCurrent = this->pSoundHead->pRight;

    while(pCurrent != this->pSoundHead)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->pSample != nullptr)
        {Mix_FreeChunk(pCurrent->pSample);}

      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pSoundHead;
    this->pSoundHead = nullptr;
  }

  if(this->pSoundHeadBuffer != nullptr)
  {
    pCurrent = this->pSoundHeadBuffer->pRight;

    while(pCurrent != this->pSoundHeadBuffer)
    {
      pNext = pCurrent->pRight;

      if(pCurrent->pSample != nullptr)
        {Mix_FreeChunk(pCurrent->pSample);}

      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pSoundHeadBuffer;
    this->pSoundHeadBuffer = nullptr;
  }
}

void LEMoon::memoryClearTexts()
{
  LEText * pCurrent = nullptr;
  LEText * pNext = nullptr;
  LinkedVec2 * pCurrentDirection = nullptr;
  LinkedVec2 * pNextDirection = nullptr;
  LELetter * pCurrentLetter = nullptr;
  LELetter * pNextLetter = nullptr;

  // original

  if(this->pTextHead != nullptr)
  {
    pCurrent = this->pTextHead->pRight;

    while(pCurrent != this->pTextHead)
    {
      pNext = pCurrent->pRight;

      // loesche Bewegungsrichtungen

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

      // loesche Buchstaben

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

      // loesche Text

      if(pCurrent->pText != nullptr)
      {
        delete [] pCurrent->pText;
        pCurrent->pText = nullptr;
      }

      // loesche Textur

      if(pCurrent->pTexture != nullptr)
      {
        SDL_DestroyTexture(pCurrent->pTexture);
        pCurrent->pTexture = nullptr;
      }

      // loesche aktuellen Text

      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pTextHead;
    this->pTextHead = nullptr;
  }

  // buffer

  if(this->pTextHeadBuffer != nullptr)
  {
    pCurrent = this->pTextHeadBuffer->pRight;

    while(pCurrent != this->pTextHeadBuffer)
    {
      pNext = pCurrent->pRight;

      // loesche Bewegungsrichtungen

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

      // loesche Buchstaben

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

      // loesche Text

      if(pCurrent->pText != nullptr)
      {
        delete [] pCurrent->pText;
        pCurrent->pText = nullptr;
      }

      // loesche Textur

      if(pCurrent->pTexture != nullptr)
      {
        SDL_DestroyTexture(pCurrent->pTexture);
        pCurrent->pTexture = nullptr;
      }

      // loesche aktuellen Text

      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pTextHeadBuffer;
    this->pTextHeadBuffer = nullptr;
  }
}

void LEMoon::memoryClearPoints()
{
  LEPoint * pCurrent = nullptr;
  LEPoint * pNext = nullptr;
  LinkedVec2 * pCurrentDirection = nullptr;
  LinkedVec2 * pNextDirection = nullptr;

  if(this->pPointHead != nullptr)
  {
    pCurrent = this->pPointHead->pRight;

    while(pCurrent != this->pPointHead)
    {
      pNext = pCurrent->pRight;

      // loesche Bewegungsrichtungen

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

      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pPointHead;
    this->pPointHead = nullptr;
  }

  // buffer

  if(this->pPointHeadBuffer != nullptr)
  {
    pCurrent = this->pPointHeadBuffer->pRight;

    while(pCurrent != this->pPointHeadBuffer)
    {
      pNext = pCurrent->pRight;

      // loesche Bewegungsrichtungen

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

      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pPointHeadBuffer;
    this->pPointHeadBuffer = nullptr;
  }
}

void LEMoon::memoryClearModels()
{
  LEModel * pCurrent = nullptr;
  LEModel * pNext = nullptr;

  if(this->pModelHead != nullptr)
  {
    pCurrent = this->pModelHead->pRight;

    while(pCurrent != this->pModelHead)
    {
      pNext = pCurrent->pRight;
      delete pCurrent->pModel;
      pCurrent->pModel = nullptr;
      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pModelHead;
    this->pModelHead = nullptr;
  }

  // buffer

  if(this->pModelHeadBuffer != nullptr)
  {
    pCurrent = this->pModelHeadBuffer->pRight;

    while(pCurrent != this->pModelHeadBuffer)
    {
      pNext = pCurrent->pRight;
      delete pCurrent->pModel;
      pCurrent->pModel = nullptr;
      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pModelHeadBuffer;
    this->pModelHeadBuffer = nullptr;
  }
}

void LEMoon::memoryClearLines()
{
  LELine * pCurrent = nullptr;
  LELine * pNext = nullptr;

  if(this->pLineHead != nullptr)
  {
    pCurrent = this->pLineHead->pRight;

    while(pCurrent != this->pLineHead)
    {
      pNext = pCurrent->pRight;
      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pLineHead;
    this->pLineHead = nullptr;
  }

  // buffer

  if(this->pLineHeadBuffer != nullptr)
  {
    pCurrent = this->pLineHeadBuffer->pRight;

    while(pCurrent != this->pLineHeadBuffer)
    {
      pNext = pCurrent->pRight;
      delete pCurrent;
      pCurrent = pNext;
    }

    delete this->pLineHeadBuffer;
    this->pLineHeadBuffer = nullptr;
  }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// private general
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::drawWithZindex()
{
  int result = LE_NO_ERROR;
  LEModel * pModel = nullptr;
  LEText * pText = nullptr;
  LELine * pLine = nullptr;
  LEPoint * pPoint = nullptr;
  uint32_t zindex = 1;
  const uint32_t AMOUNT_OBJECTS = 4;
  uint32_t fakeZindex = 0;

  // inizialize

  if(this->pModelHead != nullptr)
  {
    pModel = this->pModelHead->pRight;
    zindex = mathMin(zindex, pModel->zindex);
  }

  if(this->pTextHead != nullptr)
  {
    pText = this->pTextHead->pRight;
    zindex = mathMin(zindex, pText->zindex);
  }

  if(this->pLineHead != nullptr)
  {
    pLine = this->pLineHead->pRight;
    zindex = mathMin(zindex, pLine->zindex);
  }

  if(this->pPointHead != nullptr)
  {
    pPoint = this->pPointHead->pRight;
    zindex = mathMin(zindex, pPoint->zindex);
  }

  uint32_t zindexArray[AMOUNT_OBJECTS]; // 0 = Model, 1 = Texts, 2 = Lines, 3 = Point

  for(uint32_t i = 0 ; i < AMOUNT_OBJECTS ; i++)
    {zindexArray[i] = 0;}

  // draw

  while(pModel != this->pModelHead || pText != this->pTextHead || pLine != this->pLineHead || pPoint != this->pPointHead)
  {
    // models

    while(pModel != this->pModelHead && pModel->zindex <= zindex)
    {
      result = this->modelDraw(pModel);

      if(result)
        {break;}
      else
      {
        if(pModel != this->pModelHead)
          {pModel = pModel->pRight;}
      }
    }

    if(result)
      {break;}

    // texts

    while(pText != this->pTextHead && pText->zindex <= zindex)
    {
      result = this->textDraw(pText);

      if(result)
        {break;}
      else
      {
        if(pText != this->pTextHead)
          {pText = pText->pRight;}
      }
    }

    if(result)
      {break;}

    // lines

    while(pLine != this->pLineHead && pLine->zindex <= zindex)
    {
      result = this->lineDraw(pLine);

      if(result)
        {break;}
      else
      {
        if(pLine != this->pLineHead)
          {pLine = pLine->pRight;}
      }
    }

    if(result)
      {break;}

    // points

    while(pPoint != this->pPointHead && pPoint->zindex <= zindex)
    {
      result = this->pointDraw(pPoint);

      if(result)
        {break;}
      else
      {
        if(pPoint != this->pPointHead)
          {pPoint = pPoint->pRight;}
      }
    }

    if(result)
      {break;}

    // text, models, points and lines still available?

    for(uint32_t i = 0 ; i < AMOUNT_OBJECTS ; i++)
      {zindexArray[i] = 0;}

    if(pText != this->pTextHead && pModel != this->pModelHead && pLine != this->pLineHead && pPoint != this->pPointHead)
      {zindex = mathMin(mathMin(mathMin(pModel->zindex, pText->zindex), pLine->zindex), pPoint->zindex);}
    else
    {
      // zindex auslesen und setzen

      if(pModel != this->pModelHead)
        {zindexArray[0] = pModel->zindex;}

      if(pText != this->pTextHead)
        {zindexArray[1] = pText->zindex;}

      if(pLine != this->pLineHead)
        {zindexArray[2] = pLine->zindex;}

      if(pPoint != this->pPointHead)
        {zindexArray[3] = pPoint->zindex;}

      // tote zindex anpassen

      for(uint32_t i = 0 ; i < AMOUNT_OBJECTS ; i++)
      {
        if(zindexArray[i] != 0)
        {
          fakeZindex = zindexArray[i];
          break;
        }
      }

      for(uint32_t i = 0 ; i < AMOUNT_OBJECTS ; i++)
      {
        if(zindexArray[i] == 0)
          {zindexArray[i] = fakeZindex;}
      }

      // naechsten zindex bestimmen

      zindex = mathMin(zindexArray, AMOUNT_OBJECTS);
    }
  }

  return result;
}

void LEMoon::printErrorDialog(int error, const char * pErrorInfo)
{
  this->mtxGeneral.printErrorDialog.lock();
  size_t lengthErrorInfo = 0;

  if(pErrorInfo != nullptr)
    {lengthErrorInfo = strlen(pErrorInfo);}

  char * pErrorString = new char[lengthErrorInfo + 256 + 1];

  switch(error)
  {
    case LE_NO_ERROR:
    {} break;
    case LE_SDL_INIT:
    {
      sprintf(pErrorString, "%sSDL_Init() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SDL_WINDOW:
    {
      sprintf(pErrorString, "%sSDL_CreateWindow() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SDL_DISPLAYMODE:
    {
      sprintf(pErrorString, "%sSDL_GetCurrentDisplayMode() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SDL_RENDERER:
    {
      sprintf(pErrorString, "%sSDL_CreateRenderer() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SDL_DRAW_COLOR:
    {
      sprintf(pErrorString, "%sSDL_SetRenderDrawColor() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SDL_CLEAR_RENDERER:
    {
      sprintf(pErrorString, "%sSDL_RenderClear() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SDL_SHOW_CURSOR:
    {
      sprintf(pErrorString, "%sSDL_ShowCursor() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_MDL_EXIST:
    {
      sprintf(pErrorString, "%sid for model already exists!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_MDL_NOEXIST:
    {
      sprintf(pErrorString, "%sid for model does not exist!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_TEXTURE_EXIST:
    {
      sprintf(pErrorString, "%sid for texture already exists!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_TEXTURE_NOEXIST:
    {
      sprintf(pErrorString, "%sid for texture does not exist!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_IMG_LOAD:
    {
      sprintf(pErrorString, "%sIMG_Load() failed!\n%s\n%s", pErrorInfo, SDL_GetError(), IMG_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SDL_TEXTURE_LOAD:
    {
      sprintf(pErrorString, "%sSDL_CreateTextureFromSurface() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SDL_IMG_INIT:
    {
      sprintf(pErrorString, "%sIMG_Init() failed!\n%s\n%s", pErrorInfo, SDL_GetError(), IMG_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SDL_RENDER_COPY_EX:
    {
      sprintf(pErrorString, "%sSDL_RenderCopyEx() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SOURCE_RECT_EXIST:
    {
      sprintf(pErrorString, "%sid for source rect already exists!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SOURCE_RECT_NOEXIST:
    {
      sprintf(pErrorString, "%sid for source rect does not exist!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SOURCE_RECT_ANIMATION_NOEXIST:
    {
      sprintf(pErrorString, "%scouldn't find any source rectangles for animation!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_TIMEEVENT_NOEXIST:
    {
      sprintf(pErrorString, "%sid for time event does not exist!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_TIMEEVENT_EXIST:
    {
      sprintf(pErrorString, "%sid for time event already exists!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SDL_BLENDMODE:
    {
      sprintf(pErrorString, "%sSDL_SetTextureBlendMode() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_DIRECTION_NOEXIST:
    {
      sprintf(pErrorString, "%sid for direction does not exist!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_DIRECTION_EXIST:
    {
      sprintf(pErrorString, "%sid for direction already exists!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_ALPHA_MOD:
    {
      sprintf(pErrorString, "%sSDL_SetTextureAlphaMod() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_POINT_NOEXIST:
    {
      sprintf(pErrorString, "%sid for point does not exist!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_POINT_EXIST:
    {
      sprintf(pErrorString, "%sid for point already exists!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_DRAW_POINT:
    {
      sprintf(pErrorString, "%sSDL_RenderDrawPoint() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_DRAW_BLEND_MODE:
    {
      sprintf(pErrorString, "%sSDL_SetRenderDrawBlendMode() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_MIXER_INIT:
    {
      sprintf(pErrorString, "%sMix_Init() failed!\n%s\n%s", pErrorInfo, SDL_GetError(), Mix_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_OPEN_AUDIO:
    {
      sprintf(pErrorString, "%sMix_OpenAudio() failed!\n%s\n%s", pErrorInfo, SDL_GetError(), Mix_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SOUND_EXIST:
    {
      sprintf(pErrorString, "%sid for sound already exists!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SOUND_NOEXIST:
    {
      sprintf(pErrorString, "%sid for sound does not exist!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_LOAD_WAV:
    {
      sprintf(pErrorString, "%sMix_LoadWAV() failed!\n%s\n%s", pErrorInfo, SDL_GetError(), Mix_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_ALLOC_CHANNELS:
    {
      sprintf(pErrorString, "%sMix_AllocateChannels() failed!\n%s\n%s", pErrorInfo, SDL_GetError(), Mix_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_PLAY_CHANNEL:
    {
      sprintf(pErrorString, "%sMix_PlayChannel() failed!\n%s\n%s", pErrorInfo, SDL_GetError(), Mix_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_TEXT_EXIST:
    {
      sprintf(pErrorString, "%sid for text already exists!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_TEXT_NOEXIST:
    {
      sprintf(pErrorString, "%sid for text does not exist!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_TTF_INIT:
    {
      sprintf(pErrorString, "%sTTF_Init() failed!\n%s\n%s", pErrorInfo, SDL_GetError(), TTF_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_FONT_EXIST:
    {
      sprintf(pErrorString, "%sid for font already exists!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_FONT_NOEXIST:
    {
      sprintf(pErrorString, "%sid for font does not exist!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_OPEN_FONT:
    {
      sprintf(pErrorString, "%sTTF_OpenFont() failed!\n%s\n%s", pErrorInfo, SDL_GetError(), TTF_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_TEXT_NOSUBMIT:
    {
      sprintf(pErrorString, "%stextSubmit() has not been called yet!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_TEXT_RELATE_FONT:
    {
      sprintf(pErrorString, "%stextRelateFont() has not been called yet!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_RENDER_TEXT_BLENDED:
    {
      sprintf(pErrorString, "%sTTF_RenderUTF8_Blended() failed!\n%s\n%s", pErrorInfo, SDL_GetError(), TTF_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_INVALID_ZINDEX:
    {
      sprintf(pErrorString, "%sz-index must not be 0!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_MDL_CLONE_EXIST:
    {
      sprintf(pErrorString, "%sid for model clone already exists!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_MDL_CLONE_NOEXIST:
    {
      sprintf(pErrorString, "%sid for model clone does not exist!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_LINE_NOEXIST:
    {
      sprintf(pErrorString, "%sid for line does not exist!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_LINE_EXIST:
    {
      sprintf(pErrorString, "%sid for line already exists!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SDL_DRAW_LINE:
    {
      sprintf(pErrorString, "%sSDL_RenderDrawLine() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_MDL_COLL_RECT_NOEXIST:
    {
      sprintf(pErrorString, "%sid for model collision rectangle does not exist!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_MDL_COLL_RECT_EXIST:
    {
      sprintf(pErrorString, "%sid for model collision rectangle already exists!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_VIDEO_NOEXIST:
    {
      sprintf(pErrorString, "%sid for video does not exist!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_VIDEO_EXIST:
    {
      sprintf(pErrorString, "%sid for video already exists!", pErrorInfo);
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_SDL_HINT:
    {
      sprintf(pErrorString, "%sSDL_SetHint() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
    case LE_INIT_SUBSYSTEM:
    {
      sprintf(pErrorString, "%sSDL_InitSubSystem() failed!\n%s", pErrorInfo, SDL_GetError());
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "LE Moon", pErrorString, nullptr);
    } break;
  };

  if(pErrorString != nullptr)
  {
    delete [] pErrorString;
    pErrorString = nullptr;
  }

  this->mtxGeneral.printErrorDialog.unlock();
}

void LEMoon::clearKeyboard()
{
  this->keyboard.key0                     = LE_INACTIVE;
  this->keyboard.key1                     = LE_INACTIVE;
  this->keyboard.key2                     = LE_INACTIVE;
  this->keyboard.key3                     = LE_INACTIVE;
  this->keyboard.key4                     = LE_INACTIVE;
  this->keyboard.key5                     = LE_INACTIVE;
  this->keyboard.key6                     = LE_INACTIVE;
  this->keyboard.key7                     = LE_INACTIVE;
  this->keyboard.key8                     = LE_INACTIVE;
  this->keyboard.key9                     = LE_INACTIVE;
  this->keyboard.keyA                     = LE_INACTIVE;
  this->keyboard.keyACBack                = LE_INACTIVE;
  this->keyboard.keyACBookmarks           = LE_INACTIVE;
  this->keyboard.keyACForward             = LE_INACTIVE;
  this->keyboard.keyACHome                = LE_INACTIVE;
  this->keyboard.keyACRefresh             = LE_INACTIVE;
  this->keyboard.keyACSearch              = LE_INACTIVE;
  this->keyboard.keyACStop                = LE_INACTIVE;
  this->keyboard.keyAgain                 = LE_INACTIVE;
  this->keyboard.keyAltErase              = LE_INACTIVE;
  this->keyboard.keyApostrophe            = LE_INACTIVE;
  this->keyboard.keyApplication           = LE_INACTIVE;
  this->keyboard.keyAudioMute             = LE_INACTIVE;
  this->keyboard.keyAudioNext             = LE_INACTIVE;
  this->keyboard.keyAudioPlay             = LE_INACTIVE;
  this->keyboard.keyAudioPrev             = LE_INACTIVE;
  this->keyboard.keyAudioStop             = LE_INACTIVE;
  this->keyboard.keyB                     = LE_INACTIVE;
  this->keyboard.keyBackslash             = LE_INACTIVE;
  this->keyboard.keyBackspace             = LE_INACTIVE;
  this->keyboard.keyBrightnessDown        = LE_INACTIVE;
  this->keyboard.keyBrightnessUp          = LE_INACTIVE;
  this->keyboard.keyC                     = LE_INACTIVE;
  this->keyboard.keyCalculator            = LE_INACTIVE;
  this->keyboard.keyCancel                = LE_INACTIVE;
  this->keyboard.keyCapsLock              = LE_INACTIVE;
  this->keyboard.keyClear                 = LE_INACTIVE;
  this->keyboard.keyClearAgain            = LE_INACTIVE;
  this->keyboard.keyComma                 = LE_INACTIVE;
  this->keyboard.keyComputer              = LE_INACTIVE;
  this->keyboard.keyCopy                  = LE_INACTIVE;
  this->keyboard.keyCrSel                 = LE_INACTIVE;
  this->keyboard.keyCurrencySubUnit       = LE_INACTIVE;
  this->keyboard.keyCurrencyUnit          = LE_INACTIVE;
  this->keyboard.keyCut                   = LE_INACTIVE;
  this->keyboard.keyD                     = LE_INACTIVE;
  this->keyboard.keyDecimalSeparator      = LE_INACTIVE;
  this->keyboard.keyDelete                = LE_INACTIVE;
  this->keyboard.keyDisplaySwitch         = LE_INACTIVE;
  this->keyboard.keyDown                  = LE_INACTIVE;
  this->keyboard.keyE                     = LE_INACTIVE;
  this->keyboard.keyEject                 = LE_INACTIVE;
  this->keyboard.keyEnd                   = LE_INACTIVE;
  this->keyboard.keyEquals                = LE_INACTIVE;
  this->keyboard.keyEscape                = LE_INACTIVE;
  this->keyboard.keyExecute               = LE_INACTIVE;
  this->keyboard.keyExSel                 = LE_INACTIVE;
  this->keyboard.keyF                     = LE_INACTIVE;
  this->keyboard.keyF1                    = LE_INACTIVE;
  this->keyboard.keyF2                    = LE_INACTIVE;
  this->keyboard.keyF3                    = LE_INACTIVE;
  this->keyboard.keyF4                    = LE_INACTIVE;
  this->keyboard.keyF5                    = LE_INACTIVE;
  this->keyboard.keyF6                    = LE_INACTIVE;
  this->keyboard.keyF7                    = LE_INACTIVE;
  this->keyboard.keyF8                    = LE_INACTIVE;
  this->keyboard.keyF9                    = LE_INACTIVE;
  this->keyboard.keyF10                   = LE_INACTIVE;
  this->keyboard.keyF11                   = LE_INACTIVE;
  this->keyboard.keyF12                   = LE_INACTIVE;
  this->keyboard.keyF13                   = LE_INACTIVE;
  this->keyboard.keyF14                   = LE_INACTIVE;
  this->keyboard.keyF15                   = LE_INACTIVE;
  this->keyboard.keyF16                   = LE_INACTIVE;
  this->keyboard.keyF17                   = LE_INACTIVE;
  this->keyboard.keyF18                   = LE_INACTIVE;
  this->keyboard.keyF19                   = LE_INACTIVE;
  this->keyboard.keyF20                   = LE_INACTIVE;
  this->keyboard.keyF21                   = LE_INACTIVE;
  this->keyboard.keyF22                   = LE_INACTIVE;
  this->keyboard.keyF23                   = LE_INACTIVE;
  this->keyboard.keyF24                   = LE_INACTIVE;
  this->keyboard.keyFind                  = LE_INACTIVE;
  this->keyboard.keyG                     = LE_INACTIVE;
  this->keyboard.keyBackquote             = LE_INACTIVE;
  this->keyboard.keyH                     = LE_INACTIVE;
  this->keyboard.keyHelp                  = LE_INACTIVE;
  this->keyboard.keyHome                  = LE_INACTIVE;
  this->keyboard.keyI                     = LE_INACTIVE;
  this->keyboard.keyInsert                = LE_INACTIVE;
  this->keyboard.keyJ                     = LE_INACTIVE;
  this->keyboard.keyK                     = LE_INACTIVE;
  this->keyboard.keyKBDillumDown          = LE_INACTIVE;
  this->keyboard.keyKBDillumToggle        = LE_INACTIVE;
  this->keyboard.keyKBDillumUp            = LE_INACTIVE;
  this->keyboard.keyKeypad0               = LE_INACTIVE;
  this->keyboard.keyKeypad00              = LE_INACTIVE;
  this->keyboard.keyKeypad000             = LE_INACTIVE;
  this->keyboard.keyKeypad1               = LE_INACTIVE;
  this->keyboard.keyKeypad2               = LE_INACTIVE;
  this->keyboard.keyKeypad3               = LE_INACTIVE;
  this->keyboard.keyKeypad4               = LE_INACTIVE;
  this->keyboard.keyKeypad5               = LE_INACTIVE;
  this->keyboard.keyKeypad6               = LE_INACTIVE;
  this->keyboard.keyKeypad7               = LE_INACTIVE;
  this->keyboard.keyKeypad8               = LE_INACTIVE;
  this->keyboard.keyKeypad9               = LE_INACTIVE;
  this->keyboard.keyKeypadA               = LE_INACTIVE;
  this->keyboard.keyKeypadAnd             = LE_INACTIVE;
  this->keyboard.keyKeypadAt              = LE_INACTIVE;
  this->keyboard.keyKeypadB               = LE_INACTIVE;
  this->keyboard.keyKeypadBackspace       = LE_INACTIVE;
  this->keyboard.keyKeypadBinary          = LE_INACTIVE;
  this->keyboard.keyKeypadC               = LE_INACTIVE;
  this->keyboard.keyKeypadClear           = LE_INACTIVE;
  this->keyboard.keyKeypadClearEntry      = LE_INACTIVE;
  this->keyboard.keyKeypadColon           = LE_INACTIVE;
  this->keyboard.keyKeypadComma           = LE_INACTIVE;
  this->keyboard.keyKeypadD               = LE_INACTIVE;
  this->keyboard.keyKeypadDoubleAnd       = LE_INACTIVE;
  this->keyboard.keyKeypadDoubleOr        = LE_INACTIVE;
  this->keyboard.keyKeypadDecimal         = LE_INACTIVE;
  this->keyboard.keyKeypadDivide          = LE_INACTIVE;
  this->keyboard.keyKeypadE               = LE_INACTIVE;
  this->keyboard.keyKeypadEnter           = LE_INACTIVE;
  this->keyboard.keyKeypadEquals          = LE_INACTIVE;
  this->keyboard.keyKeypadEqualsAS400     = LE_INACTIVE;
  this->keyboard.keyKeypadExclamation     = LE_INACTIVE;
  this->keyboard.keyKeypadF               = LE_INACTIVE;
  this->keyboard.keyKeypadGreater         = LE_INACTIVE;
  this->keyboard.keyKeypadHash            = LE_INACTIVE;
  this->keyboard.keyKeypadHexadecimal     = LE_INACTIVE;
  this->keyboard.keyKeypadLeftBrace       = LE_INACTIVE;
  this->keyboard.keyKeypadLeftParen       = LE_INACTIVE;
  this->keyboard.keyKeypadLess            = LE_INACTIVE;
  this->keyboard.keyKeypadMemAdd          = LE_INACTIVE;
  this->keyboard.keyKeypadMemClear        = LE_INACTIVE;
  this->keyboard.keyKeypadMemDivide       = LE_INACTIVE;
  this->keyboard.keyKeypadMemMultiply     = LE_INACTIVE;
  this->keyboard.keyKeypadMemRecall       = LE_INACTIVE;
  this->keyboard.keyKeypadMemStore        = LE_INACTIVE;
  this->keyboard.keyKeypadMemSubtract     = LE_INACTIVE;
  this->keyboard.keyKeypadMinus           = LE_INACTIVE;
  this->keyboard.keyKeypadMultiply        = LE_INACTIVE;
  this->keyboard.keyKeypadOctal           = LE_INACTIVE;
  this->keyboard.keyKeypadPercent         = LE_INACTIVE;
  this->keyboard.keyKeypadPeriod          = LE_INACTIVE;
  this->keyboard.keyKeypadPlus            = LE_INACTIVE;
  this->keyboard.keyKeypadPlusMinus       = LE_INACTIVE;
  this->keyboard.keyKeypadPower           = LE_INACTIVE;
  this->keyboard.keyKeypadRightBrace      = LE_INACTIVE;
  this->keyboard.keyKeypadRightParen      = LE_INACTIVE;
  this->keyboard.keyKeypadSpace           = LE_INACTIVE;
  this->keyboard.keyKeypadTab             = LE_INACTIVE;
  this->keyboard.keyKeypadVerticalBar     = LE_INACTIVE;
  this->keyboard.keyKeypadXOR             = LE_INACTIVE;
  this->keyboard.keyL                     = LE_INACTIVE;
  this->keyboard.keyLeftAlt               = LE_INACTIVE;
  this->keyboard.keyLeftCtrl              = LE_INACTIVE;
  this->keyboard.keyLeft                  = LE_INACTIVE;
  this->keyboard.keyLeftBracket           = LE_INACTIVE;
  this->keyboard.keyLeftGUI               = LE_INACTIVE;
  this->keyboard.keyLeftShift             = LE_INACTIVE;
  this->keyboard.keyM                     = LE_INACTIVE;
  this->keyboard.keyMail                  = LE_INACTIVE;
  this->keyboard.keyMediaSelect           = LE_INACTIVE;
  this->keyboard.keyMenu                  = LE_INACTIVE;
  this->keyboard.keyMinus                 = LE_INACTIVE;
  this->keyboard.keyModeSwitch            = LE_INACTIVE;
  this->keyboard.keyMute                  = LE_INACTIVE;
  this->keyboard.keyN                     = LE_INACTIVE;
  this->keyboard.keyNumLock               = LE_INACTIVE;
  this->keyboard.keyO                     = LE_INACTIVE;
  this->keyboard.keyOper                  = LE_INACTIVE;
  this->keyboard.keyOut                   = LE_INACTIVE;
  this->keyboard.keyP                     = LE_INACTIVE;
  this->keyboard.keyPageDown              = LE_INACTIVE;
  this->keyboard.keyPageUp                = LE_INACTIVE;
  this->keyboard.keyPaste                 = LE_INACTIVE;
  this->keyboard.keyPause                 = LE_INACTIVE;
  this->keyboard.keyPeriod                = LE_INACTIVE;
  this->keyboard.keyPower                 = LE_INACTIVE;
  this->keyboard.keyPrintScreen           = LE_INACTIVE;
  this->keyboard.keyPrior                 = LE_INACTIVE;
  this->keyboard.keyQ                     = LE_INACTIVE;
  this->keyboard.keyR                     = LE_INACTIVE;
  this->keyboard.keyRightAlt              = LE_INACTIVE;
  this->keyboard.keyRightCtrl             = LE_INACTIVE;
  this->keyboard.keyReturn                = LE_INACTIVE;
  this->keyboard.keyReturn2               = LE_INACTIVE;
  this->keyboard.keyRightGUI              = LE_INACTIVE;
  this->keyboard.keyRight                 = LE_INACTIVE;
  this->keyboard.keyRightBracket          = LE_INACTIVE;
  this->keyboard.keyRightShift            = LE_INACTIVE;
  this->keyboard.keyS                     = LE_INACTIVE;
  this->keyboard.keyScrollLock            = LE_INACTIVE;
  this->keyboard.keySelect                = LE_INACTIVE;
  this->keyboard.keySemicolon             = LE_INACTIVE;
  this->keyboard.keySeparator             = LE_INACTIVE;
  this->keyboard.keySlash                 = LE_INACTIVE;
  this->keyboard.keySleep                 = LE_INACTIVE;
  this->keyboard.keySpace                 = LE_INACTIVE;
  this->keyboard.keyStop                  = LE_INACTIVE;
  this->keyboard.keySysReq                = LE_INACTIVE;
  this->keyboard.keyT                     = LE_INACTIVE;
  this->keyboard.keyTab                   = LE_INACTIVE;
  this->keyboard.keyThousandsSeparator    = LE_INACTIVE;
  this->keyboard.keyU                     = LE_INACTIVE;
  this->keyboard.keyUndo                  = LE_INACTIVE;
  this->keyboard.keyUp                    = LE_INACTIVE;
  this->keyboard.keyV                     = LE_INACTIVE;
  this->keyboard.keyVolumeDown            = LE_INACTIVE;
  this->keyboard.keyVolumeUp              = LE_INACTIVE;
  this->keyboard.keyW                     = LE_INACTIVE;
  this->keyboard.keyWWW                   = LE_INACTIVE;
  this->keyboard.keyX                     = LE_INACTIVE;
  this->keyboard.keyY                     = LE_INACTIVE;
  this->keyboard.keyZ                     = LE_INACTIVE;
}

void LEMoon::clearMouse()
{
  this->mouse.leftButton = LE_INACTIVE;
  this->mouse.rightButton = LE_INACTIVE;
}

void LEMoon::handleMouse()
{
  switch(this->event.type)
  {
    case SDL_MOUSEBUTTONDOWN:
    {
      switch(this->event.button.button)
      {
        case SDL_BUTTON_LEFT:
        {
          this->mouse.leftButton = LE_PRESSED;
        } break;
        case SDL_BUTTON_RIGHT:
        {
          this->mouse.rightButton = LE_PRESSED;
        } break;
      };
    } break;
    case SDL_MOUSEBUTTONUP:
    {
      switch(this->event.button.button)
      {
        case SDL_BUTTON_LEFT:
        {
          this->mouse.leftButton = LE_RELEASED;
        } break;
        case SDL_BUTTON_RIGHT:
        {
          this->mouse.rightButton = LE_RELEASED;
        } break;
      };
    } break;
  };
}

void LEMoon::handleKeyboard()
{
  switch(this->event.type)
  {
    case SDL_KEYUP:
    {
      switch(this->event.key.keysym.sym)
      {
        case SDLK_0:
        {
          this->keyboard.key0 = LE_RELEASED;
        } break;
        case SDLK_1:
        {
          this->keyboard.key1 = LE_RELEASED;
        } break;
        case SDLK_2:
        {
          this->keyboard.key2 = LE_RELEASED;
        } break;
        case SDLK_3:
        {
          this->keyboard.key3 = LE_RELEASED;
        } break;
        case SDLK_4:
        {
          this->keyboard.key4 = LE_RELEASED;
        } break;
        case SDLK_5:
        {
          this->keyboard.key5 = LE_RELEASED;
        } break;
        case SDLK_6:
        {
          this->keyboard.key6 = LE_RELEASED;
        } break;
        case SDLK_7:
        {
          this->keyboard.key7 = LE_RELEASED;
        } break;
        case SDLK_8:
        {
          this->keyboard.key8 = LE_RELEASED;
        } break;
        case SDLK_9:
        {
          this->keyboard.key9 = LE_RELEASED;
        } break;
        case SDLK_a:
        {
          this->keyboard.keyA = LE_RELEASED;
        } break;
        case SDLK_AC_BACK:
        {
          this->keyboard.keyACBack = LE_RELEASED;
        } break;
        case SDLK_AC_BOOKMARKS:
        {
          this->keyboard.keyACBookmarks = LE_RELEASED;
        } break;
        case SDLK_AC_FORWARD:
        {
          this->keyboard.keyACForward = LE_RELEASED;
        } break;
        case SDLK_AC_HOME:
        {
          this->keyboard.keyACHome = LE_RELEASED;
        } break;
        case SDLK_AC_REFRESH:
        {
          this->keyboard.keyACRefresh = LE_RELEASED;
        } break;
        case SDLK_AC_SEARCH:
        {
          this->keyboard.keyACSearch = LE_RELEASED;
        } break;
        case SDLK_AC_STOP:
        {
          this->keyboard.keyACStop = LE_RELEASED;
        } break;
        case SDLK_AGAIN:
        {
          this->keyboard.keyAgain = LE_RELEASED;
        } break;
        case SDLK_ALTERASE:
        {
          this->keyboard.keyAltErase = LE_RELEASED;
        } break;
        case SDLK_QUOTE:
        {
          this->keyboard.keyApostrophe = LE_RELEASED;
        } break;
        case SDLK_APPLICATION:
        {
          this->keyboard.keyApplication = LE_RELEASED;
        } break;
        case SDLK_AUDIOMUTE:
        {
          this->keyboard.keyAudioMute = LE_RELEASED;
        } break;
        case SDLK_AUDIONEXT:
        {
          this->keyboard.keyAudioNext = LE_RELEASED;
        } break;
        case SDLK_AUDIOPLAY:
        {
          this->keyboard.keyAudioPlay = LE_RELEASED;
        } break;
        case SDLK_AUDIOPREV:
        {
          this->keyboard.keyAudioPrev = LE_RELEASED;
        } break;
        case SDLK_AUDIOSTOP:
        {
          this->keyboard.keyAudioStop = LE_RELEASED;
        } break;
        case SDLK_b:
        {
          this->keyboard.keyB = LE_RELEASED;
        } break;
        case SDLK_BACKSLASH:
        {
          this->keyboard.keyBackslash = LE_RELEASED;
        } break;
        case SDLK_BACKSPACE:
        {
          this->keyboard.keyBackspace = LE_RELEASED;
        } break;
        case SDLK_BRIGHTNESSDOWN:
        {
          this->keyboard.keyBrightnessDown = LE_RELEASED;
        } break;
        case SDLK_BRIGHTNESSUP:
        {
          this->keyboard.keyBrightnessUp = LE_RELEASED;
        } break;
        case SDLK_c:
        {
          this->keyboard.keyC = LE_RELEASED;
        } break;
        case SDLK_CALCULATOR:
        {
          this->keyboard.keyCalculator = LE_RELEASED;
        } break;
        case SDLK_CANCEL:
        {
          this->keyboard.keyCancel = LE_RELEASED;
        } break;
        case SDLK_CAPSLOCK:
        {
          this->keyboard.keyCapsLock = LE_RELEASED;
        } break;
        case SDLK_CLEAR:
        {
          this->keyboard.keyClear = LE_RELEASED;
        } break;
        case SDLK_CLEARAGAIN:
        {
          this->keyboard.keyClearAgain = LE_RELEASED;
        } break;
        case SDLK_COMMA:
        {
          this->keyboard.keyComma = LE_RELEASED;
        } break;
        case SDLK_COMPUTER:
        {
          this->keyboard.keyComputer = LE_RELEASED;
        } break;
        case SDLK_COPY:
        {
          this->keyboard.keyCopy = LE_RELEASED;
        } break;
        case SDLK_CRSEL:
        {
          this->keyboard.keyCrSel = LE_RELEASED;
        } break;
        case SDLK_CURRENCYSUBUNIT:
        {
          this->keyboard.keyCurrencySubUnit = LE_RELEASED;
        } break;
        case SDLK_CURRENCYUNIT:
        {
          this->keyboard.keyCurrencyUnit = LE_RELEASED;
        } break;
        case SDLK_CUT:
        {
          this->keyboard.keyCut = LE_RELEASED;
        } break;
        case SDLK_d:
        {
          this->keyboard.keyD = LE_RELEASED;
        } break;
        case SDLK_DECIMALSEPARATOR:
        {
          this->keyboard.keyDecimalSeparator = LE_RELEASED;
        } break;
        case SDLK_DELETE:
        {
          this->keyboard.keyDelete = LE_RELEASED;
        } break;
        case SDLK_DISPLAYSWITCH:
        {
          this->keyboard.keyDisplaySwitch = LE_RELEASED;
        } break;
        case SDLK_DOWN:
        {
          this->keyboard.keyDown = LE_RELEASED;
        } break;
        case SDLK_e:
        {
          this->keyboard.keyE = LE_RELEASED;
        } break;
        case SDLK_EJECT:
        {
          this->keyboard.keyEject = LE_RELEASED;
        } break;
        case SDLK_END:
        {
          this->keyboard.keyEnd = LE_RELEASED;
        } break;
        case SDLK_EQUALS:
        {
          this->keyboard.keyEquals = LE_RELEASED;
        } break;
        case SDLK_ESCAPE:
        {
          this->keyboard.keyEscape = LE_RELEASED;
        } break;
        case SDLK_EXECUTE:
        {
          this->keyboard.keyExecute = LE_RELEASED;
        } break;
        case SDLK_EXSEL:
        {
          this->keyboard.keyExSel = LE_RELEASED;
        } break;
        case SDLK_f:
        {
          this->keyboard.keyF = LE_RELEASED;
        } break;
        case SDLK_F1:
        {
          this->keyboard.keyF1 = LE_RELEASED;
        } break;
        case SDLK_F10:
        {
          this->keyboard.keyF10 = LE_RELEASED;
        } break;
        case SDLK_F11:
        {
          this->keyboard.keyF11 = LE_RELEASED;
        } break;
        case SDLK_F12:
        {
          this->keyboard.keyF12 = LE_RELEASED;
        } break;
        case SDLK_F13:
        {
          this->keyboard.keyF13 = LE_RELEASED;
        } break;
        case SDLK_F14:
        {
          this->keyboard.keyF14 = LE_RELEASED;
        } break;
        case SDLK_F15:
        {
          this->keyboard.keyF15 = LE_RELEASED;
        } break;
        case SDLK_F16:
        {
          this->keyboard.keyF16 = LE_RELEASED;
        } break;
        case SDLK_F17:
        {
          this->keyboard.keyF17 = LE_RELEASED;
        } break;
        case SDLK_F18:
        {
          this->keyboard.keyF18 = LE_RELEASED;
        } break;
        case SDLK_F19:
        {
          this->keyboard.keyF19 = LE_RELEASED;
        } break;
        case SDLK_F2:
        {
          this->keyboard.keyF2 = LE_RELEASED;
        } break;
        case SDLK_F20:
        {
          this->keyboard.keyF20 = LE_RELEASED;
        } break;
        case SDLK_F21:
        {
          this->keyboard.keyF21 = LE_RELEASED;
        } break;
        case SDLK_F22:
        {
          this->keyboard.keyF22 = LE_RELEASED;
        } break;
        case SDLK_F23:
        {
          this->keyboard.keyF23 = LE_RELEASED;
        } break;
        case SDLK_F24:
        {
          this->keyboard.keyF24 = LE_RELEASED;
        } break;
        case SDLK_F3:
        {
          this->keyboard.keyF3 = LE_RELEASED;
        } break;
        case SDLK_F4:
        {
          this->keyboard.keyF4 = LE_RELEASED;
        } break;
        case SDLK_F5:
        {
          this->keyboard.keyF5 = LE_RELEASED;
        } break;
        case SDLK_F6:
        {
          this->keyboard.keyF6 = LE_RELEASED;
        } break;
        case SDLK_F7:
        {
          this->keyboard.keyF7 = LE_RELEASED;
        } break;
        case SDLK_F8:
        {
          this->keyboard.keyF8 = LE_RELEASED;
        } break;
        case SDLK_F9:
        {
          this->keyboard.keyF9 = LE_RELEASED;
        } break;
        case SDLK_FIND:
        {
          this->keyboard.keyFind = LE_RELEASED;
        } break;
        case SDLK_g:
        {
          this->keyboard.keyG = LE_RELEASED;
        } break;
        case SDLK_BACKQUOTE:
        {
          this->keyboard.keyBackquote = LE_RELEASED;
        } break;
        case SDLK_h:
        {
          this->keyboard.keyH = LE_RELEASED;
        } break;
        case SDLK_HELP:
        {
          this->keyboard.keyHelp = LE_RELEASED;
        } break;
        case SDLK_HOME:
        {
          this->keyboard.keyHome = LE_RELEASED;
        } break;
        case SDLK_i:
        {
          this->keyboard.keyI = LE_RELEASED;
        } break;
        case SDLK_INSERT:
        {
          this->keyboard.keyInsert = LE_RELEASED;
        } break;
        case SDLK_j:
        {
          this->keyboard.keyJ = LE_RELEASED;
        } break;
        case SDLK_k:
        {
          this->keyboard.keyK = LE_RELEASED;
        } break;
        case SDLK_KBDILLUMDOWN:
        {
          this->keyboard.keyKBDillumDown = LE_RELEASED;
        } break;
        case SDLK_KBDILLUMTOGGLE:
        {
          this->keyboard.keyKBDillumToggle = LE_RELEASED;
        } break;
        case SDLK_KBDILLUMUP:
        {
          this->keyboard.keyKBDillumUp = LE_RELEASED;
        } break;
        case SDLK_KP_0:
        {
          this->keyboard.keyKeypad0 = LE_RELEASED;
        } break;
        case SDLK_KP_00:
        {
          this->keyboard.keyKeypad00 = LE_RELEASED;
        } break;
        case SDLK_KP_000:
        {
          this->keyboard.keyKeypad000 = LE_RELEASED;
        } break;
        case SDLK_KP_1:
        {
          this->keyboard.keyKeypad1 = LE_RELEASED;
        } break;
        case SDLK_KP_2:
        {
          this->keyboard.keyKeypad2 = LE_RELEASED;
        } break;
        case SDLK_KP_3:
        {
          this->keyboard.keyKeypad3 = LE_RELEASED;
        } break;
        case SDLK_KP_4:
        {
          this->keyboard.keyKeypad4 = LE_RELEASED;
        } break;
        case SDLK_KP_5:
        {
          this->keyboard.keyKeypad5 = LE_RELEASED;
        } break;
        case SDLK_KP_6:
        {
          this->keyboard.keyKeypad6 = LE_RELEASED;
        } break;
        case SDLK_KP_7:
        {
          this->keyboard.keyKeypad7 = LE_RELEASED;
        } break;
        case SDLK_KP_8:
        {
          this->keyboard.keyKeypad8 = LE_RELEASED;
        } break;
        case SDLK_KP_9:
        {
          this->keyboard.keyKeypad9 = LE_RELEASED;
        } break;
        case SDLK_KP_A:
        {
          this->keyboard.keyKeypadA = LE_RELEASED;
        } break;
        case SDLK_KP_AMPERSAND:
        {
          this->keyboard.keyKeypadAnd = LE_RELEASED;
        } break;
        case SDLK_KP_AT:
        {
          this->keyboard.keyKeypadAt = LE_RELEASED;
        } break;
        case SDLK_KP_B:
        {
          this->keyboard.keyKeypadB = LE_RELEASED;
        } break;
        case SDLK_KP_BACKSPACE:
        {
          this->keyboard.keyKeypadBackspace = LE_RELEASED;
        } break;
        case SDLK_KP_BINARY:
        {
          this->keyboard.keyKeypadBinary = LE_RELEASED;
        } break;
        case SDLK_KP_C:
        {
          this->keyboard.keyKeypadC = LE_RELEASED;
        } break;
        case SDLK_KP_CLEAR:
        {
          this->keyboard.keyKeypadClear = LE_RELEASED;
        } break;
        case SDLK_KP_CLEARENTRY:
        {
          this->keyboard.keyKeypadClearEntry = LE_RELEASED;
        } break;
        case SDLK_KP_COLON:
        {
          this->keyboard.keyKeypadColon = LE_RELEASED;
        } break;
        case SDLK_KP_COMMA:
        {
          this->keyboard.keyKeypadComma = LE_RELEASED;
        } break;
        case SDLK_KP_D:
        {
          this->keyboard.keyKeypadD = LE_RELEASED;
        } break;
        case SDLK_KP_DBLAMPERSAND:
        {
          this->keyboard.keyKeypadDoubleAnd = LE_RELEASED;
        } break;
        case SDLK_KP_DBLVERTICALBAR:
        {
          this->keyboard.keyKeypadDoubleOr = LE_RELEASED;
        } break;
        case SDLK_KP_DECIMAL:
        {
          this->keyboard.keyKeypadDecimal = LE_RELEASED;
        } break;
        case SDLK_KP_DIVIDE:
        {
          this->keyboard.keyKeypadDivide = LE_RELEASED;
        } break;
        case SDLK_KP_E:
        {
          this->keyboard.keyKeypadE = LE_RELEASED;
        } break;
        case SDLK_KP_ENTER:
        {
          this->keyboard.keyKeypadEnter = LE_RELEASED;
        } break;
        case SDLK_KP_EQUALS:
        {
          this->keyboard.keyKeypadEquals = LE_RELEASED;
        } break;
        case SDLK_KP_EQUALSAS400:
        {
          this->keyboard.keyKeypadEqualsAS400 = LE_RELEASED;
        } break;
        case SDLK_KP_EXCLAM:
        {
          this->keyboard.keyKeypadExclamation = LE_RELEASED;
        } break;
        case SDLK_KP_F:
        {
          this->keyboard.keyKeypadF = LE_RELEASED;
        } break;
        case SDLK_KP_GREATER:
        {
          this->keyboard.keyKeypadGreater = LE_RELEASED;
        } break;
        case SDLK_KP_HASH:
        {
          this->keyboard.keyKeypadHash = LE_RELEASED;
        } break;
        case SDLK_KP_HEXADECIMAL:
        {
          this->keyboard.keyKeypadHexadecimal = LE_RELEASED;
        } break;
        case SDLK_KP_LEFTBRACE:
        {
          this->keyboard.keyKeypadLeftBrace = LE_RELEASED;
        } break;
        case SDLK_KP_LEFTPAREN:
        {
          this->keyboard.keyKeypadLeftParen = LE_RELEASED;
        } break;
        case SDLK_KP_LESS:
        {
          this->keyboard.keyKeypadLess = LE_RELEASED;
        } break;
        case SDLK_KP_MEMADD:
        {
          this->keyboard.keyKeypadMemAdd = LE_RELEASED;
        } break;
        case SDLK_KP_MEMCLEAR:
        {
          this->keyboard.keyKeypadMemClear = LE_RELEASED;
        } break;
        case SDLK_KP_MEMDIVIDE:
        {
          this->keyboard.keyKeypadMemDivide = LE_RELEASED;
        } break;
        case SDLK_KP_MEMMULTIPLY:
        {
          this->keyboard.keyKeypadMemMultiply = LE_RELEASED;
        } break;
        case SDLK_KP_MEMRECALL:
        {
          this->keyboard.keyKeypadMemRecall = LE_RELEASED;
        } break;
        case SDLK_KP_MEMSTORE:
        {
          this->keyboard.keyKeypadMemStore = LE_RELEASED;
        } break;
        case SDLK_KP_MEMSUBTRACT:
        {
          this->keyboard.keyKeypadMemSubtract = LE_RELEASED;
        } break;
        case SDLK_KP_MINUS:
        {
          this->keyboard.keyKeypadMinus = LE_RELEASED;
        } break;
        case SDLK_KP_MULTIPLY:
        {
          this->keyboard.keyKeypadMultiply = LE_RELEASED;
        } break;
        case SDLK_KP_OCTAL:
        {
          this->keyboard.keyKeypadOctal = LE_RELEASED;
        } break;
        case SDLK_KP_PERCENT:
        {
          this->keyboard.keyKeypadPercent = LE_RELEASED;
        } break;
        case SDLK_KP_PERIOD:
        {
          this->keyboard.keyKeypadPeriod = LE_RELEASED;
        } break;
        case SDLK_KP_PLUS:
        {
          this->keyboard.keyKeypadPlus = LE_RELEASED;
        } break;
        case SDLK_KP_PLUSMINUS:
        {
          this->keyboard.keyKeypadPlusMinus = LE_RELEASED;
        } break;
        case SDLK_KP_POWER:
        {
          this->keyboard.keyKeypadPower = LE_RELEASED;
        } break;
        case SDLK_KP_RIGHTBRACE:
        {
          this->keyboard.keyKeypadRightBrace = LE_RELEASED;
        } break;
        case SDLK_KP_RIGHTPAREN:
        {
          this->keyboard.keyKeypadRightParen = LE_RELEASED;
        } break;
        case SDLK_KP_SPACE:
        {
          this->keyboard.keyKeypadSpace = LE_RELEASED;
        } break;
        case SDLK_KP_TAB:
        {
          this->keyboard.keyKeypadTab = LE_RELEASED;
        } break;
        case SDLK_KP_VERTICALBAR:
        {
          this->keyboard.keyKeypadVerticalBar = LE_RELEASED;
        } break;
        case SDLK_KP_XOR:
        {
          this->keyboard.keyKeypadXOR = LE_RELEASED;
        } break;
        case SDLK_l:
        {
          this->keyboard.keyL = LE_RELEASED;
        } break;
        case SDLK_LALT:
        {
          this->keyboard.keyLeftAlt = LE_RELEASED;
        } break;
        case SDLK_LCTRL:
        {
          this->keyboard.keyLeftCtrl = LE_RELEASED;
        } break;
        case SDLK_LEFT:
        {
          this->keyboard.keyLeft = LE_RELEASED;
        } break;
        case SDLK_LEFTBRACKET:
        {
          this->keyboard.keyLeftBracket = LE_RELEASED;
        } break;
        case SDLK_LGUI:
        {
          this->keyboard.keyLeftGUI = LE_RELEASED;
        } break;
        case SDLK_LSHIFT:
        {
          this->keyboard.keyLeftShift = LE_RELEASED;
        } break;
        case SDLK_m:
        {
          this->keyboard.keyM = LE_RELEASED;
        } break;
        case SDLK_MAIL:
        {
          this->keyboard.keyMail = LE_RELEASED;
        } break;
        case SDLK_MEDIASELECT:
        {
          this->keyboard.keyMediaSelect = LE_RELEASED;
        } break;
        case SDLK_MENU:
        {
          this->keyboard.keyMenu = LE_RELEASED;
        } break;
        case SDLK_MINUS:
        {
          this->keyboard.keyMinus = LE_RELEASED;
        } break;
        case SDLK_MODE:
        {
          this->keyboard.keyModeSwitch = LE_RELEASED;
        } break;
        case SDLK_MUTE:
        {
          this->keyboard.keyMute = LE_RELEASED;
        } break;
        case SDLK_n:
        {
          this->keyboard.keyN = LE_RELEASED;
        } break;
        case SDLK_NUMLOCKCLEAR:
        {
          this->keyboard.keyNumLock = LE_RELEASED;
        } break;
        case SDLK_o:
        {
          this->keyboard.keyO = LE_RELEASED;
        } break;
        case SDLK_OPER:
        {
          this->keyboard.keyOper = LE_RELEASED;
        } break;
        case SDLK_OUT:
        {
          this->keyboard.keyOut = LE_RELEASED;
        } break;
        case SDLK_p:
        {
          this->keyboard.keyP = LE_RELEASED;
        } break;
        case SDLK_PAGEDOWN:
        {
          this->keyboard.keyPageDown = LE_RELEASED;
        } break;
        case SDLK_PAGEUP:
        {
          this->keyboard.keyPageUp = LE_RELEASED;
        } break;
        case SDLK_PASTE:
        {
          this->keyboard.keyPaste = LE_RELEASED;
        } break;
        case SDLK_PAUSE:
        {
          this->keyboard.keyPause = LE_RELEASED;
        } break;
        case SDLK_PERIOD:
        {
          this->keyboard.keyPeriod = LE_RELEASED;
        } break;
        case SDLK_POWER:
        {
          this->keyboard.keyPower = LE_RELEASED;
        } break;
        case SDLK_PRINTSCREEN:
        {
          this->keyboard.keyPrintScreen = LE_RELEASED;
        } break;
        case SDLK_PRIOR:
        {
          this->keyboard.keyPrior = LE_RELEASED;
        } break;
        case SDLK_q:
        {
          this->keyboard.keyQ = LE_RELEASED;
        } break;
        case SDLK_r:
        {
          this->keyboard.keyR = LE_RELEASED;
        } break;
        case SDLK_RALT:
        {
          this->keyboard.keyRightAlt = LE_RELEASED;
        } break;
        case SDLK_RCTRL:
        {
          this->keyboard.keyRightCtrl = LE_RELEASED;
        } break;
        case SDLK_RETURN:
        {
          this->keyboard.keyReturn = LE_RELEASED;
        } break;
        case SDLK_RETURN2:
        {
          this->keyboard.keyReturn2 = LE_RELEASED;
        } break;
        case SDLK_RGUI:
        {
          this->keyboard.keyRightGUI = LE_RELEASED;
        } break;
        case SDLK_RIGHT:
        {
          this->keyboard.keyRight = LE_RELEASED;
        } break;
        case SDLK_RIGHTBRACKET:
        {
          this->keyboard.keyRightBracket = LE_RELEASED;
        } break;
        case SDLK_RSHIFT:
        {
          this->keyboard.keyRightShift = LE_RELEASED;
        } break;
        case SDLK_s:
        {
          this->keyboard.keyS = LE_RELEASED;
        } break;
        case SDLK_SCROLLLOCK:
        {
          this->keyboard.keyScrollLock = LE_RELEASED;
        } break;
        case SDLK_SELECT:
        {
          this->keyboard.keySelect = LE_RELEASED;
        } break;
        case SDLK_SEMICOLON:
        {
          this->keyboard.keySemicolon = LE_RELEASED;
        } break;
        case SDLK_SEPARATOR:
        {
          this->keyboard.keySeparator = LE_RELEASED;
        } break;
        case SDLK_SLASH:
        {
          this->keyboard.keySlash = LE_RELEASED;
        } break;
        case SDLK_SLEEP:
        {
          this->keyboard.keySleep = LE_RELEASED;
        } break;
        case SDLK_SPACE:
        {
          this->keyboard.keySpace = LE_RELEASED;
        } break;
        case SDLK_STOP:
        {
          this->keyboard.keyStop = LE_RELEASED;
        } break;
        case SDLK_SYSREQ:
        {
          this->keyboard.keySysReq = LE_RELEASED;
        } break;
        case SDLK_t:
        {
          this->keyboard.keyT = LE_RELEASED;
        } break;
        case SDLK_TAB:
        {
          this->keyboard.keyTab = LE_RELEASED;
        } break;
        case SDLK_THOUSANDSSEPARATOR:
        {
          this->keyboard.keyThousandsSeparator = LE_RELEASED;
        } break;
        case SDLK_u:
        {
          this->keyboard.keyU = LE_RELEASED;
        } break;
        case SDLK_UNDO:
        {
          this->keyboard.keyUndo = LE_RELEASED;
        } break;
        case SDLK_UP:
        {
          this->keyboard.keyUp = LE_RELEASED;
        } break;
        case SDLK_v:
        {
          this->keyboard.keyV = LE_RELEASED;
        } break;
        case SDLK_VOLUMEDOWN:
        {
          this->keyboard.keyVolumeDown = LE_RELEASED;
        } break;
        case SDLK_VOLUMEUP:
        {
          this->keyboard.keyVolumeUp = LE_RELEASED;
        } break;
        case SDLK_w:
        {
          this->keyboard.keyW = LE_RELEASED;
        } break;
        case SDLK_WWW:
        {
          this->keyboard.keyWWW = LE_RELEASED;
        } break;
        case SDLK_x:
        {
          this->keyboard.keyX = LE_RELEASED;
        } break;
        case SDLK_y:
        {
          this->keyboard.keyY = LE_RELEASED;
        } break;
        case SDLK_z:
        {
          this->keyboard.keyZ = LE_RELEASED;
        } break;
      };
    } break;

    //////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////
    // key down
    //////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////

    case SDL_KEYDOWN:
    {
      switch(this->event.key.keysym.sym)
      {
        case SDLK_0:
        {
          this->keyboard.key0 = LE_PRESSED;
        } break;
        case SDLK_1:
        {
          this->keyboard.key1 = LE_PRESSED;
        } break;
        case SDLK_2:
        {
          this->keyboard.key2 = LE_PRESSED;
        } break;
        case SDLK_3:
        {
          this->keyboard.key3 = LE_PRESSED;
        } break;
        case SDLK_4:
        {
          this->keyboard.key4 = LE_PRESSED;
        } break;
        case SDLK_5:
        {
          this->keyboard.key5 = LE_PRESSED;
        } break;
        case SDLK_6:
        {
          this->keyboard.key6 = LE_PRESSED;
        } break;
        case SDLK_7:
        {
          this->keyboard.key7 = LE_PRESSED;
        } break;
        case SDLK_8:
        {
          this->keyboard.key8 = LE_PRESSED;
        } break;
        case SDLK_9:
        {
          this->keyboard.key9 = LE_PRESSED;
        } break;
        case SDLK_a:
        {
          this->keyboard.keyA = LE_PRESSED;
        } break;
        case SDLK_AC_BACK:
        {
          this->keyboard.keyACBack = LE_PRESSED;
        } break;
        case SDLK_AC_BOOKMARKS:
        {
          this->keyboard.keyACBookmarks = LE_PRESSED;
        } break;
        case SDLK_AC_FORWARD:
        {
          this->keyboard.keyACForward = LE_PRESSED;
        } break;
        case SDLK_AC_HOME:
        {
          this->keyboard.keyACHome = LE_PRESSED;
        } break;
        case SDLK_AC_REFRESH:
        {
          this->keyboard.keyACRefresh = LE_PRESSED;
        } break;
        case SDLK_AC_SEARCH:
        {
          this->keyboard.keyACSearch = LE_PRESSED;
        } break;
        case SDLK_AC_STOP:
        {
          this->keyboard.keyACStop = LE_PRESSED;
        } break;
        case SDLK_AGAIN:
        {
          this->keyboard.keyAgain = LE_PRESSED;
        } break;
        case SDLK_ALTERASE:
        {
          this->keyboard.keyAltErase = LE_PRESSED;
        } break;
        case SDLK_QUOTE:
        {
          this->keyboard.keyApostrophe = LE_PRESSED;
        } break;
        case SDLK_APPLICATION:
        {
          this->keyboard.keyApplication = LE_PRESSED;
        } break;
        case SDLK_AUDIOMUTE:
        {
          this->keyboard.keyAudioMute = LE_PRESSED;
        } break;
        case SDLK_AUDIONEXT:
        {
          this->keyboard.keyAudioNext = LE_PRESSED;
        } break;
        case SDLK_AUDIOPLAY:
        {
          this->keyboard.keyAudioPlay = LE_PRESSED;
        } break;
        case SDLK_AUDIOPREV:
        {
          this->keyboard.keyAudioPrev = LE_PRESSED;
        } break;
        case SDLK_AUDIOSTOP:
        {
          this->keyboard.keyAudioStop = LE_PRESSED;
        } break;
        case SDLK_b:
        {
          this->keyboard.keyB = LE_PRESSED;
        } break;
        case SDLK_BACKSLASH:
        {
          this->keyboard.keyBackslash = LE_PRESSED;
        } break;
        case SDLK_BACKSPACE:
        {
          this->keyboard.keyBackspace = LE_PRESSED;
        } break;
        case SDLK_BRIGHTNESSDOWN:
        {
          this->keyboard.keyBrightnessDown = LE_PRESSED;
        } break;
        case SDLK_BRIGHTNESSUP:
        {
          this->keyboard.keyBrightnessUp = LE_PRESSED;
        } break;
        case SDLK_c:
        {
          this->keyboard.keyC = LE_PRESSED;
        } break;
        case SDLK_CALCULATOR:
        {
          this->keyboard.keyCalculator = LE_PRESSED;
        } break;
        case SDLK_CANCEL:
        {
          this->keyboard.keyCancel = LE_PRESSED;
        } break;
        case SDLK_CAPSLOCK:
        {
          this->keyboard.keyCapsLock = LE_PRESSED;
        } break;
        case SDLK_CLEAR:
        {
          this->keyboard.keyClear = LE_PRESSED;
        } break;
        case SDLK_CLEARAGAIN:
        {
          this->keyboard.keyClearAgain = LE_PRESSED;
        } break;
        case SDLK_COMMA:
        {
          this->keyboard.keyComma = LE_PRESSED;
        } break;
        case SDLK_COMPUTER:
        {
          this->keyboard.keyComputer = LE_PRESSED;
        } break;
        case SDLK_COPY:
        {
          this->keyboard.keyCopy = LE_PRESSED;
        } break;
        case SDLK_CRSEL:
        {
          this->keyboard.keyCrSel = LE_PRESSED;
        } break;
        case SDLK_CURRENCYSUBUNIT:
        {
          this->keyboard.keyCurrencySubUnit = LE_PRESSED;
        } break;
        case SDLK_CURRENCYUNIT:
        {
          this->keyboard.keyCurrencyUnit = LE_PRESSED;
        } break;
        case SDLK_CUT:
        {
          this->keyboard.keyCut = LE_PRESSED;
        } break;
        case SDLK_d:
        {
          this->keyboard.keyD = LE_PRESSED;
        } break;
        case SDLK_DECIMALSEPARATOR:
        {
          this->keyboard.keyDecimalSeparator = LE_PRESSED;
        } break;
        case SDLK_DELETE:
        {
          this->keyboard.keyDelete = LE_PRESSED;
        } break;
        case SDLK_DISPLAYSWITCH:
        {
          this->keyboard.keyDisplaySwitch = LE_PRESSED;
        } break;
        case SDLK_DOWN:
        {
          this->keyboard.keyDown = LE_PRESSED;
        } break;
        case SDLK_e:
        {
          this->keyboard.keyE = LE_PRESSED;
        } break;
        case SDLK_EJECT:
        {
          this->keyboard.keyEject = LE_PRESSED;
        } break;
        case SDLK_END:
        {
          this->keyboard.keyEnd = LE_PRESSED;
        } break;
        case SDLK_EQUALS:
        {
          this->keyboard.keyEquals = LE_PRESSED;
        } break;
        case SDLK_ESCAPE:
        {
          this->keyboard.keyEscape = LE_PRESSED;
        } break;
        case SDLK_EXECUTE:
        {
          this->keyboard.keyExecute = LE_PRESSED;
        } break;
        case SDLK_EXSEL:
        {
          this->keyboard.keyExSel = LE_PRESSED;
        } break;
        case SDLK_f:
        {
          this->keyboard.keyF = LE_PRESSED;
        } break;
        case SDLK_F1:
        {
          this->keyboard.keyF1 = LE_PRESSED;
        } break;
        case SDLK_F10:
        {
          this->keyboard.keyF10 = LE_PRESSED;
        } break;
        case SDLK_F11:
        {
          this->keyboard.keyF11 = LE_PRESSED;
        } break;
        case SDLK_F12:
        {
          this->keyboard.keyF12 = LE_PRESSED;
        } break;
        case SDLK_F13:
        {
          this->keyboard.keyF13 = LE_PRESSED;
        } break;
        case SDLK_F14:
        {
          this->keyboard.keyF14 = LE_PRESSED;
        } break;
        case SDLK_F15:
        {
          this->keyboard.keyF15 = LE_PRESSED;
        } break;
        case SDLK_F16:
        {
          this->keyboard.keyF16 = LE_PRESSED;
        } break;
        case SDLK_F17:
        {
          this->keyboard.keyF17 = LE_PRESSED;
        } break;
        case SDLK_F18:
        {
          this->keyboard.keyF18 = LE_PRESSED;
        } break;
        case SDLK_F19:
        {
          this->keyboard.keyF19 = LE_PRESSED;
        } break;
        case SDLK_F2:
        {
          this->keyboard.keyF2 = LE_PRESSED;
        } break;
        case SDLK_F20:
        {
          this->keyboard.keyF20 = LE_PRESSED;
        } break;
        case SDLK_F21:
        {
          this->keyboard.keyF21 = LE_PRESSED;
        } break;
        case SDLK_F22:
        {
          this->keyboard.keyF22 = LE_PRESSED;
        } break;
        case SDLK_F23:
        {
          this->keyboard.keyF23 = LE_PRESSED;
        } break;
        case SDLK_F24:
        {
          this->keyboard.keyF24 = LE_PRESSED;
        } break;
        case SDLK_F3:
        {
          this->keyboard.keyF3 = LE_PRESSED;
        } break;
        case SDLK_F4:
        {
          this->keyboard.keyF4 = LE_PRESSED;
        } break;
        case SDLK_F5:
        {
          this->keyboard.keyF5 = LE_PRESSED;
        } break;
        case SDLK_F6:
        {
          this->keyboard.keyF6 = LE_PRESSED;
        } break;
        case SDLK_F7:
        {
          this->keyboard.keyF7 = LE_PRESSED;
        } break;
        case SDLK_F8:
        {
          this->keyboard.keyF8 = LE_PRESSED;
        } break;
        case SDLK_F9:
        {
          this->keyboard.keyF9 = LE_PRESSED;
        } break;
        case SDLK_FIND:
        {
          this->keyboard.keyFind = LE_PRESSED;
        } break;
        case SDLK_g:
        {
          this->keyboard.keyG = LE_PRESSED;
        } break;
        case SDLK_BACKQUOTE:
        {
          this->keyboard.keyBackquote = LE_PRESSED;
        } break;
        case SDLK_h:
        {
          this->keyboard.keyH = LE_PRESSED;
        } break;
        case SDLK_HELP:
        {
          this->keyboard.keyHelp = LE_PRESSED;
        } break;
        case SDLK_HOME:
        {
          this->keyboard.keyHome = LE_PRESSED;
        } break;
        case SDLK_i:
        {
          this->keyboard.keyI = LE_PRESSED;
        } break;
        case SDLK_INSERT:
        {
          this->keyboard.keyInsert = LE_PRESSED;
        } break;
        case SDLK_j:
        {
          this->keyboard.keyJ = LE_PRESSED;
        } break;
        case SDLK_k:
        {
          this->keyboard.keyK = LE_PRESSED;
        } break;
        case SDLK_KBDILLUMDOWN:
        {
          this->keyboard.keyKBDillumDown = LE_PRESSED;
        } break;
        case SDLK_KBDILLUMTOGGLE:
        {
          this->keyboard.keyKBDillumToggle = LE_PRESSED;
        } break;
        case SDLK_KBDILLUMUP:
        {
          this->keyboard.keyKBDillumUp = LE_PRESSED;
        } break;
        case SDLK_KP_0:
        {
          this->keyboard.keyKeypad0 = LE_PRESSED;
        } break;
        case SDLK_KP_00:
        {
          this->keyboard.keyKeypad00 = LE_PRESSED;
        } break;
        case SDLK_KP_000:
        {
          this->keyboard.keyKeypad000 = LE_PRESSED;
        } break;
        case SDLK_KP_1:
        {
          this->keyboard.keyKeypad1 = LE_PRESSED;
        } break;
        case SDLK_KP_2:
        {
          this->keyboard.keyKeypad2 = LE_PRESSED;
        } break;
        case SDLK_KP_3:
        {
          this->keyboard.keyKeypad3 = LE_PRESSED;
        } break;
        case SDLK_KP_4:
        {
          this->keyboard.keyKeypad4 = LE_PRESSED;
        } break;
        case SDLK_KP_5:
        {
          this->keyboard.keyKeypad5 = LE_PRESSED;
        } break;
        case SDLK_KP_6:
        {
          this->keyboard.keyKeypad6 = LE_PRESSED;
        } break;
        case SDLK_KP_7:
        {
          this->keyboard.keyKeypad7 = LE_PRESSED;
        } break;
        case SDLK_KP_8:
        {
          this->keyboard.keyKeypad8 = LE_PRESSED;
        } break;
        case SDLK_KP_9:
        {
          this->keyboard.keyKeypad9 = LE_PRESSED;
        } break;
        case SDLK_KP_A:
        {
          this->keyboard.keyKeypadA = LE_PRESSED;
        } break;
        case SDLK_KP_AMPERSAND:
        {
          this->keyboard.keyKeypadAnd = LE_PRESSED;
        } break;
        case SDLK_KP_AT:
        {
          this->keyboard.keyKeypadAt = LE_PRESSED;
        } break;
        case SDLK_KP_B:
        {
          this->keyboard.keyKeypadB = LE_PRESSED;
        } break;
        case SDLK_KP_BACKSPACE:
        {
          this->keyboard.keyKeypadBackspace = LE_PRESSED;
        } break;
        case SDLK_KP_BINARY:
        {
          this->keyboard.keyKeypadBinary = LE_PRESSED;
        } break;
        case SDLK_KP_C:
        {
          this->keyboard.keyKeypadC = LE_PRESSED;
        } break;
        case SDLK_KP_CLEAR:
        {
          this->keyboard.keyKeypadClear = LE_PRESSED;
        } break;
        case SDLK_KP_CLEARENTRY:
        {
          this->keyboard.keyKeypadClearEntry = LE_PRESSED;
        } break;
        case SDLK_KP_COLON:
        {
          this->keyboard.keyKeypadColon = LE_PRESSED;
        } break;
        case SDLK_KP_COMMA:
        {
          this->keyboard.keyKeypadComma = LE_PRESSED;
        } break;
        case SDLK_KP_D:
        {
          this->keyboard.keyKeypadD = LE_PRESSED;
        } break;
        case SDLK_KP_DBLAMPERSAND:
        {
          this->keyboard.keyKeypadDoubleAnd = LE_PRESSED;
        } break;
        case SDLK_KP_DBLVERTICALBAR:
        {
          this->keyboard.keyKeypadDoubleOr = LE_PRESSED;
        } break;
        case SDLK_KP_DECIMAL:
        {
          this->keyboard.keyKeypadDecimal = LE_PRESSED;
        } break;
        case SDLK_KP_DIVIDE:
        {
          this->keyboard.keyKeypadDivide = LE_PRESSED;
        } break;
        case SDLK_KP_E:
        {
          this->keyboard.keyKeypadE = LE_PRESSED;
        } break;
        case SDLK_KP_ENTER:
        {
          this->keyboard.keyKeypadEnter = LE_PRESSED;
        } break;
        case SDLK_KP_EQUALS:
        {
          this->keyboard.keyKeypadEquals = LE_PRESSED;
        } break;
        case SDLK_KP_EQUALSAS400:
        {
          this->keyboard.keyKeypadEqualsAS400 = LE_PRESSED;
        } break;
        case SDLK_KP_EXCLAM:
        {
          this->keyboard.keyKeypadExclamation = LE_PRESSED;
        } break;
        case SDLK_KP_F:
        {
          this->keyboard.keyKeypadF = LE_PRESSED;
        } break;
        case SDLK_KP_GREATER:
        {
          this->keyboard.keyKeypadGreater = LE_PRESSED;
        } break;
        case SDLK_KP_HASH:
        {
          this->keyboard.keyKeypadHash = LE_PRESSED;
        } break;
        case SDLK_KP_HEXADECIMAL:
        {
          this->keyboard.keyKeypadHexadecimal = LE_PRESSED;
        } break;
        case SDLK_KP_LEFTBRACE:
        {
          this->keyboard.keyKeypadLeftBrace = LE_PRESSED;
        } break;
        case SDLK_KP_LEFTPAREN:
        {
          this->keyboard.keyKeypadLeftParen = LE_PRESSED;
        } break;
        case SDLK_KP_LESS:
        {
          this->keyboard.keyKeypadLess = LE_PRESSED;
        } break;
        case SDLK_KP_MEMADD:
        {
          this->keyboard.keyKeypadMemAdd = LE_PRESSED;
        } break;
        case SDLK_KP_MEMCLEAR:
        {
          this->keyboard.keyKeypadMemClear = LE_PRESSED;
        } break;
        case SDLK_KP_MEMDIVIDE:
        {
          this->keyboard.keyKeypadMemDivide = LE_PRESSED;
        } break;
        case SDLK_KP_MEMMULTIPLY:
        {
          this->keyboard.keyKeypadMemMultiply = LE_PRESSED;
        } break;
        case SDLK_KP_MEMRECALL:
        {
          this->keyboard.keyKeypadMemRecall = LE_PRESSED;
        } break;
        case SDLK_KP_MEMSTORE:
        {
          this->keyboard.keyKeypadMemStore = LE_PRESSED;
        } break;
        case SDLK_KP_MEMSUBTRACT:
        {
          this->keyboard.keyKeypadMemSubtract = LE_PRESSED;
        } break;
        case SDLK_KP_MINUS:
        {
          this->keyboard.keyKeypadMinus = LE_PRESSED;
        } break;
        case SDLK_KP_MULTIPLY:
        {
          this->keyboard.keyKeypadMultiply = LE_PRESSED;
        } break;
        case SDLK_KP_OCTAL:
        {
          this->keyboard.keyKeypadOctal = LE_PRESSED;
        } break;
        case SDLK_KP_PERCENT:
        {
          this->keyboard.keyKeypadPercent = LE_PRESSED;
        } break;
        case SDLK_KP_PERIOD:
        {
          this->keyboard.keyKeypadPeriod = LE_PRESSED;
        } break;
        case SDLK_KP_PLUS:
        {
          this->keyboard.keyKeypadPlus = LE_PRESSED;
        } break;
        case SDLK_KP_PLUSMINUS:
        {
          this->keyboard.keyKeypadPlusMinus = LE_PRESSED;
        } break;
        case SDLK_KP_POWER:
        {
          this->keyboard.keyKeypadPower = LE_PRESSED;
        } break;
        case SDLK_KP_RIGHTBRACE:
        {
          this->keyboard.keyKeypadRightBrace = LE_PRESSED;
        } break;
        case SDLK_KP_RIGHTPAREN:
        {
          this->keyboard.keyKeypadRightParen = LE_PRESSED;
        } break;
        case SDLK_KP_SPACE:
        {
          this->keyboard.keyKeypadSpace = LE_PRESSED;
        } break;
        case SDLK_KP_TAB:
        {
          this->keyboard.keyKeypadTab = LE_PRESSED;
        } break;
        case SDLK_KP_VERTICALBAR:
        {
          this->keyboard.keyKeypadVerticalBar = LE_PRESSED;
        } break;
        case SDLK_KP_XOR:
        {
          this->keyboard.keyKeypadXOR = LE_PRESSED;
        } break;
        case SDLK_l:
        {
          this->keyboard.keyL = LE_PRESSED;
        } break;
        case SDLK_LALT:
        {
          this->keyboard.keyLeftAlt = LE_PRESSED;
        } break;
        case SDLK_LCTRL:
        {
          this->keyboard.keyLeftCtrl = LE_PRESSED;
        } break;
        case SDLK_LEFT:
        {
          this->keyboard.keyLeft = LE_PRESSED;
        } break;
        case SDLK_LEFTBRACKET:
        {
          this->keyboard.keyLeftBracket = LE_PRESSED;
        } break;
        case SDLK_LGUI:
        {
          this->keyboard.keyLeftGUI = LE_PRESSED;
        } break;
        case SDLK_LSHIFT:
        {
          this->keyboard.keyLeftShift = LE_PRESSED;
        } break;
        case SDLK_m:
        {
          this->keyboard.keyM = LE_PRESSED;
        } break;
        case SDLK_MAIL:
        {
          this->keyboard.keyMail = LE_PRESSED;
        } break;
        case SDLK_MEDIASELECT:
        {
          this->keyboard.keyMediaSelect = LE_PRESSED;
        } break;
        case SDLK_MENU:
        {
          this->keyboard.keyMenu = LE_PRESSED;
        } break;
        case SDLK_MINUS:
        {
          this->keyboard.keyMinus = LE_PRESSED;
        } break;
        case SDLK_MODE:
        {
          this->keyboard.keyModeSwitch = LE_PRESSED;
        } break;
        case SDLK_MUTE:
        {
          this->keyboard.keyMute = LE_PRESSED;
        } break;
        case SDLK_n:
        {
          this->keyboard.keyN = LE_PRESSED;
        } break;
        case SDLK_NUMLOCKCLEAR:
        {
          this->keyboard.keyNumLock = LE_PRESSED;
        } break;
        case SDLK_o:
        {
          this->keyboard.keyO = LE_PRESSED;
        } break;
        case SDLK_OPER:
        {
          this->keyboard.keyOper = LE_PRESSED;
        } break;
        case SDLK_OUT:
        {
          this->keyboard.keyOut = LE_PRESSED;
        } break;
        case SDLK_p:
        {
          this->keyboard.keyP = LE_PRESSED;
        } break;
        case SDLK_PAGEDOWN:
        {
          this->keyboard.keyPageDown = LE_PRESSED;
        } break;
        case SDLK_PAGEUP:
        {
          this->keyboard.keyPageUp = LE_PRESSED;
        } break;
        case SDLK_PASTE:
        {
          this->keyboard.keyPaste = LE_PRESSED;
        } break;
        case SDLK_PAUSE:
        {
          this->keyboard.keyPause = LE_PRESSED;
        } break;
        case SDLK_PERIOD:
        {
          this->keyboard.keyPeriod = LE_PRESSED;
        } break;
        case SDLK_POWER:
        {
          this->keyboard.keyPower = LE_PRESSED;
        } break;
        case SDLK_PRINTSCREEN:
        {
          this->keyboard.keyPrintScreen = LE_PRESSED;
        } break;
        case SDLK_PRIOR:
        {
          this->keyboard.keyPrior = LE_PRESSED;
        } break;
        case SDLK_q:
        {
          this->keyboard.keyQ = LE_PRESSED;
        } break;
        case SDLK_r:
        {
          this->keyboard.keyR = LE_PRESSED;
        } break;
        case SDLK_RALT:
        {
          this->keyboard.keyRightAlt = LE_PRESSED;
        } break;
        case SDLK_RCTRL:
        {
          this->keyboard.keyRightCtrl = LE_PRESSED;
        } break;
        case SDLK_RETURN:
        {
          this->keyboard.keyReturn = LE_PRESSED;
        } break;
        case SDLK_RETURN2:
        {
          this->keyboard.keyReturn2 = LE_PRESSED;
        } break;
        case SDLK_RGUI:
        {
          this->keyboard.keyRightGUI = LE_PRESSED;
        } break;
        case SDLK_RIGHT:
        {
          this->keyboard.keyRight = LE_PRESSED;
        } break;
        case SDLK_RIGHTBRACKET:
        {
          this->keyboard.keyRightBracket = LE_PRESSED;
        } break;
        case SDLK_RSHIFT:
        {
          this->keyboard.keyRightShift = LE_PRESSED;
        } break;
        case SDLK_s:
        {
          this->keyboard.keyS = LE_PRESSED;
        } break;
        case SDLK_SCROLLLOCK:
        {
          this->keyboard.keyScrollLock = LE_PRESSED;
        } break;
        case SDLK_SELECT:
        {
          this->keyboard.keySelect = LE_PRESSED;
        } break;
        case SDLK_SEMICOLON:
        {
          this->keyboard.keySemicolon = LE_PRESSED;
        } break;
        case SDLK_SEPARATOR:
        {
          this->keyboard.keySeparator = LE_PRESSED;
        } break;
        case SDLK_SLASH:
        {
          this->keyboard.keySlash = LE_PRESSED;
        } break;
        case SDLK_SLEEP:
        {
          this->keyboard.keySleep = LE_PRESSED;
        } break;
        case SDLK_SPACE:
        {
          this->keyboard.keySpace = LE_PRESSED;
        } break;
        case SDLK_STOP:
        {
          this->keyboard.keyStop = LE_PRESSED;
        } break;
        case SDLK_SYSREQ:
        {
          this->keyboard.keySysReq = LE_PRESSED;
        } break;
        case SDLK_t:
        {
          this->keyboard.keyT = LE_PRESSED;
        } break;
        case SDLK_TAB:
        {
          this->keyboard.keyTab = LE_PRESSED;
        } break;
        case SDLK_THOUSANDSSEPARATOR:
        {
          this->keyboard.keyThousandsSeparator = LE_PRESSED;
        } break;
        case SDLK_u:
        {
          this->keyboard.keyU = LE_PRESSED;
        } break;
        case SDLK_UNDO:
        {
          this->keyboard.keyUndo = LE_PRESSED;
        } break;
        case SDLK_UP:
        {
          this->keyboard.keyUp = LE_PRESSED;
        } break;
        case SDLK_v:
        {
          this->keyboard.keyV = LE_PRESSED;
        } break;
        case SDLK_VOLUMEDOWN:
        {
          this->keyboard.keyVolumeDown = LE_PRESSED;
        } break;
        case SDLK_VOLUMEUP:
        {
          this->keyboard.keyVolumeUp = LE_PRESSED;
        } break;
        case SDLK_w:
        {
          this->keyboard.keyW = LE_PRESSED;
        } break;
        case SDLK_WWW:
        {
          this->keyboard.keyWWW = LE_PRESSED;
        } break;
        case SDLK_x:
        {
          this->keyboard.keyX = LE_PRESSED;
        } break;
        case SDLK_y:
        {
          this->keyboard.keyY = LE_PRESSED;
        } break;
        case SDLK_z:
        {
          this->keyboard.keyZ = LE_PRESSED;
        } break;
      };
    } break;
  };
}

void LEMoon::freeKey(uint8_t &key)
{
  if(key == LE_RELEASED)
    {key = LE_INACTIVE;}
}

void LEMoon::freeKeyboardKeys()
{
  this->freeKey(this->keyboard.key0);
  this->freeKey(this->keyboard.key1);
  this->freeKey(this->keyboard.key2);
  this->freeKey(this->keyboard.key3);
  this->freeKey(this->keyboard.key4);
  this->freeKey(this->keyboard.key5);
  this->freeKey(this->keyboard.key6);
  this->freeKey(this->keyboard.key7);
  this->freeKey(this->keyboard.key8);
  this->freeKey(this->keyboard.key9);
  this->freeKey(this->keyboard.keyA);
  this->freeKey(this->keyboard.keyACBack);
  this->freeKey(this->keyboard.keyACBookmarks);
  this->freeKey(this->keyboard.keyACForward);
  this->freeKey(this->keyboard.keyACHome);
  this->freeKey(this->keyboard.keyACRefresh);
  this->freeKey(this->keyboard.keyACSearch);
  this->freeKey(this->keyboard.keyACStop);
  this->freeKey(this->keyboard.keyAgain);
  this->freeKey(this->keyboard.keyAltErase);
  this->freeKey(this->keyboard.keyApostrophe);
  this->freeKey(this->keyboard.keyApplication);
  this->freeKey(this->keyboard.keyAudioMute);
  this->freeKey(this->keyboard.keyAudioNext);
  this->freeKey(this->keyboard.keyAudioPlay);
  this->freeKey(this->keyboard.keyAudioPrev);
  this->freeKey(this->keyboard.keyAudioStop);
  this->freeKey(this->keyboard.keyB);
  this->freeKey(this->keyboard.keyBackslash);
  this->freeKey(this->keyboard.keyBackspace);
  this->freeKey(this->keyboard.keyBrightnessDown);
  this->freeKey(this->keyboard.keyBrightnessUp);
  this->freeKey(this->keyboard.keyC);
  this->freeKey(this->keyboard.keyCalculator);
  this->freeKey(this->keyboard.keyCancel);
  this->freeKey(this->keyboard.keyCapsLock);
  this->freeKey(this->keyboard.keyClear);
  this->freeKey(this->keyboard.keyClearAgain);
  this->freeKey(this->keyboard.keyComma);
  this->freeKey(this->keyboard.keyComputer);
  this->freeKey(this->keyboard.keyCopy);
  this->freeKey(this->keyboard.keyCrSel);
  this->freeKey(this->keyboard.keyCurrencySubUnit);
  this->freeKey(this->keyboard.keyCurrencyUnit);
  this->freeKey(this->keyboard.keyCut);
  this->freeKey(this->keyboard.keyD);
  this->freeKey(this->keyboard.keyDecimalSeparator);
  this->freeKey(this->keyboard.keyDelete);
  this->freeKey(this->keyboard.keyDisplaySwitch);
  this->freeKey(this->keyboard.keyDown);
  this->freeKey(this->keyboard.keyE);
  this->freeKey(this->keyboard.keyEject);
  this->freeKey(this->keyboard.keyEnd);
  this->freeKey(this->keyboard.keyEquals);
  this->freeKey(this->keyboard.keyEscape);
  this->freeKey(this->keyboard.keyExecute);
  this->freeKey(this->keyboard.keyExSel);
  this->freeKey(this->keyboard.keyF);
  this->freeKey(this->keyboard.keyF1);
  this->freeKey(this->keyboard.keyF2);
  this->freeKey(this->keyboard.keyF3);
  this->freeKey(this->keyboard.keyF4);
  this->freeKey(this->keyboard.keyF5);
  this->freeKey(this->keyboard.keyF6);
  this->freeKey(this->keyboard.keyF7);
  this->freeKey(this->keyboard.keyF8);
  this->freeKey(this->keyboard.keyF9);
  this->freeKey(this->keyboard.keyF10);
  this->freeKey(this->keyboard.keyF11);
  this->freeKey(this->keyboard.keyF12);
  this->freeKey(this->keyboard.keyF13);
  this->freeKey(this->keyboard.keyF14);
  this->freeKey(this->keyboard.keyF15);
  this->freeKey(this->keyboard.keyF16);
  this->freeKey(this->keyboard.keyF17);
  this->freeKey(this->keyboard.keyF18);
  this->freeKey(this->keyboard.keyF19);
  this->freeKey(this->keyboard.keyF20);
  this->freeKey(this->keyboard.keyF21);
  this->freeKey(this->keyboard.keyF22);
  this->freeKey(this->keyboard.keyF23);
  this->freeKey(this->keyboard.keyF24);
  this->freeKey(this->keyboard.keyFind);
  this->freeKey(this->keyboard.keyG);
  this->freeKey(this->keyboard.keyBackquote);
  this->freeKey(this->keyboard.keyH);
  this->freeKey(this->keyboard.keyHelp);
  this->freeKey(this->keyboard.keyHome);
  this->freeKey(this->keyboard.keyI);
  this->freeKey(this->keyboard.keyInsert);
  this->freeKey(this->keyboard.keyJ);
  this->freeKey(this->keyboard.keyK);
  this->freeKey(this->keyboard.keyKBDillumDown);
  this->freeKey(this->keyboard.keyKBDillumToggle);
  this->freeKey(this->keyboard.keyKBDillumUp);
  this->freeKey(this->keyboard.keyKeypad0);
  this->freeKey(this->keyboard.keyKeypad00);
  this->freeKey(this->keyboard.keyKeypad000);
  this->freeKey(this->keyboard.keyKeypad1);
  this->freeKey(this->keyboard.keyKeypad2);
  this->freeKey(this->keyboard.keyKeypad3);
  this->freeKey(this->keyboard.keyKeypad4);
  this->freeKey(this->keyboard.keyKeypad5);
  this->freeKey(this->keyboard.keyKeypad6);
  this->freeKey(this->keyboard.keyKeypad7);
  this->freeKey(this->keyboard.keyKeypad8);
  this->freeKey(this->keyboard.keyKeypad9);
  this->freeKey(this->keyboard.keyKeypadA);
  this->freeKey(this->keyboard.keyKeypadAnd);
  this->freeKey(this->keyboard.keyKeypadAt);
  this->freeKey(this->keyboard.keyKeypadB);
  this->freeKey(this->keyboard.keyKeypadBackspace);
  this->freeKey(this->keyboard.keyKeypadBinary);
  this->freeKey(this->keyboard.keyKeypadC);
  this->freeKey(this->keyboard.keyKeypadClear);
  this->freeKey(this->keyboard.keyKeypadClearEntry);
  this->freeKey(this->keyboard.keyKeypadColon);
  this->freeKey(this->keyboard.keyKeypadComma);
  this->freeKey(this->keyboard.keyKeypadD);
  this->freeKey(this->keyboard.keyKeypadDoubleAnd);
  this->freeKey(this->keyboard.keyKeypadDoubleOr);
  this->freeKey(this->keyboard.keyKeypadDecimal);
  this->freeKey(this->keyboard.keyKeypadDivide);
  this->freeKey(this->keyboard.keyKeypadE);
  this->freeKey(this->keyboard.keyKeypadEnter);
  this->freeKey(this->keyboard.keyKeypadEquals);
  this->freeKey(this->keyboard.keyKeypadEqualsAS400);
  this->freeKey(this->keyboard.keyKeypadExclamation);
  this->freeKey(this->keyboard.keyKeypadF);
  this->freeKey(this->keyboard.keyKeypadGreater);
  this->freeKey(this->keyboard.keyKeypadHash);
  this->freeKey(this->keyboard.keyKeypadHexadecimal);
  this->freeKey(this->keyboard.keyKeypadLeftBrace);
  this->freeKey(this->keyboard.keyKeypadLeftParen);
  this->freeKey(this->keyboard.keyKeypadLess);
  this->freeKey(this->keyboard.keyKeypadMemAdd);
  this->freeKey(this->keyboard.keyKeypadMemClear);
  this->freeKey(this->keyboard.keyKeypadMemDivide);
  this->freeKey(this->keyboard.keyKeypadMemMultiply);
  this->freeKey(this->keyboard.keyKeypadMemRecall);
  this->freeKey(this->keyboard.keyKeypadMemStore);
  this->freeKey(this->keyboard.keyKeypadMemSubtract);
  this->freeKey(this->keyboard.keyKeypadMinus);
  this->freeKey(this->keyboard.keyKeypadMultiply);
  this->freeKey(this->keyboard.keyKeypadOctal);
  this->freeKey(this->keyboard.keyKeypadPercent);
  this->freeKey(this->keyboard.keyKeypadPeriod);
  this->freeKey(this->keyboard.keyKeypadPlus);
  this->freeKey(this->keyboard.keyKeypadPlusMinus);
  this->freeKey(this->keyboard.keyKeypadPower);
  this->freeKey(this->keyboard.keyKeypadRightBrace);
  this->freeKey(this->keyboard.keyKeypadRightParen);
  this->freeKey(this->keyboard.keyKeypadSpace);
  this->freeKey(this->keyboard.keyKeypadTab);
  this->freeKey(this->keyboard.keyKeypadVerticalBar);
  this->freeKey(this->keyboard.keyKeypadXOR);
  this->freeKey(this->keyboard.keyL);
  this->freeKey(this->keyboard.keyLeftAlt);
  this->freeKey(this->keyboard.keyLeftCtrl);
  this->freeKey(this->keyboard.keyLeft);
  this->freeKey(this->keyboard.keyLeftBracket);
  this->freeKey(this->keyboard.keyLeftGUI);
  this->freeKey(this->keyboard.keyLeftShift);
  this->freeKey(this->keyboard.keyM);
  this->freeKey(this->keyboard.keyMail);
  this->freeKey(this->keyboard.keyMediaSelect);
  this->freeKey(this->keyboard.keyMenu);
  this->freeKey(this->keyboard.keyMinus);
  this->freeKey(this->keyboard.keyModeSwitch);
  this->freeKey(this->keyboard.keyMute);
  this->freeKey(this->keyboard.keyN);
  this->freeKey(this->keyboard.keyNumLock);
  this->freeKey(this->keyboard.keyO);
  this->freeKey(this->keyboard.keyOper);
  this->freeKey(this->keyboard.keyOut);
  this->freeKey(this->keyboard.keyP);
  this->freeKey(this->keyboard.keyPageDown);
  this->freeKey(this->keyboard.keyPageUp);
  this->freeKey(this->keyboard.keyPaste);
  this->freeKey(this->keyboard.keyPause);
  this->freeKey(this->keyboard.keyPeriod);
  this->freeKey(this->keyboard.keyPower);
  this->freeKey(this->keyboard.keyPrintScreen);
  this->freeKey(this->keyboard.keyPrior);
  this->freeKey(this->keyboard.keyQ);
  this->freeKey(this->keyboard.keyR);
  this->freeKey(this->keyboard.keyRightAlt);
  this->freeKey(this->keyboard.keyRightCtrl);
  this->freeKey(this->keyboard.keyReturn);
  this->freeKey(this->keyboard.keyReturn2);
  this->freeKey(this->keyboard.keyRightGUI);
  this->freeKey(this->keyboard.keyRight);
  this->freeKey(this->keyboard.keyRightBracket);
  this->freeKey(this->keyboard.keyRightShift);
  this->freeKey(this->keyboard.keyS);
  this->freeKey(this->keyboard.keyScrollLock);
  this->freeKey(this->keyboard.keySelect);
  this->freeKey(this->keyboard.keySemicolon);
  this->freeKey(this->keyboard.keySeparator);
  this->freeKey(this->keyboard.keySlash);
  this->freeKey(this->keyboard.keySleep);
  this->freeKey(this->keyboard.keySpace);
  this->freeKey(this->keyboard.keyStop);
  this->freeKey(this->keyboard.keySysReq);
  this->freeKey(this->keyboard.keyT);
  this->freeKey(this->keyboard.keyTab);
  this->freeKey(this->keyboard.keyThousandsSeparator);
  this->freeKey(this->keyboard.keyU);
  this->freeKey(this->keyboard.keyUndo);
  this->freeKey(this->keyboard.keyUp);
  this->freeKey(this->keyboard.keyV);
  this->freeKey(this->keyboard.keyVolumeDown);
  this->freeKey(this->keyboard.keyVolumeUp);
  this->freeKey(this->keyboard.keyW);
  this->freeKey(this->keyboard.keyWWW);
  this->freeKey(this->keyboard.keyX);
  this->freeKey(this->keyboard.keyY);
  this->freeKey(this->keyboard.keyZ);
}

void LEMoon::freeMouse()
{
  if(this->mouse.leftButton == LE_RELEASED)
    {this->mouse.leftButton = LE_INACTIVE;}

  if(this->mouse.rightButton == LE_RELEASED)
    {this->mouse.rightButton = LE_INACTIVE;}
}

int LEMoon::merge()
{
  int result = LE_NO_ERROR;

  result = this->fontMerge();

  if(!result)
    {result = this->lineMerge();}
  if(!result)
    {result = this->modelMerge();}
  if(!result)
    {result = this->pointMerge();}
  if(!result)
    {result = this->soundMerge();}
  if(!result)
    {result = this->textMerge();}
  if(!result)
    {result = this->timeEventMerge();}

  return result;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public general
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

LEMoon::LEMoon():
initialized(LE_FALSE),
timestamp(0),
timestep(0.0f)
{
  this->pWindow = nullptr;
  this->pRenderer = nullptr;

  this->fontConstructor();
  this->lineConstructor();
  this->modelConstructor();
  this->pointConstructor();
  this->soundConstructor();
  this->textConstructor();
  this->timeEventConstructor();

  this->pVideoHead = nullptr;

  this->mouse.mouseX = 0;
  this->mouse.mouseY = 0;

  this->clearKeyboard();

  this->mouse.leftButton = LE_INACTIVE;
  this->mouse.rightButton = LE_INACTIVE;

  this->backgroundColor.r = 255;
  this->backgroundColor.g = 255;
  this->backgroundColor.b = 255;
  this->backgroundColor.a = 255;

  this->fps.lastFPS = 0;
  this->fps.countToTime = 0;
  this->fps.framesPerSecond = 0;
  this->fps.recentFPS = LE_TRUE;

  this->memory.pLastModel = nullptr;
  this->memory.pLastSound = nullptr;
  this->memory.pLastTimeEvent = nullptr;
  this->memory.pLastPoint = nullptr;
  this->memory.pLastFont = nullptr;
  this->memory.pLastText = nullptr;
  this->memory.pLastLine = nullptr;

  this->window.focusGained = LE_FALSE;
  this->prefPath = nullptr;
}

LEMoon::~LEMoon()
{
  // loesche Models

  this->memoryClearModels();

  // loesche Zeitereignisse

  this->memoryClearTimeEvents();

  // loesche alle Punkte

  this->memoryClearPoints();

  // loesche alle Sounds

  this->memoryClearSounds();

  // loesche alle Texte

  this->memoryClearTexts();

  // loesche Fonts

  this->memoryClearFonts();

  // loesche Linien

  this->memoryClearLines();

  // loesche SDL

  SDL_DestroyRenderer(this->pRenderer);
  SDL_DestroyWindow(this->pWindow);
  Mix_CloseAudio();
  TTF_Quit();
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
}

void LEMoon::printErrorMessage(const char * pTitle, const char * pMessage)
{
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, pTitle, pMessage, nullptr);
}

bool LEMoon::engineInitialized()
{
  return this->initialized;
}

int LEMoon::init(const char * pAppName)
{
  int result = LE_NO_ERROR;
  char * pString = new char [512 + 1];
  char * pBasePath = nullptr;

  // initialize SDL

  if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS))
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_SDL_INIT, "LEMoon::init()\n\n");
    #endif

    result = LE_SDL_INIT;
  }

  // pref Path

  if(!result)
  {
    #ifdef LE_ANDROID
      pBasePath = (char*)SDL_AndroidGetExternalStoragePath();
      sprintf(pString, "%s/", pBasePath);
      this->prefPath = new char[strlen(pString)];
      strcpy(this->prefPath, pString);
    #else
      this->prefPath = SDL_GetPrefPath("Lynar Moon Engine", pAppName);
    #endif

    #ifdef LE_DEBUG
      sprintf(pString, "pref Path: %s\n", this->prefPath);
      this->printErrorMessage("Info", pString);
    #endif
  }

  // get display mode

  if(!result)
  {
    if(SDL_GetCurrentDisplayMode(0, &(this->displayMode)))
    {
      #ifdef LE_DEBUG
        this->printErrorDialog(LE_SDL_DISPLAYMODE, "LEMoon::init()\n\n");
      #endif

      result = LE_SDL_DISPLAYMODE;
    }
  }

  // create window

  if(!result)
  {
    this->pWindow = SDL_CreateWindow(pAppName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->displayMode.w, this->displayMode.h, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);

    if(this->pWindow == nullptr)
    {
      #ifdef LE_DEBUG
        this->printErrorDialog(LE_SDL_WINDOW, "LEMoon::init()\n\n");
      #endif

      result = LE_SDL_WINDOW;
    }
  }

  // create renderer

  if(!result)
  {
    this->pRenderer = SDL_CreateRenderer(this->pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(this->pRenderer == nullptr)
    {
      #ifdef LE_DEBUG
        this->printErrorDialog(LE_SDL_RENDERER, "LEMoon::init()\n\n");
      #endif

      result = LE_SDL_RENDERER;
    }
  }

  if(!result)
  {
    #ifdef LE_WINDOWS
      system("cls");
    #endif

    #ifdef LE_LINUX
      std::system("clear");
    #endif

    printf("                        _..._\n");
    printf("                      .'   `::.\n");
    printf("                     :       :::\n");
    printf("Lynar Moon Engine    :       :::\n");
    printf("                     `.     .::'\n");
    printf("                       `-..:''\n\n\n");
    printf("version:\t\t1.4\n");
    printf("release-date:\t\t04.05.2018\n");
    printf("website:\t\twww.lynarstudios.de\n");
    printf("\n");
    printf("author:\t\t\tPatrick-Christopher Mattulat\n");
    printf("co-author:\t\tSebastian Bruchhold\n");
    printf("\n");

    this->initialized = LE_TRUE;
  }


  if(pString != nullptr)
  {
    delete [] pString;
    pString = nullptr;
  }

  if(pBasePath != nullptr)
  {
    delete [] pBasePath;
    pBasePath = nullptr;
  }

  return result;
}

int LEMoon::initImage()
{
  int result = LE_NO_ERROR;

  // load image library

  if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) || !(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_SDL_IMG_INIT, "LEMoon::initImage()\n\n");
    #endif

    result = LE_SDL_IMG_INIT;
  }

  return result;
}

int LEMoon::initSound(int numChannels)
{
  int result = LE_NO_ERROR;
  int mixFlags = 0;

  if(SDL_InitSubSystem(SDL_INIT_AUDIO))
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_INIT_SUBSYSTEM, "LEMoon::initSound()\n\n");
    #endif
  }

  // Sounds

  if((Mix_Init(mixFlags) & mixFlags) != mixFlags)
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MIXER_INIT, "LEMoon::initSound()\n\n");
    #endif

    result = LE_MIXER_INIT;
  }

  // open Audio Channel Stereo

  if(!result)
  {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024))
    {
      #ifdef LE_DEBUG
        this->printErrorDialog(LE_OPEN_AUDIO, "LEMoon::initSound()\n\n");
      #endif

      result = LE_OPEN_AUDIO;
    }
  }

  // set number of Channels

  if(!result)
  {
    if(Mix_AllocateChannels(numChannels) != numChannels)
    {
      #ifdef LE_DEBUG
        this->printErrorDialog(LE_ALLOC_CHANNELS, "LEMoon::initSound()\n\n");
      #endif

      result = LE_ALLOC_CHANNELS;
    }
  }

  return result;
}

int LEMoon::initTTF()
{
  int result = LE_NO_ERROR;

  // init TTF

  if(TTF_Init())
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_TTF_INIT, "LEMoon::initTTF()\n\n");
    #endif

    result = LE_TTF_INIT;
  }

  return result;
}

int LEMoon::pollEvent()
{
  return SDL_PollEvent(&(this->event));
}

void LEMoon::beginFrame()
{
  this->timestamp = SDL_GetTicks();
  this->handleKeyboard();
  this->handleMouse();
  this->handleWindow();
  SDL_GetMouseState(&(this->mouse.mouseX), &(this->mouse.mouseY));

  // fps

  if(this->timestamp >= this->fps.countToTime)
  {
    this->fps.countToTime = this->timestamp + 1000;
    this->fps.lastFPS = this->fps.framesPerSecond;
    this->fps.framesPerSecond = 0;
    this->fps.recentFPS = LE_TRUE;
  }
  else
    {this->fps.framesPerSecond++;}
}

bool LEMoon::mouseEvent(uint32_t state, uint8_t button)
{
  bool flag = LE_FALSE;

  switch(state)
  {
    case SDL_MOUSEBUTTONDOWN:
    {
      switch(button)
      {
        case SDL_BUTTON_LEFT:
        {
          flag = (this->mouse.leftButton == LE_PRESSED);
        } break;
        case SDL_BUTTON_RIGHT:
        {
          flag = (this->mouse.rightButton == LE_PRESSED);
        } break;
      };
    } break;
    case SDL_MOUSEBUTTONUP:
    {
      switch(button)
      {
        case SDL_BUTTON_LEFT:
        {
          flag = (this->mouse.leftButton == LE_RELEASED);
        } break;
        case SDL_BUTTON_RIGHT:
        {
          flag = (this->mouse.rightButton == LE_RELEASED);
        } break;
      };
    } break;
  };

  return flag;
}

bool LEMoon::keyEvent(uint32_t state, SDL_Keycode key)
{
  bool flag = LE_FALSE;

  switch(state)
  {
    case SDL_KEYDOWN:
    {
      switch(key)
      {
        case SDLK_0:
        {
          flag = (this->keyboard.key0 == LE_PRESSED);
        } break;
        case SDLK_1:
        {
          flag = (this->keyboard.key1 == LE_PRESSED);
        } break;
        case SDLK_2:
        {
          flag = (this->keyboard.key2 == LE_PRESSED);
        } break;
        case SDLK_3:
        {
          flag = (this->keyboard.key3 == LE_PRESSED);
        } break;
        case SDLK_4:
        {
          flag = (this->keyboard.key4 == LE_PRESSED);
        } break;
        case SDLK_5:
        {
          flag = (this->keyboard.key5 == LE_PRESSED);
        } break;
        case SDLK_6:
        {
          flag = (this->keyboard.key6 == LE_PRESSED);
        } break;
        case SDLK_7:
        {
          flag = (this->keyboard.key7 == LE_PRESSED);
        } break;
        case SDLK_8:
        {
          flag = (this->keyboard.key8 == LE_PRESSED);
        } break;
        case SDLK_9:
        {
          flag = (this->keyboard.key9 == LE_PRESSED);
        } break;
        case SDLK_a:
        {
          flag = (this->keyboard.keyA == LE_PRESSED);
        } break;
        case SDLK_AC_BACK:
        {
          flag = (this->keyboard.keyACBack == LE_PRESSED);
        } break;
        case SDLK_AC_BOOKMARKS:
        {
          flag = (this->keyboard.keyACBookmarks == LE_PRESSED);
        } break;
        case SDLK_AC_FORWARD:
        {
          flag = (this->keyboard.keyACForward == LE_PRESSED);
        } break;
        case SDLK_AC_HOME:
        {
          flag = (this->keyboard.keyACHome == LE_PRESSED);
        } break;
        case SDLK_AC_REFRESH:
        {
          flag = (this->keyboard.keyACRefresh == LE_PRESSED);
        } break;
        case SDLK_AC_SEARCH:
        {
          flag = (this->keyboard.keyACSearch == LE_PRESSED);
        } break;
        case SDLK_AC_STOP:
        {
          flag = (this->keyboard.keyACStop == LE_PRESSED);
        } break;
        case SDLK_AGAIN:
        {
          flag = (this->keyboard.keyAgain == LE_PRESSED);
        } break;
        case SDLK_ALTERASE:
        {
          flag = (this->keyboard.keyAltErase == LE_PRESSED);
        } break;
        case SDLK_QUOTE:
        {
          flag = (this->keyboard.keyApostrophe == LE_PRESSED);
        } break;
        case SDLK_APPLICATION:
        {
          flag = (this->keyboard.keyApplication == LE_PRESSED);
        } break;
        case SDLK_AUDIOMUTE:
        {
          flag = (this->keyboard.keyAudioMute == LE_PRESSED);
        } break;
        case SDLK_AUDIONEXT:
        {
          flag = (this->keyboard.keyAudioNext == LE_PRESSED);
        } break;
        case SDLK_AUDIOPLAY:
        {
          flag = (this->keyboard.keyAudioPlay == LE_PRESSED);
        } break;
        case SDLK_AUDIOPREV:
        {
          flag = (this->keyboard.keyAudioPrev == LE_PRESSED);
        } break;
        case SDLK_AUDIOSTOP:
        {
          flag = (this->keyboard.keyAudioStop == LE_PRESSED);
        } break;
        case SDLK_b:
        {
          flag = (this->keyboard.keyB == LE_PRESSED);
        } break;
        case SDLK_BACKSLASH:
        {
          flag = (this->keyboard.keyBackslash == LE_PRESSED);
        } break;
        case SDLK_BACKSPACE:
        {
          flag = (this->keyboard.keyBackspace == LE_PRESSED);
        } break;
        case SDLK_BRIGHTNESSDOWN:
        {
          flag = (this->keyboard.keyBrightnessDown == LE_PRESSED);
        } break;
        case SDLK_BRIGHTNESSUP:
        {
          flag = (this->keyboard.keyBrightnessUp == LE_PRESSED);
        } break;
        case SDLK_c:
        {
          flag = (this->keyboard.keyC == LE_PRESSED);
        } break;
        case SDLK_CALCULATOR:
        {
          flag = (this->keyboard.keyCalculator == LE_PRESSED);
        } break;
        case SDLK_CANCEL:
        {
          flag = (this->keyboard.keyCancel == LE_PRESSED);
        } break;
        case SDLK_CAPSLOCK:
        {
          flag = (this->keyboard.keyCapsLock == LE_PRESSED);
        } break;
        case SDLK_CLEAR:
        {
          flag = (this->keyboard.keyClear == LE_PRESSED);
        } break;
        case SDLK_CLEARAGAIN:
        {
          flag = (this->keyboard.keyClearAgain == LE_PRESSED);
        } break;
        case SDLK_COMMA:
        {
          flag = (this->keyboard.keyComma == LE_PRESSED);
        } break;
        case SDLK_COMPUTER:
        {
          flag = (this->keyboard.keyComputer == LE_PRESSED);
        } break;
        case SDLK_COPY:
        {
          flag = (this->keyboard.keyCopy == LE_PRESSED);
        } break;
        case SDLK_CRSEL:
        {
          flag = (this->keyboard.keyCrSel == LE_PRESSED);
        } break;
        case SDLK_CURRENCYSUBUNIT:
        {
          flag = (this->keyboard.keyCurrencySubUnit == LE_PRESSED);
        } break;
        case SDLK_CURRENCYUNIT:
        {
          flag = (this->keyboard.keyCurrencyUnit == LE_PRESSED);
        } break;
        case SDLK_CUT:
        {
          flag = (this->keyboard.keyCut == LE_PRESSED);
        } break;
        case SDLK_d:
        {
          flag = (this->keyboard.keyD == LE_PRESSED);
        } break;
        case SDLK_DECIMALSEPARATOR:
        {
          flag = (this->keyboard.keyDecimalSeparator == LE_PRESSED);
        } break;
        case SDLK_DELETE:
        {
          flag = (this->keyboard.keyDelete == LE_PRESSED);
        } break;
        case SDLK_DISPLAYSWITCH:
        {
          flag = (this->keyboard.keyDisplaySwitch == LE_PRESSED);
        } break;
        case SDLK_DOWN:
        {
          flag = (this->keyboard.keyDown == LE_PRESSED);
        } break;
        case SDLK_e:
        {
          flag = (this->keyboard.keyE == LE_PRESSED);
        } break;
        case SDLK_EJECT:
        {
          flag = (this->keyboard.keyEject == LE_PRESSED);
        } break;
        case SDLK_END:
        {
          flag = (this->keyboard.keyEnd == LE_PRESSED);
        } break;
        case SDLK_EQUALS:
        {
          flag = (this->keyboard.keyEquals == LE_PRESSED);
        } break;
        case SDLK_ESCAPE:
        {
          flag = (this->keyboard.keyEscape == LE_PRESSED);
        } break;
        case SDLK_EXECUTE:
        {
          flag = (this->keyboard.keyExecute == LE_PRESSED);
        } break;
        case SDLK_EXSEL:
        {
          flag = (this->keyboard.keyExSel == LE_PRESSED);
        } break;
        case SDLK_f:
        {
          flag = (this->keyboard.keyF == LE_PRESSED);
        } break;
        case SDLK_F1:
        {
          flag = (this->keyboard.keyF1 == LE_PRESSED);
        } break;
        case SDLK_F10:
        {
          flag = (this->keyboard.keyF10 == LE_PRESSED);
        } break;
        case SDLK_F11:
        {
          flag = (this->keyboard.keyF11 == LE_PRESSED);
        } break;
        case SDLK_F12:
        {
          flag = (this->keyboard.keyF12 == LE_PRESSED);
        } break;
        case SDLK_F13:
        {
          flag = (this->keyboard.keyF13 == LE_PRESSED);
        } break;
        case SDLK_F14:
        {
          flag = (this->keyboard.keyF14 == LE_PRESSED);
        } break;
        case SDLK_F15:
        {
          flag = (this->keyboard.keyF15 == LE_PRESSED);
        } break;
        case SDLK_F16:
        {
          flag = (this->keyboard.keyF16 == LE_PRESSED);
        } break;
        case SDLK_F17:
        {
          flag = (this->keyboard.keyF17 == LE_PRESSED);
        } break;
        case SDLK_F18:
        {
          flag = (this->keyboard.keyF18 == LE_PRESSED);
        } break;
        case SDLK_F19:
        {
          flag = (this->keyboard.keyF19 == LE_PRESSED);
        } break;
        case SDLK_F2:
        {
          flag = (this->keyboard.keyF2 == LE_PRESSED);
        } break;
        case SDLK_F20:
        {
          flag = (this->keyboard.keyF20 == LE_PRESSED);
        } break;
        case SDLK_F21:
        {
          flag = (this->keyboard.keyF21 == LE_PRESSED);
        } break;
        case SDLK_F22:
        {
          flag = (this->keyboard.keyF22 == LE_PRESSED);
        } break;
        case SDLK_F23:
        {
          flag = (this->keyboard.keyF23 == LE_PRESSED);
        } break;
        case SDLK_F24:
        {
          flag = (this->keyboard.keyF24 == LE_PRESSED);
        } break;
        case SDLK_F3:
        {
          flag = (this->keyboard.keyF3 == LE_PRESSED);
        } break;
        case SDLK_F4:
        {
          flag = (this->keyboard.keyF4 == LE_PRESSED);
        } break;
        case SDLK_F5:
        {
          flag = (this->keyboard.keyF5 == LE_PRESSED);
        } break;
        case SDLK_F6:
        {
          flag = (this->keyboard.keyF6 == LE_PRESSED);
        } break;
        case SDLK_F7:
        {
          flag = (this->keyboard.keyF7 == LE_PRESSED);
        } break;
        case SDLK_F8:
        {
          flag = (this->keyboard.keyF8 == LE_PRESSED);
        } break;
        case SDLK_F9:
        {
          flag = (this->keyboard.keyF9 == LE_PRESSED);
        } break;
        case SDLK_FIND:
        {
          flag = (this->keyboard.keyFind == LE_PRESSED);
        } break;
        case SDLK_g:
        {
          flag = (this->keyboard.keyG == LE_PRESSED);
        } break;
        case SDLK_BACKQUOTE:
        {
          flag = (this->keyboard.keyBackquote == LE_PRESSED);
        } break;
        case SDLK_h:
        {
          flag = (this->keyboard.keyH == LE_PRESSED);
        } break;
        case SDLK_HELP:
        {
          flag = (this->keyboard.keyHelp == LE_PRESSED);
        } break;
        case SDLK_HOME:
        {
          flag = (this->keyboard.keyHome == LE_PRESSED);
        } break;
        case SDLK_i:
        {
          flag = (this->keyboard.keyI == LE_PRESSED);
        } break;
        case SDLK_INSERT:
        {
          flag = (this->keyboard.keyInsert == LE_PRESSED);
        } break;
        case SDLK_j:
        {
          flag = (this->keyboard.keyJ == LE_PRESSED);
        } break;
        case SDLK_k:
        {
          flag = (this->keyboard.keyK == LE_PRESSED);
        } break;
        case SDLK_KBDILLUMDOWN:
        {
          flag = (this->keyboard.keyKBDillumDown == LE_PRESSED);
        } break;
        case SDLK_KBDILLUMTOGGLE:
        {
          flag = (this->keyboard.keyKBDillumToggle == LE_PRESSED);
        } break;
        case SDLK_KBDILLUMUP:
        {
          flag = (this->keyboard.keyKBDillumUp == LE_PRESSED);
        } break;
        case SDLK_KP_0:
        {
          flag = (this->keyboard.keyKeypad0 == LE_PRESSED);
        } break;
        case SDLK_KP_00:
        {
          flag = (this->keyboard.keyKeypad00 == LE_PRESSED);
        } break;
        case SDLK_KP_000:
        {
          flag = (this->keyboard.keyKeypad000 == LE_PRESSED);
        } break;
        case SDLK_KP_1:
        {
          flag = (this->keyboard.keyKeypad1 == LE_PRESSED);
        } break;
        case SDLK_KP_2:
        {
          flag = (this->keyboard.keyKeypad2 == LE_PRESSED);
        } break;
        case SDLK_KP_3:
        {
          flag = (this->keyboard.keyKeypad3 == LE_PRESSED);
        } break;
        case SDLK_KP_4:
        {
          flag = (this->keyboard.keyKeypad4 == LE_PRESSED);
        } break;
        case SDLK_KP_5:
        {
          flag = (this->keyboard.keyKeypad5 == LE_PRESSED);
        } break;
        case SDLK_KP_6:
        {
          flag = (this->keyboard.keyKeypad6 == LE_PRESSED);
        } break;
        case SDLK_KP_7:
        {
          flag = (this->keyboard.keyKeypad7 == LE_PRESSED);
        } break;
        case SDLK_KP_8:
        {
          flag = (this->keyboard.keyKeypad8 == LE_PRESSED);
        } break;
        case SDLK_KP_9:
        {
          flag = (this->keyboard.keyKeypad9 == LE_PRESSED);
        } break;
        case SDLK_KP_A:
        {
          flag = (this->keyboard.keyKeypadA == LE_PRESSED);
        } break;
        case SDLK_KP_AMPERSAND:
        {
          flag = (this->keyboard.keyKeypadAnd == LE_PRESSED);
        } break;
        case SDLK_KP_AT:
        {
          flag = (this->keyboard.keyKeypadAt == LE_PRESSED);
        } break;
        case SDLK_KP_B:
        {
          flag = (this->keyboard.keyKeypadB == LE_PRESSED);
        } break;
        case SDLK_KP_BACKSPACE:
        {
          flag = (this->keyboard.keyKeypadBackspace == LE_PRESSED);
        } break;
        case SDLK_KP_BINARY:
        {
          flag = (this->keyboard.keyKeypadBinary == LE_PRESSED);
        } break;
        case SDLK_KP_C:
        {
          flag = (this->keyboard.keyKeypadC == LE_PRESSED);
        } break;
        case SDLK_KP_CLEAR:
        {
          flag = (this->keyboard.keyKeypadClear == LE_PRESSED);
        } break;
        case SDLK_KP_CLEARENTRY:
        {
          flag = (this->keyboard.keyKeypadClearEntry == LE_PRESSED);
        } break;
        case SDLK_KP_COLON:
        {
          flag = (this->keyboard.keyKeypadColon == LE_PRESSED);
        } break;
        case SDLK_KP_COMMA:
        {
          flag = (this->keyboard.keyKeypadComma == LE_PRESSED);
        } break;
        case SDLK_KP_D:
        {
          flag = (this->keyboard.keyKeypadD == LE_PRESSED);
        } break;
        case SDLK_KP_DBLAMPERSAND:
        {
          flag = (this->keyboard.keyKeypadDoubleAnd == LE_PRESSED);
        } break;
        case SDLK_KP_DBLVERTICALBAR:
        {
          flag = (this->keyboard.keyKeypadDoubleOr == LE_PRESSED);
        } break;
        case SDLK_KP_DECIMAL:
        {
          flag = (this->keyboard.keyKeypadDecimal == LE_PRESSED);
        } break;
        case SDLK_KP_DIVIDE:
        {
          flag = (this->keyboard.keyKeypadDivide == LE_PRESSED);
        } break;
        case SDLK_KP_E:
        {
          flag = (this->keyboard.keyKeypadE == LE_PRESSED);
        } break;
        case SDLK_KP_ENTER:
        {
          flag = (this->keyboard.keyKeypadEnter == LE_PRESSED);
        } break;
        case SDLK_KP_EQUALS:
        {
          flag = (this->keyboard.keyKeypadEquals == LE_PRESSED);
        } break;
        case SDLK_KP_EQUALSAS400:
        {
          flag = (this->keyboard.keyKeypadEqualsAS400 == LE_PRESSED);
        } break;
        case SDLK_KP_EXCLAM:
        {
          flag = (this->keyboard.keyKeypadExclamation == LE_PRESSED);
        } break;
        case SDLK_KP_F:
        {
          flag = (this->keyboard.keyKeypadF == LE_PRESSED);
        } break;
        case SDLK_KP_GREATER:
        {
          flag = (this->keyboard.keyKeypadGreater == LE_PRESSED);
        } break;
        case SDLK_KP_HASH:
        {
          flag = (this->keyboard.keyKeypadHash == LE_PRESSED);
        } break;
        case SDLK_KP_HEXADECIMAL:
        {
          flag = (this->keyboard.keyKeypadHexadecimal == LE_PRESSED);
        } break;
        case SDLK_KP_LEFTBRACE:
        {
          flag = (this->keyboard.keyKeypadLeftBrace == LE_PRESSED);
        } break;
        case SDLK_KP_LEFTPAREN:
        {
          flag = (this->keyboard.keyKeypadLeftParen == LE_PRESSED);
        } break;
        case SDLK_KP_LESS:
        {
          flag = (this->keyboard.keyKeypadLess == LE_PRESSED);
        } break;
        case SDLK_KP_MEMADD:
        {
          flag = (this->keyboard.keyKeypadMemAdd == LE_PRESSED);
        } break;
        case SDLK_KP_MEMCLEAR:
        {
          flag = (this->keyboard.keyKeypadMemClear == LE_PRESSED);
        } break;
        case SDLK_KP_MEMDIVIDE:
        {
          flag = (this->keyboard.keyKeypadMemDivide == LE_PRESSED);
        } break;
        case SDLK_KP_MEMMULTIPLY:
        {
          flag = (this->keyboard.keyKeypadMemMultiply == LE_PRESSED);
        } break;
        case SDLK_KP_MEMRECALL:
        {
          flag = (this->keyboard.keyKeypadMemRecall == LE_PRESSED);
        } break;
        case SDLK_KP_MEMSTORE:
        {
          flag = (this->keyboard.keyKeypadMemStore == LE_PRESSED);
        } break;
        case SDLK_KP_MEMSUBTRACT:
        {
          flag = (this->keyboard.keyKeypadMemSubtract == LE_PRESSED);
        } break;
        case SDLK_KP_MINUS:
        {
          flag = (this->keyboard.keyKeypadMinus == LE_PRESSED);
        } break;
        case SDLK_KP_MULTIPLY:
        {
          flag = (this->keyboard.keyKeypadMultiply == LE_PRESSED);
        } break;
        case SDLK_KP_OCTAL:
        {
          flag = (this->keyboard.keyKeypadOctal == LE_PRESSED);
        } break;
        case SDLK_KP_PERCENT:
        {
          flag = (this->keyboard.keyKeypadPercent == LE_PRESSED);
        } break;
        case SDLK_KP_PERIOD:
        {
          flag = (this->keyboard.keyKeypadPeriod == LE_PRESSED);
        } break;
        case SDLK_KP_PLUS:
        {
          flag = (this->keyboard.keyKeypadPlus == LE_PRESSED);
        } break;
        case SDLK_KP_PLUSMINUS:
        {
          flag = (this->keyboard.keyKeypadPlusMinus == LE_PRESSED);
        } break;
        case SDLK_KP_POWER:
        {
          flag = (this->keyboard.keyKeypadPower == LE_PRESSED);
        } break;
        case SDLK_KP_RIGHTBRACE:
        {
          flag = (this->keyboard.keyKeypadRightBrace == LE_PRESSED);
        } break;
        case SDLK_KP_RIGHTPAREN:
        {
          flag = (this->keyboard.keyKeypadRightParen == LE_PRESSED);
        } break;
        case SDLK_KP_SPACE:
        {
          flag = (this->keyboard.keyKeypadSpace == LE_PRESSED);
        } break;
        case SDLK_KP_TAB:
        {
          flag = (this->keyboard.keyKeypadTab == LE_PRESSED);
        } break;
        case SDLK_KP_VERTICALBAR:
        {
          flag = (this->keyboard.keyKeypadVerticalBar == LE_PRESSED);
        } break;
        case SDLK_KP_XOR:
        {
          flag = (this->keyboard.keyKeypadXOR == LE_PRESSED);
        } break;
        case SDLK_l:
        {
          flag = (this->keyboard.keyL == LE_PRESSED);
        } break;
        case SDLK_LALT:
        {
          flag = (this->keyboard.keyLeftAlt == LE_PRESSED);
        } break;
        case SDLK_LCTRL:
        {
          flag = (this->keyboard.keyLeftCtrl == LE_PRESSED);
        } break;
        case SDLK_LEFT:
        {
          flag = (this->keyboard.keyLeft == LE_PRESSED);
        } break;
        case SDLK_LEFTBRACKET:
        {
          flag = (this->keyboard.keyLeftBracket == LE_PRESSED);
        } break;
        case SDLK_LGUI:
        {
          flag = (this->keyboard.keyLeftGUI == LE_PRESSED);
        } break;
        case SDLK_LSHIFT:
        {
          flag = (this->keyboard.keyLeftShift == LE_PRESSED);
        } break;
        case SDLK_m:
        {
          flag = (this->keyboard.keyM == LE_PRESSED);
        } break;
        case SDLK_MAIL:
        {
          flag = (this->keyboard.keyMail == LE_PRESSED);
        } break;
        case SDLK_MEDIASELECT:
        {
          flag = (this->keyboard.keyMediaSelect == LE_PRESSED);
        } break;
        case SDLK_MENU:
        {
          flag = (this->keyboard.keyMenu == LE_PRESSED);
        } break;
        case SDLK_MINUS:
        {
          flag = (this->keyboard.keyMinus == LE_PRESSED);
        } break;
        case SDLK_MODE:
        {
          flag = (this->keyboard.keyModeSwitch == LE_PRESSED);
        } break;
        case SDLK_MUTE:
        {
          flag = (this->keyboard.keyMute == LE_PRESSED);
        } break;
        case SDLK_n:
        {
          flag = (this->keyboard.keyN == LE_PRESSED);
        } break;
        case SDLK_NUMLOCKCLEAR:
        {
          flag = (this->keyboard.keyNumLock == LE_PRESSED);
        } break;
        case SDLK_o:
        {
          flag = (this->keyboard.keyO == LE_PRESSED);
        } break;
        case SDLK_OPER:
        {
          flag = (this->keyboard.keyOper == LE_PRESSED);
        } break;
        case SDLK_OUT:
        {
          flag = (this->keyboard.keyOut == LE_PRESSED);
        } break;
        case SDLK_p:
        {
          flag = (this->keyboard.keyP == LE_PRESSED);
        } break;
        case SDLK_PAGEDOWN:
        {
          flag = (this->keyboard.keyPageDown == LE_PRESSED);
        } break;
        case SDLK_PAGEUP:
        {
          flag = (this->keyboard.keyPageUp == LE_PRESSED);
        } break;
        case SDLK_PASTE:
        {
          flag = (this->keyboard.keyPaste == LE_PRESSED);
        } break;
        case SDLK_PAUSE:
        {
          flag = (this->keyboard.keyPause == LE_PRESSED);
        } break;
        case SDLK_PERIOD:
        {
          flag = (this->keyboard.keyPeriod == LE_PRESSED);
        } break;
        case SDLK_POWER:
        {
          flag = (this->keyboard.keyPower == LE_PRESSED);
        } break;
        case SDLK_PRINTSCREEN:
        {
          flag = (this->keyboard.keyPrintScreen == LE_PRESSED);
        } break;
        case SDLK_PRIOR:
        {
          flag = (this->keyboard.keyPrior == LE_PRESSED);
        } break;
        case SDLK_q:
        {
          flag = (this->keyboard.keyQ == LE_PRESSED);
        } break;
        case SDLK_r:
        {
          flag = (this->keyboard.keyR == LE_PRESSED);
        } break;
        case SDLK_RALT:
        {
          flag = (this->keyboard.keyRightAlt == LE_PRESSED);
        } break;
        case SDLK_RCTRL:
        {
          flag = (this->keyboard.keyRightCtrl == LE_PRESSED);
        } break;
        case SDLK_RETURN:
        {
          flag = (this->keyboard.keyReturn == LE_PRESSED);
        } break;
        case SDLK_RETURN2:
        {
          flag = (this->keyboard.keyReturn2 == LE_PRESSED);
        } break;
        case SDLK_RGUI:
        {
          flag = (this->keyboard.keyRightGUI == LE_PRESSED);
        } break;
        case SDLK_RIGHT:
        {
          flag = (this->keyboard.keyRight == LE_PRESSED);
        } break;
        case SDLK_RIGHTBRACKET:
        {
          flag = (this->keyboard.keyRightBracket == LE_PRESSED);
        } break;
        case SDLK_RSHIFT:
        {
          flag = (this->keyboard.keyRightShift == LE_PRESSED);
        } break;
        case SDLK_s:
        {
          flag = (this->keyboard.keyS == LE_PRESSED);
        } break;
        case SDLK_SCROLLLOCK:
        {
          flag = (this->keyboard.keyScrollLock == LE_PRESSED);
        } break;
        case SDLK_SELECT:
        {
          flag = (this->keyboard.keySelect == LE_PRESSED);
        } break;
        case SDLK_SEMICOLON:
        {
          flag = (this->keyboard.keySemicolon == LE_PRESSED);
        } break;
        case SDLK_SEPARATOR:
        {
          flag = (this->keyboard.keySeparator == LE_PRESSED);
        } break;
        case SDLK_SLASH:
        {
          flag = (this->keyboard.keySlash == LE_PRESSED);
        } break;
        case SDLK_SLEEP:
        {
          flag = (this->keyboard.keySleep == LE_PRESSED);
        } break;
        case SDLK_SPACE:
        {
          flag = (this->keyboard.keySpace == LE_PRESSED);
        } break;
        case SDLK_STOP:
        {
          flag = (this->keyboard.keyStop == LE_PRESSED);
        } break;
        case SDLK_SYSREQ:
        {
          flag = (this->keyboard.keySysReq == LE_PRESSED);
        } break;
        case SDLK_t:
        {
          flag = (this->keyboard.keyT == LE_PRESSED);
        } break;
        case SDLK_TAB:
        {
          flag = (this->keyboard.keyTab == LE_PRESSED);
        } break;
        case SDLK_THOUSANDSSEPARATOR:
        {
          flag = (this->keyboard.keyThousandsSeparator == LE_PRESSED);
        } break;
        case SDLK_u:
        {
          flag = (this->keyboard.keyU == LE_PRESSED);
        } break;
        case SDLK_UNDO:
        {
          flag = (this->keyboard.keyUndo == LE_PRESSED);
        } break;
        case SDLK_UP:
        {
          flag = (this->keyboard.keyUp == LE_PRESSED);
        } break;
        case SDLK_v:
        {
          flag = (this->keyboard.keyV == LE_PRESSED);
        } break;
        case SDLK_VOLUMEDOWN:
        {
          flag = (this->keyboard.keyVolumeDown == LE_PRESSED);
        } break;
        case SDLK_VOLUMEUP:
        {
          flag = (this->keyboard.keyVolumeUp == LE_PRESSED);
        } break;
        case SDLK_w:
        {
          flag = (this->keyboard.keyW == LE_PRESSED);
        } break;
        case SDLK_WWW:
        {
          flag = (this->keyboard.keyWWW == LE_PRESSED);
        } break;
        case SDLK_x:
        {
          flag = (this->keyboard.keyX == LE_PRESSED);
        } break;
        case SDLK_y:
        {
          flag = (this->keyboard.keyY == LE_PRESSED);
        } break;
        case SDLK_z:
        {
          flag = (this->keyboard.keyZ == LE_PRESSED);
        } break;
      };
    } break;

    //////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////
    // key up
    //////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////

    case SDL_KEYUP:
    {
      switch(key)
      {
        case SDLK_0:
        {
          flag = (this->keyboard.key0 == LE_RELEASED);
        } break;
        case SDLK_1:
        {
          flag = (this->keyboard.key1 == LE_RELEASED);
        } break;
        case SDLK_2:
        {
          flag = (this->keyboard.key2 == LE_RELEASED);
        } break;
        case SDLK_3:
        {
          flag = (this->keyboard.key3 == LE_RELEASED);
        } break;
        case SDLK_4:
        {
          flag = (this->keyboard.key4 == LE_RELEASED);
        } break;
        case SDLK_5:
        {
          flag = (this->keyboard.key5 == LE_RELEASED);
        } break;
        case SDLK_6:
        {
          flag = (this->keyboard.key6 == LE_RELEASED);
        } break;
        case SDLK_7:
        {
          flag = (this->keyboard.key7 == LE_RELEASED);
        } break;
        case SDLK_8:
        {
          flag = (this->keyboard.key8 == LE_RELEASED);
        } break;
        case SDLK_9:
        {
          flag = (this->keyboard.key9 == LE_RELEASED);
        } break;
        case SDLK_a:
        {
          flag = (this->keyboard.keyA == LE_RELEASED);
        } break;
        case SDLK_AC_BACK:
        {
          flag = (this->keyboard.keyACBack == LE_RELEASED);
        } break;
        case SDLK_AC_BOOKMARKS:
        {
          flag = (this->keyboard.keyACBookmarks == LE_RELEASED);
        } break;
        case SDLK_AC_FORWARD:
        {
          flag = (this->keyboard.keyACForward == LE_RELEASED);
        } break;
        case SDLK_AC_HOME:
        {
          flag = (this->keyboard.keyACHome == LE_RELEASED);
        } break;
        case SDLK_AC_REFRESH:
        {
          flag = (this->keyboard.keyACRefresh == LE_RELEASED);
        } break;
        case SDLK_AC_SEARCH:
        {
          flag = (this->keyboard.keyACSearch == LE_RELEASED);
        } break;
        case SDLK_AC_STOP:
        {
          flag = (this->keyboard.keyACStop == LE_RELEASED);
        } break;
        case SDLK_AGAIN:
        {
          flag = (this->keyboard.keyAgain == LE_RELEASED);
        } break;
        case SDLK_ALTERASE:
        {
          flag = (this->keyboard.keyAltErase == LE_RELEASED);
        } break;
        case SDLK_QUOTE:
        {
          flag = (this->keyboard.keyApostrophe == LE_RELEASED);
        } break;
        case SDLK_APPLICATION:
        {
          flag = (this->keyboard.keyApplication == LE_RELEASED);
        } break;
        case SDLK_AUDIOMUTE:
        {
          flag = (this->keyboard.keyAudioMute == LE_RELEASED);
        } break;
        case SDLK_AUDIONEXT:
        {
          flag = (this->keyboard.keyAudioNext == LE_RELEASED);
        } break;
        case SDLK_AUDIOPLAY:
        {
          flag = (this->keyboard.keyAudioPlay == LE_RELEASED);
        } break;
        case SDLK_AUDIOPREV:
        {
          flag = (this->keyboard.keyAudioPrev == LE_RELEASED);
        } break;
        case SDLK_AUDIOSTOP:
        {
          flag = (this->keyboard.keyAudioStop == LE_RELEASED);
        } break;
        case SDLK_b:
        {
          flag = (this->keyboard.keyB == LE_RELEASED);
        } break;
        case SDLK_BACKSLASH:
        {
          flag = (this->keyboard.keyBackslash == LE_RELEASED);
        } break;
        case SDLK_BACKSPACE:
        {
          flag = (this->keyboard.keyBackspace == LE_RELEASED);
        } break;
        case SDLK_BRIGHTNESSDOWN:
        {
          flag = (this->keyboard.keyBrightnessDown == LE_RELEASED);
        } break;
        case SDLK_BRIGHTNESSUP:
        {
          flag = (this->keyboard.keyBrightnessUp == LE_RELEASED);
        } break;
        case SDLK_c:
        {
          flag = (this->keyboard.keyC == LE_RELEASED);
        } break;
        case SDLK_CALCULATOR:
        {
          flag = (this->keyboard.keyCalculator == LE_RELEASED);
        } break;
        case SDLK_CANCEL:
        {
          flag = (this->keyboard.keyCancel == LE_RELEASED);
        } break;
        case SDLK_CAPSLOCK:
        {
          flag = (this->keyboard.keyCapsLock == LE_RELEASED);
        } break;
        case SDLK_CLEAR:
        {
          flag = (this->keyboard.keyClear == LE_RELEASED);
        } break;
        case SDLK_CLEARAGAIN:
        {
          flag = (this->keyboard.keyClearAgain == LE_RELEASED);
        } break;
        case SDLK_COMMA:
        {
          flag = (this->keyboard.keyComma == LE_RELEASED);
        } break;
        case SDLK_COMPUTER:
        {
          flag = (this->keyboard.keyComputer == LE_RELEASED);
        } break;
        case SDLK_COPY:
        {
          flag = (this->keyboard.keyCopy == LE_RELEASED);
        } break;
        case SDLK_CRSEL:
        {
          flag = (this->keyboard.keyCrSel == LE_RELEASED);
        } break;
        case SDLK_CURRENCYSUBUNIT:
        {
          flag = (this->keyboard.keyCurrencySubUnit == LE_RELEASED);
        } break;
        case SDLK_CURRENCYUNIT:
        {
          flag = (this->keyboard.keyCurrencyUnit == LE_RELEASED);
        } break;
        case SDLK_CUT:
        {
          flag = (this->keyboard.keyCut == LE_RELEASED);
        } break;
        case SDLK_d:
        {
          flag = (this->keyboard.keyD == LE_RELEASED);
        } break;
        case SDLK_DECIMALSEPARATOR:
        {
          flag = (this->keyboard.keyDecimalSeparator == LE_RELEASED);
        } break;
        case SDLK_DELETE:
        {
          flag = (this->keyboard.keyDelete == LE_RELEASED);
        } break;
        case SDLK_DISPLAYSWITCH:
        {
          flag = (this->keyboard.keyDisplaySwitch == LE_RELEASED);
        } break;
        case SDLK_DOWN:
        {
          flag = (this->keyboard.keyDown == LE_RELEASED);
        } break;
        case SDLK_e:
        {
          flag = (this->keyboard.keyE == LE_RELEASED);
        } break;
        case SDLK_EJECT:
        {
          flag = (this->keyboard.keyEject == LE_RELEASED);
        } break;
        case SDLK_END:
        {
          flag = (this->keyboard.keyEnd == LE_RELEASED);
        } break;
        case SDLK_EQUALS:
        {
          flag = (this->keyboard.keyEquals == LE_RELEASED);
        } break;
        case SDLK_ESCAPE:
        {
          flag = (this->keyboard.keyEscape == LE_RELEASED);
        } break;
        case SDLK_EXECUTE:
        {
          flag = (this->keyboard.keyExecute == LE_RELEASED);
        } break;
        case SDLK_EXSEL:
        {
          flag = (this->keyboard.keyExSel == LE_RELEASED);
        } break;
        case SDLK_f:
        {
          flag = (this->keyboard.keyF == LE_RELEASED);
        } break;
        case SDLK_F1:
        {
          flag = (this->keyboard.keyF1 == LE_RELEASED);
        } break;
        case SDLK_F10:
        {
          flag = (this->keyboard.keyF10 == LE_RELEASED);
        } break;
        case SDLK_F11:
        {
          flag = (this->keyboard.keyF11 == LE_RELEASED);
        } break;
        case SDLK_F12:
        {
          flag = (this->keyboard.keyF12 == LE_RELEASED);
        } break;
        case SDLK_F13:
        {
          flag = (this->keyboard.keyF13 == LE_RELEASED);
        } break;
        case SDLK_F14:
        {
          flag = (this->keyboard.keyF14 == LE_RELEASED);
        } break;
        case SDLK_F15:
        {
          flag = (this->keyboard.keyF15 == LE_RELEASED);
        } break;
        case SDLK_F16:
        {
          flag = (this->keyboard.keyF16 == LE_RELEASED);
        } break;
        case SDLK_F17:
        {
          flag = (this->keyboard.keyF17 == LE_RELEASED);
        } break;
        case SDLK_F18:
        {
          flag = (this->keyboard.keyF18 == LE_RELEASED);
        } break;
        case SDLK_F19:
        {
          flag = (this->keyboard.keyF19 == LE_RELEASED);
        } break;
        case SDLK_F2:
        {
          flag = (this->keyboard.keyF2 == LE_RELEASED);
        } break;
        case SDLK_F20:
        {
          flag = (this->keyboard.keyF20 == LE_RELEASED);
        } break;
        case SDLK_F21:
        {
          flag = (this->keyboard.keyF21 == LE_RELEASED);
        } break;
        case SDLK_F22:
        {
          flag = (this->keyboard.keyF22 == LE_RELEASED);
        } break;
        case SDLK_F23:
        {
          flag = (this->keyboard.keyF23 == LE_RELEASED);
        } break;
        case SDLK_F24:
        {
          flag = (this->keyboard.keyF24 == LE_RELEASED);
        } break;
        case SDLK_F3:
        {
          flag = (this->keyboard.keyF3 == LE_RELEASED);
        } break;
        case SDLK_F4:
        {
          flag = (this->keyboard.keyF4 == LE_RELEASED);
        } break;
        case SDLK_F5:
        {
          flag = (this->keyboard.keyF5 == LE_RELEASED);
        } break;
        case SDLK_F6:
        {
          flag = (this->keyboard.keyF6 == LE_RELEASED);
        } break;
        case SDLK_F7:
        {
          flag = (this->keyboard.keyF7 == LE_RELEASED);
        } break;
        case SDLK_F8:
        {
          flag = (this->keyboard.keyF8 == LE_RELEASED);
        } break;
        case SDLK_F9:
        {
          flag = (this->keyboard.keyF9 == LE_RELEASED);
        } break;
        case SDLK_FIND:
        {
          flag = (this->keyboard.keyFind == LE_RELEASED);
        } break;
        case SDLK_g:
        {
          flag = (this->keyboard.keyG == LE_RELEASED);
        } break;
        case SDLK_BACKQUOTE:
        {
          flag = (this->keyboard.keyBackquote == LE_RELEASED);
        } break;
        case SDLK_h:
        {
          flag = (this->keyboard.keyH == LE_RELEASED);
        } break;
        case SDLK_HELP:
        {
          flag = (this->keyboard.keyHelp == LE_RELEASED);
        } break;
        case SDLK_HOME:
        {
          flag = (this->keyboard.keyHome == LE_RELEASED);
        } break;
        case SDLK_i:
        {
          flag = (this->keyboard.keyI == LE_RELEASED);
        } break;
        case SDLK_INSERT:
        {
          flag = (this->keyboard.keyInsert == LE_RELEASED);
        } break;
        case SDLK_j:
        {
          flag = (this->keyboard.keyJ == LE_RELEASED);
        } break;
        case SDLK_k:
        {
          flag = (this->keyboard.keyK == LE_RELEASED);
        } break;
        case SDLK_KBDILLUMDOWN:
        {
          flag = (this->keyboard.keyKBDillumDown == LE_RELEASED);
        } break;
        case SDLK_KBDILLUMTOGGLE:
        {
          flag = (this->keyboard.keyKBDillumToggle == LE_RELEASED);
        } break;
        case SDLK_KBDILLUMUP:
        {
          flag = (this->keyboard.keyKBDillumUp == LE_RELEASED);
        } break;
        case SDLK_KP_0:
        {
          flag = (this->keyboard.keyKeypad0 == LE_RELEASED);
        } break;
        case SDLK_KP_00:
        {
          flag = (this->keyboard.keyKeypad00 == LE_RELEASED);
        } break;
        case SDLK_KP_000:
        {
          flag = (this->keyboard.keyKeypad000 == LE_RELEASED);
        } break;
        case SDLK_KP_1:
        {
          flag = (this->keyboard.keyKeypad1 == LE_RELEASED);
        } break;
        case SDLK_KP_2:
        {
          flag = (this->keyboard.keyKeypad2 == LE_RELEASED);
        } break;
        case SDLK_KP_3:
        {
          flag = (this->keyboard.keyKeypad3 == LE_RELEASED);
        } break;
        case SDLK_KP_4:
        {
          flag = (this->keyboard.keyKeypad4 == LE_RELEASED);
        } break;
        case SDLK_KP_5:
        {
          flag = (this->keyboard.keyKeypad5 == LE_RELEASED);
        } break;
        case SDLK_KP_6:
        {
          flag = (this->keyboard.keyKeypad6 == LE_RELEASED);
        } break;
        case SDLK_KP_7:
        {
          flag = (this->keyboard.keyKeypad7 == LE_RELEASED);
        } break;
        case SDLK_KP_8:
        {
          flag = (this->keyboard.keyKeypad8 == LE_RELEASED);
        } break;
        case SDLK_KP_9:
        {
          flag = (this->keyboard.keyKeypad9 == LE_RELEASED);
        } break;
        case SDLK_KP_A:
        {
          flag = (this->keyboard.keyKeypadA == LE_RELEASED);
        } break;
        case SDLK_KP_AMPERSAND:
        {
          flag = (this->keyboard.keyKeypadAnd == LE_RELEASED);
        } break;
        case SDLK_KP_AT:
        {
          flag = (this->keyboard.keyKeypadAt == LE_RELEASED);
        } break;
        case SDLK_KP_B:
        {
          flag = (this->keyboard.keyKeypadB == LE_RELEASED);
        } break;
        case SDLK_KP_BACKSPACE:
        {
          flag = (this->keyboard.keyKeypadBackspace == LE_RELEASED);
        } break;
        case SDLK_KP_BINARY:
        {
          flag = (this->keyboard.keyKeypadBinary == LE_RELEASED);
        } break;
        case SDLK_KP_C:
        {
          flag = (this->keyboard.keyKeypadC == LE_RELEASED);
        } break;
        case SDLK_KP_CLEAR:
        {
          flag = (this->keyboard.keyKeypadClear == LE_RELEASED);
        } break;
        case SDLK_KP_CLEARENTRY:
        {
          flag = (this->keyboard.keyKeypadClearEntry == LE_RELEASED);
        } break;
        case SDLK_KP_COLON:
        {
          flag = (this->keyboard.keyKeypadColon == LE_RELEASED);
        } break;
        case SDLK_KP_COMMA:
        {
          flag = (this->keyboard.keyKeypadComma == LE_RELEASED);
        } break;
        case SDLK_KP_D:
        {
          flag = (this->keyboard.keyKeypadD == LE_RELEASED);
        } break;
        case SDLK_KP_DBLAMPERSAND:
        {
          flag = (this->keyboard.keyKeypadDoubleAnd == LE_RELEASED);
        } break;
        case SDLK_KP_DBLVERTICALBAR:
        {
          flag = (this->keyboard.keyKeypadDoubleOr == LE_RELEASED);
        } break;
        case SDLK_KP_DECIMAL:
        {
          flag = (this->keyboard.keyKeypadDecimal == LE_RELEASED);
        } break;
        case SDLK_KP_DIVIDE:
        {
          flag = (this->keyboard.keyKeypadDivide == LE_RELEASED);
        } break;
        case SDLK_KP_E:
        {
          flag = (this->keyboard.keyKeypadE == LE_RELEASED);
        } break;
        case SDLK_KP_ENTER:
        {
          flag = (this->keyboard.keyKeypadEnter == LE_RELEASED);
        } break;
        case SDLK_KP_EQUALS:
        {
          flag = (this->keyboard.keyKeypadEquals == LE_RELEASED);
        } break;
        case SDLK_KP_EQUALSAS400:
        {
          flag = (this->keyboard.keyKeypadEqualsAS400 == LE_RELEASED);
        } break;
        case SDLK_KP_EXCLAM:
        {
          flag = (this->keyboard.keyKeypadExclamation == LE_RELEASED);
        } break;
        case SDLK_KP_F:
        {
          flag = (this->keyboard.keyKeypadF == LE_RELEASED);
        } break;
        case SDLK_KP_GREATER:
        {
          flag = (this->keyboard.keyKeypadGreater == LE_RELEASED);
        } break;
        case SDLK_KP_HASH:
        {
          flag = (this->keyboard.keyKeypadHash == LE_RELEASED);
        } break;
        case SDLK_KP_HEXADECIMAL:
        {
          flag = (this->keyboard.keyKeypadHexadecimal == LE_RELEASED);
        } break;
        case SDLK_KP_LEFTBRACE:
        {
          flag = (this->keyboard.keyKeypadLeftBrace == LE_RELEASED);
        } break;
        case SDLK_KP_LEFTPAREN:
        {
          flag = (this->keyboard.keyKeypadLeftParen == LE_RELEASED);
        } break;
        case SDLK_KP_LESS:
        {
          flag = (this->keyboard.keyKeypadLess == LE_RELEASED);
        } break;
        case SDLK_KP_MEMADD:
        {
          flag = (this->keyboard.keyKeypadMemAdd == LE_RELEASED);
        } break;
        case SDLK_KP_MEMCLEAR:
        {
          flag = (this->keyboard.keyKeypadMemClear == LE_RELEASED);
        } break;
        case SDLK_KP_MEMDIVIDE:
        {
          flag = (this->keyboard.keyKeypadMemDivide == LE_RELEASED);
        } break;
        case SDLK_KP_MEMMULTIPLY:
        {
          flag = (this->keyboard.keyKeypadMemMultiply == LE_RELEASED);
        } break;
        case SDLK_KP_MEMRECALL:
        {
          flag = (this->keyboard.keyKeypadMemRecall == LE_RELEASED);
        } break;
        case SDLK_KP_MEMSTORE:
        {
          flag = (this->keyboard.keyKeypadMemStore == LE_RELEASED);
        } break;
        case SDLK_KP_MEMSUBTRACT:
        {
          flag = (this->keyboard.keyKeypadMemSubtract == LE_RELEASED);
        } break;
        case SDLK_KP_MINUS:
        {
          flag = (this->keyboard.keyKeypadMinus == LE_RELEASED);
        } break;
        case SDLK_KP_MULTIPLY:
        {
          flag = (this->keyboard.keyKeypadMultiply == LE_RELEASED);
        } break;
        case SDLK_KP_OCTAL:
        {
          flag = (this->keyboard.keyKeypadOctal == LE_RELEASED);
        } break;
        case SDLK_KP_PERCENT:
        {
          flag = (this->keyboard.keyKeypadPercent == LE_RELEASED);
        } break;
        case SDLK_KP_PERIOD:
        {
          flag = (this->keyboard.keyKeypadPeriod == LE_RELEASED);
        } break;
        case SDLK_KP_PLUS:
        {
          flag = (this->keyboard.keyKeypadPlus == LE_RELEASED);
        } break;
        case SDLK_KP_PLUSMINUS:
        {
          flag = (this->keyboard.keyKeypadPlusMinus == LE_RELEASED);
        } break;
        case SDLK_KP_POWER:
        {
          flag = (this->keyboard.keyKeypadPower == LE_RELEASED);
        } break;
        case SDLK_KP_RIGHTBRACE:
        {
          flag = (this->keyboard.keyKeypadRightBrace == LE_RELEASED);
        } break;
        case SDLK_KP_RIGHTPAREN:
        {
          flag = (this->keyboard.keyKeypadRightParen == LE_RELEASED);
        } break;
        case SDLK_KP_SPACE:
        {
          flag = (this->keyboard.keyKeypadSpace == LE_RELEASED);
        } break;
        case SDLK_KP_TAB:
        {
          flag = (this->keyboard.keyKeypadTab == LE_RELEASED);
        } break;
        case SDLK_KP_VERTICALBAR:
        {
          flag = (this->keyboard.keyKeypadVerticalBar == LE_RELEASED);
        } break;
        case SDLK_KP_XOR:
        {
          flag = (this->keyboard.keyKeypadXOR == LE_RELEASED);
        } break;
        case SDLK_l:
        {
          flag = (this->keyboard.keyL == LE_RELEASED);
        } break;
        case SDLK_LALT:
        {
          flag = (this->keyboard.keyLeftAlt == LE_RELEASED);
        } break;
        case SDLK_LCTRL:
        {
          flag = (this->keyboard.keyLeftCtrl == LE_RELEASED);
        } break;
        case SDLK_LEFT:
        {
          flag = (this->keyboard.keyLeft == LE_RELEASED);
        } break;
        case SDLK_LEFTBRACKET:
        {
          flag = (this->keyboard.keyLeftBracket == LE_RELEASED);
        } break;
        case SDLK_LGUI:
        {
          flag = (this->keyboard.keyLeftGUI == LE_RELEASED);
        } break;
        case SDLK_LSHIFT:
        {
          flag = (this->keyboard.keyLeftShift == LE_RELEASED);
        } break;
        case SDLK_m:
        {
          flag = (this->keyboard.keyM == LE_RELEASED);
        } break;
        case SDLK_MAIL:
        {
          flag = (this->keyboard.keyMail == LE_RELEASED);
        } break;
        case SDLK_MEDIASELECT:
        {
          flag = (this->keyboard.keyMediaSelect == LE_RELEASED);
        } break;
        case SDLK_MENU:
        {
          flag = (this->keyboard.keyMenu == LE_RELEASED);
        } break;
        case SDLK_MINUS:
        {
          flag = (this->keyboard.keyMinus == LE_RELEASED);
        } break;
        case SDLK_MODE:
        {
          flag = (this->keyboard.keyModeSwitch == LE_RELEASED);
        } break;
        case SDLK_MUTE:
        {
          flag = (this->keyboard.keyMute == LE_RELEASED);
        } break;
        case SDLK_n:
        {
          flag = (this->keyboard.keyN == LE_RELEASED);
        } break;
        case SDLK_NUMLOCKCLEAR:
        {
          flag = (this->keyboard.keyNumLock == LE_RELEASED);
        } break;
        case SDLK_o:
        {
          flag = (this->keyboard.keyO == LE_RELEASED);
        } break;
        case SDLK_OPER:
        {
          flag = (this->keyboard.keyOper == LE_RELEASED);
        } break;
        case SDLK_OUT:
        {
          flag = (this->keyboard.keyOut == LE_RELEASED);
        } break;
        case SDLK_p:
        {
          flag = (this->keyboard.keyP == LE_RELEASED);
        } break;
        case SDLK_PAGEDOWN:
        {
          flag = (this->keyboard.keyPageDown == LE_RELEASED);
        } break;
        case SDLK_PAGEUP:
        {
          flag = (this->keyboard.keyPageUp == LE_RELEASED);
        } break;
        case SDLK_PASTE:
        {
          flag = (this->keyboard.keyPaste == LE_RELEASED);
        } break;
        case SDLK_PAUSE:
        {
          flag = (this->keyboard.keyPause == LE_RELEASED);
        } break;
        case SDLK_PERIOD:
        {
          flag = (this->keyboard.keyPeriod == LE_RELEASED);
        } break;
        case SDLK_POWER:
        {
          flag = (this->keyboard.keyPower == LE_RELEASED);
        } break;
        case SDLK_PRINTSCREEN:
        {
          flag = (this->keyboard.keyPrintScreen == LE_RELEASED);
        } break;
        case SDLK_PRIOR:
        {
          flag = (this->keyboard.keyPrior == LE_RELEASED);
        } break;
        case SDLK_q:
        {
          flag = (this->keyboard.keyQ == LE_RELEASED);
        } break;
        case SDLK_r:
        {
          flag = (this->keyboard.keyR == LE_RELEASED);
        } break;
        case SDLK_RALT:
        {
          flag = (this->keyboard.keyRightAlt == LE_RELEASED);
        } break;
        case SDLK_RCTRL:
        {
          flag = (this->keyboard.keyRightCtrl == LE_RELEASED);
        } break;
        case SDLK_RETURN:
        {
          flag = (this->keyboard.keyReturn == LE_RELEASED);
        } break;
        case SDLK_RETURN2:
        {
          flag = (this->keyboard.keyReturn2 == LE_RELEASED);
        } break;
        case SDLK_RGUI:
        {
          flag = (this->keyboard.keyRightGUI == LE_RELEASED);
        } break;
        case SDLK_RIGHT:
        {
          flag = (this->keyboard.keyRight == LE_RELEASED);
        } break;
        case SDLK_RIGHTBRACKET:
        {
          flag = (this->keyboard.keyRightBracket == LE_RELEASED);
        } break;
        case SDLK_RSHIFT:
        {
          flag = (this->keyboard.keyRightShift == LE_RELEASED);
        } break;
        case SDLK_s:
        {
          flag = (this->keyboard.keyS == LE_RELEASED);
        } break;
        case SDLK_SCROLLLOCK:
        {
          flag = (this->keyboard.keyScrollLock == LE_RELEASED);
        } break;
        case SDLK_SELECT:
        {
          flag = (this->keyboard.keySelect == LE_RELEASED);
        } break;
        case SDLK_SEMICOLON:
        {
          flag = (this->keyboard.keySemicolon == LE_RELEASED);
        } break;
        case SDLK_SEPARATOR:
        {
          flag = (this->keyboard.keySeparator == LE_RELEASED);
        } break;
        case SDLK_SLASH:
        {
          flag = (this->keyboard.keySlash == LE_RELEASED);
        } break;
        case SDLK_SLEEP:
        {
          flag = (this->keyboard.keySleep == LE_RELEASED);
        } break;
        case SDLK_SPACE:
        {
          flag = (this->keyboard.keySpace == LE_RELEASED);
        } break;
        case SDLK_STOP:
        {
          flag = (this->keyboard.keyStop == LE_RELEASED);
        } break;
        case SDLK_SYSREQ:
        {
          flag = (this->keyboard.keySysReq == LE_RELEASED);
        } break;
        case SDLK_t:
        {
          flag = (this->keyboard.keyT == LE_RELEASED);
        } break;
        case SDLK_TAB:
        {
          flag = (this->keyboard.keyTab == LE_RELEASED);
        } break;
        case SDLK_THOUSANDSSEPARATOR:
        {
          flag = (this->keyboard.keyThousandsSeparator == LE_RELEASED);
        } break;
        case SDLK_u:
        {
          flag = (this->keyboard.keyU == LE_RELEASED);
        } break;
        case SDLK_UNDO:
        {
          flag = (this->keyboard.keyUndo == LE_RELEASED);
        } break;
        case SDLK_UP:
        {
          flag = (this->keyboard.keyUp == LE_RELEASED);
        } break;
        case SDLK_v:
        {
          flag = (this->keyboard.keyV == LE_RELEASED);
        } break;
        case SDLK_VOLUMEDOWN:
        {
          flag = (this->keyboard.keyVolumeDown == LE_RELEASED);
        } break;
        case SDLK_VOLUMEUP:
        {
          flag = (this->keyboard.keyVolumeUp == LE_RELEASED);
        } break;
        case SDLK_w:
        {
          flag = (this->keyboard.keyW == LE_RELEASED);
        } break;
        case SDLK_WWW:
        {
          flag = (this->keyboard.keyWWW == LE_RELEASED);
        } break;
        case SDLK_x:
        {
          flag = (this->keyboard.keyX == LE_RELEASED);
        } break;
        case SDLK_y:
        {
          flag = (this->keyboard.keyY == LE_RELEASED);
        } break;
        case SDLK_z:
        {
          flag = (this->keyboard.keyZ == LE_RELEASED);
        } break;
      };
    } break;
  };

  return flag;
}

void LEMoon::setBackgroundColor(uint8_t r, uint8_t g, uint8_t b)
{
  this->backgroundColor.r = r;
  this->backgroundColor.g = g;
  this->backgroundColor.b = b;
}

int LEMoon::drawFrame()
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = nullptr;

  // background color

  if(SDL_SetRenderDrawColor(this->pRenderer, this->backgroundColor.r, this->backgroundColor.g, this->backgroundColor.b, this->backgroundColor.a))
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_SDL_DRAW_COLOR, "LEMoon::drawFrame()\n\n");
    #endif

    result = LE_SDL_DRAW_COLOR;
  }

  // clear renderer

  if(!result)
  {
    if(SDL_RenderClear(this->pRenderer))
    {
      #ifdef LE_DEBUG
        this->printErrorDialog(LE_SDL_CLEAR_RENDERER, "LEMoon::drawFrame()\n\n");
      #endif

      result = LE_SDL_CLEAR_RENDERER;
    }
  }

  // draw Models, Texts, Points and Lines, depending on zindex 

  if(!result)
    {result = this->drawWithZindex();}

  // render present state

  if(!result)
    {SDL_RenderPresent(this->pRenderer);}

  return result;
}

void LEMoon::messageBox(const char * pTitle, const char * pText)
{
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, pTitle, pText, nullptr);
}

int LEMoon::endFrame()
{
  int result = LE_NO_ERROR;

  this->timestep = (SDL_GetTicks() - this->timestamp) * 0.001f;
  this->freeKeyboardKeys();
  this->freeMouse();

  result = this->merge();

  return result;
}

int LEMoon::showCursor(bool flag)
{
  int result = LE_NO_ERROR;

  if(flag)
  {
    if(SDL_ShowCursor(SDL_ENABLE) < 0)
    {
      #ifdef LE_DEBUG
        this->printErrorDialog(LE_SDL_SHOW_CURSOR, "LEMoon::showCursor()\n\n");
      #endif

      result = LE_SDL_SHOW_CURSOR;
    }
  }
  else
  {
    if(SDL_ShowCursor(SDL_DISABLE) < 0)
    {
      #ifdef LE_DEBUG
        this->printErrorDialog(LE_SDL_SHOW_CURSOR, "LEMoon::showCursor()\n\n");
      #endif

      result = LE_SDL_SHOW_CURSOR;
    }
  }

  return result;
}

int LEMoon::getScreenWidth()
{
  return this->displayMode.w;
}

int LEMoon::getScreenHeight()
{
  return this->displayMode.h;
}

uint32_t LEMoon::getTimestamp()
{
  return this->timestamp;
}

SDL_Point LEMoon::mouseGetPosition()
{
  SDL_Point posMouse;
  posMouse.x = this->mouse.mouseX;
  posMouse.y = this->mouse.mouseY;

  return posMouse;
}

double LEMoon::percentToPixelX(double percent)
{
  return this->displayMode.w * (percent * 0.01f);
}

double LEMoon::percentToPixelY(double percent)
{
  return this->displayMode.h * (percent * 0.01f);
}

double LEMoon::pixelToPercentX(double pixel)
{
  return (pixel / this->displayMode.w) * 100.0f;
}

double LEMoon::pixelToPercentY(double pixel)
{
  return (pixel / this->displayMode.h) * 100.0f;
}

double LEMoon::getTimestep()
{
  return this->timestep;
}

Color LEMoon::getBackgroundColor()
{
  return this->backgroundColor;
}

double LEMoon::convertResWidth(double pixel, double originalWidth)
{
  return (pixel / originalWidth) * this->displayMode.w;
}

double LEMoon::convertResHeight(double pixel, double originalHeight)
{
  return (pixel / originalHeight) * this->displayMode.h;
}

bool LEMoon::recentFPSAvailable()
{
  bool available = this->fps.recentFPS;

  if(this->fps.recentFPS)
    {this->fps.recentFPS = LE_FALSE;}

  return available;
}

uint16_t LEMoon::getFPS()
{
  return this->fps.lastFPS;
}

void LEMoon::delay(uint32_t waitTime)
{
  SDL_Delay(waitTime);
}

char * LEMoon::getPrefPath()
{
  return this->prefPath;
}

#ifdef LE_LINUX
void LEMoon::mkpath(const char * dir, mode_t mode)
{
  char tmp[256];
  char * p = nullptr;
  size_t len;

  snprintf(tmp, sizeof(tmp),"%s",dir);
  len = strlen(tmp);

  if(tmp[len - 1] == '/')
    {tmp[len - 1] = 0;}
        
  for(p = tmp + 1 ; *p ; p++)
  {
    if(*p == '/') 
    {
      *p = 0;
      mkdir(tmp, mode);
      *p = '/';
    }
  }

  mkdir(tmp, mode);
}
#endif