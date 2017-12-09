#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "multisprite.h"

class Engine {
public:
  Engine ();
  ~Engine ();
  bool play();
  void switchSprite();

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World world;
  Viewport& viewport;

  MultiSprite player;
  std::vector<Drawable*> sprites;

  int currentSprite;
  bool makeVideo;
  bool gameOver;

  void draw() const;
  void update(Uint32);

  Engine(const Engine&);
  Engine& operator=(const Engine&);
  void printScales() const;
};
