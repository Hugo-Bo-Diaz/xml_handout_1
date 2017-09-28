#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

enum perspective : int
{
	INVALID = 0,
	ORTHOGONAL = 1,
	ISOMETRICAL = 2,
	HEXAGONAL = 3
};
enum render_order : int
{
	INVALID_ORDER = 0,
	RIGHT_DOWN = 1,
	LEFT_DOWN = 2,
	RIGHT_UP = 3,
	LEFT_UP = 4
};

struct map_info
{
	uint version;
	perspective perspective = ORTHOGONAL;
	render_order order = INVALID_ORDER;
	uint width = 0;
	uint height = 0;
	uint tile_width = 0;
	uint tile_height = 0;
	uint next_object_id = 1;

};


// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
// ----------------------------------------------------

struct tileset
{
	uint firstgid;
	p2SString name;
	uint tile_width;
	uint tile_height;
	uint spacing;
	uint margin;
	uint image_height;
	uint image_width;
	SDL_Texture* tileset_texture;
};
// TODO 1: Create a struct needed to hold the information to Map node

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

private:


public:

	// TODO 1: Add your struct for map info as public for now
	
	map_info map;
	p2List<tileset> tilesets_1;
	tileset tilesets;
	
private:

	pugi::xml_document	map_file;
	pugi::xml_node		map_node;
	pugi::xml_node		tileset_node;
	p2SString			folder;
	bool				map_loaded;
	void load_tileset(tileset* tiles,pugi::xml_node* map_node);
	void load_map_data();

};

#endif // __j1MAP_H__