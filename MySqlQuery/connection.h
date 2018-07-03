#pragma once

#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QTextCodec>

static bool creatConnection(QString userNmae,QString password)
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setDatabaseName("mysql");
	db.setUserName(userNmae);
	db.setPassword(password);
	/*db.setUserName("root");
	db.setPassword("123456");*/
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	//QTextCodec *codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForLocale(codec);
	

	if (!db.open())
	{
		qDebug() << "Failed to connect to root mydata";
		return false;
	}
	else
	{
		qDebug() << "open";
	}
	//QSqlQuery query(db);
	return true;
}

#endif
