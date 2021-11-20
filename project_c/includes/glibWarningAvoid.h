#ifndef ___GLIBW_H___
#define ___GLIBW_H___
/**
@file glibw.h
\brief Ficheiro que ignora warnings da glib.
*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic" 
#pragma GCC diagnostic ignored "-Wvariadic-macros"
#pragma GCC diagnostic ignored "-Wlong-long" 
#pragma GCC diagnostic ignored "-Wpedantic"

#include <glib.h>

#pragma GCC diagnostic pop

#endif
