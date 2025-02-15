#ifndef GAME_H
#define GAME_H

#include <random>
#include <string>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game
{
public:
  Game(std::size_t grid_width, std::size_t grid_height, std::string name, std::string name2);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  std::vector<int> GetScore() const;
  std::vector<int> GetSize() const;

private:
  Snake snake;
  Snake snake2;
  SDL_Point food;
  SDL_Point food2;
  std::string name;
  std::string name2;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int score2{0};

  void PlaceFood();
  void Update();
};

#endif