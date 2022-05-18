/*Using SDL and standard IO*/
// #define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>

#define UNUSED(x) (void)(x)

/*Screen dimension constants*/
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* argv[] )
{
    UNUSED(argc);
    UNUSED(argv);
    /*The window we'll be rendering to*/
    SDL_Window* window = NULL;
    
    /*The surface contained by the window*/
    SDL_Surface* screenSurface = NULL;

    /*Initialize SDL*/
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    
    else
    {
        /*Create window*/
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            /*Get window surface*/
            screenSurface = SDL_GetWindowSurface( window );

            /*Fill the surface white*/
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
            /*Update the surface*/
            SDL_UpdateWindowSurface( window );

            /*Wait two seconds*/
            SDL_Delay( 6000 );
        }
    }
        /*Destroy window*/
    SDL_DestroyWindow( window );

    /*Quit SDL subsystems*/
    SDL_Quit();

    return 0;
}

// int main( int argc, char *argv[] )
// {

//     UNUSED(argc);
//     UNUSED(argv);

//     if(SDL_Init(SDL_INIT_VIDEO) < 0)
//     {
//         printf("Failed to initialize the SDL2 library\n");
//         // std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
//         return -1;
//     }

//     SDL_Window *window = SDL_CreateWindow("SDL2 Window",
//                                           SDL_WINDOWPOS_CENTERED,
//                                           SDL_WINDOWPOS_CENTERED,
//                                           680, 480,
//                                           0);

//     if(!window)
//     {
//         printf("Failed to create window\n");
//         // std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
//         return -1;
//     }

//     SDL_Surface *window_surface = SDL_GetWindowSurface(window);

//     if(!window_surface)
//     {
//         printf("Failed to get the surface from the window\n");
//         // std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
//         return -1;
//     }

//     int open = 1;
//     while(open == 1)
//     {
//         SDL_Event e;
//         while(SDL_PollEvent(&e) > 0)
//         {
//             switch(e.type)
//             {
//                 case SDL_QUIT:
//                     open = 0;
//                     break;
//             }

//             SDL_UpdateWindowSurface(window);
//         }
//     }
//     return 0;
// }