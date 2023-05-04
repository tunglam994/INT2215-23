
#include "Bullet.h"

Bullet::Bullet()
{
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    frame_ = 0;
    is_move_ = false;
}

Bullet::~Bullet()
{

}

bool Bullet::loadBullet(std::string path, SDL_Renderer* screen)
{
    bool ret = ImageBase::loadImg(path, screen);

    if (ret == true)
    {
        width_frame_ = rect_.w / BULLET_FRAME;
        height_frame_ = rect_.h;
    }
    return ret;
}

void Bullet::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < BULLET_FRAME; i++)
        {
            frame_clip_[i].x = 0 + width_frame_ * i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

SDL_Rect Bullet::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}

void Bullet::HandleMove(const int& x_border, const int& y_border)
{
    if (bullet_direction_ == DIR_RIGHT)
    {
        rect_.x += x_val_;
        if (rect_.x > x_border)
        {
            is_move_ = false;
        }
    }
    else if (bullet_direction_ == DIR_LEFT)
    {
        rect_.x -= x_val_;
        if (rect_.x < 0)
        {
            is_move_ = false;
        }
    }

}
void Bullet::Show(SDL_Renderer* des)
{
    SDL_RendererFlip flip_type = SDL_FLIP_NONE;
    if (bullet_direction_ == DIR_LEFT) flip_type = SDL_FLIP_HORIZONTAL;
    else flip_type = SDL_FLIP_NONE;

    frame_++;

    if (frame_ >= BULLET_FRAME) frame_ = 0;

    SDL_Rect* current_clip = &frame_clip_[frame_];

    SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

    SDL_RenderCopyEx(des, p_texture_, current_clip, &renderQuad, 0.0, NULL, flip_type);
}