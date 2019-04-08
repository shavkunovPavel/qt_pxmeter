#ifndef PXCOLORINFO_H
#define PXCOLORINFO_H

#include <QWidget>

class QLabel;
class PxColoric;
class PxWindow;

class PxColorInfo : public QWidget
{
		Q_OBJECT

	public:
		explicit PxColorInfo(QWidget *parent = 0);
		void updateColorInfo(QPoint top_left, QPoint top_right, QPoint bottom_left);

	private:
		int mclick_x;
		int mclick_y;
		PxWindow *pxmeter;
		PxColoric *scrLeftTop;
		PxColoric *scrRightTop;
		PxColoric *scrLeftBottom;
		void gui();
	protected:
		virtual void mousePressEvent(QMouseEvent *event);
		virtual void mouseMoveEvent(QMouseEvent *event);
		virtual void mouseReleaseEvent(QMouseEvent *);
};

#endif // PXCOLORINFO_H
