#pragma once
#include "ui_SignInWidget.h"


class SignInWidget :public QWidget
{
	Q_OBJECT
public:
	SignInWidget();
	~SignInWidget();
	bool isOpenSuccess = false;

	Ui::SignInForm uiSignIn;
//private:

private slots :
	//void on_SignInButton_clicked(); 
	void on_SignIn_clicked();
	void on_Exit_clicked();
};
