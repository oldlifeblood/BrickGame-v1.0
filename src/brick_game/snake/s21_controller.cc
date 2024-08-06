#include "s21_controller.h"

namespace s21 {
void s21_controller::userInput(UserAction_t action, bool *hold) {
  switch (action) {
    case Left:
      if (direction == Left)
        *hold = true;
      else if (direction != Right) {
        direction = Left;
      }
      break;
    case Right:
      if (direction == Right)
        *hold = true;
      else if (direction != Left) {
        direction = Right;
      }
      break;
    case Up:
      if (direction == Up)
        *hold = true;
      else if (direction != Down) {
        direction = Up;
      }
    case Down:
      if (direction == Down)
        *hold = true;
      else if (direction != Up) {
        direction = Down;
      }
      break;
    case Pause:
      if (pause == 0)
        pause = 1;
      else
        pause = 0;
      break;
    default:
      break;
  }
}
}  // namespace s21
