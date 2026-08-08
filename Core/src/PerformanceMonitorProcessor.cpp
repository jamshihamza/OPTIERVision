#include "pch.h"

#include <iostream>

#include <optier/PerformanceMonitorProcessor.h>
#include <string_view>

namespace optier
{

    bool PerformanceMonitorProcessor::ProcessFrame(
        VideoFrame& frame)
    {
        std::cout
            << "[PerformanceMonitor] Frame "
            << frame.FrameNumber
            << '\n';

        std::cout
            << "[PerformanceMonitor] this="
            << this
            << '\n';

        //
        // Convert processing time to microseconds
        //
       /* auto processingTime =
            std::chrono::duration_cast<std::chrono::microseconds>(
                frame.Statistics.ProcessingDuration);*/

        std::chrono::microseconds processingTime{ 0 };

        for (const auto& timing : frame.Statistics.ProcessorTimings)
        {
            processingTime += timing.Duration;
        }
        //
        // Count processed frames
        //
        ++m_frameCounter;

        //
        // Accumulate per-stage timings
        //
        for (const auto& timing : frame.Statistics.ProcessorTimings)
        {
            m_stageTotals[std::string(timing.ProcessorName)] +=
                timing.Duration;
        }

        //
        // Accumulate processing time
        //
        m_totalTime += processingTime;

        //
        // Minimum
        //
        if (processingTime < m_minTime)
        {
            m_minTime = processingTime;
        }

        //
        // Maximum
        //
        if (processingTime > m_maxTime)
        {
            m_maxTime = processingTime;
        }

        //
        // Report every 30 frames
        //
        if (m_frameCounter >= 30)
        {
            const auto averageTime =
                m_totalTime.count() /
                static_cast<long long>(m_frameCounter);

            const auto now =
                std::chrono::steady_clock::now();

            const auto elapsed =
                std::chrono::duration_cast<
                std::chrono::milliseconds>(
                    now - m_lastReport);

            double fps = 0.0;

            if (elapsed.count() > 0)
            {
                fps =
                    static_cast<double>(m_frameCounter) /
                    (elapsed.count() / 1000.0);
            }

            std::cout << "\n";
            std::cout << "========================================\n";
            std::cout << " Performance Report\n";
            std::cout << "========================================\n";
            std::cout << "Frames        : " << m_frameCounter << "\n";
            std::cout << "FPS           : " << fps << "\n";
            std::cout << "Average Time  : " << averageTime << " us\n";
            std::cout << "Minimum Time  : " << m_minTime.count() << " us\n";
            std::cout << "Maximum Time  : " << m_maxTime.count() << " us\n";
            std::cout << "========================================\n\n";

            std::cout << "\n";
            std::cout << "Per-Stage Average\n";
            std::cout << "----------------------------------------\n";

            long long totalStageAverage = 0;

            for (const auto& stage : m_stageTotals)
            {
                const auto average =
                    stage.second.count() /
                    static_cast<long long>(m_frameCounter);

                totalStageAverage += average;

                std::cout
                    << stage.first
                    << " : "
                    << average
                    << " us\n";
            }

            std::cout << "----------------------------------------\n";
            std::cout
                << "Total Stage Time : "
                << totalStageAverage
                << " us\n";

            //
            // Reset
            //
            m_stageTotals.clear();

            m_frameCounter = 0;
            m_totalTime = std::chrono::microseconds{ 0 };
            m_minTime = std::chrono::microseconds::max();
            m_maxTime = std::chrono::microseconds{ 0 };
            m_lastReport = now;
        }

        return true;
    }
    std::string_view optier::PerformanceMonitorProcessor::Name() const
    {
        return "PerformanceMonitorProcessor";
    }
} // namespace optier