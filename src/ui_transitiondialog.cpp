#include "ui_transitiondialog.h"

#include <QDialog>

transitiondialog::transitiondialog(QString state1, QString state2, QWidget *parent )
        : QDialog(parent),
        ui(new Ui::transitiondialog){

        ui-setupUi(this);
        ui->lineEditSt1->setText(state1);
        ui->lineEditSt2->setText(state2);


}
int transitiondialog::getState1() {
        return ui->lineEditSt1;
    }
int transitiondialog:;getState2();
