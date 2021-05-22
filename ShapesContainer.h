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
	void drawShapes(AreaAbsorber& aa){
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			aa.FillCircle(it->second.first, it->second.second, olc::RED);
		}
	}
	void hideShapes(AreaAbsorber& aa){
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			aa.FillCircle(it->second.first, it->second.second, olc::WHITE);
		}
	}
	void addShape(AreaAbsorber& aa){
		olc::vi2d loc = olc::vi2d(rand() % aa.ScreenWidth(), 0);
		int radius = rand() % maxRadius;
		otherCircle[id] = std::make_pair(loc, radius);
		++id;
	}
	void moveShapes(AreaAbsorber& aa, int pixels){
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			it->second.first += olc::vi2d(0, pixels);
			// if it reaches the bottom, delete it
			int pos = it->second.first.y;
			if(pos == aa.ScreenHeight()){
				deleteShape(it->first);
			}
		}
	}
	void deleteShape(int shapeId){
		otherCircle.erase(shapeId);
	}
	void eraseAll(AreaAbsorber& aa){
		hideShapes(aa);
		otherCircle.clear();
	}

	// Returns true if the collision destroyed the circle
	bool checkCollision(olc::vi2d pos, int& radius, int& score){
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			// Get the distances
			int32_t x = it->second.first.x;
			int32_t y = it->second.first.y;
			double distance = std::sqrt( (pos.x - x) * (pos.x - x) + (pos.y - y) * (pos.y - y) );

			// check if distance is less or equal the two radius combined
			if(distance <= it->second.second + radius){
				if(it->second.second > radius){
					return true;
				}else{
					deleteShape(it->first);
					// Add the smaller circle to the main Circle
					radius += it->second.second / 2;
					score += it->second.second;
				}
			}
		}

		return false;
	}
};

#endif