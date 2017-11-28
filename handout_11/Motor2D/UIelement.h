#ifndef __UI_ELEMENT__
#define __UI_ELEMENT__

#include "p2Point.h"
#include "p2Log.h"
#include "SDL\include\SDL.h"

#include "j1Module.h"

enum UIelement_type
{
	BUTTON,
	CHECKBOX,
	IMAGE,
	TEXT,
	TEXTBOX,
	NONE
};

class UIelement
{
public:
	iPoint position;
	SDL_Rect portion = {0,0,0,0};
	j1Module* callback = nullptr;

	UIelement_type type_of_element = NONE;

	bool mouseover;
public:
	UIelement() {};
	~UIelement() {};

	virtual void OnClick() {};
	virtual bool OnRelease() { return true; };
	virtual void Draw() {};

	virtual bool OnActivation() 
	{ 
		bool ret = true;
		if (callback != nullptr) 
		{
			ret = callback->UIinteraction(this);
		}
		return ret; 
	};

	SDL_Rect GetRect()
	{
		return {position.x,position.y,portion.w,portion.h};
	}
};

#endif 