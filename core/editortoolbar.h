#ifndef EDITORTOOLBAR_H
#define EDITORTOOLBAR_H

#include <utils/styledbar.h>


struct EditorToolBarPrivate;

class EditorToolBar : public Utils::StyledBar
{
    Q_OBJECT

public:
    explicit EditorToolBar(QWidget *parent = 0);
    virtual ~EditorToolBar();

signals:
    void proSelectionActivated(int row);

protected:

    EditorToolBarPrivate *d;
};



#endif // EDITORTOOLBAR_H


