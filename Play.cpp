#include <Play.h>

#include <Wave.h>

#include <Curie/Input.h>
#include <Curie/Quartz.h>
#include <Curie/RM.h>
#include <Curie/SB.h>
#include <Curie/SH.h>

#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

Play::Play(Quartz& a_Q, RM& a_RM, SB& a_SB)
: m_Q(a_Q)
, m_RM(a_RM)
, m_SB(a_SB)
{
    m_SB.AddSound(Sounds::BigDeal, m_SB.SForF(25.0), [&](uint32_t t, uint32_t l, int16_t& left, int16_t& right)
    {
        left = SH<int16_t>(t, l)
            .Sin(12.777)
            .Vol(0.85)
            .Done();

        right = SH<int16_t>(t + 256, l)
            .Sin(15.777)
            .Vol(0.85)
            .Done();
    });
}

void Play::Run()
{
    Wave* w = nullptr;

    auto s = m_SB.m_Sounds.find(Sounds::BigDeal);

    if (s != m_SB.m_Sounds.end())
    {
        w = new Wave(m_RM, 12, s->second);
    }

    bool exit = false;
    while ( ! exit)
    {
        m_SB.PlaySound(Sounds::BigDeal);

        Input in(m_Q);
        in.m_KeyDownResponses[{SDLK_RETURN}] = [](SDL_Keycode a_Key)
        {
            return true;
        };
        in.m_KeyDownResponses[{SDLK_ESCAPE}] = [&](SDL_Keycode a_Key)
        {
            exit = true;
            return exit;
        };

        in.Enter([&]()
        {
        });
    }

    if (w)
        delete w;
}
