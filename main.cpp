#include <iostream>
#include "crosshair.h"
#include <windows.h>
#include <winuser.h>
#include <fstream>
#include <thread>
#include <QApplication>

int i = 0;

void check_key(QApplication* app)
{
    while(true)
    {
        if(GetAsyncKeyState(VK_RSHIFT))
        {
            i++;
            app->quit();
            ExitProcess(0);
        }
    }
}

int main(int argc, char *argv[])
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    QApplication app(argc, argv);

    // Default crosshair color
    struct RGBA color;

    // Create class instance
    crosshair chr(color, nullptr, 16, 2, 3);
    chr.show();

    std::thread thread_(check_key, &app);

    // Execute the application
    return app.exec();
}


