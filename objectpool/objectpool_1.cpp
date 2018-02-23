/**
 * ObjectPoolのサンプル
 * 
 * 
 * 
 **/


class Particle
{
  public:
    Particle() : framesLeft_(0) {}

    void init(double x, double y, double xVel, double yVel, int lifetime)
    {
        // initではパーティクルを使用状態に初期化する
        x_ = x;
        y_ = y;
        xVel_ = xVel;
        yVel_ = yVel;
        framesLeft_ = lifetime;
    }

    void animate()
    {
        if (!inUse())
            return;

        framesLeft_--;
        x_ += xVel_;
        y_ += yVel_;
    }
    bool inUse() const
    {
        return framesLeft_ > 0;
    }

  private:
    int framesLeft_;
    double x_, y_;
    double xVel_, yVel_;
};

// パーティクル用のオブジェクトプール
class ParticlePool
{
  public:
    void create(double x, double y, double xVel, double yVel, int lifetime)
    {
        for (int i = 0; i < POOL_SIZE; ++i) {
            if (!particles_[i].inUse()) {
                particles_[i].init(x, y, xVel, yVel, lifetime);
                return;
            }
        }
    }

    void animate()
    {
        for (int i = 0; i < POOL_SIZE; ++i) {
            particles_[i].animate();
        }
    }

  private:
    static const int POOL_SIZE = 100;
    Particle particles_[POOL_SIZE];
};