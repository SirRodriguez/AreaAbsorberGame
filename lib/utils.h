#ifndef UTILS_H
#define UTILS_H

#include "./shapes/derivedShapes/Square.h"
#include "./shapes/derivedShapes/flower/Flower.h"
#include "./shapes/derivedShapes/flower/Pedal.h"

#define square(x) ((x)*(x))

// 
// Circle & Point Collision detection functions
// 
bool circlePointCillision(int cx, int cy, int r, int px, int py){
	return square(cx - px) + square(cy - py) <= square(r);
}

bool circlePointCillision(olc::vi2d pos, int r, olc::vi2d p){
	return circlePointCillision(pos.x, pos.y, r, p.x, p.y);
}

bool circlePointCillision(Circle& c, olc::vi2d p){
	return circlePointCillision(c.getPosition(), c.getRadius(), p);
}

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
	// Check if points are the same ie sx = ex and sy = ey
	if(sx == ex && sy == ey){
		return circlePointCillision(x, y, r, sx, sy);
	}

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

bool circleLineCollision(Circle& c, Line& l){
	return circleLineCollision(c.getPosition(), c.getRadius(), l.getStartPoint(), l.getEndPoint());
}

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

// 
// Circle & Square Collision functions
// 

bool circleSquareCollision(olc::vi2d pos, int r, olc::vi2d tlp, olc::vi2d trp, olc::vi2d blp, olc::vi2d brp){
	return circleLineCollision(pos, r, tlp, trp) || 
		circleLineCollision(pos, r, trp, brp) || 
		circleLineCollision(pos, r, brp, blp) ||
		circleLineCollision(pos, r, blp, tlp);
}

bool circleSquareCollision(Circle& c, Square& s){
	return circleSquareCollision(c.getPosition(), c.getRadius(), s.getTopLeftPoint(), s.getTopRightPoint(), s.getBotLeftPoint(), s.getBotRightPoint());
}

// 
// Line & Line Collision functions
// 

bool lineLineCollision(int sx, int sy, int ex, int ey, int sx2, int sy2, int ex2, int ey2){
	// FROM: http://paulbourke.net/geometry/pointlineplane/


	float denom = (((float)ey2 - (float)sy2)*((float)ex - (float)sx)) -
                      (((float)ex2 - (float)sx2)*((float)ey - (float)sy));

    float nume_a = (((float)ex2 - (float)sx2)*((float)sy - (float)sy2)) -
                   (((float)ey2 - (float)sy2)*((float)sx - (float)sx2));

    float nume_b = (((float)ex - (float)sx)*((float)sy - (float)sy2)) -
                   (((float)ey - (float)sy)*((float)sx - (float)sx2));

    if(denom == 0.0f)
    {
        if(nume_a == 0.0f && nume_b == 0.0f)
        {
            return true; // COINCIDENT
        }
        return false; // PARALLEL
    }

    float ua = nume_a / denom;
    float ub = nume_b / denom;

    if(ua >= 0.0f && ua <= 1.0f && ub >= 0.0f && ub <= 1.0f)
    {
        // Get the intersection point.
        // intersection.x_ = begin_.x_ + ua*(end_.x_ - begin_.x_);
        // intersection.y_ = begin_.y_ + ua*(end_.y_ - begin_.y_);

        return true; // INTERESECTING
    }

    return false; // NOT_INTERESECTING
}

bool lineLineCollision(olc::vi2d s, olc::vi2d e, olc::vi2d s2, olc::vi2d e2){
	return lineLineCollision(s.x, s.y, e.x, e.y, s2.x, s2.y, e2.x, e2.y);
}

bool lineLineCollision(Line& l, Line& l2){
	return lineLineCollision(l.getStartPoint(), l.getEndPoint(), l2.getStartPoint(), l2.getEndPoint());
}

// 
// Line Square Collision Functions
// 

bool lineSquareCollision(olc::vi2d ls, olc::vi2d le, olc::vi2d stl, olc::vi2d str, olc::vi2d sbl, olc::vi2d sbr){
	return lineLineCollision(ls, le, stl, str) ||
		lineLineCollision(ls, le, str, sbr) ||
		lineLineCollision(ls, le, sbr, sbl) ||
		lineLineCollision(ls, le, sbl, stl);
}

bool lineSquareCollision(Line& l, Square& s){
	return lineSquareCollision(l.getStartPoint(), l.getEndPoint(), s.getTopLeftPoint(), s.getTopRightPoint(), s.getBotLeftPoint(), s.getBotRightPoint());
}

// 
// Circle Flower Collision Functions
// 

bool circlePedalsCollision(Circle& c, std::vector<Pedal>& pedals){
	for(auto it = pedals.begin(); it != pedals.end(); ++it)
		if(circleCircleCollision(c, *it))
			return true;

	return false;
}

bool circleFlowerCollision(Circle& c, Flower& f){
	return circlePedalsCollision(c, f.getPedals()) || circleCircleCollision(c, f);
}

// 
// Line Flower Collision Functions
// 

bool linePedalsCollision(Line& l, std::vector<Pedal>& pedals){
	for(auto it = pedals.begin(); it != pedals.end(); ++it)
		if(circleLineCollision(*it, l))
			return true;

	return false;
}

bool lineFlowerCollision(Line& l, Flower& f){
	return linePedalsCollision(l, f.getPedals()) || circleLineCollision(f, l);
}

// 
// Triangle Flower Collision Functions
// 

bool trianglePedalsCollision(Triangle& t, std::vector<Pedal>& pedals){
	for(auto it = pedals.begin(); it != pedals.end(); ++it)
		if(circleTriangleCollision(*it, t))
			return true;

	return false;
}

bool triangleFlowerCollision(Triangle& t, Flower& f){
	return trianglePedalsCollision(t, f.getPedals()) || circleTriangleCollision(f, t);
}

// 
// Square Flower Collision Functions
// 

bool squarePedalsCollision(Square& s, std::vector<Pedal>& pedals){
	for(auto it = pedals.begin(); it != pedals.end(); ++it)
		if(circleSquareCollision(*it, s))
			return true;

	return false;
}

bool squareFlowerCollision(Square& s, Flower& f){
	return squarePedalsCollision(s, f.getPedals()) || circleSquareCollision(f, s);
}

#endif