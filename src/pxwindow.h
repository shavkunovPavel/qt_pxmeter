#ifndef PXWINDOW_H
#define PXWINDOW_H

#include <QMainWindow>
#include <QBasicTimer>

class QMouseEvent;
class QImage;
class PxRule;
class PxInfo;
class PxSize;
class PxColorInfo;

class PxWindow : public QMainWindow
{
	Q_OBJECT

private:
	PxInfo *info;
	PxSize *msize;
	PxColorInfo *colorinfo;
	int min_size;
	int step_finding;
	QColor bcolor_dark;
	QColor bcolor_light;
	int mclick_x;
	int mclick_y;
	QImage img_desk;
	PxRule *rhor;
	PxRule *rver;
	QBasicTimer timer_info;
	QBasicTimer timer_color;
	QPoint getTopPoint();
	QPoint getBottomPoint();
	QPoint getLeftPoint();
	QPoint getRightPoint();
	QPoint getRBottomPoint();
	QRgb getPx(int x_in, int y_in);
	void doImg();
	void debugImg();
	void mup(int st = 1);
	void mdown(int st = 1);
	void mleft(int st = 1);
	void mright(int st = 1);
	void rright(int st = 1);
	void unrright(int st =1);
	int doMoveY(int x_in, int y_in, int st, bool do_screen);
	void doQuickMoveY();
	int doMoveX(int x_in, int y_in, int st, bool do_screen);
	void findUp();
	void stretchUp();
	void findLeft();
	void stretchRight();
	void rup();
	void unrup();
	void rdown(int st = 1);
	void unrdown(int st = 1);
	void findDown();
	void stretchDown();
	void updMagnify();
	void updColorInfo();
	void recolor();
	void quickVert();
	void quickHor();
	void quickMin();
	void delColorInfo();
	void delInfo();
	void delSizeInput();
	void minimize_pxmeter();
	void move_to_cursor();
	void size_move();
	void move_to_size();

public:
	explicit PxWindow(QWidget *parent = 0);
	void setBig();

protected:
	virtual void keyPressEvent(QKeyEvent *kev);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void resizeEvent(QResizeEvent *re);
	virtual void moveEvent(QMoveEvent *);
	virtual void timerEvent(QTimerEvent *event);
signals:

public slots:
};

#endif // PXWINDOW_H
