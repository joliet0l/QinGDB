
#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    textEdit = new QPlainTextEdit;
    setCentralWidget(textEdit);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();

    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::closeEvent(QCloseEvent *event)
{

}

void MainWindow::newFile()
{

}

void MainWindow::open()
{

}



void MainWindow::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>Application</b> example demonstrates how to "
               "write modern GUI applications using Qt, with a menu bar, "
               "toolbars, and a status bar."));
}


void MainWindow::createActions()
{
    //File->new
    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
    
    //File->open
    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    //File->About
    aboutAct = new QAction(QIcon(":/images/about.png"), tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    //-----------------------------------------------------------------------------
    // Debug->Restart
    gdbRestartAct = new QAction(QIcon(":/images/restart.png"), tr("&Restart"), this);
    gdbRestartAct->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_F5));
    gdbRestartAct->setStatusTip(tr("Restar the program"));
    connect(gdbRestartAct, SIGNAL(triggered()), this, SLOT(onRestart()));

    // Debug->Stop
    gdbStopAct = new QAction(QIcon(":/images/stop.png"), tr("&Stop"), this);
    gdbStopAct->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F5));
    gdbStopAct->setStatusTip(tr("Stops debugging the program"));
    connect(gdbStopAct, SIGNAL(triggered()), this, SLOT(onStop()));
    
    // Debug->Break
    gdbBreakAct = new QAction(QIcon(":/images/break.png"), tr("&Break"), this);
    gdbBreakAct->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_Pause));
    gdbBreakAct->setStatusTip(tr("Stops program execution;breaks into the debugger"));
    connect(gdbBreakAct, SIGNAL(triggered()), this, SLOT(onBreak()));
    
    // Debug->Next
    gdbStepNextAct = new QAction(QIcon(":/images/stepnext.png"), tr("Show &Next"), this);
    gdbStepNextAct->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_F10));
    gdbStepNextAct->setStatusTip(tr("Displays the source line for the instruction pointer"));
    connect(gdbStepNextAct, SIGNAL(triggered()), this, SLOT(onStepNext()));
    
    // Debug->Step Into
    gdbStepIntoAct = new QAction(QIcon(":/images/stepinto.png"), tr("Step &Into"), this);
    gdbStepIntoAct->setShortcut(QKeySequence(Qt::Key_F11));
    gdbStepIntoAct->setStatusTip(tr("Steps into the next statement"));
    connect(gdbStepIntoAct, SIGNAL(triggered()), this, SLOT(onStepInto()));
    
    // Debug->Step Into
    gdbStepOverAct = new QAction(QIcon(":/images/stepover.png"), tr("Step &Over"), this);
    gdbStepOverAct->setShortcut(QKeySequence(Qt::Key_F10));
    gdbStepOverAct->setStatusTip(tr("Step over the next statement"));
    connect(gdbStepOverAct, SIGNAL(triggered()), this, SLOT(onStepOver()));
    
    // Debug->Step Out
    gdbStepOutAct = new QAction(QIcon(":/images/stepout.png"), tr("Step O&ut"), this);
    gdbStepOutAct->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F11));
    gdbStepOutAct->setStatusTip(tr("Step over the next statement"));
    connect(gdbStepOutAct, SIGNAL(triggered()), this, SLOT(onStepOut()));
    
    // Debug->Goto
    gdbGotoAct = new QAction(QIcon(":/images/goto.png"), tr("&Goto"), this);
    gdbGotoAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F10));
    gdbGotoAct->setStatusTip(tr("Runs the program to the line containing the cursor"));
    connect(gdbGotoAct, SIGNAL(triggered()), this, SLOT(onGoto()));
    
    // Debug->SetBP
    gdbSetpBPAct = new QAction(QIcon(":/images/setbp.png"), tr("Set &Breakpoint"), this);
    gdbSetpBPAct->setShortcut(QKeySequence(Qt::Key_F9));
    gdbSetpBPAct->setStatusTip(tr("Inserts or Removes BreakPoint"));
    connect(gdbSetpBPAct, SIGNAL(triggered()), this, SLOT(onSetBP()));
    
    //-----------------------------------------------------------------------------
    //build ->Download
    gdbDownload = new QAction(QIcon(":/images/download.png"), tr("&Download"), this);
    //gdbDownload->setShortcut(QKeySequence(Qt::Key_F9));
    gdbDownload->setStatusTip(tr("Download a file to target."));
    connect(gdbDownload, SIGNAL(triggered()), this, SLOT(onDownload()));
    
    //build ->reset
    gdbReset = new QAction(QIcon(":/images/reset.png"), tr("&Reset"), this);
    //gdbReset->setShortcut(QKeySequence(Qt::Key_F9));
    gdbReset->setStatusTip(tr("Restar the program."));
    connect(gdbReset, SIGNAL(triggered()), this, SLOT(onReset()));
    
    //build ->Start
    gdbStart = new QAction(QIcon(":/images/start.png"), tr("&Go"), this);
    gdbStart->setShortcut(QKeySequence(Qt::Key_F5));
    gdbStart->setStatusTip(tr("Restar the program."));
    connect(gdbStart, SIGNAL(triggered()), this, SLOT(onGo()));
    
    //build ->Mips16
    gdbMIPS16 = new QAction(QIcon(":/images/mips16.png"), tr("&MIPS16"), this);
    //gdbMIPS16->setShortcut(QKeySequence(Qt::Key_F5));
    gdbMIPS16->setStatusTip(tr("Restar the program."));
    connect(gdbMIPS16, SIGNAL(triggered()), this, SLOT(onMips16()));
    
    //build ->Platform
    gdbPlatform = new QAction(QIcon(":/images/platform.png"), tr("&Platform"), this);
    //gdbPlatform->setShortcut(QKeySequence(Qt::Key_F5));
    gdbPlatform->setStatusTip(tr("Restar the program."));
    connect(gdbPlatform, SIGNAL(triggered()), this, SLOT(onPlatform()));
    
    //build ->Option
    gdbOptions = new QAction(QIcon(":/images/option.png"), tr("&Option"), this);
    //gdbOptions->setShortcut(QKeySequence(Qt::Key_F5));
    gdbOptions->setStatusTip(tr("Restar the program."));
    connect(gdbOptions, SIGNAL(triggered()), this, SLOT(onOptions()));
    
    //build ->CPUMaster
    gdbCPUMaster = new QAction(QIcon(":/images/master.png"), tr("&Mastr CPU"), this);
    //gdbCPUMaster->setShortcut(QKeySequence(Qt::Key_F5));
    gdbCPUMaster->setStatusTip(tr("Switch master CPU"));
    connect(gdbCPUMaster, SIGNAL(triggered()), this, SLOT(onCPUMaster()));
    
    //build ->CPUSlave
    gdbCPUSlave = new QAction(QIcon(":/images/slave.png"), tr("&Slave CPU"), this);
    //gdbCPUSlave->setShortcut(QKeySequence(Qt::Key_F5));
    gdbCPUSlave->setStatusTip(tr("Switch slave CPU"));
    connect(gdbCPUSlave, SIGNAL(triggered()), this, SLOT(onCPUSlave()));
    
        
    //build ->CPUSlave
    gdbRegEvent = new QAction(QIcon(":/images/reqevent.png"), tr("&ReqEvent"), this);
    //gdbRegEvent->setShortcut(QKeySequence(Qt::Key_F5));
    gdbRegEvent->setStatusTip(tr("Switch slave CPU"));
    connect(gdbRegEvent, SIGNAL(triggered()), this, SLOT(onReqEvent()));
    
    
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(aboutAct);

    debugMenu = menuBar()->addMenu(tr("&Debug"));
    debugMenu->addAction(gdbRestartAct);
    debugMenu->addAction(gdbStopAct);
    debugMenu->addAction(gdbBreakAct);
    debugMenu->addAction(gdbStepNextAct);
    debugMenu->addAction(gdbStepIntoAct);
    debugMenu->addAction(gdbStepOverAct);
    debugMenu->addAction(gdbStepOutAct);
    debugMenu->addAction(gdbGotoAct);
    debugMenu->addAction(gdbSetpBPAct);
    
    buildMenu = menuBar()->addMenu(tr("&Build"));
    buildMenu->addAction(gdbDownload);
    buildMenu->addAction(gdbReset);
    buildMenu->addAction(gdbStart);
    buildMenu->addSeparator();
    buildMenu->addAction(gdbPlatform);
    buildMenu->addAction(gdbOptions);
    buildMenu->addSeparator();
    buildMenu->addAction(gdbMIPS16);
    buildMenu->addAction(gdbCPUMaster);
    buildMenu->addAction(gdbCPUSlave);
    buildMenu->addAction(gdbRegEvent);
    
}

