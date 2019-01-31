#pragma once

#include <better_enums/enum.h>
#include <pcg/pcg_random.hpp>

#include <vector>

struct Quartz;
struct RM;
struct SB;

BETTER_ENUM(Sounds, uint32_t,
    BigDeal
);

struct Play
{
    Play(Quartz& a_Q, RM& a_RM, SB& a_SB);
    ~Play()
    {
    }

    void Run();

    Quartz& m_Q;

    RM& m_RM;

    SB& m_SB;
};
