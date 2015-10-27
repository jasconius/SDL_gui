//
//  SDLManager.cpp
//  SDL_gui
//
//  Created by Michael Ryan on 10/13/15.
//  Copyright © 2015 Michael Ryan. All rights reserved.
//

#include "SDLManager.h"

SDL_Manager *SDL_Manager::sharedManager = nullptr;

SDL_Manager::SDL_Manager(SDL_Window *theWindow, SDL_Renderer *theRenderer, int theLogicalWindowWidth, int theLogicalWindowHeight, string thePathToDefaultFont, int theDefaultFontSize)
{
    sharedManager = this;
    
    this->window = theWindow;
    this->renderer = theRenderer;
    this->logicalWindowWidth = theLogicalWindowWidth;
    this->logicalWindowHeight = theLogicalWindowHeight;
    //this->defaultFont = theDefaultFont;
    
    this->pathToDefaultFont = thePathToDefaultFont;
    this->defaultFont = TTF_OpenFont(thePathToDefaultFont.c_str(), theDefaultFontSize);
}