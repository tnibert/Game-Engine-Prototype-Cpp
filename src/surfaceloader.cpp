#include "ironlotus.h"

SurfaceLoader* SurfaceLoader::instance = NULL;

SurfaceLoader::SurfaceLoader() {}

SurfaceLoader* SurfaceLoader::getInstance() {
    if (instance == NULL) {
        instance = new SurfaceLoader();
        return instance;
    } else {
        return instance;
    }
}

void SurfaceLoader::setPixelFormat(Uint32 fmt) {
    pixelFmt = fmt;
}

/*
Load a surface from a file
Return NULL if we can't load the surface
*/
SDL_Surface* SurfaceLoader::loadSurface(char *fname) {
    SDL_Surface *temp = NULL;
    SDL_Surface *opt = NULL;

    if ((temp = IMG_Load(fname)) == NULL) {
        return NULL;
    }

    opt = SDL_ConvertSurfaceFormat(temp, pixelFmt, 0);
    SDL_FreeSurface(temp);

    return opt;
}