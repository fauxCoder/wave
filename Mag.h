#pragma once

#include <Curie/RM.h>

#include <better_enums/enum.h>

BETTER_ENUM(MagFlags, uint32_t,
    None = 0x0
);

struct Mag
{
    Mag(RM& a_RM, int32_t a_X, int32_t a_Y, uint32_t a_Width, uint32_t a_Height, int32_t a_Margin, std::vector<double>& a_Data, MagFlags a_Flags = MagFlags::None);

    ~Mag();

    Mag(const Mag&) = delete;

    void See(SDL_Rect& a_Rect);

    RM& m_RM;
    End* m_End;
    std::vector<double>& m_Data;

    int32_t m_X;
    int32_t m_Y;
    uint32_t m_Width;
    uint32_t m_Height;
    int32_t m_Margin;

    double m_Scale;

    MagFlags m_Flags;

    double* m_Input;
};
