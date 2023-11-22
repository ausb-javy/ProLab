#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DemoRibbonWindow.h"
#include <QPlainTextEdit>

/* MainWindow */
class MainWindow : public DemoRibbonWindow
{
    Q_OBJECT
public:
    enum LOGLEVAL {
        INFO = 01,
        WARNNING,
        ERROR
    };

    explicit MainWindow(QWidget* parent = Q_NULL);
    virtual ~MainWindow();
private:
    void creatAction();
    void creatHomeButton(RibbonPage* page);
    void creatCadButton(RibbonPage* page);
    void creatCaeButton(RibbonPage* page);
    void creatCamButton(RibbonPage* page);
    void creatDockWindows();
    void creatTreeItem(QDockWidget* treeDock);

    void addLog(QPlainTextEdit* logtext, const QString& message, LOGLEVAL level);

private slots:
    void openFile();
    // add page
    void creatPage(QDockWidget* dock);

protected:

    // action
    QAction* m_newFile;
    QAction* m_addDock;

    // button
    QToolButton* button1;

    // Widget
    QDockWidget* treeDock;
    QDockWidget* logDock;
    QDockWidget* oprDock;
    QWidget* graphWidget;       // 在cpp文件中将new一个OSGwidget
    QWidget* treeItem;

    // log textbrowser 
    QPlainTextEdit* LogText;

    // opr page
    RibbonPage* cadOpr;

private:
    Q_DISABLE_COPY(MainWindow)
};

#endif // MAINWINDOW_H

