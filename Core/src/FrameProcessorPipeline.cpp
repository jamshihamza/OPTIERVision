#include "pch.h"
#include <optier/FrameProcessorPipeline.h>

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
        for (const auto& processor : m_processors)
        {
            if (!processor->ProcessFrame(frame))
            {
                return false;
            }
        }

        return true;
    }

    std::size_t FrameProcessorPipeline::ProcessorCount() const
    {
        return m_processors.size();
    }

}