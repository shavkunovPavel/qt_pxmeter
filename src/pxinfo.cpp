#include <iostream>
#include "pxinfo.h"
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMargins>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBoxLayout>
#include <QScreen>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QDebug>
#include "pxwindow.h"

PxInfo::PxInfo(QWidget *parent) :
QWidget(parent, Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::NoDropShadowWindowHint)
{
	pxmeter = (PxWindow *) parent;
	int winfo = 300;
	QRect rec = QApplication::desktop()->screenGeometry();
	setGeometry(rec.width()-winfo, 0, winfo, winfo);
	setCursor(Qt::SizeAllCursor);
	setWindowTitle("zoom info");

	gui();
	show();
}

void PxInfo::gui() {
	scrLeftTop = new PxZoomic(this);
	scrRightTop = new PxZoomic(this);
	scrLeftBottom = new PxZoomic(this);
	scrRightBottom = new PxZoomic(this);
	QGridLayout *grid = new QGridLayout();
	grid->addWidget(scrLeftTop, 0, 0);
	grid->addWidget(scrRightTop, 0, 1);
	grid->addWidget(scrLeftBottom, 1, 0);
	grid->addWidget(scrRightBottom, 1, 1);
	grid->setSpacing(1);
	grid->setMargin(1);
	setLayout(grid);
}

void PxInfo::updateMagnify(QPoint top_left, QPoint top_right, QPoint bottom_left, QPoint bottom_right) {
	QScreen *screen = qApp->screens().at(qApp->desktop()->screenNumber());
	scrLeftTop->show_desk(top_left, 0.11, 0.1, screen);
	scrRightTop->show_desk(top_right, 0.2, 0.1, screen);
	scrLeftBottom->show_desk(bottom_left, 0.115, 0.2, screen);
	scrRightBottom->show_desk(bottom_right, 0.19, 0.2, screen);
}

void PxInfo::mousePressEvent(QMouseEvent *event) {
	mclick_x = event->x();
	mclick_y = event->y();
}

void PxInfo::mouseMoveEvent(QMouseEvent *event) {
	if (mclick_x > 0 && (event->buttons() & Qt::LeftButton)) {
		this->move(event->globalX()-mclick_x, event->globalY()-mclick_y);
	}
}

void PxInfo::mouseReleaseEvent(QMouseEvent *) {
	mclick_x = -1;
	mclick_y = -1;
	pxmeter->activateWindow();
}
