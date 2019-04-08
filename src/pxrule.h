#ifndef PXRULE_H
#define PXRULE_H

#include <QWidget>

class PxRule : public QWidget
{
	Q_OBJECT

private:
	QColor cd;
	QColor cl;
public:
	explicit PxRule(bool isVert, QColor coldark, QColor collight, QString ttl, QWidget *parent = 0);
	void recolor();

signals:

public slots:
};

#endif // PXRULE_H
