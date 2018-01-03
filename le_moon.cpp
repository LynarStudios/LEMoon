/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Visual Studio 2015 Community, g++ Compiler
  date:               18.05.2017
  updated:            29.12.2017
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
  uint32_t zindex = 1;
  const uint32_t AMOUNT_OBJECTS = 3;
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

  uint32_t zindexArray[AMOUNT_OBJECTS]; // 0 = Model, 1 = Texts, 2 = Lines

  for(uint32_t i = 0 ; i < AMOUNT_OBJECTS ; i++)
    {zindexArray[i] = 0;}

  // draw

  while(pModel != this->pModelHead || pText != this->pTextHead || pLine != this->pLineHead)
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

    // text, models and lines still available?

    for(uint32_t i = 0 ; i < AMOUNT_OBJECTS ; i++)
      {zindexArray[i] = 0;}

    if(pText != this->pTextHead && pModel != this->pModelHead && pLine != this->pLineHead)
      {zindex = mathMin(mathMin(pModel->zindex, pText->zindex), pLine->zindex);}
    else
    {
      // zindex auslesen und setzen

      if(pModel != this->pModelHead)
        {zindexArray[0] = pModel->zindex;}

      if(pText != this->pTextHead)
        {zindexArray[1] = pText->zindex;}

      if(pLine != this->pLineHead)
        {zindexArray[2] = pLine->zindex;}

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
        case SDLK_DOWN:
        {
          this->keyboard.keyDown = LE_RELEASED;
        } break;
        case SDLK_ESCAPE:
        {
          this->keyboard.keyEscape = LE_RELEASED;
        } break;
        case SDLK_LEFT:
        {
          this->keyboard.keyLeft = LE_RELEASED;
        } break;
        case SDLK_RETURN:
        {
          this->keyboard.keyReturn = LE_RELEASED;
        } break;
        case SDLK_RIGHT:
        {
          this->keyboard.keyRight = LE_RELEASED;
        } break;
        case SDLK_SPACE:
        {
          this->keyboard.keySpace = LE_RELEASED;
        } break;
        case SDLK_UP:
        {
          this->keyboard.keyUp = LE_RELEASED;
        } break;
      };
    } break;
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
        case SDLK_DOWN:
        {
          this->keyboard.keyDown = LE_PRESSED;
        } break;
        case SDLK_ESCAPE:
        {
          this->keyboard.keyEscape = LE_PRESSED;
        } break;
        case SDLK_LEFT:
        {
          this->keyboard.keyLeft = LE_PRESSED;
        } break;
        case SDLK_RETURN:
        {
          this->keyboard.keyReturn = LE_PRESSED;
        } break;
        case SDLK_RIGHT:
        {
          this->keyboard.keyRight = LE_PRESSED;
        } break;
        case SDLK_SPACE:
        {
          this->keyboard.keySpace = LE_PRESSED;
        } break;
        case SDLK_UP:
        {
          this->keyboard.keyUp = LE_PRESSED;
        } break;
      };
    } break;
  };
}

