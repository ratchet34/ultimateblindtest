#include <QApplication>
#include <QString>
#include <QMessageBox>

#include <string.h>
#include <vector>

#include "mainwindow.h"
#include "database.h"

using namespace std;

int main(int argc, char *argv[])

{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    MainWindow window;
    window.setCategories(getAllCat());
    window.connectTcp();
    window.show();
    return app.exec();
}

/*    QString url = QString::fromStdString(getFieldFromId("link", getCatRandomId("t_cat_cartoon")));

    window.startSong(30, url);*/
