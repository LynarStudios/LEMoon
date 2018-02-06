/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Ubuntu 16.04 LTS, g++ Compiler
  date:               18.05.2017
  updated:            29.01.2018
*/

#ifndef H_LE_ERROR
#define H_LE_ERROR

#define LE_NO_ERROR                             0         // no error
#define LE_SDL_INIT                             1         // SDL_init() failed
#define LE_SDL_WINDOW                           2         // SDL_CreateWindow() failed
#define LE_SDL_DISPLAYMODE                      3         // SDL_GetCurrentDisplayMode() failed
#define LE_SDL_RENDERER                         4         // SDL_CreateRenderer() failed
#define LE_SDL_DRAW_COLOR                       5         // SDL_SetRenderDrawColor() failed
#define LE_SDL_CLEAR_RENDERER                   6         // SDL_RenderClear() failed
#define LE_SDL_SHOW_CURSOR                      7         // SDL_ShowCursor() failed
#define LE_MDL_EXIST                            8         // Model ID already exists
#define LE_MDL_NOEXIST                          9         // Model ID does not exist
#define LE_TEXTURE_EXIST                        12        // Texture ID already exists
#define LE_TEXTURE_NOEXIST                      13        // Texture ID does not exist
#define LE_IMG_LOAD                             14        // unable to load image
#define LE_SDL_TEXTURE_LOAD                     15        // SDL_CreateTextureFromSurface() failed
#define LE_SDL_IMG_INIT                         16        // IMG_Init() failed
#define LE_SDL_RENDER_COPY_EX                   17        // SDL_RenderCopy() failed
#define LE_SOURCE_RECT_EXIST                    18        // id for source rect already exists
#define LE_SOURCE_RECT_NOEXIST                  19        // id for source rect does not exist
#define LE_SOURCE_RECT_ANIMATION_NOEXIST        20        // couldn't find any source rectangles for animation
#define LE_TIMEEVENT_NOEXIST                    21        // time event id does not exist
#define LE_TIMEEVENT_EXIST                      22        // time event id already exists
#define LE_SDL_BLENDMODE                        23        // SDL_SetTextureBlendMode() failed
#define LE_DIRECTION_NOEXIST                    24        // id for direction does not exist
#define LE_DIRECTION_EXIST                      25        // id for direction already exists
#define LE_ALPHA_MOD                            26        // SDL_SetTextureAlphaMod() failed
#define LE_POINT_NOEXIST                        27        // id for point does not exist
#define LE_POINT_EXIST                          28        // id for point already exists
#define LE_DRAW_POINT                           29        // SDL_RenderDrawPoint() failed
#define LE_DRAW_BLEND_MODE                      30        // SDL_SetRenderDrawBlendMode() failed
#define LE_MIXER_INIT                           31        // Mix_Init() failed
#define LE_OPEN_AUDIO                           32        // Mix_OpenAudio() failed
#define LE_SOUND_EXIST                          33        // id for sound already exists
#define LE_SOUND_NOEXIST                        34        // id for sound does not exist
#define LE_LOAD_WAV                             35        // Mix_LoadWAV() failed
#define LE_ALLOC_CHANNELS                       36        // Mix_AllocateChannels() failed
#define LE_PLAY_CHANNEL                         37        // Mix_PlayChannel() failed
#define LE_TEXT_NOEXIST                         38        // id for text does not exist
#define LE_TEXT_EXIST                           39        // id for text already exists
#define LE_TTF_INIT                             40        // TTF_Init() failed
#define LE_FONT_EXIST                           41        // id for font already exists
#define LE_FONT_NOEXIST                         42        // id for font does not exist
#define LE_OPEN_FONT                            43        // TTF_OpenFont() failed
#define LE_TEXT_NOSUBMIT                        44        // textSubmit() has not been called yet
#define LE_TEXT_RELATE_FONT                     45        // textRelateFont() has not been called yet
#define LE_RENDER_TEXT_BLENDED                  46        // TTF_RenderUTF8_Blended() failed
#define LE_INVALID_ZINDEX                       47        // zindex ist 0
#define LE_MDL_CLONE_NOEXIST                    48        // id for model clone does not exist
#define LE_MDL_CLONE_EXIST                      49        // id for model clone already exists
#define LE_LINE_NOEXIST                         50        // id for line does not exist
#define LE_LINE_EXIST                           51        // id for line already exists
#define LE_SDL_DRAW_LINE                        52        // SDL_RenderDrawLine() failed
#define LE_MDL_COLL_RECT_EXIST                  53        // id for model collision rectangle already exists
#define LE_MDL_COLL_RECT_NOEXIST                54        // id for model collision rectangle does not exist
#define LE_VIDEO_EXIST                          55        // id for video already exists
#define LE_VIDEO_NOEXIST                        56        // id for video does not exist
#define LE_SDL_HINT                             57        // SDL_SetHint() failed
#define LE_INIT_SUBSYSTEM                       58        // SDL_InitSubSystem failed

#endif
