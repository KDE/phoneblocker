#include "mainwindow.h"

#include <bb/cascades/Application>

using namespace bb::cascades;

Q_DECL_EXPORT int main(int argc, char **argv)
{
    Application app(argc, argv);
    MainWindow mainWindow;
    return Application::exec();
}
