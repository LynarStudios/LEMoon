/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Ubuntu 16.04 LTS, g++ Compiler
  date:               18.05.2017
  updated:            29.12.2017
*/

#ifndef H_LE_MOON
#define H_LE_MOON

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <string.h>
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "theoraplay.h"
#include "le_error.h"
#include "le_glb.h"
#include "le_model.h"
#include "le_math.h"
#include "sys/stat.h"
#include "errno.h"

typedef struct sLEMoonModel
{
  sLEMoonModel * pLeft;
  sLEMoonModel * pRight;
  uint32_t id;
  uint32_t zindex;                                                                            // zindex, niedriger zindex wird zuerst gemalt 
  bool visible;
  LEMdl * pModel;
} LEModel;

typedef struct sLETimeEvent
{
  sLETimeEvent * pLeft;
  sLETimeEvent * pRight;
  uint32_t id;
  uint32_t timestamp;
  bool reached;
} LETimeEvent;

typedef struct sLEKeyboard
{
  uint8_t key0;
  uint8_t key1;
  uint8_t key2;
  uint8_t key3;
  uint8_t key4;
  uint8_t key5;
  uint8_t key6;
  uint8_t key7;
  uint8_t key8;
  uint8_t key9;
  uint8_t keyA;
  uint8_t keyACBack;
  uint8_t keyACBookmarks;
  uint8_t keyACForward;
  uint8_t keyACHome;
  uint8_t keyACRefresh;
  uint8_t keyACSearch;
  uint8_t keyACStop;
  uint8_t keyAgain;
  uint8_t keyAltErase; // all done

  uint8_t keyApplication;
  uint8_t keyAudioMute;
  uint8_t keyAudioNext;
  uint8_t keyAudioPlay;
  uint8_t keyAudioPrev;
  uint8_t keyAudioStop;
  uint8_t keyB;
  uint8_t keyBackslash;
  uint8_t keyBackspace;
  uint8_t keyBrightnessDown;

  uint8_t keyBrightnessUp;
  uint8_t keyC;
  uint8_t keyCalculator;
  uint8_t keyCancel;
  uint8_t keyCapsLock;
  uint8_t keyClear;
  uint8_t keyClearAgain;
  uint8_t keyComputer;
  uint8_t keyCopy;
  uint8_t keyCrSel;

  uint8_t keyCurrencySubUnit;
  uint8_t keyCurrencyUnit;
  uint8_t keyCut;
  uint8_t keyD;
  uint8_t keyDecimalSeparator;
  uint8_t keyDelete;
  uint8_t keyDisplaySwitch;
  uint8_t keyDown; // done
  uint8_t keyE;
  uint8_t keyEject;

  uint8_t keyEnd;
  uint8_t keyEquals;
  uint8_t keyEscape;  // done
  uint8_t keyExecute;
  uint8_t keyExSel;
  uint8_t keyF;
  uint8_t keyF1;
  uint8_t keyF2;
  uint8_t keyF3;
  uint8_t keyF4;

  uint8_t keyF5;
  uint8_t keyF6;
  uint8_t keyF7;
  uint8_t keyF8;
  uint8_t keyF9;
  uint8_t keyF10;
  uint8_t keyF11;
  uint8_t keyF12;
  uint8_t keyF13;
  uint8_t keyF14;

  uint8_t keyF15;
  uint8_t keyF16;
  uint8_t keyF17;
  uint8_t keyF18;
  uint8_t keyF19;
  uint8_t keyF20;
  uint8_t keyF21;
  uint8_t keyF22;
  uint8_t keyF23;
  uint8_t keyF24;

  uint8_t keyFind;
  uint8_t keyG;
  uint8_t keyBackquote;
  uint8_t keyH;
  uint8_t keyHelp;
  uint8_t keyHome;
  uint8_t keyI;
  uint8_t keyInsert;
  uint8_t keyJ;
  uint8_t keyK;

  uint8_t keyKBDillumDown;
  uint8_t keyKBDillumToggle;
  uint8_t keyKBDillumUp;
  uint8_t keyKeypad0;
  uint8_t keyKeypad00;
  uint8_t keyKeypad000;
  uint8_t keyKeypad1;
  uint8_t keyKeypad2;
  uint8_t keyKeypad3;
  uint8_t keyKeypad4;

  uint8_t keyKeypad5;
  uint8_t keyKeypad6;
  uint8_t keyKeypad7;
  uint8_t keyKeypad8;
  uint8_t keyKeypad9;
  uint8_t keyKeypadA;
  uint8_t keyKeypadAnd;
  uint8_t keyKeypadAt;
  uint8_t keyKeypadB;
  uint8_t keyKeypadBackspace;

  uint8_t keyKeypadBinary;
  uint8_t keyKeypadC;
  uint8_t keyKeypadClear;
  uint8_t keyKeypadClearEntry;
  uint8_t keyKeypadColon;
  uint8_t keyKeypadComma;
  uint8_t keyKeypadD;
  uint8_t keyKeypadDoubleAnd;
  uint8_t keyKeypadDoubleOr;
  uint8_t keyKeypadDecimal;

  uint8_t keyKeypadDivide;
  uint8_t keyKeypadE;
  uint8_t keyKeypadEnter;
  uint8_t keyKeypadEquals;
  uint8_t keyKeypadEqualsAS400;
  uint8_t keyKeypadExclamation;
  uint8_t keyKeypadF;
  uint8_t keyKeypadGreater;
  uint8_t keyKeypadHash;
  uint8_t keyKeypadHexadecimal;

  uint8_t keyKeypadLeftBrace;
  uint8_t keyKeypadLeftParen;
  uint8_t keyKeypadLess;
  uint8_t keyKeypadMemAdd;
  uint8_t keyKeypadMemClear;
  uint8_t keyKeypadMemDivide;
  uint8_t keyKeypadMemMultiply;
  uint8_t keyKeypadMemRecall;
  uint8_t keyKeypadMemStore;
  uint8_t keyKeypadMemSubtract;

  uint8_t keyKeypadMinus;
  uint8_t keyKeypadMultiply;
  uint8_t keyKeypadOctal;
  uint8_t keyKeypadPercent;
  uint8_t keyKeypadPeriod;
  uint8_t keyKeypadPlus;
  uint8_t keyKeypadPlusMinus;
  uint8_t keyKeypadPower;
  uint8_t keyKeypadRightBrace;
  uint8_t keyKeypadRightParen;

  uint8_t keyKeypadSpace;
  uint8_t keyKeypadTab;
  uint8_t keyKeypadVerticalBar;
  uint8_t keyKeypadXOR;
  uint8_t keyL;
  uint8_t keyLeftAlt;
  uint8_t keyLeftCtrl;
  uint8_t keyLeft;  // done
  uint8_t keyLeftBracket;
  uint8_t keyLeftGUI;

  uint8_t keyLeftShift;
  uint8_t keyM;
  uint8_t keyMail;
  uint8_t keyMediaSelect;
  uint8_t keyMenu;
  uint8_t keyMinus;
  uint8_t keyModeSwitch;
  uint8_t keyMute;
  uint8_t keyN;
  uint8_t keyNumLock;

  uint8_t keyO;
  uint8_t keyOper;
  uint8_t keyOut;
  uint8_t keyPageDown;
  uint8_t keyPageUp;
  uint8_t keyPaste;
  uint8_t keyPause;
  uint8_t keyPeriod;
  uint8_t keyPower;
  uint8_t keyPrintScreen;

  uint8_t keyPrior;
  uint8_t keyQ;
  uint8_t keyR;
  uint8_t keyRightAlt;
  uint8_t keyRightCtrl;
  uint8_t keyReturn; // done
  uint8_t keyReturn2;
  uint8_t keyRightGUI;
  uint8_t keyRight; //done
  uint8_t keyRightBracket;

  uint8_t keyRightShift;
  uint8_t keyS;
  uint8_t keyScrollLock;
  uint8_t keySelect;
  uint8_t keySemicolon;
  uint8_t keySeparator;
  uint8_t keySlash;
  uint8_t keySleep;
  uint8_t keySpace; // done
  uint8_t keyStop;

  uint8_t keySysReq;
  uint8_t keyT;
  uint8_t keyTab;
  uint8_t keyThousandsSeparator;
  uint8_t keyU;
  uint8_t keyUndo;
  uint8_t keyUp; // done
  uint8_t keyV;
  uint8_t keyVolumeDown;
  uint8_t keyVolumeUp;

  uint8_t keyW;
  uint8_t keyWWW;
  uint8_t keyX;
  uint8_t keyY;
  uint8_t keyZ;
} LEKeyboard;

