#include "editortoolbar.h"

#include <QComboBox>
#include <QToolButton>
#include <QVBoxLayout>

struct EditorToolBarPrivate
{
    explicit EditorToolBarPrivate(QWidget *parent, EditorToolBar *q);

    QComboBox *m_proList;
    QComboBox *m_fileList;
    QComboBox *m_funcList;	
	QComboBox *m_modeList;	



    bool m_isStandalone;
};

EditorToolBarPrivate::EditorToolBarPrivate(QWidget *parent, EditorToolBar *q) :
    m_proList(new QComboBox(q)),
	m_fileList(new QComboBox(q)),
	m_funcList(new QComboBox(q)),
	m_modeList(new QComboBox(q)),	
    m_isStandalone(false)
{
}


EditorToolBar::EditorToolBar(QWidget *parent) :
        StyledBar(parent), d(new EditorToolBarPrivate(parent, this))
{

	//Combo Box pro  
    d->m_proList->setProperty("hideicon", true);
    d->m_proList->setProperty("notelideasterisk", true);
    d->m_proList->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    d->m_proList->setMinimumContentsLength(12);
    d->m_proList->setMaxVisibleItems(40);
    d->m_proList->setEditable(false);


	//Combo Box file  
    d->m_fileList->setProperty("hideicon", true);
    d->m_fileList->setProperty("notelideasterisk", true);
    d->m_fileList->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    d->m_fileList->setMinimumContentsLength(32);
    d->m_fileList->setMaxVisibleItems(40);
    d->m_fileList->setEditable(true);
    d->m_fileList->setInsertPolicy(QComboBox::NoInsert);
	
	//Combo Box function 
    d->m_funcList->setProperty("hideicon", true);
    d->m_funcList->setProperty("notelideasterisk", true);
    d->m_funcList->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    d->m_funcList->setMinimumContentsLength(48);
    d->m_funcList->setMaxVisibleItems(40);
    d->m_funcList->setEditable(true);
    d->m_fileList->setInsertPolicy(QComboBox::NoInsert);
	
	//Combo Box mode
	d->m_modeList->setProperty("hideicon", true);
	d->m_modeList->setProperty("notelideasterisk", true);
	d->m_modeList->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	d->m_modeList->setMinimumContentsLength(10);
	d->m_modeList->setMaxVisibleItems(40);
    d->m_modeList->setEditable(false);

	connect(d->m_proList, SIGNAL(activated(int)), this, SIGNAL(proSelectionActivated(int)));


    QHBoxLayout *toplayout = new QHBoxLayout(this);
    toplayout->setSpacing(10);
    toplayout->setMargin(0);
    toplayout->addWidget(d->m_proList);
    toplayout->addWidget(d->m_fileList);
    toplayout->addWidget(d->m_funcList);
    toplayout->addWidget(d->m_modeList);
    toplayout->addStretch();

    setLayout(toplayout);
}

EditorToolBar::~EditorToolBar()
{
    delete d;
}

