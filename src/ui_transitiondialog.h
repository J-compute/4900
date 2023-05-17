#ifndef UI_TRANSITIONDIALOG_H
#define UI_TRANSITIONDIALOG_H

#include <QDialog>

namespace Ui {
    class transitiondialog : public QDialog
    {
        Q_OBJECT
    public:
        transitiondialog(QString state1, QString state2, QWidget *parent = nullptr);

        int getState1();
        int getState2();
    private:
        Ui::transitiondialog *ui;
    };
}
#endif // UI_TRANSITIONDIALOG_H
