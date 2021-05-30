

#define square(x) ((x)*(x))

// 
// Circle & Circle Collision detection functions
// 

bool circleCircleCollision(int x, int y, int r, int x2, int y2, int r2){
	return square(x - x2) + square(y - y2) <= square(r + r2);
}

bool circleCircleCollision(olc::vi2d pos, int r, olc::vi2d pos2, int r2){
	return circleCircleCollision(pos.x, pos.y, r, pos2.x, pos2.y, r2);
}

bool circleCircleCollision(Circle& c, Circle& c2){
	return circleCircleCollision(c.getPosition(), c.getRadius(), c2.getPosition(), c2.getRadius());
}

// 
// Circle & Line collision detection functions
// 

bool circleLineCollision(int x, int y, int r, int sx, int sy, int ex, int ey){
	int SEx = ex - sx;
	int SEy = ey - sy;

	int SCx = x - sx;
	int SCy = y - sy;

	int lineLength = square(SEx) + square(SEy);

	int t = std::max(0, std::min(lineLength, (SEx * SCx + SEy * SCy)));

	int closestPointX = sx * lineLength + t * SEx;
	int closestPointY = sy * lineLength + t * SEy;

	float distSqr = square(x - closestPointX / lineLength) + square(y - closestPointY / lineLength);
	return distSqr <= square(r);
}

bool circleLineCollision(olc::vi2d pos, int r, olc::vi2d s, olc::vi2d e){
	return circleLineCollision(pos.x, pos.y, r, s.x, s.y, e.x, e.y);
}

// bool circleLineCollision(Circle& c, Line& l){
// 	circleLineCollision(c.getPosition(), l.)
// }

// 
// Circle & Triangle Collision functions
// 

bool circleTriangleCollision(olc::vi2d pos, int r, olc::vi2d p1, olc::vi2d p2, olc::vi2d p3){
	return circleLineCollision(pos, r, p1, p2) ||
		circleLineCollision(pos, r, p2, p3) ||
		circleLineCollision(pos, r, p3, p1);
}

bool circleTriangleCollision(Circle& c, Triangle& t){
	return circleTriangleCollision(c.getPosition(), c.getRadius(), t.topPoint(), t.botLeftPoint(), t.botRightPoint());
}