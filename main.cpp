
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<stdlib.h>
#include<list>



SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*game_background,*game1_background,*game2_background, *pelotita_mala, *pelotita_buena;
SDL_Rect rect_background,rect_pelotita,rect_pelotita1;
double delay=16.66;
int cont = 0;
int inte=1;
int sumaInte=3;
using namespace std;

void loopjuego()
{
    list<float>pelotitas_x;
    pelotitas_x.push_back(0);
    pelotitas_x.push_back(80);
    pelotitas_x.push_back(160);
    pelotitas_x.push_back(240);

    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                exit(0);
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_ESCAPE)
                    return;

            }
            if(Event.type == SDL_MOUSEBUTTONDOWN)
            {
                int clickX, clickY;
                SDL_GetMouseState(&clickX, &clickY);
                cout<<clickX<<" , "<<clickY<<endl;

                for(list<float>::iterator i=pelotitas_x.begin(); i!=pelotitas_x.end(); i++)
                {
                    if(clickX<66+(rect_pelotita.x) && clickX>(rect_pelotita.x) && clickY<(*i+66) && clickY>*i)
                    {

                        pelotitas_x.erase(i);
//                        delay = delay/3;

                        inte+=sumaInte;
                        sumaInte+=10;
                        cout<<delay<<endl;
                        break;
                    }
                }


            }
        }

        SDL_RenderCopy(renderer,game_background,NULL,&rect_background);
int x=0;
        rect_pelotita.x+=inte;
        for(list<float>::iterator i=pelotitas_x.begin(); i!=pelotitas_x.end(); i++)
        {
            x++;
            cout<<x<<endl;
            SDL_RenderCopy(renderer,pelotita_mala,NULL,&rect_pelotita);
            //rect_pelotita.x+=inte;
            rect_pelotita.y=(*i);
            if(rect_pelotita.x>=500)
            {
                cont++;
                rect_pelotita.x=0;
            }

        }

        if(pelotitas_x.empty())
        {
            rect_pelotita.x=0;
            inte=1;
            sumaInte=3;
            SDL_RenderCopy(renderer,game1_background,NULL,&rect_background);
       }//else if(cont>=25)
//        {
//            rect_pelotita.x=0;
//            inte=1;
//            sumaInte=3;
//            SDL_RenderCopy(renderer,game1_background,NULL,&rect_background);
//        }

        SDL_RenderPresent(renderer);

        SDL_Delay(delay);
    }
}
void loopmenu()
{
    while (true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return;
            }
            if(Event.type == SDL_KEYDOWN)
            {

                if(Event.key.keysym.sym == SDLK_RETURN)
                {
                    loopjuego();
                }

            }
        }
        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        SDL_RenderPresent(renderer);
    }
}
int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 500/*WIDTH*/, 320/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"PelotitasSDL/menu.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = 500;
    rect_background.h = 320;


    game_background = IMG_LoadTexture(renderer, "PelotitasSDL/background.png");
    game1_background = IMG_LoadTexture(renderer, "PelotitasSDL/background1.png");
    game2_background = IMG_LoadTexture(renderer, "PelotitasSDL/background2.png");
    pelotita_mala = IMG_LoadTexture(renderer, "PelotitasSDL/pelotita_mala.png");
    pelotita_buena = IMG_LoadTexture(renderer, "PelotitasSDL/pelotita_buena.png");
    SDL_QueryTexture(pelotita_buena,NULL, NULL, &rect_pelotita.w,&rect_pelotita.h);
    rect_pelotita.x=0;
    rect_pelotita.y=0;
    //Main Loop

    loopmenu();

    return 0;
}
//int main( int argc, char* args[]){
//list<int>mi_lista;
//mi_lista.push_back(1);
//mi_lista.push_back(2);
//mi_lista.push_back(3);
//
//
//
//for(list<int>::iterator i = mi_lista.begin(); i!=mi_lista.end();i++){
//  cout<<(*i)<<endl;
//}
//
//}
