#ifndef METER_H
#define METER_H

#include "View.h"

using namespace SDLGUI;

namespace SDLGUI
{

    class Meter : public View
    {
        public:

            bool horizontal = false;

            SDL_Color meterColor;
            SDL_Texture *meterTexture;

            int maximum;
            int value;

            virtual void Render();

            Meter();
            virtual ~Meter();

        protected:
        private:

            boost::shared_ptr<View> meterView;
    };

}

#endif // METER_H
