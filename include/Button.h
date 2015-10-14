#ifndef BUTTON_H
#define BUTTON_H

#include "View.h"
#include "Label.h"

namespace SDLGUI
{
    class Button : public View
    {
        public:

            void SetText(string text);

            Button();
            virtual ~Button();
        protected:

            boost::shared_ptr<Label> label;

        private:
    };
}


#endif // BUTTON_H
