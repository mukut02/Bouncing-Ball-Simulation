#include<stdio.h>
#include<SDL2/SDL.h>
#define WIDTH 900
#define HEIGHT 600
#define WHITE 0xffffff
#define BLACK 0x000000
#define A_GRAVITY 0.2

struct Circle{
    double x;
    double y;
    double radius;
    double v_x;
    double v_y;
};

void FillCircle(SDL_Surface* surface,struct Circle circle){
    double low_x=circle.x - circle.radius;
    double high_x=circle.x + circle.radius;
    double low_y=circle.y - circle.radius;
    double high_y=circle.y + circle.radius;
    
    double sq_radius=circle.radius*circle.radius;

    for(double x=low_x; x<high_x; ++x){
        for(double y=low_y;y<high_y; ++y){
            // is coordinate within circle??
            double d=(x-circle.x)*(x-circle.x) + (y-circle.y)*(y-circle.y);
            if(sq_radius >= d){
                SDL_Rect pixel = (SDL_Rect){(int)x,(int)y,1,1};
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
    // ball exiting the screen
    
    // right boundary
    if((circle->x + circle->radius) > WIDTH ){
        circle->x = WIDTH- circle->radius;
        circle->v_x = - circle->v_x; // reverse velocity direction
    }

    // left boundary
    if((circle->x - circle->radius) < 0){
        circle->x = circle->radius;
        circle->v_x = - circle->v_x; // reverse velocity direction
    }
    
    // down boundary
    if((circle->y + circle->radius) > HEIGHT){
        circle->y = HEIGHT- circle->radius;
        circle-> v_y = -circle->v_y; // reverse velocity direction
    }

    // up boundary

    if((circle->y - circle->radius) < 0){
        circle->y = circle->radius;
        circle-> v_y = -circle->v_y; // reverse velocity direction
    }
}

int main(){
    printf("Hello Bouncy Ball\n");
    SDL_Init(SDL_INIT_VIDEO); // intiliased video
    SDL_Window* window=SDL_CreateWindow("Bouncy Ball", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0 );
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    
    struct Circle circle=(struct Circle) {100,100,100,5,0};

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
    SDL_Quit();
}
