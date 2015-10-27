#include "Label.h"
//#include "Game.h"
#include "SDLManager.h"

//Walk back the W/H scaling on labels to prevent fuzzy text
//Also compute special snaps
SDL_Rect Label::RenderFrame()
{
    SDL_Rect retval = View::RenderFrame();

    bool shouldSnapX = false;
    bool shouldSnapY = false;

    int xSnap = 0;
    int ySnap = 0;

    if(snap != SnapNone)
    {
        SDL_Rect windowSz = this->WindowSize();

        if(this->superview != nullptr)
        {
            windowSz = this->superview->RenderFrame();

            //LOG(logDEBUG) << "superview rect for label " << windowSz.w << " " << windowSz.h;
        }

        if(snap == SnapHCenter)
        {
            shouldSnapX = true;
            xSnap = windowSz.w / 2;
            xSnap -= (this->frame.w) / 2;
        }

        if(snap == SnapVCenter)
        {
            shouldSnapY = true;
            ySnap = windowSz.h / 2;
            ySnap -= (this->frame.h) / 2;
        }

        if(snap == SnapBoth)
        {
            shouldSnapX = true;
            xSnap = windowSz.w / 2;
            xSnap -= (this->frame.w) / 2;

            shouldSnapY = true;
            ySnap = windowSz.h / 2;
            ySnap -= (this->frame.h) / 2;
        }
    }

    //LOG(logDEBUG) << "Label X and Y snap: " << xSnap << " " << ySnap;

    double scale = this->RenderScale();

    retval.x = shouldSnapX ? xSnap : (int)ceilf(this->frame.x * scale);
    retval.y = shouldSnapY ? ySnap : (int)ceilf(this->frame.y * scale);

    retval.w /= scale;
    retval.h /= scale;

    //Add superview x/y
    if(this->superview != nullptr)
    {
        //if(!shouldSnapX)
        //{
            retval.x += this->superview->RenderFrame().x;
        //}

        //if(!shouldSnapY)
        //{
            retval.y += this->superview->RenderFrame().y;
        //}
    }

    return retval;
}

void Label::SetText(string theText)
{
	if(this->text != theText)
	{
		this->text = theText;
        
        double scale = this->RenderScale();
        
        double scaledFontSize = (double)fontSize;
        
        scaledFontSize *= scale;
        
        int scaledFontInt = (int)scaledFontSize;
		
        TTF_Font *guiFont = TTF_OpenFont(SDL_Manager::sharedManager->pathToDefaultFont.c_str(), scaledFontInt);
		
		SDL_Surface *newLineSurface = TTF_RenderText_Blended(guiFont, theText.c_str(), this->textColor);
		
		this->frame.w = newLineSurface->w;
		this->frame.h = newLineSurface->h;
		
		if(labelTex != NULL)
		{
			//TODO need to research this so it both works and doesn't crash shit
			SDL_DestroyTexture(labelTex);
		}
		
        labelTex = SDL_CreateTextureFromSurface(SDL_Manager::sharedManager->renderer, newLineSurface);
		
		SDL_FreeSurface(newLineSurface);
		
		TTF_CloseFont(guiFont);
	}
}

void Label::Render()
{
    View::Render();

    SDL_Rect txtRect = this->RenderFrame();

    SDL_RenderCopy(SDL_Manager::sharedManager->renderer, labelTex, NULL, &txtRect);
}

Label::Label()
{
    //ctor
    textColor.r = textColor.g = textColor.b = textColor.a = 255;
    backgroundColor.r = backgroundColor.g = backgroundColor.b = backgroundColor.a = 0;
    borderWidth = 1;
    fontSize = kDEFAULT_FONT_SIZE;
}

Label::~Label()
{
    //dtor
    SDL_DestroyTexture(labelTex);
}
