#include "common_keyword.h"

class InputComponent;
class PhysicsComponent;
class GraphicsComponent;

class Bjorn
{
  public:
    int velocity;
    int x, y;

    void update(World &world, Graphics &graphics)
    {
        input_.update(*this);
        physics_.update(*this, world);
        graphics_.update(*this, graphics);
    }

  private:
    InputComponent input_;
    PhysicsComponent physics_;
    GraphicsComponent graphics_;
};

/**
 * 入力処理コンポーネント
 **/
class InputComponent
{
  public:
    void update(Bjorn &bjorn)
    {
        switch (Controller::getJoystickDirection())
        {
        case DIR_LEFT:
            bjorn.velocity -= WALK_ACCELEARATION;
            break;
        case DIR_RIGHT:
            bjorn.velocity += WALK_ACCELEARATION;
            break;
        }
    }

  private:
    static const int WALK_ACCELEARATION = 1;
};
/**
 * 物理コンポーネント
 * */
class PhysicsComponent
{
  public:
    void update(Bjorn &bjorn, World &world)
    {
        bjorn.x += bjorn.velocity;
        world.resolveCollision(volume_, bjorn.x, bjorn.y, bjorn.velocity);
    }

  private:
    Volume volume_;
};

/**
 * グラフィックコンポーネント
 * */
class GraphicsComponent
{
  public:
    void update(Bjorn &bjorn, Graphics &graphics)
    {
        Sprite *sprite = &spriteStand_;
        if (bjorn.velocity < 0)
        {
            sprite = &spriteWalkLeft_;
        }
        else if (bjorn.velocity > 0)
        {
            sprite = &spriteWalkRight_;
        }

        graphics.draw(sprite, bjorn.x, bjorn.y);
    }

  private:
    Sprite spriteStand_;
    Sprite spriteWalkLeft_;
    Sprite spriteWalkRight_;
}