#include <Wave.h>

#include <functional>

Wave::Wave(RM& a_RM, int32_t a_X, int32_t a_Y, std::vector<int16_t>& a_Data, WaveFlags a_Flags)
: m_RM(a_RM)
, m_End(m_RM.AddEnd(std::bind(&Wave::See, this, std::placeholders::_1), this))
, m_X(a_X)
, m_Y(a_Y)
, m_Data(a_Data)
, m_Flags(a_Flags)
{
}

Wave::~Wave()
{
    m_RM.RemoveEnd(m_End);
}

void Wave::See(SDL_Rect& a_Rect)
{
    SDL_SetRenderDrawColor(m_RM.m_Renderer, 0xb0, 0xb0, 0xb0, 0xff);

    for (int32_t i = -m_Scale; i < (int32_t)m_Scale; ++i)
    {
        SDL_RenderDrawPoint(m_RM.m_Renderer, m_X, m_Y + i);
    }

    for (uint32_t i = 0; i < m_Length; ++i)
    {
        SDL_RenderDrawPoint(m_RM.m_Renderer, m_X + i, m_Y);
    }

    SDL_SetRenderDrawColor(m_RM.m_Renderer, 0xff, 0x22, 0x33, 0xff);

    for (uint32_t i = 0; i < m_Data.size() && i < m_Length; i += 2)
    {
        double d = m_Data[i];

        d /= std::numeric_limits<int16_t>::max();

        int32_t final = d * (double)m_Scale;

        SDL_RenderDrawPoint(m_RM.m_Renderer, m_X + (i / 2) + 1, m_Y + final);
    }
}
