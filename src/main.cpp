#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <string>

int main()
{
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  std::string name, name2;
  std::cout << "Enter name for Player_1: \n";
  std::cin >> name;
  std::cout << "Enter name for Player_2: \n";
  std::cin >> name2;
  Game game(kGridWidth, kGridHeight, name, name2);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  int score = game.GetScore()[0], score2 = game.GetScore()[1];
  std::cout << "Score_1: " << score << "\n"
            << "Score_2: " << score2 << "\n";
  // std::cout << "Size: " << game.GetSize() << "\n";
  if (score > score2)
  {
    std::cout << "The winner is: Player_1!"
              << "\n";
  }
  else if (score < score2)
  {
    std::cout << "The winner is: Player_2!"
              << "\n";
  }
  else
  {
    std::cout << "Player_1 and Player_2 score equals."
              << "\n";
  }

  return 0;
}