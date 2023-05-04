#include "Button.h"
//Button
Button::Button()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}

bool Button::loadButton(std::string path, SDL_Renderer* screen)
{
    bool ret = ImageBase::loadImg(path, screen);
    if (ret)
    {
        button_height_ = rect_.h;
        button_width_ = rect_.w / 2;
    }
    return ret;

}

void Button::set_clips()
{
    for (int i = 0; i < 2; i++)
    {
        button_clip[i].x = 0 + button_width_ * i;
        button_clip[i].y = 0;
        button_clip[i].w = button_width_;
        button_clip[i].h = button_height_;
    }
}

bool Button::isInside(SDL_Event* e)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    //Check if mouse is in button
    bool inside = true;

    //Mouse is left of the button
    if (x < mPosition.x)
    {
        inside = false;
    }
    //Mouse is right of the button
    else if (x > mPosition.x + button_width_)
    {
        inside = false;
    }
    //Mouse above the button
    else if (y < mPosition.y)
    {
        inside = false;
    }
    //Mouse below the button
    else if (y > mPosition.y + button_height_)
    {
        inside = false;
    }
    return inside;
}

void Button::handleEvent(SDL_Event* e)
{
    //If mouse event happened
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        bool inside = isInside(e);
        if (!inside)
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch (e->type)
            {
            case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            }

        }
    }
}

void Button::handleEventSwitch(SDL_Event* e, bool& isOn)
{
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        bool inside = isInside(e);
        if (inside) {
            if (isOn)
            {
                isOn = false;
            }
            else
            {
                isOn = true;
            }
        }
    }
    
    switch (isOn)
    {
    case true:
        mSwitchCurrentSprite = SWITCH_SPRITE_MOUSE_ON;
        break;
    case false:
        mSwitchCurrentSprite = SWITCH_SPRITE_MOUSE_OFF;
        break;
    }
}

void Button::ShowButton(SDL_Renderer* screen)
{
    //Show current button sprite
    SDL_Rect* current_clip = &button_clip[mCurrentSprite];
    SDL_Rect renderQuad = { mPosition.x, mPosition.y, button_width_, button_height_ };
    SDL_RenderCopy(screen, p_texture_, current_clip, &renderQuad);
}

void Button::ShowSwitch(SDL_Renderer* screen)
{
    //Show current button sprite
    SDL_Rect* current_clip = &button_clip[mSwitchCurrentSprite];
    SDL_Rect renderQuad = { mPosition.x, mPosition.y, button_width_, button_height_ };
    SDL_RenderCopy(screen, p_texture_, current_clip, &renderQuad);
}




