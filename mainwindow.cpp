#include <QFontComboBox>
#include <QScreen>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QGroupBox>
#include <QBoxLayout>
#include <QTreeWidget>
#include <QTime>

#include "aboutdialog.h"
#include "mainwindow.h"
#include "QtitanRibbon.h"
#include "QtitanBase.h"
#include "QtnRibbonButton.h"



/* MainWindow */
MainWindow::MainWindow(QWidget* parent)
    : DemoRibbonWindow(parent),
    topoOptimizeWidget(new TopoOptimizeWidget)
{
    // init
    setWindowTitle(QObject::tr("ProLab"));
    setWindowIcon(QIcon(":/res/MainWindow/companyLogo.png"));
    setStyleByName(QStringLiteral("Office2016Colorful"));
    ribbonBar()->setFrameThemeEnabled();
    QFont defautFont = QApplication::font();
    defautFont.setPointSize(defautFont.pointSize() + 1);
    ribbonBar()->setFont(defautFont);


    RibbonPage* homePage = ribbonBar()->addPage("&开始");
    RibbonPage* structureOptiPage = ribbonBar()->addPage("&结构优化");
    RibbonPage* cadPage = ribbonBar()->addPage("&CAD");
    RibbonPage* caePage = ribbonBar()->addPage("&CAE");
    RibbonPage* camPage = ribbonBar()->addPage("&CAM");

    creatHomeButton(homePage);
    creatStructureOptiButton(structureOptiPage);
    creatCadButton(cadPage);
    creatCaeButton(caePage);
    creatCamButton(camPage);

    creatDockWindows();
    creatConnect();

/*    selectedIndex = treeView->currentIndex();     */                  // selected row


#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    const int factor = 5;
    const QRect availableGeometry = screen()->availableGeometry();
    resize(2 * availableGeometry.width() / factor, 2 * availableGeometry.height() / (factor * 3));
    move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
#else
    resize(1000, 300); move(200, 200);
#endif
}

MainWindow::~MainWindow()
{
}

void MainWindow::creatConnect()
{
    QObject::connect(m_newFile, &QAction::triggered, this, &MainWindow::openFile);

    // ????
    connect(m_addDock, SIGNAL(m_addDock->triggered()), this, SLOT(openFile()));
}