void LEMoon::freeKeyboardKeys()
{
  if(this->keyboard.key0 == LE_RELEASED)
    {this->keyboard.key0 = LE_INACTIVE;}

  if(this->keyboard.key1 == LE_RELEASED)
    {this->keyboard.key1 = LE_INACTIVE;}

  if(this->keyboard.key2 == LE_RELEASED)
    {this->keyboard.key2 = LE_INACTIVE;}

  if(this->keyboard.key3 == LE_RELEASED)
    {this->keyboard.key3 = LE_INACTIVE;}

  if(this->keyboard.key4 == LE_RELEASED)
    {this->keyboard.key4 = LE_INACTIVE;}

  if(this->keyboard.key5 == LE_RELEASED)
    {this->keyboard.key5 = LE_INACTIVE;}

  if(this->keyboard.key6 == LE_RELEASED)
    {this->keyboard.key6 = LE_INACTIVE;}

  if(this->keyboard.key7 == LE_RELEASED)
    {this->keyboard.key7 = LE_INACTIVE;}

  if(this->keyboard.key8 == LE_RELEASED)
    {this->keyboard.key8 = LE_INACTIVE;}

  if(this->keyboard.key9 == LE_RELEASED)
    {this->keyboard.key9 = LE_INACTIVE;}

  if(this->keyboard.keyA == LE_RELEASED)
    {this->keyboard.keyA = LE_INACTIVE;}

  if(this->keyboard.keyACBack == LE_RELEASED)
    {this->keyboard.keyACBack = LE_INACTIVE;}

  if(this->keyboard.keyACBookmarks == LE_RELEASED)
    {this->keyboard.keyACBookmarks = LE_INACTIVE;}

  if(this->keyboard.keyACForward == LE_RELEASED)
    {this->keyboard.keyACForward = LE_INACTIVE;}

  if(this->keyboard.keyACHome == LE_RELEASED)
    {this->keyboard.keyACHome = LE_INACTIVE;}

  if(this->keyboard.keyACRefresh == LE_RELEASED)
    {this->keyboard.keyACRefresh = LE_INACTIVE;}

  if(this->keyboard.keyACSearch == LE_RELEASED)
    {this->keyboard.keyACSearch = LE_INACTIVE;}

  if(this->keyboard.keyACStop == LE_RELEASED)
    {this->keyboard.keyACStop = LE_INACTIVE;}

  if(this->keyboard.keyAgain == LE_RELEASED)
    {this->keyboard.keyAgain = LE_INACTIVE;}

  if(this->keyboard.keyAltErase == LE_RELEASED)
    {this->keyboard.keyAltErase = LE_INACTIVE;}

  if(this->keyboard.keyDown == LE_RELEASED)
    {this->keyboard.keyDown = LE_INACTIVE;}

  if(this->keyboard.keyEscape == LE_RELEASED)
    {this->keyboard.keyEscape = LE_INACTIVE;}

  if(this->keyboard.keyLeft == LE_RELEASED)
    {this->keyboard.keyLeft = LE_INACTIVE;}

  if(this->keyboard.keyReturn == LE_RELEASED)
    {this->keyboard.keyReturn = LE_INACTIVE;}

  if(this->keyboard.keyRight == LE_RELEASED)
    {this->keyboard.keyRight = LE_INACTIVE;}

  if(this->keyboard.keySpace == LE_RELEASED)
    {this->keyboard.keySpace = LE_INACTIVE;}

  if(this->keyboard.keyUp == LE_RELEASED)
    {this->keyboard.keyUp = LE_INACTIVE;}
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
    this->printErrorDialog(result, "LEMoon::modelDraw()\n\n");
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

  if(pText->visible && pText->alpha > 0.0f)
  {
    if(SDL_RenderCopyEx(this->pRenderer, pText->pTexture, nullptr, &(pText->posSize), 0.0f, nullptr, SDL_FLIP_NONE))
    {
      #ifdef LE_DEBUG
        this->printErrorDialog(LE_SDL_RENDER_COPY_EX, "LEMoon::textDraw()\n\n");
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

  if(pLine->visible)
  {
    if(SDL_SetRenderDrawColor(this->pRenderer, pLine->color.r, pLine->color.g, pLine->color.b, pLine->color.a))
    {
      result = LE_SDL_DRAW_COLOR;

      #ifdef LE_DEBUG
        this->printErrorDialog(result, "LEMoon::lineDraw()\n\n");
      #endif
    }

    if(!result)
    {
      if(SDL_RenderDrawLine(this->pRenderer, pLine->line.pointA.x, pLine->line.pointA.y, pLine->line.pointB.x, pLine->line.pointB.y))
      {
        result = LE_SDL_DRAW_LINE;

        #ifdef LE_DEBUG
          this->printErrorDialog(result, "LEMoon::lineDraw()\n\n");
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

  #ifdef LE_DESKTOP_APP
    this->clearKeyboard();
  #endif

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

int LEMoon::init(int numChannels, const char * pAppName)
{
  int result = LE_NO_ERROR;
  int mixFlags = 0;
  char * pString = new char [512 + 1];
  char * pBasePath = nullptr;

  // initialize SDL

  if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS))
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

  // load image library

  if(!result)
  {
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
      #ifdef LE_DEBUG
        this->printErrorDialog(LE_SDL_IMG_INIT, "LEMoon::init()\n\n");
      #endif

      result = LE_SDL_IMG_INIT;
    }
  }

  // Sounds

  if(!result)
  {
    if((Mix_Init(mixFlags) & mixFlags) != mixFlags)
    {
      #ifdef LE_DEBUG
        this->printErrorDialog(LE_MIXER_INIT, "LEMoon::init()\n\n");
      #endif

      result = LE_MIXER_INIT;
    }
  }

  // open Audio Channel Stereo

  if(!result)
  {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024))
    {
      #ifdef LE_DEBUG
        this->printErrorDialog(LE_OPEN_AUDIO, "LEMoon::init()\n\n");
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
        this->printErrorDialog(LE_ALLOC_CHANNELS, "LEMoon::init()\n\n");
      #endif

      result = LE_ALLOC_CHANNELS;
    }
  }

  // init TTF

  if(!result)
  {
    if(TTF_Init())
    {
      #ifdef LE_DEBUG
        this->printErrorDialog(LE_TTF_INIT, "LEMoon::init()\n\n");
      #endif

      result = LE_TTF_INIT;
    }
  }

  if(!result)
  {
    printf("Lynar Engine Moon 1.0.0 (author: Patrick-Christopher Mattulat)\n");
    this->initialized = LE_TRUE;
  }

  delete [] pString;
  pString = nullptr;
  return result;
}

int LEMoon::pollEvent()
{
  return SDL_PollEvent(&(this->event));
}

void LEMoon::beginFrame()
{
  this->timestamp = SDL_GetTicks();
  #ifdef LE_DESKTOP_APP
  this->handleKeyboard();
  #endif
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
        case SDLK_DOWN:
        {
          flag = (this->keyboard.keyDown == LE_PRESSED);
        } break;
        case SDLK_ESCAPE:
        {
          flag = (this->keyboard.keyEscape == LE_PRESSED);
        } break;
        case SDLK_LEFT:
        {
          flag = (this->keyboard.keyLeft == LE_PRESSED);
        } break;
        case SDLK_RETURN:
        {
          flag = (this->keyboard.keyReturn == LE_PRESSED);
        } break;
        case SDLK_RIGHT:
        {
          flag = (this->keyboard.keyRight == LE_PRESSED);
        } break;
        case SDLK_SPACE:
        {
          flag = (this->keyboard.keySpace == LE_PRESSED);
        } break;
        case SDLK_UP:
        {
          flag = (this->keyboard.keyUp == LE_PRESSED);
        } break;
      };
    } break;
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
        case SDLK_DOWN:
        {
          flag = (this->keyboard.keyDown == LE_RELEASED);
        } break;
        case SDLK_ESCAPE:
        {
          flag = (this->keyboard.keyEscape == LE_RELEASED);
        } break;
        case SDLK_LEFT:
        {
          flag = (this->keyboard.keyLeft == LE_RELEASED);
        } break;
        case SDLK_RETURN:
        {
          flag = (this->keyboard.keyReturn == LE_RELEASED);
        } break;
        case SDLK_RIGHT:
        {
          flag = (this->keyboard.keyRight == LE_RELEASED);
        } break;
        case SDLK_SPACE:
        {
          flag = (this->keyboard.keySpace == LE_RELEASED);
        } break;
        case SDLK_UP:
        {
          flag = (this->keyboard.keyUp == LE_RELEASED);
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

  // draw points

  if(!result && this->pPointHead != nullptr)
  {
    pPoint = this->pPointHead->pRight;

    while(pPoint != this->pPointHead)
    {
      if(pPoint->visible)
      {
        // choose right color

        if(SDL_SetRenderDrawColor(this->pRenderer, pPoint->color.r, pPoint->color.g, pPoint->color.b, pPoint->color.a))
        {
          #ifdef LE_DEBUG
            this->printErrorDialog(LE_SDL_DRAW_COLOR, "LEMoon::drawFrame()\n\n");
          #endif

          result = LE_SDL_DRAW_COLOR;
          break;
        }

        // blend mode

        if(SDL_SetRenderDrawBlendMode(this->pRenderer, SDL_BLENDMODE_BLEND))
        {
          #ifdef LE_DEBUG
            this->printErrorDialog(LE_DRAW_BLEND_MODE, "LEMoon::drawFrame()\n\n");
          #endif

          result = LE_DRAW_BLEND_MODE;
          break;
        }

        // draw point

        if(SDL_RenderDrawPoint(this->pRenderer, pPoint->pointBuffer.x, pPoint->pointBuffer.y))
        {
          #ifdef LE_DEBUG
            this->printErrorDialog(LE_DRAW_POINT, "LEMoon::drawFrame()\n\n");
          #endif

          result = LE_DRAW_POINT;
          break;
        }
      }

      pPoint = pPoint->pRight;
    }
  }

  // draw Models, Texts and Lines, depending on zindex 

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
  #ifdef LE_DESKTOP_APP
    this->freeKeyboardKeys();
  #endif
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

double LEMoon::relativeSizeX(double pixel)
{
  return this->percentToPixelX(this->pixelToPercentX(pixel));
}

double LEMoon::relativeSizeY(double pixel)
{
  return this->percentToPixelY(this->pixelToPercentY(pixel));
}

double LEMoon::getTimestep()
{
  return this->timestep;
}

Color LEMoon::getBackgroundColor()
{
  return this->backgroundColor;
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
int LEMoon::mkpath(const char* dir, mode_t mode)
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
      this->printErrorDialog(LE_MDL_EXIST, "LEMoon::modelCreate()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelDelete()\n\n");
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelCreateTexture(uint32_t id, uint32_t idTexture, const char * pFile)
{
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlCreateTexture(idTexture, pFile, this->pRenderer);

    #ifdef LE_DEBUG
      this->printErrorDialog(result, "LEMoon::modelCreateTexture()\n\n");
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelCreateTexture()\n\n");
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelAddTextureSourceRect(uint32_t id, uint32_t idTexture, uint32_t idSrcRect, int x, int y, int w, int h)
{
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlAddTextureSourceRect(idTexture, idSrcRect, x, y, w, h);

    #ifdef LE_DEBUG
      this->printErrorDialog(result, "LEMoon::modelAddTextureSourceRect()\n\n");
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelAddTextureSourceRect()\n\n");
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
      sprintf(pErrorString, "LEMoon::modelFocusTextureSourceRect(%d, %d)\n\n", idTexture, idSrcRect);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelFocusTextureSourceRect()\n\n");
    #endif

    result = LE_MDL_NOEXIST;
  }

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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelSetSize()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelSetSize()\n\n");
    #endif
  }

  return factor;
}

int LEMoon::modelAnimateTexture(uint32_t id, uint32_t idTexture, int idStart, int stepsTotal, uint32_t animationDuration)
{
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlAnimateTexture(idTexture, idStart, stepsTotal, animationDuration, this->timestep);

    #ifdef LE_DEBUG
      this->printErrorDialog(result, "LEMoon::modelAnimateTexture()\n\n");
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelAnimateTexture()\n\n");
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelAnimateTextureRepeat(uint32_t id, uint32_t idTexture, int idStart, uint8_t direction, uint32_t animationDuration)
{
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlAnimateTextureRepeat(idTexture, idStart, direction, animationDuration, this->timestep);

    #ifdef LE_DEBUG
      this->printErrorDialog(result, "LEMoon::modelAnimateTextureRepeat()\n\n");
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelAnimateTextureRepeat()\n\n");
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelResetTextureAnimation(uint32_t id, uint32_t idTexture)
{
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem != nullptr)
  {
    result = pElem->pModel->mdlResetTextureAnimation(idTexture);

    #ifdef LE_DEBUG
      this->printErrorDialog(result, "LEMoon::modelResetTextureAnimation()\n\n");
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelResetTextureAnimation()\n\n");
    #endif

    result = LE_MDL_NOEXIST;
  }

  return result;
}

int LEMoon::modelSetZindex(uint32_t id, uint32_t zindex)
{
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);
  LEModel * pCurrent = nullptr;

  if(zindex == 0)
  {
    #ifdef LE_DEBUG
    this->printErrorDialog(LE_INVALID_ZINDEX, "LEMoon::modelSetZindex()\n\n");
    #endif

    result = LE_INVALID_ZINDEX;
  }

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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelSetZindex()\n\n");
    #endif

    result = LE_MDL_NOEXIST;
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
      this->printErrorDialog(result, "LEMoon::modelSetTextureZindex()\n\n");
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelSetTextureZindex()\n\n");
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
      this->printErrorDialog(result, "LEMoon::modelSetTextureActive()\n\n");
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelSetTextureActive()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelSetPosition()\n\n");
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
      this->printErrorDialog(result, "LEMoon::modelAddDirection()\n\n");
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelAddDirection()\n\n");
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
      this->printErrorDialog(result, "LEMoon::modelMoveDirection()\n\n");
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelMoveDirection()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelRotate()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelRotateOnce()\n\n");
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
    {result = pElem->pModel->mdlSetTextureAlpha(idTexture, alpha);}
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelSetTextureAlpha()\n\n");
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
    {result = pElem->pModel->mdlFadeTexture(idTexture, alphaPerSecond, this->timestep);}
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelFadeTexture()\n\n");
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
      this->printErrorDialog(result, "LEMoon::modelRotateDir()\n\n");
    #endif
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelRotateDir()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelGetSize()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelGetPosition()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelGetPosition()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelGetTextureAlpha()\n\n");
    #endif
  }

  return alpha;
}

