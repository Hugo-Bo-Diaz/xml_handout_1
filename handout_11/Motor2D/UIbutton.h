#ifndef __UI_BUTTON__
#define __UI_BUTTON__

#include "p2Point.h"
#include "p2SString.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "UIelement.h"

enum button_type
{
	LOGIN,
	CINEMATICS,
	CREDITS,
	TERMS_OF_USE,
	MANAGE_ACCOUNT,
	COMUNITY_SITE,
	QUIT,
	NUL

};

class UIButton : public UIelement
{
public:
	bool mouseover = false;
	bool clicked = false;
	SDL_Rect pressed = {0,105,133,34};
	SDL_Rect glow = {0,139,144,46};
	button_type type = NUL;
	p2SString string;
	int text_w;
	int text_h;
	SDL_Texture* tex;
public:
	UIButton() {};
	UIButton(iPoint pos, button_type _type = NUL)// color is a 4 dim array in this order{r g b a} this is for the default font need to adapt it better
	{
		position = pos;
		portion = {0,73,133,34};
		type = _type;
		switch (type)
		{
		case LOGIN:
		{string = "Login";
		break;}
		case CINEMATICS:
		{string = "Cinematics";
		break;}
		case CREDITS:
		{string = "Credits";
		break;}
		case TERMS_OF_USE:
		{string = "Terms of use";
		break;}
		case MANAGE_ACCOUNT:
		{string = "Manage account";
		break;}
		case COMUNITY_SITE:
		{string = "Comunity site";
		break; }
		case QUIT:
		{string = "Quit";
		break;}
		default:
		{string = "kys stupid programer";
		break;}
		}
		tex = App->tex->textures.add(App->font->Print(string.GetString(), { 255,255,0,255 }, App->font->default))->data;
		SDL_QueryTexture(tex, NULL, NULL, &text_w, &text_h);
	}
	~UIButton() { App->tex->UnLoad(tex); };

	void Draw() {

		if (clicked)
		{
			App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &pressed);
		}
		else 
		{
			App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &portion);
		}
		if (mouseover)
		{
			App->render->Blit(App->gui->GetAtlas(), position.x - 6, position.y - 6, &glow);
			mouseover = false;
		}
		App->render->Blit(tex, position.x + portion.w / 2 - text_w / 2, (position.y + portion.h / 2 - text_h / 2) -2);
		};

	void OnClick() { clicked = true; };
	void OnMouseOver() { mouseover = true; };
	bool OnRelease() 
	{
		bool ret = true;

		if (mouseover && clicked) 
		{ 
			switch (type)
			{
			case LOGIN:
			{LOG("LOL U HAVE LOGGED IN");
			break; }
			case CINEMATICS:
			{LOG("WE HAVE NONE YET LOL");
			break; }
			case CREDITS:
			{LOG("I DID THIS LOL");
			break; }
			case TERMS_OF_USE:
			{LOG("I DON'T LET U USE THIS LOL");
			break; }
			case MANAGE_ACCOUNT:
			{LOG("LOL WHAT ACCOUNT");
			break; }
			case COMUNITY_SITE:
			{LOG("WHAT COMUNITY LOL");
			break; }
			case QUIT:
			{ret = false;
			break; }
			default:
			{LOG("LOL U DUMB");
			break; }
			}
		} 
		clicked = false;
		return ret;
	};

	//functions for the buttons
};

#endif 