//
//  Game.h
//  SDL_gui
//
//  Created by Michael Ryan on 10/13/15.
//  Copyright © 2015 Michael Ryan. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include "includes.h"
#include "SDLGUI.h"

using namespace IFSGUI;
using namespace Awesomium;

class Game
{
    
public:
    
    string base_resource_path;
    void InitializeDataPath();
    
    
    static Game *SharedGame;
    
    static string inputText;
    
    //Essential
    Game();
    //virtual ~Game();
    int OnExecute();
    bool OnInit();
    bool LoadContent();
    void BuildGame();
    void OnEvent(SDL_Event *Event);
    void OnLoop();
    void OnRender();
    void Cleanup();
    
    void OnMainMenuEvent(SDL_Event *Event);
    void OnGameEvent(SDL_Event *Event);
    
    bool onMainMenu = false;
    bool runningGame = false;
    bool buildGameNow = false;
    
    void MenuRender();
    void GameRender();
    
    bool paused = false;
    void Pause();
    void Unpause();
    
    void ShowCursor(SDL_SystemCursor id);
    
    int lastTime = 0;
    
    bool acceptingTextInput;
    
    SDL_Point lastKnownMousePos;
    
    
    boost::shared_ptr<ViewController> activeViewController;
    
    
    void SetFullscreen();
    void SetWindowed();
    
    TTF_Font *guiFont;
    
    SDL_Renderer *renderer;
    
    SDL_Window *window;
    
    SDL_Texture *gameTex;
    
    //Demo
protected:
private:
    //Essential
    bool Running;
    
};

#endif /* Game_h */
