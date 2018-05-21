/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Ubuntu 16.04 LTS, g++ Compiler
  date:               18.05.2017
  updated:            21.05.2018

  NOTES:              (TS) = thread safe
*/

#ifndef H_LE_MOON
#define H_LE_MOON

#define SDL_MAIN_HANDLED
#include "SDL_mixer.h"
#include "SDL_ttf.h"
//#include "theoraplay.h"
#include "le_mdl.h"
#include "le_mutex.h"
#include "le_keyboard.h"

typedef struct sLEMoonModel
{
  sLEMoonModel * pLeft;
  sLEMoonModel * pRight;
  uint32_t id;
  uint32_t zindex;                                                                            // zindex, niedriger zindex wird zuerst gemalt 
  bool visible;
  bool markedAsDelete;
  LEMdl * pModel;
} LEModel;

typedef struct sLETimeEvent
{
  sLETimeEvent * pLeft;
  sLETimeEvent * pRight;
  uint32_t id;
  uint32_t timestamp;
  bool reached;
  bool markedAsDelete;
} LETimeEvent;

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
  uint32_t zindex;
  bool markedAsDelete;
  mutex direction;
  LinkedVec2 * pDirectionHead;
  sLEPoint * pLeft;
  sLEPoint * pRight;
} LEPoint;

typedef struct sLESound
{
  uint32_t id;
  Mix_Chunk * pSample;
  bool lock;
  bool markedAsDelete;
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
  bool markedAsDelete;
  TTF_Font * pFont;
  sLEFont * pLeft;
  sLEFont * pRight;
} LEFont;

