/**
 * DoubleBufferサンプル
 */

#include <iostream>

class Actor
{
  public:
    Actor(const char *name) : slapped_(false), name_(name) {}
    virtual ~Actor() {}
    virtual void update() = 0;
    virtual void reset()
    {
        slapped_ = false;
    }
    virtual void slap()
    {
        slapped_ = true;
    }
    virtual bool wasSlapped()
    {
        return slapped_;
    }

    const char *getName()
    {
        return name_;
    }

  private:
    bool slapped_;
    const char *name_;
};

class Comedian : public Actor
{
  public:
    Comedian(const char *name) : Actor(name) {}
    void face(Actor *actor)
    {
        facing_ = actor;
    }
    virtual void update() override
    {
        if (wasSlapped())
        {
            std::cout << getName() << " is slapped." << std::endl;
            std::cout << "clap back to " << facing_->getName() << std::endl;
            facing_->slap();
        }
        else
        {
            std::cout << getName() << " is not slapped." << std::endl;
        }
    }

  private:
    Actor *facing_;
};

class Stage
{
  public:
    void add(Actor *actor, int index)
    {
        actors_[index] = actor;
    }
    void update()
    {
        for (int i = 0; i < NUM_ACTORS; ++i)
        {
            std::cout << "Actor[" << i << "] update." << std::endl;
            actors_[i]->update();
            actors_[i]->reset();
        }

        std::cout << "update completed." << std::endl;
    }

  private:
    static const int NUM_ACTORS = 3;
    Actor *actors_[NUM_ACTORS];
};

int main()
{

    Stage stage;

    Comedian *harry = new Comedian("harry");
    Comedian *baldy = new Comedian("baldy");
    Comedian *chump = new Comedian("chump");

    harry->face(baldy);
    baldy->face(chump);
    chump->face(harry);

    stage.add(harry, 0);
    stage.add(baldy, 1);
    stage.add(chump, 2);

    // 逆周り配置
    /*
    stage.add(harry, 2);
    stage.add(baldy, 1);
    stage.add(chump, 0);
    */

    harry->slap();
    stage.update();
}