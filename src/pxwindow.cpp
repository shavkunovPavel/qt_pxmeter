#include "pxwindow.h"
#include <QPalette>
#include <QPixmap>
#include <QApplication>
#include <QRgb>
#include <QRegion>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QScreen>
#include <QThread>
#include <QDebug>
#include <QPainter>
#include <QInputDialog>
#include <iostream>
#include "pxinfo.h"
#include "pxrule.h"
#include "pxsize.h"
#include "pxcolorinfo.h"

using namespace std;

PxWindow::PxWindow(QWidget *parent) : QMainWindow
(parent ,
Qt::FramelessWindowHint | Qt::Window | Qt::NoDropShadowWindowHint | Qt::WindowStaysOnTopHint
)
{
	min_size = 1;
	step_finding = 1;
	QRect rec = QApplication::desktop()->screenGeometry();
	resize(50, 50);
	move(rec.width()*0.5, rec.height()*0.5);
	QColor col_dark = QColor(231, 75, 75);
	QColor col_light = QColor(255, 225, 75);
	bcolor_dark = QColor(13, 0, 13);
	bcolor_light = QColor(255, 255, 255);
	setCursor(Qt::SizeAllCursor);
	QPalette pal = palette();
	pal.setColor(backgroundRole(), bcolor_dark);
	setPalette(pal);
	setAutoFillBackground(true);
	rhor = new PxRule(false, col_dark, col_light, "hor line", parent);
	rver = new PxRule(true, col_dark, col_light, "vert line", parent);
	msize = new PxSize(this);
	info = 0;
	colorinfo = 0;
	setWindowTitle("PxMeter");
	size_move();
	show();
}

void PxWindow::setBig() {
	resize(50, 50);
	this->activateWindow();
}

void PxWindow::recolor() {
	QPalette pal = palette();
	QColor cb = pal.color(backgroundRole());
	if (cb == bcolor_dark) pal.setColor(backgroundRole(), bcolor_light);
	else pal.setColor(backgroundRole(), bcolor_dark);
	setPalette(pal);
	rhor->recolor();
	rver->recolor();
}

void PxWindow::doImg() {
	QScreen *screen = qApp->screens().at(qApp->desktop()->screenNumber());
	if (screen) {
		QPixmap pix = screen->grabWindow(qApp->desktop()->winId());
		img_desk = pix.toImage();
	}
}

QPoint PxWindow::getTopPoint() {
	QPoint ret_pnt(pos().x(), pos().y()-1);
	return ret_pnt;
}

QPoint PxWindow::getBottomPoint() {
	QPoint ret_pnt(pos().x(), pos().y()+height());
	return ret_pnt;
}

QPoint PxWindow::getLeftPoint() {
	QPoint ret_pnt(pos().x()-1, pos().y());
	return ret_pnt;
}

QPoint PxWindow::getRightPoint() {
	QPoint ret_pnt(pos().x()+width(), pos().y());
	return ret_pnt;
}

QPoint PxWindow::getRBottomPoint() {
	QPoint ret_pnt(pos().x()+width()-1, pos().y()+height());
	return ret_pnt;
}

QRgb PxWindow::getPx(int x_in, int y_in) {
	QRgb px = img_desk.pixel(x_in, y_in);
	return px;
}

void PxWindow::doQuickMoveY() {}

void PxWindow::quickVert() {
	QPoint pnt_start_top = getTopPoint();
	QPoint pnt_start_bottom = getBottomPoint();
	int new_yt = doMoveY(pnt_start_top.x(), pnt_start_top.y(), -1, true);
	int new_yb = doMoveY(pnt_start_bottom.x(), pnt_start_bottom.y(), 1, false);
	move(pnt_start_top.x(), new_yt+1);
	resize(width(), new_yb-new_yt-1);
}

void PxWindow::quickHor() {
	QPoint pnt_start_left = getLeftPoint();
	QPoint pnt_start_right = getRightPoint();
	int new_xl = doMoveX(pnt_start_left.x(), pnt_start_left.y(), -1, true);
	int new_xr = doMoveX(pnt_start_right.x(), pnt_start_right.y(), 1, false);
	move(new_xl+1, pnt_start_left.y());
	resize(new_xr-new_xl-1, height());
}

