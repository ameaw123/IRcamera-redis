#pragma once

#include <QtWidgets/QWidget>
#include "ui_UserDemo.h"

class UserDemo : public QWidget
{
	Q_OBJECT

public:
	UserDemo(QWidget *parent = Q_NULLPTR);

private:
	Ui::UserDemoClass ui;
};
