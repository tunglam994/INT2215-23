
#include "CommonFunction.h"
#include "Background.h"

Background::Background()
{
    layer1_.x = 0;
    layer1_.y = 0;
    layer1_.w = 0;
    layer1_.h = 0;
    layer2_.x = SCREEN_WIDTH;
    layer2_.y = 0;
    layer2_.w = 0;
    layer2_.h = 0;
}

Background::~Background()
{

}


bool Background::loadBackground(std::string path, SDL_Renderer* screen)
{
    bool ret = ImageBase::loadImg(path, screen);
    if (ret)
    {
        layer1_.w = rect_.w;
        layer1_.h = rect_.h;
        layer2_.w = rect_.w;
        layer2_.h = rect_.h;
    }
    return ret;
}

void Background::renderBackground(SDL_Renderer* des, const SDL_Rect* clip)
{
    layer1_.x -= SCROLLING_SPEED;
    layer2_.x -= SCROLLING_SPEED;

    if (layer1_.x < -SCREEN_WIDTH) layer1_.x = SCREEN_WIDTH;
    if (layer2_.x < -SCREEN_WIDTH) layer2_.x = SCREEN_WIDTH;

    /*SDL_Rect renderquad1 = { layer1_.x, layer1_.y, layer1_.w, layer1_.h };
    SDL_Rect renderquad2 = { layer2_.x, layer2_.y, layer2_.w, layer2_.h };*/


    SDL_RenderCopy(des, p_texture_, clip, &layer1_);
    SDL_RenderCopy(des, p_texture_, clip, &layer2_);
}

void Background::freeBackground()
{
    ImageBase::Free();
    layer1_.w = 0;
    layer1_.h = 0;
    layer2_.w = 0;
    layer2_.h = 0;

}


