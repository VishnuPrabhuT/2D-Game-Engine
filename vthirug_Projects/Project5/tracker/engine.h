#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "hud.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"

class Player;
class CollisionStrategy;
class SmartSprite;

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();

private:
  const RenderContext* rc;
  const IOmod& io;
  const HUD& hud;
  Clock& clock;

  SDL_Renderer * const renderer;
  World hills1;
  World hills2;
  World hills3;
  World hills4;
  World hills5;
  Viewport& viewport;
  Player* player;
  Player* realPlayer;
  std::vector<SmartSprite*> sprites;
  std::vector<CollisionStrategy*> strategies;
  std::vector<Drawable*> explosionSprites;
  bool explosion;
  unsigned int endTime;
  int currentExplosion;
  int currentStrategy;
  bool playerCollision;
  bool gameOver;
  int currentSprite;
  bool showHUD;
  bool initialFlag;
  bool reset;
  bool makeVideo;

  void draw();
  void update(Uint32);

  Engine(const Engine&)=delete;
  Engine& operator=(const Engine&)=delete;
  void printScales() const;
  void checkForCollisions();
  void checkBulletCollisions();
};
