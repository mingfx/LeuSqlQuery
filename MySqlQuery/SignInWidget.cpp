#include "SignInWidget.h"
#include "connection.h"
#include "MainWindow.h"
#include <QMessageBox>
#include <QDebug>

SignInWidget::SignInWidget()
{
	uiSignIn.setupUi(this);
}
SignInWidget::~SignInWidget()
{
	//delete uiSignIn;
}

void SignInWidget::on_SignIn_clicked()
{
	QString userName = uiSignIn.lineEdit->text();
	QString passWord = uiSignIn.lineEdit_2->text();
	if (creatConnection(userName, passWord))
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("登录成功"), QMessageBox::Ok);
		QTextCodec *codec = QTextCodec::codecForName("GB2312");
		QTextCodec::setCodecForLocale(codec);
		isOpenSuccess = true;
		MainWindow *m = new MainWindow;
		m->show();
		SignInWidget::close();
	}
	else
	{
		QMessageBox::warning(this, tr("waring"), tr("your passward is wrong"), QMessageBox::Yes);
		uiSignIn.lineEdit->clear();  //清空姓名nameLine
		uiSignIn.lineEdit_2->clear();  //清空密码passwardLine
		uiSignIn.lineEdit->setFocus();  //将鼠标重新定位到nameLine
	}

}

void SignInWidget::on_Exit_clicked()
{

}