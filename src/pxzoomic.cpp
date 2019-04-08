#include "pxzoomic.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QString>


PxZoomic::PxZoomic(QWidget *parent) : QLabel(parent)
{}

void PxZoomic::paintEvent(QPaintEvent *) {
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, false);
	p.scale(3, 3);
	p.drawPixmap(0, 0, pix);
}

void PxZoomic::show_desk(QPoint pnt, qreal x_off, qreal y_off, QScreen *screen) {
	int w = width();
	int h = height();
	int x_in = pnt.x()-w*x_off;
	int y_in = pnt.y()-h*y_off;
	pix = screen->grabWindow(qApp->desktop()->winId(), x_in, y_in, w, h);
	update();
}
