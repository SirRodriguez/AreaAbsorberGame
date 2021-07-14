#ifndef UTILS_H
#define UTILS_H

#include "./shapes/derivedShapes/Triangle.h"
#include "./shapes/derivedShapes/Line.h"
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
// Line Triangle collision
// 

bool lineTriangleCollision(olc::vi2d ls, olc::vi2d le, olc::vi2d tp, olc::vi2d blp, olc::vi2d brp){
	return lineLineCollision(ls, le, tp, blp) ||
		lineLineCollision(ls, le, blp, brp) ||
		lineLineCollision(ls, le, brp, tp);
}

bool lineTriangleCollision(Line& l, Triangle& t){
	return lineTriangleCollision(l.getStartPoint(), l.getEndPoint(), t.topPoint(), t.botLeftPoint(), t.botRightPoint());
}

// 
// Triangle Triangle Collision
// 

bool triangleTriangleCollision(olc::vi2d tp, olc::vi2d blp, olc::vi2d brp, olc::vi2d tp2, olc::vi2d blp2, olc::vi2d brp2){
	return lineLineCollision(tp, blp, tp2, blp2) || lineLineCollision(tp, blp, blp2, brp2) || lineLineCollision(tp, blp, brp2, tp2) ||
		lineLineCollision(blp, brp, tp2, blp2) || lineLineCollision(blp, brp, blp2, brp2) || lineLineCollision(blp, brp, brp2, tp2) ||
		lineLineCollision(brp, tp, tp2, blp2) || lineLineCollision(brp, tp, blp2, brp2) || lineLineCollision(brp, tp, brp2, tp2);
}

bool triangleTriangleCollision(Triangle& t, Triangle& t2){
	return triangleTriangleCollision(t.topPoint(), t.botLeftPoint(), t.botRightPoint(), t2.topPoint(), t2.botLeftPoint(), t2.botRightPoint());
}

// 
// Square Square Collision
// 

bool squareSquareCollision(olc::vi2d stl, olc::vi2d str, olc::vi2d sbl, olc::vi2d sbr, olc::vi2d stl2, olc::vi2d str2, olc::vi2d sbl2, olc::vi2d sbr2){
	return lineLineCollision(stl, str, stl2, str2) || lineLineCollision(stl, str, str2, sbr2) || lineLineCollision(stl, str, sbr2, sbl2) || lineLineCollision(stl, str, sbl2, stl2) ||
		lineLineCollision(str, sbr, stl2, str2) || lineLineCollision(str, sbr, str2, sbr2) || lineLineCollision(str, sbr, sbr2, sbl2) || lineLineCollision(str, sbr, sbl2, stl2) ||
		lineLineCollision(sbr, sbl, stl2, str2) || lineLineCollision(sbr, sbl, str2, sbr2) || lineLineCollision(sbr, sbl, sbr2, sbl2) || lineLineCollision(sbr, sbl, sbl2, stl2) ||
		lineLineCollision(sbl, stl, stl2, str2) || lineLineCollision(sbl, stl, str2, sbr2) || lineLineCollision(sbl, stl, sbr2, sbl2) || lineLineCollision(sbl, stl, sbl2, stl2);
}

bool squareSquareCollision(Square& s, Square& s2){
	return squareSquareCollision(s.getTopLeftPoint(), s.getTopRightPoint(), s.getBotLeftPoint(), s.getBotRightPoint(), s2.getTopLeftPoint(), s2.getTopRightPoint(), s2.getBotLeftPoint(), s2.getBotRightPoint());
}

// 
// Square Triangle collision
// 

