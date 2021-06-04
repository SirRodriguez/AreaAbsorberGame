#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H

// likelyHoodOfCircles = 50;
// likelyHoodOfPowerUps = 500;
// likelyHoodOfNeedles = 1000;
// likelyHoodOfBuddyPowerUps = 1000;

class ShapeGenerator{
	ShapeContainer* shapeContainer;

	// Likelyhood of shapes generated
	int likelyHoodOfCircles = 0;
	int likelyHoodOfPowerUps = 0;
	int likelyHoodOfNeedles = 0;
	int likelyHoodOfBuddyPowerUps = 0;

	void generateCircles(){
		if(likelyHoodOfCircles - (level - 1) * likelyHoodOfCircles / 10 > 0){
			if(rand() % (likelyHoodOfCircles - (level - 1) * likelyHoodOfCircles / 10 == 0)){
				shapeContainer->addCircle();
			}
		}else{
			if(rand() % 5 == 0){
				shapeContainer->addCircle();
			}
		}
	}
	void generatePowerUps(){

	}
	void generateNeedles(){

	}
	void generateBuddyPowerUps(){

	}

public:
	ShapeGenerator()
	: shapeContainer(nullptr){}
	ShapeGeerator(ShapeContainer& newShapeContainer)
	: shapeContainer(&newShapeContainer){}
	ShapeGeerator(ShapeContainer& newShapeContainer)
	: shapeContainer(&newShapeContainer){}

	void setLikelyHoodOfCircles(int value){ likelyHoodOfCircles = value; }
	void setLikelyHoodOfPowerUps(int value){ likelyHoodOfPowerUps = value; }
	void setLikelyHoodOfNeedles(int value){ likelyHoodOfNeedles = value; }
	void setLikelyHoodOfBuddyPowerUps(int value){ likelyHoodOfBuddyPowerUps = value; }

	void runShapeGenerationFrame(){

	}
};

#endif