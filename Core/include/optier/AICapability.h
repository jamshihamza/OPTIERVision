#pragma once

namespace optier
{

    enum class AICapability
    {
        FaceDetection,
        FaceRecognition,

        LicensePlateDetection,
        LicensePlateRecognition,

        LineCrossing,
        IntrusionDetection,
        RegionEntrance,
        RegionExit,

        ObjectCounting,
        CrowdDensity,
        HeatMap,
        QueueManagement,

        SoundDetection,

        PedestrianClassification,
        VehicleClassification,
        NonMotorVehicleClassification
    };

}