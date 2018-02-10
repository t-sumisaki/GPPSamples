class Sprite
{
};
class Volume
{
};
class World
{
  public:
    void resolveCollision(Volume volume, int x, int y, int velocity);
};
class Graphics
{
  public:
    void draw(Sprite *sprite, int x, int y);
};
class Controller
{
  public:
    static int getJoystickDirection();
};

const int DIR_LEFT = -1;
const int DIR_RIGHT = 1;