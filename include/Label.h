#ifndef LABEL_H
#define LABEL_H

#include "View.h"
#include "IFSGUISettings.h"

using namespace IFSGUI;

namespace IFSGUI
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
            virtual SDL_Rect RenderFrame();
        private:
    };
}

#endif // LABEL_H
