#include "nostock.h"
#include "ui_nostock.h"

nostock::nostock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nostock)
{
    ui->setupUi(this);
}

nostock::~nostock()
{
    delete ui;
}
