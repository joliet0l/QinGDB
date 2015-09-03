/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "editortoolbar.h"


QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class QsciScintilla;	
class QsciLexer;
//! [0]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void newFile();
    void open();
    void about();
    //debug
    void onRestart();
    void onStop();
    void onBreak();
    void onStepNext();
    void onStepInto();
    void onStepOver();
    void onStepOut();
    void onGoto();
    void onSetBP();
    void onDownload();
    void onReset();
    void onGo();
    void onMips16();
    void onPlatform();
    void onOptions();
    void onCPUMaster();
    void onCPUSlave();
    void onReqEvent();
    void onMarginClicked(int margin, int line, Qt::KeyboardModifiers state);

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
	void create_main_widget();
	void create_dock_widgets();
	
private:
    QsciScintilla *textASM;
    QsciScintilla *textSource;
    QsciLexer *cpplexer;
	
	QTabWidget *main_tab_widget;
	EditorToolBar *editToolbar;
	
    QMenu *fileMenu;
    QMenu *debugMenu;
    QMenu *buildMenu;
    QToolBar *fileToolBar;
    QToolBar *debugToolBar;
    QToolBar *buildToolBar;

	//actions
private:
    //file actions
    QAction *newAct;
    QAction *openAct;
    QAction *aboutAct;
    //debug actions
    QAction *gdbRestartAct;
    QAction *gdbStopAct;
    QAction *gdbBreakAct;
    QAction *gdbStepNextAct;
    QAction *gdbStepIntoAct;
    QAction *gdbStepOverAct;
    QAction *gdbStepOutAct;
    QAction *gdbGotoAct;
    QAction *gdbSetpBPAct;
    
    //build actions
    QAction *gdbDownload;
    QAction *gdbReset;
    QAction *gdbStart;
    QAction *gdbMIPS16;
    QAction *gdbPlatform;
    QAction *gdbOptions;
    QAction *gdbCPUMaster;
    QAction *gdbCPUSlave;
    QAction *gdbRegEvent;

	//dockwidget
private:    
    QDockWidget* dwRegisters;
	QDockWidget* dwOutput;
	QDockWidget* dwCallstack;
    
    
};
//! [0]

#endif
