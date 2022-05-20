#ifndef ALIENITEM_H
#define ALIENITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPathItem>
#include <QPropertyAnimation>

class AlienItem :public QObject , public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)

public:
    explicit AlienItem();
    ~AlienItem();

    qreal x() const;

    void freezInPlace();

signals:
    void collideFail();

public slots:

    void setX(qreal x);

private:

    bool collision();

    QGraphicsPixmapItem * topAlien;
    QGraphicsPixmapItem * bottomAlien;
    QPropertyAnimation * xAnimation;
    int yPos;

    qreal m_x;
    bool pastShip;
};

#endif // ALIENITEM_H
