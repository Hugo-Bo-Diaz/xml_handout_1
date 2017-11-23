#ifndef __UI_BUTTON__
#define __UI_BUTTON	__

#include "p2Point.h"
#include "p2SString.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1App.h"
#include "UIelement.h"
#include "j1Gui.h"
#include "j1Render.h"

class UIbutton : public UIelement
{
public:

public:
	UIbutton() {};
	UIbutton(iPoint pos, SDL_Rect _rect)// color is a 4 dim array in this order{r g b a} this is for the default font need to adapt it better
	{
		position = pos;
		portion = _rect;
	}
	~UIbutton() {};

	virtual void Draw() {
		App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &portion);
	};
	virtual void OnClick() {};
	virtual void OnMouseOver() {};

};

#endif 