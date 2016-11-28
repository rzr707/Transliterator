#include <QApplication>
#include <QStyleFactory>
#include "mainwindow.h"

int main(int argc, char** argv) {
	
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("fusion"));

    MainWindow wnd;
    app.setWindowIcon(wnd.style()->standardIcon(QStyle::SP_DialogApplyButton));
    wnd.show();

    return app.exec();
}
