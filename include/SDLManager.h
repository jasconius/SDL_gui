//
//  SDLManager.h
//  SDL_gui
//
//  Created by Michael Ryan on 10/13/15.
//  Copyright © 2015 Michael Ryan. All rights reserved.
//

#ifndef SDLManager_h
#define SDLManager_h

#include "includes.h"

namespace SDLGUI
{
    class SDL_Manager
    {
        
    public:
        SDL_Renderer *renderer;
        
        SDL_Window *window;
        
        int logicalWindowWidth;
        int logicalWindowHeight;
        
        float logicalScale;
        
        TTF_Font *defaultFont;
        string pathToDefaultFont;
        
        SDL_Manager(SDL_Window *theWindow, SDL_Renderer *theRenderer, int theLogicalWindowWidth, int theLogicalWindowHeight, string thePathToDefaultFont, int theDefaultFontSize);
        
        static SDL_Manager *sharedManager;
        
    };
}

using namespace SDLGUI;

#endif /* SDLManager_h */
