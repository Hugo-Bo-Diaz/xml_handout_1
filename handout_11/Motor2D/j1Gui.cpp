#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Window.h"

#include "UItext.h"
#include "UIimage.h"
#include "UIStartButton.h"
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

	//pugi::xml_node elements_node = conf.child("elements");

	//for (pugi::xml_node elem = elements_node.child("elem"); elem; elem = elem.next_sibling())
	//{
	//	switch (elem.attribute("type").as_int())
	//	{
	//		case 0://image
	//		{
	//			break;
	//		}
	//		case 1://text
	//		{
	//			SDL_Color color = {elem.attribute("r").as_uint() ,elem.attribute("g").as_uint(),elem.attribute("b").as_uint(), elem.attribute("a").as_uint() };
	//			
	//			UIelement* element = new UItext(
	//			{ elem.attribute("x").as_int(),elem.attribute("y").as_int() },
	//			elem.attribute("text").as_string(),
	//			color);
	//			elements.add(element);
	//			break;
	//		}
	//	}
	//}
	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());
	
	background = App->tex->Load("gui/background.png");

	UIelement* element_1 = new UItext({0,0}, "this is a test", { 255,255,0,255 });
	elements.add(element_1);
	UIelement* element_2 = new UIimage({ 451, 460 }, { 0,0,122,74 });
	elements.add(element_2);
	UIelement* element_3 = new UIStartButton({ 200, 200 });
	elements.add(element_3);

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	p2List_item<UIelement*>* item = elements.start;

	while (item != NULL)
	{
		if (MouseInside(&item->data->GetRect()))
		{
			item->data->OnMouseOver();
			if (App->input->GetMouseButtonDown(1) == KEY_REPEAT)//left click
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

