#include "pch.h"

#include <iostream>

#include <opencv2/core.hpp>

#include <optier/OpenCVRTSPClient.h>
#include <optier/VideoFrame.h>

int main()
{
    std::cout << "========================================\n";
    std::cout << " OPTIER Vision RTSP Test\n";
    std::cout << "========================================\n\n";

    std::cout << cv::getBuildInformation() << "\n";

    const std::string rtspUrl =
        "rtsp://admin:Opt@12345@192.168.10.3:554/rtsp/streaming?channel=01&subtype=0";

    optier::OpenCVRTSPClient client;

    std::cout << "\nConnecting...\n";

    if (!client.Connect(rtspUrl))
    {
        std::cout << "Failed to connect to RTSP stream.\n";
        return -1;
    }

    std::cout << "Connected successfully.\n\n";

    optier::VideoFrame frame;

    if (!client.ReadFrame(frame))
    {
        std::cout << "Failed to read first frame.\n";
        client.Disconnect();
        return -1;
    }

    std::cout << "First frame received.\n\n";

    std::cout << "Width       : "
        << frame.Width
        << '\n';

    std::cout << "Height      : "
        << frame.Height
        << '\n';

    std::cout << "FrameNumber : "
        << frame.FrameNumber
        << '\n';

    client.Disconnect();

    std::cout << "\nDisconnected.\n";

    return 0;
}