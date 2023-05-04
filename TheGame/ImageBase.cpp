// Load và render ?nh
#include "CommonFunction.h"
#include "ImageBase.h"

ImageBase::ImageBase()
{
    p_texture_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

ImageBase::~ImageBase()
{
    Free();
}


bool ImageBase::loadImg(std::string path, SDL_Renderer* screen)
{
    Free();
    SDL_Texture* new_texture = NULL;

    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if (load_surface != NULL)
    {
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_texture != NULL)
        {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface); // vì ?ã chuy?n sang new_texture

    }
    p_texture_ = new_texture;

    return p_texture_ != NULL; // ki?m tra p_object khác Null thì return true
}

void ImageBase::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
    SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };

    SDL_RenderCopy(des, p_texture_, clip, &renderquad);
}

void ImageBase::Free()
{
    if (p_texture_ != NULL)
    {
        SDL_DestroyTexture(p_texture_);
        p_texture_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}


