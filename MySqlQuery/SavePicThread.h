#pragma once
#include <QThread>
#include <QObject>


class SavePicThread :public QThread
{
	Q_OBJECT
public:
	SavePicThread();
	SavePicThread(QString& toDir, QStringList& picDir, QObject *parent = 0);
	~SavePicThread();

	virtual void run();
	void setDir(QString& toDir, QStringList& picDir);
signals:
	void processFinished();
	void processProgress(int maxValue, int progress);
private:
	QString toDir;
	QStringList picDir;
};
