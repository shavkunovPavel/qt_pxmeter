#include "pxcoloric.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>

PxColoric::PxColoric(QWidget *parent) : QLabel(parent)
{
	setCursor(Qt::PointingHandCursor);
	setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
	setText("#ffffff");
	setAlignment(Qt::AlignCenter);
	QPalette pal;
	pal.setColor(QPalette::Window, QColor(255, 255, 255));
	setPalette(pal);
	setAutoFillBackground(true);
}

void PxColoric::update_lbl() {
	QImage img = pix.toImage();
	QRgb px = img.pixel(0, 0);
	img.invertPixels();
	QRgb ipx = img.pixel(0, 0);
	QPalette pal;
	pal.setColor(QPalette::Window, px);
	pal.setColor(QPalette::WindowText, ipx);
	setPalette(pal);
	setText(QColor(px).name());
}

void PxColoric::show_px(QPoint pnt, QScreen *screen) {
	int w = pnt.x();
	int h = pnt.y();
	pix = screen->grabWindow(qApp->desktop()->winId(), w, h, w, h);
	update_lbl();
}
