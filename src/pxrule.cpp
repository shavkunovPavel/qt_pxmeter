#include "pxrule.h"
#include <QRegion>
#include <QPalette>
#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>

PxRule::PxRule(bool isVert, QColor coldark, QColor collight, QString ttl, QWidget *parent) :
QWidget(parent, Qt::FramelessWindowHint | Qt::Window | Qt::NoDropShadowWindowHint | Qt::WindowStaysOnTopHint |
Qt::WindowDoesNotAcceptFocus)
{
	cd = coldark;
	cl = collight;
	QPalette pl = palette();
	pl.setColor(backgroundRole(), cd);
	setPalette(pl);
	setAutoFillBackground(true);
	setWindowTitle(ttl);
	QScreen *screen = qApp->screens().at(qApp->desktop()->screenNumber());
	if (isVert) {
		resize(1, screen->availableSize().height());
		setMaximumSize(1, height());
	} else {
		resize(screen->availableSize().width(), 1);
		setMaximumSize(width(), 1);
	}
	show();
}

void PxRule::recolor() {
	QPalette pal = palette();
	QColor cb = pal.color(backgroundRole());
	if (cb == cd) pal.setColor(backgroundRole(), cl);
	else pal.setColor(backgroundRole(), cd);
	setPalette(pal);
}
