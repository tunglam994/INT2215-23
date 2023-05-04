
#include "Boss.h"

Boss::Boss()
{
    idle_frame_ = 0;
    hurt_frame_ = 0;
    die_frame_ = 0;
    shoot_frame_ = 0;
    cast_frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    map_x_ = 0;
    map_y_ = 0;
    on_ground_ = false;
    status_ = IDLE;
    is_hurt_ = false;
    is_dead_ = false;
    is_shoot_ = false;
    is_casting_spell_ = false;
    appear = true;
}

Boss::~Boss()
{

}

bool Boss::loadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = ImageBase::loadImg(path, screen);
    if (ret == true)
    {
        width_frame_ = BOSS_FRAME_WIDTH;
        height_frame_ = BOSS_FRAME_HEIGHT;
    }

    return ret;
}

void Boss::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < 14; i++)
        {
            frame_clip_[i].x = width_frame_ * i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void Boss::Show(SDL_Renderer* des)
{
    UpdateBoss(des);
    rect_.x = x_pos_ - map_x_; //x_pos_ vtri tren map, rect.x vtri trên screen
    rect_.y = y_pos_ - map_y_;
    if (status_ == DEATH && !is_dead_)
    {
        die_frame_++;
        if (die_frame_ >= BOSS_DEAD_FRAME_)
        {
            die_frame_ = 0;
            is_dead_ = true;
        }
        SDL_Rect* current_clip = &frame_clip_[die_frame_];
        SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
        if (current_clip != NULL)
        {
            renderQuad.w = current_clip->w;
            renderQuad.h = current_clip->h;
        }

        SDL_RenderCopy(des, p_texture_, current_clip, &renderQuad);
    }
    else if (!is_dead_)
    {
        if (is_shoot_)
        {
            idle_frame_ = 0;
            shoot_frame_++;
            if (shoot_frame_ >= BOSS_SHOOT_FRAME_)
            {
                shoot_frame_ = 0;
                is_shoot_ = false;
            }
            SDL_Rect* current_clip = &frame_clip_[shoot_frame_];
            SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
            if (current_clip != NULL)
            {
                renderQuad.w = current_clip->w;
                renderQuad.h = current_clip->h;
            }

            SDL_RenderCopy(des, p_texture_, current_clip, &renderQuad);
        }
        else if (is_casting_spell_)
        {
            idle_frame_ = 0;
            shoot_frame_ = 0;
            cast_frame_++;
            if (cast_frame_ >= BOSS_CAST_FRAME_)
            {
                cast_frame_ = 0;
                is_casting_spell_ = false;
            }
            SDL_Rect* current_clip = &frame_clip_[cast_frame_];
            SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
            if (current_clip != NULL)
            {
                renderQuad.w = current_clip->w;
                renderQuad.h = current_clip->h;
            }

            SDL_RenderCopy(des, p_texture_, current_clip, &renderQuad);
        }
        else if (is_hurt_)
        {
            idle_frame_ = 0;
            shoot_frame_ = 0;
            cast_frame_ = 0;
            hurt_frame_++;
            if (hurt_frame_ >= BOSS_HURT_FRAME_)
            {
                hurt_frame_ = 0;
                is_hurt_ = false;
            }
            SDL_Rect* current_clip = &frame_clip_[hurt_frame_];
            SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
            if (current_clip != NULL)
            {
                renderQuad.w = current_clip->w;
                renderQuad.h = current_clip->h;
            }

            SDL_RenderCopy(des, p_texture_, current_clip, &renderQuad);
        }
        else
        {

            idle_frame_++;
            if (idle_frame_ >= BOSS_IDLE_FRAME_)
            {
                idle_frame_ = 0;
            }
            SDL_Rect* current_clip = &frame_clip_[idle_frame_];
            SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
            if (current_clip != NULL)
            {
                renderQuad.w = current_clip->w;
                renderQuad.h = current_clip->h;
            }

            SDL_RenderCopy(des, p_texture_, current_clip, &renderQuad);
        }
    }
}

void Boss::HandleMove(Map& g_map, int player_x_pos, bool meet_boss)
{
    x_val_ = 0;
    y_val_ += GRAVITY_SPEED;

    if (y_val_ >= MAX_FALL_SPEED)
        y_val_ = MAX_FALL_SPEED;

    int relative_pos = x_pos_ - player_x_pos;

    int old_status = status_;


    if (hp_ <= 0)
    {
        status_ = DEATH;
        if (old_status != status_) is_change_status_ = true;
        else is_change_status_ = false;
    }
    else if (meet_boss)
    {
        if (cool_down_time_ == 50)
        {
            if (hp_ > MAX_BOSS_HP / 2)
            {
                status_ = CAST;
                is_shoot_ = false;
                is_casting_spell_ = true;
                is_dead_ = false;
                is_hurt_ = false;
                cool_down_time_ = 0;
                relative_pos = -1;
            }
            else
            {
                status_ = SHOOT;
                is_shoot_ = true;
                is_casting_spell_ = false;
                is_dead_ = false;
                is_hurt_ = false;
                cool_down_time_ = 0;
                relative_pos = -1;
            }

        }

        else if (!is_shoot_ && !is_casting_spell_)
        {
            if (is_hurt_)
            {
                status_ = HURT;
            }
            else
            {
                status_ = IDLE;
            }
        }
        cool_down_time_++;
    }

    

    CheckToMap(g_map);
}



void Boss::CheckToMap(Map& map_data) //hàm quan trọng check colision 
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

    /* if (y_pos_ > map_data.max_y_)
     {
         come_back_time_ = 60;
     }*/
}