typedef struct sLEText
{
  uint32_t id;
  LELetter * pCurrentCursorPosition;
  LELetter * pLetterHead;
  unsigned char * pText;																																			                                   // der Fliesstext, um ihn auszugeben
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
  bool markedAsDelete;
  mutex direction;
  mutex letter;
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
  bool markedAsDelete;
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

    //////////////////////////////
    // threading
    //////////////////////////////

    LEMutexFont mtxFont;
    LEMutexGeneral mtxGeneral;
    LEMutexLine mtxLine;
    LEMutexModel mtxModel;
    LEMutexPoint mtxPoint;
    LEMutexSound mtxSound;
    LEMutexText mtxText;
    LEMutexTimeEvent mtxTimeEvent;

    Notify notifyFont;                                                                        // sagt aus, ob Listen sich veraendert haben, und die Engine das merkt, oder der Nutzer die Listen veraendern moechte
    Notify notifyLine;                                                                        // sagt aus, ob Listen sich veraendert haben, und die Engine das merkt, oder der Nutzer die Listen veraendern moechte
    Notify notifyModel;                                                                       // sagt aus, ob Listen sich veraendert haben, und die Engine das merkt, oder der Nutzer die Listen veraendern moechte
    Notify notifyPoint;                                                                       // sagt aus, ob Listen sich veraendert haben, und die Engine das merkt, oder der Nutzer die Listen veraendern moechte
    Notify notifySound;                                                                       // sagt aus, ob Listen sich veraendert haben, und die Engine das merkt, oder der Nutzer die Listen veraendern moechte
    Notify notifyText;                                                                        // sagt aus, ob Listen sich veraendert haben, und die Engine das merkt, oder der Nutzer die Listen veraendern moechte
    Notify notifyTimeEvent;                                                                   // sagt aus, ob Listen sich veraendert haben, und die Engine das merkt, oder der Nutzer die Listen veraendern moechte

    //////////////////////////////
    // memory
    //////////////////////////////

    void memoryClearFonts();                                                                  // diese Funktion loescht alle Fonts im Destruktor der Engine
    void memoryClearLines();                                                                  // diese Funktion loescht alle Linien im Destruktor der Engine
    void memoryClearModels();                                                                 // diese Funktion loescht alle Models im Destruktor der Engine
    void memoryClearPoints();                                                                 // diese Funktion loescht alle Punkte im Destruktor der Engine
    void memoryClearSounds();                                                                 // diese Funktion loescht alle Sounds im Destruktor der Engine
    void memoryClearTexts();                                                                  // diese Funktion loescht alle Texturen im Destruktor der Engine
    void memoryClearTimeEvents();                                                             // diese Funktion loescht alle Zeitereignisse im Destruktor der Engine

    // -----------------------------------------------------------------------------------------------------------------------------------------

    //////////////////////////////
    // font
    //////////////////////////////

    LEFont * pFontHead;                                                                       // Liste mit Fonts
    LEFont * pFontHeadBuffer;                                                                 // Liste mit Fonts zum hinzufuegen (threadfaehig)

    void fontCleanList();                                                                     // diese Funktion loescht alle zum loeschen markierte Elemente der Original Liste
    void fontCleanBufferList();                                                               // diese Funktion loescht alle zum loeschen markierte Elemente aus der Bufferliste
    void fontConstructor();                                                                   // diese Funktion wird im LEMoon constructor aufgerufen
    void fontDeleteBufferList();                                                              // diese Funktion loescht die Bufferliste 
    void fontDeleteOriginalList();                                                            // diese Funktion loescht die Originalliste, wenn keine Elemente mehr drin sind
    uint32_t fontGenerateID();                                                                // diese Funktion generiert eine freie ID
    uint32_t fontGenerateIDFromBufferList();                                                  // (TS) diese Funktion versucht in der Buffer Liste eine frei ID zu generieren
    uint32_t fontGenerateIDFromOriginalList();                                                // (TS) diese Funktion versucht in der original Liste eine frei ID zu generieren
    LEFont * fontGet(uint32_t);																																                               // (TS) diese Funktion gibt eine Referenz auf einen Font aus der Original Liste zurueck
    LEFont * fontGetFromBuffer(uint32_t);                                                     // (TS) diese Funktion gibt eine Referenz auf einen Font aus der Buffer Liste zurueck
    int fontMerge();                                                                          // diese Funktion fuegt alle Fonts zusammen aus beiden Listen und loescht die Buffer Liste, ACHTUNG: diese Funktion wird nie aufgerufen, wenn font Funktionen noch in Threads laufen!!!
    void fontMergeLists();                                                                    // diese Funktion fuegt die Original- und die Buffer Liste zusammen

    //////////////////////////////
    // general
    //////////////////////////////

    bool initialized;
    SDL_Window * pWindow;
    SDL_DisplayMode displayMode;
    SDL_Event event;
    SDL_Renderer * pRenderer;
    uint32_t timestamp;
    double timestep;
    LEKeyboard keyboard;                                                                      // keyboard 0 = inactive, 1 = pressed, 2 = released
    LEMouse mouse;                                                                            // mouse 0 = inactive, 1 = pressed, 2 = released
    Color backgroundColor;                                                                    // Hintergrundfarbe
    FPS fps;                                                                                  // frames per second
    LEMemory memory;                                                                          // hier werden Zeiger fuer alle grossen Arten gespeichert, sodass die Suche durch Listen performanter wird
    char * prefPath;                                                                          // der Pfad wo Dateien geschrieben werden koennen

    void clearKeyboard();                                                                     // diese Funktion setzt alle Tasten auf 0
    void clearMouse();                                                                        // diese Funktion setzt alle Maustasten auf 0
    int drawWithZindex();                                                                     // diese Funktion zeichnet Objekte (Models / Texte) anhand ihres Zindex
    void freeKey(uint8_t&);                                                                   // diese Funktion setzt eine Keyboard Taste zurueck
    void freeKeyboardKeys();                                                                  // diese Funktion setzt alle Keys auf inactive, die vorher auf released standen
    void freeMouse();                                                                         // diese Funktion setzt alle Maus Events wieder zurueck
    void handleKeyboard();                                                                    // diese Funktion haelt alle keyboard events fest
    void handleMouse();                                                                       // diese Funktion haelt alle Mouse events fest
    int merge();                                                                              // diese Funktion fuegt die Bufferlisten und die Originallisten zusammen und loescht zum loeschen markierte Elemente
    void printErrorDialog(int, const char*);                                                  // (TS) diese Funktion gibt einen Fehler in einem Dialogfenster aus

    //////////////////////////////
    // line
    //////////////////////////////

    LELine * pLineHead;                                                                       // Originalliste
    LELine * pLineHeadBuffer;                                                                 // Bufferliste

    void lineCleanList();                                                                     // diese Funktion loescht alle zum loeschen markierte Elemente der Original Liste
    void lineCleanBufferList();                                                               // diese Funktion loescht alle zum loeschen markierte Elemente aus der Bufferliste
    void lineConstructor();                                                                   // diese Funktion wird im LEMoon constructor aufgerufen
    void lineDeleteBufferList();                                                              // diese Funktion loescht die Bufferliste 
    void lineDeleteOriginalList();                                                            // diese Funktion loescht die Originalliste, wenn keine Elemente mehr drin sind
    int lineDraw(LELine*);                                                                    // diese Funktion malt eine Linie
    uint32_t lineGenerateID();                                                                // diese Funktion generiert eine freie ID
    uint32_t lineGenerateIDFromBufferList();                                                  // (TS) diese Funktion versucht in der Buffer Liste eine frei ID zu generieren
    uint32_t lineGenerateIDFromOriginalList();                                                // (TS) diese Funktion versucht in der original Liste eine frei ID zu generieren
    LELine * lineGet(uint32_t);                                                               // (TS) diese Funktion gibt eine Referenz auf eine Linie zurueck
    LELine * lineGetFromBuffer(uint32_t);                                                     // (TS) diese Funktion gibt eine Referenz auf eine Linie aus der Buffer Liste zurueck
    int lineMerge();                                                                          // diese Funktion fuegt alle Linien zusammen aus beiden Listen und loescht die Buffer Liste, ACHTUNG: diese Funktion wird nie aufgerufen, wenn Linien Funktionen noch in Threads laufen!!!
    void lineMergeLists();                                                                    // diese Funktion fuegt die Original- und die Buffer Liste zusammen
    void lineSortZindex();                                                                    // diese Funktion sortiert die Elemente nach Z-Index

    //////////////////////////////
    // model
    //////////////////////////////

    LEModel * pModelHead;                                                                     // original list
    LEModel * pModelHeadBuffer;                                                               // buffer list

    bool modelCheckCollision(LEModel*, LEModel*);                                             // diese Funktion prueft anhand von Kollisionsbereichen zweier Models, ob sie kollidieren
    bool modelCheckFrameBoxCollision(LEModel*, LEModel*);                                     // diese Funktion prueft, ob zwei Models im groben Kollisionsbereich kollidieren
    void modelCleanList();                                                                    // diese Funktion loescht alle zum loeschen markierte Elemente der Original Liste
    void modelCleanBufferList();                                                              // diese Funktion loescht alle zum loeschen markierte Elemente aus der Bufferliste
    void modelConstructor();                                                                  // diese Funktion wird im LEMoon constructor aufgerufen
    void modelDeleteBufferList();                                                             // diese Funktion loescht die Bufferliste 
    void modelDeleteOriginalList();                                                           // diese Funktion loescht die Originalliste, wenn keine Elemente mehr drin sind
    int modelDraw(LEModel*);                                                                  // diese Funktion zeichnet ein Model
    uint32_t modelGenerateID();                                                               // diese Funktion generiert eine freie ID
    uint32_t modelGenerateIDFromBufferList();                                                 // (TS) diese Funktion versucht in der Buffer Liste eine frei ID zu generieren
    uint32_t modelGenerateIDFromOriginalList();                                               // (TS) diese Funktion versucht in der original Liste eine frei ID zu generieren
    LEModel * modelGet(uint32_t);                                                             // (TS) diese Funktion gibt eine Modelreferenz anhand einer eindeutigen ID zurueck
    uint32_t modelGetAmount();                                                                // diese Funktion gibt die Anzahl aller Modelle zurueck
    LEModel * modelGetFromBuffer(uint32_t);                                                   // (TS) diese Funktion gibt eine Referenz auf ein Model aus der Buffer Liste zurueck
    int modelMerge();                                                                         // diese Funktion fuegt alle Models zusammen aus beiden Listen und loescht die Buffer Liste, ACHTUNG: diese Funktion wird nie aufgerufen, wenn Model Funktionen noch in Threads laufen!!!
    void modelMergeLists();                                                                   // diese Funktion fuegt die Original- und die Buffer Liste zusammen
    void modelSortZindex();                                                                   // diese Funktion sortiert die Elemente nach Z-Index

    //////////////////////////////
    // point
    //////////////////////////////

    LEPoint * pPointHead;                                                                     // Originalliste
    LEPoint * pPointHeadBuffer;                                                               // Bufferliste

    void pointCleanList();                                                                    // diese Funktion loescht alle zum loeschen markierte Elemente der Original Liste
    void pointCleanBufferList();                                                              // diese Funktion loescht alle zum loeschen markierte Elemente aus der Bufferliste
    void pointConstructor();                                                                  // diese Funktion wird im LEMoon constructor aufgerufen
    void pointDeleteBufferList();                                                             // diese Funktion loescht die Bufferliste 
    void pointDeleteOriginalList();                                                           // diese Funktion loescht die Originalliste, wenn keine Elemente mehr drin sind
    int pointDraw(LEPoint*);                                                                  // diese Funktion malt einen Punkt
    bool pointFinishedAllMutexes(LEPoint*);                                                   // diese Funktion prueft, ob alle Mutexes momentan verfuegbar sind
    uint32_t pointGenerateID();                                                               // diese Funktion generiert eine freie ID
    uint32_t pointGenerateIDFromBufferList();                                                 // (TS) diese Funktion versucht in der Buffer Liste eine frei ID zu generieren
    uint32_t pointGenerateIDFromOriginalList();                                               // (TS) diese Funktion versucht in der original Liste eine frei ID zu generieren
    LEPoint * pointGet(uint32_t);                                                             // (TS) diese Funktion gibt eine Referenz auf einen Punkt zurueck
    LinkedVec2 * pointGetDirection(LEPoint*, uint32_t);                                       // diese Funktion gibt eine Referenz auf eine Bewegungsrichtung zurueck
    LEPoint * pointGetFromBuffer(uint32_t);                                                   // (TS) diese Funktion gibt eine Referenz auf einen Punkt aus der Buffer Liste zurueck
    int pointMerge();                                                                         // diese Funktion fuegt alle Punkte zusammen aus beiden Listen und loescht die Buffer Liste, ACHTUNG: diese Funktion wird nie aufgerufen, wenn Punkte Funktionen noch in Threads laufen!!!
    void pointMergeLists();                                                                   // diese Funktion fuegt die Original- und die Buffer Liste zusammen
    void pointSortZindex();                                                                   // diese Funktion sortiert die Elemente nach Z-Index

    //////////////////////////////
    // sound
    //////////////////////////////

    LESound * pSoundHead;                                                                     // Originalliste mit Sounds
    LESound * pSoundHeadBuffer;                                                               // Bufferliste mit Sounds

    void soundCleanList();                                                                    // diese Funktion loescht alle zum loeschen markierte Elemente der Original Liste
    void soundCleanBufferList();                                                              // diese Funktion loescht alle zum loeschen markierte Elemente aus der Bufferliste
    void soundConstructor();                                                                  // diese Funktion wird im LEMoon constructor aufgerufen
    void soundDeleteBufferList();                                                             // diese Funktion loescht die Bufferliste 
    void soundDeleteOriginalList();                                                           // diese Funktion loescht die Originalliste, wenn keine Elemente mehr vorhanden sind
    uint32_t soundGenerateID();                                                               // diese Funktion generiert eine freie ID
    uint32_t soundGenerateIDFromBufferList();                                                 // (TS) diese Funktion versucht in der Buffer Liste eine frei ID zu generieren
    uint32_t soundGenerateIDFromOriginalList();                                               // (TS) diese Funktion versucht in der original Liste eine frei ID zu generieren
    LESound * soundGet(uint32_t);                                                             // (TS) diese Funktion gibt eine Referenz auf einen Sound zurueck
    LESound * soundGetFromBuffer(uint32_t);                                                   // (TS) diese Funktion gibt eine Referenz auf einen Sound aus der Buffer Liste zurueck
    int soundMerge();                                                                         // diese Funktion fuegt alle Sounds zusammen aus beiden Listen und loescht die Buffer Liste, ACHTUNG: diese Funktion wird nie aufgerufen, wenn Sound Funktionen noch in Threads laufen!!!
    void soundMergeLists();                                                                   // diese Funktion fuegt die Original- und die Buffer Liste zusammen

    //////////////////////////////
    // text
    //////////////////////////////

    LEText * pTextHead;                                                                       // Liste mit Texten
    LEText * pTextHeadBuffer;                                                                 // Buffer Liste

    void textCleanList();                                                                     // diese Funktion loescht alle zum loeschen markierte Elemente der Original Liste
    void textCleanBufferList();                                                               // diese Funktion loescht alle zum loeschen markierte Elemente aus der Bufferliste
    void textConstructor();                                                                   // diese Funktion wird im LEMoon constructor aufgerufen
    void textDeleteBufferList();                                                              // diese Funktion loescht die Bufferliste 
    void textDeleteOriginalList();                                                            // diese Funktion loescht die Originalliste, wenn keine Elemente mehr drin sind
    int textDraw(LEText*);                                                                    // diese Funktion zeichnet einen Text
    bool textFinishedAllMutexes(LEText*);                                                     // diese Funktion prueft, ob alle Mutexes momentan verfuegbar sind
    uint32_t textGenerateID();                                                                // diese Funktion generiert eine freie ID
    uint32_t textGenerateIDFromBufferList();                                                  // (TS) diese Funktion versucht in der Buffer Liste eine frei ID zu generieren
    uint32_t textGenerateIDFromOriginalList();                                                // (TS) diese Funktion versucht in der original Liste eine frei ID zu generieren
    LEText * textGet(uint32_t);                                                               // (TS) diese Funktion gibt eine Referenz auf einen Text zurueck
    uint32_t textGetAmount();                                                                 // diese Funktion gibt die Anzahl aller Texte zurueck
    LinkedVec2 * textGetDirection(LEText*, uint32_t);                                         // diese Funktion gibt die Referenz auf eine Bewegungsrichtung zurueck
    LEText * textGetFromBuffer(uint32_t);                                                     // (TS) diese Funktion gibt eine Referenz auf einen Text aus der Buffer Liste zurueck
    int textMerge();                                                                          // diese Funktion fuegt alle Texte zusammen aus beiden Listen und loescht die Buffer Liste, ACHTUNG: diese Funktion wird nie aufgerufen, wenn Text Funktionen noch in Threads laufen!!!
    void textMergeLists();                                                                    // diese Funktion fuegt die Original- und die Buffer Liste zusammen
    void textSortZindex();                                                                    // diese Funktion sortiert die Elemente nach Z-Index

    //////////////////////////////
    // time event
    //////////////////////////////

    LETimeEvent * pTimeEventHead;                                                             // Originalliste
    LETimeEvent * pTimeEventHeadBuffer;                                                       // Bufferliste

    void timeEventCleanList();                                                                // diese Funktion loescht alle zum loeschen markierte Elemente der Original Liste
    void timeEventCleanBufferList();                                                          // diese Funktion loescht alle zum loeschen markierte Elemente aus der Bufferliste
    void timeEventConstructor();                                                              // diese Funktion wird im LEMoon constructor aufgerufen
    void timeEventDeleteBufferList();                                                         // diese Funktion loescht die Bufferliste 
    void timeEventDeleteOriginalList();                                                       // diese Funktion loescht die Originalliste, wenn keine Elemente mehr vorhanden sind
    uint32_t timeEventGenerateID();                                                           // diese Funktion generiert eine freie ID
    uint32_t timeEventGenerateIDFromBufferList();                                             // (TS) diese Funktion versucht in der Buffer Liste eine frei ID zu generieren
    uint32_t timeEventGenerateIDFromOriginalList();                                           // (TS) diese Funktion versucht in der original Liste eine frei ID zu generieren
    LETimeEvent * timeEventGet(uint32_t);                                                     // (TS) diese Funktion gibt eine Referenz auf ein Zeitereignis zurueck
    LETimeEvent * timeEventGetFromBuffer(uint32_t);                                           // (TS) diese Funktion gibt eine Referenz auf ein Zeitereignis aus der Buffer Liste zurueck
    int timeEventMerge();                                                                     // diese Funktion fuegt alle Zeitereignisse zusammen aus beiden Listen und loescht die Buffer Liste, ACHTUNG: diese Funktion wird nie aufgerufen, wenn Zeitereignis Funktionen noch in Threads laufen!!!
    void timeEventMergeLists();                                                               // diese Funktion fuegt die Original- und die Buffer Liste zusammen

    //////////////////////////////
    // video
    //////////////////////////////

    LEVideo * pVideoHead;                                                                     // Liste mit Videos

    LEVideo * videoGet(uint32_t);                                                             // diese Funktion liefert eine Referenz auf ein Video zurueck

    //////////////////////////////
    // window
    //////////////////////////////

    LEWindow window;                                                                          // diese Struktur speichert verschiedene Zustaende des Fenster

    void handleWindow();                                                                      // diese Funktion behandelt das Fenster

  public:

    LEMoon();
    ~LEMoon();

    //////////////////////////////
    // font
    //////////////////////////////

    int fontCreateTTF(uint32_t, const char*, int);                                            // (TS) diese Funktion fuegt einen Font hinzu
    uint32_t fontCreateTTF(const char*, int);                                                 // (TS) diese Funktion erzeugt einen Font mit einer selbst generierten ID, diese wird auch zurueck gegeben!
    int fontDelete(uint32_t);                                                                 // (TS) diese Funktion loescht einen Font
    void fontPrintBufferList();                                                               // (TS) diese Funktion gibt die komplette Font Buffer Liste aus
    void fontPrintList();                                                                     // (TS) diese Funktion gibt die komplette Original Font Liste aus
    int fontSetStyle(uint32_t, int);                                                          // (TS) diese Funktion setzt den Stil des Fonts, TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE, TTF_STYLE_STRIKETHROUGH
    void fontUsingThread(bool);                                                               // (TS) mit dieser Funktion kann der Nutzer festlegen, ob er Font Funktionen in einem Thread benutzen moechte (LE_TRUE) oder diesen Vorgang beendet hat (LE_FALSE)

    //////////////////////////////
    // general
    //////////////////////////////

    void beginFrame();                                                                        // diese Funktion sollte am Anfang eines Frames in einem main loop erfolgen
    double convertResHeight(double, double);                                                  // diese Funktion gibt die relative Y-Pixelgroesse eines Wertes anhand einer Ausgangsbildschirmaufloesung zurueck
    double convertResWidth(double, double);                                                   // diese Funktion gibt die relative X-Pixelgroesse eines Wertes anhand einer Ausgangsbildschirmaufloesung zurueck
    void delay(uint32_t);                                                                     // diese Funktion verzoegert die Anwendung um die angegebene Anzahl an Millisekunden
    int drawFrame();                                                                          // diese Funktion zeichnet ein Frame, sie sollte nach lemoonBeginFrame() und vor lemoonEndFrame() aufgerufen werden
    int endFrame();                                                                           // diese Funktion sollte am Ende eines Frames aufgerufen werden
    bool engineInitialized();                                                                 // diese Funktion gibt ein flag zurueck, das aussagt, ob die Engine gestartet wurde
    Color getBackgroundColor();                                                               // diese Funktion gibt die Hintergrundfarbe zurueck
    uint16_t getFPS();                                                                        // diese Funktion gibt die Anzahl an Frames der letzten Sekunde zurueck
    char * getPrefPath();                                                                     // diese Funktion gibt den externen Pref Pfad zurueck
    int getScreenHeight();                                                                    // diese Funktion gibt die Hoehe der Bildschirmaufloesung zurueck
    int getScreenWidth();                                                                     // diese Funktion gibt die Breite der Bildschirmaufloesung zurueck
    uint32_t getTimestamp();                                                                  // diese Funktion gibt den aktuellen Zeitstempel zurueck
    double getTimestep();                                                                     // diese Funktion gibt die Dauer des letzten Frames zurueck
    int init(const char*);                                                                    // diese Funktion initialisiert die Engine
    int initImage();                                                                          // diese Funktion initialisiert den Bilderteil der Engine
    int initSound(int);                                                                       // diese Funktion initialisiert den Soundteil der Engine
    int initTTF();                                                                            // diese Funktion initialisiert den TTF - Teil der Engine
    bool keyEvent(uint32_t, SDL_Keycode);                                                     // diese Funktion prueft, ob ein SDL_Keycode (https://wiki.libsdl.org/SDL_Keycode) gedrueckt oder losgelassen wird
    void messageBox(const char*, const char*);                                                // diese Funktion ruft eine Dialogbox auf mit einem gewaehlten Titel und einem gewaehlten Text
    #ifdef LE_LINUX
    void mkpath(const char*, mode_t);                                                         // diese Funktion erstellt einen Pfad unter Linux
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
    void setBackgroundColor(uint8_t, uint8_t, uint8_t);                                       // diese Funktion setzt die Hintergrundfarbe der Anwendung
    int showCursor(bool);                                                                     // diese Funktion versteckt den Cursor (LE_FALSE) oder zeigt ihn (LE_TRUE)

    //////////////////////////////
    // line
    //////////////////////////////

    int lineCreate(uint32_t);                                                                 // (TS) diese Funktion erstellt eine Linie
    uint32_t lineCreate();                                                                    // (TS) diese Funktion erzeugt eine Linie mit einer selbst generierten ID, diese wird auch zurueck gegeben!
    int lineDelete(uint32_t);                                                                 // (TS) diese Funktion loescht eine Linie
    void linePrintBufferList();                                                               // (TS) diese Funktion gibt die komplette Buffer Linien liste aus
    void linePrintList();                                                                     // (TS) diese Funktion gibt die komplette original Linien liste aus
    int lineSet(uint32_t, int, int, int, int);                                                // (TS) diese Funktion setzt die Linie
    int lineSetColor(uint32_t, uint8_t, uint8_t, uint8_t, uint8_t);                           // (TS) diese Funktion setzt die Farbe einer Linie
    int lineSetVisible(uint32_t, bool);                                                       // (TS) diese Funktion setzt eine Linie auf sichtbar oder unsichtbar
    int lineSetZindex(uint32_t, uint32_t);                                                    // (TS) diese Funktion setzt den Zindex fuer eine Linie, 0 nicht erlaubt
    void lineUsingThread(bool);                                                               // (TS) diese Funktion sperrt die Listen, falls der User Linien Funktionen in einem Thread benutzen moechte

    //////////////////////////////
    // model
    //////////////////////////////

    int modelAddCollisionRect(uint32_t, uint32_t, SDL_Rect);                                  // (TS) diese Funktion fuegt eine Kollisionsbereich in Form eines Rechteckes hinzu
    int modelAddDirection(uint32_t, uint32_t, glm::vec2);                                     // (TS) diese Funktion legt eine Bewegungsrichtung fuer ein Model an
    int modelAddTextureSourceRect(uint32_t, uint32_t, uint32_t, int, int, int, int);          // (TS) diese Funktion fuegt einen Texturbereich hinzu aus welchem ausschliesslich gezeichnet werden soll
    int modelChangeDirection(uint32_t, uint32_t, glm::vec2);                                  // (TS) diese Funktion aendert eine Bewegungsrichtung
    bool modelCheckCollision(uint32_t, uint32_t);                                             // (TS) diese Funktion prueft, ob zwei Models miteinander kollidieren
    bool modelCheckFrameBoxCollision(uint32_t, uint32_t);                                     // (TS) diese Funktion prueft, ob die groben Kollisionsbereiche von zwei Models miteinander kollidieren
    int modelClearClones(uint32_t);                                                           // (TS) diese Funktion loescht alle Clones des Models
    int modelCreate(uint32_t);                                                                // (TS) diese Funktion erzeugt ein Model mit Hilfe einer eindeutigen ID
    uint32_t modelCreate();                                                                   // (TS) diese Funktion erzeugt ein Model mit einer selbst generierten ID, diese wird auch zurueck gegeben!
    int modelCreateClone(uint32_t, uint32_t);                                                 // (TS) diese Funktion erstellt einen Clone fuer ein Model
    int modelCreateSurface(uint32_t, uint32_t, const char*);                                  // (TS) diese Funktion erstellt ein Surface aus einem Bild, um mit den Pixeldaten direkt arbeiten zu koennen
    int modelCreateTexture(uint32_t, uint32_t, const char*);                                  // (TS) diese Funktion erzeugt eine Textur, alle Texturen sollten die selbe Groesse haben, wegen des groben Kollisionsbereiches!
    int modelDelete(uint32_t);                                                                // (TS) diese Funktion loescht ein Model wieder
    int modelDeleteSurface(uint32_t, uint32_t);                                               // (TS) diese Funktion loescht das Surface einer Textur wieder
    int modelFadeTexture(uint32_t, uint32_t, double);                                         // (TS) diese Funktion blendet eine Textur ein oder aus
    int modelFocusTextureSourceRect(uint32_t, uint32_t, uint32_t);                            // (TS) diese Funktion setzt den Fokus auf einen Texturbereich, sodass nur dieser gezeichnet werden soll
    uint32_t modelGetAmountOfCollisionBoxes(uint32_t);                                        // (TS) diese Funktion gibt die Anzahl an Kollisionsbereichen zurueck
    uint32_t modelGetAmountOfTextureSourceRectangles(uint32_t, uint32_t);                     // (TS) diese Funktion gibt die Anzahl an Texturbereichen einer Textur zurueck
    LECollBox_d modelGetCollisionBox(uint32_t, uint32_t);                                     // (TS) diese Funktion gibt einen bestimmten Kollisionsbereich zurueck
    glm::vec2 modelGetDirection(uint32_t, uint32_t);                                          // (TS) diese Funktion gibt eine Bewegungsrichtung zurueck
    LECollBox_d modelGetFrameBox(uint32_t);                                                   // (TS) diese Funktion gibt den groben Kollisionsbereich eines Models zurueck
    Color modelGetPixelRGBA(uint32_t, uint32_t, uint32_t, uint32_t);                          // (TS) diese Funktion gibt einen Pixel einer Textur zurueck, modelCreateSurface() muss vorher aufgerufen worden sein
    glm::vec2 modelGetPositionD(uint32_t);                                                    // (TS) diese Funktion gibt die genauen Positionswerte des Models zurueck
    SDL_Point modelGetPosition(uint32_t);                                                     // (TS) diese Funktion gibt die Position eines Models zurueck
    SDL_Point modelGetSize(uint32_t);                                                         // (TS) diese Funktion gibt die Groesse eines Models zurueck
    double modelGetSizeFactor(uint32_t);                                                      // (TS) diese Funktion gibt den Faktor der Modelgroesse zurueck
    SDL_Surface * modelGetSurface(uint32_t, uint32_t);                                        // (TS) diese Funktion gibt einen Zeiger auf ein erstelltes Surface zurueck
    double modelGetTextureAlpha(uint32_t, uint32_t);                                          // (TS) diese Funktion gibt den Alphawert einer Textur zurueck
    bool modelGetVisible(uint32_t);                                                           // (TS) diese Funktion gibt visible zurueck
    uint32_t modelGetZindex(uint32_t);                                                        // (TS) diese Funktion gibt den Z-index des Models zurueck
    int modelMoveDirection(uint32_t, uint32_t);                                               // (TS) diese Funktion bewegt ein Model in eine vorher angelegte Richtung
    void modelPrintBufferList();                                                              // (TS) diese Funktion gibt die komplette Buffer Model liste aus
    void modelPrintList();                                                                    // (TS) diese Funktion gibt die komplette original Model liste aus
    int modelRotate(uint32_t, double);                                                        // (TS) diese Funktion rotiert ein Model um die angegebene Gradzahl pro Sekunde
    int modelRotateDir(uint32_t, uint32_t, double);                                           // (TS) diese Funktion rotiert eine Bewegungsrichtung um eine angegebene Gradzahl pro Sekunde
    int modelRotateOnce(uint32_t, double);                                                    // (TS) diese Funktion rotiert ein Model einmalig
    int modelSetClonePosition(uint32_t, uint32_t, glm::vec2);                                 // (TS) diese Funktion setzt die Position eines Model Clones
    int modelSetCloneVisible(uint32_t, uint32_t, bool);                                       // (TS) diese Funktion macht einen Clone eines Models sichtbar oder unsichtbar
    int modelSetPosition(uint32_t, double, double);                                           // (TS) diese Funktion setzt die Position eines Models in NDC
    int modelSetSize(uint32_t, int, int);                                                     // (TS) diese Funktion legt die Groesse des Models fest
    double modelSetSize(uint32_t, double);                                                    // (TS) diese Funktion legt die Groesse des Models in Prozent fest und gibt den Vergroesserungsfaktor zurueck, der dabei entsteht
    int modelSetSizeFactor(uint32_t, double);                                                 // (TS) diese Funktion setzt den Faktor der Modelgroesse
    int modelSetTextureActive(uint32_t, uint32_t, bool);                                      // (TS) diese Funktion left fest, ob eine Textur sichtbar ist, oder nicht
    int modelSetTextureAlpha(uint32_t, uint32_t, uint8_t);                                    // (TS) diese Funktion setzt einen Alphawert fuer eine Textur
    int modelSetTextureZindex(uint32_t, uint32_t, uint32_t);                                  // (TS) diese Funktion setzt den zindex einer Textur innerhalb eines Models
    int modelSetVisible(uint32_t, bool);                                                      // (TS) diese Funktion setzt ein Model auf sichtbar oder unsichtbar
    int modelSetZindex(uint32_t, uint32_t);                                                   // (TS) diese Funktion setzt den zindex eines Models, 0 nicht erlaubt
    bool modelTextureExists(uint32_t, uint32_t);                                              // (TS) diese Funktion prueft, ob eine Modeltextur ID existiert
    void modelUsingThread(bool);                                                              // (TS) diese Funktion sperrt die Listen, falls der User Model Funktionen in einem Thread benutzen moechte

    //////////////////////////////
    // point
    //////////////////////////////

    int pointAddDirection(uint32_t, uint32_t, glm::vec2);                                     // (TS) diese Funktion fuegt eine Bewegungsrichtung hinzu
    int pointCreate(uint32_t);                                                                // (TS) diese Funktion fuegt einen Punkt hinzu
    uint32_t pointCreate();                                                                   // (TS) diese Funktion erzeugt einen Punkt mit einer selbst generierten ID, diese wird auch zurueck gegeben!
    int pointDelete(uint32_t);                                                                // (TS) diese Funktion loescht einen Punkt
    int pointFade(uint32_t, double);                                                          // (TS) diese Funktion blendet einen Punkt ein oder aus
    Color pointGetColor(uint32_t);                                                            // (TS) diese Funktion gibt die Farbe eines Punktes zurueck
    SDL_Point pointGetPosition(uint32_t);                                                     // (TS) diese Funktion gibt die Position eines Punktes zurueck
    int pointMoveDirection(uint32_t, uint32_t);                                               // (TS) diese Funktion bewegt einen Punkt in eine zuvor erstelle Bewegungsrichtung
    void pointPrintBufferList();                                                              // (TS) diese Funktion gibt die komplette Buffer Punkte liste aus
    void pointPrintList();                                                                    // (TS) diese Funktion gibt die komplette original Punkte liste aus
    int pointRotate(uint32_t, double, SDL_Point);                                             // (TS) diese Funktion laesst einen Punkt um einen bestimmten Punkt rotieren
    int pointSetColor(uint32_t, uint8_t, uint8_t, uint8_t, uint8_t);                          // (TS) diese Funktion legt die Farbe eines Punktes fest
    int pointSetPosition(uint32_t, int, int);                                                 // (TS) diese Funktion setzt die Position eines Punktes
    int pointSetVisible(uint32_t, bool);                                                      // (TS) diese Funktion macht einen Punkt sichtbar oder unsichtbar
    int pointSetZindex(uint32_t, uint32_t);                                                   // (TS) diese Funktion setzt den Z-index eines Punktes
    void pointUsingThread(bool);                                                              // (TS) diese Funktion sperrt die Listen, falls der User Punkt Funktionen in einem Thread benutzen moechte

    //////////////////////////////
    // sound
    //////////////////////////////

    int soundCreate(uint32_t);                                                                // (TS) diese Funktion fuegt einen Sound hinzu
    uint32_t soundCreate();                                                                   // (TS) diese Funktion erzeugt einen Sound mit einer selbst generierten ID, diese wird auch zurueck gegeben!
    int soundDelete(uint32_t);                                                                // (TS) diese Funktion loescht einen Sound
    int soundFadeIn(uint32_t, int);                                                           // (TS) diese Funktion blendet einen Kanal oder alle Kanaele ein
    void soundFadeOut(int);                                                                   // (TS) diese Funktion blendet einen Kanal oder alle Kanaele aus
    int soundLoadWAV(uint32_t, const char*);                                                  // (TS) diese Funktion laedt eine WAV Datei fuer einen erstellten Sound
    int soundLock(uint32_t, bool);                                                            // (TS) diese Funktion sperrt einen Sound, sodass er hier nach nicht wieder gespielt wird, bis er entsperrt ist
    void soundPause();                                                                        // (TS) diese Funktion pausiert einen Sound
    int soundPlay(uint32_t, int);                                                             // (TS) diese Funktion spielt einen Sound ab
    void soundPrintBufferList();                                                              // (TS) diese Funktion gibt die komplette Buffer sound liste aus
    void soundPrintList();                                                                    // (TS) diese Funktion gibt die komplette original sound liste aus
    void soundSetVolume(uint8_t);                                                             // (TS) diese Funktion setzt die Lautstaerke
    void soundUsingThread(bool);                                                              // (TS) diese Funktion sperrt die Listen, falls der User sound Funktionen in einem Thread benutzen moechte

    //////////////////////////////
    // text
    //////////////////////////////

    int textAddDirection(uint32_t, uint32_t, glm::vec2);                                      // (TS) diese Funktion fuegt einem Text eine Bewegungsrichtung hinzu
    int textAddLetter(uint32_t, uint8_t);                                                     // (TS) diese Funktion fuegt einen Buchstaben an das Ende hinzu
    int textAddString(uint32_t, const char*);                                                 // (TS) diese Funktion fuegt einen kompletten String dem Text hinzu
    int textClear(uint32_t);                                                                  // (TS) diese Funktion loescht den kompletten Text
    int textCreate(uint32_t);                                                                 // (TS) diese Funktion fuegt einen UTF8 Text hinzu
    uint32_t textCreate();                                                                    // (TS) diese Funktion erzeugt einen Text mit einer selbst generierten ID, diese wird auch zurueck gegeben!
    int textDelete(uint32_t);                                                                 // (TS) diese Funktion loescht einen Text
    int textFade(uint32_t, double);                                                           // (TS) diese Funktion blendet einen Text ein oder aus
    double textGetAlpha(uint32_t);                                                            // (TS) diese Funktion gibt den Alpha Wert eines Textes zurueck
    SDL_Point textGetPosition(uint32_t);                                                      // (TS) diese Funktion gibt die Position des Textes zurueck
    SDL_Point textGetSize(uint32_t);                                                          // (TS) diese Funktion gibt die Dimensionen des Textes zurueck
    bool textGetVisible(uint32_t);                                                            // (TS) diese Funktion prueft, ob ein Text sichtbar ist
    int textMoveDirection(uint32_t, uint32_t);                                                // (TS) diese Funktion bewegt eine Text in eine zuvor erstellte Bewegungsrichtung
    int textPrepareForDrawing(uint32_t);                                                      // (TS) diese Funktion bereitet einen Text auf das Zeichnen vor, ein Text kann anschliessend gezeichnet werden
    void textPrintBufferList();                                                               // (TS) diese Funktion gibt die komplette Buffer text liste aus
    void textPrintList();                                                                     // (TS) diese Funktion gibt die komplette original text liste aus
    int textRelateFont(uint32_t, uint32_t);                                                   // (TS) diese Funktion ordnet dem Text einen Font zu, muss vor textPrepareForDrawing() aufgerufen werden
    int textSetAlpha(uint32_t, uint8_t);                                                      // (TS) diese Funktion setzt den Alphawert eines Textes, muss nach textPrepareForDrawing() aufgerufen werden!
    int textSetColor(uint32_t, uint8_t, uint8_t, uint8_t, uint8_t);                           // (TS) diese Funktion setzt die Farbe eines Textes, muss vor textPrepareForDrawing() aufgerufen werden
    int textSetPosition(uint32_t, int, int);                                                  // (TS) diese Funktion setzt die Position eines Textes
    int textSetVisible(uint32_t, bool);                                                       // (TS) diese Funktion sagt aus, ob ein Text sichtbar ist, oder nicht
    int textSetZindex(uint32_t, uint32_t);                                                    // (TS) diese Funktion setzt den z-index fuer einen Text, 0 nicht erlaubt
    int textSubmit(uint32_t);                                                                 // (TS) diese Funktion erstellt aus allen Buchstaben einen Text
    void textUsingThread(bool);                                                               // (TS) diese Funktion sperrt die Listen, falls der User sound Funktionen in einem Thread benutzen moechte

    //////////////////////////////
    // time event
    //////////////////////////////

    int timeEventCreate(uint32_t, uint32_t);                                                  // (TS) diese Funktion erstellt ein Zeitereignis
    uint32_t timeEventCreate(uint32_t);                                                       // (TS) diese Funktion erzeugt ein Zeitereignis mit einer selbst generierten ID, diese wird auch zurueck gegeben!
    int timeEventDelete(uint32_t);                                                            // (TS) diese Funktion loescht ein Zeitereignis
    uint32_t timeEventGetStamp(uint32_t);                                                     // (TS) diese Funktion gibt den Zeitstempel fuer das Zeitereignis zurueck
    void timeEventPrintBufferList();                                                          // (TS) diese Funktion gibt die komplette Buffer time event liste aus 
    void timeEventPrintList();                                                                // (TS) diese Funktion gibt die komplette original time event liste aus 
    bool timeEventReached(uint32_t);                                                          // (TS) diese Funktion prueft, ob ein Zeitereignis bereits erreicht wurde
    int timeEventReset(uint32_t, uint32_t);                                                   // (TS) diese Funktion setzt den Wert eines Zeitereignisses neu
    int timeEventUpdate(uint32_t, uint32_t);                                                  // (TS) diese Funktion verlaengert ein Zeitereignis um eine Anzahl von Millisekunden
    void timeEventUpdateValidALL(uint32_t);                                                   // (TS) diese Funktion verlaengert alle noch nicht erreichten Zeitereignisse um eine Anzahl von Millisekunden
    void timeEventUsingThread(bool);                                                          // (TS) diese Funktion sperrt die Listen, falls der User timeEvent Funktionen in einem Thread benutzen moechte

    //////////////////////////////
    // video
    //////////////////////////////

    int videoCreate(uint32_t, const char*);                                                   // diese Funktion erstellt ein Video
    int videoDelete(uint32_t);                                                                // diese Funktion loescht ein Video
    bool videoPlay(uint32_t);                                                                 // diese Funktion legt fest, ob ein Video gespielt wird oder nicht

    //////////////////////////////
    // window
    //////////////////////////////

    bool windowFocused();                                                                     // diese Funktion prueft, ob das Fenster gerade im Focus ist, oder nicht
} *LEMoonInstance;

#endif
