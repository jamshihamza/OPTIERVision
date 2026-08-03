#include "pch.h"

#include <optier/DummyDetector.h>

namespace optier
{

    DetectionCollection
        DummyDetector::Detect(
            const VideoFrame& frame)
    {
        DetectionCollection collection;

        //
        // Copy frame information
        //
        collection.FrameNumber =
            frame.FrameNumber;

        collection.Timestamp =
            frame.Timestamp;

        //
        // Demo Detection 1
        //
        DetectionResult car;

        car.ClassId = 0;
        car.ClassName = "Car";

        car.Confidence = 0.98f;

        car.X = 200;
        car.Y = 120;
        car.Width = 260;
        car.Height = 180;

        collection.Results.push_back(
            std::move(car));

        //
        // Demo Detection 2
        //
        DetectionResult person;

        person.ClassId = 1;
        person.ClassName = "Person";

        person.Confidence = 0.95f;

        person.X = 520;
        person.Y = 180;
        person.Width = 90;
        person.Height = 220;

        collection.Results.push_back(
            std::move(person));

        //
        // Demo Detection 3
        //
        DetectionResult motorcycle;

        motorcycle.ClassId = 2;
        motorcycle.ClassName = "Motorcycle";

        motorcycle.Confidence = 0.91f;

        motorcycle.X = 900;
        motorcycle.Y = 260;
        motorcycle.Width = 180;
        motorcycle.Height = 120;

        collection.Results.push_back(
            std::move(motorcycle));

        return collection;
    }

} // namespace optier