bool LEMoon::modelGetTextureAnimationState(uint32_t id, uint32_t idTexture)
{
  bool animationEnd = LE_FALSE;
  LEModel * pElem = this->modelGet(id);

  if(pElem != nullptr)
    {animationEnd = pElem->pModel->mdlGetTextureAnimationState(idTexture);}
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelGetTextureAnimationState()\n\n");
    #endif
  }

  return animationEnd;
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelSetSizeFactor()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelGetSizeFactor()\n\n");
    #endif
  }

  return sizeFactor;
}

int LEMoon::modelCreateSurface(uint32_t id, uint32_t idTexture, const char * pFile)
{
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem != nullptr)
    {result = pElem->pModel->mdlCreateSurface(idTexture, pFile);}
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelCreateSurface()\n\n");
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
    {result = pElem->pModel->mdlDeleteSurface(idTexture);}
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelDeleteSurface()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelGetSurface()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelGetPixelRGBA()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelGetDirection()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelGetFrameBox()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelGetCollisionBox()\n\n");
    #endif
  }

  return collisionBox;
}

int LEMoon::modelChangeDirection(uint32_t id, uint32_t idDirection, glm::vec2 dir)
{
  int result = LE_NO_ERROR;
  LEModel * pElem = this->modelGet(id);

  if(pElem != nullptr)
    {result = pElem->pModel->mdlChangeDirection(idDirection, dir);}
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelGetDirection()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelSetVisible()\n\n");
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
    {result = pElem->pModel->mdlCreateClone(idClone);}
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelCreateClone()\n\n");
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
    {result = pElem->pModel->mdlSetClonePosition(idClone, position);}
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelSetClonePosition()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelClearClones()\n\n");
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
    {result = pElem->pModel->mdlSetCloneVisible(idClone, visible);}
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelSetCloneVisible()\n\n");
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
    {result = pElem->pModel->mdlAddCollisionRect(idCollRect, collRect);}
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelAddCollisionRect()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelCheckFrameBoxCollision()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelCheckCollision()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelGetAmountOfCollisionBoxes()\n\n");
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
      this->printErrorDialog(LE_MDL_NOEXIST, "LEMoon::modelGetAmountOfTextureSourceRectangles()\n\n");
    #endif
  }

  return amount;
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
      this->printErrorDialog(LE_TIMEEVENT_EXIST, "LEMoon::timeEventCreate()\n\n");
    #endif

    result = LE_TIMEEVENT_EXIST;
  }

  return result;
}

