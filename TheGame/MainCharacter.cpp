
#include "MainCharacter.h"

MainCharacter::MainCharacter()
{
    frame_ = 0;
    frame_shoot_ = 0;
    frame_ultimate_ = 0;
    x_pos_ = 0;
    y_pos_ = 250;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = IDLE;
    input_type_.right_ = 0;
    input_type_.left_ = 0;
    input_type_.jump_ = 0;
    on_ground_ = false;
    map_x_ = 0;
    map_y_ = 0;
    call_back_time_ = 0;
    cool_down_time_ = 0;
    immortal_time_ = 0;
    range_ = 0;
    is_shooting_ = false;
    is_casting_ulti_ = false;
    hp_ = 0;
    is_dead_ = false;
}

MainCharacter::~MainCharacter()
{

}

void MainCharacter::reset_player()
{
    set_x_pos(0);
    set_y_pos(250);
    reset_input_type();
    is_dead_ = false;
    range_ = 0;
    call_back_time_ = 0;
    cool_down_time_ = 0;
    immortal_time_ = 0;
    frame_ = 0;
    frame_shoot_ = 0;
    frame_ultimate_ = 0;
}

bool MainCharacter::loadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = ImageBase::loadImg(path, screen);

    if (ret == true)
    {
        width_frame_ = FRAME_SIZE;
        height_frame_ = FRAME_SIZE;
    }
    return ret;
}

SDL_Rect MainCharacter::GetRectFrame()
{
    SDL_Rect rect;
    if (direction_ == RIGHT) rect.x = rect_.x;
    else if (direction_ == LEFT) rect.x = rect_.x + width_frame_ / 2;
    rect.y = rect_.y + height_frame_ / 2;
    rect.w = width_frame_ / 2;
    rect.h = height_frame_ / 2;

    return rect;
}

