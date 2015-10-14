#ifndef VIEW_H
#define VIEW_H

#include "includes.h"

namespace IFSGUI
{
    typedef enum IFSGSnapTo
    {
        SnapNone,
        SnapHCenter,
        SnapVCenter,
        SnapBoth
    } IFSGSnapTo;

    class View : public std::enable_shared_from_this<View>
    {


        public:
        
            string name;

            bool hidden = false;

            //If a mouse is clicked over this view, that click does not trickle into the game simulation
            bool eatsClicks = false;

            SDL_Rect frame;

            int borderWidth = 0;

            SDL_Color borderColor;

            //Snaps are helpers that override normal positioning at the RenderFrame level
            IFSGSnapTo snap;

            //View::superview;// = whateverValue;

            View *superview;

            list<boost::shared_ptr<View>> subviews;

            virtual void AddSubview(boost::shared_ptr<View> theView);

            void RemoveAllSubviews();

            void RemoveFromSuperview();

            SDL_Color backgroundColor;

            //Returns: whether or not the click was handled and eaten
            virtual bool HandleClick();

            //auto clickLambda = nullptr;

            //IFSGUIEventHandler clickHandler = nullptr;
            std::function<void ()> clickHandler;

            virtual void Render();

            virtual SDL_Rect RenderFrame();

            View();
            virtual ~View();

        protected:


            double RenderScale();
            SDL_Rect WindowSize();
        
            list<boost::shared_ptr<View>> subviewsToRemove;

        private:
            bool MatchTo(View *view);




    };
}



#endif // VIEW_H
