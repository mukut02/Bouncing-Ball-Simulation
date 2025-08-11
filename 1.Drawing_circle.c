#include<stdio.h>
#include<SDL2/SDL.h>
#define WIDTH 900
#define HEIGHT 600
#define WHITE 0xffffff

struct Circle{
    int x;
    int y;
    int radius;
};

void FillCircle(SDL_Surface* surface,struct Circle circle){
    int low_x=circle.x - circle.radius;
    int high_x=circle.x + circle.radius;
    int low_y=circle.y - circle.radius;
    int high_y=circle.y + circle.radius;
    
    int sq_radius=circle.radius*circle.radius;

    for(int x=low_x; x<high_x; ++x){
        for(int y=low_y;y<high_y; ++y){
            // is coordinate within circle??
            int d=(x-circle.x)*(x-circle.x) + (y-circle.y)*(y-circle.y);
            if(sq_radius >= d){
                SDL_Rect pixel = (SDL_Rect){x,y,1,1};
                SDL_FillRect(surface,&pixel,WHITE);
            }
        }
    }
}

int main(){
    printf("Hello Bouncy Ball\n");
    SDL_Init(SDL_INIT_VIDEO); // intiliased video
    SDL_Window* window=SDL_CreateWindow("Bouncy Ball", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0 ); // window initialised
    SDL_Surface* surface = SDL_GetWindowSurface(window); // its the place where we can i/o our stuff
    
    struct Circle circle=(struct Circle) {200,200,100};
    
    FillCircle(surface, circle);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(10000);
    
}