void PxWindow::quickMin() {
	int w = width();
	int h = height();
	if (h == 3 && w > 3) w = 3;
	else if (h > 3) h = 3;
	else if (h == 3 && w == 3) {
		w = 30;
		h = 30;
	}
	resize(w, h);
}

void PxWindow::debugImg() {
	doImg();

	QPoint pp = getTopPoint();
	img_desk.setPixel(pp.x(), pp.y(), qRgb(255, 255, 0));
	img_desk.setPixel(pp.x(), pp.y()+1, qRgb(0, 0, 255));
	img_desk.setPixel(pp.x(), pp.y()-1, qRgb(0, 0, 255));
	img_desk.setPixel(pp.x()+1, pp.y(), qRgb(0, 0, 255));
	img_desk.setPixel(pp.x()-1, pp.y(), qRgb(0, 0, 255));

	pp = getBottomPoint();
	img_desk.setPixel(pp.x(), pp.y(), qRgb(255, 255, 0));
	img_desk.setPixel(pp.x(), pp.y()+1, qRgb(0, 0, 255));
	img_desk.setPixel(pp.x(), pp.y()-1, qRgb(0, 0, 255));
	img_desk.setPixel(pp.x()+1, pp.y(), qRgb(0, 0, 255));
	img_desk.setPixel(pp.x()-1, pp.y(), qRgb(0, 0, 255));

	pp = getLeftPoint();
	img_desk.setPixel(pp.x(), pp.y(), qRgb(255, 0, 0));
	img_desk.setPixel(pp.x(), pp.y()+1, qRgb(0, 0, 255));
	img_desk.setPixel(pp.x(), pp.y()-1, qRgb(0, 0, 255));
	img_desk.setPixel(pp.x()+1, pp.y(), qRgb(0, 0, 255));
	img_desk.setPixel(pp.x()-1, pp.y(), qRgb(0, 0, 255));

	pp = getRightPoint();
	img_desk.setPixel(pp.x(), pp.y(), qRgb(255, 255, 0));
	img_desk.setPixel(pp.x(), pp.y()+1, qRgb(0, 0, 255));
	img_desk.setPixel(pp.x(), pp.y()-1, qRgb(0, 0, 255));
	img_desk.setPixel(pp.x()+1, pp.y(), qRgb(0, 0, 255));
	img_desk.setPixel(pp.x()-1, pp.y(), qRgb(0, 0, 255));

	pp = getRBottomPoint();
	img_desk.setPixel(pp.x(), pp.y(), qRgb(255, 255, 0));
	img_desk.setPixel(pp.x(), pp.y()+1, qRgb(0, 0, 255));
	img_desk.setPixel(pp.x(), pp.y()-1, qRgb(0, 0, 255));
	img_desk.setPixel(pp.x()+1, pp.y(), qRgb(0, 0, 255));
	img_desk.setPixel(pp.x()-1, pp.y(), qRgb(0, 0, 255));

	QString format ="png";
	img_desk.save("/home/pasha/temp/scr.png", format.toLatin1().constData());

}

void PxWindow::mousePressEvent(QMouseEvent *event) {
	if (event->button()==Qt::RightButton) {
		minimize_pxmeter();
	} else {
		mclick_x = event->x();
		mclick_y = event->y();
	}
}

void PxWindow::mouseMoveEvent(QMouseEvent *event) {
	if (mclick_x > 0 && (event->buttons() & Qt::LeftButton)) {
		this->move(event->globalX()-mclick_x, event->globalY()-mclick_y);
	}
}

void PxWindow::mouseReleaseEvent(QMouseEvent *) {
	mclick_x = -1;
	mclick_y = -1;
}

void PxWindow::mup(int st) {
	move(x(), y()-st);
}

void PxWindow::mdown(int st) {
	move(x(), y()+st);
}

void PxWindow::mleft(int st) {
	move(x()-st, y());
}

void PxWindow::mright(int st) {
	move(x()+st, y());
}

