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
/*	uint number_of_tiles_x = (tilesets.image_width - tilesets.margin) / (tilesets.tile_width + tilesets.margin);
	uint number_of_tiles_y = (tilesets.image_height - tilesets.margin) / (tilesets.tile_height + tilesets.margin);*/

	App->render->Blit(tilesets.start->data.tileset_texture,0,0);

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map

	map_file.reset();
	delete(&map);
	delete(&tilesets);

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

	pugi::xml_node tileset_node = map_node.child("tileset");	
	p2SString string1 = tileset_node.name();
	p2SString string2 = "tileset";	
	while (string1.Length() == string2.Length())
	{
		tilesets.add(load_tileset(&tileset_node));
		map.number_of_tiles++;
		LOG("Loaded tileset %s",tileset_node.attribute("name").as_string());
		tileset_node = tileset_node.next_sibling();
		string1 = tileset_node.name();
	}


	pugi::xml_node layer_node = map_node.child("layer");
	string1 = layer_node.name();
	string2 = "layer";
	while (string1.Length() == string2.Length())
	{
		layers.add(load_layer(&layer_node));
		LOG("Loaded layer %s", layer_node.attribute("name").as_string());
		layer_node = layer_node.next_sibling();
		string1 = layer_node.name();
	}


	if(ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
		LOG("map, tileset/s and layers have been successfully loaded");
	}

	map_loaded = ret;

	return ret;
}
	tileset j1Map::load_tileset( pugi::xml_node* tileset_node)
	{
		tileset tiles;
		tiles.spacing = tileset_node->attribute("spacing").as_uint();
		tiles.tile_width = tileset_node->attribute("tilewidth").as_uint();
		tiles.tile_height = tileset_node->attribute("tileheight").as_uint();
		tiles.spacing = tileset_node->attribute("spacing").as_uint();
		tiles.margin = tileset_node->attribute("margin").as_uint();
		tiles.image_width = tileset_node->child("image").attribute("width").as_uint();
		tiles.image_height = tileset_node->child("image").attribute("height").as_uint();
		tiles.name = tileset_node->attribute("name").as_string();
		tiles.firstgid = tileset_node->attribute("firstgid").as_uint();

		p2SString image_directory = tileset_node->child("image").attribute("source").as_string();
		tiles.tileset_texture = App->tex->Load(image_directory.GetString());

		return tiles;
	}
	layer j1Map::load_layer(pugi::xml_node* layer_node)
	{
		layer layer_1;
		layer_1.width = layer_node->attribute("width").as_uint();
		layer_1.height = layer_node->attribute("height").as_uint();
		layer_1.name = layer_node->attribute("name").as_string();
		return layer_1;
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