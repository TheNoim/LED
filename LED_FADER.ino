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
      cout << "R" << this->r << "G" << this->g << "B" << this->b << endl; 
      return;
    }
    void ledinit(int p[]) {
      this->r = random(1, 255);
      this->g = random(1, 255);
      this->b = random(1, 255);
      for (int i = 0; i < 3; i++) {
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
      cout << "Pin0=" << pins[0] << endl;
      cout << "Pin1=" << pins[1] << endl;
      cout << "Pin2=" << pins[2] << endl;
      cout << "Pin3=" << pins[3] << endl;
      return;
    }
    void redefine(int rr, int gg, int bb) {
      r = rr;
      g = gg;
      b = bb;
      return;
    }
    /*
    ~LED() { delete [] pins, r, g, b, task, taskgoal; }
    LED &operator=(LED const& other) 
    {
        LED copy(other);
        swap(*this, copy);
        return *this;
    }

    LED(LED&& that) noexcept
        : pins(nullptr)
        , r(0)
        , g(0)
        , b(0)
        , task(0)
        , taskgoal(0)
    {
        swap(*this, that);
    }

    LED& operator=(LED&& that) noexcept
    {
        swap(*this, that);
        return *this;
    }

    friend void swap(LED& lhs, LED& rhs) noexcept
    {
        std::swap(lhs.pins, rhs.pins);
        std::swap(lhs.r, rhs.r);
        std::swap(lhs.g, rhs.g);
        std::swap(lhs.b, rhs.b);
        std::swap(lhs.task, rhs.task);
        std::swap(lhs.taskgoal, rhs.taskgoal);
    }
    */
};
//std::vector< LED >leds;
LED ll1;

void setup() {
  Serial.begin(9600);
  LED l1;
  int l1pins[4] = {11, 9, 8, 10};
  l1.ledinit(l1pins);
  ll1 = l1;
  //leds.push_back(std::move(l1));
}

void loop() {
  /*
  for (LED &l : leds) {
    l.runTask();
  }*/
  ll1.runTask();
  delay(30);
}