void PxWindow::rright(int st) {
	resize(width()+st, height());
}

void PxWindow::unrright(int st) {
	int neww = width()-st;
	if (neww < min_size) neww = min_size;
	resize(neww, height());
}

void PxWindow::rup() {
	mup();
	resize(width(), height()+1);
}

void PxWindow::unrup() {
	mdown();
	resize(width(), height()-1);
}

void PxWindow::rdown(int st) {
	resize(width(), height()+st);
}

void PxWindow::unrdown(int st) {
	int newh = height()-st;
	if (newh < min_size) newh = min_size;
	resize(width(), newh);
}

int PxWindow::doMoveY(int x_in, int y_in, int st, bool do_screen) {
	if (do_screen) doImg();
	int ret_val = y_in;
	QRgb pix_prev = getPx(x_in, ret_val);
	QRgb pix_next = pix_prev;
	while (pix_prev == pix_next)
	{
		ret_val = ret_val + st;
		pix_next = getPx(x_in, ret_val);
	}
	return ret_val;
}

int PxWindow::doMoveX(int x_in, int y_in, int st, bool do_screen) {
	if (do_screen) doImg();
	int ret_val = x_in;
	QRgb pix_prev = getPx(ret_val, y_in);
	QRgb pix_next = pix_prev;
	while (pix_prev == pix_next)
	{
		ret_val = ret_val + st;
		pix_next = getPx(ret_val, y_in);
	}
	return ret_val;
}

void PxWindow::findUp() {
	QPoint pnt_start = getTopPoint();
	int new_y = doMoveY(pnt_start.x(), pnt_start.y(), -1, true);
	move(pnt_start.x(), new_y+1);
}

void PxWindow::stretchDown() {
	QPoint pnt_start = getBottomPoint();
	int new_y = doMoveY(pnt_start.x(), pnt_start.y(), 1, true);
	resize(width(), height()+(new_y-pnt_start.y()));
}

void PxWindow::findLeft() {
	QPoint pnt_start = getLeftPoint();
	int new_x = doMoveX(pnt_start.x(), pnt_start.y(), -1, true);
	move(new_x+1, pnt_start.y());
}

void PxWindow::stretchRight() {
	QPoint pnt_start = getRightPoint();
	int new_x = doMoveX(pnt_start.x(), pnt_start.y(), 1, true);
	resize(width()+(new_x-pnt_start.x()), height());
}

void PxWindow::delColorInfo() {
	if (colorinfo) {
		delete colorinfo;
		colorinfo = 0;
		timer_color.stop();
	}
}

void PxWindow::delInfo() {
	if (info) {
		delete info;
		info = 0;
		timer_info.stop();
	}
}

void PxWindow::minimize_pxmeter() {
	QApplication::exit();

	delColorInfo();
	delInfo();
	QRect rec = QApplication::desktop()->screenGeometry();
	quickMin();
	move(rec.width(), rec.height());
	size_move();
}

void PxWindow::move_to_cursor() {
	setBig();
	move(cursor().pos().x()-width()*0.5, cursor().pos().y()-height()*0.5);
}

