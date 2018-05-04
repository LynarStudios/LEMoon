/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Ubuntu 16.04 LTS, g++ Compiler
  date:               11.04.2018
  updated:            03.05.2018
*/

#ifndef H_LE_MUTEX
#define H_LE_MUTEX

#include <mutex>
using namespace std;

struct LEMutexFont
{
  // general

  mutex originalList;
  mutex bufferList;

  // public

  mutex fontCreateTTF;
  mutex fontDelete;
  mutex fontPrintBufferList;
  mutex fontPrintList;
  mutex fontSetStyle;
  mutex fontUsingThread;

  // locked by merge

  bool fontCreateTTFLockedByMerge;
  bool fontDeleteLockedByMerge;
};

struct LEMutexGeneral
{
  // private

  mutex printErrorDialog;

  // public
};

struct LEMutexLine
{
  // general

  mutex originalList;
  mutex bufferList;

  // public

  mutex lineCreate;
  mutex lineDelete;
  mutex linePrintBufferList;
  mutex linePrintList;
  mutex lineSet;
  mutex lineSetColor;
  mutex lineSetVisible;
  mutex lineSetZindex;
  mutex lineUsingThread;

  // locked by merge

  bool lineCreateLockedByMerge;
  bool lineDeleteLockedByMerge;
  bool lineSetZindexLockedByMerge;

  // locked by setZindex

  bool originalLockedBySetZindex;
  bool bufferLockedBySetZindex;
};

struct LEMutexModel
{
  // general

  mutex originalList;
  mutex bufferList;

  // public

  mutex modelAddCollisionRect;
  mutex modelAddDirection;
  mutex modelAddTextureSourceRect;
  mutex modelChangeDirection;
  mutex modelCheckCollision;
  mutex modelCheckFrameBoxCollision;
  mutex modelClearClones;
  mutex modelCreate;
  mutex modelCreateClone;
  mutex modelCreateSurface;
  mutex modelCreateTexture;
  mutex modelDelete;
  mutex modelDeleteSurface;
  mutex modelFadeTexture;
  mutex modelFocusTextureSourceRect;
  mutex modelGetAmountOfCollisionBoxes;
  mutex modelGetAmountOfTextureSourceRectangles;
  mutex modelGetCollisionBox;
  mutex modelGetDirection;
  mutex modelGetFrameBox;
  mutex modelGetPixelRGBA;
  mutex modelGetPositionD;
  mutex modelGetPosition;
  mutex modelGetSize;
  mutex modelGetSizeFactor;
  mutex modelGetSurface;
  mutex modelGetTextureAlpha;
  mutex modelGetVisible;
  mutex modelGetZindex;
  mutex modelMoveDirection;
  mutex modelPrintBufferList;
  mutex modelPrintList;
  mutex modelRotate;
  mutex modelRotateDir;
  mutex modelRotateOnce;
  mutex modelSetClonePosition;
  mutex modelSetCloneVisible;
  mutex modelSetPosition;
  mutex modelSetSize;
  mutex modelSetSizeFactor;
  mutex modelSetTextureActive;
  mutex modelSetTextureAlpha;
  mutex modelSetTextureZindex;
  mutex modelSetVisible;
  mutex modelSetZindex;
  mutex modelTextureExists;
  mutex modelUsingThread;

  // locked by merge

  bool modelCreateLockedByMerge;
  bool modelDeleteLockedByMerge;
  bool modelSetZindexLockedByMerge;

  // locked by setZindex

  bool originalLockedBySetZindex;
  bool bufferLockedBySetZindex;
};

struct LEMutexPoint
{
  // general

  mutex originalList;
  mutex bufferList;

  // public

  mutex pointAddDirection;
  mutex pointCreate;
  mutex pointDelete;
  mutex pointFade;
  mutex pointGetColor;
  mutex pointGetPosition;
  mutex pointMoveDirection;
  mutex pointPrintBufferList;
  mutex pointPrintList;
  mutex pointRotate;
  mutex pointSetColor;
  mutex pointSetPosition;
  mutex pointSetVisible;
  mutex pointSetZindex;
  mutex pointUsingThread;

  // locked by merge

  bool pointCreateLockedByMerge;
  bool pointDeleteLockedByMerge;
  bool pointSetZindexLockedByMerge;

  // locked by setZindex

  bool originalLockedBySetZindex;
  bool bufferLockedBySetZindex;
};

struct LEMutexSound
{
  // general

  mutex originalList;
  mutex bufferList;

  // public

  mutex soundCreate;
  mutex soundDelete;
  mutex soundFadeIn;
  mutex soundFadeOut;
  mutex soundLoadWAV;
  mutex soundLock;
  mutex soundPause;
  mutex soundPlay;
  mutex soundPrintBufferList;
  mutex soundPrintList;
  mutex soundSetVolume;
  mutex soundUsingThread;

  // locked by merge

  bool soundCreateLockedByMerge;
  bool soundDeleteLockedByMerge;
};

struct LEMutexText
{
  // general

  mutex originalList;
  mutex bufferList;

  // public

  mutex textAddDirection;
  mutex textAddLetter;
  mutex textAddString;
  mutex textClear;
  mutex textCreate;
  mutex textDelete;
  mutex textFade;
  mutex textGetAlpha;
  mutex textGetPosition;
  mutex textGetSize;
  mutex textGetVisible;
  mutex textMoveDirection;
  mutex textPrepareForDrawing;
  mutex textPrintBufferList;
  mutex textPrintList;
  mutex textRelateFont;
  mutex textSetAlpha;
  mutex textSetColor;
  mutex textSetPosition;
  mutex textSetVisible;
  mutex textSetZindex;
  mutex textSubmit;
  mutex textUsingThread;

  // locked by merge

  bool textCreateLockedByMerge;
  bool textDeleteLockedByMerge;
  bool textSetZindexLockedByMerge;

  // locked by setZindex

  bool originalLockedBySetZindex;
  bool bufferLockedBySetZindex;
};

struct LEMutexTimeEvent
{
  // general

  mutex originalList;
  mutex bufferList;

  // public

  mutex timeEventCreate;
  mutex timeEventDelete;
  mutex timeEventGetStamp;
  mutex timeEventPrintBufferList;
  mutex timeEventPrintList;
  mutex timeEventReached;
  mutex timeEventReset;
  mutex timeEventUpdate;
  mutex timeEventUpdateValidALL;
  mutex timeEventUsingThread;

  // locked by merge

  bool timeEventCreateLockedByMerge;
  bool timeEventDeleteLockedByMerge;
};

#endif