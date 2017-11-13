#include "hud.h"

HUD& HUD::getInstance() {
		static HUD hud;
		return hud;
}

std::string HUD::getText() const{
	return instructions;
}

HUD::HUD():instructions(Gamedata::getInstance().getXmlStr("HUD/instructions")){

}

HUD::~HUD() { }
