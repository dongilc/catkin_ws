/**
 * @file /src/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date 09 2020
 *
 * @author Syong 
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QApplication>
#include "../include/qtros/main_window.hpp"

/*****************************************************************************
** Main
*****************************************************************************/

int main(int argc, char **argv) {

    /*********************
    ** Qt
    **********************/
    QApplication app(argc, argv);
    qtros::MainWindow w(argc,argv);
    w.show();
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    int result = app.exec();

	return result;
}
