#include <Wave.h>

#include <functional>

Wave::Wave(RM& a_RM, int32_t a_Margin, std::vector<int16_t>& a_Data, WaveFlags a_Flags)
: m_RM(a_RM)
, m_End(m_RM.AddEnd(std::bind(&Wave::See, this, std::placeholders::_1), this))
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
    uint32_t usableWidth = RM::s_ScreenWidth - (m_Margin * 2);
    uint32_t wOriginX = m_Margin;
    uint32_t wOriginY = RM::s_ScreenHeight / 2;
    uint32_t wHeight = wOriginY - m_Margin;

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
        if ((i % 2) == 0)
        {
            SDL_SetRenderDrawColor(m_RM.m_Renderer, 0xff, 0x99, 0x77, 0xff);
        }
        else
        {
            SDL_SetRenderDrawColor(m_RM.m_Renderer, 0x77, 0x99, 0xff, 0xff);
        }

        double d = m_Data[i];

        d /= std::numeric_limits<int16_t>::max();

        int32_t final = std::round(d * (double)(wHeight * m_Scale));

        SDL_RenderDrawPoint(m_RM.m_Renderer, wOriginX + i + 1 + 1, wOriginY + final);
        SDL_RenderDrawPoint(m_RM.m_Renderer, wOriginX + i + 1 - 1, wOriginY + final);
        SDL_RenderDrawPoint(m_RM.m_Renderer, wOriginX + i + 1, wOriginY + final + 1);
        SDL_RenderDrawPoint(m_RM.m_Renderer, wOriginX + i + 1, wOriginY + final - 1);
    }
}