int LEMoon::timeEventDelete(uint32_t id)
{
  int result = LE_NO_ERROR;
  LETimeEvent * pElem = this->timeEventGet(id);
  #ifdef LE_DEBUG
  char * pErrorString = new char[256 + 1];
  #endif

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
      sprintf(pErrorString, "LEMoon::timeEventDelete(%d)\n\n", id);
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
  #ifdef LE_DEBUG
  char * pErrorString = new char[256 + 1];
  #endif

  if(pElem != nullptr)
  {
    if(pElem->timestamp <= this->timestamp)
      {pElem->reached = LE_TRUE;}
  }
  else
  {
    #ifdef LE_DEBUG
      sprintf(pErrorString, "LEMoon::timeEventReached(%d)\n\n", id);
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
  #ifdef LE_DEBUG
  char * pErrorString = new char[256 + 1];
  #endif

  if(pElem != nullptr)
  {
    pElem->timestamp = ntimestamp;
    pElem->reached = LE_FALSE;
  }
  else
  {
    #ifdef LE_DEBUG
      sprintf(pErrorString, "LEMoon::timeEventReset(%d)\n\n", id);
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
    this->printErrorDialog(LE_TIMEEVENT_NOEXIST, "LEMoon::timeEventUpdate()\n\n");
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
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_POINT_EXIST, "LEMoon::pointCreate()\n\n");
    #endif

    result = LE_POINT_EXIST;
  }

  return result;
}

