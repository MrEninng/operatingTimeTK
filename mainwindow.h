#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QIcon>

struct exl_fills;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QIcon *icon;

    struct exl_fills {
        struct input {
            double E7,E8,E9,E10,E11,E12;
            double E21,E22;
            double E29,E30;
        } in;
        struct output {
                double I10,I11,I12;
                double G16;
                double I21,I22;
                double G24;
                double I30;
                double G32;
                double final_G35;
        } out;
    } fills;


    void input();
    void calculate();
    void fillValues();


private slots:
    void debugSlot() {qDebug() << "I'm, Debuging"; }
    void constantsMenu();
    void calculatePushButtonCkicked();
    void clearAction();
    void exitAction();
    void aboutQtAction();
};



#endif // MAINWINDOW_H
