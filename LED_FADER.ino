#include <StandardCplusplus.h>
#include <vector>
#include <serstream>

using namespace std;
namespace std
{
ohserialstream cout(Serial);
}
//LED RGB color fade 1.0 by Noim


bool randomBool() {
  return rand() % 2 == 1;
}
class LED {
    int pins[4];
    int r;
    int g;
    int b;
    int task;
    int taskgoal;
  public:
    void newTask() {
      int t = random(1, 4);
      this->task = t;
      return;
    }
    void newGoal() {
      int t = random(1, 256);
      this->taskgoal = t;
      return;
    }
    boolean taskFinished() {
      int current;
      switch (task) {
        case 1:
          current = this->r;
          break;
        case 2:
          current = this->g;
          break;
        case 3:
          current = this->b;
          break;
      }
      if (current == taskgoal) {
        return true;
      } else {
        return false;
      }
      return false;
    }
    void runTask() {
      if (taskFinished()) {
        newTask();
        newGoal();
      }
      int current;
      switch (task) {
        case 1:
          current = this->r;
          break;
        case 2:
          current = this->g;
          break;
        case 3:
          current = this->b;
          break;
      }
      if (current < taskgoal) {
        switch (task) {
          case 1:
            this->redefine(this->r + 1, this->g, this->b);
            break;
          case 2:
            this->redefine(this->g, this->g + 1, this->b);
            break;
          case 3:
            this->redefine(this->r, this->g, this->b + 1);
            break;
        }
      } else if (current > taskgoal) {
        switch (task) {
          case 1:
            this->redefine(this->r - 1, this->g, this->b);
            break;
          case 2:
            this->redefine(this->r, this->g - 1, this->b);
            break;
          case 3:
            this->redefine(this->r, this->g, this->b - 1);
            break;
        }
      }
      analogWrite(pins[0], this->r);
      analogWrite(pins[1], this->g);
      analogWrite(pins[2], this->b);
      return;
    }
    void ledinit(int p[]) {
      this->r = random(1, 255);
      this->g = random(1, 255);
      this->b = random(1, 255);
      for (int i = 1; i < 3; i++) {
        pins[i] = p[i];
        pinMode(pins[i], OUTPUT);
      }
      pins[3] = p[3];
      analogWrite(pins[0], this->r);
      analogWrite(pins[1], this->g);
      analogWrite(pins[2], this->b);
      analogWrite(pins[3], LOW);
      newTask();
      newGoal();
      runTask();
      return;
    }
    void redefine(int rr, int gg, int bb) {
      r = rr;
      g = gg;
      b = bb;
      return;
    }
};
std::vector< LED >leds;

void setup() {
  Serial.begin(9600);
  LED l1;
  int l1pins[4] = {11, 9, 8, 10};
  l1.ledinit(l1pins);
  leds.push_back(l1);
}

void loop() {
  for (LED &l : leds) {
    l.runTask();
  }
  delay(100);
}
