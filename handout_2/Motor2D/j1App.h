#ifndef __j1APP_H__
#define __j1APP_H__

#include "p2List.h"
#include "j1Module.h"
#include "PugiXml\src\pugixml.hpp"

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1Scene;

class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	// TODO 1: Create methods to save and load
	// that can be called anytime, even if they 
	// will one execute by the very end of the frame
	// Load / Save
	bool load()
	{
		needs_load = true;
		return true;
	};
	const bool save()
	{
		needs_save = true;
		return true;
	};

	bool reset()
	{
		needs_reset = true;
		return true;
	}

private:
	bool real_load();
	bool real_save();
	bool real_reset();


	// Load config file
	bool LoadConfig();

	bool Load_save_file();
	bool Load_default_values();

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

public:

	// Modules
	j1Window*			win;
	j1Input*			input;
	j1Render*			render;
	j1Textures*			tex;
	j1Audio*			audio;
	j1Scene*			scene;

private:

	p2List<j1Module*>	modules;
	uint				frames;
	float				dt;
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	pugi::xml_node		app_config;
	int					argc;
	char**				args;
	//this variables are for the save/load/reset
	bool needs_save =	false;
	bool needs_load =	false;
	bool needs_reset =	false;
	pugi::xml_document	save_file;
	pugi::xml_node		save_node;

	pugi::xml_document	default_values_file;
	pugi::xml_node		default_values_node;

	p2SString			title;
	p2SString			organization;

};

extern j1App* App;

#endif