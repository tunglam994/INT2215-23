#ifndef BOSS_H_
#define BOSS_H_

#include "ImageBase.h"
#include "CommonFunction.h"
#include "Bullet.h"
#include "Skill.h"

#define BOSS_CAST_FRAME_ 14
#define BOSS_SHOOT_FRAME_ 10
#define BOSS_IDLE_FRAME_ 8
#define BOSS_HURT_FRAME_ 3
#define BOSS_DEAD_FRAME_ 10

#define MAX_BOSS_HP 70

#define BOSS_FRAME_WIDTH 560
#define BOSS_FRAME_HEIGHT 372

class Boss : public ImageBase
{
public:
    Boss();
    ~Boss();

    enum Action
    {
        IDLE,
        HURT,
        DEATH,
        SHOOT,
        CAST,
    };

    //Handle image
    void Show(SDL_Renderer* des);
    bool loadImg(std::string path, SDL_Renderer* screen);
    void UpdateBoss(SDL_Renderer* des);
    void set_clips();

    //Set and get position on map
    void set_xpos(const int& xps) { x_pos_ = xps; }
    void set_ypos(const int& yps) { y_pos_ = yps; }
    int get_x_pos() const { return x_pos_; }
    int get_y_pos() const { return y_pos_; }
    void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }

    //Check collision
    SDL_Rect GetRectFrame();

    //Handle move
    void CheckToMap(Map& map_data);
    void HandleMove(Map& g_map, int player_x_pos, bool meet_boss);
    
    //Handle bullet
    std::vector<Bullet*> get_bullet_list() const { return bullet_list_; }
    void InitBullet(SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit, int player_x_pos, bool meet_boss);
    void RemoveBullet(const int& idx);
    
    //Handle skill
    std::vector<Skill*> get_skill_list() const { return skill_list_; }
    void InitSkill(SDL_Renderer* screen, int player_x_pos);
    void MakeSkill(SDL_Renderer* screen, int player_x_pos, bool meet_boss);

    //Handle HP
    void reset_hp_() { hp_ = MAX_BOSS_HP; }
    int get_hp() { return hp_; }
    void decrease_hp(const int& value);

    //Handle status
    void set_is_hurt(bool isHurt) { is_hurt_ = isHurt; }
    void set_is_dead(bool isDead) { is_dead_ = isDead; }
    bool get_is_dead() { return is_dead_; }

    //Boss reset
    void reset_boss(bool& meet_boss);

private:
    //Velocity
    int x_val_;
    int y_val_;
    
    //Position on map
    int x_pos_;
    int y_pos_;
    int map_x_;
    int map_y_;
    bool on_ground_;

    //Render frame
    SDL_Rect frame_clip_[14];
    int width_frame_;
    int height_frame_;
    int idle_frame_;
    int hurt_frame_;
    int shoot_frame_;
    int cast_frame_;
    int die_frame_;

    //Bullet and skill
    std::vector<Bullet*> bullet_list_;
    std::vector<Skill*> skill_list_;

    //Status
    Action status_;
    bool is_change_status_;
    bool is_hurt_;
    bool is_dead_;
    bool is_shoot_;
    bool is_casting_spell_;
    bool appear_;

    //Cool down time
    int cool_down_time_;

    //HP
    int hp_;

    //
    bool appear;
};

#endif