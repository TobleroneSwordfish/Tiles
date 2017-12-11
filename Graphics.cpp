extern "C"
{
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
}
#include <string>
#include <iostream>
#include <vector>
#include "Graphics.h"
#include "Tiles.h"
#include "tinydir.h"
//cross platform way of getting current directory - thanks to https://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
// #include <stdio.h>  //defines FILENAME_MAX
// #ifdef WINDOWS
//     #include <direct.h>
//     #define GetCurrentDir _getcwd
// #else
//     #include <unistd.h>
//     #define GetCurrentDir getcwd
//  #endif

enum EntityType
{
    TILE,
    TILE_EFFECT
};

std::string GetCurrentDirectory()
{
    char *dir = SDL_GetBasePath();
    std::string out = std::string(dir);
    SDL_free(dir);
    return out;
}

class Texture
{
public:
    int subID, typeID;
    SDL_Texture *SDLt;
    Texture(std::string path, SDL_Renderer *renderer)
    {
        std::cout << "Loading texture at " << path << std::endl;
        SDLt = IMG_LoadTexture(renderer, path.c_str());
        int i = path.length();
        while (path[i] != ')' && i >= 0)
        {
            i--;
        }
        if (i == 0)
        {
            std::cout << "texture name format fucked\n";
        }
        subID = path[i - 1] - '0';
        typeID = path[i - 3] - '0';
        std::cout << "SubID: " << subID << " TypeID: " << typeID << std::endl;
    }
};

//adaptation of Ian's c API for C++ and the specifics of this project
//okay, it's become a pretty loose adaptation
Display::Display(char *title, int xSize, int ySize, int textureSize)
{
    std::cout << "Initializing display" << std::endl;
    this->width = xSize * textureSize;
    this->height = ySize * textureSize;
    NotNeg(SDL_Init(SDL_INIT_VIDEO));
    int x = SDL_WINDOWPOS_UNDEFINED, y = SDL_WINDOWPOS_UNDEFINED;
    window = (SDL_Window *)NotNull(SDL_CreateWindow(title, x, y, width, height, 0));
    std::cout << "Window created" << std::endl;
    // SDL_Surface *surface = (SDL_Surface *)NotNull(SDL_GetWindowSurface(window));
    // std::cout << "Surface created" << std::endl;
    renderer = (SDL_Renderer *)NotNull(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
    std::cout << "Renderer created" << std::endl;
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    std::cout << "Window updated" << std::endl;
}
Display::~Display()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
void Display::Fail()
{
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);
}
void *Display::NotNull(void *p)
{
    if (p == NULL)
    {
        Fail();
    }
    return p;
}
int Display::NotNeg(int n)
{
    if (n < 0)
    {
        Fail();
    }
    return n;
}
//draws a texture on the renderer, but doesn't display it (0,0 at top left corner, fucking SDL)
void Display::DrawTexture(Texture *texture, int x, int y)
{
    std::cout << "Drawing texture with SubID " << texture->subID << " at " << x << "," << y << std::endl;
    SDL_Rect rect;
    rect.x = x * textureSize;
    rect.y = y * textureSize;
    rect.w = textureSize;
    rect.h = textureSize;
    SDL_RenderCopy(renderer, texture->SDLt, NULL, &rect);
}
Texture *Display::FindTexture(int subID, int typeID)
{
    for (auto i = textures.begin(); i != textures.end(); i++)
    {
        if ((*i)->subID == subID && (*i)->typeID == typeID)
        {
            return *i;
        }
    }
    return nullptr;
}
//loads all textures from a folder into RAM
void Display::LoadTextures()
{
    //no cross platform method of getting list of files from directory until C++17, which I really don't want to upgrade to
    //I have three solutions: import boost - massive lib that I really don't want to bother with
    //or define one for unix and one for windows
    //or just tell windows to go get fucked and just parse 'ls'

    //have found fourth solution: tinydir!
    std::string baseDir = GetCurrentDirectory();
    std::cout << "Base directory: " << baseDir << std::endl;
    tinydir_dir dir;
    if (tinydir_open(&dir, "./Textures") == -1)
    {
        std::cout << "Cannot find textures folder, SELF DESTRUCT INITIATED" << std::endl;
        exit(1);
    }
    while (dir.has_next)
    {
        tinydir_file file;
        std::cout << "Reading file: " << file.name << std::endl;
        NotNeg(tinydir_readfile(&dir, &file));
        if (!file.is_dir)
        {
            std::string path = baseDir + "Textures/" + std::string(file.name);
            Texture *nextTexture = new Texture(path, renderer);
            if (textureSize = -1)
            {
                int w, h;
                SDL_QueryTexture(nextTexture->SDLt, nullptr, nullptr, &w, &h);
                if (w != h)
                {
                    std::cout << "Texture is not square, blaaaaaghle" << std::endl;
                    Fail();
                }
                textureSize = w;
            }
            textures.push_back(nextTexture);
        }
        NotNeg(tinydir_next(&dir));
    }
}
void Display::Render(World *world)
{
    SDL_RenderClear(renderer);
    for (int y = world->yLimit; y >= 0; y--)
    {
        for (int x = world->xLimit; x >= 0; x--)
        {
            Tile *tile = world->GetTile(x, y);
            int ID = tile->ID;
            Texture *texture = (Texture *)NotNull(FindTexture(ID, TILE));
            std::cout << "Found texture with SubID " << texture->subID << std::endl;
            DrawTexture(texture, x, world->yLimit - y);
            if (tile->effectsCount > 0)
            {
                for (auto i = tile->effects.begin(); i != tile->effects.end(); i++)
                {
                    TileEffect *effect = *i;
                    Texture *effectTexture = (Texture *)NotNull(FindTexture(effect->ID, TILE_EFFECT));

                }
            }
        }
    }
    SDL_RenderPresent(renderer);
}


// void Render(World *world)
// {
//     Display disp = new Display();
//     disp.Load()
//     SDL_Texture img = IMG_LoadTexture(disp.renderer, "C:\cygwin64\home\Idiot end user\Tiles\Textures\cheese.png");
//     SDL_QueryTexture(img, )
// }