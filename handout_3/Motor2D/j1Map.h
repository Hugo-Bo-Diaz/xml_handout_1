#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

enum perspective : int
{
	ORTOGONAL = 1,
	ISOMETRICAL = 2,
	HEXAGONAL = 3
};

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
// ----------------------------------------------------

struct tileset
{
	uint firstgid;
	char* name;
	uint tile_measures[2];
	uint spacing;
	uint margin;
	p2SString image;
	uint image_measures[2];
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

	struct map_info
	{
		uint version;
		perspective perspective = ORTOGONAL;
		uint render_order_x = 1;
		uint render_order_y = 1;
		uint measures[2];
		uint tile_measures[2];
		uint next_object_id = 1;

	};
	

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__