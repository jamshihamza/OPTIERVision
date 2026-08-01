#pragma once

#include <memory>
#include <vector>

#include <optier/IFrameProcessor.h>

namespace optier
{

    class FrameProcessorPipeline
    {
    public:

        FrameProcessorPipeline() = default;

        ~FrameProcessorPipeline() = default;

        FrameProcessorPipeline(const FrameProcessorPipeline&) = delete;
        FrameProcessorPipeline& operator=(const FrameProcessorPipeline&) = delete;

        FrameProcessorPipeline(FrameProcessorPipeline&&) = delete;
        FrameProcessorPipeline& operator=(FrameProcessorPipeline&&) = delete;

    public:

        void AddProcessor(
            std::shared_ptr<IFrameProcessor> processor);

        bool ProcessFrame(
            VideoFrame& frame);

        std::size_t ProcessorCount() const;

    private:

        std::vector<std::shared_ptr<IFrameProcessor>> m_processors;
    };

}