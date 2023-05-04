
#include "Threat.h"


Threat::Threat()
{
    width_frame_ = 0;
    height_frame_ = 0;
    x_val_ = 0.0;
    y_val_ = 0.0;
    x_pos_ = 0.0;
    y_pos_ = 0.0;
    on_ground_ = 0;
    call_back_time_ = 0;
    frame_ = 0;
    animation_a_ = 0;
    animation_b_ = 0;
    direction_ = LEFT;
    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.jump_ = 0;
    threat_type_ = KING;
}

Threat::~Threat()
{

}

SDL_Rect Threat::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}

bool Threat::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = ImageBase::loadImg(path, screen);
    if (ret)
    {
        width_frame_ = rect_.w / THREAT_FRAME_NUM;
        height_frame_ = rect_.h;
    }
    return ret;
}

void Threat::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < THREAT_FRAME_NUM; i++)
        {
            frame_clip_[i].x = 0 + width_frame_ * i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void Threat::Show(SDL_Renderer* des)
{
    if (call_back_time_ == 0)
    {
        SDL_RendererFlip flip_type_ = SDL_FLIP_NONE;
        if (direction_ == LEFT) flip_type_ = SDL_FLIP_NONE;
        else if (direction_ == RIGHT) flip_type_ = SDL_FLIP_HORIZONTAL;
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if (frame_ >= 8)
        {
            frame_ = 0;
        }

        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
        SDL_RenderCopyEx(des, p_texture_, currentClip, &renderQuad, 0.0, NULL, flip_type_);
    }
}

void Threat::DoPlayer(Map& gMap)
{
    if (call_back_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += GRAVITY_SPEED;
        if (y_val_ >= MAX_FALL_SPEED)
        {
            y_val_ = MAX_FALL_SPEED;
        }

        if (input_type_.left_ == 1)
        {
            x_val_ -= THREAT_SPEED;
        }
        else if (input_type_.right_ == 1)
        {
            x_val_ += THREAT_SPEED;
        }
        CheckToMap(gMap);
    }
    else if (call_back_time_ > 0)
    {
        call_back_time_--;
        if (call_back_time_ == 0)
        {
            x_val_ = 0;
            y_val_ = 0;
            if (x_pos_ > 256)
            {
                x_pos_ -= 256;
            }
            else
            {
                x_pos_ = 0;
            }
            y_pos_ = 0;
            call_back_time_ = 0;
        }
    }
}

void Threat::CheckToMap(Map& gMap)
{
    int x1 = 0;
    int x2 = 0; // checking limits of horizontal

    int y1 = 0;
    int y2 = 0;


    //Check horizontal
    int height_min = height_frame_ > TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

    y1 = (y_pos_) / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) // main character is moving to right
        {
            if (gMap.tile[y1][x2] > BLANK_TILE || gMap.tile[y2][x2] > BLANK_TILE)
            {
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
            }
        }
        else if (x_val_ < 0)
        {
            if (gMap.tile[y1][x1] > BLANK_TILE || gMap.tile[y1][x1] > BLANK_TILE)
            {
                x_pos_ = (x1 + 1) * TILE_SIZE;
                x_val_ = 0;
            }
        }
    }

    //check veritcal
    int width_min = width_frame_ > TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_) / TILE_SIZE;
    x2 = (x_pos_ + width_min) / TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0)
        {
            if (gMap.tile[y2][x1] > BLANK_TILE || gMap.tile[y2][x2] > BLANK_TILE)
            {
                y_pos_ = y2 * TILE_SIZE;
                y_pos_ -= (height_frame_ + 1);
                y_val_ = 0;
                on_ground_ = true;
            }

        }
        else if (y_val_ < 0)
        {
            if (gMap.tile[y1][x1] > BLANK_TILE || gMap.tile[y1][x2] > BLANK_TILE)
            {
                y_pos_ = (y1 + 1) * TILE_SIZE;
                y_val_ = 0;
            }
        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;
    if (x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ > gMap.max_x_)
    {
        x_pos_ = gMap.max_x_ - width_frame_ - 1;
    }

    if (y_pos_ > gMap.max_y_)
    {
        call_back_time_ = 60;
    }
}

