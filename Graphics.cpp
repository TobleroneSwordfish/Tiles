#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//cross platform way of getting current directory - thanks to https://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
#include <stdio.h>  //defines FILENAME_MAX
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

//adaptation of Ian's c API for C++ and the specifics of this project
class Display
{
    int height, width;
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::vector<std::pair<std::string, SDL_Texture>> textures;

    Display(char *title, int width, int height)
    {
        this.width = width;
        this.height = height;
        NotNeg(SDL_Init(SDL_INIT_VIDEO));
        int x = SDL_WINDOWPOS_UNDEFINED, y = SDL_WINDOWPOS_UNDEFINED;
        window = notNull(SDL_CreateWindow(title, x, y, width, height, 0));
        SDL_Surface *surface = notNull(SDL_GetWindowSurface(d->window));
        renderer = notNull(SDL_CreateSoftwareRenderer(surface));
        SDL_RenderClear(renderer);
        SDL_UpdateWindowSurface(window);
    }
    Display~()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }
    private static void Fail()
    {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    private static void *NotNull(void *p)
    {
        if (p == NULL)
        {
            fail();
        }
        return p;
    }
    private static int NotNeg(int n)
    {
        if (n < 0)
        {
            fail();
        }
        return n;
    }
    //loads all textures from a folder into RAM
    public LoadTextures(char *path)
    {
        //no cross platform method of getting list of files from directory until C++17, which I really don't want to upgrade to
        //I have three solutions: import boost - massive lib that I really don't want to bother with
        //or define one for unix and one for windows
        //or just tell windows to go get fucked and just parse 'ls'

        //have found fourth solution: tinydir!
        char currentDir[FILENAME_MAX];
        GetCurrentDir(currentDir, sizeof(currentDir));
        tinydir_dir dir;
        if (tinydir_open(&dir, "./Textures") == -1)
        {
            std::cout << "Cannot find textures folder, SELF DESTRUCT INITIATED" << std::endl;
            exit(1);
        }
        while (dir.has_next)
        {
            tinydir_file file;

        }
    }
};

void Render(World *world)
{
    Display disp = new Display();
    SDL_Texture img = IMG_LoadTexture(disp.renderer, "C:\cygwin64\home\Idiot end user\Tiles\Textures\cheese.png");
    SDL_QueryTexture(img, )
}