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



namespace IFSGUI
{
    class SDL_Manager
    {
        
    public:
        SDL_Renderer *renderer;
        
        SDL_Window *window;
        
        SDL_Point lastKnownMousePos;
        
        int logicalWindowWidth;
        int logicalWindowHeight;
        
        static SDL_Manager *sharedManager;
        
    };
}

using namespace IFSGUI;

#endif /* SDLManager_h */
