#pragma once
#include "Shape.h"
#include <map>


class Grid {
public:
	Grid(int width, int height, std::multimap<int, Shape*> multimap);
	~Grid();

	std::multimap<int, Shape*> GetMultimap();
private:
	int width, height;
	std::multimap<int, Shape*> multimap;
};

