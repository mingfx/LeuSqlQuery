#pragma once
#include "ui_AddWidget.h"

class AddWidget :public QWidget
{
	Q_OBJECT
public:
	AddWidget(QWidget *parent = Q_NULLPTR);
	~AddWidget();

	Ui::AddWidget uiAdd;
private:

	private slots :
		void on_SelectButton_clicked();
};
