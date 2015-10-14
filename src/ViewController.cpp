#include "ViewController.h"
//#include "SDLManager.h"

void ViewController::Update()
{

}

void ViewController::Render()
{
    if(this->view != nullptr)
    {
        this->view->Render();
    }
}

ViewController::ViewController()
{
    //ctor

    view = boost::make_shared<View>();
    
}

ViewController::~ViewController()
{
    //dtor
}
