#pragma once

#include <chrono>
#include <cstdint>

#include <optier/IFrameProcessor.h>

namespace optier
{

    class PerformanceMonitorProcessor final
        : public IFrameProcessor
    {
    public:

        PerformanceMonitorProcessor() = default;

        bool ProcessFrame(
            VideoFrame& frame) override;

    private:

        //
        // Frame Statistics
        //
        std::uint64_t m_frameCounter = 0;

        std::chrono::steady_clock::time_point
            m_lastReport =
            std::chrono::steady_clock::now();

        std::chrono::microseconds
            m_totalTime{ 0 };

        std::chrono::microseconds
            m_minTime{
                std::chrono::microseconds::max()
        };

        std::chrono::microseconds
            m_maxTime{ 0 };
    };

} // namespace optier