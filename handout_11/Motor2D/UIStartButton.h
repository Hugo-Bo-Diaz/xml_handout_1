#ifndef __UI_START__
#define __UI_START__

#include "p2Point.h"
#include "p2SString.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "UIelement.h"

class UIStartButton : public UIelement
{
public:
	bool mouseover = false;
	bool clicked = false;
	SDL_Rect pressed = {0,105,133,34};
	SDL_Rect glow = {0,139,144,46};

	p2SString string = "Raul";
	int text_w;
	int text_h;
	SDL_Texture* tex;
public:
	UIStartButton() {};
	UIStartButton(iPoint pos)// color is a 4 dim array in this order{r g b a} this is for the default font need to adapt it better
	{
		position = pos;
		portion = {0,73,133,34};
		tex = App->tex->textures.add(App->font->Print(string.GetString(), { 255,255,0,255 }, App->font->default))->data;

		SDL_QueryTexture(tex, NULL, NULL, &text_w, &text_h);
	}
	~UIStartButton() {};

	void Draw() {

		App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &portion);
		if (clicked)
		{
			App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &pressed);
			clicked = false;
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
	void OnRelease() { if (clicked = true) { LOG("I'VE BEEN ACTIVATED"); } };

};

#endif 