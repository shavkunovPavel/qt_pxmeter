#ifndef PXZOOMIC_H
#define PXZOOMIC_H

#include <QLabel>
#include <QPixmap>
#include <QScreen>


class PxZoomic : public QLabel
{
	Q_OBJECT

private:
	QPixmap pix;

public:
	explicit PxZoomic(QWidget *parent = 0);
	void show_desk(QPoint pnt, qreal x_off, qreal y_off, QScreen *screen);

protected:
	virtual void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // PXZOOMIC_H
