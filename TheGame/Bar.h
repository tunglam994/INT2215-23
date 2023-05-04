
#ifndef BAR_H_
#define BAR_H_

#include "CommonFunction.h"
#include "ImageBase.h"


class Bar
{
public:
    Bar();
    ~Bar();

    //Init bar
    bool loadBar(std::string path1, std::string path2, SDL_Renderer* screen);
    void setBarPosition(const int x1, const int y1, const int x2, const int y2);

    //Update status of bar
    void updateBar(const int current_value, const int max_value);

    //Render bar
    void showBar(SDL_Renderer* screen);
    void FreeGUIBar();


private:
    // Back bar and real bar
    ImageBase current_bar_;
    ImageBase back_bar_;

    // Bar size
    double current_width_;
    
    // Bar max size
    int max_width_;
    int max_height_;

    // Bar position
    int bar_x_;
    int bar_y_;
};

#endif 
