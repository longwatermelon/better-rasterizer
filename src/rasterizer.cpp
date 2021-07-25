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

        float rotx[3][3] = {
            { 1, 0, 0 },
            { 0, cosf(m_camera.va()), sinf(m_camera.va()) },
            { 0, -sinf(m_camera.va()), cosf(m_camera.va()) }
        };

        float roty[3][3] = {
            { cosf(m_camera.ha()), 0, sinf(m_camera.ha()) },
            { 0, 1, 0 },
            { -sinf(m_camera.ha()), 0, cosf(m_camera.ha()) }
        };

        for (auto& obj : m_objects)
        {
            obj.render(m_rend, m_camera, rotx, roty);
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
            case SDLK_d:
                m_camera.move(1.f, 0.f, 0.f);
                break;
            case SDLK_a:
                m_camera.move(-1.f, 0.f, 0.f);
                break;
            case SDLK_w:
                m_camera.move(0.f, 0.f, 1.f);
                break;
            case SDLK_s:
                m_camera.move(0.f, 0.f, -1.f);
                break;
            case SDLK_SPACE:
                m_camera.move(0.f, -1.f, 0.f);
                break;
            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                m_camera.move(0.f, 1.f, 0.f);
                break;
            
            case SDLK_LEFT:
                m_camera.rotate(-0.1f, 0.f);
                break;
            case SDLK_RIGHT:
                m_camera.rotate(0.1f, 0.f);
                break;
            case SDLK_UP:
                m_camera.rotate(0.f, -0.1f);
                break;
            case SDLK_DOWN:
                m_camera.rotate(0.f, 0.1f);
                break;
            }
        } break;
        }
    }
}

