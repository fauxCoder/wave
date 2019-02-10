#include <Wave.h>

#include <functional>

Wave::Wave(RM& a_RM, int32_t a_X, int32_t a_Y, uint32_t a_Width, uint32_t a_Height, int32_t a_Margin, std::vector<double>& a_Data, WaveFlags a_Flags)
: m_RM(a_RM)
, m_End(m_RM.AddEnd(std::bind(&Wave::See, this, std::placeholders::_1), this))
, m_X(a_X)
, m_Y(a_Y)
, m_Width(a_Width)
, m_Height(a_Height)
, m_Margin(a_Margin)
, m_Data(a_Data)
, m_Scale(0.5)
, m_Flags(a_Flags)
{
}

Wave::~Wave()
{
    m_RM.RemoveEnd(m_End);
}

void Wave::See(SDL_Rect& a_Rect)
{
    uint32_t usableWidth = m_Width - (m_Margin * 2);
    uint32_t wHeight = (m_Height / 2) - m_Margin;
    int32_t wOriginX = m_X + m_Margin;
    int32_t wOriginY = m_Y + m_Margin + wHeight;

    SDL_SetRenderDrawColor(m_RM.m_Renderer, 0xb0, 0xb0, 0xb0, 0xff);

    for (int32_t i = -(wHeight * m_Scale); i < (int32_t)(wHeight * m_Scale); ++i)
    {
        SDL_RenderDrawPoint(m_RM.m_Renderer, wOriginX, wOriginY + i);
    }

    for (uint32_t i = 0; i < usableWidth; ++i)
    {
        SDL_RenderDrawPoint(m_RM.m_Renderer, wOriginX + i, wOriginY);
    }

    for (uint32_t i = 0; i < m_Data.size() && i < usableWidth; ++i)
    {
        // if ((i % 2) == 0)
        // {
        SDL_SetRenderDrawColor(m_RM.m_Renderer, 0xff, 0x99, 0x77, 0xff);
        // }
        // else
        // {
        //     SDL_SetRenderDrawColor(m_RM.m_Renderer, 0x77, 0x99, 0xff, 0xff);
        // }

        double d = m_Data[i];

        int32_t final = std::round(d * (double)(wHeight * m_Scale));

        SDL_RenderDrawPoint(m_RM.m_Renderer, wOriginX + i + 1 + 1, wOriginY + final);
        SDL_RenderDrawPoint(m_RM.m_Renderer, wOriginX + i + 1 - 1, wOriginY + final);
        SDL_RenderDrawPoint(m_RM.m_Renderer, wOriginX + i + 1, wOriginY + final + 1);
        SDL_RenderDrawPoint(m_RM.m_Renderer, wOriginX + i + 1, wOriginY + final - 1);
    }
}
