#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include "View.h"

using namespace SDLGUI;

namespace SDLGUI
{
    class ViewController
    {
        public:

            boost::shared_ptr<View> view;

            virtual void Update();
            void Render();

            ViewController();
            virtual ~ViewController();


        protected:
        private:
    };
}



#endif // VIEWCONTROLLER_H
