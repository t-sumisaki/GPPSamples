/**
 * DoubleBufferサンプル
 * 
 */

// Framebufferクラス
class Framebuffer
{
  public:
    void clear()
    {
        for (int i = 0; i < WIDTH * HEIGHT; ++i)
        {
            pixels_[i] = WHITE;
        }
    }
    void draw(int x, int y)
    {
        pixels_[(WIDTH * y) + x] = BLACK;
    }
    const char *getPixels()
    {
        return pixels_;
    }

  private:
    static const int WIDTH = 160;
    static const int HEIGHT = 120;
    static const char WHITE = 0;
    static const char BLACK = 1;
    char pixels_[WIDTH * HEIGHT];
};

// Sceneクラス
class Scene
{
  public:
    void draw()
    {
        buffer_.clear();
        buffer_.draw(1, 1);
        buffer_.draw(4, 1);
        buffer_.draw(1, 3);
        buffer_.draw(2, 4);
        buffer_.draw(3, 4);
        buffer_.draw(4, 3);
    }

    Framebuffer &getBuffer()
    {
        return buffer_;
    }

  private:
    Framebuffer buffer_;
};

// DoubleBuffer対応Sceneクラス（Sceneと比較用）
class DoubleBufferedScene
{
  public:
    DoubleBufferedScene()
        : current_(&buffers_[0]),
          next_(&buffers_[1])
    {
    }

    void draw() {
        next_->clear();
        next_->clear();
        next_->draw(1, 1);
        next_->draw(4, 1);
        next_->draw(1, 3);
        next_->draw(2, 4);
        next_->draw(3, 4);
        next_->draw(4, 3);

        // 出力が終わったら、読み込みと書き込みのFramebufferを入れ替える
        swap();
    }

  private:
    void swap()
    {
        // Bufferのポインタを切り替える
        Framebuffer *temp = current_;
        current_ = next_;
        next_ = temp;
    }
    Framebuffer buffers_[2];
    Framebuffer *current_;
    Framebuffer *next_;
};