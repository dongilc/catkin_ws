/********************************************************************************
** Form generated from reading UI file 'me_exp_2020.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ME_EXP_2020_H
#define UI_ME_EXP_2020_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qwt_slider.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QPushButton *Button_connect;
    QPushButton *Button_disconnect;
    QLabel *label_6;
    QCheckBox *checkbox_remember_settings;
    QCheckBox *checkbox_use_environment;
    QLineEdit *lineEdit_host;
    QLineEdit *lineEdit_master;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QSplitter *splitter_4;
    QPushButton *Button_reset;
    QPushButton *pushButton_apply;
    QPushButton *pushButton_quit;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter_6;
    QWidget *widget;
    QRadioButton *Button_lineEdit;
    QWidget *widget_2;
    QRadioButton *Button_Silder;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *Button_FK;
    QSplitter *splitter;
    QLabel *label;
    QLineEdit *lineEdit_th1;
    QwtSlider *Slider_th1;
    QSplitter *splitter_2;
    QLabel *label_2;
    QLineEdit *lineEdit_th2;
    QwtSlider *Slider_th2;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *Button_IK;
    QSplitter *splitter_3;
    QLabel *label_3;
    QLineEdit *lineEdit_position_x;
    QwtSlider *Slider_positio_x;
    QSplitter *splitter_5;
    QLabel *label_4;
    QLineEdit *lineEdit_position_y;
    QwtSlider *Slider_position_y;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_3;
    QListView *view_logging;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(900, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setEnabled(true);
        label_5->setMinimumSize(QSize(170, 25));
        label_5->setMaximumSize(QSize(170, 25));
        label_5->setFrameShape(QFrame::StyledPanel);
        label_5->setFrameShadow(QFrame::Raised);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);

        Button_connect = new QPushButton(groupBox_4);
        Button_connect->setObjectName(QString::fromUtf8("Button_connect"));
        Button_connect->setMinimumSize(QSize(90, 25));
        Button_connect->setMaximumSize(QSize(90, 25));

        gridLayout_3->addWidget(Button_connect, 3, 4, 1, 1);

        Button_disconnect = new QPushButton(groupBox_4);
        Button_disconnect->setObjectName(QString::fromUtf8("Button_disconnect"));
        Button_disconnect->setMinimumSize(QSize(90, 25));
        Button_disconnect->setMaximumSize(QSize(90, 25));

        gridLayout_3->addWidget(Button_disconnect, 3, 5, 1, 1);

        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setEnabled(true);
        label_6->setMinimumSize(QSize(170, 25));
        label_6->setMaximumSize(QSize(170, 25));
        label_6->setFrameShape(QFrame::StyledPanel);
        label_6->setFrameShadow(QFrame::Raised);
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        checkbox_remember_settings = new QCheckBox(groupBox_4);
        checkbox_remember_settings->setObjectName(QString::fromUtf8("checkbox_remember_settings"));
        checkbox_remember_settings->setMinimumSize(QSize(233, 25));
        checkbox_remember_settings->setMaximumSize(QSize(233, 25));
        checkbox_remember_settings->setLayoutDirection(Qt::LeftToRight);

        gridLayout_3->addWidget(checkbox_remember_settings, 1, 3, 1, 3);

        checkbox_use_environment = new QCheckBox(groupBox_4);
        checkbox_use_environment->setObjectName(QString::fromUtf8("checkbox_use_environment"));
        checkbox_use_environment->setMinimumSize(QSize(233, 25));
        checkbox_use_environment->setMaximumSize(QSize(233, 25));
        checkbox_use_environment->setLayoutDirection(Qt::LeftToRight);

        gridLayout_3->addWidget(checkbox_use_environment, 0, 3, 1, 3);

        lineEdit_host = new QLineEdit(groupBox_4);
        lineEdit_host->setObjectName(QString::fromUtf8("lineEdit_host"));
        lineEdit_host->setEnabled(true);
        lineEdit_host->setMinimumSize(QSize(300, 25));
        lineEdit_host->setMaximumSize(QSize(300, 25));

        gridLayout_3->addWidget(lineEdit_host, 1, 1, 1, 1);

        lineEdit_master = new QLineEdit(groupBox_4);
        lineEdit_master->setObjectName(QString::fromUtf8("lineEdit_master"));
        lineEdit_master->setEnabled(true);
        lineEdit_master->setMinimumSize(QSize(300, 25));
        lineEdit_master->setMaximumSize(QSize(300, 25));

        gridLayout_3->addWidget(lineEdit_master, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 2, 1, 1);


        gridLayout->addWidget(groupBox_4, 0, 0, 1, 1);

        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setMinimumSize(QSize(882, 43));
        widget_3->setMaximumSize(QSize(880, 43));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(498, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        splitter_4 = new QSplitter(widget_3);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        splitter_4->setOrientation(Qt::Horizontal);
        Button_reset = new QPushButton(splitter_4);
        Button_reset->setObjectName(QString::fromUtf8("Button_reset"));
        Button_reset->setMinimumSize(QSize(90, 25));
        Button_reset->setMaximumSize(QSize(90, 25));
        splitter_4->addWidget(Button_reset);
        pushButton_apply = new QPushButton(splitter_4);
        pushButton_apply->setObjectName(QString::fromUtf8("pushButton_apply"));
        pushButton_apply->setMinimumSize(QSize(90, 25));
        pushButton_apply->setMaximumSize(QSize(90, 25));
        splitter_4->addWidget(pushButton_apply);
        pushButton_quit = new QPushButton(splitter_4);
        pushButton_quit->setObjectName(QString::fromUtf8("pushButton_quit"));
        pushButton_quit->setMinimumSize(QSize(90, 25));
        pushButton_quit->setMaximumSize(QSize(90, 25));
        splitter_4->addWidget(pushButton_quit);

        horizontalLayout_2->addWidget(splitter_4);


        gridLayout->addWidget(widget_3, 3, 0, 1, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter_6 = new QSplitter(groupBox_3);
        splitter_6->setObjectName(QString::fromUtf8("splitter_6"));
        splitter_6->setOrientation(Qt::Horizontal);
        widget = new QWidget(splitter_6);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(50, 25));
        widget->setMaximumSize(QSize(50, 25));
        splitter_6->addWidget(widget);
        Button_lineEdit = new QRadioButton(splitter_6);
        Button_lineEdit->setObjectName(QString::fromUtf8("Button_lineEdit"));
        Button_lineEdit->setMinimumSize(QSize(130, 25));
        Button_lineEdit->setMaximumSize(QSize(130, 25));
        splitter_6->addWidget(Button_lineEdit);
        widget_2 = new QWidget(splitter_6);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(255, 25));
        widget_2->setMaximumSize(QSize(255, 25));
        splitter_6->addWidget(widget_2);
        Button_Silder = new QRadioButton(splitter_6);
        Button_Silder->setObjectName(QString::fromUtf8("Button_Silder"));
        Button_Silder->setMinimumSize(QSize(120, 25));
        Button_Silder->setMaximumSize(QSize(120, 25));
        splitter_6->addWidget(Button_Silder);

        verticalLayout->addWidget(splitter_6);

        frame = new QFrame(groupBox_3);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(858, 0));
        frame->setMaximumSize(QSize(858, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        Button_FK = new QRadioButton(frame);
        Button_FK->setObjectName(QString::fromUtf8("Button_FK"));
        Button_FK->setMinimumSize(QSize(758, 25));
        Button_FK->setMaximumSize(QSize(758, 25));

        verticalLayout_2->addWidget(Button_FK);

        splitter = new QSplitter(frame);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        label = new QLabel(splitter);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(true);
        label->setMinimumSize(QSize(80, 25));
        label->setMaximumSize(QSize(80, 20));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setFrameShape(QFrame::StyledPanel);
        label->setFrameShadow(QFrame::Raised);
        label->setAlignment(Qt::AlignCenter);
        splitter->addWidget(label);
        lineEdit_th1 = new QLineEdit(splitter);
        lineEdit_th1->setObjectName(QString::fromUtf8("lineEdit_th1"));
        lineEdit_th1->setMinimumSize(QSize(70, 25));
        lineEdit_th1->setMaximumSize(QSize(70, 25));
        lineEdit_th1->setAlignment(Qt::AlignCenter);
        splitter->addWidget(lineEdit_th1);
        Slider_th1 = new QwtSlider(splitter);
        Slider_th1->setObjectName(QString::fromUtf8("Slider_th1"));
        Slider_th1->setUpperBound(180);
        Slider_th1->setScaleMaxMajor(18);
        Slider_th1->setScaleMaxMinor(10);
        Slider_th1->setTotalSteps(1800u);
        Slider_th1->setSingleSteps(1u);
        Slider_th1->setTracking(false);
        Slider_th1->setOrientation(Qt::Horizontal);
        splitter->addWidget(Slider_th1);

        verticalLayout_2->addWidget(splitter);

        splitter_2 = new QSplitter(frame);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(splitter_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(80, 25));
        label_2->setMaximumSize(QSize(80, 25));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setFrameShape(QFrame::StyledPanel);
        label_2->setFrameShadow(QFrame::Raised);
        label_2->setAlignment(Qt::AlignCenter);
        splitter_2->addWidget(label_2);
        lineEdit_th2 = new QLineEdit(splitter_2);
        lineEdit_th2->setObjectName(QString::fromUtf8("lineEdit_th2"));
        lineEdit_th2->setMaximumSize(QSize(70, 25));
        lineEdit_th2->setAlignment(Qt::AlignCenter);
        splitter_2->addWidget(lineEdit_th2);
        Slider_th2 = new QwtSlider(splitter_2);
        Slider_th2->setObjectName(QString::fromUtf8("Slider_th2"));
        Slider_th2->setLowerBound(-155);
        Slider_th2->setUpperBound(155);
        Slider_th2->setScaleMaxMinor(10);
        Slider_th2->setScaleStepSize(20);
        Slider_th2->setTotalSteps(3100u);
        Slider_th2->setOrientation(Qt::Horizontal);
        splitter_2->addWidget(Slider_th2);

        verticalLayout_2->addWidget(splitter_2);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(groupBox_3);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(858, 0));
        frame_2->setMaximumSize(QSize(858, 16777215));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        Button_IK = new QRadioButton(frame_2);
        Button_IK->setObjectName(QString::fromUtf8("Button_IK"));
        Button_IK->setEnabled(true);
        Button_IK->setMinimumSize(QSize(758, 25));
        Button_IK->setMaximumSize(QSize(758, 25));

        verticalLayout_4->addWidget(Button_IK);

        splitter_3 = new QSplitter(frame_2);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(splitter_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(80, 25));
        label_3->setMaximumSize(QSize(80, 25));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setFrameShape(QFrame::StyledPanel);
        label_3->setFrameShadow(QFrame::Raised);
        label_3->setAlignment(Qt::AlignCenter);
        splitter_3->addWidget(label_3);
        lineEdit_position_x = new QLineEdit(splitter_3);
        lineEdit_position_x->setObjectName(QString::fromUtf8("lineEdit_position_x"));
        lineEdit_position_x->setMinimumSize(QSize(70, 25));
        lineEdit_position_x->setMaximumSize(QSize(70, 25));
        lineEdit_position_x->setAlignment(Qt::AlignCenter);
        splitter_3->addWidget(lineEdit_position_x);
        Slider_positio_x = new QwtSlider(splitter_3);
        Slider_positio_x->setObjectName(QString::fromUtf8("Slider_positio_x"));
        Slider_positio_x->setLowerBound(-330);
        Slider_positio_x->setUpperBound(330);
        Slider_positio_x->setScaleMaxMinor(6);
        Slider_positio_x->setScaleStepSize(60);
        Slider_positio_x->setTotalSteps(660u);
        Slider_positio_x->setOrientation(Qt::Horizontal);
        splitter_3->addWidget(Slider_positio_x);

        verticalLayout_4->addWidget(splitter_3);

        splitter_5 = new QSplitter(frame_2);
        splitter_5->setObjectName(QString::fromUtf8("splitter_5"));
        splitter_5->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(splitter_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(80, 25));
        label_4->setMaximumSize(QSize(80, 25));
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setFrameShape(QFrame::StyledPanel);
        label_4->setFrameShadow(QFrame::Raised);
        label_4->setAlignment(Qt::AlignCenter);
        splitter_5->addWidget(label_4);
        lineEdit_position_y = new QLineEdit(splitter_5);
        lineEdit_position_y->setObjectName(QString::fromUtf8("lineEdit_position_y"));
        lineEdit_position_y->setMaximumSize(QSize(70, 25));
        lineEdit_position_y->setAlignment(Qt::AlignCenter);
        splitter_5->addWidget(lineEdit_position_y);
        Slider_position_y = new QwtSlider(splitter_5);
        Slider_position_y->setObjectName(QString::fromUtf8("Slider_position_y"));
        Slider_position_y->setUpperBound(330);
        Slider_position_y->setScaleStepSize(30);
        Slider_position_y->setTotalSteps(330u);
        Slider_position_y->setSingleSteps(1u);
        Slider_position_y->setOrientation(Qt::Horizontal);
        splitter_5->addWidget(Slider_position_y);

        verticalLayout_4->addWidget(splitter_5);


        verticalLayout->addWidget(frame_2);


        gridLayout->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout_3 = new QVBoxLayout(groupBox_5);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        view_logging = new QListView(groupBox_5);
        view_logging->setObjectName(QString::fromUtf8("view_logging"));

        verticalLayout_3->addWidget(view_logging);


        gridLayout->addWidget(groupBox_5, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "ROS Master", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Ros Master Url", 0, QApplication::UnicodeUTF8));
        Button_connect->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        Button_disconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Ros IP(Host)", 0, QApplication::UnicodeUTF8));
        checkbox_remember_settings->setText(QApplication::translate("MainWindow", "Remember settings on startup", 0, QApplication::UnicodeUTF8));
        checkbox_use_environment->setText(QApplication::translate("MainWindow", "Use environment variables", 0, QApplication::UnicodeUTF8));
        Button_reset->setText(QApplication::translate("MainWindow", "Reset", 0, QApplication::UnicodeUTF8));
        pushButton_apply->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
        pushButton_quit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Control", 0, QApplication::UnicodeUTF8));
        Button_lineEdit->setText(QApplication::translate("MainWindow", "Line Edit Mode", 0, QApplication::UnicodeUTF8));
        Button_Silder->setText(QApplication::translate("MainWindow", "Slider Mode", 0, QApplication::UnicodeUTF8));
        Button_FK->setText(QApplication::translate("MainWindow", "Forward Kinematics", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "th1", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "th2", 0, QApplication::UnicodeUTF8));
        Button_IK->setText(QApplication::translate("MainWindow", "Inverse Kinematics", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Position X", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Position Y", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Logging", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ME_EXP_2020_H
