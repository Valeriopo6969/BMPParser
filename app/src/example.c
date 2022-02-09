#include "bmp_parser.h"

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("bmp_parser example",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          960,
                                          560,
                                          SDL_WINDOW_RESIZABLE);
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture *example_bgr24_texture;
    bmpp_get_texture("flower.bmp", renderer, &example_bgr24_texture);

    SDL_Texture *example_bgr32_texture;
    bmpp_get_texture("foo.bmp", renderer, &example_bgr32_texture);
    
    SDL_Rect dest_rect = {0,0,480,560};

    int running = 1;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
           
        }
        SDL_SetRenderDrawColor(renderer, 100,125,100,255);
        SDL_RenderClear(renderer);

        dest_rect.x = 0;
        SDL_RenderCopy(renderer,example_bgr24_texture,NULL,&dest_rect);

        dest_rect.x = 480;
        SDL_RenderCopy(renderer,example_bgr32_texture,NULL,&dest_rect);

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}       

 
	
         
  
   

    

