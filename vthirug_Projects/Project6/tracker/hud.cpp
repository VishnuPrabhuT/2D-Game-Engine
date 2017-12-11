#include "hud.h"

HUD& HUD::getInstance() {
		static HUD hud;
		return hud;
}

const std::string& HUD::getText() const{
	return instructions;
}

int HUD::getHeight() const{
	return width;
}

int HUD::getWidth() const{
	return height;
}

HUD::HUD():instructions(Gamedata::getInstance().getXmlStr("HUD/instructions")),width(Gamedata::getInstance().getXmlInt("HUD/width")),height(Gamedata::getInstance().getXmlInt("HUD/height")){

}

HUD::~HUD() {

}