void MainWindow::createToolBars()
{
/*    
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(aboutAct);
*/
    buildToolBar = addToolBar(tr("Build"));
    buildToolBar->addAction(gdbDownload);
    buildToolBar->addAction(gdbReset);
    buildToolBar->addAction(gdbStart);
    buildToolBar->addSeparator();
    buildToolBar->addAction(gdbPlatform);
    buildToolBar->addAction(gdbOptions);
    buildToolBar->addSeparator();
    buildToolBar->addAction(gdbMIPS16);
    buildToolBar->addAction(gdbCPUMaster);
    buildToolBar->addAction(gdbCPUSlave);
    buildToolBar->addAction(gdbRegEvent);
    
    
    debugToolBar = addToolBar(tr("Debug"));
    debugToolBar->addAction(gdbRestartAct);
    debugToolBar->addAction(gdbStopAct);
    debugToolBar->addAction(gdbBreakAct);
    debugToolBar->addSeparator();
    debugToolBar->addAction(gdbStepNextAct);
    debugToolBar->addAction(gdbStepIntoAct);
    debugToolBar->addAction(gdbStepOverAct);
    debugToolBar->addAction(gdbStepOutAct);
    debugToolBar->addAction(gdbGotoAct);
    debugToolBar->addAction(gdbSetpBPAct);
    
    
}
void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}
void MainWindow::readSettings()
{
    QSettings settings("QtProject", "Application Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}

void MainWindow::writeSettings()
{
    QSettings settings("QtProject", "Application Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}


//============================================================================================
// Actions SLOTs
void MainWindow::onRestart()
{

}
void MainWindow::onStop()
{

}
void MainWindow::onBreak()
{

}
void MainWindow::onStepNext()
{

}
void MainWindow::onStepInto()
{

}
void MainWindow::onStepOver()
{

}
void MainWindow::onStepOut()
{

}
void MainWindow::onGoto()
{

}
void MainWindow::onSetBP()
{

}

void MainWindow::onDownload()
{
}
void MainWindow::onReset()
{
}
void MainWindow::onGo()
{
}
void MainWindow::onMips16(){}
void MainWindow::onPlatform(){}
void MainWindow::onOptions(){}
void MainWindow::onCPUMaster(){}
void MainWindow::onCPUSlave(){}
void MainWindow::onReqEvent(){}
    