void Threat::ImpMoveType(SDL_Renderer* screen)
{

    if (threat_type_ != MONSTER)
    {
        if (on_ground_ = true)
        {
            if (x_pos_ > animation_b_)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                //if (threat_type LoadImg("img//GolemAttack.png", screen);
                direction_ = LEFT;

            }
            else if (x_pos_ < animation_a_)
            {
                input_type_.left_ = 0;
                input_type_.right_ = 1;
                direction_ = RIGHT;
            }
            else
            {
                if (input_type_.left_ == 1)
                {
                    //loadImg("img//GolemAttack.png", screen);
                    direction_ = LEFT;
                }
            }
        }
    }
}

void Threat::InitBullet(Bullet* p_bullet, SDL_Renderer* screen)
{
    if (p_bullet != NULL)
    {
        bool ret;
        if (threat_type_ == MONSTER) ret = p_bullet->loadBullet("img//Wind.png", screen);
        else if (threat_type_ == GOLEM) ret = p_bullet->loadBullet("img//Fireball.png", screen);
        p_bullet->set_clips();

        if (ret)
        {
            p_bullet->set_is_move(true);
            if (direction_ == LEFT)
            {
                p_bullet->set_bullet_direction(Bullet::DIR_LEFT);
                p_bullet->SetRect(rect_.x, rect_.y + 10);
            }
            else if (direction_ == RIGHT)
            {
                p_bullet->set_bullet_direction(Bullet::DIR_RIGHT);
                p_bullet->SetRect(rect_.x + width_frame_ - 20, rect_.y + 10);
            }
            if (threat_type_ == MONSTER) p_bullet->set_x_val(20);
            else if (threat_type_ == GOLEM) p_bullet->set_x_val(10);
            bullet_list_.push_back(p_bullet);
        }
    }
}

void Threat::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
    for (int i = 0; i < bullet_list_.size(); i++)
    {
        Bullet* p_bullet = bullet_list_.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move())
            {
                int bullet_distance;
                if (direction_ == LEFT) bullet_distance = rect_.x + width_frame_ - p_bullet->GetRect().x;
                else if (direction_ == RIGHT) bullet_distance = p_bullet->GetRect().x - rect_.x;
                if (threat_type_ == MONSTER)
                {
                    if (bullet_distance < 450 && bullet_distance > 0)
                    {
                        p_bullet->HandleMove(x_limit, y_limit);
                        p_bullet->Show(screen);
                    }
                    else
                    {
                        p_bullet->set_is_move(false);
                    }
                }
                else if (threat_type_ == GOLEM)
                {
                    if (bullet_distance < 200 && bullet_distance > 0)
                    {
                        p_bullet->HandleMove(x_limit, y_limit);
                        p_bullet->Show(screen);
                    }
                    else
                    {
                        p_bullet->set_is_move(false);
                        if (direction_ == LEFT)
                        {
                            p_bullet->set_bullet_direction(Bullet::DIR_LEFT);
                            p_bullet->SetRect(rect_.x, rect_.y + 10);
                        }
                        else if (direction_ == RIGHT)
                        {
                            p_bullet->set_bullet_direction(Bullet::DIR_RIGHT);
                            p_bullet->SetRect(rect_.x + width_frame_ - 20, rect_.y + 10);
                        }
                    }
                }

            }
            else
            {
                p_bullet->set_is_move(true);
                p_bullet->SetRect(rect_.x + 5, rect_.y + height_frame_ * 0.1);
            }

        }
    }
}

void Threat::RemoveBullet(const int& idx)
{
    int size = bullet_list_.size();
    if (size > 0 && idx < size)
    {
        Bullet* p_bullet = bullet_list_.at(idx);
        bullet_list_.erase(bullet_list_.begin() + idx);

        if (p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}