#include "pch.h"
#include <optier/FrameProcessorPipeline.h>
#include <iostream>
#include <chrono>
#include <string_view>


namespace optier
{

    void FrameProcessorPipeline::AddProcessor(
        std::shared_ptr<IFrameProcessor> processor)

    {
        if (!processor)
        {
            return;
        }

        m_processors.push_back(std::move(processor));
    }

    bool FrameProcessorPipeline::ProcessFrame(
        VideoFrame& frame)
    {
        frame.Statistics.ReserveProcessorTimings(
            m_processors.size());

        frame.Statistics.ProcessingStartTime =
            std::chrono::steady_clock::now();

       /* std::cout
            << "[Pipeline] Frame "
            << frame.FrameNumber
            << '\n';*/
        for (const auto& processor : m_processors)
        {
            const auto start =
                std::chrono::steady_clock::now();

            const bool result =
                processor->ProcessFrame(frame);

            const auto end =
                std::chrono::steady_clock::now();

            const auto duration =
                std::chrono::duration_cast<std::chrono::microseconds>(
                    end - start);

            frame.Statistics.ProcessorTimings.push_back(
                ProcessorTiming
                {
                    processor->Name(),
                    duration
                });

            if (!result)
            {
                return false;
            }
        }

        frame.Statistics.ProcessingEndTime =
            std::chrono::steady_clock::now();

        frame.Statistics.ProcessingDuration =
            std::chrono::duration_cast<
            std::chrono::microseconds>(
                frame.Statistics.ProcessingEndTime -
                frame.Statistics.ProcessingStartTime);
        return true;
    }

    std::size_t FrameProcessorPipeline::ProcessorCount() const
    {
        return m_processors.size();
    }

}