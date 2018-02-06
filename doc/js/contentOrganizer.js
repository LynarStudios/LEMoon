function newTab(url)
{
  var win = window.open(url, '_blank');
  win.focus();
}

function loadSite()
{
  var hashString = window.location.hash.substring(1);

  if(hashString == '' || hashString == 'index')
    {loadDiv('navDiv');}

  //////////////////////////////////
  // LINKS
  //////////////////////////////////

  if(hashString == 'links')
    {loadDiv('linksDiv');}

  //////////////////////////////////
  // FONT
  //////////////////////////////////

  if(hashString == 'font')
    {loadDiv('fontDiv');}
  if(hashString == 'fCreate')
    {loadDiv('fCreateDiv');}
  if(hashString == 'fDelete')
    {loadDiv('fDeleteDiv');}
  if(hashString == 'fSetStyle')
    {loadDiv('fSetStyleDiv');}

  //////////////////////////////////
  // GENERAL
  //////////////////////////////////

  if(hashString == 'general')
    {loadDiv('generalDiv');}
  if(hashString == 'gBeginFrame')
    {loadDiv('gBeginFrameDiv');}
  if(hashString == 'gConvertResHeight')
    {loadDiv('gConvertResHeightDiv');}
  if(hashString == 'gConvertResWidth')
    {loadDiv('gConvertResWidthDiv');}
  if(hashString == 'gDelay')
    {loadDiv('gDelayDiv');}
  if(hashString == 'gDrawFrame')
    {loadDiv('gDrawFrameDiv');}
  if(hashString == 'gEndFrame')
    {loadDiv('gEndFrameDiv');}
  if(hashString == 'gEngineInitialized')
    {loadDiv('gEngineInitializedDiv');}
  if(hashString == 'gGetBackgroundColor')
    {loadDiv('gGetBackgroundColorDiv');}
  if(hashString == 'gGetFPS')
    {loadDiv('gGetFPSDiv');}
  if(hashString == 'gGetPrefPath')
    {loadDiv('gGetPrefPathDiv');}
  if(hashString == 'gGetScreenHeight')
    {loadDiv('gGetScreenHeightDiv');}
  if(hashString == 'gGetScreenWidth')
    {loadDiv('gGetScreenWidthDiv');}
  if(hashString == 'gGetTimestamp')
    {loadDiv('gGetTimestampDiv');}
  if(hashString == 'gGetTimestep')
    {loadDiv('gGetTimestepDiv');}
  if(hashString == 'gInit')
    {loadDiv('gInitDiv');}
  if(hashString == 'gInitImage')
    {loadDiv('gInitImageDiv');}
  if(hashString == 'gInitSound')
    {loadDiv('gInitSoundDiv');}
  if(hashString == 'gInitTTF')
    {loadDiv('gInitTTFDiv');}
  if(hashString == 'gKeyEvent')
    {loadDiv('gKeyEventDiv');}
  if(hashString == 'gMessageBox')
    {loadDiv('gMessageBoxDiv');}
  if(hashString == 'gMkpath')
    {loadDiv('gMkpathDiv');}
  if(hashString == 'gMouseEvent')
    {loadDiv('gMouseEventDiv');}
  if(hashString == 'gMouseGetPosition')
    {loadDiv('gMouseGetPositionDiv');}
  if(hashString == 'gPercentToPixelX')
    {loadDiv('gPercentToPixelXDiv');}
  if(hashString == 'gPercentToPixelY')
    {loadDiv('gPercentToPixelYDiv');}
  if(hashString == 'gPixelToPercentX')
    {loadDiv('gPixelToPercentXDiv');}
  if(hashString == 'gPixelToPercentY')
    {loadDiv('gPixelToPercentYDiv');}
  if(hashString == 'gPollEvent')
    {loadDiv('gPollEventDiv');}
  if(hashString == 'gPrintErrorMessage')
    {loadDiv('gPrintErrorMessageDiv');}
  if(hashString == 'gRecentFPSAvailable')
    {loadDiv('gRecentFPSAvailableDiv');}
  if(hashString == 'gSetBackgroundColor')
    {loadDiv('gSetBackgroundColorDiv');}
  if(hashString == 'gShowCursor')
    {loadDiv('gShowCursorDiv');}

  //////////////////////////////////
  // LINE
  //////////////////////////////////

  if(hashString == 'line')
    {loadDiv('lineDiv');}
  if(hashString == 'lCreate')
    {loadDiv('lCreateDiv');}
  if(hashString == 'lDelete')
    {loadDiv('lDeleteDiv');}
  if(hashString == 'lSet')
    {loadDiv('lSetDiv');}
  if(hashString == 'lSetColor')
    {loadDiv('lSetColorDiv');}
  if(hashString == 'lSetVisible')
    {loadDiv('lSetVisibleDiv');}
  if(hashString == 'lSetZindex')
    {loadDiv('lSetZindexDiv');}

  //////////////////////////////////
  // MODEL
  //////////////////////////////////

  if(hashString == 'model')
    {loadDiv('modelDiv');}
  if(hashString == 'mAddDirection')
    {loadDiv('mAddDirectionDiv');}
  if(hashString == 'mAddCollisionRect')
    {loadDiv('mAddCollisionRectDiv');}
  if(hashString == 'mAddTextureSourceRect')
    {loadDiv('mAddTextureSourceRectDiv');}
  if(hashString == 'mChangeDirection')
    {loadDiv('mChangeDirectionDiv');}
  if(hashString == 'mCheckCollision')
    {loadDiv('mCheckCollisionDiv');}
  if(hashString == 'mCheckFrameBoxCollision')
    {loadDiv('mCheckFrameBoxCollisionDiv');}
  if(hashString == 'mClearClones')
    {loadDiv('mClearClonesDiv');}
  if(hashString == 'mCreate')
    {loadDiv('mCreateDiv');}
  if(hashString == 'mCreateClone')
    {loadDiv('mCreateCloneDiv');}
  if(hashString == 'mCreateSurface')
    {loadDiv('mCreateSurfaceDiv');}
  if(hashString == 'mCreateTexture')
    {loadDiv('mCreateTextureDiv');}
  if(hashString == 'mDelete')
    {loadDiv('mDeleteDiv');}
  if(hashString == 'mDeleteSurface')
    {loadDiv('mDeleteSurfaceDiv');}
  if(hashString == 'mFadeTexture')
    {loadDiv('mFadeTextureDiv');}
  if(hashString == 'mFocusTextureSourceRect')
    {loadDiv('mFocusTextureSourceRectDiv');}
  if(hashString == 'mGetAmountOfCollisionBoxes')
    {loadDiv('mGetAmountOfCollisionBoxesDiv');}
  if(hashString == 'mGetAmountOfTextureSourceRectangles')
    {loadDiv('mGetAmountOfTextureSourceRectanglesDiv');}
  if(hashString == 'mGetCollisionBox')
    {loadDiv('mGetCollisionBoxDiv');}
  if(hashString == 'mGetDirection')
    {loadDiv('mGetDirectionDiv');}
  if(hashString == 'mGetFrameBox')
    {loadDiv('mGetFrameBoxDiv');}
  if(hashString == 'mGetPixelRGBA')
    {loadDiv('mGetPixelRGBADiv');}
  if(hashString == 'mGetPositionD')
    {loadDiv('mGetPositionDDiv');}
  if(hashString == 'mGetPosition')
    {loadDiv('mGetPositionDiv');}
  if(hashString == 'mGetSize')
    {loadDiv('mGetSizeDiv');}
  if(hashString == 'mGetSizeFactor')
    {loadDiv('mGetSizeFactorDiv');}
  if(hashString == 'mGetSurface')
    {loadDiv('mGetSurfaceDiv');}
  if(hashString == 'mGetTextureAlpha')
    {loadDiv('mGetTextureAlphaDiv');}
  if(hashString == 'mGetVisible')
    {loadDiv('mGetVisibleDiv');}
  if(hashString == 'mGetZindex')
    {loadDiv('mGetZindexDiv');}
  if(hashString == 'mMoveDirection')
    {loadDiv('mMoveDirectionDiv');}
  if(hashString == 'mRotate')
    {loadDiv('mRotateDiv');}
  if(hashString == 'mRotateDir')
    {loadDiv('mRotateDirDiv');}
  if(hashString == 'mRotateOnce')
    {loadDiv('mRotateOnceDiv');}
  if(hashString == 'mSetClonePosition')
    {loadDiv('mSetClonePositionDiv');}
  if(hashString == 'mSetCloneVisible')
    {loadDiv('mSetCloneVisibleDiv');}
  if(hashString == 'mSetPosition')
    {loadDiv('mSetPositionDiv');}
  if(hashString == 'mSetSize')
    {loadDiv('mSetSizeDiv');}
  if(hashString == 'mSetSizeFactor')
    {loadDiv('mSetSizeFactorDiv');}
  if(hashString == 'mSetTextureActive')
    {loadDiv('mSetTextureActiveDiv');}
  if(hashString == 'mSetTextureAlpha')
    {loadDiv('mSetTextureAlphaDiv');}
  if(hashString == 'mSetTextureZindex')
    {loadDiv('mSetTextureZindexDiv');}
  if(hashString == 'mSetVisible')
    {loadDiv('mSetVisibleDiv');}
  if(hashString == 'mSetZindex')
    {loadDiv('mSetZindexDiv');}
  if(hashString == 'mTextureExists')
    {loadDiv('mTextureExistsDiv');}

  //////////////////////////////////
  // POINT
  //////////////////////////////////

  if(hashString == 'point')
    {loadDiv('pointDiv');}
  if(hashString == 'pAddDirection')
    {loadDiv('pAddDirectionDiv');}
  if(hashString == 'pCreate')
    {loadDiv('pCreateDiv');}
  if(hashString == 'pDelete')
    {loadDiv('pDeleteDiv');}
  if(hashString == 'pFade')
    {loadDiv('pFadeDiv');}
  if(hashString == 'pGetColor')
    {loadDiv('pGetColorDiv');}
  if(hashString == 'pGetPosition')
    {loadDiv('pGetPositionDiv');}
  if(hashString == 'pMoveDirection')
    {loadDiv('pMoveDirectionDiv');}
  if(hashString == 'pRotate')
    {loadDiv('pRotateDiv');}
  if(hashString == 'pSetColor')
    {loadDiv('pSetColorDiv');}
  if(hashString == 'pSetPosition')
    {loadDiv('pSetPositionDiv');}
  if(hashString == 'pSetVisible')
    {loadDiv('pSetVisibleDiv');}
  if(hashString == 'pSetZindex')
    {loadDiv('pSetZindexDiv');}

  //////////////////////////////////
  // SOUND
  //////////////////////////////////

  if(hashString == 'sound')
    {loadDiv('soundDiv');}
  if(hashString == 'sCreate')
    {loadDiv('sCreateDiv');}
  if(hashString == 'sDelete')
    {loadDiv('sDeleteDiv');}
  if(hashString == 'sFadeIn')
    {loadDiv('sFadeInDiv');}
  if(hashString == 'sFadeOut')
    {loadDiv('sFadeOutDiv');}
  if(hashString == 'sLoadWAV')
    {loadDiv('sLoadWAVDiv');}
  if(hashString == 'sLock')
    {loadDiv('sLockDiv');}
  if(hashString == 'sPause')
    {loadDiv('sPauseDiv');}
  if(hashString == 'sPlay')
    {loadDiv('sPlayDiv');}
  if(hashString == 'sSetVolume')
    {loadDiv('sSetVolumeDiv');}

  //////////////////////////////////
  // TEXT
  //////////////////////////////////

  if(hashString == 'text')
    {loadDiv('textDiv');}
  if(hashString == 'tAddDirection')
    {loadDiv('tAddDirectionDiv');}
  if(hashString == 'tAddLetter')
    {loadDiv('tAddLetterDiv');}
  if(hashString == 'tAddString')
    {loadDiv('tAddStringDiv');}
  if(hashString == 'tClear')
    {loadDiv('tClearDiv');}
  if(hashString == 'tCreate')
    {loadDiv('tCreateDiv');}
  if(hashString == 'tDelete')
    {loadDiv('tDeleteDiv');}
  if(hashString == 'tFade')
    {loadDiv('tFadeDiv');}
  if(hashString == 'tGetAlpha')
    {loadDiv('tGetAlphaDiv');}
  if(hashString == 'tGetPosition')
    {loadDiv('tGetPositionDiv');}
  if(hashString == 'tGetSize')
    {loadDiv('tGetSizeDiv');}
  if(hashString == 'tGetVisible')
    {loadDiv('tGetVisibleDiv');}
  if(hashString == 'tMoveDirection')
    {loadDiv('tMoveDirectionDiv');}
  if(hashString == 'tPrepareForDrawing')
    {loadDiv('tPrepareForDrawingDiv');}
  if(hashString == 'tRelateFont')
    {loadDiv('tRelateFontDiv');}
  if(hashString == 'tSetAlpha')
    {loadDiv('tSetAlphaDiv');}
  if(hashString == 'tSetColor')
    {loadDiv('tSetColorDiv');}
  if(hashString == 'tSetPosition')
    {loadDiv('tSetPositionDiv');}
  if(hashString == 'tSetVisible')
    {loadDiv('tSetVisibleDiv');}
  if(hashString == 'tSetZindex')
    {loadDiv('tSetZindexDiv');}
  if(hashString == 'tSubmit')
    {loadDiv('tSubmitDiv');}

  //////////////////////////////////
  // TIME EVENT
  //////////////////////////////////

  if(hashString == 'timeevent')
    {loadDiv('timeEventDiv');}
  if(hashString == 'teCreate')
    {loadDiv('teCreateDiv');}
  if(hashString == 'teDelete')
    {loadDiv('teDeleteDiv');}
  if(hashString == 'teGetStamp')
    {loadDiv('teGetStampDiv');}
  if(hashString == 'teReached')
    {loadDiv('teReachedDiv');}
  if(hashString == 'teReset')
    {loadDiv('teResetDiv');}
  if(hashString == 'teUpdate')
    {loadDiv('teUpdateDiv');}
  if(hashString == 'teUpdateValidALL')
    {loadDiv('teUpdateValidALLDiv');}

  //////////////////////////////////
  // VIDEO
  //////////////////////////////////

  if(hashString == 'video')
    {loadDiv('videoDiv');}
  if(hashString == 'vCreate')
    {loadDiv('vCreateDiv');}
  if(hashString == 'vDelete')
    {loadDiv('vDeleteDiv');}
  if(hashString == 'vPlay')
    {loadDiv('vPlayDiv');}

  //////////////////////////////////
  // WINDOW
  //////////////////////////////////

  if(hashString == 'window')
    {loadDiv('windowDiv');}
  if(hashString == 'wFocused')
    {loadDiv('wFocusedDiv');}
}

function loadDiv(divName)
  {document.getElementById('content').innerHTML = document.getElementById(divName).innerHTML;}

function goBack()
  {window.history.back();}