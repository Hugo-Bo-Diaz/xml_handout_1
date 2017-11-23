#ifndef __UI_ELEMENT__
#define __UI_ELEMENT__

#include "p2Point.h"
#include "p2Log.h"

class UIelement
{
public:
	iPoint position;
	SDL_Rect portion = {0,0,0,0};
public:
	UIelement() {};
	~UIelement() {};

	virtual void OnClick() {
		LOG("HI");
	};
	virtual void OnRelease() {
		LOG("BYE");
	};
	virtual void OnMouseOver() {
		//LOG("I'm being harrassed");
	};

	virtual void Draw() {};
};

#endif 