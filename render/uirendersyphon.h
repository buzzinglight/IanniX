#include <QGLWidget>

class UiRenderSyphon {
public:
    explicit UiRenderSyphon();
    ~UiRenderSyphon();

public:
    void openPort();
    void publishTexture(GLuint textureId, int textureTarget, int width, int height);

protected:
    void *mSyphon;
    GLuint texture;
};
