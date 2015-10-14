#include "ImageView.h"
//#include "Game.h"
#include "SDLManager.h"

using namespace SDLGUI;

void ImageView::Render()
{
    View::Render();

    //LOG(logDEBUG) << "Rendering image view";

    if(this->image != nullptr)
    {
        SDL_Rect targBounds = this->RenderFrame();

        SDL_RenderCopy(SDL_Manager::sharedManager->renderer, this->image, NULL, &targBounds);
    }
}

void ImageView::SetImageWithName(string name)
{
    string path = "assets/images/" + name + ".png";

    this->image = IMG_LoadTexture(SDL_Manager::sharedManager->renderer, path.c_str());
}

ImageView::ImageView()
{
    this->image = nullptr;
    //ctor
}

ImageView::~ImageView()
{
    //dtor
}
