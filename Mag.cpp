#include <Mag.h>

#include <FFT.h>

#include <functional>

#define DSIZE 1024

Mag::Mag(RM& a_RM, int32_t a_X, int32_t a_Y, uint32_t a_Width, uint32_t a_Height, int32_t a_Margin, MagFlags a_Flags)
: m_RM(a_RM)
, m_End(m_RM.AddEnd(std::bind(&Mag::See, this, std::placeholders::_1), this))
, m_X(a_X)
, m_Y(a_Y)
, m_Width(a_Width)
, m_Height(a_Height)
, m_Margin(a_Margin)
, m_Scale(1.0)
, m_Flags(a_Flags)
{
    m_Data = (double*)malloc(sizeof(double) * DSIZE);
}

Mag::~Mag()
{
    m_RM.RemoveEnd(m_End);
}

void Mag::See(SDL_Rect& a_Rect)
{
    uint32_t usableWidth = m_Width - (m_Margin * 2);
    int32_t gOriginX = m_X + m_Margin;
    int32_t gOriginY = m_Y + m_Height - m_Margin;
    uint32_t gHeight = m_Height - (m_Margin * 2);

    SDL_SetRenderDrawColor(m_RM.m_Renderer, 0xb0, 0xb0, 0xb0, 0xff);

    for (uint32_t i = 0; i < (uint32_t)(gHeight * m_Scale); ++i)
    {
        SDL_RenderDrawPoint(m_RM.m_Renderer, gOriginX, gOriginY - i);
    }

    for (uint32_t i = 0; i < DSIZE; ++i)
    {
        m_Data[i] = (std::sin(((double)i) / 12.0));
        m_Data[++i] = 0.0;
    }

    for (uint32_t i = 0; i < usableWidth && i < DSIZE; ++i)
    {
        SDL_RenderDrawPoint(m_RM.m_Renderer, gOriginX + i, gOriginY);
        SDL_RenderDrawPoint(m_RM.m_Renderer, gOriginX + i, gOriginY - (m_Data[i] * gHeight * m_Scale));
    }

    DanielsonLanczos<DSIZE/2> dl;
    dl.apply(m_Data);

    SDL_SetRenderDrawColor(m_RM.m_Renderer, 0xff, 0x99, 0x77, 0xff);

    for (uint32_t i = 0; i < DSIZE; ++i)
    {
        SDL_RenderDrawPoint(m_RM.m_Renderer, gOriginX + i, gOriginY - m_Data[i] - (gHeight * m_Scale * 0.5));
    }
}
