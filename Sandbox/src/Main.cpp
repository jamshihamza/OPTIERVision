#include <optier/Application.h>
#include <optier/FileSystem.h>

int main()
{
    optier::Application application;
    optier::FileSystem::CreateDirectory("logs");

    if (!application.Initialize())
    {
        return -1;
    }

    application.Run();
    application.Shutdown();

    return 0;
}