typedef struct sLEMouse
{
  int mouseX;
  int mouseY;
  uint8_t leftButton;
  uint8_t rightButton;
} LEMouse;

typedef struct sLEPoint
{
  uint32_t id;
  SDL_Point point;
  double posX;
  double posY;
  SDL_Point pointBuffer;
  Color color;
  double currentAlpha;
  double currentDegree;
  bool visible;
  LinkedVec2 * pDirectionHead;
  sLEPoint * pLeft;
  sLEPoint * pRight;
} LEPoint;

typedef struct sLESound
{
  uint32_t id;
  Mix_Chunk * pSample;
  bool lock;
  sLESound * pLeft;
  sLESound *pRight;
} LESound;

typedef struct sLELetter
{
  uint8_t letter;
  sLELetter * pLeft;
  sLELetter * pRight;
} LELetter;

typedef struct sLEFont
{
  uint32_t id;
  TTF_Font * pFont;
  sLEFont * pLeft;
  sLEFont * pRight;
} LEFont;

typedef struct sLEText
{
  uint32_t id;
  LELetter * pCurrentCursorPosition;
  LELetter * pLetterHead;
  unsigned char * pText;																																			// der Fliesstext, um ihn auszugeben
  uint32_t length;
  uint32_t zindex;
  bool visible;
  Color color;
  LEFont * pFont;
  SDL_Texture * pTexture;
  SDL_Rect posSize;
  double alpha;
  LinkedVec2 * pDirectionHead;                                                                // Liste mit Richtungsvektoren
  glm::vec2 position;                                                                         // genauere Position fuer Bewegungsberechnungen
  sLEText * pLeft;
  sLEText * pRight;
} LEText;

