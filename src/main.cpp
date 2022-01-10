#include "../include/demo_application.h"

#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    (void)nCmdShow;
    (void)lpCmdLine;
    (void)hPrevInstance;

    DemoApplication app;
    app.initialize(hInstance, ysContextObject::DeviceAPI::DirectX11);
    app.run();
    app.destroy();

    return 0;
}
