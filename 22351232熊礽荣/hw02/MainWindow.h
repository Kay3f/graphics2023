#pragma once

#include <QtWidgets/QMainWindow>
#include <QKeyEvent>

#include "MainWidget.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool fullscreen;
    //��������¼�
    void keyPressEvent(QKeyEvent* e);

private:
    MainWidget* mainWidget;
    Ui::MainWindowClass ui;
};
