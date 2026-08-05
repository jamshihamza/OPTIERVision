#pragma once

namespace optier
{

    struct PreprocessMetadata
    {
        //
        // Original frame size.
        //
        int OriginalWidth = 0;

        int OriginalHeight = 0;

        //
        // Model input size.
        //
        int ModelWidth = 640;

        int ModelHeight = 640;

        //
        // Resize scale.
        //
        float Scale = 1.0f;

        //
        // Letterbox padding.
        //
        int PadLeft = 0;

        int PadTop = 0;

        int PadRight = 0;

        int PadBottom = 0;
    };

} // namespace optier