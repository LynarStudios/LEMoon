/*
  Author:             Patrick-Christopher Mattulat
  e-mail:             pmattulat@outlook.de
  Dev-Tool:           Ubuntu 16.04, g++ Compiler
  date:               29.05.2017
  updated:            26.04.2018
*/

#ifndef H_LE_MODEL
#define H_LE_MODEL

#include "SDL.h"
#include "SDL_image.h"
#include "glm/gtx/rotate_vector.hpp"
#include "le_error.h"
#include "le_math.h"

struct Texture
{
  Texture * pLeft;
  Texture * pRight;
  uint32_t id;
  bool active;
  double idStep;                                                                    // die Anzahl an Schritten, die zu einem neuen Texturbereich fuehren
  bool startSet;                                                                    // sagt aus, ob der Anfang einer Animation erkannt wurde
  bool animationEnd;                                                                // sagt aus, ob das Ende einer Animation erreicht wurde
  uint32_t zindex;                                                                  // Order des Zeichenvorganges, kleinerer index wird zuerst gemalt
  double alpha;                                                                     // der Alphawert der Textur, Standardmaessig bei 255
  SDL_Surface * pSurface;                                                           // ein Surface, um beispielsweise mit Pixeldaten direkt zu arbeiten
  SDL_Texture * pTexture;
  SourceRect * pSrcRectHead;
  SourceRect * pSourceRect;                                                         // der aktuelle Bereich aus einer Textur, der gezeichnet werden soll
};

typedef struct sClone
{
  uint32_t id;
  glm::vec2 position;
  bool visible;
  sClone * pLeft;
  sClone * pRight;
} Clone;

typedef struct sCollisionRect
{
  uint32_t id;
  SDL_Rect collRect;
  LECollBox_d collRectBuffer;
  sCollisionRect * pLeft;
  sCollisionRect * pRight;
} CollisionRect;

class LEMdl
{
  private:

    // thread

    mutex mtxDirection;
    mutex mtxClone;
    mutex mtxCollisionRect;
    mutex mtxSourceRectList;
    mutex mtxTexture;

    // members

    Texture * pTextureHead;
    SDL_Rect rectPosSize;                                                           // Bildschirm Koordinaten und Groesse in Pixel
    double sizeFactor;                                                              // ein Faktor, um die Bildgroesse zu veraendern, standardmaessig auf 1.0f
    glm::vec2 position;                                                             // Position in NDC / nur fuer interne Berechnungen
    LinkedVec2 * pDirectionHead;                                                    // Bewegungsrichtungen
    double currentDegree;                                                           // die aktuelle Rotationsgradzahl
    Clone * pCloneHead;                                                             // Listenkopf mit Clones des Models
    LECollBox_d frameBox;                                                           // grober Kollisionsbereich
    LECollBox_d bufferFrameBox;                                                     // Kopie des groben Kollisionsbereiches fuer Rotationen

    uint32_t amountSourceRect(Texture*);                                            // diese Funktion gibt die Anzahl an Texturbereichen einer Textur zurueck
    Clone * cloneGet(uint32_t);                                                     // diese Funktion liefert eine Referenz auf einen Clone des Models
    CollisionRect * collisionRectGet(uint32_t);                                     // diese Funktion gibt eine Referenz auf einen Kollisionsbereich zurueck
    LinkedVec2 * directionGet(uint32_t);                                            // diese Funktion gibt eine Referenz auf eine Bewegungsrichtung zurueck
    void memoryClearClones();                                                       // diese Funktion loescht alle Clones vom Model
    void memoryClearCollisionRects();                                               // diese Funktion loescht alle Kollisionsbereiche
    void memoryClearDirections();                                                   // diese Funktion loescht alle Bewegungsrichtungen im Destruktor der Klasse
    void memoryClearTextures();                                                     // diese Funktion loescht alle Texturen im Destruktor der Klasse
    LECollBox_d rotateCollisionBox(LECollBox_d);                                    // diese Funktion rotiert eine Kollisionsbox
    SourceRect * sourceRectGet(Texture*, uint32_t);                                 // diese Funktion gibt eine Referenz auf ein Source Rect zurueck
    Texture * textureGet(uint32_t);                                                 // diese Funktion gibt eine Referenz auf eine Textur zurueck
    void updateCollisionBox(CollisionRect*);                                        // diese Funktion aktualisiert einen Kollisionsbereich
    void updateFrameBox();                                                          // diese Funktion aktualisiert den groben Kollisionsbereich

  public:

    CollisionRect * pCollisionRectHead;                                             // Listenkopf mit Kollisionsbereichen

    LEMdl();
    ~LEMdl();

