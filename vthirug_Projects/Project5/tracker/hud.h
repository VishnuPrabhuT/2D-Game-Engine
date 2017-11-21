#ifndef HUD__H
#define HUD__H
#include <string>
#include <map>
#include "vector2f.h"
#include "parseXML.h"
#include "gamedata.h"

class HUD{
public:
	static HUD& getInstance();
  	~HUD();
	const std::string& getText() const;
	int getWidth() const;
	int getHeight() const;
private:
	HUD(const HUD&)=delete;
	HUD();
  HUD& operator=(const HUD&)=delete;
	const std::string instructions;
	int width;
	int height;
};

#endif
