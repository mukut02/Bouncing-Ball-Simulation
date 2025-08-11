#include<stdio.h>
#include<SDL2/SDL.h>
#define WIDTH 900
#define HEIGHT 600
#define WHITE 0xffffff
#define BLACK 0x000000
#define A_GRAVITY 1

struct Circle{
    int x;
    int y;
    int radius;
    int v_x;
    int v_y;
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

void step(struct Circle* circle){
    // how do we calculate the new position
    circle->x = circle->x + circle->v_x;
    circle->y = circle->y + circle->v_y + A_GRAVITY;
    circle->v_y+=A_GRAVITY;
}

int main(){
    printf("Hello Bouncy Ball\n");
    SDL_Init(SDL_INIT_VIDEO); // intiliased video
    SDL_Window* window=SDL_CreateWindow("Bouncy Ball", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0 );
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    
    struct Circle circle=(struct Circle) {100,100,100,1,0};

    int simulation_running=1;
    SDL_Event event;

    SDL_Rect erase_rect = (SDL_Rect){0,0,WIDTH,HEIGHT};
    while(simulation_running){
         while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                simulation_running=0;
            }
         }
         //Delete Prev circle,then Draw the circle
         SDL_FillRect(surface,&erase_rect, BLACK);
         FillCircle(surface, circle);
         step(&circle);
         SDL_UpdateWindowSurface(window);
         SDL_Delay(30);

    }
    SDL_Delay(5000);
    
}
