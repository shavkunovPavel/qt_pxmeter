#ifndef PXINFO_H
#define PXINFO_H

#include <QWidget>
#include <QPixmap>
#include <pxzoomic.h>
#include <QMouseEvent>

class QLabel;
class PxWindow;

class PxInfo : public QWidget
{
	Q_OBJECT

	private:
		PxWindow *pxmeter;
		int mclick_x;
		int mclick_y;
		PxZoomic *scrLeftTop;
		PxZoomic *scrRightTop;
		PxZoomic *scrLeftBottom;
		PxZoomic *scrRightBottom;
		void gui();

	public:
		explicit PxInfo(QWidget *parent = 0);
		void updateMagnify(QPoint top_left, QPoint top_right, QPoint bottom_left, QPoint bottom_right);

	protected:
		virtual void mousePressEvent(QMouseEvent *event);
		virtual void mouseMoveEvent(QMouseEvent *event);
		virtual void mouseReleaseEvent(QMouseEvent *);

	signals:

	public slots:
};

#endif // PXINFO_H
