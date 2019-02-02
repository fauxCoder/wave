#pragma once

#include <cmath>

template<uint32_t N, typename T = double>
class DanielsonLanczos
{
    DanielsonLanczos<N/2,T> next;

public:
    void apply(T* data)
    {
        next.apply(data);
        next.apply(data+N);

        T wtemp,tempr,tempi,wr,wi,wpr,wpi;
        wtemp = std::sin(M_PI/N);
        wpr = -2.0*wtemp*wtemp;
        wpi = -std::sin(2*M_PI/N);
        wr = 1.0;
        wi = 0.0;
        for (uint32_t i = 0; i < N; i += 2)
        {
            tempr = data[i+N]*wr - data[i+N+1]*wi;
            tempi = data[i+N]*wi + data[i+N+1]*wr;
            data[i+N] = data[i]-tempr;
            data[i+N+1] = data[i+1]-tempi;
            data[i] += tempr;
            data[i+1] += tempi;

            wtemp = wr;
            wr += wr*wpr - wi*wpi;
            wi += wi*wpr + wtemp*wpi;
        }
    }
};

template<typename T>
class DanielsonLanczos<1, T>
{
public:
   void apply(T* data) { }
};
