/**
 * DoubleBufferサンプル
 */

#include <iostream>

class Actor
{
  public:
    Actor(const char *name)
        : currentSlapped_(false),
          nextSlapped_(false),
          name_(name) {}
    virtual ~Actor() {}
    virtual void update() = 0;

    void slap()
    {
        nextSlapped_ = true;
    }
    bool wasSlapped()
    {
        return currentSlapped_;
    }
    void swap()
    {
        // バッファを入れ替え
        currentSlapped_ = nextSlapped_;
        // 新しい「次」バッファをクリアする
        nextSlapped_ = false;
    }

    const char *getName()
    {
        return name_;
    }

  private:
    bool currentSlapped_;
    bool nextSlapped_;
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
        }
        for (int i = 0; i < NUM_ACTORS; ++i)
        {
            std::cout << "Actor[" << i << "] swap." << std::endl;
            actors_[i]->swap();
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
    for (int i = 0; i < 5; i++) {
        std::cout << "frame:" << i << " ----------" << std::endl;
        stage.update();
    }
}