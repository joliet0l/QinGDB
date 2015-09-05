
#include <QtWidgets>
#include "mainwindow.h"
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexer.h>
#include <Qsci/qscilexercpp.h>

#define MAKER_BREAKPOINT    6
#define MAKER_RUNAT         7
MainWindow::MainWindow()
{
	create_main_widget();
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
	create_dock_widgets();

    readSettings();

    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();

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
    QSettings settings("ALiTech", "QinGDB");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}

void MainWindow::writeSettings()
{
    QSettings settings("ALiTech", "QinGDB");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

void MainWindow::create_main_widget()
{
    QWidget *main_widget = new QWidget(this);
	QVBoxLayout *v_box = new QVBoxLayout;
    v_box->setSpacing(0);
    v_box->setMargin(0);
	main_widget->setLayout (v_box);

	main_tab_widget = new QTabWidget;
	main_tab_widget->setObjectName ("main_tab_widget");

    main_tab_widget->setTabShape (QTabWidget::Rounded);
    main_tab_widget->setTabPosition(QTabWidget::South);
    main_tab_widget->setMinimumHeight (20);

	//create toolbar
	editToolbar = new EditorToolBar(this);

	//create the editor
    textASM = new QsciScintilla(this);
    textSource = new QsciScintilla(this);


	//font for line number
    QFont marginFont("Courier", 9);
	marginFont.setFixedPitch(true);
	QFontMetrics fontmetrics(marginFont);
	

	//font for text
	QFont textFont("Consolas", 11);

	//set asm source
    textASM->setFont(textFont);
    textASM->setTabWidth(4);

    //margin 0 for line number
    textASM->setMarginLineNumbers(0, true);
    textASM->setMarginsFont(marginFont);
    textASM->setMarginWidth(0, fontmetrics.width("00000") + 6);
    textASM->setMarginsBackgroundColor(QColor("#f0f0f0"));
    //margin 1
    textASM->setMarginSensitivity(1, true);
    connect(textASM, SIGNAL(marginClicked(int, int, Qt::KeyboardModifiers)),
            this, SLOT(onAsmMarginClicked(int, int, Qt::KeyboardModifiers)));
    textASM->markerDefine(QsciScintilla::Circle, MAKER_BREAKPOINT);
    textASM->setMarkerBackgroundColor(QColor("#ee1111"), MAKER_BREAKPOINT);
    textASM->markerDefine(QsciScintilla::RightArrow, MAKER_RUNAT);
    textASM->setMarkerBackgroundColor(QColor("#eeee00"), MAKER_RUNAT);


	//set c/c++ source
	cpplexer = new QsciLexerCPP;
	cpplexer->setDefaultFont(textFont);
    textSource->setFont(textFont);
	textSource->setLexer(cpplexer);
    textSource->setTabWidth(4);

    //margin 0 for line number
    textSource->setMarginLineNumbers(0, true);
    textSource->setMarginsFont(marginFont);
    textSource->setMarginWidth(0, fontmetrics.width("00000") + 6);
    textSource->setMarginsBackgroundColor(QColor("#f0f0f0"));
    //margin 1
    textSource->setMarginSensitivity(1, true);
    connect(textSource, SIGNAL(marginClicked(int, int, Qt::KeyboardModifiers)),
            this, SLOT(onSrcMarginClicked(int, int, Qt::KeyboardModifiers)));

    textSource->markerDefine(QsciScintilla::Circle, MAKER_BREAKPOINT);
    textSource->setMarkerBackgroundColor(QColor("#ee1111"), MAKER_BREAKPOINT);
    textSource->markerDefine(QsciScintilla::RightArrow, MAKER_RUNAT);
    textSource->setMarkerBackgroundColor(QColor("#eeee00"), MAKER_RUNAT);


	//add to tab
    main_tab_widget->addTab(textASM, QIcon(":/images/asm.ico"), tr ("ASM"));
    main_tab_widget->addTab(textSource,QIcon(":/images/c.ico"),  tr ("Source"));
	
	v_box->addWidget(editToolbar);	
	v_box->addWidget(main_tab_widget);	
	setCentralWidget (main_widget);

}

void MainWindow::create_dock_widgets()
{
	QDockWidget *dw = new QDockWidget;    
	dw->setObjectName(tr("Registers Dock"));    
	dw->setWindowTitle(tr("Registers"));    
	dw->setWidget(new QTextEdit);
    addDockWidget(Qt::LeftDockWidgetArea, dw);
	dwRegisters = dw;

	
	dw = new QDockWidget;    
	dw->setObjectName(tr("Output Dock"));    
	dw->setWindowTitle(tr("Output"));    
	dw->setWidget(new QTextEdit);
    addDockWidget(Qt::BottomDockWidgetArea, dw);
	dwOutput = dw;

	dw = new QDockWidget;    
	dw->setObjectName(tr("CallStack Dock"));    
	dw->setWindowTitle(tr("CallStack"));    
	dw->setWidget(new QTextEdit);
    addDockWidget(Qt::RightDockWidgetArea, dw);
	dwCallstack = dw;

	
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
    int line = 0;
    int index = 0;

    textSource->getCursorPosition(&line, &index);
    unsigned int makers = textSource->markersAtLine(line);
    if(( makers & (1<< MAKER_RUNAT)) != 0)
        textSource->markerDelete(line, MAKER_RUNAT);
    else
        textSource->markerAdd(line, MAKER_RUNAT);
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

void MainWindow::onSrcMarginClicked(int margin, int line, Qt::KeyboardModifiers state)
{
    unsigned int makers = textSource->markersAtLine(line);
    if(( makers & (1<< MAKER_BREAKPOINT)) != 0)
        textSource->markerDelete(line, MAKER_BREAKPOINT);
    else
        textSource->markerAdd(line, MAKER_BREAKPOINT);
}
void MainWindow::onAsmMarginClicked(int margin, int line, Qt::KeyboardModifiers state)
{
    unsigned int makers = textASM->markersAtLine(line);
    if(( makers & (1<< MAKER_BREAKPOINT)) != 0)
        textASM->markerDelete(line, MAKER_BREAKPOINT);
    else
        textASM->markerAdd(line, MAKER_BREAKPOINT);
}
