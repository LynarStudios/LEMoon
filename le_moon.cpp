/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Visual Studio 2015 Community, g++ Compiler
  date:               18.05.2017
  updated:            07.03.2018
*/

#include "le_moon.h"

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
}

void LEMoon::memoryClearFonts()
{
  LEFont * pCurrent = nullptr;
  LEFont * pNext = nullptr;

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
}

void LEMoon::memoryClearTexts()
{
  LEText * pCurrent = nullptr;
  LEText * pNext = nullptr;
  LinkedVec2 * pCurrentDirection = nullptr;
  LinkedVec2 * pNextDirection = nullptr;
  LELetter * pCurrentLetter = nullptr;
  LELetter * pNextLetter = nullptr;

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
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// private window
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void LEMoon::handleWindow()
{
  if(this->event.type = SDL_WINDOWEVENT)
  {
    switch(this->event.window.event)
    {
      case SDL_WINDOWEVENT_SHOWN:
      {

      } break;
      case SDL_WINDOWEVENT_HIDDEN:
      {

      } break;
      case SDL_WINDOWEVENT_EXPOSED:
      {

      } break;
      case SDL_WINDOWEVENT_MOVED:
      {

      } break;
      case SDL_WINDOWEVENT_RESIZED:
      {

      } break;
      case SDL_WINDOWEVENT_SIZE_CHANGED:
      {

      } break;
      case SDL_WINDOWEVENT_MINIMIZED:
      {

      } break;
      case SDL_WINDOWEVENT_MAXIMIZED:
      {

      } break;
      case SDL_WINDOWEVENT_RESTORED:
      {

      } break;
      case SDL_WINDOWEVENT_ENTER:
      {

      } break;
      case SDL_WINDOWEVENT_LEAVE:
      {

      } break;
      case SDL_WINDOWEVENT_FOCUS_GAINED:
      {
        this->window.focusGained = LE_TRUE;
      } break;
      case SDL_WINDOWEVENT_FOCUS_LOST:
      {
        this->window.focusGained = LE_FALSE;
      } break;
      case SDL_WINDOWEVENT_CLOSE:
      {

      } break;
      case SDL_WINDOWEVENT_TAKE_FOCUS:
      {

      } break;
      case SDL_WINDOWEVENT_HIT_TEST:
      {

      } break;
    };
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
    zindex = mathMin(zindex, pModel->zindex);
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
  uint32_t lengthErrorInfo = 0;

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
// private point
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::pointDraw(LEPoint * pPoint)
{
  int result = LE_NO_ERROR;
  #ifdef LE_DEBUG
    char * pErrorString = nullptr;
  #endif

  // draw points

  if(pPoint->visible)
  {
    // choose right color

    if(SDL_SetRenderDrawColor(this->pRenderer, pPoint->color.r, pPoint->color.g, pPoint->color.b, pPoint->color.a))
    {
      #ifdef LE_DEBUG
        pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::pointDraw(%d)\n\n", pPoint->id);
        this->printErrorDialog(LE_SDL_DRAW_COLOR, pErrorString);
        delete [] pErrorString;
      #endif

      result = LE_SDL_DRAW_COLOR;
    }

    // blend mode

    if(!result)
    {
      if(SDL_SetRenderDrawBlendMode(this->pRenderer, SDL_BLENDMODE_BLEND))
      {
        #ifdef LE_DEBUG
          pErrorString = new char[256 + 1];
          sprintf(pErrorString, "LEMoon::pointDraw(%d)\n\n", pPoint->id);
          this->printErrorDialog(LE_DRAW_BLEND_MODE, pErrorString);
          delete [] pErrorString;
        #endif
      
        result = LE_DRAW_BLEND_MODE;
      }
    }

    // draw point

    if(!result)
    {
      if(SDL_RenderDrawPoint(this->pRenderer, pPoint->pointBuffer.x, pPoint->pointBuffer.y))
      {
        #ifdef LE_DEBUG
          pErrorString = new char[256 + 1];
          sprintf(pErrorString, "LEMoon::pointDraw(%d)\n\n", pPoint->id);
          this->printErrorDialog(LE_DRAW_POINT, pErrorString);
          delete [] pErrorString;
        #endif
      
        result = LE_DRAW_POINT;
      }
    }
  }

  return result;
}

LEPoint * LEMoon::pointGet(uint32_t id)
{
  LEPoint * pRet = nullptr;
  LEPoint * pCurrent = nullptr;

  if(this->pPointHead != nullptr)
  {
    if(this->memory.pLastPoint != nullptr && this->memory.pLastPoint->id == id)
      {pRet = this->memory.pLastPoint;}
    else
    {
      pCurrent = this->pPointHead->pRight;

      while(pCurrent != this->pPointHead)
      {
        if(pCurrent->id == id)
        {
          pRet = pCurrent;
          this->memory.pLastPoint = pRet;
          break;
        }

        pCurrent = pCurrent->pRight;
      }
    }
  }

  return pRet;
}

LinkedVec2 * LEMoon::pointGetDirection(LEPoint * pPoint, uint32_t idDirection)
{
  LinkedVec2 * pRet = nullptr;
  LinkedVec2 * pCurrent = nullptr;

  if(pPoint->pDirectionHead != nullptr)
  {
    pCurrent = pPoint->pDirectionHead->pRight;

    while(pCurrent != pPoint->pDirectionHead)
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
// private font
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

LEFont * LEMoon::fontGet(uint32_t id)
{
  LEFont * pRet = nullptr;
  LEFont * pCurrent = nullptr;

  if(this->pFontHead != nullptr)
  {
    if(this->memory.pLastFont != nullptr && this->memory.pLastFont->id == id)
      {pRet = this->memory.pLastFont;}
    else
    {
      pCurrent = this->pFontHead->pRight;

      while(pCurrent != this->pFontHead)
      {
        if(pCurrent->id == id)
        {
          pRet = pCurrent;
          this->memory.pLastFont = pCurrent;
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
// private line
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::lineDraw(LELine * pLine)
{
  int result = LE_NO_ERROR;
  #ifdef LE_DEBUG
    char * pErrorString = nullptr;
  #endif

  if(pLine->visible)
  {
    if(SDL_SetRenderDrawColor(this->pRenderer, pLine->color.r, pLine->color.g, pLine->color.b, pLine->color.a))
    {
      result = LE_SDL_DRAW_COLOR;

      #ifdef LE_DEBUG
        pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::lineDraw(%d)\n\n", pLine->id);
        this->printErrorDialog(result, pErrorString);
        delete [] pErrorString;
      #endif
    }

    if(!result)
    {
      if(SDL_RenderDrawLine(this->pRenderer, pLine->line.pointA.x, pLine->line.pointA.y, pLine->line.pointB.x, pLine->line.pointB.y))
      {
        result = LE_SDL_DRAW_LINE;

        #ifdef LE_DEBUG
          pErrorString = new char[256 + 1];
          sprintf(pErrorString, "LEMoon::lineDraw(%d)\n\n", pLine->id);
          this->printErrorDialog(result, pErrorString);
          delete [] pErrorString;
        #endif
      }
    }
  }

  return result;
}

LELine * LEMoon::lineGet(uint32_t id)
{
  LELine * pRet = nullptr;
  LELine * pCurrent = nullptr;

  if(this->pLineHead != nullptr)
  {
    if(this->memory.pLastLine != nullptr && this->memory.pLastLine->id == id)
      {pRet = this->memory.pLastLine;}
    else
    {
      pCurrent = this->pLineHead->pRight;

      while(pCurrent != this->pLineHead)
      {
        if(pCurrent->id == id)
        {
          pRet = pCurrent;
          this->memory.pLastLine = pCurrent;
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
// private video
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

LEVideo * LEMoon::videoGet(uint32_t id)
{
  LEVideo * pRet = nullptr;
  LEVideo * pCurrent = nullptr;

  if(this->pVideoHead != nullptr)
  {
    pCurrent = this->pVideoHead->pRight;

    while(pCurrent != this->pVideoHead)
    {
      if(pCurrent->id == id)
      {
        pRet = pCurrent;
        break;
      }
    }
  }

  return pRet;
}

#ifdef LE_THEORA
static Uint32 baseticks = 0;
static volatile AudioQueue * pAudioQueue = nullptr;
static volatile AudioQueue * pAudioQueueTail = nullptr;

static void SDLCALL audioCallback(void * pUserData, Uint8 * pStream, int len)
{
  Sint16 * pDst = (Sint16*) pStream;

  while(pAudioQueue != nullptr && (len > 0)) 
  {
    volatile AudioQueue * pItem = pAudioQueue;
    AudioQueue * pNext = pItem->pNext;
    const int channels = pItem->pAudio->channels;

    const float * pSrc = pItem->pAudio->samples + (pItem->offset * channels);
    int cpy = (pItem->pAudio->frames - pItem->offset) * channels;
    int i = 0;

    if(cpy > (len / (int)sizeof(Sint16)))
      {cpy = len / sizeof(Sint16);}

    for (i = 0; i < cpy; i++) 
    {
      const float val = *(pSrc++);

      if(val < -1.0f)
        {*(pDst++) = -32768;}
      else
      {
        if(val > 1.0f)
          {*(pDst++) = 32767;}
        else
          {*(pDst++) = (Sint16)(val * 32767.0f);}
      }

      pItem->offset += (cpy / channels);
      len -= cpy * sizeof(Sint16);

      if(pItem->offset >= pItem->pAudio->frames) 
      {
        THEORAPLAY_freeAudio(pItem->pAudio);
        SDL_free((void *)pItem);
        pAudioQueue = pNext;
      }
    }

    if(pAudioQueue == nullptr)
      {pAudioQueueTail = nullptr;}

    if(len > 0)
      {memset(pDst, '\0', len);}

    if(pUserData == nullptr)
      {printf("video: no user data\n");}
  }
}

static void queueAudio(const THEORAPLAY_AudioPacket * pAudio) 
{
  AudioQueue * pItem = (AudioQueue*) SDL_malloc(sizeof(AudioQueue));

  if(pItem == nullptr) 
  {
    THEORAPLAY_freeAudio(pAudio);
    return;
  }

  pItem->pAudio = pAudio;
  pItem->offset = 0;
  pItem->pNext = nullptr;

  SDL_LockAudio();

  if(pAudioQueueTail != nullptr)
    {pAudioQueueTail->pNext = pItem;}
  else
  {
    pAudioQueue = pItem;
    pAudioQueueTail = pItem;
    SDL_UnlockAudio();
  }
}

static bool playFile(const char * pFileName, SDL_Renderer * pRenderer)
{
  bool endPlaying = LE_FALSE;
  THEORAPLAY_Decoder * pDecoder = nullptr;
  const THEORAPLAY_VideoFrame * pVideo = nullptr;
  const THEORAPLAY_AudioPacket * pAudio = nullptr;
  SDL_Texture * pTexture = nullptr;
  SDL_AudioSpec spec;
  Uint32 framems = 0;
  static uint32_t frame = 1;

  pDecoder = THEORAPLAY_startDecodeFile(pFileName, 30, THEORAPLAY_VIDFMT_IYUV);

  while(pAudio == nullptr || pVideo == nullptr) 
  {
    if(pAudio == nullptr)
      {pAudio = THEORAPLAY_getAudio(pDecoder);}

    if(pVideo == nullptr)
      {pVideo = THEORAPLAY_getVideo(pDecoder);}

    SDL_Delay(10);
  }

  framems = (pVideo->fps == 0.0f) ? 0 : ((Uint32)(1000.0f / pVideo->fps));

  pTexture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, pVideo->width, pVideo->height);

  if(pTexture != nullptr)
  {
    memset(&spec, '\0', sizeof(SDL_AudioSpec));
    spec.freq = pAudio->freq;
    spec.format = AUDIO_S16SYS;
    spec.channels = pAudio->channels;
    spec.samples = 2048;
    spec.callback = audioCallback;

    void * pPixel = nullptr;
    int pitch = 0;

    while(pAudio != nullptr)
    {
      queueAudio(pAudio);
      pAudio = THEORAPLAY_getAudio(pDecoder);
    }

    baseticks = SDL_GetTicks();

    while(THEORAPLAY_isDecoding(pDecoder))
    {
      const Uint32 now = SDL_GetTicks() - baseticks;

      if(pVideo == nullptr)
        {pVideo = THEORAPLAY_getVideo(pDecoder);}

      if(pVideo && (pVideo->playms <= now))
      {
        if(framems && ((now - pVideo->playms) >= framems))
        {
          const THEORAPLAY_VideoFrame * pLast = pVideo;

          while((pVideo = THEORAPLAY_getVideo(pDecoder)) != nullptr)
          {
            THEORAPLAY_freeVideo(pLast);
            pLast = pVideo;

            if((now - pVideo->playms) < framems)
              {break;}
          }

          if(pVideo == nullptr)
            {pVideo = pLast;}
        }

        SDL_LockTexture(pTexture, nullptr, &pPixel, &pitch);
        const int w = pVideo->width;
        const int h = pVideo->height;
        const Uint8 * pY = (const Uint8*) pVideo->pixels;
        const Uint8 * pU = pY + (w * h);
        const Uint8 * pV = pU + ((w / 2) * (h / 2));
        Uint8 * pDst = (Uint8*)pPixel;
        int i = 0;

        for(i = 0 ; i < h ; i++, pY += w, pDst += pitch)
          {memcpy(pDst, pY, w);}

        for(i = 0 ; i < h / 2 ; i++,	pU += w / 2, pDst += pitch / 2)
          {memcpy(pDst, pU, w / 2);}

        for(i = 0 ; i < h / 2 ; i++,	pV += w / 2,	pDst += pitch / 2) 
          {memcpy(pDst, pV, w / 2);}

        SDL_UnlockTexture(pTexture);
        THEORAPLAY_freeVideo(pVideo);
        pVideo = nullptr;
      }
      else
        {SDL_Delay(10);}

      while((pAudio = THEORAPLAY_getAudio(pDecoder)) != nullptr)
        {queueAudio(pAudio);}

      if(frame < 10)
      {
        SDL_SetRenderDrawColor(pRenderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderClear(pRenderer);
        SDL_RenderPresent(pRenderer);
        frame++;
      }
      else
      {
        SDL_RenderClear(pRenderer);
        SDL_RenderCopy(pRenderer, pTexture, nullptr, nullptr);
        SDL_RenderPresent(pRenderer);
      }
    }
/*
    while(!quit)
    {
      SDL_LockAudio();
      quit = (pAudioQueue == nullptr);
      SDL_UnlockAudio();

      if(!quit)
        {SDL_Delay(100);}
    }
*/
    if(pTexture != nullptr)
      {SDL_DestroyTexture(pTexture);}

    if(pVideo != nullptr)
      {THEORAPLAY_freeVideo(pVideo);}

    if(pAudio != nullptr)
      {THEORAPLAY_freeAudio(pAudio);}

    if(pDecoder != nullptr)
      {THEORAPLAY_stopDecode(pDecoder);}

    endPlaying = LE_TRUE;
  }

  frame = 1;
  return endPlaying;
}
#endif

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public window
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

bool LEMoon::windowFocused()
{
  return this->window.focusGained;
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
  this->pTimeEventHead = nullptr;
  this->pFontHead = nullptr;
  this->pSoundHead = nullptr;
  this->pTextHead = nullptr;
  this->pPointHead = nullptr;
  this->pModelHead = nullptr;
  this->pLineHead = nullptr;
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
    printf("Lynar Engine Moon 1.3.0 (author: Patrick-Christopher Mattulat)\n");
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

void LEMoon::endFrame()
{
  this->timestep = (SDL_GetTicks() - this->timestamp) * 0.001f;
  this->freeKeyboardKeys();
  this->freeMouse();
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

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public model
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::modelCreate(uint32_t id)
{
  #ifdef LE_MUTEX
    this->mtxModel.mtxAdd.lock();
  #endif

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

  #ifdef LE_MUTEX
    this->mtxModel.mtxAdd.unlock();
  #endif

  return result;
}

int LEMoon::modelDelete(uint32_t id)
{
  #ifdef LE_MUTEX
    this->mtxModel.mtxDel.lock();
  #endif

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

  #ifdef LE_MUTEX
    this->mtxModel.mtxDel.unlock();
  #endif

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

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public time event
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::timeEventCreate(uint32_t id, uint32_t ntimestamp)
{
  #ifdef LE_MUTEX
    this->mtxTimeEvent.mtxAdd.lock();
  #endif

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

  #ifdef LE_MUTEX
    this->mtxTimeEvent.mtxAdd.unlock();
  #endif

  return result;
}

int LEMoon::timeEventDelete(uint32_t id)
{
  #ifdef LE_MUTEX
    this->mtxTimeEvent.mtxDel.lock();
  #endif

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

  #ifdef LE_MUTEX
    this->mtxTimeEvent.mtxDel.unlock();
  #endif

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

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public point
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::pointCreate(uint32_t id)
{
  #ifdef LE_MUTEX
    this->mtxPoint.mtxAdd.lock();
  #endif

  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint == nullptr)
  {
    if(this->pPointHead == nullptr)
    {
      this->pPointHead = new LEPoint;
      this->pPointHead->pLeft = this->pPointHead;
      this->pPointHead->pRight = this->pPointHead;
    }

    pPoint = new LEPoint;
    pPoint->pLeft = this->pPointHead->pLeft;
    pPoint->pRight = this->pPointHead;
    this->pPointHead->pLeft->pRight = pPoint;
    this->pPointHead->pLeft = pPoint;
    pPoint->id = id;
    pPoint->currentDegree = 0.0f;
    pPoint->visible = LE_TRUE;
    pPoint->pDirectionHead = nullptr;
    pPoint->posX = 0.0f;
    pPoint->posY = 0.0f;
    pPoint->point = {0, 0};
    pPoint->pointBuffer = {0, 0};
    pPoint->zindex = 1;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointCreate(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_EXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_EXIST;
  }

  #ifdef LE_MUTEX
    this->mtxPoint.mtxAdd.unlock();
  #endif

  return result;
}

int LEMoon::pointDelete(uint32_t id)
{
  #ifdef LE_MUTEX
    this->mtxPoint.mtxDel.lock();
  #endif

  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);
  LinkedVec2 * pCurrentDirection = nullptr;
  LinkedVec2 * pNextDirection = nullptr;

  if(pPoint != nullptr)
  {
    pPoint->pLeft->pRight = pPoint->pRight;
    pPoint->pRight->pLeft = pPoint->pLeft;

    // loesche Bewegungsrichtungen

    if(pPoint->pDirectionHead != nullptr)
    {
      pCurrentDirection = pPoint->pDirectionHead->pRight;

      while(pCurrentDirection != pPoint->pDirectionHead)
      {
        pNextDirection = pCurrentDirection->pRight;
        delete pCurrentDirection;
        pCurrentDirection = pNextDirection;
      }

      delete pPoint->pDirectionHead;
      pPoint->pDirectionHead = nullptr;
    }

    delete pPoint;

    if(this->pPointHead->pLeft == this->pPointHead && this->pPointHead->pRight == this->pPointHead)
    {
      delete this->pPointHead;
      this->pPointHead = nullptr;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointDelete(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  #ifdef LE_MUTEX
    this->mtxPoint.mtxDel.unlock();
  #endif

  return result;
}

int LEMoon::pointSetColor(uint32_t id, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint != nullptr)
  {
    pPoint->color.r = r;
    pPoint->color.g = g;
    pPoint->color.b = b;
    pPoint->color.a = a;
    pPoint->currentAlpha = (uint8_t) a;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointSetColor(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  return result;
}

int LEMoon::pointSetPosition(uint32_t id, int x, int y)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint != nullptr)
  {
    pPoint->point.x = x;
    pPoint->point.y = y;
    pPoint->pointBuffer.x = x;
    pPoint->pointBuffer.y = y;
    pPoint->posX = x;
    pPoint->posY = y;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointSetPosition(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  return result;
}

Color LEMoon::pointGetColor(uint32_t id)
{
  LEPoint * pPoint = this->pointGet(id);
  Color color;

  if(pPoint != nullptr)
    {color = pPoint->color;}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointGetColor(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return color;
}

int LEMoon::pointFade(uint32_t id, double alphaPerSecond)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint != nullptr)
  {
    pPoint->currentAlpha += (alphaPerSecond * this->timestep);

    if(pPoint->currentAlpha > 255.0f)
      {pPoint->currentAlpha = 255.0f;}

    if(pPoint->currentAlpha < 0.0f)
      {pPoint->currentAlpha = 0.0f;}

    pPoint->color.a = (uint8_t) pPoint->currentAlpha;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointFade(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  return result;
}

int LEMoon::pointRotate(uint32_t id, double degreePerSecond, SDL_Point rotationPoint)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint != nullptr)
  {
    pPoint->currentDegree += degreePerSecond * this->timestep;
    pPoint->currentDegree = mathMod(pPoint->currentDegree, 360.0f); 
    pPoint->pointBuffer = mathRotatePoint(pPoint->point, rotationPoint, pPoint->currentDegree);
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointRotate(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  return result;
}

int LEMoon::pointSetVisible(uint32_t id, bool visible)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);

  if(pPoint != nullptr)
    {pPoint->visible = visible;}
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointSetVisible(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  return result;
}

int LEMoon::pointAddDirection(uint32_t id, uint32_t idDirection, glm::vec2 direction)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);
  LinkedVec2 * pDirection = nullptr;

  if(pPoint != nullptr)
  {
    pDirection = this->pointGetDirection(pPoint, idDirection);

    if(pDirection == nullptr)
    {
      // wurde schon einmal eine Bewegungsrichtung hinzugefuegt? Wenn nicht: fuege Kopf hinzu

      if(pPoint->pDirectionHead == nullptr)
      {
        pPoint->pDirectionHead = new LinkedVec2;
        pPoint->pDirectionHead->pLeft = pPoint->pDirectionHead;
        pPoint->pDirectionHead->pRight = pPoint->pDirectionHead;
      }

      // fuege neue Bewegungsrichtung hinzu

      pDirection = new LinkedVec2;
      pDirection->pRight = pPoint->pDirectionHead;
      pDirection->pLeft = pPoint->pDirectionHead->pLeft;
      pPoint->pDirectionHead->pLeft->pRight = pDirection;
      pPoint->pDirectionHead->pLeft = pDirection;
      pDirection->id = idDirection;
      pDirection->data = direction;
      pDirection->currentDegree = 0.0f;
    }
    else
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::pointAddDirection(%u, %u, glm::vec2(%1.2f, %1.2f))\n\n", id, idDirection, direction.x, direction.y);
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
      sprintf(pErrorString, "LEMoon::pointAddDirection(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  return result;
}

int LEMoon::pointMoveDirection(uint32_t id, uint32_t idDirection)
{
  int result = LE_NO_ERROR;
  LEPoint * pPoint = this->pointGet(id);
  LinkedVec2 * pDirection = nullptr;

  if(pPoint != nullptr)
  {
    pDirection = this->pointGetDirection(pPoint, idDirection);

    if(pDirection != nullptr)
    {
      pPoint->posX += this->timestep * pDirection->data.x;
      pPoint->posY += this->timestep * pDirection->data.y;
      pPoint->pointBuffer.x = (int) pPoint->posX;
      pPoint->pointBuffer.y = (int) pPoint->posY;
    }
    else
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::pointMoveDirection(%u, %u)\n\n", id, idDirection);
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
      sprintf(pErrorString, "LEMoon::pointMoveDirection(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_POINT_NOEXIST;
  }

  return result;
}

SDL_Point LEMoon::pointGetPosition(uint32_t id)
{
  LEPoint * pPoint = this->pointGet(id);
  SDL_Point position;

  if(pPoint != nullptr)
  {
    position.x = pPoint->pointBuffer.x;
    position.y = pPoint->pointBuffer.y;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointGetPosition(%u)\n\n", id);
      this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return position;
}

int LEMoon::pointSetZindex(uint32_t id, uint32_t zindex)
{
  int result = LE_NO_ERROR;
  LEPoint * pElem = this->pointGet(id);
  LEPoint * pCurrent = nullptr;
  bool moreThanOneElement = this->pPointHead->pLeft->id != this->pPointHead->pRight->id;

  if(zindex == 0)
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::pointSetZindex(%u, %u)\n\n", id, zindex);
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
    
      pCurrent = this->pPointHead->pRight;
    
      while(pElem->zindex > pCurrent->zindex && pCurrent != this->pPointHead)
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
        sprintf(pErrorString, "LEMoon::pointSetZindex(%u)\n\n", id);
        this->printErrorDialog(LE_POINT_NOEXIST, pErrorString);
        delete [] pErrorString;
      #endif
    
      result = LE_POINT_NOEXIST;
    }
  }

  return result;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public sound
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::soundCreate(uint32_t id)
{
  #ifdef LE_MUTEX
    this->mtxSound.mtxAdd.lock();
  #endif

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

  #ifdef LE_MUTEX
    this->mtxSound.mtxAdd.unlock();
  #endif

  return result;
}

int LEMoon::soundDelete(uint32_t id)
{
  #ifdef LE_MUTEX
    this->mtxSound.mtxDel.lock();
  #endif

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

  #ifdef LE_MUTEX
    this->mtxSound.mtxDel.unlock();
  #endif

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

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public text
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::textCreate(uint32_t id)
{
  #ifdef LE_MUTEX
    this->mtxText.mtxAdd.lock();
  #endif

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

  #ifdef LE_MUTEX
    this->mtxText.mtxAdd.unlock();
  #endif

  return result;
}

int LEMoon::textDelete(uint32_t id)
{
  #ifdef LE_MUTEX
    this->mtxText.mtxDel.lock();
  #endif

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

  #ifdef LE_MUTEX
    this->mtxText.mtxDel.unlock();
  #endif

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

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public font
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::fontCreateTTF(uint32_t id, const char * pFile, int fontSize)
{
  #ifdef LE_MUTEX
    this->mtxFont.mtxAdd.lock();
  #endif

  int result = LE_NO_ERROR;
  LEFont * pNew = this->fontGet(id);

  if(pNew == nullptr)
  {
    if(this->pFontHead == nullptr)
    {
      this->pFontHead = new LEFont;
      this->pFontHead->pLeft = this->pFontHead;
      this->pFontHead->pRight = this->pFontHead;
    }

    pNew = new LEFont;
    pNew->pLeft = this->pFontHead->pLeft;
    pNew->pRight = this->pFontHead;
    this->pFontHead->pLeft->pRight = pNew;
    this->pFontHead->pLeft = pNew;
    pNew->id = id;
    pNew->pFont = TTF_OpenFont(pFile, fontSize);

    if(pNew->pFont == nullptr)
    {
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::fontCreateTTF(%u, %s, %d)\n\n", id, pFile, fontSize);
        this->printErrorDialog(LE_OPEN_FONT, pErrorString);
        delete [] pErrorString;
      #endif

      result = LE_OPEN_FONT;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::fontCreateTTF(%u)\n\n", id);
      this->printErrorDialog(LE_FONT_EXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_FONT_EXIST;
  }

  #ifdef LE_MUTEX
    this->mtxFont.mtxAdd.unlock();
  #endif

  return result;
}

int LEMoon::fontDelete(uint32_t id)
{
  #ifdef LE_MUTEX
    this->mtxFont.mtxDel.lock();
  #endif

  int result = LE_NO_ERROR;
  LEFont * pFont = this->fontGet(id);

  if(pFont != nullptr)
  {
    pFont->pLeft->pRight = pFont->pRight;
    pFont->pRight->pLeft = pFont->pLeft;

    if(pFont->pFont != nullptr)
      {TTF_CloseFont(pFont->pFont);}

    delete pFont;

    if(this->pFontHead->pLeft == this->pFontHead && this->pFontHead->pRight == this->pFontHead)
    {
      delete this->pFontHead;
      this->pFontHead = nullptr;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::fontDelete(%u)\n\n", id);
      this->printErrorDialog(LE_FONT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_FONT_NOEXIST;
  }

  #ifdef LE_MUTEX
    this->mtxFont.mtxDel.unlock();
  #endif

  return result;
}

int LEMoon::fontSetStyle(uint32_t id, int style)
{
  int result = LE_NO_ERROR;
  LEFont * pFont = this->fontGet(id);

  if(pFont != nullptr)
  {
    if(pFont->pFont != nullptr)
      {TTF_SetFontStyle(pFont->pFont, style);}
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::fontSetStyle(%u)\n\n", id);
      this->printErrorDialog(LE_FONT_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_FONT_NOEXIST;
  }

  return result;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public line
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::lineCreate(uint32_t id)
{
  #ifdef LE_MUTEX
    this->mtxLine.mtxAdd.lock();
  #endif

  int result = LE_NO_ERROR;
  LELine * pNew = this->lineGet(id);

  if(pNew == nullptr)
  {
    if(this->pLineHead == nullptr)
    {
      this->pLineHead = new LELine;
      this->pLineHead->pLeft = this->pLineHead;
      this->pLineHead->pRight = this->pLineHead;
      this->pLineHead->zindex = 0;
    }

    pNew = new LELine;
    pNew->pRight = this->pLineHead;
    pNew->pLeft = this->pLineHead->pLeft;
    this->pLineHead->pLeft->pRight = pNew;
    this->pLineHead->pLeft = pNew;
    pNew->id = id;
    pNew->line.pointA = {0, 0};
    pNew->line.pointB = {0, 0};
    pNew->zindex = 0;
    pNew->color = {255, 255, 255, 255};
    pNew->visible = LE_TRUE;
  }
  else
  {
    result = LE_LINE_EXIST;

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::lineCreate(%u)\n\n", id);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }

  #ifdef LE_MUTEX
    this->mtxLine.mtxAdd.unlock();
  #endif

  return result;
}

int LEMoon::lineDelete(uint32_t id)
{
  #ifdef LE_MUTEX
    this->mtxLine.mtxDel.lock();
  #endif

  int result = LE_NO_ERROR;
  LELine * pLine = this->lineGet(id);

  if(pLine != nullptr)
  {
    pLine->pLeft->pRight = pLine->pRight;
    pLine->pRight->pLeft = pLine->pLeft;
    delete pLine;

    if(this->pLineHead->pLeft == this->pLineHead && this->pLineHead->pRight == this->pLineHead)
    {
      delete this->pLineHead;
      this->pLineHead = nullptr;
    }
  }
  else
  {
    result = LE_LINE_NOEXIST;

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::lineDelete(%u)\n\n", id);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }

  #ifdef LE_MUTEX
    this->mtxLine.mtxDel.unlock();
  #endif

  return result;
}

int LEMoon::lineSet(uint32_t id, int x1, int y1, int x2, int y2)
{
  int result = LE_NO_ERROR;
  LELine * pLine = this->lineGet(id);

  if(pLine != nullptr)
  {
    pLine->line.pointA.x = x1;
    pLine->line.pointA.y = y1;
    pLine->line.pointB.x = x2;
    pLine->line.pointB.y = y2;
  }
  else
  {
    result = LE_LINE_NOEXIST;

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::lineSet(%u)\n\n", id);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return result;
}

int LEMoon::lineSetColor(uint32_t id, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  int result = LE_NO_ERROR;
  LELine * pLine = this->lineGet(id);

  if(pLine != nullptr)
  {
    pLine->color.r = r;
    pLine->color.g = g;
    pLine->color.b = b;
    pLine->color.a = a;
  }
  else
  {
    result = LE_LINE_NOEXIST;

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::lineSetColor(%u)\n\n", id);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return result;
}

int LEMoon::lineSetVisible(uint32_t id, bool visible)
{
  int result = LE_NO_ERROR;
  LELine * pLine = this->lineGet(id);

  if(pLine != nullptr)
    {pLine->visible = visible;}

  return result;
}

int LEMoon::lineSetZindex(uint32_t id, uint32_t zindex)
{
  int result = LE_NO_ERROR;
  LELine * pLine = this->lineGet(id);
  LELine * pCurrent = nullptr;
  bool moreThanOneElement = this->pLineHead->pLeft->id != this->pLineHead->pRight->id;

  if(zindex == 0)
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::lineSetZindex(%u, %u)\n\n", id, zindex);
      this->printErrorDialog(LE_INVALID_ZINDEX, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_INVALID_ZINDEX;
  }

  if(moreThanOneElement)
  {
    if(!result && pLine != nullptr)
    {
      pLine->zindex = zindex;
    
      // exclude from list
    
      pLine->pLeft->pRight = pLine->pRight;
      pLine->pRight->pLeft = pLine->pLeft;
    
      // search right place for zindex
    
      pCurrent = this->pLineHead->pRight;
    
      while(pLine->zindex > pCurrent->zindex && pCurrent != this->pLineHead)
        {pCurrent = pCurrent->pRight;}
    
      // include at right postion
    
      pLine->pLeft = pCurrent->pLeft;
      pLine->pRight = pCurrent;
      pCurrent->pLeft->pRight = pLine;
      pCurrent->pLeft = pLine;
    }
    else
    {
      result = LE_LINE_NOEXIST;
    
      #ifdef LE_DEBUG
        char * pErrorString = new char[256 + 1];
        sprintf(pErrorString, "LEMoon::lineSetZindex(%u)\n\n", id);
        this->printErrorDialog(result, pErrorString);
        delete [] pErrorString;
      #endif
    }
  }

  return result;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// public video
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

int LEMoon::videoCreate(uint32_t id, const char * pFile)
{
  #ifdef LE_MUTEX
    this->mtxVideo.mtxAdd.lock();
  #endif

  int result = LE_NO_ERROR;
  LEVideo * pVideo = this->videoGet(id);

  if(pVideo == nullptr)
  {
    if(this->pVideoHead == nullptr)
    {
      this->pVideoHead = new LEVideo;
      this->pVideoHead->pLeft = this->pVideoHead;
      this->pVideoHead->pRight = this->pVideoHead;
      this->pVideoHead->id = 0;
    }

    pVideo = new LEVideo;
    pVideo->pRight = this->pVideoHead;
    pVideo->pLeft = this->pVideoHead->pLeft;
    this->pVideoHead->pLeft->pRight = pVideo;
    this->pVideoHead->pLeft = pVideo;
    pVideo->id = id;
    pVideo->pFile = (char*) pFile;
  }
  else
  {
    result = LE_VIDEO_EXIST;

    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::videoCreate(%u)\n\n", id);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }

  #ifdef LE_MUTEX
    this->mtxVideo.mtxAdd.unlock();
  #endif

  return result;
}

bool LEMoon::videoPlay(uint32_t id)
{
  bool endPlaying = LE_FALSE;
  LEVideo * pVideo = this->videoGet(id);

  if(pVideo != nullptr)
  {
    #ifdef LE_THEORA
      endPlaying = playFile(pVideo->pFile, this->pRenderer);
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::videoPlay(%u)\n\n", id);
      this->printErrorDialog(LE_VIDEO_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif
  }

  return endPlaying;
}

int LEMoon::videoDelete(uint32_t id)
{
  #ifdef LE_MUTEX
    this->mtxVideo.mtxDel.lock();
  #endif

  int result = LE_NO_ERROR;
  LEVideo * pVideo = this->videoGet(id);

  if(pVideo != nullptr)
  {
    pVideo->pLeft->pRight = pVideo->pRight;
    pVideo->pRight->pLeft = pVideo->pLeft;

    if(pVideo->pFile != nullptr)
    {
      delete [] pVideo->pFile;
      pVideo->pFile = nullptr;
    }

    delete pVideo;
    pVideo = nullptr;
  }
  else
  {
    #ifdef LE_DEBUG
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::videoDelete(%u)\n\n", id);
      this->printErrorDialog(LE_VIDEO_NOEXIST, pErrorString);
      delete [] pErrorString;
    #endif

    result = LE_VIDEO_NOEXIST;
  }

  #ifdef LE_MUTEX
    this->mtxVideo.mtxDel.unlock();
  #endif

  return result;
}
