#ifndef QTAPP_H
#define QTAPP_H

#include <QtWidgets/QMainWindow>
#include "ui_qtapp.h"

class qtApp : public QMainWindow
{
	Q_OBJECT

public:
	qtApp(QWidget *parent = 0);
	~qtApp();

private:
	Ui::qtAppClass ui;
};

#endif // QTAPP_H
