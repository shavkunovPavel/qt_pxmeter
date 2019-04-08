#include "pxcolorinfo.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBoxLayout>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include "pxcoloric.h"
#include "pxwindow.h"


PxColorInfo::PxColorInfo(QWidget *parent) :
QWidget(parent, Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::NoDropShadowWindowHint)
{
	pxmeter = (PxWindow *) parent;
	setWindowTitle("color info");
	setGeometry(0, 0, 500, 200);
	setCursor(Qt::SizeAllCursor);
	gui();
	show();
}

void PxColorInfo::gui() {
	scrLeftTop = new PxColoric(this);
	scrRightTop = new PxColoric(this);
	scrLeftBottom = new PxColoric(this);
	QGridLayout *grid = new QGridLayout();
	grid->addWidget(scrLeftTop, 0, 0);
	grid->addWidget(scrRightTop, 0, 1);
	grid->addWidget(scrLeftBottom, 1, 0);
	setLayout(grid);
}

void PxColorInfo::updateColorInfo(QPoint top_left, QPoint top_right, QPoint bottom_left) {
	QScreen *screen = qApp->screens().at(qApp->desktop()->screenNumber());
	scrLeftTop->show_px(top_left, screen);
	scrRightTop->show_px(top_right, screen);
	scrLeftBottom->show_px(bottom_left, screen);
}

void PxColorInfo::mousePressEvent(QMouseEvent *event) {
	mclick_x = event->x();
	mclick_y = event->y();
}

void PxColorInfo::mouseMoveEvent(QMouseEvent *event) {
	if (mclick_x > 0 && (event->buttons() & Qt::LeftButton)) {
		this->move(event->globalX()-mclick_x, event->globalY()-mclick_y);
	}
}

void PxColorInfo::mouseReleaseEvent(QMouseEvent *) {
	mclick_x = -1;
	mclick_y = -1;
	pxmeter->activateWindow();
}
