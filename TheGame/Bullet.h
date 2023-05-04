
#ifndef BULLET_H_
#define BULLET_H_

#include "ImageBase.h"
#include "CommonFunction.h"

#define BULLET_FRAME 8

class Bullet : public ImageBase
{

public:
	Bullet();
	~Bullet();

	enum BulletDirection
	{
		DIR_RIGHT,
		DIR_LEFT,
	};

	//Init bullet
	bool loadBullet(std::string path, SDL_Renderer* screen);
	void set_clips();
	void set_is_move(const bool& isMove) { is_move_ = isMove; }
	void set_bullet_direction(const BulletDirection& bulletDir) { bullet_direction_ = bulletDir; }
	void set_x_val(const int& xVal) { x_val_ = xVal; }
	void set_y_val(const int& yVal) { y_val_ = yVal; }
	
	// Get status of bullet
	int get_x_val() const { return x_val_; }
	int get_y_val() const { return y_val_; }
	bool get_is_move() const { return is_move_; }
	int get_bullet_direction() const { return bullet_direction_; }
	SDL_Rect GetRectFrame();
	
	//Handle bullet
	void HandleMove(const int& x_border, const int& y_border);

	//Render bullet
	void Show(SDL_Renderer* des);

private:
	// Bullet velocity
	int x_val_;
	int y_val_;

	// Frame size
	int width_frame_;
	int height_frame_;

	//Render frame
	SDL_Rect frame_clip_[8];
	int frame_;

	//Bullet status
	bool is_move_;
	BulletDirection bullet_direction_;
};

#endif // ! BULLET_OBJECT_H_
