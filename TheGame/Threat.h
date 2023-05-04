
#ifndef THREATS_H_ 
#define THREATS_H_ 

#include "CommonFunction.h"
#include "ImageBase.h"
#include "Bullet.h"

#define THREAT_FRAME_NUM 8
#define THREAT_SPEED 3

class Threat : public ImageBase
{
public:
    Threat();
    ~Threat();

    enum TypeOfThreat
    {
        MONSTER,
        GOLEM,
        KING,
    };

    enum Direction
    {
        LEFT,
        RIGHT,
    };

    //Handle image
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void set_clips();
    void Show(SDL_Renderer* des);
    
    //Set and handle position on map
    void set_x_pos(const float& xp) { x_pos_ = xp; }
    void set_y_pos(const float& yp) { y_pos_ = yp; }
    float get_x_pos() const { return x_pos_; }
    float get_y_pos() const { return y_pos_; }
    void SetMapXY(const int& mp_x, const int& mp_y) { map_x_ = mp_x; map_y_ = mp_y; }

    //Init threat
    void InitThreats();
    void set_threat_type(const TypeOfThreat& threatType) { threat_type_ = threatType; }
    void SetAnimationPos(const int& pos_a, const int& pos_b) { animation_a_ = pos_a; animation_b_ = pos_b; }
    void set_input_left(const int& ipLeft) { input_type_.left_ = ipLeft; }
    
    //Hnadle move
    void DoPlayer(Map& gMap);
    void CheckToMap(Map& gMap);
    void ImpMoveType(SDL_Renderer* screen);
    
    //Check collision
    SDL_Rect GetRectFrame();

    //Handle
    std::vector<Bullet*> get_bullet_list() const { return bullet_list_; }
    void set_bullet_list(const std::vector<Bullet*>& bl_list) { bullet_list_ = bl_list; }
    void InitBullet(Bullet* p_bullet, SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
    void RemoveBullet(const int& idx);

private:
    //Velocity
    float x_val_;
    float y_val_;
    
    //Position on map
    float x_pos_;
    float y_pos_;
    int map_x_;
    int map_y_;
    
    //Check on ground
    bool on_ground_;
    int call_back_time_;
    
    //Render frame
    SDL_Rect frame_clip_[THREAT_FRAME_NUM];
    int width_frame_;
    int height_frame_;
    int frame_;

    //Type and direction of threat
    TypeOfThreat threat_type_;
    Direction direction_;
    
    //Moving limits
    int animation_a_; 
    int animation_b_;
    
    //Input action
    Input input_type_;

    //Bullet
    std::vector<Bullet*> bullet_list_;
};



#endif // !THREATS_OBJECT_H_ 
