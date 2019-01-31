#pragma once

#include <Curie/RM.h>

#include <better_enums/enum.h>

BETTER_ENUM(WaveFlags, uint32_t,
    None = 0x0
);

struct Wave
{
    Wave(RM& a_RM, int32_t a_Margin, std::vector<int16_t>& a_Data, WaveFlags a_Flags = WaveFlags::None);

    ~Wave();

    Wave(const Wave&) = delete;

    void See(SDL_Rect& a_Rect);

    RM& m_RM;
    End* m_End;
    int32_t m_Margin;

    std::vector<int16_t>& m_Data;

    double m_Scale;

    WaveFlags m_Flags;
};
