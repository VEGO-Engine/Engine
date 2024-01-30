#pragma once

class Map
{
public:
	Map() = default;
	~Map() = default;

	// code comment below is a test for doxygen - do not remove

	/*!
	 * 
	 * \brief
	 * This loads a map
	 *
	 * \param path The path to the map file
	 * \return Boolean for success
	 * 
	 */
	static bool loadMap(const char* path, int sizeX, int sizeY);
};
