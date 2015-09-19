#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Point.hpp"
#include "NumericMatrix.hpp"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qtablewidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool doStep();


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;

    unsigned int _currentI;
    unsigned int _currentJ;
    unsigned int _currentK;
    unsigned int _nrows;
    unsigned int _ncols;
    typedef int NumericType;

    bool _started;
    bool _multiplicationDone;

    NumericMatrix<NumericType> *_matrixA, *_matrixB, *_matrixC;

    void restart();

    void multiplyStep();

    bool readValues();

    void updateQTableWidgetFromMatrix(QTableWidget &qTableWidget, Matrix<int> &matrix);

};

#endif // MAINWINDOW_H
