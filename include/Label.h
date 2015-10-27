#ifndef LABEL_H
#define LABEL_H

#include "View.h"
#include "SDLGUISettings.h"

using namespace SDLGUI;

namespace SDLGUI
{
    class Label : public View
    {
        public:

            void SetText(string theText);

            string text;

            int fontSize = kDEFAULT_FONT_SIZE;

            SDL_Color textColor;

            SDL_Texture *labelTex = NULL;

            virtual void Render();

            Label();
            virtual ~Label();

        protected:
            //virtual SDL_Rect RenderFrame();
        private:
    };
}

#endif // LABEL_H
