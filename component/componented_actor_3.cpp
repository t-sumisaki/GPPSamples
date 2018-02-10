#include "common_keyword.h"

class GameObject;

class Component
{
  public:
    virtual ~Component() {}
    virtual void receive(int message) = 0;
};

class GameObject
{
  public:
    void send(int message)
    {
        for (int i = 0; i < MAX_COMPONENTS; ++i)
        {
            if (components_[i] != nullptr)
            {
                components_[i]->receive(message);
            }
        }
    }

  private:
    static const int MAX_COMPONENTS = 10;
    Component *components_[MAX_COMPONENTS];
};

