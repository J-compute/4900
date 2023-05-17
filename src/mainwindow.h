#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "State.h"
#include "Transition.h"
#include "NFA/nfa.h"
#include "DFA/dfa.h"
#include "drawwidget.h"
#include "qpushbutton.h"
#include "StateWidget.h"
#include "drawwidget.h"
#include "QFileDialog"
#include "QMessageBox"
#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

 //   void saveFile();
 //   void loadFile();

private slots:
 //   void on_stateButton_clicked();
    void on_transitionButton_clicked();
    void on_initialButton_clicked();
    void on_acceptingButton_clicked();
    void on_revStateButton_clicked();
    void on_revTransitionButton_clicked();
    void on_testButton_clicked();
    void on_stateButton_clicked();

    void on_actionExit_triggered();

    void on_comboBox_textActivated(const QString &arg1);

    void on_actionClear_triggered();

    void on_actionConvert_To_DFA_triggered();

    void on_actionRun_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionLoad_triggered();


private:
    void createActions();
    void createSlots();
    void createMenus();

    bool hasSaved = false;

    Ui::MainWindow *ui;

    drawWidget *drawWdg;
// enabling shortcuts
    QPushButton *stateButton;
    QPushButton *transitionButton;
    QPushButton *initialButton;
    QPushButton *acceptingButton;
    QPushButton *revStateButton;
    QPushButton *revTransitionButton;
    QPushButton *testButton;

 // menus
    QMenu *fileMenu;
    QMenu *EditMenu;
    QMenu *ViewMenu;
    QMenu *ExecMenu;
    QMenu *HelpMenu;

// actions
    QAction *newAct;
    QAction *openAct;
    QAction *loadAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *clearAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *aboutAct;
    QAction *HelpAct;
};
#endif // MAINWINDOW_H
