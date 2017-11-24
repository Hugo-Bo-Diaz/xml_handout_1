#ifndef __UI_CHECK__
#define __UI_CHECK__

#include "p2Point.h"
#include "p2SString.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "UIelement.h"

enum check_type
{
	ACCOUNT_NAME,
	NULLL
};

class UICheckBox : public UIelement
{
public:
	bool mouseover = false;
	bool clicked = false;
	bool active = false;
	SDL_Rect cross = {199,170,16,16};
	SDL_Rect glow = {159,170,16,16};
	SDL_Rect pressed = { 178,170,16,16 };
	check_type type = NULLL;
	p2SString string;
	int text_w;
	int text_h;
	SDL_Texture* tex;
public:
	UICheckBox() {};
	UICheckBox(iPoint pos, check_type _type = NULLL)// color is a 4 dim array in this order{r g b a} this is for the default font need to adapt it better
	{
		position = pos;
		portion = {219,169,16,16};
		type = _type;
		switch (type)
		{
		case ACCOUNT_NAME:
		{string = "Remember Account Name";
		break;}
		default:
		{string = "kys stupid programer";
		break;}
		}
		tex = App->tex->textures.add(App->font->Print(string.GetString(), { 255,255,0,255 }, App->font->default))->data;
		SDL_QueryTexture(tex, NULL, NULL, &text_w, &text_h);
	}
	~UICheckBox() { App->tex->UnLoad(tex); };

	void Draw() {

		App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &portion);

		if (mouseover)
		{
			App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &glow);
			mouseover = false;
		}
		if (clicked)
		{
			App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &pressed);
		}
		if (active)
		{
			App->render->Blit(App->gui->GetAtlas(), position.x+1, position.y+1, &cross);
		}
		App->render->Blit(tex, position.x + 20, (position.y + portion.h / 2 - text_h / 2));
	};

	void OnClick() { clicked = true; };
	void OnMouseOver() { mouseover = true; };
	bool OnRelease() 
	{
		bool ret = true;

		if (mouseover && clicked) 
		{ 
			active = !active;
		} 
		clicked = false;
		return ret;
	};

	//functions for the buttons
};

#endif 