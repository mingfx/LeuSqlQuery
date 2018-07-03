
#include "MainWindow.h"
#include "connection.h"
#include "SignInWidget.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QString userName = "root";
	QString password = "123456";

	SignInWidget *signInWidget = new SignInWidget;
	signInWidget->show();
	/*if (!creatConnection(userName, password))
	{
		return 1;
	}*/
	/*QTextCodec *codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForLocale(codec);*/
	/*MainWindow w;
	w.show();*/
	return a.exec();

}
