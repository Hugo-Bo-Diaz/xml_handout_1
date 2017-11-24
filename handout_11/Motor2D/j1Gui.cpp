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
#include "UIbutton.h"
#include "UICheckBox.h"

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

	UIelement* copyright_text = new UItext({320,560}, "Copyright 2004 2007 Blizzard entretainment All rights reserved", { 255,255,0,255 });
	elements.add(copyright_text);
	UIelement* version_text = new UItext({ 10,546 }, "Version 2.0.12 (6546) Release", { 255,255,0,255 });
	elements.add(version_text);
	UIelement* date_text = new UItext({ 10,560 }, "Mar 30 2007", { 255,255,0,255 });
	elements.add(date_text);
	UIelement* web_text = new UItext({ 920,450 }, "WoWps.org TBC", { 150,150,150,255 });
	elements.add(web_text);

	UIelement* wow_logo = new UIimage({ 0, 0 }, { 133,21,319,127 });
	elements.add(wow_logo);
	UIelement* esrb_rating = new UIimage({ 15, 500 }, { 327,153,127,40 });
	elements.add(esrb_rating);
	UIelement* blizzard_logo = new UIimage({ 451, 485 }, { 0,0,122,74 });
	elements.add(blizzard_logo);

	UIelement* login_button = new UIButton({ 446, 370 }, button_type::LOGIN);
	elements.add(login_button);

	UIelement* manage_account_button = new UIButton({ 10, 390 }, button_type::MANAGE_ACCOUNT);
	elements.add(manage_account_button);
	UIelement* community_site = new UIButton({ 10, 430 }, button_type::COMUNITY_SITE);
	elements.add(community_site);

	UIelement* quit_button = new UIButton({ 880, 515 }, button_type::QUIT);
	elements.add(quit_button);
	UIelement* terms_of_use_button = new UIButton({ 880, 410 }, button_type::TERMS_OF_USE);
	elements.add(terms_of_use_button);
	UIelement* credits_button = new UIButton({ 880, 368 }, button_type::CREDITS);
	elements.add(credits_button);
	UIelement* cinematics_button = new UIButton({ 880, 326 }, button_type::CINEMATICS);
	elements.add(cinematics_button);

	UIelement* account_check = new UICheckBox({ 10, 475 }, check_type::ACCOUNT_NAME);
	elements.add(account_check);

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	p2List_item<UIelement*>* item = elements.start;
	bool ret = true;
	while (item != NULL)
	{
		if (MouseInside(&item->data->GetRect()))
		{
			item->data->OnMouseOver();
			if (App->input->GetMouseButtonDown(1) == KEY_DOWN)//left click
			{
				item->data->OnClick();
			}
		}
		if (App->input->GetMouseButtonDown(1) == KEY_UP)
		{
			if (ret == true)
				ret = item->data->OnRelease();

		}
		item = item->next;
	}

	return ret;
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
	App->render->Blit(background, 0, 0);

	p2List_item<UIelement*>* item = elements.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
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

