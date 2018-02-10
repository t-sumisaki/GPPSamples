#include "common_keyword.h"

class GameObject;

class InputComponent
{
  public:
    virtual ~InputComponent() {}
    virtual void update(GameObject &object) = 0;
};
class PhysicsComponent
{
  public:
    virtual ~PhysicsComponent() {}
    virtual void update(GameObject &object, World &world) = 0;
};
class GraphicsComponent
{
  public:
    virtual ~GraphicsComponent() {}
    virtual void update(GameObject &object, Graphics &graphics) = 0;
};

class GameObject
{
  public:
    int velocity;
    int x, y;

    GameObject(InputComponent *input, PhysicsComponent *physics, GraphicsComponent *graphics)
        : input_(input), physics_(physics), graphics_(graphics) {}

    void update(World &world, Graphics &graphics)
    {
        input_->update(*this);
        physics_->update(*this, world);
        graphics_->update(*this, graphics);
    }

  private:
    InputComponent *input_;
    PhysicsComponent *physics_;
    GraphicsComponent *graphics_;
};

/**
 * 入力処理コンポーネント
 **/
class PlayerInputComponent : public InputComponent
{
  public:
    virtual void update(GameObject &object) override
    {
        switch (Controller::getJoystickDirection())
        {
        case DIR_LEFT:
            object.velocity -= WALK_ACCELEARATION;
            break;
        case DIR_RIGHT:
            object.velocity += WALK_ACCELEARATION;
            break;
        }
    }

  private:
    static const int WALK_ACCELEARATION = 1;
};
/**
 * 物理コンポーネント
 * */
class PlayerPhysicsComponent
{
  public:
    void update(GameObject &object, World &world)
    {
        object.x += object.velocity;
        world.resolveCollision(volume_, object.x, object.y, object.velocity);
    }

  private:
    Volume volume_;
};

/**
 * グラフィックコンポーネント
 * */
class PlayerGraphicsComponent
{
  public:
    void update(GameObject &object, Graphics &graphics)
    {
        Sprite *sprite = &spriteStand_;
        if (object.velocity < 0)
        {
            sprite = &spriteWalkLeft_;
        }
        else if (object.velocity > 0)
        {
            sprite = &spriteWalkRight_;
        }

        graphics.draw(sprite, object.x, object.y);
    }

  private:
    Sprite spriteStand_;
    Sprite spriteWalkLeft_;
    Sprite spriteWalkRight_;
}