#ifndef SHAPESCONTAINER
#define SHAPESCONTAINER

struct ShapesContainer{
	int id;
	std::map<int, std::pair<olc::vi2d, int>> otherCircle; // key = id, value = location, radius
	int maxRadius;

	void initialize(){
		id = 0;
		otherCircle.clear();
		maxRadius = 50;
	}

	// Iterators
	std::map<int, std::pair<olc::vi2d, int>>::iterator begin(){
		return otherCircle.begin();
	}
	std::map<int, std::pair<olc::vi2d, int>>::iterator end(){
		return otherCircle.end();
	}

	void addShape(int32_t screenWidth){
		olc::vi2d loc = olc::vi2d(rand() % screenWidth, 0);
		int radius = rand() % maxRadius;
		otherCircle[id] = std::make_pair(loc, radius);
		++id;
	}

	void moveShapes(int32_t screenHeight, int pixels){
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			it->second.first += olc::vi2d(0, pixels);
			// if it reaches the bottom, delete it
			int pos = it->second.first.y;
			if(pos == screenHeight){
				deleteShape(it->first);
			}
		}
	}

	void deleteShape(int shapeId){
		otherCircle.erase(shapeId);
	}

	void deleteAllShapes(){
		otherCircle.clear();
	}

	// return 0 if no collision
	// return -1 if other circle is bigger
	// return any positive number means that the circle was smaller and thats the size
	int checkCollision2(const olc::vi2d& pos, const int& radius){
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			// Get the distances
			int32_t x = it->second.first.x;
			int32_t y = it->second.first.y;
			double distance = std::sqrt( (pos.x - x) * (pos.x - x) + (pos.y - y) * (pos.y - y) );

			// Check if distanceis less or equal to the two radius combined
			if(distance <= it->second.second + radius){
				// if the other circle is bigger
				if(it->second.second > radius){
					return -1;
				// else if the distance is less than or equal
				}else{
					deleteShape(it->first);
					return it->second.second;
				}
			}
		}

		return 0;
	}
};

#endif