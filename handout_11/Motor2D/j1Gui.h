#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "UIelement.h"
#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Gui creation functions

	bool UIinteraction(UIelement* element);

	SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;

	p2List<UIelement*> elements;
	SDL_Texture* background;

	bool MouseInside(SDL_Rect* rect);
};

#endif // __j1GUI_H__