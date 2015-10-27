Hi, this repo is still under construction, I'm doing a lot of refactoring as I rip this code out of one of my other projects. So this is not intended for use yet... check back soon and I'll have information in this file as to what this repo is all about...


#Basics

This library provides a set of basic user interface controls for use with the SDL2 renderer. SDL_TTF and SDL_Image are required plugins. At the moment, this library is built with SDL_RenderSetLogicalSize in mind to support total resolution independence at a given aspect ratio. Going outside of your aspect ratio will result in letter-boxing. Use of this library without SDL_RenderSetLogicalSize is hypothetical... I guess if you were writing an app for a very specific device like an iPad or an Xbox One, you'd probably be fine.

The most significant weakness of this library at the moment is font-downscaling yielding too much blurriness. I have plans to fix this. Not implemented yet.