typedef struct sLEFPS
{
  uint16_t framesPerSecond;                                                                   // hier werden die FPS gezaehlt
  uint32_t countToTime;                                                                       // der Zeitpunkt, bis zu dem gezaehlt werden soll
  uint16_t lastFPS;                                                                           // die FPS der letzten Sekunde
  bool recentFPS;                                                                             // sagt aus, ob es neue FPS der letzten Sekunde gibt
} FPS;

typedef struct sLELine
{
  uint32_t id;
  Line line;
  uint32_t zindex;
  Color color;
  bool visible;
  sLELine * pLeft;
  sLELine * pRight;
} LELine;

typedef struct sLEMemory
{
  LEModel * pLastModel;
  LESound * pLastSound;
  LETimeEvent * pLastTimeEvent;
  LEPoint * pLastPoint;
  LEFont * pLastFont;
  LEText * pLastText;
  LELine * pLastLine;
} LEMemory;

typedef struct sLEVideo
{
  uint32_t id;
  char * pFile;
  sLEVideo * pLeft;
  sLEVideo * pRight;
} LEVideo;

typedef struct sLEWindow
{
  bool focusGained;
} LEWindow;

typedef class LEMoon
{
  private:

    bool initialized;
    SDL_Window * pWindow;
    SDL_DisplayMode displayMode;
    SDL_Event event;
    SDL_Renderer * pRenderer;
    uint32_t timestamp;
    double timestep;
    LEModel * pModelHead;
    LETimeEvent * pTimeEventHead;
    LEKeyboard keyboard;                                                                      // keyboard 0 = inactive, 1 = pressed, 2 = released
    LEMouse mouse;                                                                            // mouse 0 = inactive, 1 = pressed, 2 = released
    LEPoint * pPointHead;                                                                     // Liste mit Punkten
    Color backgroundColor;                                                                    // Hintergrundfarbe
    LESound * pSoundHead;                                                                     // Liste mit Sounds
    LEText * pTextHead;																																				                                   // Liste mit Texten
    LEFont * pFontHead;																																				                                   // Liste mit Fonts
    LELine * pLineHead;                                                                       // Liste mit Linien
    LEVideo * pVideoHead;                                                                     // Liste mit Videos
    FPS fps;                                                                                  // frames per second
    LEMemory memory;                                                                          // hier werden Zeiger fuer alle grossen Arten gespeichert, sodass die Suche durch Listen performanter wird
    LEWindow window;                                                                          // diese Struktur speichert verschiedene Zustaende des Fenster
    char * prefPath;                                                                          // der Pfad wo Dateien geschrieben werden koennen

    // memory

    void memoryClearFonts();                                                                  // diese Funktion loescht alle Fonts im Destruktor der Engine
    void memoryClearLines();                                                                  // diese Funktion loescht alle Linien im Destruktor der Engine
    void memoryClearModels();                                                                 // diese Funktion loescht alle Models im Destruktor der Engine
    void memoryClearPoints();                                                                 // diese Funktion loescht alle Punkte im Destruktor der Engine
    void memoryClearSounds();                                                                 // diese Funktion loescht alle Sounds im Destruktor der Engine
    void memoryClearTexts();                                                                  // diese Funktion loescht alle Texturen im Destruktor der Engine
    void memoryClearTimeEvents();                                                             // diese Funktion loescht alle Zeitereignisse im Destruktor der Engine

    // general

    void clearKeyboard();                                                                     // diese Funktion setzt alle Tasten auf 0
    void clearMouse();                                                                        // diese Funktion setzt alle Maustasten auf 0
    int drawWithZindex();                                                                     // diese Funktion zeichnet Objekte (Models / Texte) anhand ihres Zindex
    void freeKeyboardKeys();                                                                  // diese Funktion setzt alle Keys auf inactive, die vorher auf released standen
    void freeMouse();
    void handleKeyboard();                                                                    // diese Funktion haelt alle keyboard events fest
    void handleMouse();                                                                       // diese Funktion haelt alle Mouse events fest
    void printErrorDialog(int, const char*);                                                  // diese Funktion gibt einen Fehler in einem Dialogfenster aus

    // window

    void handleWindow();                                                                      // diese Funktion behandelt das Fenster

    // model

    bool modelCheckCollision(LEModel*, LEModel*);                                             // diese Funktion prueft anhand von Kollisionsbereichen zweier Models, ob sie kollidieren
    bool modelCheckFrameBoxCollision(LEModel*, LEModel*);                                     // diese Funktion prueft, ob zwei Models im groben Kollisionsbereich kollidieren
    int modelDraw(LEModel*);                                                                  // diese Funktion zeichnet ein Model
    LEModel * modelGet(uint32_t);                                                             // diese Funktion gibt eine Modelreferenz anhand einer eindeutigen ID zurueck
    uint32_t modelGetAmount();                                                                // diese Funktion gibt die Anzahl aller Modelle zurueck

    // time

    LETimeEvent * timeEventGet(uint32_t);                                                     // diese Funktion gibt eine Referenz auf ein Zeitereignis zurueck

    // point

    LEPoint * pointGet(uint32_t);                                                             // diese Funktion gibt eine Referenz auf einen Punkt zurueck
    LinkedVec2 * pointGetDirection(LEPoint*, uint32_t);                                       // diese Funktion gibt eine Referenz auf eine Bewegungsrichtung zurueck

    // sound

    LESound * soundGet(uint32_t);                                                             // diese Funktion gibt eine Referenz auf einen Sound zurueck

    // text

    int textDraw(LEText*);                                                                    // diese Funktion zeichnet einen Text
    LEText * textGet(uint32_t);																																                               // diese Funktion gibt eine Referenz auf einen Text zurueck
    uint32_t textGetAmount();                                                                 // diese Funktion gibt die Anzahl aller Texte zurueck
    LinkedVec2 * textGetDirection(LEText*, uint32_t);                                         // diese Funktion gibt die Referenz auf eine Bewegungsrichtung zurueck

    // font

    LEFont * fontGet(uint32_t);																																                               // diese Funktion gibt eine Referenz auf einen Font zurueck

    // line

    int lineDraw(LELine*);                                                                    // diese Funktion malt eine Linie
    LELine * lineGet(uint32_t);                                                               // diese Funktion gibt eine Referenz auf eine Linie zurueck

    // video

    LEVideo * videoGet(uint32_t);                                                             // diese Funktion liefert eine Referenz auf ein Video zurueck

  public:

    LEMoon();
    ~LEMoon();

    // general

    void beginFrame();                                                                        // diese Funktion sollte am Anfang eines Frames in einem main loop erfolgen
    void delay(uint32_t);                                                                     // diese Funktion verzoegert die Anwendung um die angegebene Anzahl an Millisekunden
    int drawFrame();                                                                          // diese Funktion zeichnet ein Frame, sie sollte nach lemoonBeginFrame() und vor lemoonEndFrame() aufgerufen werden
    void endFrame();                                                                          // diese Funktion sollte am Ende eines Frames aufgerufen werden
    bool engineInitialized();                                                                 // diese Funktion gibt ein flag zurueck, das aussagt, ob die Engine gestartet wurde
    Color getBackgroundColor();                                                               // diese Funktion gibt die Hintergrundfarbe zurueck
    uint16_t getFPS();                                                                        // diese Funktion gibt die Anzahl an Frames der letzten Sekunde zurueck
    char * getPrefPath();                                                                     // diese Funktion gibt den externen Pref Pfad zurueck
    int getScreenHeight();                                                                    // diese Funktion gibt die Hoehe der Bildschirmaufloesung zurueck
    int getScreenWidth();                                                                     // diese Funktion gibt die Breite der Bildschirmaufloesung zurueck
    uint32_t getTimestamp();                                                                  // diese Funktion gibt den aktuellen Zeitstempel zurueck
    double getTimestep();                                                                     // diese Funktion gibt die Dauer des letzten Frames zurueck
    int init(int, const char*);                                                               // diese Funktion initialisiert die Engine
    bool keyEvent(uint32_t, SDL_Keycode);                                                     // diese Funktion prueft, ob ein SDL_Keycode (https://wiki.libsdl.org/SDL_Keycode) gedrueckt oder losgelassen wird
    void messageBox(const char*, const char*);                                                // diese Funktion ruft eine Dialogbox auf mit einem gewaehlten Titel und einem gewaehlten Text
    #ifdef LE_LINUX
    int mkpath(const char*, mode_t);                                                          // diese Funktion erstellt einen Pfad unter Linux
    #endif
    bool mouseEvent(uint32_t, uint8_t);                                                       // diese Funktion prueft, ob ein Mousebutton gedrueckt oder losgelassen wurde
    SDL_Point mouseGetPosition();                                                             // diese Funktion gibt die Mausposition zurueck
    double percentToPixelX(double);                                                           // diese Funktion wandelt eine Prozentangabe in eine Pixelgroesse in X Dimension um
    double percentToPixelY(double);                                                           // diese Funktion wandelt eine Prozentangabe in eine Pixelgroesse in Y Dimension um
    double pixelToPercentX(double);                                                           // diese Funktion wandelt eine Pixelangabe in eine Prozentangabe in X Dimension um
    double pixelToPercentY(double);                                                           // diese Funktion wandelt eine Pixelangabe in eine Prozentangabe in Y Dimension um
    int pollEvent();                                                                          // diese Funktion prueft auf events
    void printErrorMessage(const char*, const char*);                                         // diese Funktion ermoeglicht dem Programmierer eine Fehlermeldung in einem Fenster auszugeben
    bool recentFPSAvailable();                                                                // diese Funktion sagt aus, ob aktuelle FPS verfuegbar sind, diese Funktion gibt nur einmal pro Sekunde LE_TRUE zurueck
    double relativeSizeX(double);                                                             // diese Funktion gibt die relative Groesse einer Pixelgroesse in der X-Dimension in Prozent zurueck
    double relativeSizeY(double);                                                             // diese Funktion gibt die relative Groesse einer Pixelgroesse in der Y-Dimension in Prozent zurueck
    void setBackgroundColor(uint8_t, uint8_t, uint8_t);                                       // diese Funktion setzt die Hintergrundfarbe der Anwendung
    int showCursor(bool);                                                                     // diese Funktion versteckt den Cursor (LE_FALSE) oder zeigt ihn (LE_TRUE)

    // window

    bool windowFocused();                                                                     // diese Funktion prueft, ob das Fenster gerade im Focus ist, oder nicht

    // model

    int modelAddCollisionRect(uint32_t, uint32_t, SDL_Rect);                                  // diese Funktion fuegt eine Kollisionsbereich in Form eines Rechteckes hinzu
    int modelAddDirection(uint32_t, uint32_t, glm::vec2);                                     // diese Funktion legt eine Bewegungsrichtung fuer ein Model an
    int modelAddTextureSourceRect(uint32_t, uint32_t, uint32_t, int, int, int, int);          // diese Funktion fuegt einen Texturbereich hinzu aus welchem ausschliesslich gezeichnet werden soll
    int modelAnimateTexture(uint32_t, uint32_t, int, int, uint32_t);                          // DEPRECATED: diese Funktion animiert eine Textur, indem es Texturbereiche nacheinander anzeigt, Parameter 3: id des Texturbereiches, oder LE_CURRENT_SRCRECT, Parameter 4: Anzahl von Texturbereichschritten ab "Parameter 3", positiv fuer vorwaerts, negativ fuer rueckwaerts
    int modelAnimateTextureRepeat(uint32_t, uint32_t, int, uint8_t, uint32_t);                // DEPRECATED: wie modelAnimateTexture(), nur, dass die Animation wiederholt wird, 4. Parameter: LE_FORWARD oder LE_BACKWARD
    int modelChangeDirection(uint32_t, uint32_t, glm::vec2);                                  // diese Funktion aendert eine Bewegungsrichtung
    bool modelCheckCollision(uint32_t, uint32_t);                                             // diese Funktion prueft, ob zwei Models miteinander kollidieren
    bool modelCheckFrameBoxCollision(uint32_t, uint32_t);                                     // diese Funktion prueft, ob die groben Kollisionsbereiche von zwei Models miteinander kollidieren
    int modelClearClones(uint32_t);                                                           // diese Funktion loescht alle Clones des Models
    int modelCreate(uint32_t);                                                                // diese Funktion erzeugt ein Model mit Hilfe einer eindeutigen ID
    int modelCreateClone(uint32_t, uint32_t);                                                 // diese Funktion erstellt einen Clone fuer ein Model
    int modelCreateSurface(uint32_t, uint32_t, const char*);                                  // diese Funktion erstellt ein Surface aus einem Bild, um mit den Pixeldaten direkt arbeiten zu koennen
    int modelCreateTexture(uint32_t, uint32_t, const char*);                                  // diese Funktion erzeugt eine Textur, alle Texturen sollten die selbe Groesse haben, wegen des groben Kollisionsbereiches!
    int modelDelete(uint32_t);                                                                // diese Funktion loescht ein Model wieder
    int modelDeleteSurface(uint32_t, uint32_t);                                               // diese Funktion loescht das Surface einer Textur wieder
    int modelFadeTexture(uint32_t, uint32_t, double);                                         // diese Funktion blendet eine Textur ein oder aus
    int modelFocusTextureSourceRect(uint32_t, uint32_t, uint32_t);                            // diese Funktion setzt den Fokus auf einen Texturbereich, sodass nur dieser gezeichnet werden soll
    uint32_t modelGetAmountOfCollisionBoxes(uint32_t);                                        // diese Funktion gibt die Anzahl an Kollisionsbereichen zurueck
    uint32_t modelGetAmountOfTextureSourceRectangles(uint32_t, uint32_t);                     // diese Funktion gibt die Anzahl an Texturbereichen einer Textur zurueck
    LECollBox_d modelGetCollisionBox(uint32_t, uint32_t);                                     // diese Funktion gibt einen bestimmten Kollisionsbereich zurueck
    glm::vec2 modelGetDirection(uint32_t, uint32_t);                                          // diese Funktion gibt eine Bewegungsrichtung zurueck
    LECollBox_d modelGetFrameBox(uint32_t);                                                   // diese Funktion gibt den groben Kollisionsbereich eines Models zurueck
    Color modelGetPixelRGBA(uint32_t, uint32_t, uint32_t, uint32_t);                          // diese Funktion gibt einen Pixel einer Textur zurueck, modelCreateSurface() muss vorher aufgerufen worden sein
    glm::vec2 modelGetPositionD(uint32_t);                                                    // diese Funktion gibt die genauen Positionswerte des Models zurueck
    SDL_Point modelGetPosition(uint32_t);                                                     // diese Funktion gibt die Position eines Models zurueck
    SDL_Point modelGetSize(uint32_t);                                                         // diese Funktion gibt die Groesse eines Models zurueck
    double modelGetSizeFactor(uint32_t);                                                      // diese Funktion gibt den Faktor der Modelgroesse zurueck
    SDL_Surface * modelGetSurface(uint32_t, uint32_t);                                        // diese Funktion gibt einen Zeiger auf ein erstelltes Surface zurueck
    double modelGetTextureAlpha(uint32_t, uint32_t);                                          // diese Funktion gibt den Alphawert einer Textur zurueck
    bool modelGetTextureAnimationState(uint32_t, uint32_t);                                   // diese Funktion sagt aus, ob eine Texturanimation beendet wurde oder nicht true = beendet, false = nicht beendet
    int modelMoveDirection(uint32_t, uint32_t);                                               // diese Funktion bewegt ein Model in eine vorher angelegte Richtung
    int modelResetTextureAnimation(uint32_t, uint32_t);                                       // diese Funktion setzt eine Texturanimation wieder zurueck
    int modelRotate(uint32_t, double);                                                        // diese Funktion rotiert ein Model um die angegebene Gradzahl pro Sekunde
    int modelRotateDir(uint32_t, uint32_t, double);                                           // diese Funktion rotiert eine Bewegungsrichtung um eine angegebene Gradzahl pro Sekunde
    int modelRotateOnce(uint32_t, double);                                                    // diese Funktion rotiert ein Model einmalig
    int modelSetClonePosition(uint32_t, uint32_t, glm::vec2);                                 // diese Funktion setzt die Position eines Model Clones
    int modelSetCloneVisible(uint32_t, uint32_t, bool);                                       // diese Funktion macht einen Clone eines Models sichtbar oder unsichtbar
    int modelSetPosition(uint32_t, double, double);                                           // diese Funktion setzt die Position eines Models in NDC
    int modelSetSize(uint32_t, int, int);                                                     // diese Funktion legt die Groesse des Models fest
    double modelSetSize(uint32_t, double);                                                    // diese Funktion legt die Groesse des Models in Prozent fest und gibt den Vergroesserungsfaktor zurueck, der dabei entsteht
    int modelSetSizeFactor(uint32_t, double);                                                 // diese Funktion setzt den Faktor der Modelgroesse
    int modelSetTextureActive(uint32_t, uint32_t, bool);                                      // diese Funktion left fest, ob eine Textur sichtbar ist, oder nicht
    int modelSetTextureAlpha(uint32_t, uint32_t, uint8_t);                                    // diese Funktion setzt einen Alphawert fuer eine Textur
    int modelSetTextureZindex(uint32_t, uint32_t, uint32_t);                                  // diese Funktion setzt den zindex einer Textur innerhalb eines Models
    int modelSetVisible(uint32_t, bool);                                                      // diese Funktion setzt ein Model auf sichtbar oder unsichtbar
    int modelSetZindex(uint32_t, uint32_t);                                                   // diese Funktion setzt den zindex eines Models, 0 nicht erlaubt

    // time

    int timeEventCreate(uint32_t, uint32_t);                                                  // diese Funktion erstellt ein Zeitereignis
    int timeEventDelete(uint32_t);                                                            // diese Funktion loescht ein Zeitereignis
    uint32_t timeEventGetStamp(uint32_t);                                                     // diese Funktion gibt den Zeitstempel fuer das Zeitereignis zurueck
    bool timeEventReached(uint32_t);                                                          // diese Funktion prueft, ob ein Zeitereignis bereits erreicht wurde
    int timeEventReset(uint32_t, uint32_t);                                                   // diese Funktion setzt den Wert eines Zeitereignisses neu
    int timeEventUpdate(uint32_t, uint32_t);                                                  // diese Funktion verlaengert ein Zeitereignis um eine Anzahl von Millisekunden
    void timeEventUpdateValidALL(uint32_t);                                                   // diese Funktion verlaengert alle noch nicht erreichten Zeitereignisse um eine Anzahl von Millisekunden

    // point

    int pointAddDirection(uint32_t, uint32_t, glm::vec2);                                     // diese Funktion fuegt eine Bewegungsrichtung hinzu
    int pointCreate(uint32_t);                                                                // diese Funktion fuegt einen Punkt hinzu
    int pointDelete(uint32_t);                                                                // diese Funktion loescht einen Punkt
    int pointFade(uint32_t, double);                                                          // diese Funktion blendet einen Punkt ein oder aus
    Color pointGetColor(uint32_t);                                                            // diese Funktion gibt die Farbe eines Punktes zurueck
    SDL_Point pointGetPosition(uint32_t);                                                     // diese Funktion gibt die Position eines Punktes zurueck
    int pointMoveDirection(uint32_t, uint32_t);                                               // diese Funktion bewegt einen Punkt in eine zuvor erstelle Bewegungsrichtung
    int pointRotate(uint32_t, double, SDL_Point);                                             // diese Funktion laesst einen Punkt um einen bestimmten Punkt rotieren
    int pointSetColor(uint32_t, uint8_t, uint8_t, uint8_t, uint8_t);                          // diese Funktion legt die Farbe eines Punktes fest
    int pointSetPosition(uint32_t, int, int);                                                 // diese Funktion setzt die Position eines Punktes
    int pointSetVisible(uint32_t, bool);                                                      // diese Funktion macht einen Punkt sichtbar oder unsichtbar

    // sound

    int soundCreate(uint32_t);                                                                // diese Funktion fuegt einen Sound hinzu
    int soundDelete(uint32_t);                                                                // diese Funktion loescht einen Sound
    int soundFadeIn(uint32_t, int);                                                           // diese Funktion blendet einen Kanal oder alle Kanaele ein
    void soundFadeOut(int);                                                                   // diese Funktion blendet einen Kanal oder alle Kanaele aus
    int soundLoadWAV(uint32_t, const char*);                                                  // diese Funktion laedt eine WAV Datei fuer einen erstellten Sound
    int soundLock(uint32_t, bool);                                                            // diese Funktion sperrt einen Sound, sodass er hier nach nicht wieder gespielt wird, bis er entsperrt ist
    void soundPause();                                                                        // diese Funktion pausiert einen Sound
    int soundPlay(uint32_t, int);                                                             // diese Funktion spielt einen Sound ab
    void soundSetVolume(uint8_t);                                                             // diese Funktion setzt die Lautstaerke

		  // text

    int textAddDirection(uint32_t, uint32_t, glm::vec2);                                      // diese Funktion fuegt einem Text eine Bewegungsrichtung hinzu
    int textAddLetter(uint32_t, uint8_t);																											                          // diese Funktion fuegt einen Buchstaben an das Ende hinzu
    int textAddString(uint32_t, const char*);                                                 // diese Funktion fuegt einen kompletten String dem Text hinzu
    int textClear(uint32_t);                                                                  // diese Funktion loescht den kompletten Text
    int textCreate(uint32_t);																																	                                // diese Funktion fuegt einen UTF8 Text hinzu
    int textDelete(uint32_t);																																	                                // diese Funktion loescht einen Text
    int textFade(uint32_t, double);                                                           // diese Funktion blendet einen Text ein oder aus
    double textGetAlpha(uint32_t);                                                            // diese Funktion gibt den Alpha Wert eines Textes zurueck
    SDL_Point textGetPosition(uint32_t);                                                      // diese Funktion gibt die Position des Textes zurueck
    SDL_Point textGetSize(uint32_t);                                                          // diese Funktion gibt die Dimensionen des Textes zurueck
    bool textGetVisible(uint32_t);                                                            // diese Funktion prueft, ob ein Text sichtbar ist
    int textMoveDirection(uint32_t, uint32_t);                                                // diese Funktion bewegt eine Text in eine zuvor erstellte Bewegungsrichtung
    int textPrepareForDrawing(uint32_t);                                                      // diese Funktion bereitet einen Text auf das Zeichnen vor, ein Text kann anschliessend gezeichnet werden
    int textRelateFont(uint32_t, uint32_t);                                                   // diese Funktion ordnet dem Text einen Font zu, muss vor textPrepareForDrawing() aufgerufen werden
    int textSetAlpha(uint32_t, uint8_t);                                                      // diese Funktion setzt den Alphawert eines Textes, muss nach textPrepareForDrawing() aufgerufen werden!
    int textSetColor(uint32_t, uint8_t, uint8_t, uint8_t, uint8_t);														             // diese Funktion setzt die Farbe eines Textes, muss vor textPrepareForDrawing() aufgerufen werden
    int textSetPosition(uint32_t, int, int);                                                  // diese Funktion setzt die Position eines Textes
    int textSetVisible(uint32_t, bool);                                                       // diese Funktion sagt aus, ob ein Text sichtbar ist, oder nicht
    int textSetZindex(uint32_t, uint32_t);                                                    // diese Funktion setzt den z-index fuer einen Text, 0 nicht erlaubt
    int textSubmit(uint32_t);																																	                                // diese Funktion erstellt aus allen Buchstaben einen Text

    // font

    int fontCreateTTF(uint32_t, const char*, int);																						                      // diese Funktion fuegt einen Font hinzu
    int fontDelete(uint32_t);																																	                                // diese Funktion loescht einen Font
    int fontSetStyle(uint32_t, int);                                                          // diese Funktion setzt den Stil des Fonts, TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE, TTF_STYLE_STRIKETHROUGH

    // line

    int lineCreate(uint32_t);                                                                 // diese Funktion erstellt eine Linie
    int lineDelete(uint32_t);                                                                 // diese Funktion loescht eine Linie
    int lineSet(uint32_t, int, int, int, int);                                                // diese Funktion setzt die Linie
    int lineSetColor(uint32_t, uint8_t, uint8_t, uint8_t, uint8_t);                           // diese Funktion setzt die Farbe einer Linie
    int lineSetVisible(uint32_t, bool);                                                       // diese Funktion setzt eine Linie auf sichtbar oder unsichtbar
    int lineSetZindex(uint32_t, uint32_t);                                                    // diese Funktion setzt den Zindex fuer eine Linie, 0 nicht erlaubt

    // video

    int videoCreate(uint32_t, const char*);                                                   // diese Funktion erstellt ein Video
    int videoDelete(uint32_t);                                                                // diese Funktion loescht ein Video
    bool videoPlay(uint32_t);                                                                 // diese Funktion legt fest, ob ein Video gespielt wird oder nicht
} *LEMoonInstance;

#endif
