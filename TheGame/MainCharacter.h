
#ifndef MAIN_CHARACTER_H
#define MAIN_CHARACTER_H_

#include "CommonFunction.h"
#include "ImageBase.h"
#include "Bullet.h"
#include "Skill.h"


#define PLAYER_SPEED 15
#define PLAYER_JUMP_VALUE 15 
#define RANGE_MAX 15
#define MAX_PLAYER_HP 30

#define FRAME_SIZE 128

#define SHOOT_FRAME 6
#define CAST_FRAME 16

class MainCharacter : public ImageBase
{
public:
    MainCharacter();
    ~MainCharacter();

    enum Status
    {
        IDLE,
        RUN,
        SHOOT,
    };

    enum Direction
    {
        RIGHT,
        LEFT,
    };

    //Reset 
    void reset_player();

    //Handle and render image
    virtual bool loadImg(std::string path, SDL_Renderer* screen); 
    void Show(SDL_Renderer* des);
    void set_clips();
    void UpdateImagePlayer(SDL_Renderer* des);

    //Handle action
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
    void DoPlayer(Map& map_data, bool& meet_boss);
    void CheckToMap(Map& map_data, bool& meet_boss);
    void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }
    void CenterEntityOnMap(Map& map_data);
    void reset_input_type() { input_type_.left_ = 0; input_type_.right_ = 0; }
    
    //Handle collision
    SDL_Rect GetRectFrame();

    void set_immortal_time(const int& value) { immortal_time_ = value; }
    void decrease_immortal_time() { if (immortal_time_ > 0) immortal_time_--; }
    bool is_immortal() { return immortal_time_ > 0; }
    void set_y_val(const int& value) { y_val_ = -value; }
    void set_x_val(const int& value) { x_val_ = value; }

    //Handle bullet
    void set_bullet_list(std::vector<Bullet*> bullet_list) { p_bullet_list_ = bullet_list; }
    std::vector<Bullet*> get_bullet_list() const { return p_bullet_list_; }
    void RemoveBullet(const int& idx);
    void HandleBullet(SDL_Renderer* des);
    void decrease_cool_down_time() { if (cool_down_time_ > 0) cool_down_time_--; }

    //Handle Skill
    std::vector<Skill*> get_ultimate_list() const { return p_ultimate_list_; }
    void HandleUltimate(SDL_Renderer* des);
    int get_range() { return range_; }

    //Get and set player's position on map
    int get_player_x_pos() { return x_pos_; }
    void set_x_pos(const int& xPos) { x_pos_ = xPos; }
    void set_y_pos(const int& yPos) { y_pos_ = yPos; }

    //Handle player's hp
    void set_hp(const int& hp_value) { hp_ = hp_value; }
    int get_hp() { return hp_; }
    void decrease_hp(const int& damage);
    bool get_is_dead() { return is_dead_; }

private:
    // Player's velocity
    float x_val_;
    float y_val_;

    // Player's position on map
    float x_pos_;
    float y_pos_;

    // Size of frame
    int width_frame_;
    int height_frame_;

    // Bullet and skill
    std::vector<Bullet*> p_bullet_list_;
    std::vector<Skill*> p_ultimate_list_;
    int range_;
    
    // Handle input
    Input input_type_;
    bool is_shooting_;
    bool is_casting_ulti_;
    int cool_down_time_;

    // Render frame
    SDL_Rect frame_clip_[16];
    int frame_;
    int frame_shoot_;
    int frame_ultimate_;
    int frame_dead_;
    int status_;
    Direction direction_;

    // Check on the ground
    bool on_ground_;

    int map_x_;
    int map_y_;
    
    // Call back time and immortal time
    int call_back_time_;
    int immortal_time_;

    // Player's hp
    int hp_;
    bool is_dead_;
};

#endif // MAIN_CHARACTER_H
