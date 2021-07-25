#include "rasterizer.h"
#include <iostream>


int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    {
        std::vector<Object> objects = {
            Object({ 0, 0, 3 }, "res/cube.facet")
        };

        Rasterizer r(objects);
        r.mainloop();
    }

    SDL_Quit();

	return 0;
}
