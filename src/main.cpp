#include "rasterizer.h"
#include <iostream>


int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    {
        std::vector<Object> objects = {
            Object({ 0, 0, 20 }, "res/spirala.facet"),
            Object({ 0, -15, 15 }, "res/donut.facet"),
            Object({ 0, -14, 15 }, "res/sphere1568.facet")
        };

        Rasterizer r(objects);
        r.mainloop();
    }

    SDL_Quit();

	return 0;
}
