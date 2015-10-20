//
//  Game.cpp
//  SDL_gui
//
//  Created by Michael Ryan on 10/13/15.
//  Copyright © 2015 Michael Ryan. All rights reserved.
//

#include <stdio.h>
#include "Game.h"


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
    
    return true;
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
    
    SDL_SetRenderTarget(Game::SharedGame->renderer, gameTex);
    SDL_SetRenderDrawColor(Game::SharedGame->renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    if(runningGame)
    {
        activeViewController->Render();
    }
    
    SDL_SetRenderTarget(Game::SharedGame->renderer, NULL);
    SDL_RenderClear(Game::SharedGame->renderer);
    SDL_RenderCopy(Game::SharedGame->renderer, gameTex, NULL, NULL);
    
    SDL_RenderPresent(renderer);
}

void Game::Cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}