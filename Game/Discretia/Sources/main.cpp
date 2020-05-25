#include <Core/Application.h>

int main()
{
    Application discretia;
    discretia.InitFromPrototype();
    discretia.Run();

    while (discretia.IsRunning())
    {
        discretia.Update();
    }

    return 0;
}