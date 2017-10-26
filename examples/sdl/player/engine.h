#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"

class Player;
class CollisionStrategy;

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World world;
  Viewport& viewport;

  Player* player;
  std::vector<Drawable*> sprites;
  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;
  bool collision;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  void checkForCollisions();
};
