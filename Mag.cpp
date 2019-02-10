#include <Mag.h>

#include <FFT.h>

#include <functional>

#include <iostream>

#define DSIZE 1024

Mag::Mag(RM& a_RM, int32_t a_X, int32_t a_Y, uint32_t a_Width, uint32_t a_Height, int32_t a_Margin, std::vector<double>& a_Data, MagFlags a_Flags)
: m_RM(a_RM)
, m_End(m_RM.AddEnd(std::bind(&Mag::See, this, std::placeholders::_1), this))
, m_Data(a_Data)
, m_X(a_X)
, m_Y(a_Y)
, m_Width(a_Width)
, m_Height(a_Height)
, m_Margin(a_Margin)
, m_Scale(1.0)
, m_Flags(a_Flags)
{
    m_Input = (double*)malloc(sizeof(double) * DSIZE);
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
        m_Input[i] = m_Data[i];

        if (i < (DSIZE / 4))
        {
            m_Input[i] *= ((double)i) / (DSIZE / 4);
        }
        else if (i > ((DSIZE * 3) / 4))
        {
            m_Input[i] *= ((double)(DSIZE - i)) / (DSIZE / 4);
        }
    }

    for (uint32_t i = 0; i < usableWidth; ++i)
    {
        SDL_RenderDrawPoint(m_RM.m_Renderer, gOriginX + i, gOriginY);
    }

    DanielsonLanczos<DSIZE/2> dl;
    dl.apply(m_Input);

    SDL_SetRenderDrawColor(m_RM.m_Renderer, 0xff, 0x99, 0x77, 0xff);

    static const uint32_t s = 64;
    uint32_t bins[s] = {0};

    double i = 1.0;
    std::vector<double> ranges;
    while (ranges.size() < s)
    {
        ranges.push_back(i*0.5);
        i++;
    }

    for (uint32_t i = 0; i < (DSIZE / 2); i += 2)
    {
        double r = sqrt(pow(m_Input[i], 2.0) + pow(m_Input[i+1], 2.0));

        uint32_t index = 0;
        while (index < s)
        {
            if (ranges[index] >= r)
            {
                bins[index]++;
                break;
            }

            ++index;
        }
    }

    for (uint32_t i = 0; i < usableWidth; ++i)
    {
        uint32_t step = usableWidth / s;
        uint32_t steps = i / step;
        SDL_RenderDrawPoint(m_RM.m_Renderer, gOriginX + i, gOriginY - bins[steps]);
    }
}
