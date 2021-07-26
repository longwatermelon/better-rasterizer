#include "rasterizer.h"
#include "graphics.h"


Rasterizer::Rasterizer(const std::vector<Object>& objects)
    : m_objects(objects), m_camera({ 0.f, 0.f, 0.f })
{
    m_window = SDL_CreateWindow("Rasterizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
    m_rend = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_RenderClear(m_rend);
    SDL_RenderPresent(m_rend);

    m_screen_tex = SDL_CreateTexture(m_rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 800, 800);

    m_keys_down = {
        { SDLK_w, false },
        { SDLK_a, false },
        { SDLK_s, false },
        { SDLK_d, false },
        
        { SDLK_RIGHT, false },
        { SDLK_LEFT, false },
        { SDLK_UP, false },
        { SDLK_DOWN, false },

        { SDLK_LSHIFT, false },
        { SDLK_SPACE, false }
    };
}


Rasterizer::~Rasterizer()
{
    SDL_DestroyTexture(m_screen_tex);

    SDL_DestroyRenderer(m_rend);
    SDL_DestroyWindow(m_window);
}


void Rasterizer::mainloop()
{
    SDL_Event evt;

    while (m_running)
    {
        handle_events(evt);
        receive_keys();

        SDL_RenderClear(m_rend);
        graphics::texbuf_reset(m_texbuf, m_zbuf);

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
            obj.render(m_texbuf, m_zbuf, m_camera, rotx, roty);
        }

        SDL_SetRenderDrawColor(m_rend, 0, 0, 0, 255);

        graphics::update_texture(m_screen_tex, m_texbuf);
        SDL_RenderCopy(m_rend, m_screen_tex, 0, 0);

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
            if (m_keys_down.find(evt.key.keysym.sym) != m_keys_down.end())
            {
                m_keys_down[evt.key.keysym.sym] = true;
            }
            /* switch (evt.key.keysym.sym) */
            /* { */
            /* case SDLK_d: */
            /*     m_camera.move(rotate_speed, 0.f, 0.f); */
            /*     break; */
            /* case SDLK_a: */
            /*     m_camera.move(-rotate_speed, 0.f, 0.f); */
            /*     break; */
            /* case SDLK_w: */
            /*     m_camera.move(0.f, 0.f, rotate_speed); */
            /*     break; */
            /* case SDLK_s: */
            /*     m_camera.move(0.f, 0.f, -rotate_speed); */
            /*     break; */
            /* case SDLK_SPACE: */
            /*     m_camera.move(0.f, -rotate_speed, 0.f); */
            /*     break; */
            /* case SDLK_LSHIFT: */
            /*     m_camera.move(0.f, 1.f, 0.f); */
            /*     break; */
            
            /* case SDLK_LEFT: */
            /*     m_camera.rotate(-0.1f, 0.f); */
            /*     break; */
            /* case SDLK_RIGHT: */
            /*     m_camera.rotate(0.1f, 0.f); */
            /*     break; */
            /* case SDLK_UP: */
            /*     m_camera.rotate(0.f, -0.1f); */
            /*     break; */
            /* case SDLK_DOWN: */
            /*     m_camera.rotate(0.f, 0.1f); */
            /*     break; */
            /* } */
        } break;
        case SDL_KEYUP:
        {
            if (m_keys_down.find(evt.key.keysym.sym) != m_keys_down.end())
            {
                m_keys_down[evt.key.keysym.sym] = false;
            }
        } break;
        }
    }
}


void Rasterizer::receive_keys()
{
    float rotate_speed = 0.03f;
    float move_speed = 0.3f;

    if (m_keys_down[SDLK_SPACE])
        m_camera.move(0.f, -move_speed, 0.f);
    if (m_keys_down[SDLK_LSHIFT])
        m_camera.move(0.f, move_speed, 0.f);

    if (m_keys_down[SDLK_d])
        m_camera.move(move_speed, 0.f, 0.f);
    if (m_keys_down[SDLK_a])
        m_camera.move(-move_speed, 0.f, 0.f);
    if (m_keys_down[SDLK_w])
        m_camera.move(0.f, 0.f, move_speed);
    if (m_keys_down[SDLK_s])
        m_camera.move(0.f, 0.f, -move_speed);

    if (m_keys_down[SDLK_LEFT])
        m_camera.rotate(-rotate_speed, 0.f);
    if (m_keys_down[SDLK_RIGHT])
        m_camera.rotate(rotate_speed, 0.f);
    if (m_keys_down[SDLK_UP])
        m_camera.rotate(0.f, -rotate_speed);
    if (m_keys_down[SDLK_DOWN])
        m_camera.rotate(0.f, rotate_speed);
}

