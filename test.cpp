class Flower: public Circle{
protected:
	std::vector<Pedal> pedals;
	int numPedals;
	double degOffset;

	// Pedal Radius
	int getPedalRadius(int r){ return r / 2; }
	int getPedalRadius(){ return getPedalRadius(getRadius()); }

	olc::vi2d getLocationOffsetFromDeg(double d){
		int r = getRadius() + getPedalRadius();
		int x = r * std::cos(d * PI() / 180);
		int y = r * std::sin(d * PI() / 180);

		return olc::vi2d(x, y);
	}

public:
	Flower()
	: Circle(){}
	Flower(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, const olc::Pixel& _pedalColor, int newRadius, int _numPedals, double _degOffset)
	: Circle(pge, ac, pos, _speed, _color, newRadius), numPedals(_numPedals), degOffset(_degOffset){
		if(numPedals > 0){
			double increment = 360 / numPedals;
			double deg = increment + degOffset;

			for(int i = 0; i < numPedals; ++i){
				olc::vi2d locOffset = getLocationOffsetFromDeg(deg);
				olc::vi2d loc = pos + locOffset;
				// Here when it does the push back is when it crashes ---
				pedals.push_back(Pedal(pge, ac, loc, _speed, _pedalColor, getPedalRadius()));
				deg += increment;
			}
		}
	}

};

class Car: public Flower{
public:
	Car()
	: Flower(), life(0){}
	Car(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, const olc::Pixel& _wheelColor, int newRadius)
	// In Flower is what is crashing ---
	: Flower(pge, ac, pos, _speed, _color, _wheelColor, newRadius, NUMWHEELS, WHEELANGLEOFFSET), life(0){
	}
};

class MainCircle: public Circle{
protected:
	TrapSquare trapSquare;
	Car car;
	BuddyCircle buddy;

	Direction dir;

	int lives;
	int initialRadius;
	int baseSpeed;

public:
	MainCircle(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d pos, int _speed, const olc::Pixel& _color, int _initialRadius, int newLives, const olc::Pixel& carColor, const olc::Pixel& wheelColor, int carRadius, int buddySpeed, const olc::Pixel& buddyColor)
	: Circle(pge, ac, pos, _speed, _color, _initialRadius), 
		dir(Direction::DOWN){
			lives = newLives;
			initialRadius = _initialRadius;
			baseSpeed = _speed;
			trapSquare = TrapSquare(pge, ac, pos, _speed, _color, _initialRadius);
			// This object is what crashes ---
			car = Car(pge, ac, pos, _speed, carColor, wheelColor, carRadius);
			buddy = BuddyCircle(pge, ac, pos, buddySpeed, buddyColor, 0, 0);
		}
};

class MainCircleList: public ShapeList{
protected:
	MainCircle* mainCircle;
	uint8_t default_speed;
	olc::Pixel default_color;
	uint8_t default_initial_size;
	olc::Pixel default_circle_car_color;
	olc::Pixel default_circle_car_wheel_color;
	uint8_t default_circle_car_radius;
	uint8_t default_buddy_circle_speed;
	olc::Pixel default_buddy_circle_color;

public:
	MainCircleList()
	: ShapeList(ShapeType::MAINCIRCLE){}
	MainCircleList(
		olc::PixelGameEngine& pge, 
		AnimationContainer& ac, 
		uint32_t _speed, 
		olc::Pixel _color, 
		uint8_t _initial_size, 
		olc::Pixel _circle_car_color, 
		olc::Pixel _cirlce_car_wheel_color, 
		uint8_t _circle_car_radius, 
		uint8_t _buddy_circle_speed, 
		olc::Pixel _buddy_circle_color
	)
	: ShapeList(pge, ac, ShapeType::MAINCIRCLE), 
		default_speed(_speed),
		default_color(_color),
		default_initial_size(_initial_size),
		default_circle_car_color(_circle_car_color),
		default_circle_car_wheel_color(_cirlce_car_wheel_color),
		default_circle_car_radius(_circle_car_radius),
		default_buddy_circle_speed(_buddy_circle_speed),
		default_buddy_circle_color(_buddy_circle_color)
		{
		olc::vi2d centerPos = olc::vi2d(pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight() / 2);
		uint8_t numLives = 0;
		// New gets called here ---
		mainCircle = new MainCircle(
			pge,
			ac, 
			centerPos,
			default_speed,
			default_color, 
			default_initial_size, 
			numLives,
			default_circle_car_color,
			default_circle_car_wheel_color,
			default_circle_car_radius,
			default_buddy_circle_speed,
			default_buddy_circle_color
		);
	}
};