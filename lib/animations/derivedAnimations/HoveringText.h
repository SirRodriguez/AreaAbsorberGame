#ifndef HOVERINGTEXT_H
#define HOVERINGTEXT_H

class HoveringText : public Animation{
protected:
	olc::Pixel color;
	const std::string text;
	int height;
	int scale;

public:
	HoveringText()
	: Animation(){}
	HoveringText(olc::PixelGameEngine& pge, olc::vi2d& pos, int _maxFrames, const olc::Pixel _color, const std::string& _text, int _height, int _scale)
	: Animation(pge, pos, _maxFrames), color(_color), text(_text), height( _height), scale(_scale){}

	virtual void drawFrame() override {

		olc::vi2d textSize = pixelGameEngine->GetTextSize(text);

		int h = (currentFrame * height) / maxFrames;

		olc::vi2d loc = position + olc::vi2d(0, -h);

		pixelGameEngine->DrawString(
			loc.x - scale * (textSize.x / 2),
			loc.y - scale * (textSize.y / 2),
			text,
			color,
			scale
		);
	}

	virtual void clear() override {
		decrementFrame();

		olc::vi2d textSize = pixelGameEngine->GetTextSize(text);

		int h = (currentFrame * height) / maxFrames;

		olc::vi2d loc = position + olc::vi2d(0, -h);

		pixelGameEngine->DrawString(
			loc.x - scale * (textSize.x / 2),
			loc.y - scale * (textSize.y / 2),
			text,
			olc::WHITE,
			scale
		);

		incrementFrame();
	}
};

#endif