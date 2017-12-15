#include "World.h"
class SDL_Window;
class SDL_Renderer;
class Texture;
class Display
{
private:
    int height, width;
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::vector<Texture *> textures;
    int textureSize = -1;
    static void Fail();
    static void *NotNull(void *p);
    static int NotNeg(int n);
    void DrawTexture(Texture *texture, int x, int y, Direction dir);
    Texture *FindTexture(int subID, int typeID);
public:
    Display(char *title, int xSize, int ySize, int textureSize);
    ~Display();
    void LoadTextures();
    void Render(World *world, int x, int y, int r);
    void Render(World *world);
    char GetKey();
    void MsgBox(const char *title, const char *msg);
    void DrawString(const char *text, int x, int y);
};