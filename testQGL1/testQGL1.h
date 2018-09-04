#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_testQGL1.h"

class testQGL1 : public QMainWindow
{
	Q_OBJECT

public:
	testQGL1(QWidget *parent = Q_NULLPTR);

private:
	Ui::testQGL1Class ui;
};
