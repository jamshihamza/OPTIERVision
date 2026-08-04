#include "pch.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include <optier/OpenCVRTSPClient.h>

#include <optier/AIProcessor.h>
#include <optier/CaptureThread.h>
#include <optier/ConsumerThread.h>
#include <optier/DetectionMapperProcessor.h>
#include <optier/DummyDetector.h>
#include <optier/FrameProcessorPipeline.h>
#include <optier/FrameQueue.h>
#include <optier/OpenCVRTSPClient.h>
#include <optier/OverlayProcessor.h>
#include <optier/PerformanceMonitorProcessor.h>
#include <optier/SnapshotProcessor.h>
#include <optier/VideoRenderer.h>

using namespace optier;

int main()
{
    std::cout << "========================================\n";
    std::cout << " OPTIER Vision Pipeline Test\n";
    std::cout << "========================================\n\n";

    OpenCVRTSPClient client;

    const std::string rtspUrl =
        "rtsp://admin:Opt$0987@192.168.1.100:80/rtsp/streaming?channel=09&subtype=0";

    std::cout << "Connecting...\n";

    if (!client.Connect(rtspUrl))
    {
        std::cout << "Failed to connect to RTSP stream.\n";
        return -1;
    }

    std::cout << "Connected successfully.\n";

    FrameQueue queue(30);

    FrameProcessorPipeline pipeline;

    //
    // Create processors
    //
    auto aiProcessor =
        std::make_shared<AIProcessor>(
            std::make_unique<DummyDetector>());

    auto detectionMapperProcessor =
        std::make_shared<DetectionMapperProcessor>();

    auto overlayProcessor =
        std::make_shared<OverlayProcessor>();

    auto renderer =
        std::make_shared<VideoRenderer>(
            "OPTIER Vision");

    auto snapshotProcessor =
        std::make_shared<SnapshotProcessor>(
            "snapshots");

    auto performanceProcessor =
        std::make_shared<PerformanceMonitorProcessor>();

    //
    // Register processors
    //
    pipeline.AddProcessor(aiProcessor);

    pipeline.AddProcessor(
        detectionMapperProcessor);

    pipeline.AddProcessor(
        overlayProcessor);

    pipeline.AddProcessor(
        renderer);

    pipeline.AddProcessor(
        snapshotProcessor);

    pipeline.AddProcessor(
        performanceProcessor);

    //
    // Threads
    //
    CaptureThread capture(
        client,
        queue);

    ConsumerThread consumer(
        queue,
        pipeline);

    std::cout << "Starting CaptureThread...\n";
    capture.Start();

    std::cout << "Starting ConsumerThread...\n";
    consumer.Start();

    std::cout << "\n";
    std::cout << "Pipeline running...\n";
    std::cout << "Displaying video for 10 seconds...\n\n";

    const auto endTime =
        std::chrono::steady_clock::now() +
        std::chrono::seconds(10);

    while (std::chrono::steady_clock::now() < endTime)
    {
        renderer->Display();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(1));
    }

    std::cout << "\nStopping...\n";

    std::cout << "Stopping Capture...\n";
    capture.Stop();

    std::cout << "Stopping Consumer...\n";
    consumer.Stop();

    std::cout << "Disconnecting...\n";
    client.Disconnect();

    std::cout << "Done.\n";

    std::cout
        << "Processed Frames : "
        << consumer.ProcessedFrames()
        << "\n";

    std::cout
        << "\nPipeline stopped successfully.\n";

    return 0;
}