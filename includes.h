//
//  includes.h
//  SDL_gui
//
//  Created by Michael Ryan on 10/13/15.
//  Copyright © 2015 Michael Ryan. All rights reserved.
//

#ifndef includes_h
#define includes_h

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <boost/shared_ptr.hpp>

#include <boost/serialization/extended_type_info.hpp>//make boost run on 32bit
#include <boost/serialization/singleton.hpp>//make boost run on 32bit
#include <boost/serialization/shared_ptr.hpp>
//#include <boost/archive/shared_ptr_helper.hpp>
#include <boost/serialization/shared_ptr_helper.hpp>

//Boost archiving
// include headers that implement a archive
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <boost/serialization/vector.hpp>

#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost;

#endif /* includes_h */
