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
      char * pErrorString = new char[256 + 1];
      sprintf(pErrorString, "LEMoon::videoCreate(%u)\n\n", id);
      this->printErrorDialog(result, pErrorString);
      delete [] pErrorString;
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

  return result;
}