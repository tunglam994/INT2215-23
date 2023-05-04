
#include "Skill.h"

Skill::Skill()
{
    width_frame_ = 0;
    height_frame_ = 0;
    frame_ = 0;
    is_activating_ = true;
    damaging_time_ = 0;
    is_damaging_ = false;
}

Skill::~Skill()
{

}

SDL_Rect Skill::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}

bool Skill::loadUltimate(std::string path, SDL_Renderer* screen)
{
    bool ret = ImageBase::loadImg(path, screen);

    if (ret == true)
    {
        width_frame_ = rect_.w / ULTIMATE_FRAME;
        height_frame_ = rect_.h;
    }
    return ret;
}

bool Skill::loadBossskill(std::string path, SDL_Renderer* screen)
{
    bool ret = ImageBase::loadImg(path, screen);

    if (ret == true)
    {
        width_frame_ = rect_.w / BOSS_SKILL_FRAME;
        height_frame_ = rect_.h;
    }
    return ret;
}

void Skill::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < ULTIMATE_FRAME; i++)
        {
            p_frame_clip_[i].x = 0 + width_frame_ * i;
            p_frame_clip_[i].y = 0;
            p_frame_clip_[i].w = width_frame_;
            p_frame_clip_[i].h = height_frame_;
        }
    }
}

void Skill::boss_skill_set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < BOSS_SKILL_FRAME; i++)
        {
            b_frame_clip_[i].x = 0 + width_frame_ * i;
            b_frame_clip_[i].y = 0;
            b_frame_clip_[i].w = width_frame_;
            b_frame_clip_[i].h = height_frame_;
        }
    }
}



void Skill::Show(SDL_Renderer* des)
{
    SDL_RendererFlip flip_type = SDL_FLIP_NONE;
    if (Skill_direction_ == SKILL_LEFT) flip_type = SDL_FLIP_HORIZONTAL;
    else flip_type = SDL_FLIP_NONE;

    frame_++;
    if (frame_ == damaging_time_) is_damaging_ = true;
    else if (frame_ == damaging_time_ + 1) is_damaging_ = false;

    if (frame_ >= ULTIMATE_FRAME)
    {
        frame_ = 0;
        is_activating_ = false;
    }

    SDL_Rect* current_clip = &p_frame_clip_[frame_];

    SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

    SDL_RenderCopyEx(des, p_texture_, current_clip, &renderQuad, 0.0, NULL, flip_type);
}

void Skill::boss_skill_Show(SDL_Renderer* des)
{
    SDL_RendererFlip flip_type = SDL_FLIP_NONE;
    if (Skill_direction_ == SKILL_LEFT) flip_type = SDL_FLIP_HORIZONTAL;
    else flip_type = SDL_FLIP_NONE;

    frame_++;
    if (frame_ == damaging_time_) is_damaging_ = true;
    else if (frame_ == damaging_time_ + 1) is_damaging_ = false;

    if (frame_ >= BOSS_SKILL_FRAME)
    {
        frame_ = 0;
        is_activating_ = false;
    }

    SDL_Rect* current_clip = &b_frame_clip_[frame_];

    SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

    SDL_RenderCopyEx(des, p_texture_, current_clip, &renderQuad, 0.0, NULL, flip_type);
}