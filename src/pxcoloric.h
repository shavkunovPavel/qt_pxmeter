#ifndef PXCOLORIC_H
#define PXCOLORIC_H

#include <QLabel>
#include <QPixmap>
#include <QScreen>


class PxColoric : public QLabel
{
	Q_OBJECT

	private:
		QPixmap pix;
		void update_lbl();

	public:
		explicit PxColoric(QWidget *parent = 0);
		void show_px(QPoint pnt, QScreen *screen);

	protected:

	signals:

	public slots:
};

#endif // PXCOLORIC_H
