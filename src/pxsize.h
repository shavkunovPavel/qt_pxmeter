#ifndef PXSIZE_H
#define PXSIZE_H

#include <QWidget>

class QMouseEvent;
class QLabel;
class PxWindow;

class PxSize : public QWidget
{
		Q_OBJECT

private:
	PxWindow *pxmeter;
	QLabel *lbl;
	int mclick_x;
	int mclick_y;
public:
	explicit PxSize(QWidget *parent = 0);
	void setInfoSize(int w_in, int h_in, int bas_in);
protected:
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *);

signals:

public slots:

};

#endif // PXSIZE_H
