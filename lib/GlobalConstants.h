#ifndef GLOBALCONSTANTS_H
#define GLOBALCONSTANTS_H

///////////////
// Resources //
///////////////

// White Circle
const std::string whiteCircleFile = "lib/resources/whiteCircle.png";
const int whiteCirclePixelWidth = 1000;
const int whiteCirclePixelHeight = 1000;
const float whiteCircleScaleToOneRadius = 0.002f;
olc::Sprite* whiteCircleSprite;

// White Equilateral Triangle
const std::string whiteEquilateralTriangleFile = "lib/resources/whiteEquilateralTriangle.png";
const int whiteEquilateralTriangleWidth = 1000;
const int whiteEquilateralTriangleHeight = 1000;
const float whiteEquilateralTriangleScaleToOneHeight = 0.001f;
olc::Sprite* whiteEquilateralTriangleSprite;

// White Line
const std::string whiteLineFile = "lib/resources/thickWhiteLine.png";
const int whiteLineWidth = 1000;
const int whiteLineHeight = 1000;
const float whiteLineScaleToOneLength = 0.0007071f;
olc::Sprite* whiteLineSprite;

// White Square Outline
const std::string whiteSquareOutlineFile = "lib/resources/whiteSquareOutline.png";
const int whiteSquareOutlineWidth = 1000;
const int whiteSquareOutlineHeight = 1000;
const float whiteSquareOutlineScaleToOneLength = 0.001f;
olc::Sprite* whiteSquareOutlineSprite;

#endif