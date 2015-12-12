#include "View.h"
//#include "Game.h"
#include "SDLManager.h"

using namespace SDLGUI;


void View::setClickHandler(std::function<void ()> theHandler)
{
    this->clickHandler = theHandler;
    
    if (this->clickHandler == NULL)
    {
        this->eatsClicks = false;
    }
    else
    {
        this->eatsClicks = true;
    }
}

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

bool View::ShouldSnapX()
{
    return this->snap == SnapHCenter || this->snap == SnapBoth;
}

bool View::ShouldSnapY()
{
    return this->snap == SnapVCenter || this->snap == SnapBoth;
}

double View::RenderScale()
{
	return this->WindowSize().h / (double)SDL_Manager::sharedManager->logicalWindowHeight;
}

SDL_Rect View::LogicalFrame()
{
    int xSnap = 0;
    int ySnap = 0;
    
    SDL_Rect parentFrame;
    
    if (this->superview != nullptr)
    {
        parentFrame = this->superview->LogicalFrame();
    }
    else
    {
        parentFrame.h = SDL_Manager::sharedManager->logicalWindowHeight;
        parentFrame.w = SDL_Manager::sharedManager->logicalWindowWidth;
    }
    
    if (this->ShouldSnapX())
    {
        xSnap = parentFrame.w / 2;
        xSnap -= (this->frame.w) / 2;
    }
    
    if (this->ShouldSnapY())
    {
        ySnap = parentFrame.h / 2;
        ySnap -= (this->frame.h) / 2;
    }
    
    SDL_Rect retval = {
        this->ShouldSnapX() ? xSnap : (int)ceilf(this->frame.x),
        this->ShouldSnapY() ? ySnap : (int)ceilf(this->frame.y),
        (int)ceilf(this->frame.w),
        (int)ceilf(this->frame.h)
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

//TODO this over-evaluates RenderScale
SDL_Rect View::RenderFrame()
{
    double scale = this->RenderScale();
    
    scale = 1.0f;

    SDL_Rect retval = this->LogicalFrame();

    retval.w = (int)ceilf(retval.w * scale);
    retval.h = (int)ceilf(retval.h * scale);
    
    if (!this->ShouldSnapY())
    {
        retval.y = (int)ceilf(retval.y * scale);
    }
    
    if (!this->ShouldSnapX())
    {
        retval.x = (int)ceilf(retval.x * scale);
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
        int x, y;
        
        SDL_GetMouseState(&x, &y);

        SDL_Rect clickRect = {
            (int)((float)x*SDL_Manager::sharedManager->logicalScale),
            (int)((float)y*SDL_Manager::sharedManager->logicalScale),
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
