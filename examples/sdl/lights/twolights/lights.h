// The design and implementation of the classes Light and Triple
// were contributed by Sean Kelly, Spring 2013.
// The idea derived from Dr. Geist's course on Graphics, CpSc 405
#include <list>
#include <SDL.h>
#include "triple.h"
#include "light.h"

class Gamedata;

class Lights {
public:
  Lights();
  ~Lights();
  // Triple specifies the position of the light in (x, y, z)
  // The second parameter specifies brightness, where 2,000,000 is 
  // somewhat dark!
  void draw() const;
  void update() const;
  void addLights();
  void addLight(const Triple& triple, int brightness);
private:
  Gamedata& gdata;
  SDL_Renderer* renderer;
  unsigned int viewWidth;
  unsigned int viewHeight;
  unsigned int diffuseGridX;
  unsigned int diffuseGridY;
  std::list<Light*> lights;
  Lights(const Lights&);
  Lights& operator=(const Lights&);
};
