#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "pin_map.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void button_pressed();
    void button_released();

    void on_pRESET_clicked();

    void on_pRESET_2_clicked();

private:

    Ui::MainWindow *ui;

    QMap<QObject*, Button_t> button_map;
};

#endif // MAINWINDOW_H