    int mdlAddCollisionRect(uint32_t, SDL_Rect);                                    // diese Funktion fuegt einen Kollisionsbereich hinzu
    int mdlAddDirection(uint32_t, glm::vec2);                                       // diese Funktion fuegt eine Bewegungsrichtung hinzu
    int mdlAddTextureSourceRect(uint32_t, uint32_t, int, int, int, int);            // diese Funktion fuegt einen Texturbereich hinzu
    int mdlChangeDirection(uint32_t, glm::vec2);                                    // diese Funktion aendert eine Bewegungsrichtung
    void mdlClearClones();                                                          // diese Funktion loescht alle Clones
    int mdlCreateClone(uint32_t);                                                   // diese Funktion erstellt einen Clone des Models
    int mdlCreateSurface(uint32_t, const char*);                                    // diese Funktion erstellt ein Surface einer Textur, um mit den Pixeldaten direkt arbeiten zu koennen
    int mdlCreateTexture(uint32_t, const char*, SDL_Renderer*);                     // diese Funktion erstellt eine Textur
    int mdlDeleteSurface(uint32_t);                                                 // diese Funktion loescht das Surface einer Textur wieder
    int mdlDrawActiveTexture(SDL_Renderer*);                                        // diese Funktion zeichnet alle aktiven Texturen
    int mdlFadeTexture(uint32_t, double, double);                                   // diese Funktion blendet eine Textur ein oder aus
    bool mdlFinishedAllMutexes();                                                   // diese Funktion sagt aus, ob alle Mutexes auf unlock stehen
    int mdlFocusTextureSourceRect(uint32_t, uint32_t);                              // diese Funktion setzt den Fokus auf einen bestimmten Texturbereich, sodass nur dieser gezeichnet wird
    uint32_t mdlGetAmountOfCollisionBoxes();                                        // diese Funktion gibt die Anzahl an Kollisionsbereichen zurueck
    uint32_t mdlGetAmountOfTextureSourceRectangles(uint32_t);                       // diese Funktion gibt die Anzahl an Texturbereichen einer Textur zurueck
    LECollBox_d mdlGetCollisionBox(uint32_t);                                       // diese Funktion gibt einen bestimmten Kollisionsbereich zurueck
    double mdlGetCurrentDegree();                                                   // diese Funktion gibt den aktuellen Rotationsgrad zurueck
    glm::vec2 mdlGetDirection(uint32_t);                                            // diese Funktion gibt eine Bewegungsrichtung zurueck
    LECollBox_d mdlGetFrameBox();                                                   // diese Funktion gibt den groben Kollisionsbereich eines Models zurueck
    Color mdlGetPixelRGBA(uint32_t, uint32_t, uint32_t);                            // diese Funktion gibt einen Pixel zurueck
    SDL_Point mdlGetPosition();                                                     // diese Funktion gibt die Position eines Models zurueck
    glm::vec2 mdlGetPositionD();                                                    // diese Funktion gibt die genauen Positionswerte zurueck
    SDL_Point mdlGetSize();                                                         // diese Funktion gibt die Groesse des Models zurueck
    SDL_Surface * mdlGetSurface(uint32_t);                                          // diese Funktion gibt ein SDL_Surface einer Textur zurueck
    double mdlGetSizeFactor();                                                      // diese Funktion gibt den Faktor der Modelgroesse zurueck
    double mdlGetTextureAlpha(uint32_t);                                            // diese Funktion gibt den Alphawert einer Textur zurueck
    int mdlMoveDirection(uint32_t, double);                                         // diese Funktion bewegt das Model in eine Bewegungsrichtung
    void mdlRotate(double, double);                                                 // diese Funktion rotiert das Model
    int mdlRotateDir(uint32_t, double, double);                                     // diese Funktion rotiert eine Bewegungsrichtung pro Sekunde
    void mdlRotateOnce(double);                                                     // diese Funktion rotiert ein Model einmalig
    int mdlSetClonePosition(uint32_t, glm::vec2);                                   // diese Funktion setzt die Position des Clones
    int mdlSetCloneVisible(uint32_t, bool);                                         // diese Funktion macht einen Clone sichtbar
    void mdlSetPosition(double, double);                                            // diese Funktion setzt die Position eines Models anhand einer ID
    void mdlSetSize(int w, int h);                                                  // diese Funktion legt die Groesse des Models fest
    double mdlSetSize(double, int);                                                 // diese Funktion legt die Groesse des Models in Prozent fest und gibt den Vergroesserungsfaktor zurueck
    void mdlSetSizeFactor(double);                                                  // diese Funktion setzt den Faktor der Modelgroesse
    int mdlSetTextureActive(uint32_t, bool);                                        // diese Funktion legt fest, ob eine Textur sichtbar ist oder nicht
    int mdlSetTextureAlpha(uint32_t, uint8_t);                                      // diese Funktion setzt den Alphawert einer Textur
    int mdlSetTextureZindex(uint32_t, uint32_t);                                    // diese Funktion setzt einen zindex fuer eine Textur
    bool mdlTextureExist(uint32_t);                                                 // diese Funktion prueft, ob eine Textur existiert
};

#endif
