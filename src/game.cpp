#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      snake2(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, snake2);
    Update();
    renderer.Render(snake, snake2, food, food2);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, score2, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !snake2.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      break;;
    }
  }

  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !snake2.SnakeCell(x, y)) {
      food2.x = x;
      food2.y = y;
      break;;
    }
  }
}

void Game::Update() {
  if (!snake.alive || !snake2.alive) return;

  snake.Update();
  snake2.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  bool food_1 = true, food_2 = true;
  if (food.x == new_x && food.y == new_y) {
    food_1 = false;
    score++;
    // PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  if (food2.x == new_x && food2.y == new_y) {
    food_2 = false;
    score++;
    snake.GrowBody();
    snake.speed += 0.02;
  }

  int new_x2 = static_cast<int>(snake2.head_x);
  int new_y2 = static_cast<int>(snake2.head_y);

  // Check if there's food over here
  if (food.x == new_x2 && food.y == new_y2 && food_1) {
    food_1 = false;
    score2++;
    // PlaceFood();
    // Grow snake and increase speed.
    snake2.GrowBody();
    snake2.speed += 0.02;
  }

  if (food2.x == new_x2 && food2.y == new_y2 && food_2) {
    food_2 = false;
    score2++;
    // PlaceFood();
    // Grow snake and increase speed.
    snake2.GrowBody();
    snake2.speed += 0.02;
  }
  if (!food_1 && !food_2){
    PlaceFood();
  }
}

std::vector<int> Game::GetScore() const { return {score, score2}; }
std::vector<int> Game::GetSize() const { return {snake.size, snake2.size}; }