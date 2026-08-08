#include "pch.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include <optier/OpenCVRTSPClient.h>

#include <optier/FrameQueue.h>
#include <optier/CaptureThread.h>
#include <optier/ConsumerThread.h>
#include <optier/FrameProcessorPipeline.h>

#include <optier/YOLODetector.h>
#include <optier/YOLODetectorProcessor.h>

#include <optier/VideoRenderer.h>
#include <optier/SnapshotProcessor.h>
#include <optier/OverlayProcessor.h>
#include <optier/DetectionMapperProcessor.h>

using namespace optier;

int main()
{
    std::cout << "========================================\n";
    std::cout << " OPTIER Vision\n";
    std::cout << "========================================\n\n";

    //
    // -------------------------------------------------
    // Initialize YOLO Detector
    // -------------------------------------------------
    //
    std::cout << "Loading YOLO model...\n";

    auto detector =
        std::make_shared<YOLODetector>(
            "libraries/models/yolov8n.onnx");

    if (!detector->Initialize())
    {
        std::cout
            << "ERROR : Failed to initialize YOLO detector.\n";

        return -1;
    }

    std::cout
        << "YOLO detector initialized successfully.\n\n";

    //
    // -------------------------------------------------
    // RTSP Client
    // -------------------------------------------------
    //
    OpenCVRTSPClient client;

    const std::string rtspUrl =
        "rtsp://admin:Opt$0987@192.168.1.100:80/rtsp/streaming?channel=09&subtype=0";

    std::cout
        << "Connecting to RTSP stream...\n";

    if (!client.Connect(rtspUrl))
    {
        std::cout
            << "Failed to connect to RTSP stream.\n";

        detector->Shutdown();

        return -1;
    }

    std::cout
        << "Connected successfully.\n";

    //
    // -------------------------------------------------
    // Frame Queue
    // -------------------------------------------------
    //
    FrameQueue queue(30);

    //
    // -------------------------------------------------
    // Processing Pipeline
    // -------------------------------------------------
    //
    FrameProcessorPipeline pipeline;

    auto yoloProcessor =
        std::make_shared<YOLODetectorProcessor>(
            detector);

    auto detectionMapper =
        std::make_shared<DetectionMapperProcessor>();

    auto overlayProcessor =
        std::make_shared<OverlayProcessor>();

    auto renderer =
        std::make_shared<VideoRenderer>(
            "OPTIER Vision");

    auto snapshotProcessor =
        std::make_shared<SnapshotProcessor>(
            "snapshots");
    auto performanceMonitor =
        std::make_shared<PerformanceMonitorProcessor>();

    //
    // Processing Order
    //
    pipeline.AddProcessor(
        yoloProcessor);

    pipeline.AddProcessor(
       detectionMapper);

  pipeline.AddProcessor(
       overlayProcessor);

    pipeline.AddProcessor(
        renderer);

    pipeline.AddProcessor(
        snapshotProcessor);

   // pipeline.AddProcessor(
		//performanceMonitor);    

    //
    // -------------------------------------------------
    // Threads
    // -------------------------------------------------
    //
    CaptureThread capture(
        client,
        queue);

    ConsumerThread consumer(
        queue,
        pipeline);

    std::cout
        << "Starting CaptureThread...\n";

    capture.Start();

    std::cout
        << "Starting ConsumerThread...\n";

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

    //
    // -------------------------------------------------
    // Shutdown
    // -------------------------------------------------
    //
    std::cout
        << "\nStopping...\n";

    capture.Stop();

    consumer.Stop();

    client.Disconnect();

    detector->Shutdown();

    std::cout << "\n";
    std::cout
        << "Processed Frames : "
        << consumer.ProcessedFrames()
        << "\n";

    std::cout
        << "\nPipeline stopped successfully.\n";

    return 0;
}