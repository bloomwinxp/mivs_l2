#include "stream_of_event.h"


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    Stream *stream = new Stream();
    mainWindow.setCentralWidget(stream);
    mainWindow.show();
    return app.exec();
}