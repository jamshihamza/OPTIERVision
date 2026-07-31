#include "pch.h"

#include <iostream>

#include <optier/Camera.h>

int main()
{
    using namespace optier;

    std::cout << "=========================================\n";
    std::cout << "       OPTIER Vision Sandbox Test\n";
    std::cout << "=========================================\n\n";

    //----------------------------------------------------------
    // Create Device Information
    //----------------------------------------------------------

    DeviceInfo deviceInfo;

    deviceInfo.Id = "CAM001";
    deviceInfo.Name = "Front Gate Camera";
    deviceInfo.IPAddress = "192.168.1.10";
    deviceInfo.Port = 554;
    deviceInfo.Username = "admin";
    deviceInfo.Password = "admin";
    deviceInfo.Manufacturer = "OPTIER";
    deviceInfo.Model = "IPC-AI-4MP";
    deviceInfo.FirmwareVersion = "1.0.0";
    deviceInfo.MacAddress = "00:11:22:33:44:55";

    //----------------------------------------------------------
    // Create Camera Information
    //----------------------------------------------------------

    CameraInfo cameraInfo;

    cameraInfo.RtspUrl =
        "rtsp://admin:admin@192.168.1.10:554/main";

    cameraInfo.MainStreamUrl =
        "rtsp://192.168.1.10/main";

    cameraInfo.SubStreamUrl =
        "rtsp://192.168.1.10/sub";

    cameraInfo.SnapshotUrl =
        "http://192.168.1.10/snapshot.jpg";

    cameraInfo.SupportsPTZ = true;
    cameraInfo.SupportsAudio = true;

    cameraInfo.MaxWidth = 2560;
    cameraInfo.MaxHeight = 1440;
    cameraInfo.MaxFPS = 30;

    cameraInfo.SupportedAICapabilities =
    {
        AICapability::FaceDetection,
        AICapability::FaceRecognition,
        AICapability::LicensePlateRecognition,
        AICapability::LineCrossing
    };

    //----------------------------------------------------------
    // Create Camera
    //----------------------------------------------------------

    Camera camera(deviceInfo, cameraInfo);

    std::cout << "[1] Camera object created.\n\n";

    //----------------------------------------------------------
    // Device Information
    //----------------------------------------------------------

    const DeviceInfo& info = camera.GetInfo();

    std::cout << "[2] Device Information\n";

    std::cout << "ID            : " << info.Id << '\n';
    std::cout << "Name          : " << info.Name << '\n';
    std::cout << "IP Address    : " << info.IPAddress << '\n';
    std::cout << "Port          : " << info.Port << '\n';
    std::cout << "Manufacturer  : " << info.Manufacturer << '\n';
    std::cout << "Model         : " << info.Model << '\n';
    std::cout << "Firmware      : " << info.FirmwareVersion << '\n';
    std::cout << "MAC Address   : " << info.MacAddress << '\n';

    //----------------------------------------------------------
    // Connect
    //----------------------------------------------------------

    std::cout << "\n[3] Connecting...\n";

    bool connected = camera.Connect();

    std::cout << "Connected : "
        << std::boolalpha
        << connected
        << '\n';

    //----------------------------------------------------------
    // Camera Information
    //----------------------------------------------------------

    const CameraInfo& camInfo =
        camera.GetCameraInfo();

    std::cout << "\n[4] Camera Information\n";

    std::cout << "RTSP URL       : " << camInfo.RtspUrl << '\n';
    std::cout << "Main Stream    : " << camInfo.MainStreamUrl << '\n';
    std::cout << "Sub Stream     : " << camInfo.SubStreamUrl << '\n';
    std::cout << "Snapshot URL   : " << camInfo.SnapshotUrl << '\n';

    std::cout << "PTZ            : "
        << camInfo.SupportsPTZ
        << '\n';

    std::cout << "Audio          : "
        << camInfo.SupportsAudio
        << '\n';

    std::cout << "Resolution     : "
        << camInfo.MaxWidth
        << " x "
        << camInfo.MaxHeight
        << '\n';

    std::cout << "Max FPS        : "
        << camInfo.MaxFPS
        << '\n';

    std::cout << "AI Features    : "
        << camInfo.SupportedAICapabilities.size()
        << '\n';

    //----------------------------------------------------------
    // Camera Status
    //----------------------------------------------------------

    const CameraStatus& status =
        camera.GetCameraStatus();

    std::cout << "\n[5] Runtime Status\n";

    std::cout << "Connection     : "
        << static_cast<int>(status.ConnectionState)
        << '\n';

    std::cout << "Streaming      : "
        << status.IsStreaming
        << '\n';

    std::cout << "Recording      : "
        << status.IsRecording
        << '\n';

    std::cout << "AI Running     : "
        << status.IsAIRunning
        << '\n';

    std::cout << "FPS            : "
        << status.CurrentFPS
        << '\n';

    std::cout << "Bitrate        : "
        << status.CurrentBitrate
        << '\n';

    std::cout << "Dropped Frames : "
        << status.DroppedFrames
        << '\n';

    //----------------------------------------------------------
    // Disconnect
    //----------------------------------------------------------

    std::cout << "\n[6] Disconnecting...\n";

    camera.Disconnect();

    std::cout << "Connection State : "
        << static_cast<int>(camera.GetConnectionState())
        << '\n';

    std::cout << "\n=========================================\n";
    std::cout << "Sandbox Test Completed Successfully\n";
    std::cout << "=========================================\n";

    return 0;
}