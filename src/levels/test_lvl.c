#include "game.h"
#include "maps.h"

SDL_Renderer *renderer = NULL;

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

  /*HERO CREATION*/
  t_mainHero hero;
  create_hero(renderer, &hero, 400, 350);

  /*KNIGHT TEST*/
  t_enemy knights[3];
  for(int i = 0, j = 4; i < 3; i++, j++)
      create_knight(renderer, &knights[i], 5 * 64, j * 64);
/**/
  int scene_counter = 0;
  int left = 0;
  int right = 0;
  int up = 0;
  int down = 0;

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
      hero.HeroA.filepath = "../resource/characters/main_hero/idle/hero_idle.png";
      hero.HeroA.totalFrames = 3;
      hero.HeroA.delayPerFrame = 255;
      if(wasLeft)
        flip = true;
    }

    if (left && up)
    {
      hero.HeroA.filepath = "../resource/characters/main_hero/run/hero_run.png";
      hero.HeroA.totalFrames = 6;
      hero.HeroA.delayPerFrame = 100;
      hero.velX = -300;
      hero.velY = -300;
      HeroMove(dir, hero.velX, hero.velY, &hero.windowRect);
      flip = true;
    }
    else if (left && down)
    {
      hero.HeroA.filepath = "../resource/characters/main_hero/run/hero_run.png";
      hero.HeroA.totalFrames = 6;
      hero.HeroA.delayPerFrame = 100;
      hero.velX = -300;
      hero.velY = 300;
      HeroMove(dir, hero.velX, hero.velY, &hero.windowRect);
      flip = true;
    }
    else if (right && up)
    {
      hero.HeroA.filepath = "../resource/characters/main_hero/run/hero_run.png";
      hero.HeroA.totalFrames = 6;
      hero.HeroA.delayPerFrame = 100;
      hero.velX = 300;
      hero.velY = -300;
      HeroMove(dir, hero.velX, hero.velY, &hero.windowRect);
    }
    else if (right && down)
    {
      hero.HeroA.filepath = "../resource/characters/main_hero/run/hero_run.png";
      hero.HeroA.totalFrames = 6;
      hero.HeroA.delayPerFrame = 100;
      hero.velX = 300;
      hero.velY = 300;
      HeroMove(dir, hero.velX, hero.velY, &hero.windowRect);
    }
    else if (left)
    {
      hero.HeroA.filepath = "../resource/characters/main_hero/run/hero_run.png";
      hero.HeroA.totalFrames = 6;
      hero.HeroA.delayPerFrame = 100;
      hero.velX = -300;
      hero.velY = 0;
      HeroMove(dir, hero.velX, hero.velY, &hero.windowRect);
      flip = true;
    }
    else if (right)
    {
      hero.HeroA.filepath = "../resource/characters/main_hero/run/hero_run.png";
      hero.HeroA.totalFrames = 6;
      hero.HeroA.delayPerFrame = 100;
      hero.velX = 300;
      hero.velY = 0;
      HeroMove(dir, hero.velX, hero.velY, &hero.windowRect);
    }
    else if (up)
    {
      hero.HeroA.filepath = "../resource/characters/main_hero/run/hero_run_up.png";
      hero.HeroA.totalFrames = 4;
      hero.HeroA.delayPerFrame = 100;
      hero.velX = 0;
      hero.velY = -300;
      HeroMove(dir, hero.velX, hero.velY, &hero.windowRect);
    }
    else if (down)
    {
      hero.HeroA.filepath = "../resource/characters/main_hero/run/hero_run_down.png";
      hero.HeroA.totalFrames = 4;
      hero.HeroA.delayPerFrame = 100;
      hero.velX = 0;
      hero.velY = 300;
      HeroMove(dir, hero.velX, hero.velY, &hero.windowRect);
    }

    if (up || down || left || right) {
      if (!Mix_Playing(0))
        Mix_PlayChannel(0, stepSound, 0);
    }

//KNIGHT BEHAVIOUR
    for(int i = 0; i < 3; i++)
        knight_behaviour(&hero, &knights[i], text, renderer);
    //END
      hero.HeroT = Animation(&hero.HeroA);

    camera.x = windowRect.x - 800;
    camera.y = windowRect.y - 400;

    if(hero_collision_detect(text, hero))
    {
      HeroMove(dir, -hero.velX, -hero.velY, &hero.windowRect);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    RenderTextureByInput(Background, renderer, 0, 0, 1600, 800);
    DrawMap(renderer, &text);
    //Copying the texture on to the window using
    //renderer, texture rectangle and window rectangle
    hero_render(renderer, &hero, flip);
//    KNIGHT RENDER
      for(int i = 0; i < 3; i++)
          knight_render(renderer, &knights[i], false);

    SDL_Delay(1000/60);
    SDL_RenderPresent(renderer);
//    SDL_Log("Scene: %d\n\n", scene_counter++);

  }
}