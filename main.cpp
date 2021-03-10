#include "Controller.h"
#include "View/MainWindow.h"
#include "Model/CharacterSheet.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);

    MainWindow view;
    CharacterSheet model;
    Controller controller;

    controller.setView(&view);
    controller.setModel(&model);

    view.setController(&controller);
    view.show();

    application.setStyle("fusion");
    application.setFont(QFont("Helvetica", 10));

    return QApplication::exec();
}
