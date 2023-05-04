#include "Bar.h"

Bar::Bar()
{
	current_width_ = 0;
	max_width_ = 0;
	max_height_ = 0;
	bar_x_ = 0;
	bar_y_ = 0;
}

Bar::~Bar()
{

}


bool Bar::loadBar(std::string path1, std::string path2, SDL_Renderer* screen)
{
	bool ret1 = back_bar_.loadImg(path1, screen);
	bool ret2 = current_bar_.loadImg(path2, screen);
	SDL_Rect rect = current_bar_.GetRect();
	max_height_ = rect.h;
	max_width_ = rect.w;

	if (ret1 && ret2) return true;
	return false;
}

void Bar::setBarPosition(const int x1, const int y1, const int x2, const int y2)
{
	back_bar_.SetRect(x1, y1);
	current_bar_.SetRect(x2, y2);
	bar_x_ = x2;
	bar_y_ = y2;
}

void Bar::updateBar(const int current_value, const int max_value)
{
	current_width_ = max_width_ * current_value / max_value * 1.0;
}

void Bar::showBar(SDL_Renderer* screen)
{
	SDL_Rect srcRect = { 0, 0, current_width_, max_height_ };
	SDL_Rect dstRect = { bar_x_, bar_y_, current_width_, max_height_ };

	SDL_RenderCopy(screen, current_bar_.GetObject(), &srcRect, &dstRect);

	back_bar_.Render(screen);
}

void Bar::FreeGUIBar()
{
	back_bar_.Free();
	current_bar_.Free();
	current_width_ = 0;
	max_height_ = 0;
	max_width_ = 0;
}
