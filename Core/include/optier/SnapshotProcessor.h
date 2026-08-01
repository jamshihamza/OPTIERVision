#pragma once

#include <atomic>
#include <filesystem>

#include <optier/IFrameProcessor.h>

namespace optier
{

    class SnapshotProcessor final : public IFrameProcessor
    {
    public:

        explicit SnapshotProcessor(
            const std::filesystem::path& outputDirectory);

        bool ProcessFrame(
            VideoFrame& frame) override;

    private:

        std::filesystem::path m_outputDirectory;

        std::atomic<std::uint64_t> m_snapshotIndex{ 0 };
    };

}