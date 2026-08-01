#include "pch.h"

#include <optier/SnapshotProcessor.h>

#include <iomanip>
#include <opencv2/imgcodecs.hpp>
#include <sstream>

namespace optier
{

    SnapshotProcessor::SnapshotProcessor(
        const std::filesystem::path& outputDirectory)
        : m_outputDirectory(outputDirectory)
    {
        std::filesystem::create_directories(
            m_outputDirectory);
    }

    bool SnapshotProcessor::ProcessFrame(
        VideoFrame& frame)
    {
        if (!frame.Image)
        {
            return false;
        }

        if (frame.Image->empty())
        {
            return false;
        }

        //
        // Save every 100th frame.
        //
        if ((frame.FrameNumber % 100) != 0)
        {
            return true;
        }

        const auto index =
            ++m_snapshotIndex;

        std::ostringstream fileName;

        fileName
            << "snapshot_"
            << std::setw(6)
            << std::setfill('0')
            << index
            << ".jpg";

        const auto fullPath =
            m_outputDirectory /
            fileName.str();

        return cv::imwrite(
            fullPath.string(),
            *frame.Image);
    }

}