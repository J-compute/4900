#include "mainwindow.h"
#include "qevent.h"
#include "ui_mainwindow.h"


bool stateClicked = false;
bool transitionClicked = false;
bool removeClicked = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Automata Designer");
    drawWdg = new drawWidget();
    //ui->graphicsView->setWidget(drawWdg);
    ui->graphicsView->setViewport(drawWdg);


 //  createActions();
 //   createSlots();
    // createMenus();
    ui->lineEdit->setText("Program launch successful.");

    QComboBox comboBox;
    ui->comboBox->addItem("DFA");
    ui->comboBox->addItem("NFA");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions() {

}

/*void MainWindow::on_stateButton_clicked()
{
    drawWdg->addState();
    setCursor(QCursor(Qt::PointingHandCursor));
  transitionClicked = false;
    removeClicked = false;
    QPoint latestPoint;
*/
// }

void MainWindow::createMenus() {

}


void MainWindow::on_transitionButton_clicked()
{
    drawWdg->addTransition();
    setCursor(QCursor(Qt::SizeHorCursor));
}


void MainWindow::on_initialButton_clicked()
{
    drawWdg->setStart();
    setCursor(QCursor(Qt::PointingHandCursor));
}


void MainWindow::on_acceptingButton_clicked()
{
    drawWdg->setAccept();
    setCursor(QCursor(Qt::PointingHandCursor));
}


void MainWindow::on_revStateButton_clicked()
{
    drawWdg->removeState();
    setCursor(QCursor(Qt::PointingHandCursor));
}


void MainWindow::on_revTransitionButton_clicked()
{
    drawWdg->removeTransition();
    setCursor(QCursor(Qt::PointingHandCursor));
}


void MainWindow::on_testButton_clicked()
{
    drawWdg->execFA();
}

void MainWindow::on_stateButton_clicked()
{
    drawWdg->addState();
    setCursor(QCursor(Qt::PointingHandCursor));

}


void MainWindow::on_actionExit_triggered()
{
    close();
}


void MainWindow::on_comboBox_textActivated(const QString &arg1)
{
    drawWdg->setFA(arg1);
}


void MainWindow::on_actionClear_triggered()
{
    drawWdg->clearAll();
}


void MainWindow::on_actionConvert_To_DFA_triggered()
{
    drawWdg->convertFA();
}


void MainWindow::on_actionRun_triggered()
{
    drawWdg->execFA();
}


void MainWindow::on_actionSave_triggered()
{
    if (hasSaved == false) {
        on_actionSave_As_triggered();
    } else {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Finite Automaton"), "",
                                                    tr("Finite Automaton (*.fin);;All Files (*)"));
        if (fileName.isEmpty()) {
            return;
        }
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
                return;
            }
            drawWdg->saveToFile(file);
            file.close();
    }
    }
}


void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Finite Automaton"), "",
                                                tr("Finite Automaton (*.fin);;All Files (*)"));
    if (fileName.isEmpty()) {
        return;
    }
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
            return;
        }
        drawWdg->saveToFile(file);
        file.close();
    }
    hasSaved = true;
}


void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Finite Automaton"), "", tr("Finite Automaton (*.fin)"));

    if (fileName.isEmpty()) {
        return;
    }
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Failed to open file"), file.errorString());
            return;
        }
        drawWdg->loadFromFile(file);
        file.close();
    }
}
