#include "game.h"
#include "minilib.h"
#include "maps.h"

SDL_Renderer *renderer = NULL;

int lvl1[20][25] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 12, 2, 2, 2, 2, 2, 11, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 3, -1, -1, -1, -1, -1, 7, 2, 2, 2, 2, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 3, 0, 0, 0, 0, 0, -2, -1, -1, -1, -1, -1, -1, -1, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 3, 0, 0, 0, 0, 0, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 6, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -3, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

};


void Level2Loop(int wW, int wH)
{


  /* Music */
  Mix_Chunk *stepSound = Mix_LoadWAV("../resource/music/hero_sound/steps.mp3");
  if (!stepSound)
    SDL_Log("%s", Mix_GetError());


  SDL_Rect camera = {0, 0, 1600, 800};
  /* Base Variables */
  SDL_Window *window = CreateWindow(1600, 800);
  renderer = CreateRenderer(window);

  SDL_Event event;
  bool quit = false;

  /* Textures */
  SDL_Texture *Background = LoadTexture("../resource/background/background_1.png", renderer);
  TextureMap text = Map(renderer, lvl1);

  /* Make Rectangles */

  //'windowRect' defines the dimensions of the rendering sprite on window
  SDL_Rect windowRect = {.x = 0,.y = 0, .w = 0, .h = 0};

  //'textureRect' defines the dimensions of the rendering sprite on texture
  SDL_Rect textureRect = {.x = 0, .y = 0, .w = 0, .h = 0};

  int totalFrames = 6;
  int delayPerFrame = 157.835782842584534950903505000099999990999090905949;
  int anim = false;

  SDL_Texture *CurrentHeroT;
  t_animation CurrentHeroA =
      {
          .windowsRect = &windowRect, .textureRect = &textureRect,
          .renderer = renderer, .filepath = "../resource/characters/main_hero/idle/hero_idle.png",
          .delayPerFrame = 255, .totalFrames = 3
      };

  int scene_counter = 0;
  int left = 0;
  int right = 0;
  int up = 0;
  int down = 0;

  int x_vel = 0;
  int y_vel = 0;

  int dir = 0;


  int flip = false;


  while (!quit)
  {
    anim = false;
    int wasLeft = false;

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT) quit = true;

      if (event.type == SDL_KEYDOWN)
      {
        if (event.key.keysym.scancode == SDL_SCANCODE_W)
        {
          up = 1;
          dir = 3;
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_S)
        {
          down = 1;
          dir = 4;
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_D)
        {
          flip = false;
          right = 1;
          dir = 2;
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_A)
        {
          left = 1;
          dir = 1;
        }
      }
      else if (event.type == SDL_KEYUP)
      {
        if (event.key.keysym.scancode == SDL_SCANCODE_D)
        {
          wasLeft = false;
          right = 0;
          dir = 0;
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_A)
        {
          flip = false;
          wasLeft = true;
          left = 0;
          dir = 0;
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_W)
        {
          up = 0;
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_S)
        {
          down = 0;
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // TODO Fix multiply touch W/A or S/D
    if (!left && !right && !down && !up)
    {
      if (Mix_Playing(0))
      {
        SDL_Log("Stop Music");
        Mix_HaltChannel(0);
      }
      CurrentHeroA.filepath = "../resource/characters/main_hero/idle/hero_idle.png";
      CurrentHeroA.totalFrames = 3;
      CurrentHeroA.delayPerFrame = 255;
      if(wasLeft)
        flip = true;
    }

    if (left && up)
    {
      CurrentHeroA.filepath = "../resource/characters/main_hero/run/hero_run.png";
      CurrentHeroA.totalFrames = 6;
      CurrentHeroA.delayPerFrame = 100;
      x_vel = -300;
      y_vel = -300;
      HeroMove(dir, x_vel, y_vel, &windowRect);
      flip = true;
    }
    else if (left && down)
    {
      CurrentHeroA.filepath = "../resource/characters/main_hero/run/hero_run.png";
      CurrentHeroA.totalFrames = 6;
      CurrentHeroA.delayPerFrame = 100;
      x_vel = -300;
      y_vel = 300;
      HeroMove(dir, x_vel, y_vel, &windowRect);
      flip = true;
    }
    else if (right && up)
    {
      CurrentHeroA.filepath = "../resource/characters/main_hero/run/hero_run.png";
      CurrentHeroA.totalFrames = 6;
      CurrentHeroA.delayPerFrame = 100;
      x_vel = 300;
      y_vel = -300;
      HeroMove(dir, x_vel, y_vel, &windowRect);
    }
    else if (right && down)
    {
      CurrentHeroA.filepath = "../resource/characters/main_hero/run/hero_run.png";
      CurrentHeroA.totalFrames = 6;
      CurrentHeroA.delayPerFrame = 100;
      x_vel = 300;
      y_vel = 300;
      HeroMove(dir, x_vel, y_vel, &windowRect);
    }
    else if (left)
    {
      CurrentHeroA.filepath = "../resource/characters/main_hero/run/hero_run.png";
      CurrentHeroA.totalFrames = 6;
      CurrentHeroA.delayPerFrame = 100;
      x_vel = -300;
      y_vel = 0;
      HeroMove(dir, x_vel, y_vel, &windowRect);
      flip = true;
    }
    else if (right)
    {
      CurrentHeroA.filepath = "../resource/characters/main_hero/run/hero_run.png";
      CurrentHeroA.totalFrames = 6;
      CurrentHeroA.delayPerFrame = 100;
      x_vel = 300;
      y_vel = 0;
      HeroMove(dir, x_vel, y_vel, &windowRect);
    }
    else if (up)
    {
      CurrentHeroA.filepath = "../resource/characters/main_hero/run/hero_run_up.png";
      CurrentHeroA.totalFrames = 4;
      CurrentHeroA.delayPerFrame = 100;
      x_vel = 0;
      y_vel = -300;
      HeroMove(dir, x_vel, y_vel, &windowRect);
    }
    else if (down)
    {
      CurrentHeroA.filepath = "../resource/characters/main_hero/run/hero_run_down.png";
      CurrentHeroA.totalFrames = 4;
      CurrentHeroA.delayPerFrame = 100;
      x_vel = 0;
      y_vel = 300;
      HeroMove(dir, x_vel, y_vel, &windowRect);
    }

    if (up || down || left || right) {
      if (!Mix_Playing(0))
        Mix_PlayChannel(0, stepSound, 0);
    }

    CurrentHeroT = Animation(&CurrentHeroA);

    camera.x = windowRect.x - 800;
    camera.y = windowRect.y - 400;

    if(text.map[(windowRect.y + windowRect.h/2)/64][(windowRect.x + windowRect.w/3)/64] > 0
       || text.map[(windowRect.y + windowRect.h/3)/64][(windowRect.x + windowRect.w/2)/64] > 0
       || text.map[(windowRect.y + windowRect.h*2/3)/64][(windowRect.x + windowRect.w/2)/64] > 0
       || text.map[(windowRect.y + windowRect.h/2)/64][(windowRect.x + windowRect.w*2/3)/64] >0)

    {
      HeroMove(dir, -x_vel, -y_vel, &windowRect);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    RenderTextureByInput(Background, renderer, 0, 0, 1600, 800);
    DrawMap(renderer, &text);
    //Copying the texture on to the window using
    //renderer, texture rectangle and window rectangle

    if (!flip)
      SDL_RenderCopy(renderer, CurrentHeroT, &textureRect, &windowRect);
    else
      SDL_RenderCopyEx(renderer, CurrentHeroT, &textureRect, &windowRect, 360, NULL, SDL_FLIP_HORIZONTAL);

    SDL_Delay(1000/60);
    SDL_RenderPresent(renderer);
    SDL_Log("Scene: %d\n\n", scene_counter++);

  }
}