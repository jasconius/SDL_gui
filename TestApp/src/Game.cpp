//
//  Game.cpp
//  SDL_gui
//
//  Created by Michael Ryan on 10/13/15.
//  Copyright © 2015 Michael Ryan. All rights reserved.
//

#include <stdio.h>
#include "Game.h"

Game *Game::SharedGame;

int Game::OnExecute()
{
    if(OnInit() == false)
    {
        return -1;
    }
    
    if(LoadContent() == false)
    {
        return -1;
    }
    
    while(Running)
    {
        while(SDL_PollEvent(&Event))
        {
            OnEvent(&Event);
        }
        
        OnLoop();
        OnRender();
    }
    
    Cleanup();
    
    return 0;
}


void Game::res1click()
{
    
}

float logicalScale()
{
    return (float)kLogicalWindowHeight/(float)kWindowHeight;
}

bool Game::LoadContent()
{
    SDL_Manager::sharedManager->logicalScale = logicalScale();
    
    activeViewController = boost::make_shared<ViewController>();
    
    boost::shared_ptr<View> redView = boost::make_shared<View>();
    
    redView->backgroundColor = { 255,0,0,255 };
    redView->frame = { 0, 0, kLogicalWindowWidth, kLogicalWindowHeight };
    
    activeViewController->view->AddSubview(redView);
    
    boost::shared_ptr<Label> lblTest = boost::make_shared<Label>();
    
    lblTest->SetText("test");
    lblTest->snap = SnapHCenter;
    
    redView->AddSubview(lblTest);
    
    boost::shared_ptr<Button> btn1 = boost::make_shared<Button>();
    
    btn1->SetText("Set Res 1");
    
    btn1->setClickHandler([] () -> void {
        
        printf("btn1 clicked\n");
        
    });
    
    btn1->borderWidth = 2;
    
    redView->setClickHandler([] () -> void {
        
        printf("redview clicked\n");
        
    });
    
    //redView->eatsClicks = true;
    
    printf("test..\n");
    
    redView->AddSubview(btn1);
    
    
    return true;
}

bool Game::OnInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }
    
    if(TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }
    
    if(Mix_Init(MIX_INIT_MP3) == -1)
    {
        printf("Failed to MIX_INIT_MP3: %s\n", Mix_GetError());
        return false;
    }
    
    //Initialize SDL_mixer
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        printf("Failed to MIX_OpenAudio: %s\n", Mix_GetError());
        return false;
    }
    
    //SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    //SDL_WINDOW_FULLSCREEN_DESKTOP |
    if ((window = SDL_CreateWindow(kGAME_TITLE, -1500, 350, kWindowWidth, kWindowHeight, SDL_WINDOW_OPENGL | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED)) == NULL)
    {
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
    
    if(renderer == NULL)
    {
        cout << SDL_GetError() << endl;
        return 1;
    }
    
    if(kUSE_LOGICAL_SIZING == 1)
    {
        //Might fix rendering issue?
        //SDL_RenderSetScale
        
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
        
        SDL_RenderSetLogicalSize(renderer, kLogicalWindowWidth, kLogicalWindowHeight);
        //small fonts shouldn't technically be a problem... font size shifts relative to LOGICAL size, not literal window size
    }
    
    //this->guiFont = TTF_OpenFont("assets/fonts/arial.ttf", kSMALL_FONT_SIZE);
    
    SDL_Manager::sharedManager = new SDL_Manager(window, renderer, kLogicalWindowWidth, kLogicalWindowHeight, "assets/fonts/arial.ttf", 12);
    
    
    runningGame = true;
    //TTF_Font *test = new TTF_Font();
    
    return true;
}

void Game::OnEvent(SDL_Event *Event)
{
    if(Event->type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_MouseButtonEvent *e = (SDL_MouseButtonEvent *)Event;
        
        switch(e->button)
        {
            case SDL_BUTTON_LEFT:
                
                if(activeViewController->view->HandleClick())
                {
                    return;
                }
                
                
                
                break;
                
            case SDL_BUTTON_RIGHT:
                
                break;
        }
    }
}

void Game::OnLoop()
{
    if (runningGame)
    {
        activeViewController->Update();
    }
}

void Game::OnRender()
{
    //Create game buffer tex
    SDL_Rect gameRect = { 0, 0, kLogicalWindowWidth, kLogicalWindowHeight };
    
    if (gameTex == nullptr)
    {
        gameTex = SDL_CreateTexture(Game::SharedGame->renderer,
                                    SDL_PIXELFORMAT_ABGR8888,
                                    SDL_TEXTUREACCESS_TARGET,
                                    gameRect.w,
                                    gameRect.h);
    }
    
    //SDL_SetRenderTarget(Game::SharedGame->renderer, gameTex);
    SDL_SetRenderDrawColor(Game::SharedGame->renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    if(runningGame)
    {
        activeViewController->Render();
    }
    
    //SDL_SetRenderTarget(Game::SharedGame->renderer, NULL);
    //SDL_RenderClear(Game::SharedGame->renderer);
    //SDL_RenderCopy(Game::SharedGame->renderer, gameTex, NULL, NULL);
    
    SDL_RenderPresent(renderer);
}

void Game::Cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


Game::Game()
{
    window = NULL;
    Running = true;
    
    onMainMenu = true;
    runningGame = false;
    
    guiFont = NULL;
    
    activeViewController = nullptr;
    
    lastTime = 0;
    
    acceptingTextInput = false;
    
    Game::SharedGame = this;
    
    gameTex = nullptr;
    
}

int main(int argc, char* argv[])
{
    Game theGame;
    
    return theGame.OnExecute();
}