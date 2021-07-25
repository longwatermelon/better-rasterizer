#include "rasterizer.h"


Rasterizer::Rasterizer(const std::vector<Object>& objects)
    : m_objects(objects), m_camera({ 0.f, 0.f, 0.f })
{
    m_window = SDL_CreateWindow("Rasterizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
    m_rend = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_RenderClear(m_rend);
    SDL_RenderPresent(m_rend);
}


Rasterizer::~Rasterizer()
{
    SDL_DestroyRenderer(m_rend);
    SDL_DestroyWindow(m_window);
}


void Rasterizer::mainloop()
{
    SDL_Event evt;

    while (m_running)
    {
        handle_events(evt);

        SDL_RenderClear(m_rend);

        for (auto& obj : m_objects)
        {
            obj.render(m_rend, m_camera);
        }

        SDL_SetRenderDrawColor(m_rend, 0, 0, 0, 255);
        SDL_RenderPresent(m_rend);
    }
}


void Rasterizer::handle_events(SDL_Event& evt)
{
    while (SDL_PollEvent(&evt))
    {
        switch (evt.type)
        {
        case SDL_QUIT:
            m_running = false;
            return;
        case SDL_KEYDOWN:
        {
            switch (evt.key.keysym.sym)
            {
            case SDLK_RIGHT:
                m_camera.move(1.f, 0.f, 0.f);
                break;
            case SDLK_LEFT:
                m_camera.move(-1.f, 0.f, 0.f);
                break;
            case SDLK_UP:
                m_camera.move(0.f, 0.f, 1.f);
                break;
            case SDLK_DOWN:
                m_camera.move(0.f, 0.f, -1.f);
                break;
            case SDLK_SPACE:
                m_camera.move(0.f, -1.f, 0.f);
                break;
            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                m_camera.move(0.f, 1.f, 0.f);
                break;
            }
        } break;
        }
    }
}

