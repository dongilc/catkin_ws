/**
 * @file /include/qtros/main_window.hpp
 *
 * @brief Qt based gui for qtros.
 *
 * @date 09 2020
 *
 * @author Syong 
 **/
#ifndef qtros_MAIN_WINDOW_H
#define qtros_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/
#include <QtGui/QMainWindow>
#include "ui_me_exp_2020.h"
#include "qnode.hpp"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace qtros {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();

	void ReadSettings(); // Load up qt program settings at startup
	void WriteSettings(); // Save qt program settings when closing

	void closeEvent(QCloseEvent *event); // Overloaded function
	void showNoMasterMessage();

public Q_SLOTS:
	/******************************************
	** Auto-connections (connectSlotsByName())
	*******************************************/

	//void on_actionAbout_triggered();
	void on_button_connect_clicked(bool check);
  	void on_button_disconnect_clicked(bool check);
	void on_checkbox_use_environment_stateChanged(int state);
	void on_button_reset_clicked(bool check);
	void on_button_apply_clicked(bool check);


    /******************************************
    ** Manual connections
    *******************************************/

    void updateLoggingView(); // no idea why this can't connect automatically

private:
	Ui::MainWindow ui;
	QNode qnode;
};

}  // namespace qtros

#endif // qtros_MAIN_WINDOW_H
