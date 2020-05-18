#include <Core/Application.h>

int main()
{
    Application discretia;
    discretia.Init();

    while (discretia.IsRunning())
    {
        discretia.Update();
    }

    return 0;
}