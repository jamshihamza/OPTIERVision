#include "pch.h"
#include <chrono>
#include <iostream>
#include <thread>

#include "optier/OpenCVRTSPClient.h"
#include "optier/FrameQueue.h"
#include "optier/CaptureThread.h"
#include "optier/ConsumerThread.h"

using namespace optier;

int main()
{
    OpenCVRTSPClient client;

    if (!client.Connect("rtsp://admin:Opt@12345@192.168.10.3:554/rtsp/streaming?channel=01&subtype=0"))
    {
        std::cout << "Failed to connect\n";
        return -1;
    }

    FrameQueue queue(30);

    CaptureThread capture(client, queue);
    ConsumerThread consumer(queue);

    capture.Start();
    consumer.Start();

    std::cout << "Pipeline running...\n";

    std::this_thread::sleep_for(std::chrono::seconds(10));

    std::cout << "Stopping...\n";

    capture.Stop();
    consumer.Stop();

    client.Disconnect();

    std::cout
        << "Processed Frames : "
        << consumer.ProcessedFrames()
        << std::endl;

    return 0;
}