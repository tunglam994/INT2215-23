#ifndef BUTTON_H_
#define BUTTON_H_

#include "CommonFunction.h"
#include "ImageBase.h"

class Button : public ImageBase
{
public:
    //Initializes internal variables
    Button();

    //Load button
    bool loadButton(std::string path, SDL_Renderer* screen);
    void set_clips();

    //Sets top left position
    void setPosition(int x, int y);

    //Handles mouse event
    bool isInside(SDL_Event* e);
    void handleEvent(SDL_Event* e);
    void handleEventSwitch(SDL_Event* e, bool& isOn);
    
    //Shows button sprite
    void ShowButton(SDL_Renderer* screen);
    void ShowSwitch(SDL_Renderer* screen);

private:
    //Top left position
    SDL_Point mPosition;

    //button size
    int button_width_;
    int button_height_;

    //Currently used global sprite
    LButtonSprite mCurrentSprite;

    //Currently used global sprite
    LSwitchSprite mSwitchCurrentSprite;

    //Render Rect
    SDL_Rect button_clip[2];

};

#endif