#include "winningdialog.h"
#include "ui_winningdialog.h"

WinningDialog::WinningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinningDialog)
{
    ui->setupUi(this);
}

WinningDialog::~WinningDialog()
{
    delete ui;
}