void PxWindow::keyPressEvent(QKeyEvent *kev) {
	switch (kev->key()) {
	case Qt::Key_Left:
		if (kev->modifiers() & Qt::ControlModifier) findLeft();
		else if (kev->modifiers() & Qt::ShiftModifier) unrright();
		else mleft();
		break;
	case Qt::Key_Home:
		if (kev->modifiers() & Qt::ShiftModifier) unrright(50);
		else mleft(50);
		break;
	case Qt::Key_Right:
		if ((kev->modifiers() & Qt::ShiftModifier) && (kev->modifiers() & Qt::ControlModifier)) stretchRight();
		else if (kev->modifiers() & Qt::ShiftModifier) rright();
		else mright();
		break;
	case Qt::Key_End:
		if (kev->modifiers() & Qt::ShiftModifier) rright(50);
		else mright(50);
		break;
	case Qt::Key_Up:
		if (kev->modifiers() & Qt::ControlModifier) {
			findUp();
		} else if (kev->modifiers() & Qt::ShiftModifier) {
			unrdown();
		} else {
			mup();
		}
		break;
	case Qt::Key_PageUp:
		if (kev->modifiers() & Qt::ShiftModifier) unrdown(50);
		else mup(50);
		break;
	case Qt::Key_Down:
		if ((kev->modifiers() & Qt::ShiftModifier) && (kev->modifiers() & Qt::ControlModifier)) stretchDown();
		else if (kev->modifiers() & Qt::ShiftModifier) rdown();
		else mdown();
		break;
	case Qt::Key_PageDown:
		if (kev->modifiers() & Qt::ShiftModifier) rdown(50);
		else mdown(50);
		break;
	case Qt::Key_F10: case Qt::Key_X:
		QApplication::exit();
		break;
	case Qt::Key_Q:
		if (!colorinfo) {
			colorinfo = new PxColorInfo(this);
			this->activateWindow();
			timer_color.start(100, this);
		} else {
			delColorInfo();
		}
		break;
	case Qt::Key_Z:
		if (!info) {
			info = new PxInfo(this);
			this->activateWindow();
			timer_info.start(100, this);
		} else {
			delInfo();
		}
		break;
	case Qt::Key_C:
		recolor();
		break;
	case Qt::Key_V:
		if (kev->modifiers() & Qt::ControlModifier) {
			bool ok;
			int i = QInputDialog::getInt(this, tr("New Height"),
			"", height(), 3, 3000, 10, &ok, Qt::WindowStaysOnTopHint);
			if (ok) resize(width(), i);
		} else quickVert();
		break;
	case Qt::Key_H:
		if (kev->modifiers() & Qt::ControlModifier) {
			bool ok;
			int i = QInputDialog::getInt(this, tr("New Width"),
			"", width(), 3, 3000, 10, &ok, Qt::WindowStaysOnTopHint);
			if (ok) resize(i, height());
		} else quickHor();
		break;
	case Qt::Key_B:
		quickMin();
		break;
	case Qt::Key_M:
		move_to_cursor();
		break;
	case Qt::Key_D:
		if (kev->modifiers() & Qt::ControlModifier) {
//			qDebug() << "debug image";
//			debugImg();
		} else {
			minimize_pxmeter();
		}
		break;
	case Qt::Key_N:
		setBig();
		break;
	case Qt::Key_S:
		if (kev->modifiers() & Qt::ControlModifier) {
			size_move();
		} else {
			setBig();
			move(msize->geometry().x() + msize->width() + 10, msize->geometry().y() + msize->height() + 10);
		}
		break;
	default:
		break;
	}
}

void PxWindow::updMagnify() {
	if (info) {
		info->updateMagnify(getLeftPoint(), getRightPoint(), getBottomPoint(), getRBottomPoint());
	}
}

void PxWindow::updColorInfo() {
	if (colorinfo) {
		QPoint t = getLeftPoint();
		colorinfo->updateColorInfo(QPoint(t.x(), t.y()-1), getRightPoint(), getBottomPoint());
	}
}

void PxWindow::resizeEvent(QResizeEvent *re) {
	int w_info = width();
	int bas = 0;
	bas = re->oldSize().width() != re->size().width() ? w_info : height();

//	QRegion rgn(0, 0, w_info-30, height()-30, QRegion::Rectangle);
//	setMask(rgn);

	if (msize->isVisible()) {
		msize->setInfoSize(w_info, height(), bas);
	}
}

void PxWindow::moveEvent(QMoveEvent *) {
	rhor->move(rhor->x(), geometry().y()+step_finding);
	rver->move(geometry().x()+step_finding, rver->y());
}

void PxWindow::size_move() {
	msize->move(geometry().x()-msize->width()-10, geometry().y()-msize->height()-10);
}

void PxWindow::timerEvent(QTimerEvent *event) {
	if (event->timerId() == timer_info.timerId()) {
		updMagnify();
	} else if (event->timerId() == timer_color.timerId()) {
		updColorInfo();
	} else {
		QWidget::timerEvent(event);
	}
}
