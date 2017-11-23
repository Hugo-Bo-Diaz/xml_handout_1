#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

#include "UItext.h"
#include "UIimage.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());
	
	background = App->tex->Load("gui/background.png");

	UIelement* element_1 = new UItext({0,0}, "this is a test", { 255,255,0,255 });
	elements.add(element_1);
	UIelement* element_2 = new UIimage({ 0,0 }, { 0,0,122,74 });
	elements.add(element_2);

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	p2List_item<UIelement*>* item = elements.start;

	while (item != NULL)
	{
		if (MouseInside(&item->data->portion))
		{
			item->data->OnMouseOver();
			if (App->input->GetMouseButtonDown(1) == KEY_DOWN)//left click
			{
				item->data->OnClick();
			}
			if (App->input->GetMouseButtonDown(1) == KEY_UP)
			{
				item->data->OnRelease();
			}
		}
		item = item->next;
	}

	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	App->render->Blit(background,0,0);

	p2List_item<UIelement*>* item = elements.start;

	while (item !=NULL)
	{
		item->data->Draw();
		item = item->next;
	}
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

bool j1Gui::MouseInside(SDL_Rect* rect)
{
	int x = 0;
	int y = 0;
	App->input->GetMousePosition(x, y);
	if (x < (rect->x + rect->w) && x > rect->x &&y < (rect->y + rect->h) && y > rect->y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// class Gui ---------------------------------------------------

