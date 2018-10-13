#ifdef TILES

#include "sdl_wrappers.h"

#include "debug.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <cassert>

#define dbg(x) DebugLog((DebugLevel)(x),D_SDL) << __FILE__ << ":" << __LINE__ << ": "

void printErrorIf( const bool condition, const char *const message )
{
    if( !condition ) {
        return;
    }
    dbg( D_ERROR ) << message << ": " << SDL_GetError();
}

void throwErrorIf( const bool condition, const char *const message )
{
    if( !condition ) {
        return;
    }
    throw std::runtime_error( std::string( message ) + ": " + SDL_GetError() );
}

void RenderCopy( const SDL_Renderer_Ptr &renderer, const SDL_Texture_Ptr &texture,
                 const SDL_Rect *srcrect, const SDL_Rect *dstrect )
{
    if( !renderer ) {
        dbg( D_ERROR ) << "Tried to render to a null renderer";
        return;
    }
    if( !texture ) {
        dbg( D_ERROR ) << "Tried to render a null texture";
        return;
    }
    printErrorIf( SDL_RenderCopy( renderer.get(), texture.get(), srcrect, dstrect ) != 0,
                  "SDL_RenderCopy failed" );
}

SDL_Texture_Ptr CreateTextureFromSurface( const SDL_Renderer_Ptr &renderer,
        const SDL_Surface_Ptr &surface )
{
    if( !renderer ) {
        dbg( D_ERROR ) << "Tried to create texture with a null renderer";
        return SDL_Texture_Ptr();
    }
    if( !surface ) {
        dbg( D_ERROR ) << "Tried to create texture from a null surface";
        return SDL_Texture_Ptr();
    }
    SDL_Texture_Ptr result( SDL_CreateTextureFromSurface( renderer.get(), surface.get() ) );
    printErrorIf( !result, "SDL_CreateTextureFromSurface failed" );
    return result;
}

void SetRenderDrawColor( const SDL_Renderer_Ptr &renderer, const Uint8 r, const Uint8 g,
                         const Uint8 b, const Uint8 a )
{
    if( !renderer ) {
        dbg( D_ERROR ) << "Tried to use a null renderer";
        return;
    }
    printErrorIf( SDL_SetRenderDrawColor( renderer.get(), r, g, b, a ) != 0,
                  "SDL_SetRenderDrawColor failed" );
}

void RenderFillRect( const SDL_Renderer_Ptr &renderer, const SDL_Rect *const rect )
{
    if( !renderer ) {
        dbg( D_ERROR ) << "Tried to use a null renderer";
        return;
    }
    printErrorIf( SDL_RenderFillRect( renderer.get(), rect ) != 0, "SDL_RenderFillRect failed" );
}

void SetRenderDrawBlendMode( const SDL_Renderer_Ptr &renderer, const SDL_BlendMode blendMode )
{
    if( !renderer ) {
        dbg( D_ERROR ) << "Tried to use a null renderer";
        return;
    }
    printErrorIf( SDL_SetRenderDrawBlendMode( renderer.get(), blendMode ) != 0,
                  "SDL_SetRenderDrawBlendMode failed" );
}

SDL_Surface_Ptr load_image( const char *const path )
{
    assert( path );
    SDL_Surface_Ptr result( IMG_Load( path ) );
    if( !result ) {
        throw std::runtime_error( "Could not load image \"" + std::string( path ) + "\": " +
                                  IMG_GetError() );
    }
    return result;
}

void SetRenderTarget( const SDL_Renderer_Ptr &renderer, const SDL_Texture_Ptr &texture )
{
    if( !renderer ) {
        dbg( D_ERROR ) << "Tried to use a null renderer";
        return;
    }
    // a null texture is fine for SDL
    printErrorIf( SDL_SetRenderTarget( renderer.get(), texture.get() ) != 0,
                  "SDL_SetRenderTarget failed" );
}

#endif
