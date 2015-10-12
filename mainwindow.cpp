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
    setWindowTitle("Visual Matrix Multiplication");

    restart();

    _matrixA = NULL;
    _matrixB = NULL;
    _matrixC = NULL;
}

void MainWindow::restart()
{
    _currentI = 0;
    _currentJ = 0;
    _currentK = 0;
    _nrows = ui->tableWidget->rowCount();
    _ncols = ui->tableWidget->columnCount();
    _started = false;
    _multiplicationDone = false;
    ui->tableWidget->setEnabled(true);
    ui->tableWidget_2->setEnabled(true);
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

bool MainWindow::readValues()
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
                try {

                    if ( ui->tableWidget->item(i,j) != NULL ) {
                        tmp = ui->tableWidget->item(i,j)->text().toDouble();
                        _matrixA->set(i,j,tmp);
                    } else
                        throw -20;
                    if ( ui->tableWidget_2->item(i,j) != NULL ) {
                        tmp = ui->tableWidget_2->item(i,j)->text().toDouble();
                        _matrixB->set(i,j,tmp);
                    } else
                        throw -20;
                } catch (int) {
                    ui->label_2->setText("Please, initialize the matrices");
                    return false;
                }
            }
        }

        // Disable widgets
        ui->tableWidget->setEnabled(false);
        ui->tableWidget_2->setEnabled(false);
        // This is not necessary because they won't be read
        //ui->tableWidget_3->setEnabled(false);

        _started = true;
        return true;
    }
    return true;
}

bool MainWindow::doStep()
{
    if ( readValues() ) {
        ui->label_2->setText("");
        multiplyStep();
        updateQTableWidgetFromMatrix(*(ui->tableWidget_3), *_matrixC);
        return true;
    } else
        return false;
}

void MainWindow::updateQTableWidgetFromMatrix(QTableWidget &qTableWidget, Matrix<NumericType> &matrix)
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

                    /* Visual selection */
                    ui->tableWidget->clearSelection();
                    ui->tableWidget->item(_currentI, _currentK)->setSelected(true);
                    ui->tableWidget_2->clearSelection();
                    ui->tableWidget_2->item(_currentK, _currentJ)->setSelected(true);
                    std::ostringstream sI, sJ, sK;
                    sI << "I=" << _currentI+1;
                    sJ << "J=" << _currentJ+1;
                    sK << "K=" << _currentK+1;
                    ui->label_currI->setText(sI.str().c_str());
                    ui->label_currJ->setText(sJ.str().c_str());
                    ui->label_currK->setText(sK.str().c_str());

                    _currentK++;
                } else {
                    _currentK = 0;
                    _currentJ++;

                    if ( _currentJ < _ncols ) {
                        currA = _matrixA->get(_currentI, _currentK);
                        currB = _matrixB->get(_currentK, _currentJ);
                        currC = _matrixC->get(_currentI, _currentJ);
                        _matrixC->set(_currentI, _currentJ, currC+(currA*currB));

                        /* Visual selection */
                        ui->tableWidget->clearSelection();
                        ui->tableWidget->item(_currentI, _currentK)->setSelected(true);
                        ui->tableWidget_2->clearSelection();
                        ui->tableWidget_2->item(_currentK, _currentJ)->setSelected(true);
                        std::ostringstream sI, sJ, sK;
                        sI << "I=" << _currentI+1;
                        sJ << "J=" << _currentJ+1;
                        sK << "K=" << _currentK+1;
                        ui->label_currI->setText(sI.str().c_str());
                        ui->label_currJ->setText(sJ.str().c_str());
                        ui->label_currK->setText(sK.str().c_str());

                        _currentK++;
                    } else {
                        _currentI++;
                        _currentJ = 0;
                        _currentK = 0;
                        if ( _currentI < _nrows ) {
                            currA = _matrixA->get(_currentI, _currentK);
                            currB = _matrixB->get(_currentK, _currentJ);
                            currC = _matrixC->get(_currentI, _currentJ);
                            _matrixC->set(_currentI, _currentJ, currC+(currA*currB));

                            /* Visual selection */
                            ui->tableWidget->clearSelection();
                            ui->tableWidget->item(_currentI, _currentK)->setSelected(true);
                            ui->tableWidget_2->clearSelection();
                            ui->tableWidget_2->item(_currentK, _currentJ)->setSelected(true);
                            std::ostringstream sI, sJ, sK;
                            sI << "I=" << _currentI+1;
                            sJ << "J=" << _currentJ+1;
                            sK << "K=" << _currentK+1;
                            ui->label_currI->setText(sI.str().c_str());
                            ui->label_currJ->setText(sJ.str().c_str());
                            ui->label_currK->setText(sK.str().c_str());

                            _currentK++;
                        } else {
                            // We've finished
                            _currentI = 0;
                            ui->label->setText("Finished");
                            _multiplicationDone = true;
                        }
                    }
                }
            } else {
                _currentJ = 0;
                _currentK = 0;
                _currentI++;

                currA = _matrixA->get(_currentI, _currentK);
                currB = _matrixB->get(_currentK, _currentJ);
                currC = _matrixC->get(_currentI, _currentJ);
                _matrixC->set(_currentI, _currentJ, currC+(currA*currB));

                /* Visual selection */
                ui->tableWidget->clearSelection();
                ui->tableWidget->item(_currentI, _currentK)->setSelected(true);
                ui->tableWidget_2->clearSelection();
                ui->tableWidget_2->item(_currentK, _currentJ)->setSelected(true);

                _currentK++;
            }
        }
    }
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
    if ( !_started ) {
        fillMatrix(ui->tableWidget);
        fillMatrix(ui->tableWidget_2);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    doStep();
}

void MainWindow::on_pushButton_3_clicked()
{
    while ( !this->_multiplicationDone ) {
        if ( !doStep() )
            break;
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    restart();
}
