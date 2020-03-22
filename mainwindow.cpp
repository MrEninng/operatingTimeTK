#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QString"
#include <QValidator>
#include <QRegExp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    icon = new QIcon();
    icon->addFile(":/imgs/burenie.png");
    setWindowIcon(*icon);

    QRegExp regExpWordInput("[0-9 | .]*");//using only digits and dot;
    QRegExpValidator *myValidator = new QRegExpValidator(regExpWordInput, this);
    ui->lineEditE7->setValidator(myValidator);
    ui->lineEditE8->setValidator(myValidator);
    ui->lineEditE9->setValidator(myValidator);
    ui->lineEditE10->setValidator(myValidator);
    ui->lineEditE11->setValidator(myValidator);
    ui->lineEditE12->setValidator(myValidator);
    ui->lineEditE21->setValidator(myValidator);
    ui->lineEditE22->setValidator(myValidator);
    ui->lineEditE29->setValidator(myValidator);
    ui->lineEditE30->setValidator(myValidator);

    connect(ui->constantAction, SIGNAL(triggered(bool)), this, SLOT(constantsMenu()));
    // ИДЕЯ БЕЗ КНОПКИ
    //connect(ui->lineEdit, SIGNAL(editingFinished()), this, SLOT(debugSlot()));
    connect(ui->calculatePushButton, SIGNAL(clicked(bool)),this, SLOT(calculatePushButtonCkicked()));

    connect(ui->exitAction, SIGNAL(triggered(bool)), this, SLOT(exitAction()));
    connect(ui->clearAction, SIGNAL(triggered(bool)), this, SLOT(clearAction()));
    connect(ui->aboutQtAction, SIGNAL(triggered(bool)), this, SLOT(aboutQtAction()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::constantsMenu()
{
    QMessageBox::information(this,"Константы","УБТ 178 =158 кг.п.м\n"
                                              "ТБТ 89 = 33 кг.п.м\n"
                                              "СБТ - 89 = 19,3кг.п.м\n"
                                              "ТБПК -127 = 31,5 кг.п.м.");
}

void MainWindow::calculatePushButtonCkicked()
{
    // Reading values from input lineEdits
    input();
    // Calculating values for output lineEdits
    calculate();
    // Filling output lineEdits
    fillValues();
}

void MainWindow::input()
{
    // Cheking empty lineEdits

    // First Block
    if (ui->lineEditE7->text().isEmpty()) {
        fills.in.E7 = 0;
        ui->lineEditE7->setText("0");
    } else {
        fills.in.E7 = ui->lineEditE7->text().toDouble();
    }

    if (ui->lineEditE8->text().isEmpty()) {
        fills.in.E8 = 0;
        ui->lineEditE8->setText("0");
    } else {
        fills.in.E8 = ui->lineEditE8->text().toDouble();
    }
    if (ui->lineEditE9->text().isEmpty()) {
        fills.in.E9 = 0;
        ui->lineEditE9->setText("0");
    } else {
        fills.in.E9 = ui->lineEditE9->text().toDouble();
    }
    if (ui->lineEditE9->text().isEmpty()) {
        fills.in.E9 = 0;
        ui->lineEditE9->setText("0");
    } else {
        fills.in.E9 = ui->lineEditE9->text().toDouble();
    }

    if (ui->lineEditE10->text().isEmpty()) {
        fills.in.E10 = 0;
        ui->lineEditE10->setText("0");
    } else {
        fills.in.E10 = ui->lineEditE10->text().toDouble();
    }

    if (ui->lineEditE11->text().isEmpty()) {
        fills.in.E11 = 0;
        ui->lineEditE11->setText("0");
    } else {
        fills.in.E11 = ui->lineEditE11->text().toDouble();
    }

    if (ui->lineEditE12->text().isEmpty()) {
        fills.in.E12 = 0;
        ui->lineEditE12->setText("0");
    } else {
        fills.in.E12 = ui->lineEditE12->text().toDouble();
    }

    // Second Block
    fills.in.E21 = ui->lineEditE21->text().toDouble();
    fills.in.E22 = ui->lineEditE22->text().toDouble();

    // Third Block
    fills.in.E29 = ui->lineEditE29->text().toDouble();
    fills.in.E30 = ui->lineEditE30->text().toDouble();
}
void MainWindow::calculate()
{
    fills.out.I10 = ((7.85 - fills.in.E8) / 7.85) * fills.in.E9;
    fills.out.I11 = fills.in.E11 * ((7.85 - fills.in.E8) / 7.85);
    fills.out.I12 = (fills.in.E10 * (fills.out.I10 - fills.out.I11)) / 2;

    fills.out.G16 = 2 * ((fills.out.I11 * fills.in.E7*(fills.in.E7 + 16.6)) + ( 2 * fills.in.E7 * (fills.in.E12 + fills.out.I12))) / 1000000;

    const long double CALCULATION_COEF = 0.000000981;
    // For calculating of formuls with long double constant use temp Variable
    {
        long double tempLongDoubleI21 = 0;
        tempLongDoubleI21 = CALCULATION_COEF * (((fills.in.E21 * fills.out.I11)
                            * (fills.in.E21 + 18.8)) + ((4 * fills.in.E21)
                            * (fills.in.E12 + fills.out.I12)));
        fills.out.I21 = static_cast<double>(tempLongDoubleI21);
    }


    {
        long double tempLongDoubleI22 = 0;
        tempLongDoubleI22 = CALCULATION_COEF * (((fills.out.I11 * fills.in.E22)
                           *(fills.in.E22 + 18.8)) + ((4 * fills.in.E22)*(fills.in.E12 + fills.out.I12)));
        fills.out.I22 = static_cast<double>(tempLongDoubleI22);
    }

    fills.out.G24 = 3 * (fills.out.I22 - fills.out.I21);


    fills.out.I30 = fills.in.E30 * ((7.85 - fills.in.E8) / 7.85);

    {
        long double tempLongDoubleG32 = 0;
        tempLongDoubleG32 = (CALCULATION_COEF * (((fills.out.I30 * fills.in.E29)
                            * (fills.in.E29 + 12)) + ((4 * fills.in.E29) * fills.in.E12))) / 2;
        fills.out.G32 = static_cast<double>(tempLongDoubleG32);
    }

    fills.out.final_G35 = fills.out.G16 + fills.out.G24 + fills.out.G32;
}

void MainWindow::fillValues()
{
    ui->outLineEditI10->setText(QString::number(fills.out.I10));
    ui->outLineEditI11->setText(QString::number(fills.out.I11));
    ui->outLineEditI12->setText(QString::number(fills.out.I12));

    ui->outLineEditG16->setText(QString::number(fills.out.G16));

    ui->outLineEditI21->setText(QString::number(fills.out.I21));
    ui->outLineEditI22->setText(QString::number(fills.out.I22));

    ui->outLineEditG24->setText(QString::number(fills.out.G24));

    ui->outLineEditI30->setText(QString::number(fills.out.I30));

    ui->outLineEditG32->setText(QString::number(fills.out.G32));;
    ui->outLineEditG35->setText(QString::number(fills.out.final_G35));
}

void MainWindow::clearAction()
{

    ui->lineEditE8->setText("0");
    ui->lineEditE9->setText("0");
    ui->lineEditE10->setText("0");
    ui->lineEditE11->setText("0");
    ui->lineEditE12->setText("0");
    ui->lineEditE21->setText("0");
    ui->lineEditE22->setText("0");
    ui->lineEditE29->setText("0");
    ui->lineEditE30->setText("0");

    // Output block
    ui->outLineEditI10->setText("0");
    ui->outLineEditI11->setText("0");
    ui->outLineEditI12->setText("0");

    ui->outLineEditG16->setText("0");

    ui->outLineEditI21->setText("0");
    ui->outLineEditI22->setText("0");

    ui->outLineEditG24->setText("0");

    ui->outLineEditI30->setText("0");

    ui->outLineEditG32->setText("0");;
    ui->outLineEditG35->setText("0");

}

void MainWindow::exitAction()
{
    MainWindow::close();
}

void MainWindow::aboutQtAction()
{
    QMessageBox::aboutQt(this, "About Qt");
}

//TODO Добавить максимальную длину для эдитов
