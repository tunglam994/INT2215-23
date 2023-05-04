#include "CommonFunction.h"
#include "ImageBase.h"
#include "game_map.h"
#include "MainCharacter.h"
#include "Timer.h"
#include "Threat.h"
#include "Text.h"
#include "Background.h"
#include "Bar.h"
#include "Button.h"
#include "Skill.h"
#include "Boss.h"


//ImageBase g_background;
Background g_background;
TTF_Font* font_time = NULL;
Mix_Music* gMusic = NULL;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("theGame",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }

        // Init text ttf
        if (TTF_Init() == -1)
            success = false;
        font_time = TTF_OpenFont("font//dlxfont_.ttf", 15);
        if (font_time == NULL)
            success = false;

        //Init Audio
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            success = false;
        }
    }

    return success;
}

bool LoadBackground()
{
    bool ret = g_background.loadBackground("img//background.png", g_screen);
    //bool ret = g_background.loadImg("img//background.png", g_screen);
    if (!ret) return false;
    return true;

}

bool LoadMusic()
{
    bool success = true;

    gMusic = Mix_LoadMUS("Jo_Wandrini_-_A_Place_Of_Wonder_And_Beauty.mp3");
    if (gMusic == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    return success;
}

void close()
{
    //g_background.freeBackground();
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

std::vector<Threat*> MakeThreatsList()
{
    std::vector<Threat*> list_threats;

    Threat* threat_golem = new Threat[20];
    for (int i = 0; i < 20; i++)
    {
        Threat* p_threat = (threat_golem + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img//GolemAttack.png", g_screen);
            p_threat->set_clips();
            p_threat->set_threat_type(Threat::GOLEM);
            p_threat->set_x_pos(1500 + i * 1000);
            p_threat->set_y_pos(200);

            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_x_pos() + 60;
            // khoang di chuyen
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);

            Bullet* p_bullet = new Bullet();
            p_threat->InitBullet(p_bullet, g_screen);


            list_threats.push_back(p_threat);
        }
    }

    Threat* threat_king = new Threat[20];
    for (int i = 0; i < 20; i++)
    {
        Threat* p_threat = (threat_king + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img//KingFixed.png", g_screen);
            p_threat->set_clips();
            p_threat->set_threat_type(Threat::KING);
            p_threat->set_x_pos(1700 + i * 1000);
            p_threat->set_y_pos(200);

            int pos1 = p_threat->get_x_pos() - 80;
            int pos2 = p_threat->get_x_pos() + 80;
            // khoang di chuyen
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);

            list_threats.push_back(p_threat);
        }
    }

    Threat* threat_monster = new Threat[20];
    for (int i = 0; i < 20; i++)
    {
        Threat* p_threat = (threat_monster + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img//MonsterAttack.png", g_screen);
            p_threat->set_clips();
            p_threat->set_threat_type(Threat::MONSTER);
            p_threat->set_x_pos(1000 + i * 1000);
            p_threat->set_y_pos(200);

            Bullet* p_bullet = new Bullet();
            p_threat->InitBullet(p_bullet, g_screen);


            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}

void HandlePlayButton(SDL_Event* e,
    Button& PlayButton,
    bool& QuitMenu,
    bool& Play)
{
    if (e->type == SDL_QUIT)
    {
        QuitMenu = true;
    }

    PlayButton.handleEvent(e);

    if (PlayButton.isInside(e))
    {
        switch (e->type)
        {
        case SDL_MOUSEMOTION:
            break;
        case SDL_MOUSEBUTTONDOWN:
            Play = true;
            QuitMenu = true;
            break;
        }
    }
}

void HandleInformationButton(SDL_Event* e,
    ImageBase& InstructionMenu,
    Button& InformationButton,
    Button& BackButton,
    SDL_Renderer* gRenderer,
    bool& Quit_game)
{
    InformationButton.handleEvent(e);
    if (InformationButton.isInside(e))
    {
        switch (e->type)
        {
        case SDL_MOUSEBUTTONDOWN:
            bool ReadDone = false;
            while (!ReadDone)
            {
                do
                {

                    if (e->type == SDL_QUIT)
                    {
                        ReadDone = true;
                        Quit_game = true;
                    }

                    else
                    {
                        BackButton.handleEvent(e);
                        if (BackButton.isInside(e))
                        {
                            switch (e->type)
                            {
                            case SDL_MOUSEBUTTONDOWN:
                                ReadDone = true;
                                break;
                            }
                        }
                    }

                    InstructionMenu.Render(gRenderer);
                    BackButton.ShowButton(gRenderer);


                    SDL_RenderPresent(gRenderer);
                } while (SDL_PollEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
            }
            break;
        }
    }
}

void HandleExitButton(SDL_Event* e,
    Button& ExitButton,
    bool& Quit)
{
    ExitButton.handleEvent(e);
    if (ExitButton.isInside(e))
    {
        switch (e->type)
        {
        case SDL_MOUSEBUTTONDOWN:
            Quit = true;
            break;
        }
    }

}

void HandleMusicButton(SDL_Event* e, Button& MusicButton, bool& isOn)
{
    MusicButton.handleEventSwitch(e, isOn);
    if (MusicButton.isInside(e))
    {
        switch (e->type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if (Mix_PausedMusic() == 1)
            {
                //Resume the music
                Mix_ResumeMusic();
            }
            //If the music is playing
            else
            {
                //Pause the music
                Mix_PauseMusic();
            }
        }
    }
}

void HandleYesButton(SDL_Event* e,
    Button& YesButton,
    GameState& gameState)
{
    YesButton.handleEvent(e);
    if (YesButton.isInside(e))
    {
        switch (e->type)
        {
        case SDL_MOUSEBUTTONDOWN:
            gameState = GAME_IN;
            break;
        }
    }
}

void HandleNoButton(SDL_Event* e,
    Button& NoButton,
    GameState& gameState, bool& PlayAgain)
{
    NoButton.handleEvent(e);
    if (NoButton.isInside(e))
    {
        switch (e->type)
        {
        case SDL_MOUSEBUTTONDOWN:
        {
            gameState = GAME_OUT;
            PlayAgain = false;
        }
        break;
        }
    }

}

int main(int argc, char* argv[])
{
    Timer fps_timer;

    if (InitData() == false)
        return -1;
    if (LoadBackground() == false)
        return -1;
    if (LoadMusic() == false)
        return -1;

    GameMap game_map;
    game_map.LoadMap("map/map.dat");
    game_map.LoadTiles(g_screen);

    MainCharacter p_player;
    p_player.loadImg("img//Idle.png", g_screen);
    p_player.set_clips();
    

    //text ttf
    Text time_game;
    time_game.SetColor(Text::WHITE_TEXT);

    Text mark_game;
    mark_game.SetColor(Text::BLACK_TEXT);
    int mark_value = 0;

    std::vector<Threat*> threats_list;

    //HP bar
    Bar HP_bar;
    HP_bar.loadBar("img//back_bar.png", "img//hp_bar.png", g_screen);
    HP_bar.setBarPosition(60, 24, 84, 32);

    Bar Boss_HP_bar;
    Boss_HP_bar.loadBar("img//back_bar.png", "img//hp_bar.png", g_screen);
    Boss_HP_bar.setBarPosition(860, 24, 884, 32);

    //Range bar
    Bar Range_bar_;
    Range_bar_.loadBar("img//range_back_bar.png", "img//range_bar.png", g_screen);
    Range_bar_.setBarPosition(60, 48, 65, 48);

    //Home menu
    Button PlayButton;
    PlayButton.loadButton("img//PlayButton.png", g_screen);
    PlayButton.set_clips();
    PlayButton.setPosition(422, 264);

    ImageBase menu_background;
    menu_background.loadImg("img//StartMenu.png", g_screen);

    Button InstructionButton;
    InstructionButton.loadButton("img//InstructionButton.png", g_screen);
    InstructionButton.set_clips();
    InstructionButton.setPosition(422, 330);

    ImageBase instruction_menu;
    instruction_menu.loadImg("img//InstructionMenu.png", g_screen);

    Button BackButton;
    BackButton.loadButton("img//NoButton.png", g_screen);
    BackButton.set_clips();
    BackButton.setPosition(896, 43);

    Button CreditButton;
    CreditButton.loadButton("img//CreditsButton.png", g_screen);
    CreditButton.set_clips();
    CreditButton.setPosition(422, 396);

    ImageBase credit_menu;
    credit_menu.loadImg("img//CreditMenu.png", g_screen);

    Button ExitButton;
    ExitButton.loadButton("img//ExitButton.png", g_screen);
    ExitButton.set_clips();
    ExitButton.setPosition(422, 462);

    bool Quit_Menu = false;
    bool Play_Again = true;

    //Yes No button
    Button YesButton;
    YesButton.loadButton("img//YesButton.png", g_screen);
    YesButton.set_clips();
    YesButton.setPosition(366, 474);

    Button NoButton;
    NoButton.loadButton("img//NoButton.png", g_screen);
    NoButton.set_clips();
    NoButton.setPosition(690, 474);

    //Win menu
    ImageBase win_menu;
    win_menu.loadImg("img//WinMenu.png", g_screen);

    //Lose menu
    ImageBase lose_menu;
    lose_menu.loadImg("img//LoseMenu.png", g_screen);

    //Music
    Button MusicButton;
    MusicButton.loadButton("img//MusicButton.png", g_screen);
    MusicButton.set_clips();
    MusicButton.setPosition(1040, 500);
    Mix_PlayMusic(gMusic, -1);

    Boss Boss;
    Boss.loadImg("img//BossIdle.png", g_screen);
    Boss.set_clips();
    int xPosBoss = 800 * TILE_SIZE - BOSS_FRAME_WIDTH;
    
    // Check meeting boss
    bool boss_battle = false;

    // Game state
    GameState gameState;
    

    while (!Quit_Menu)
    {
        bool Quit_Game = false;
        menu_background.Render(g_screen);
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                Quit_Game = true;
                Play_Again = false;
            }

            HandlePlayButton(&g_event, PlayButton, Quit_Menu, Play_Again);

            HandleInformationButton(&g_event, instruction_menu, InstructionButton, BackButton, g_screen, Quit_Game);

            HandleInformationButton(&g_event, credit_menu, CreditButton, BackButton, g_screen, Quit_Game);

            HandleExitButton(&g_event, ExitButton, Quit_Game);

            HandleMusicButton(&g_event, MusicButton, musicOn);

            if (Quit_Game == true)
            {
                return 0;
            }
        }

        PlayButton.ShowButton(g_screen);
        InstructionButton.ShowButton(g_screen);
        CreditButton.ShowButton(g_screen);
        ExitButton.ShowButton(g_screen);
        MusicButton.ShowSwitch(g_screen);
        SDL_RenderPresent(g_screen);
    }


    while (Play_Again)
    {
        Boss.set_is_dead(false);
        gameState = GAME_IN;
        p_player.set_hp(MAX_PLAYER_HP);
        p_player.reset_player();

        /*Boss.set_xpos(xPosBoss);
        Boss.set_ypos(0);
        Boss.reset_hp_();*/
        Boss.reset_boss(boss_battle);

        threats_list = MakeThreatsList();
        while (gameState == GAME_IN)
        {
            fps_timer.start();

            while (SDL_PollEvent(&g_event) != 0)
            {
                if (g_event.type == SDL_QUIT)
                {
                    gameState = GAME_OUT;
                    Play_Again = false;
                }
                p_player.HandelInputAction(g_event, g_screen);
                HandleMusicButton(&g_event, MusicButton, musicOn);
            }


            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);

            g_background.renderBackground(g_screen, NULL);

            Map map_data = game_map.getMap();

            p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
            p_player.DoPlayer(map_data, boss_battle);
            game_map.SetMap(map_data);
            game_map.DrawMap(g_screen);
            p_player.Show(g_screen);

            if (p_player.get_player_x_pos() >= TILE_SIZE * 800 - (SCREEN_WIDTH / 2)) boss_battle = true;

            if (!Boss.get_is_dead())
            {
                Boss.SetMapXY(map_data.start_x_, map_data.start_y_);
                Boss.HandleMove(map_data, p_player.get_player_x_pos(), boss_battle);
                Boss.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT, p_player.GetRect().x, boss_battle);
                Boss.MakeSkill(g_screen, p_player.GetRect().x, boss_battle);
                Boss.Show(g_screen);
                if (boss_battle)
                {
                    Boss_HP_bar.updateBar(Boss.get_hp(), MAX_BOSS_HP);
                    Boss_HP_bar.showBar(g_screen);
                }

            }

            for (int i = 0; i < threats_list.size(); i++)
            {
                Threat* p_threat = threats_list.at(i);
                if (p_threat != NULL)
                {
                    p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                    p_threat->ImpMoveType(g_screen);
                    p_threat->DoPlayer(map_data);

                    p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                    p_threat->Show(g_screen);

                    SDL_Rect rect_player = p_player.GetRectFrame();
                    bool bCol1 = false;
                    std::vector<Bullet*> tBullet_list = p_threat->get_bullet_list();
                    for (int jj = 0; jj < tBullet_list.size(); jj++)
                    {
                        Bullet* pt_bullet = tBullet_list.at(jj);
                        if (pt_bullet != NULL)
                        {
                            bCol1 = SDLCommonFunction::CheckCollision(pt_bullet->GetRectFrame(), rect_player);
                            if (bCol1)
                            {
                                p_threat->RemoveBullet(jj);
                                break;
                            }
                        }
                    }

                    SDL_Rect rect_threat = p_threat->GetRectFrame();
                    bool bCol2 = SDLCommonFunction::CheckCollision(rect_player, rect_threat);

                    if (bCol1 || bCol2)
                    {
                        if (!p_player.is_immortal())
                        {
                            p_player.decrease_hp(1);

                            if (p_player.get_hp() > 0)
                            {
                                p_player.set_immortal_time(54);
                                if (bCol2) p_player.set_y_val(15);
                                break;
                            }

                            if (p_player.get_is_dead())
                            {
                                gameState = GAME_OVER;
                            }
                        }
                    }
                }
            }

            std::vector<Bullet*> bullet_arr = p_player.get_bullet_list();
            for (int r = 0; r < bullet_arr.size(); r++)
            {
                Bullet* p_bullet = bullet_arr.at(r);
                if (p_bullet != NULL)
                {
                    SDL_Rect bRect = p_bullet->GetRectFrame();
                    for (int t = 0; t < threats_list.size(); t++)
                    {
                        Threat* obj_threat = threats_list.at(t);
                        if (obj_threat != NULL)
                        {
                            SDL_Rect tRect = obj_threat->GetRectFrame();

                            bool bCol = SDLCommonFunction::CheckCollision(bRect, tRect);

                            if (bCol)
                            {
                                mark_value++;

                                p_player.RemoveBullet(r);
                                obj_threat->Free();
                                threats_list.erase(threats_list.begin() + t);
                            }
                        }
                    }

                    SDL_Rect boRect = Boss.GetRectFrame();
                    bool BCol = SDLCommonFunction::CheckCollision(boRect, bRect);
                    {
                        if (BCol)
                        {
                            Boss.decrease_hp(1);
                            p_player.RemoveBullet(r);
                            if (Boss.get_hp() >= 0)
                            {
                                Boss.set_is_hurt(true);
                            }

                            p_player.RemoveBullet(r);
                        }
                    }
                }
            }

            std::vector<Skill*> ultimate_arr = p_player.get_ultimate_list();
            for (int r = 0; r < ultimate_arr.size(); r++)
            {
                Skill* p_ultimate = ultimate_arr.at(r);
                if (p_ultimate != NULL)
                {
                    SDL_Rect bRect = p_ultimate->GetRectFrame();
                    for (int t = 0; t < threats_list.size(); t++)
                    {
                        Threat* obj_threat = threats_list.at(t);
                        if (obj_threat != NULL)
                        {
                            SDL_Rect tRect = obj_threat->GetRectFrame();

                            bool bCol = SDLCommonFunction::CheckCollision(bRect, tRect);

                            if (bCol)
                            {
                                if (p_ultimate->get_is_damaging())
                                {
                                    mark_value++;
                                    obj_threat->Free();
                                    threats_list.erase(threats_list.begin() + t);
                                }
                            }
                        }
                    }
                    
                    SDL_Rect boRect = Boss.GetRectFrame();
                    bool BCol = SDLCommonFunction::CheckCollision(boRect, bRect);
                    {
                        if (BCol)
                        {
                            if (p_ultimate->get_is_damaging())
                            {
                                Boss.decrease_hp(15);
                            }

                            if (Boss.get_hp() >= 0)
                            {
                                Boss.set_is_hurt(true);
                            }

                        }
                    }
                }
            }

            SDL_Rect rect_player = p_player.GetRectFrame();
            
            std::vector<Bullet*> tBullet_list = Boss.get_bullet_list();
            for (int b = 0; b < tBullet_list.size(); b++)
            {
                Bullet* pt_bullet = tBullet_list.at(b);
                if (pt_bullet != NULL)
                {
                    bool bCol1 = SDLCommonFunction::CheckCollision(pt_bullet->GetRect(), rect_player);
                    if (bCol1)
                    {
                        Boss.RemoveBullet(b);
                        if (!p_player.is_immortal())
                        {
                            p_player.decrease_hp(3);

                            if (p_player.get_hp() > 0)
                            {
                                p_player.set_immortal_time(54);
                                break;
                            }

                            if (p_player.get_is_dead())
                            {
                                gameState = GAME_OVER;
                            }
                        }
                    }
                }
            }
             
            std::vector<Skill*> skill_arr = Boss.get_skill_list();
            for (int r = 0; r < skill_arr.size(); r++)
            {
                Skill* p_skill = skill_arr.at(r);
                if (p_skill != NULL)
                {
                    SDL_Rect bRect = p_skill->GetRectFrame();
                    
                    bool bCol = SDLCommonFunction::CheckCollision(bRect, rect_player);

                    if (bCol)
                    {
                        if (p_skill->get_is_damaging())
                        {
                            if (!p_player.is_immortal())
                            {
                                p_player.decrease_hp(3);

                                if (p_player.get_hp() > 0)
                                {
                                    p_player.set_immortal_time(54);
                                    break;
                                }

                                if (p_player.get_is_dead())
                                {
                                    gameState = GAME_OVER;
                                }
                            }
                        }
                    }
                        
                }
            }

            bool player_and_boss = SDLCommonFunction::CheckCollision(rect_player, Boss.GetRectFrame());
            if (player_and_boss)
            {
                if (!p_player.is_immortal())
                {
                    p_player.decrease_hp(2);
                    p_player.set_x_val(30);
                    p_player.set_y_val(15);

                    if (p_player.get_hp() > 0)
                    {
                        p_player.set_immortal_time(54);
                        break;
                    }

                    if (p_player.get_is_dead())
                    {
                        gameState = GAME_OVER;
                    }
                }
            }
          
            p_player.decrease_immortal_time();
            p_player.HandleUltimate(g_screen);
            p_player.HandleBullet(g_screen);

            std::string val_str_mark = std::to_string(mark_value);
            std::string strMark("Score: ");
            strMark += val_str_mark;

            mark_game.SetText(strMark);
            mark_game.LoadFromRenderText(font_time, g_screen);
            mark_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 50, 15);

            if (Boss.get_is_dead())
            {
                gameState = GAME_WIN;
            }

            //Show HP bar
            HP_bar.updateBar(p_player.get_hp(), MAX_PLAYER_HP);
            HP_bar.showBar(g_screen);

            //Show Range bar
            Range_bar_.updateBar(p_player.get_range(), RANGE_MAX);
            Range_bar_.showBar(g_screen);

            MusicButton.ShowSwitch(g_screen);

            SDL_RenderPresent(g_screen);

            int real_imp_time = fps_timer.get_ticks();
            int time_one_frame = 1000 / FRAME_PER_SECOND;

            if (real_imp_time < time_one_frame)
            {
                int delay_time = time_one_frame - real_imp_time;
                if (delay_time >= 0)
                    SDL_Delay(delay_time);
            }

        }
        while (gameState == GAME_OVER)
        {
            while (SDL_PollEvent(&g_event) != 0)
            {
                if (g_event.type == SDL_QUIT)
                {
                    gameState = GAME_OUT;
                    Play_Again = false;

                }
                HandleYesButton(&g_event, YesButton, gameState);
                HandleNoButton(&g_event, NoButton, gameState, Play_Again);
            }

            lose_menu.Render(g_screen);
            YesButton.ShowButton(g_screen);
            NoButton.ShowButton(g_screen);
            SDL_RenderPresent(g_screen);

        }
        
        while (gameState == GAME_WIN)
        {
            while (SDL_PollEvent(&g_event) != 0)
            {
                if (g_event.type == SDL_QUIT)
                {
                    gameState = GAME_OUT;
                    Play_Again = false;

                }
                HandleYesButton(&g_event, YesButton, gameState);
                HandleNoButton(&g_event, NoButton, gameState, Play_Again);
            }
            win_menu.Render(g_screen);
            YesButton.ShowButton(g_screen);
            NoButton.ShowButton(g_screen);
            SDL_RenderPresent(g_screen);

        }

        threats_list.clear();
    }
    close();
    SDL_Quit();
    return 0;

}


