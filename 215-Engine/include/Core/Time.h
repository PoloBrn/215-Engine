#pragma once

namespace Core
{
    class Time
    {
        public:
            static void Update(float currentTime);

            static float DeltaTime();
            static float TimeSinceStart();

        private:
            static float s_lastTime;
            static float s_deltaTime;
            static float s_timeSinceStart;
    };
}