void MainCharacter::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < 16; i++)
        {
            frame_clip_[i].x = 0 + width_frame_ * i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void MainCharacter::Show(SDL_Renderer* des)
{
    SDL_RendererFlip flip_type_ = SDL_FLIP_NONE;
    if (direction_ == LEFT)
    {
        flip_type_ = SDL_FLIP_HORIZONTAL;
    }
    else
    {
        flip_type_ = SDL_FLIP_NONE;
    }

    UpdateImagePlayer(des);

    if (hp_ <= 0 && !is_dead_)
    {
        frame_dead_++;
        if (frame_dead_ >= 4)
        {
            frame_dead_ = 0;
            is_dead_ = true;
        }

        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;


        SDL_Rect* current_clip = &frame_clip_[frame_dead_];

        SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

        SDL_RenderCopyEx(des, p_texture_, current_clip, &renderQuad, 0, NULL, flip_type_);
    }
    else if (!is_dead_)
    {

        if (is_shooting_)
        {
            frame_shoot_++;

            if (frame_shoot_ >= SHOOT_FRAME)
            {
                frame_shoot_ = 0;
                is_shooting_ = false;
            }

            rect_.x = x_pos_ - map_x_;
            rect_.y = y_pos_ - map_y_;


            SDL_Rect* current_clip = &frame_clip_[frame_shoot_];

            SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

            SDL_RenderCopyEx(des, p_texture_, current_clip, &renderQuad, 0, NULL, flip_type_);
        }
        else if (is_casting_ulti_)
        {
            frame_ultimate_++;

            if (frame_ultimate_ >= CAST_FRAME)
            {
                frame_ultimate_ = 0;
                is_casting_ulti_ = false;
                immortal_time_ = 0;
            }

            rect_.x = x_pos_ - map_x_;
            rect_.y = y_pos_ - map_y_;


            SDL_Rect* current_clip = &frame_clip_[frame_ultimate_];

            SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

            SDL_RenderCopyEx(des, p_texture_, current_clip, &renderQuad, 0, NULL, flip_type_);
        }
        else
        {
            frame_++;

            if (frame_ >= 8) frame_ = 0;
            rect_.x = x_pos_ - map_x_;
            rect_.y = y_pos_ - map_y_;


            SDL_Rect* current_clip = &frame_clip_[frame_];

            SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

            SDL_RenderCopyEx(des, p_texture_, current_clip, &renderQuad, 0, NULL, flip_type_);
        }
    }
}

void MainCharacter::HandelInputAction(SDL_Event events, SDL_Renderer* screen)
{

    if (events.type == SDL_KEYDOWN)
    {
        if (hp_ > 0)
        {
            switch (events.key.keysym.sym)
            {
            case SDLK_d:
            {
                direction_ = RIGHT;
                input_type_.right_ = 1;
                input_type_.left_ = 0;
                UpdateImagePlayer(screen);

            }
            break;
            case SDLK_a:
            {
                direction_ = LEFT;
                input_type_.left_ = 1;
                input_type_.right_ = 0; // check xem input nao truoc
                UpdateImagePlayer(screen);

            }
            break;
            case SDLK_w:
            {
                input_type_.jump_ = 1;
                on_ground_ = false;
                UpdateImagePlayer(screen);
            }
            break;

            case SDLK_u:
            {
                if (cool_down_time_ == 0)
                {
                    is_shooting_ = true;
                    Bullet* p_bullet = new Bullet();
                    p_bullet->loadBullet("img//waterarrow.png", screen);
                    p_bullet->set_clips();
                    if (direction_ == LEFT)
                    {
                        p_bullet->set_bullet_direction(Bullet::DIR_LEFT);
                        p_bullet->SetRect(rect_.x, rect_.y + height_frame_ * 0.575);
                    }
                    else
                    {
                        p_bullet->set_bullet_direction(Bullet::DIR_RIGHT);
                        p_bullet->SetRect(rect_.x + width_frame_ - 64, rect_.y + height_frame_ * 0.575);
                    }

                    p_bullet->set_x_val(20);
                    p_bullet->set_is_move(true);

                    p_bullet_list_.push_back(p_bullet);

                    cool_down_time_ = 10;
                    if (range_ < RANGE_MAX) range_++;

                }
            }
            break;

            case SDLK_i:
            {
                if (range_ == RANGE_MAX && on_ground_)
                {
                    is_casting_ulti_ = true;
                    immortal_time_ = 17;
                    Skill* p_ultimate = new Skill();
                    p_ultimate->loadUltimate("img//fixed-aquametria.png", screen);
                    p_ultimate->set_clips();
                    p_ultimate->set_damaging_time(11);
                    if (direction_ == LEFT)
                    {
                        p_ultimate->set_Skill_direction(Skill::SKILL_LEFT);
                        p_ultimate->SetRect(rect_.x - 450, rect_.y + height_frame_ - 302);
                    }
                    else
                    {
                        p_ultimate->set_Skill_direction(Skill::SKILL_RIGHT);
                        p_ultimate->SetRect(rect_.x + width_frame_ - 20, rect_.y + height_frame_ - 302);
                    }

                    p_ultimate->set_is_activating(true);
                    p_ultimate_list_.push_back(p_ultimate);

                    range_ = 0;
                }
            }
            break;

            default:
                break;
            }
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_d:
        {
            direction_ = RIGHT;
            input_type_.right_ = 0;

        }
        break;
        case SDLK_a:
        {
            direction_ = LEFT;
            input_type_.left_ = 0;

        }
        break;
        case SDLK_w:
        {
            input_type_.jump_ = 0;
        }
        break;
        default:
            break;
        }
    }
}

void MainCharacter::HandleBullet(SDL_Renderer* des)
{
    for (int i = 0; i < p_bullet_list_.size(); i++)
    {
        Bullet* p_bullet = p_bullet_list_.at(i);
        if (p_bullet->get_is_move() == true)
        {
            p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            p_bullet->Show(des);
        }
        else
        {
            p_bullet_list_.erase(p_bullet_list_.begin() + i);
            if (p_bullet != NULL)
            {
                delete p_bullet;
                p_bullet = NULL;
            }
        }
    }
}

void MainCharacter::RemoveBullet(const int& idx)
{
    int size = p_bullet_list_.size();
    if (size > 0 && idx < size)
    {
        Bullet* p_bullet = p_bullet_list_.at(idx);
        p_bullet_list_.erase(p_bullet_list_.begin() + idx);

        if (p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

void MainCharacter::HandleUltimate(SDL_Renderer* des)
{
    for (int i = 0; i < p_ultimate_list_.size(); i++)
    {
        Skill* p_ultimate = p_ultimate_list_.at(i);
        if (p_ultimate->get_is_activating() == true)
        {
            p_ultimate->Show(des);
        }
        else
        {
            p_ultimate_list_.erase(p_ultimate_list_.begin() + i);
            if (p_ultimate != NULL)
            {
                delete p_ultimate;
                p_ultimate = NULL;
            }
        }
    }
}

void MainCharacter::DoPlayer(Map& map_data, bool& meet_boss)
{
    if (call_back_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += 0.8;

        if (y_val_ >= MAX_FALL_SPEED)
        {
            y_val_ = MAX_FALL_SPEED;
        }

        if (input_type_.left_ == 1)
        {
            if (!(is_shooting_ && on_ground_) && !is_casting_ulti_)
                x_val_ -= PLAYER_SPEED;
        }
        else if (input_type_.right_ == 1)
        {
            if (!(is_shooting_ && on_ground_) && !is_casting_ulti_)
                x_val_ += PLAYER_SPEED;
        }

        if (input_type_.jump_ == 1)
        {
            if (!is_casting_ulti_)
                if (on_ground_ == true)
                {
                    y_val_ = -PLAYER_JUMP_VALUE;
                    input_type_.jump_ = 0;
                }
        }

        CheckToMap(map_data, meet_boss);
        if (!meet_boss) CenterEntityOnMap(map_data);
    }

    if (call_back_time_ > 0)
    {
        call_back_time_--;

        if (call_back_time_ == 0)
        {
            on_ground_ = false;
            if (x_pos_ > 256)
            {
                x_pos_ -= 256; // 8 tiles
            }
            else
            {
                x_pos_ = 0;
            }
            y_pos_ = SCREEN_HEIGHT * 0.2;
            x_val_ = 0;
            y_val_ = 0;
        }
        if (call_back_time_ == 1) decrease_hp(2);
    }
    decrease_cool_down_time();
}

void MainCharacter::CenterEntityOnMap(Map& map_data)
{
    map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);
    if (map_data.start_x_ < 0)
    {
        map_data.start_x_ = 0;
    }
    else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
    {
        map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
    }

    map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2);
    if (map_data.start_y_ < 0)
    {
        map_data.start_y_ = 0;
    }
    else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
    {
        map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
    }
}

void MainCharacter::CheckToMap(Map& map_data, bool& meet_boss)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //Check horizontal (ý nghĩa: check frame nhân vật đang nằm ở ô thứ bao nhiêu của bản đồ tile)
    int height_min = height_frame_ > TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

    y1 = y_pos_ / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) // main character is moving to right
        {
            if (map_data.tile[y1][x2] > BLANK_TILE || map_data.tile[y2][x2] > BLANK_TILE)
            {
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
            }
        }
        else if (x_val_ < 0)
        {
            if (map_data.tile[y1][x1] > BLANK_TILE || map_data.tile[y2][x1] > BLANK_TILE)
            {
                x_pos_ = (x1 + 1) * TILE_SIZE;
                x_val_ = 0;
            }
        }
    }

    //check veritcal
    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_) / TILE_SIZE;
    x2 = (x_pos_ + width_min) / TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0)
        {
            if (map_data.tile[y2][x1] > BLANK_TILE || map_data.tile[y2][x2] > BLANK_TILE)
            {
                y_pos_ = y2 * TILE_SIZE;
                y_pos_ -= (height_frame_ + 1);
                y_val_ = 0;
                on_ground_ = true;
            }
        }
        else if (y_val_ < 0)
        {
            on_ground_ = false;
            if (map_data.tile[y1][x1] > BLANK_TILE || map_data.tile[y1][x2] > BLANK_TILE)
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
    else if (x_pos_ + width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_ - width_frame_ - 1;
    }
    else if (meet_boss)
    {
        if (x_pos_ <= TILE_SIZE * 800 - SCREEN_WIDTH) x_pos_ = TILE_SIZE * 800 - SCREEN_WIDTH;
    }

    if (y_pos_ > map_data.max_y_)
    {
        call_back_time_ = 60;
    }
}

void MainCharacter::UpdateImagePlayer(SDL_Renderer* des)
{
    if (hp_ <= 0) loadImg("img//Dead.png", des);
    else
    {
        if (on_ground_ == true)
        {
            if (is_shooting_) loadImg("img//Attack_1.png", des);
            else if (is_casting_ulti_) loadImg("img//Magic_sphere.png", des);
            else
            {
                if (x_val_ == 0) loadImg("img//Idle.png", des);
                else loadImg("img//Run.png", des);
            }
        }
        else if (on_ground_ == false)
        {
            if (y_val_ < 0) loadImg("img//Flying.png", des);
            else loadImg("img//Falling.png", des);
        }
    }
}

void MainCharacter::decrease_hp(const int& damage)
{
    hp_ -= damage;
    if (hp_ <= 0)
    {
        hp_ = 0;
    }
}