
#include "MainWindow.h"
#include "connection.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	if (!creatConnection())
	{
		return 1;
	}
	QTextCodec *codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForLocale(codec);
	MainWindow w;
	w.show();
	return a.exec();
}
