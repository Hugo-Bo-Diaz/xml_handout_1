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
#include "UItextbox.h"

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

	UIelement* copyright_text = new UItext({320,560}, "Copyright 2004 2007 Blizzard entretainment All rights reserved", { 255,255,0,255 });
	copyright_text->callback = this;
	elements.add(copyright_text);
	UIelement* version_text = new UItext({ 10,546 }, "Version 2.0.12 (6546) Release", { 255,255,0,255 });
	version_text->callback = this;
	elements.add(version_text);
	UIelement* date_text = new UItext({ 10,560 }, "Mar 30 2007", { 255,255,0,255 });
	date_text->callback = this;
	elements.add(date_text);
	UIelement* web_text = new UItext({ 920,450 }, "WoWps.org TBC", { 150,150,150,255 });
	web_text->callback = this;
	elements.add(web_text);

	UIelement* wow_logo = new UIimage({ 0, 0 }, { 133,21,319,127 });
	wow_logo->callback = this;
	elements.add(wow_logo);
	UIelement* esrb_rating = new UIimage({ 15, 500 }, { 327,153,127,40 });
	esrb_rating->callback = this;
	elements.add(esrb_rating);
	UIelement* blizzard_logo = new UIimage({ 451, 485 }, { 0,0,122,74 });
	blizzard_logo->callback = this;
	elements.add(blizzard_logo);

	UIelement* login_button = new UIButton({ 446, 350 }, button_type::LOGIN);
	login_button->callback = this;
	elements.add(login_button);

	UIelement* manage_account_button = new UIButton({ 10, 390 }, button_type::MANAGE_ACCOUNT);
	manage_account_button->callback = this;
	elements.add(manage_account_button);
	UIelement* community_site = new UIButton({ 10, 430 }, button_type::COMUNITY_SITE);
	community_site->callback = this;
	elements.add(community_site);

	UIelement* quit_button = new UIButton({ 880, 515 }, button_type::QUIT);
	quit_button->callback = this;
	elements.add(quit_button);
	UIelement* terms_of_use_button = new UIButton({ 880, 410 }, button_type::TERMS_OF_USE);
	terms_of_use_button->callback = this;
	elements.add(terms_of_use_button);
	UIelement* credits_button = new UIButton({ 880, 368 }, button_type::CREDITS);
	credits_button->callback = this;
	elements.add(credits_button);
	UIelement* cinematics_button = new UIButton({ 880, 326 }, button_type::CINEMATICS);
	cinematics_button->callback = this;
	elements.add(cinematics_button);

	UIelement* account_check = new UICheckBox({ 10, 475 }, check_type::ACCOUNT_NAME);
	account_check->callback = this;
	elements.add(account_check);


	UIelement* name_textbox = new UITextbox({450,200}, "Account Name");
	name_textbox->callback = this;
	elements.add(name_textbox);
	UIelement* password_textbox = new UITextbox({ 450,275 }, "Account Password");
	password_textbox->callback = this;
	elements.add(password_textbox);


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
			item->data->mouseover = true;
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

bool j1Gui::UIinteraction(UIelement* element)
{
	bool ret = true;
	if (element->type_of_element == BUTTON)
	{
		UIButton* button = (UIButton*)element;
		switch (button->type)
		{
		case LOGIN:
		{LOG("U HAVE LOGGED IN");
		break; }
		case CINEMATICS:
		{LOG("WE HAVE NONE YET");
		break; }
		case CREDITS:
		{LOG("I DID THIS");
		break; }
		case TERMS_OF_USE:
		{LOG("I DON'T LET U USE THIS");
		break; }
		case MANAGE_ACCOUNT:
		{LOG("WHAT ACCOUNT");
		break; }
		case COMUNITY_SITE:
		{LOG("WHAT COMUNITY");
		break; }
		case QUIT:
		{ret = false;
		break; }
		default:
		{LOG("LOL Y");
		break; }
		}
	}
	return ret;
}

// class Gui ---------------------------------------------------

