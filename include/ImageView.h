#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include "View.h"

#include "includes.h"

namespace SDLGUI
{
    class ImageView : public View
    {
        public:

            SDL_Texture *image;

            void SetImage(SDL_Texture *tex);

            void SetImageWithName(string name);

            virtual void Render();

            ImageView();
            virtual ~ImageView();
        protected:
        private:
    };
}

#endif // IMAGEVIEW_H
