#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _currentI = 0;
    _currentJ = 0;
    _currentK = 0;
    _nrows = ui->tableWidget->rowCount();
    _ncols = ui->tableWidget->columnCount();
    _started = false;
    _matrixA = NULL;
    _matrixB = NULL;
    _matrixC = NULL;
}

MainWindow::~MainWindow()
{
    if ( _matrixA != NULL ) {
        delete _matrixA;
        delete _matrixB;
        delete _matrixC;
    }
    delete ui;
}

void MainWindow::readValues()
{
    if ( !_started ) {
        // Allocate memory if necessary
        if ( _matrixA == NULL ) {
            _matrixA = new NumericMatrix<NumericType>(_nrows, _ncols);
            _matrixB = new NumericMatrix<NumericType>(_nrows, _ncols);
            _matrixC = new NumericMatrix<NumericType>(_nrows, _ncols);
        }

        _matrixC->setZero();
        _multiplicationDone = false;
        ui->label->setText("");

        // Read values from widgets
        NumericType tmp;
        for ( unsigned int i=0; i<_nrows; i++ )
        {
            for ( unsigned int j=0; j<_ncols; j++ )
            {
                tmp = ui->tableWidget->item(i,j)->text().toInt();
                _matrixA->set(i,j,tmp);
                tmp = ui->tableWidget_2->item(i,j)->text().toInt();
                _matrixB->set(i,j,tmp);
            }
        }

        // Disable widgets
        ui->tableWidget->setEnabled(false);
        ui->tableWidget_2->setEnabled(false);
        // This is not necessary because they won't be read
        //ui->tableWidget_3->setEnabled(false);

        _started = true;
    }
}

void MainWindow::doStep()
{
    readValues();

    multiplyStep();

    updateQTableWidgetFromMatrix(*(ui->tableWidget_3), *_matrixC);

    updateQTableWidgetFromMatrix(*(ui->tableWidget), *_matrixA);


    // Multiply
    //for ( unsigned int i=startI; i<endI; i++ )
    //int value = ui->tableWidget_2->itemAt(_currentI,_currentK)->text().toInt() * ui->tableWidget_2->itemAt(_currentK, _currentJ)->text().toInt();

    //Point<int> point(_currentI, _currentJ, value);

    //point.getValue();

    //setValueOnCMatrix(ui->tableWidget_3, new Point( _currentI, _currentJ, value));

    {
        //for ( unsigned int j=startJ; j<endJ; j++ )
        {
            //for ( unsigned int k=startK; k<endK; k++ )
            {

            }
        }
    }
}

void MainWindow::updateQTableWidgetFromMatrix(QTableWidget &qTableWidget, Matrix<int> &matrix)
{
    for ( unsigned int i=0; i<_nrows; i++ )
    {
        for ( unsigned int j=0; j<_ncols; j++ )
        {
            // Update C values
            std::ostringstream buffer;
            buffer << matrix.get(i, j);
            QTableWidgetItem *newItem = new QTableWidgetItem();
            newItem->setText(buffer.str().c_str());
            qTableWidget.setItem(i, j, newItem);
        }
    }
}


void MainWindow::multiplyStep()
{
    // Multiply
    if ( !_multiplicationDone ) {
        NumericType currA, currB, currC;
        if ( _currentI < _nrows ) {
            if ( _currentJ < _ncols ) {
                if ( _currentK < _nrows /* Assuming all have the same dimensions */ ) {
                    currA = _matrixA->get(_currentI, _currentK);
                    currB = _matrixB->get(_currentK, _currentJ);
                    currC = _matrixC->get(_currentI, _currentJ);
                    _matrixC->set(_currentI, _currentJ, currC+(currA*currB));
                    _currentK++;
                } else {
                    _currentK = 0;
                    _currentJ++;

                    currA = _matrixA->get(_currentI, _currentK);
                    currB = _matrixB->get(_currentK, _currentJ);
                    currC = _matrixC->get(_currentI, _currentJ);
                    _matrixC->set(_currentI, _currentJ, currC+(currA*currB));
                    _currentK++;
                }
            } else {
                _currentJ = 0;
                _currentI++;

                currA = _matrixA->get(_currentI, _currentK);
                currB = _matrixB->get(_currentK, _currentJ);
                currC = _matrixC->get(_currentI, _currentJ);
                _matrixC->set(_currentI, _currentJ, currC+(currA*currB));
                _currentJ++;
            }
        } else {
            // We've finished
            _currentI = 0;
            ui->label->setText("Finished");
            _multiplicationDone = true;
        }
    }

/*
    for ( unsigned int i=startI; i<endI; i++ )
    {
        for ( unsigned int j=startJ; j<endJ; j++ )
        {
            for ( unsigned int k=startK; k<endK; k++ )
            {
                setValueOnCMatrix(ui->tableWidget_3, );
            }
        }
    }
*/
}


/*
void setValueOnCMatrix(QTableWidget &qtablewidget, Point &point)
{
    std::ostringstream buffer;
    QTableWidgetItem *newItem = new QTableWidgetItem();
    buffer << point.getValue(); qtablewidget.itemAt();
    newItem->setText(buffer.str().c_str());
    qtablewidget->setItem(i, j, newItem);
}
*/

void fillMatrix(QTableWidget *qtableWidget)
{
    unsigned int nrows = qtableWidget->rowCount();
    unsigned int ncols = qtableWidget->columnCount();

    std::ostringstream buffer;
    int totalValue;

    for ( unsigned int i=0; i<nrows; i++ )
    {
        for ( unsigned int j=0; j<ncols; j++ )
        {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            totalValue = 1+(i*ncols+j);
            std::ostringstream buffer;
            buffer << totalValue;
            newItem->setText(buffer.str().c_str());
            qtableWidget->setItem(i, j, newItem);
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    fillMatrix(ui->tableWidget);
    fillMatrix(ui->tableWidget_2);
}

void MainWindow::on_pushButton_2_clicked()
{
    doStep();
}
