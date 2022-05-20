#ifndef SHIPITEM_H
#define SHIPITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class ShipItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)

public:
    explicit ShipItem(QPixmap pixmap);

    qreal rotation() const;

    qreal y() const;

    void shootUp();

    void startFlight();

    void freezInPlace();

public slots:
    void setRotation(qreal rotation);

    void setY(qreal y);

    void rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve);

    void fallToGround();

signals:
private:
    qreal m_rotation;
    qreal m_y;

    QPropertyAnimation * yAnimation;
    QPropertyAnimation * rotationAnimation;
    qreal groundPosition;

};

#endif // SHIPITEM_H