bool squareTriangleCollision(olc::vi2d stlp, olc::vi2d strp, olc::vi2d sblp, olc::vi2d sbrp, olc::vi2d ttp, olc::vi2d tblp, olc::vi2d tbrp){
	return lineLineCollision(stlp, strp, ttp, tblp) || lineLineCollision(stlp, strp, tblp, tbrp) || lineLineCollision(stlp, strp, tbrp, ttp) ||
		lineLineCollision(strp, sbrp, ttp, tblp) || lineLineCollision(strp, sbrp, tblp, tbrp) || lineLineCollision(strp, sbrp, tbrp, ttp) ||
		lineLineCollision(sbrp, sblp, ttp, tblp) || lineLineCollision(sbrp, sblp, tblp, tbrp) || lineLineCollision(sbrp, sblp, tbrp, ttp) ||
		lineLineCollision(sblp, stlp, ttp, tblp) || lineLineCollision(sblp, stlp, tblp, tbrp) || lineLineCollision(sblp, stlp, tbrp, ttp);
}

bool squareTriangleCollision(Square& s, Triangle& t){
	return squareTriangleCollision(s.getTopLeftPoint(), s.getTopRightPoint(), s.getBotLeftPoint(), s.getBotRightPoint(), t.topPoint(), t.botLeftPoint(), t.botRightPoint());
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

// 
// Flower Flower Collision Functions
// 

bool pedalsPedalsCollision(std::vector<Pedal>& p, std::vector<Pedal>& p2){
	for(auto it = p.begin(); it != p.end(); ++it)
		for(auto it2 = p2.begin(); it2 != p2.end(); ++it2)
			if(circleCircleCollision(*it, *it2))
				return true;

	return false;
}

bool flowerFlowerCollision(Flower& f, Flower& f2){
	return pedalsPedalsCollision(f.getPedals(), f2.getPedals()) ||
		circlePedalsCollision(f, f2.getPedals()) ||
		circlePedalsCollision(f2, f.getPedals()) ||
		circleCircleCollision(f, f2);
}

// 
// Generalized Collision Functions for easy access
// 

// Point Collisions
bool collision(olc::vi2d p, Circle& c){ return circlePointCillision(c, p); }

// Circle Collisions
bool collision(Circle& c, Circle& c2){ return circleCircleCollision(c, c2); }
bool collision(Circle& c, olc::vi2d p){ return circlePointCillision(c, p); }
bool collision(Circle& c, Line& l){ return circleLineCollision(c, l); }
bool collision(Circle& c, Triangle& t){ return circleTriangleCollision(c, t); }
bool collision(Circle& c, Square& s){ return circleSquareCollision(c, s); }
bool collision(Circle& c, Flower& f){ return circleFlowerCollision(c, f); }

// Line Collisions
bool collision(Line& l, Line& l2){ return lineLineCollision(l ,l2); }
bool collision(Line& l, Circle& c){ return circleLineCollision(c, l); }
bool collision(Line& l, Square& s){ return lineSquareCollision(l, s); }
bool collision(Line& l, Triangle& t){ return lineTriangleCollision(l, t); }
bool collision(Line& l, Flower& f){ return lineFlowerCollision(l, f); }

// Triangle Collisions
bool collision(Triangle& t, Triangle& t2){ return triangleTriangleCollision(t, t2); }
bool collision(Triangle& t, Circle& c){ return circleTriangleCollision(c, t); }
bool collision(Triangle& t, Line& l){ return lineTriangleCollision(l, t); }
bool collision(Triangle& t, Square& s){ return squareTriangleCollision(s, t); }
bool collision(Triangle& t, Flower& f){ return triangleFlowerCollision(t, f); }

// Square Collisions
bool collision(Square& s, Square& s2){ return squareSquareCollision(s, s2); }
bool collision(Square& s, Circle& c){ return circleSquareCollision(c, s); }
bool collision(Square& s, Line& l){ return lineSquareCollision(l, s); }
bool collision(Square& s, Triangle& t){ return squareTriangleCollision(s, t); }
bool collision(Square& s, Flower& f){ return squareFlowerCollision(s, f); }

// Flower Collisions
bool collision(Flower& f, Flower& f2){ return flowerFlowerCollision(f, f2); }
bool collision(Flower& f, Circle& c){ return circleFlowerCollision(c, f); }
bool collision(Flower& f, Line& l){ return lineFlowerCollision(l, f); }
bool collision(Flower& f, Triangle& t){ return triangleFlowerCollision(t, f); }
bool collision(Flower& f, Square& s){ return squareFlowerCollision(s, f); }

#endif