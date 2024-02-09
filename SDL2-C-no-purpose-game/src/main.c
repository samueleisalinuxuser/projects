#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_NAME "GAME"
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 1200

#define GAME_WORLD_HEIGHT WINDOW_HEIGHT * 3
#define GAME_WORLD_WIDTH  WINDOW_WIDTH * 3
#define CELL_SIZE 50

#define MAX_ENTITIES 50

#define RANDOM_NUMBER(minimumNumber, maximumNumber) (int)((rand() % (maximumNumber - minimumNumber + 1)) + maximumNumber)

#define REFRESH SDL_RenderPresent(renderer)

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Color black, white, red, green, blue, yellow;

typedef enum {
    UP = SDLK_UP,
    DOWN = SDLK_DOWN,
    LEFT = SDLK_LEFT,
    RIGHT = SDLK_RIGHT,
    STAY = false
} directions;

typedef struct {
    SDL_Color color;
    SDL_Rect rect;
} entity;

directions direction;
entity entities[MAX_ENTITIES];
entity player;

void init();
void quit();
void handleEvents();
void clearWindow();
void initializeColors();

void initGame();
void moveInGame(directions direction);
void inGameEntitiesGenerator();
void renderGameOverlay();
void renderEntitiesOnScreen();
void game();

int main() {
    init();

    /* TESTING */ initGame();

    handleEvents();

    quit();

    return 0;
}

void init() {
    if(SDL_Init(SDL_INIT_EVERYTHING)) printf("SDL_Init(SDL_INIT_EVERYTHING) Error: %s", SDL_GetError());

    window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    /* DEBUG */ printf("[DEBUG] init() Created window and renderer\n");

    clearWindow();

    initializeColors();
}

void quit() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
}

void handleEvents() {
    bool quit = false;
    SDL_Event event;
    
    while(!quit) while(SDL_PollEvent(&event)) switch(event.type) {
        case SDL_QUIT:
            quit = true;

            /* DEBUG */ printf("[DEBUG] handleEvents() Quit\n");
            
            break;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
                case SDLK_UP:
                    direction = UP;

                    /* DEBUG */ printf("[DEBUG] handleEvents() Pressed: SDLK_UP\n");
                    
                    break;
                
                case SDLK_DOWN:
                    direction = DOWN;

                    /* DEBUG */ printf("[DEBUG] handleEvents() Pressed: SDLK_DOWN\n");
                    
                    break;
                
                case SDLK_LEFT:
                    direction = LEFT;

                    /* DEBUG */ printf("[DEBUG] handleEvents() Pressed: SDLK_LEFT\n");
                    
                    break;
                
                case SDLK_RIGHT:
                    direction = RIGHT;

                    /* DEBUG */ printf("[DEBUG] handleEvents() Pressed: SDLK_RIGHT\n");

                    break;

                default:
                    direction = STAY;
            }
            
            break;

        /* TESTING */ default: game();
    }
}

void clearWindow() {
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.g, black.a);
    SDL_RenderFillRect(renderer, NULL);

    REFRESH;
}

void initializeColors() {
    black.r = 0;
    black.g = 0;
    black.b = 0;
    black.a = 255;

    white.r = 255;
    white.g = 255;
    white.b = 255;
    white.a = 255;

    red.r = 255;
    red.g = 0;
    red.b = 0;
    red.a = 255;

    green.r = 0;
    green.g = 255;
    green.b = 0;
    green.a = 255;

    blue.r = 0;
    blue.g = 0;
    blue.b = 255;
    blue.a = 255;

    yellow.r = 255;
    yellow.g = 255;
    yellow.b = 0;
    yellow.a = 255;
}

void initGame() {
    player.color = yellow;

    player.rect.x = (int)(WINDOW_WIDTH / 2);
    player.rect.y = (int)(WINDOW_HEIGHT / 2);
    player.rect.w = 50;
    player.rect.h = 50;

    inGameEntitiesGenerator();
}

void inGameEntitiesGenerator() {
    for(int i = 0; i < MAX_ENTITIES; i++) {
        entities[i].color = blue;
        
        entities[i].rect.x = RANDOM_NUMBER(0, GAME_WORLD_WIDTH);
        entities[i].rect.y = RANDOM_NUMBER(0, GAME_WORLD_HEIGHT);
        entities[i].rect.w = 50;
        entities[i].rect.h = 50;

        /* DEBUG */ printf("[DEBUG] inGameEntitiesGenerator() Created Entity: %d of %d, x = %d, y = %d\n", i + 1, MAX_ENTITIES, entities[i].rect.x, entities[i].rect.y);
    }
}

void moveInGame(directions direction) {
    switch(direction) {
        case UP:
            printf("[DEBUG] moveInGame() Moving: UP\n");

            break;
        
        case DOWN:
            printf("[DEBUG] moveInGame() Moving: DOWN\n");

            break;

        case LEFT:
            printf("[DEBUG] moveInGame() Moving: LEFT\n");

            break;

        case RIGHT:
            printf("[DEBUG] moveInGame() Moving: RIGHT\n");

            break;
    }
}

void renderGameOverlay() {
    SDL_SetRenderDrawColor(renderer, player.color.r, player.color.g, player.color.b, player.color.a);
    SDL_RenderFillRect(renderer, &player.rect);
}

void renderEntitiesOnScreen() {
    for(int i = 0; i < MAX_ENTITIES; i++) {
        if(true) { // Add check to not draw entities that are not on the screen
            SDL_Rect partOfTheEntityToDraw;

            partOfTheEntityToDraw.x = entities[i].rect.x;
            partOfTheEntityToDraw.y = entities[i].rect.y;
            partOfTheEntityToDraw.w = entities[i].rect.w;
            partOfTheEntityToDraw.h = entities[i].rect.h;

            SDL_SetRenderDrawColor(renderer, entities[i].color.r, entities[i].color.g, entities[i].color.b, entities[i].color.a);
            SDL_RenderFillRect(renderer, &partOfTheEntityToDraw);
        }
    }
}

void game() {
    moveInGame(direction);

    renderEntitiesOnScreen();

    renderGameOverlay();

    REFRESH;
}
