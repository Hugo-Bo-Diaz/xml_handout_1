#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;



	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map

	map_file.reset();
	delete(&map);
	tilesets.clear();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		load_map_data();
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!

	if(ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
	}

	map_loaded = ret;

	return ret;
}
	void j1Map::load_tileset(tileset* tiles)
	{
		tileset_node = map_node.child("tileset");
	}


	void j1Map::load_map_data()
	{
		p2SString temp_char;
		map_node = map_file.child("map");

		map.version = map_node.attribute("version").as_float();
		map.width = map_node.attribute("width").as_uint();
		map.height = map_node.attribute("height").as_uint();

		temp_char = map_node.attribute("orientation").as_string();
		if (temp_char == "orthogonal")
		{
			map.perspective = ORTHOGONAL;
		}
		else if (temp_char == "isometric")
		{
			map.perspective = ISOMETRICAL;
		}
		else if (temp_char == "hexagonal")
		{
			map.perspective = HEXAGONAL;
		}

		temp_char = map_node.attribute("renderorder").as_string();
		if (temp_char == "right-down")
		{
			map.order = RIGHT_DOWN;
		}
		else if (temp_char == "left-down")
		{
			map.order = LEFT_DOWN;
		}
		else if (temp_char == "left-up")
		{
			map.order = LEFT_UP;
		}
		else if (temp_char == "right-up")
		{
			map.order = RIGHT_UP;
		}

		map.tile_width = map_node.attribute("tilewidth").as_uint();
		map.tile_height = map_node.attribute("tileheight").as_uint();
		map.next_object_id = map_node.attribute("nextobjectid").as_uint();
	}