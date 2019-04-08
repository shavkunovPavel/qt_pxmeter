#include "pxsize.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QRegion>
#include <QDebug>
#include <QMouseEvent>
#include "pxwindow.h"

PxSize::PxSize(QWidget *parent) :
QWidget(parent, Qt::FramelessWindowHint | Qt::Window | Qt::NoDropShadowWindowHint | Qt::WindowStaysOnTopHint)
{
	pxmeter = (PxWindow *) parent;
	lbl = new QLabel("1111", this);
	lbl->setAlignment(Qt::AlignCenter);
	QFont ff = lbl->font();
	ff.setPointSize(13);
	lbl->setFont(ff);
	QPalette pal = palette();
	pal.setColor(foregroundRole(), QColor(255, 255, 255));
	pal.setColor(backgroundRole(), QColor(113, 0, 113));
	setPalette(pal);
	setCursor(Qt::PointingHandCursor);
	QBoxLayout *box = new QBoxLayout(QBoxLayout::LeftToRight);
	box->addWidget(lbl);
	setLayout(box);

	show();
}

void PxSize::setInfoSize(int w_in, int h_in, int bas_in) {
	lbl->setText(QString::number(bas_in));
	setToolTip(QString::number(w_in) + "x" + QString::number(h_in));
}

void PxSize::mousePressEvent(QMouseEvent *event) {
	mclick_x = event->x();
	mclick_y = event->y();
}

void PxSize::mouseMoveEvent(QMouseEvent *event) {
	if (mclick_x > 0 && (event->buttons() & Qt::LeftButton)) {
		this->move(event->globalX()-mclick_x, event->globalY()-mclick_y);
	}
}

void PxSize::mouseReleaseEvent(QMouseEvent *) {
	mclick_x = -1;
	mclick_y = -1;
	pxmeter->activateWindow();
}
