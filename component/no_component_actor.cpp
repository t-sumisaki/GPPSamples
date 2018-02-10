#include "common_keyword.h"


// Componentパターンを使わない場合の実装
class Bjorn
{
  public:
    Bjorn() : velocity_(0), x_(0), y_(0) {}

    void update(World &world, Graphics &graphics);

  private:
    static const int WALK_ACCELEARATION = 1;

    int velocity_;
    int x_, y_;

    Volume volume_;
    Sprite spriteStand_;
    Sprite spriteWalkLeft_;
    Sprite spriteWalkRight_;
};

void Bjorn::update(World &world, Graphics &graphics)
{
    switch (Controller::getJoystickDirection())
    {
    case DIR_LEFT:
        velocity_ -= WALK_ACCELEARATION;
        break;
    case DIR_RIGHT:
        velocity_ += WALK_ACCELEARATION;
        break;
    }

    x_ += velocity_;
    world.resolveCollision(volume_, x_, y_, velocity_);

    Sprite* sprite = &spriteStand_;
    if (velocity_ < 0) {
        sprite = &spriteWalkLeft_;
    } else if (velocity_ > 0) {
        sprite = &spriteWalkRight_;
    }

    graphics.draw(sprite, x_, y_);
}