void MainWindow::creatHomeButton(RibbonPage* page)
{
    RibbonGroup* groupHome = page->addGroup("文件操作");
    RibbonToolBarControl* toolBar = new RibbonToolBarControl(groupHome);
    m_newFile = toolBar->addAction(QIcon(QStringLiteral(":/res/largeNewFile.png")), "new", Qt::ToolButtonTextUnderIcon);
    m_addDock = toolBar->addAction(QIcon(QStringLiteral(":/res/MainWindow/companyLogo.png")), "新建\n文件", Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(QIcon(QStringLiteral(":/res/MainWindow/companyLogo.png")), "新建\n文件", Qt::ToolButtonTextUnderIcon);
    toolBar->addSeparator();
    toolBar->addAction(QIcon(QStringLiteral(":/res/MainWindow/companyLogo.png")), "新建\n文件", Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(QIcon(QStringLiteral("C:/Users/49769/Desktop/plIcon.png")), "新建\n文件2", Qt::ToolButtonTextUnderIcon);
    groupHome->addControl(toolBar);
}

void MainWindow::creatStructureOptiButton(RibbonPage* page)
{
    RibbonGroup* groupCad = page->addGroup("优化选择");
    RibbonToolBarControl* toolBar = new RibbonToolBarControl(groupCad);
    m_newFile = toolBar->addAction(QIcon(QStringLiteral(":/res/largeNewFile.png")), "2D拓扑优化", Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(QIcon(QStringLiteral(":/res/MainWindow/companyLogo.png")), "3D拓扑优化", Qt::ToolButtonTextUnderIcon);
    groupCad->addControl(toolBar);
}


void MainWindow::creatCadButton(RibbonPage* page)
{
    RibbonGroup* groupCad = page->addGroup("文件操作");
    RibbonToolBarControl* toolBar = new RibbonToolBarControl(groupCad);
    m_newFile = toolBar->addAction(QIcon(QStringLiteral(":/res/largeNewFile.png")), "new", Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(QIcon(QStringLiteral(":/res/MainWindow/companyLogo.png")), "新建\n文件", Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(QIcon(QStringLiteral(":/res/MainWindow/companyLogo.png")), "新建\n文件", Qt::ToolButtonTextUnderIcon);
    groupCad->addControl(toolBar);
}

void MainWindow::creatCaeButton(RibbonPage* page)
{
}

void MainWindow::creatCamButton(RibbonPage* page)
{
}

void MainWindow::creatDockWindows()
{
    // creat tree dock
    treeDock = new QDockWidget(tr("Project Tree View"), this);
    treeDock->setMaximumWidth(600);
    treeDock->setMinimumWidth(200);
    treeDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    treeDock->setFeatures(QDockWidget::DockWidgetMovable);
    treeDock->setWidget(topoOptimizeWidget->treeWidget);
    addDockWidget(Qt::LeftDockWidgetArea, treeDock);
    // creat log dock
    myLogWidget* logWidget = new myLogWidget;
    logDock = new QDockWidget(tr("Log Message"));
    logDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    logDock->setFeatures(QDockWidget::DockWidgetVerticalTitleBar);
    //resizeDocks({ logDock }, { 400 }, Qt::Vertical);
    logDock->setWidget(logWidget);
    LogText = new QPlainTextEdit();
    //LogText->setStyleSheet(QString("background-color: #E7EEF6;"));
    LogText->setReadOnly(true);                                             // set read only
    for (int i = 0; i < 100; i++) {
        addLog(LogText, "hello ProLab", MainWindow::INFO);
        addLog(LogText, "hello ProLab", MainWindow::WARNNING);
        addLog(LogText, "hello ProLab", MainWindow::WRONG);
    }

    logDock->setWidget(LogText);
    addDockWidget(Qt::BottomDockWidgetArea, logDock);

    // creat operate Dock
    oprDock = new QDockWidget(tr("operate"), this);
    oprDock->setMaximumWidth(600);
    oprDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    oprDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // addOprPage();
    oprDock->setWidget(topoOptimizeWidget->oprStackWidget);
    //creatOprPage(oprDock);
    addDockWidget(Qt::RightDockWidgetArea, oprDock);

    // creat graphWidget
    osg::Node* displaynode = osgDB::readNodeFile("D:/osgLIB_and_openLIB/osgLIB/build/data/cow.osg");
    OsgWidget* osgWidget = new OsgWidget(0, Qt::Widget, osgViewer::ViewerBase::SingleThreaded, displaynode);
    setCentralWidget(osgWidget);

}


void MainWindow::addLog(QPlainTextEdit* logtext, const QString& message, LOGLEVAL level)
{
    QString log;
    // set text format
    QTextCharFormat fmt;
    fmt.setFontPointSize(9);
    logtext->document()->setMaximumBlockCount(200);                     // set maximum display rows 

    switch (level)
    {
    case MainWindow::INFO:
        log = QTime::currentTime().toString("hh:mm:ss:zzz ") + QString(" [   INFO\t") + QString("]\t") + message;
        logtext->appendPlainText(log);
        break;
    case MainWindow::WARNNING:
        log = QTime::currentTime().toString("hh:mm:ss:zzz ") + QString(" [  WARNNING\t") + QString("]\t") + message;
        logtext->appendPlainText(log);
        break;
    case MainWindow::WRONG:
        log = QTime::currentTime().toString("hh:mm:ss:zzz ") + QString(" [   ERROR\t") + QString("]\t") + message;
        fmt.setForeground(QColor("red"));
        logtext->mergeCurrentCharFormat(fmt);
        logtext->appendPlainText(log);
        fmt.setForeground(QColor("black"));
        logtext->mergeCurrentCharFormat(fmt);
        break;
    }
}

void MainWindow::creatOprPage(QDockWidget* dock)
{
    QLayout* Lay = dock->layout();
    if (Lay) {
        // clear components
    }

    cadOpr = new RibbonPage();
    button1 = new RibbonButton();
    button1->setText(QString("button1"));
    QToolButton* button2 = new RibbonButton();
    button2->setText(QString("button2"));
    QToolButton* button3 = new RibbonButton();
    button3->setText(QString("button3"));
    QToolButton* button4 = new RibbonButton();
    button4->setText(QString("button4"));

    QWidget* wid = new QWidget();
    QGridLayout* Hlayout = new QGridLayout(wid);
    Hlayout->addWidget(button1);
    Hlayout->addWidget(button2);
    Hlayout->addWidget(button3);
    Hlayout->addWidget(button4);

    dock->setWidget(wid);
}

void MainWindow::openFile()
{
    QMessageBox::information(NULL, QString("openFile"), QString("prolab->now open file"));
    return;
}

