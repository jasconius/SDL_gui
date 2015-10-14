#include "Button.h"

using namespace SDLGUI;

void Button::SetText(string text)
{
    label->SetText(text);
}

Button::Button()
{
    //ctor

    this->frame.w = 200;
    this->frame.h = 50;

    this->backgroundColor = {
        0x66,
        0x66,
        0x66,
        0xFF
    };

    label = boost::make_shared<Label>();
	
	label->fontSize = kDEFAULT_FONT_SIZE;

    label->SetText("My Button");

    label->snap = SnapBoth;

    this->AddSubview(label);

    this->eatsClicks = true;
}

Button::~Button()
{
    //dtor
}
