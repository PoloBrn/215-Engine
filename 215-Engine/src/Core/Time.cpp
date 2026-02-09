#include "Core/Time.h"

namespace Core
{
    float Time::s_lastTime = 0.0f;
    float Time::s_deltaTime = 0.0f;
    float Time::s_timeSinceStart = 0.0f;

    void Time::Update(float currentTime)
    {
        s_deltaTime = currentTime - s_lastTime;
        s_lastTime = currentTime;
        s_timeSinceStart += s_deltaTime;
    }

    float Time::DeltaTime() { return s_deltaTime; }

    float Time::TimeSinceStart() { return s_timeSinceStart; }
}