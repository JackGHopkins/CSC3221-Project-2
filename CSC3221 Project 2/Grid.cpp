#include "Grid.h"

Grid::Grid(int width, int height, std::multimap<int, Shape*> multimap) {
	this->width = width;
	this->height = height;
	this->multimap = multimap;
}

Grid::~Grid() {}

std::multimap<int, Shape*> Grid::GetMultimap() {
	return this->multimap;
}