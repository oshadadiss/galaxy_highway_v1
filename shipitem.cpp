#include "shipitem.h"
#include <QGraphicsScene>

ShipItem::ShipItem(QPixmap pixmap)
{
    setPixmap(pixmap);

    groundPosition = scenePos().y() + 290;

    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);
   // yAnimation->start();
    rotationAnimation = new QPropertyAnimation(this, "rotation", this);
   // rotateTo(90,1200,QEasingCurve::InQuad);
}

qreal ShipItem::rotation() const
{
    return m_rotation;
}

qreal ShipItem::y() const
{
    return m_y;
}

void ShipItem::shootUp()
{
    yAnimation->stop();
    rotationAnimation->stop();

    qreal curPosY = y();
    yAnimation->setStartValue(curPosY);
    yAnimation->setEndValue(curPosY - scene()->sceneRect().height()/8);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(285);


    connect(yAnimation,&QPropertyAnimation::finished,[=](){
       fallToGround();
    });

    yAnimation->start();

    rotateTo(-20,200, QEasingCurve::OutCubic);
}

void ShipItem::startFlight()
{
    yAnimation->start();
    rotateTo(90,1200,QEasingCurve::InQuad);
}

void ShipItem::freezInPlace()
{
    yAnimation->stop();
    rotationAnimation->stop();
}

void ShipItem::setRotation(qreal rotation)
{
    m_rotation = rotation;
    QPointF c = boundingRect().center();
    QTransform t;
    t.translate(c.x(),c.y());
    t.rotate(rotation);
    t.translate(-c.x(),-c.y());
    setTransform(t);
}

void ShipItem::setY(qreal y)
{
    moveBy(0,y - m_y);
    m_y = y;
}

void ShipItem::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);
    rotationAnimation->start();
}

void ShipItem::fallToGround()
{
    if(y() < groundPosition){

        rotationAnimation->stop();
        //yAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEndValue(groundPosition);
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setDuration(1000);
        yAnimation->start();

        rotateTo(90,1200,QEasingCurve::InQuad);

    }
}
