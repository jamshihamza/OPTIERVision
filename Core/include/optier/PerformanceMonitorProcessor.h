#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <unordered_map>

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

        std::string_view Name() const override;
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

        std::unordered_map<
            std::string,
            std::chrono::microseconds>
            m_stageTotals;
    };

} // namespace optier