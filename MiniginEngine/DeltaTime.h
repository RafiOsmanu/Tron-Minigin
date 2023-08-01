#pragma once
#include <chrono>
#include "Singleton.h"

namespace dae
{
    class DeltaTime : public Singleton<DeltaTime>
    {
    private:
        std::chrono::high_resolution_clock::time_point m_LastTime = std::chrono::steady_clock::now();;
        float m_DeltaTime = 0;
        float m_MaxTime = 28.f;
        float m_Time = 0;

    public:
        DeltaTime() = default;

        void Update() {
            auto currentTime = std::chrono::steady_clock::now();
            m_DeltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - m_LastTime).count();
            if (m_DeltaTime >= m_MaxTime)
            {
                m_DeltaTime = m_MaxTime;
            }
            m_Time += m_DeltaTime;

            m_LastTime = currentTime;
        }

        float getDeltaTime() const {
            return m_DeltaTime;
        }
    };
}




