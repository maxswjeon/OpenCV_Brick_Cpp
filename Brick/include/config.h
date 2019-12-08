#pragma once
//Logger Config
#define LOG_LEVEL LogLevel::DEBG
#define LOG_COLOR 1
#define LOG_COLOR_ARRAY {37, 34, 32, 33, 31}

//Game Config
#define GAME_TITLE "Brick on Hand"
#define GAME_WIDTH 1280
#define GAME_HEIGHT 720
#define GAME_RENDERER 1 //OpenGL is Better than DirectX (Better Pipeline)
#define GAME_RENDERER_FLAGS (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)