int LEMoon::pointDelete(uint32_t id)
{
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
      this->printErrorDialog(LE_POINT_NOEXIST, "LEMoon::pointDelete()\n\n");
    #endif

    result = LE_POINT_NOEXIST;
  }

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
      this->printErrorDialog(LE_POINT_NOEXIST, "LEMoon::pointSetColor()\n\n");
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
      this->printErrorDialog(LE_POINT_NOEXIST, "LEMoon::pointSetPosition()\n\n");
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
      this->printErrorDialog(LE_POINT_NOEXIST, "LEMoon::pointGetColor()\n\n");
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
      this->printErrorDialog(LE_POINT_NOEXIST, "LEMoon::pointFade()\n\n");
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
      this->printErrorDialog(LE_POINT_NOEXIST, "LEMoon::pointRotate()\n\n");
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
      this->printErrorDialog(LE_POINT_NOEXIST, "LEMoon::pointSetVisible()\n\n");
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
        this->printErrorDialog(LE_DIRECTION_EXIST, "LEMoon::pointAddDirection()\n\n");
      #endif

      result = LE_DIRECTION_EXIST;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_POINT_NOEXIST, "LEMoon::pointAddDirection()\n\n");
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
        this->printErrorDialog(LE_DIRECTION_NOEXIST, "LEMoon::pointMoveDirection()\n\n");
      #endif

      result = LE_DIRECTION_NOEXIST;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_POINT_NOEXIST, "LEMoon::pointMoveDirection()\n\n");
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
      this->printErrorDialog(LE_POINT_NOEXIST, "LEMoon::pointGetPosition()\n\n");
    #endif
  }

  return position;
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
      this->printErrorDialog(LE_SOUND_EXIST, "LEMoon::soundCreate()\n\n");
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
      this->printErrorDialog(LE_SOUND_NOEXIST, "LEMoon::soundDelete()\n\n");
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
          this->printErrorDialog(LE_LOAD_WAV, "LEMoon::soundLoadWAV()\n\n");
        #endif

        result = LE_LOAD_WAV; 
      }
    }
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_SOUND_NOEXIST, "LEMoon::soundLoadWAV()\n\n");
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
          this->printErrorDialog(LE_PLAY_CHANNEL, "LEMoon::soundPlay()\n\n");
        #endif

        result = LE_PLAY_CHANNEL;
      }
    }
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_SOUND_NOEXIST, "LEMoon::soundPlay()\n\n");
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
      this->printErrorDialog(LE_SOUND_NOEXIST, "LEMoon::soundLock()\n\n");
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
      this->printErrorDialog(LE_SOUND_NOEXIST, "LEMoon::soundFadeIn()\n\n");
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
  int result = LE_NO_ERROR;
  LEText * pNew = this->textGet(id);
  #ifdef LE_DEBUG
    char * pErrorString = new char[256 + 1];
  #endif

  if(pNew == nullptr)
  {
    if(this->pTextHead == nullptr)
    {
      this->pTextHead = new LEText;
      this->pTextHead->pLeft = this->pTextHead;
      this->pTextHead->pRight = this->pTextHead;
      this->pTextHead->zindex = 0;
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
      sprintf(pErrorString, "LEMoon::textCreate(%d)\n\n", id);
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
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textDelete()\n\n");
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
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textAddLetter()\n\n");
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
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textSubmit()\n\n");
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
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textSetColor()\n\n");
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
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textSetVisible()\n\n");
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

  if(zindex == 0)
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_INVALID_ZINDEX, "LEMoon::textSetZindex()\n\n");
    #endif

    result = LE_INVALID_ZINDEX;
  }

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
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textSetZindex()\n\n");
    #endif

    result = LE_TEXT_NOEXIST;	
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
        this->printErrorDialog(LE_FONT_NOEXIST, "LEMoon::textRelateFont()\n\n");
      #endif

      result = LE_FONT_NOEXIST;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textRelateFont()\n\n");
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
                  this->printErrorDialog(LE_SDL_BLENDMODE, "LEMoon::textPrepareForDrawing()\n\n");
                #endif

                result = LE_SDL_BLENDMODE;
              }
            }
            else
            {
              #ifdef LE_DEBUG
                this->printErrorDialog(LE_SDL_TEXTURE_LOAD, "LEMoon::textPrepareForDrawing()\n\n");
              #endif

              result = LE_SDL_TEXTURE_LOAD;
            }
          }
          else
          {
            #ifdef LE_DEBUG
              this->printErrorDialog(LE_SDL_HINT, "LEMoon::textPrepareForDrawing()\n\n");
            #endif

            result = LE_SDL_HINT;
          }
        }
        else
        {
          #ifdef LE_DEBUG
            this->printErrorDialog(LE_RENDER_TEXT_BLENDED, "LEMoon::textPrepareForDrawing()\n\n");
          #endif

          result = LE_RENDER_TEXT_BLENDED;
        }
      }
      else
      {
        #ifdef LE_DEBUG
          this->printErrorDialog(LE_TEXT_RELATE_FONT, "LEMoon::textPrepareForDrawing()\n\n");
        #endif

        result = LE_TEXT_RELATE_FONT;
      }
    }
    else
    {
      #ifdef LE_DEBUG
        this->printErrorDialog(LE_TEXT_NOSUBMIT, "LEMoon::textPrepareForDrawing()\n\n");
      #endif

      result = LE_TEXT_NOSUBMIT;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textPrepareForDrawing()\n\n");
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
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textSetPosition()\n\n");
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
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textAddString()\n\n");
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
        this->printErrorDialog(LE_ALPHA_MOD, "LEMoon::textSetAlpha()\n\n");
      #endif

      result = LE_ALPHA_MOD;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textSetAlpha()\n\n");
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
        this->printErrorDialog(LE_ALPHA_MOD, "LEMoon::textFade()\n\n");
      #endif

      result = LE_ALPHA_MOD;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textFade()\n\n");
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
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textClear()\n\n");
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
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textGetAlpha()\n\n");
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
        this->printErrorDialog(LE_DIRECTION_EXIST, "LEMoon::textAddDirection()\n\n");
      #endif

      result = LE_DIRECTION_EXIST;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textAddDirection()\n\n");
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
      pText->position.x += pDirection->data.x * this->timestep;
      pText->position.y += pDirection->data.y * this->timestep;
      pText->posSize.x = (int) pText->position.x;
      pText->posSize.y = (int) pText->position.y;
    }
    else
    {
      #ifdef LE_DEBUG
        this->printErrorDialog(LE_DIRECTION_NOEXIST, "LEMoon::textMoveDirection()\n\n");
      #endif

      result = LE_DIRECTION_NOEXIST;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textMoveDirection()\n\n");
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
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textGetPosition()\n\n");
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
      this->printErrorDialog(LE_TEXT_NOEXIST, "LEMoon::textGetSize()\n\n");
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
        this->printErrorDialog(LE_OPEN_FONT, "LEMoon::fontCreateTTF()\n\n");
      #endif

      result = LE_OPEN_FONT;
    }
  }
  else
  {
    #ifdef LE_DEBUG
      this->printErrorDialog(LE_FONT_EXIST, "LEMoon::fontCreateTTF()\n\n");
    #endif

    result = LE_FONT_EXIST;
  }

  return result;
}

