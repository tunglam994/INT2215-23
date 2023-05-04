#ifndef IMAGE_BASE
#define IMAGE_BASE

#include "CommonFunction.h"

class ImageBase
{
public:
    ImageBase();
    ~ImageBase();
    void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; } 
    SDL_Rect GetRect() const { return rect_; } 
    SDL_Texture* GetObject() const { return p_texture_; } 

    virtual bool loadImg(std::string path, SDL_Renderer* screen); 
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();
protected:
    SDL_Texture* p_texture_; 
    SDL_Rect rect_; 
};

#endif
