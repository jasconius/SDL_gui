#include "View.h"
//#include "Game.h"
#include "SDLManager.h"

using namespace SDLGUI;

SDL_Rect View::WindowSize()
{
    int w = 0;
    int h = 0;
    
    //SDL_GetWindow
    
    SDL_GetWindowSize(SDL_Manager::sharedManager->window, &w, &h);

    SDL_Rect retval = {
        0,
        0,
        w,
        h
    };

    return retval;
}

double View::RenderScale()
{
	return this->WindowSize().h / (double)SDL_Manager::sharedManager->logicalWindowHeight;
}

//TODO this over-evaluates RenderScale
SDL_Rect View::RenderFrame()
{
    double scale = this->RenderScale();
    
    scale = 1.0f;

    bool shouldSnapX = false;
    bool shouldSnapY = false;

    int xSnap = 0;
    int ySnap = 0;

    if(snap != SnapNone)
    {
        SDL_Rect windowSz;
        windowSz.h = this->WindowSize().h;
        windowSz.w = this->WindowSize().w;

        if(this->superview != nullptr)
        {
            windowSz = this->superview->RenderFrame();
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
            ySnap -= (this->frame.h * scale) / 2;
        }

        if(snap == SnapBoth)
        {
            shouldSnapX = true;
            xSnap = windowSz.w / 2;
            xSnap -= (this->frame.w * scale) / 2;

            shouldSnapY = true;
            ySnap = windowSz.h / 2;
            ySnap -= (this->frame.h * scale) / 2;
        }
    }

    SDL_Rect retval = {
        shouldSnapX ? xSnap : (int)ceilf(this->frame.x * scale),
        shouldSnapY ? ySnap : (int)ceilf(this->frame.y * scale),
        (int)ceilf(this->frame.w * scale),
        (int)ceilf(this->frame.h * scale)
    };

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

void View::RemoveAllSubviews()
{
    this->subviews.clear();
}

void View::AddSubview(boost::shared_ptr<View> theView)
{
    //LOG(logDEBUG) << "Adding subview that has X... " << theView->frame.x;

    //shared_ptr<View> test(this);

    theView->superview = this;
    this->subviews.push_back(theView);
}

bool View::MatchTo(View *view)
{
    if(this == view)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void View::RemoveFromSuperview()
{
    if(this->superview != nullptr)
    {
        boost::shared_ptr<View> me;

        for (auto & i: this->superview->subviews)
        {
            if(i->MatchTo(this))
            {
                me = i;
            }
        }
        
        this->superview->subviewsToRemove.push_back(me);
    }
}

bool View::HandleClick()
{
    bool retval = false;

    for (auto const& i: this->subviews)
    {
        if(i != nullptr)
        {
            if(i->HandleClick())
            {
                retval = true;
                break;
            }
        }
    }

    //Always prefer childrens click handling. the deepest possible view gets to handle
    if(this->eatsClicks && !retval)
    {
        //Get the mouse state and figure out if it's a click on the render bounds
        SDL_Point simClick = SDL_Manager::sharedManager->lastKnownMousePos;

        SDL_Rect clickRect = {
            simClick.x,
            simClick.y,
            5,
            5
        };

        SDL_Rect renderRect = this->RenderFrame();
        SDL_Rect intersect;

        SDL_bool hit = SDL_IntersectRect(&clickRect, &renderRect, &intersect);

        if(hit)
        {
            //Eat the click even if the event handler is null
            retval = true;

            //Run click handler
            if(this->clickHandler != nullptr)
            {
                this->clickHandler();
            }
        }

    }

    return retval;
}

void View::Render()
{
    if(hidden)
    {
        return;
    }
    
    SDL_SetRenderDrawBlendMode(SDL_Manager::sharedManager->renderer, SDL_BLENDMODE_BLEND);

    SDL_Rect targBounds = this->RenderFrame();
	
	

    SDL_SetRenderDrawColor(SDL_Manager::sharedManager->renderer, this->backgroundColor.r, this->backgroundColor.g, this->backgroundColor.b, this->backgroundColor.a);
    SDL_RenderFillRect(SDL_Manager::sharedManager->renderer, &targBounds);
    
    //TODO When I dump a view from the stack (Floater), this loop fucks up supremely
    for (boost::shared_ptr<View> i: this->subviews)
    {
        if(i != nullptr)
            i->Render();
    }
    
    if(borderWidth > 0)
    {
        SDL_Rect borderRect = targBounds;
        SDL_SetRenderDrawColor(SDL_Manager::sharedManager->renderer, this->borderColor.r, this->borderColor.g, this->borderColor.b, this->borderColor.a);
        SDL_RenderDrawRect(SDL_Manager::sharedManager->renderer, &borderRect);
    }
    
    for (boost::shared_ptr<View> i: this->subviewsToRemove)
    {
        if(i != nullptr)
            this->subviews.remove(i);
    }
    
    this->subviewsToRemove.clear();
}

View::View()
{
    this->backgroundColor.a = this->backgroundColor.r = this->backgroundColor.g = this->backgroundColor.b = 0;

    this->borderColor = {255,255,255,255};

    this->superview = NULL;

    this->frame = {
        0,
        0,
        this->WindowSize().w,
        this->WindowSize().h
    };

    this->clickHandler = nullptr;
    
    this->name = "v";
    
    this->snap = SnapNone;
}

View::~View()
{
    //dtor
}