int LEMoon::fontDelete(uint32_t id)
{
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
      this->printErrorDialog(LE_FONT_NOEXIST, "LEMoon::fontDelete()\n\n");
    #endif

    result = LE_FONT_NOEXIST;
  }

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
      this->printErrorDialog(LE_FONT_NOEXIST, "LEMoon::fontSetStyle()\n\n");
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
      this->printErrorDialog(result, "LEMoon::lineCreate()\n\n");
    #endif
  }

  return result;
}

int LEMoon::lineDelete(uint32_t id)
{
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
      this->printErrorDialog(result, "LEMoon::lineDelete()\n\n");
    #endif
  }

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
      this->printErrorDialog(result, "LEMoon::lineSet()\n\n");
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
      this->printErrorDialog(result, "LEMoon::lineSetColor()\n\n");
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

  if(pLine != nullptr)
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
      this->printErrorDialog(result, "LEMoon::lineSetZindex()\n\n");
    #endif
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
      this->printErrorDialog(result, "LEMoon::videoCreate()\n\n");
    #endif
  }

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
      this->printErrorDialog(LE_VIDEO_NOEXIST, "LEMoon::videoPlay()\n\n");
    #endif
  }

  return endPlaying;
}

int LEMoon::videoDelete(uint32_t id)
{
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
      this->printErrorDialog(LE_VIDEO_NOEXIST, "LEMoon::videoDelete()\n\n");
    #endif

    result = LE_VIDEO_NOEXIST;
  }

  return result;
}
