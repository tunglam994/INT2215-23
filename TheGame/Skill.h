#ifndef	SKILL_H_
#define SKILL_H_

#include "CommonFunction.h"
#include "ImageBase.h"

#define ULTIMATE_FRAME 18
#define	BOSS_SKILL_FRAME 40

class Skill : public ImageBase
{
public:
	Skill();
	~Skill();

	enum SkillDirection
	{
		SKILL_LEFT,
		SKILL_RIGHT,
	};

	SDL_Rect GetRectFrame();
	//Init skill
	bool loadUltimate(std::string path, SDL_Renderer* screen);
	bool loadBossskill(std::string path, SDL_Renderer* screen);
	void set_clips();
	void boss_skill_set_clips();
	void set_Skill_direction(const unsigned int& uDir) { Skill_direction_ = uDir; }
	void set_is_activating(const bool& isactivating) { is_activating_ = isactivating; }
	void set_damaging_time(const int& damagingTime) { damaging_time_ = damagingTime; }
	
	//Get status of skill
	int get_Skill_direction() const { return Skill_direction_; }
	bool get_is_activating() const { return is_activating_; }
	bool get_is_damaging() { return is_damaging_; }

	//sRender skill
	void Show(SDL_Renderer* des);
	void boss_skill_Show(SDL_Renderer* des);

	

private:
	//Skill size
	int width_frame_;
	int height_frame_;

	//Skill frame
	SDL_Rect p_frame_clip_[ULTIMATE_FRAME];
	SDL_Rect b_frame_clip_[BOSS_SKILL_FRAME];
	int frame_;

	//Skill direction
	unsigned int Skill_direction_;

	//Handle skill
	bool is_activating_;
	
	//Skill damaging moment
	bool is_damaging_;
	int damaging_time_;
};


#endif



