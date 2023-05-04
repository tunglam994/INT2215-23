#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "CommonFunction.h"
#include "ImageBase.h"

#define SCROLLING_SPEED 1

class Background : public ImageBase
{
public:
    Background();
    ~Background();

    bool loadBackground(std::string path, SDL_Renderer* screen);
    void renderBackground(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void freeBackground();
private:
    SDL_Rect layer1_;
    SDL_Rect layer2_;
};
#endif


