#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include "UI/UI.h"
#include "GUI/GUI.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    GUI window;
    window.show();

    return QApplication::exec();

    UI ui;
    ui.run();
    return 0;
}
