#include "Meter.h"
#include "ImageView.h"

void Meter::Render()
{
    double mod = (double)value / (double)maximum;

    if(horizontal)
    {
        meterView->frame.x = 0;
        meterView->frame.y = 0;
        meterView->frame.h = this->frame.h;
        meterView->frame.w = this->frame.w * mod;
    }
    else
    {
        //bkgRect.y+5+maxHealthHeight-healthHeight,

        meterView->frame.x = 0;

        meterView->frame.h = this->frame.h * mod;

        meterView->frame.y = 0 + this->frame.h - meterView->frame.h;

        meterView->frame.w = this->frame.w;
    }

    meterView->backgroundColor = this->meterColor;

    View::Render();

}

Meter::Meter()
{
    meterView = boost::make_shared<ImageView>();

    this->AddSubview(meterView);

    //ctor
}

Meter::~Meter()
{
    //dtor
}