void Boss::InitBullet(SDL_Renderer* screen)
{
    Bullet* p_bullet = new Bullet();
    bool ret = p_bullet->loadBullet("img//DarkBullet.png", screen);
    p_bullet->set_clips();
    if (ret)
    {
        p_bullet->set_bullet_direction(Bullet::DIR_LEFT);
        p_bullet->set_is_move(true);
        p_bullet->SetRect(rect_.x + 100, rect_.y + 260);
        p_bullet->set_x_val(30);
        bullet_list_.push_back(p_bullet);
    }
}

void Boss::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit, int play_x_pos, bool meet_boss)
{

    if (is_shoot_ && shoot_frame_ == 4 && meet_boss) InitBullet(des);
    for (int i = 0; i < bullet_list_.size(); i++)
    {
        Bullet* p_bullet = bullet_list_.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move() == true)
            {
                p_bullet->HandleMove(x_limit, y_limit);
                p_bullet->Show(des);
            }
            else
            {
                p_bullet->Free();
                bullet_list_.erase(bullet_list_.begin() + i);
            }
        }
    }
}

void Boss::RemoveBullet(const int& idx)
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

void Boss::InitSkill(SDL_Renderer* screen, int player_x_pos)
{
    Skill* p_skill = new Skill();
    p_skill->loadBossskill("img//BossSpell.png", screen);
    p_skill->boss_skill_set_clips();
    p_skill->set_damaging_time(36);
    p_skill->set_Skill_direction(Skill::SKILL_LEFT);
    p_skill->SetRect(player_x_pos, 0);

    p_skill->set_is_activating(true);

    skill_list_.push_back(p_skill);
}

void Boss::MakeSkill(SDL_Renderer* screen, int player_x_pos, bool meet_boss)
{
    if (is_casting_spell_ && cast_frame_ == 0 && meet_boss)
    {
        InitSkill(screen, player_x_pos);
    }
    for (int i = 0; i < skill_list_.size(); i++)
    {
        Skill* p_skill = skill_list_.at(i);
        if (p_skill->get_is_activating() == true)
        {
            p_skill->boss_skill_Show(screen);
        }
        else
        {
            skill_list_.erase(skill_list_.begin() + i);
            if (p_skill != NULL)
            {
                delete p_skill;
                p_skill = NULL;
            }
        }
    }
}


SDL_Rect Boss::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x + 370;
    rect.y = rect_.y + 144;
    rect.w = 174;
    rect.h = 256;

    return rect;
}

void Boss::UpdateBoss(SDL_Renderer* des)
{
    if (status_ == IDLE) loadImg("img//BossIdle.png", des);
    else if (status_ == SHOOT) loadImg("img//BossAttack.png", des);
    else if (status_ == CAST) loadImg("img//BossCast.png", des);
    else if (status_ == HURT)
    {
        loadImg("img//BossHurt.png", des);
    }

    else if (status_ == DEATH)
    {
        loadImg("img//BossDead.png", des);
    }
}

void Boss::decrease_hp(const int& value)
{
    hp_ -= value;
    if (hp_ < 0) hp_ = 0;
}

void Boss::reset_boss(bool& meet_boss)
{
    meet_boss = false;
    idle_frame_ = 0;
    hurt_frame_ = 0;
    die_frame_ = 0;
    shoot_frame_ = 0;
    cast_frame_ = 0;
    x_pos_ = 800 * TILE_SIZE - BOSS_FRAME_WIDTH;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    map_x_ = 0;
    map_y_ = 0;
    on_ground_ = false;
    status_ = IDLE;
    is_hurt_ = false;
    is_dead_ = false;
    is_shoot_ = false;
    is_casting_spell_ = false;
    appear = true;
    hp_ = MAX_BOSS_HP;
    
}