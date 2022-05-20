#include "alienitem.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsScene>
#include "shipitem.h"
#include "scene.h"

AlienItem::AlienItem():
    topAlien(new QGraphicsPixmapItem(QPixmap(":/Images/UFO.png"))),
    bottomAlien(new QGraphicsPixmapItem(QPixmap(":/Images/UFO.png"))),
    pastShip(false)
{
    topAlien->setPos(QPointF(0,0) - QPointF(topAlien->boundingRect().width()/2,
                                            topAlien->boundingRect().height() + 60));
    bottomAlien->setPos(QPointF(0,0) + QPointF(- bottomAlien->boundingRect().width()/2,
                                                60));

    addToGroup(topAlien);
    addToGroup(bottomAlien);

    yPos = QRandomGenerator::global()->bounded(150);
    int xRandom = QRandomGenerator::global()->bounded(200);

    setPos(QPointF(0,0) + QPointF(260 + xRandom, yPos));

    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(260 + xRandom);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);

    connect(xAnimation,&QPropertyAnimation::finished,[=](){
       scene()->removeItem(this);
       delete this;
    });

    xAnimation->start();

}

AlienItem::~AlienItem()
{
    delete topAlien;
    delete bottomAlien;
}

qreal AlienItem::x() const
{
    return m_x;
}

void AlienItem::freezInPlace()
{
    xAnimation->stop();
}

void AlienItem::setX(qreal x)
{
    m_x = x;

    if(x < 0 && !pastShip){
        pastShip = true;
        QGraphicsScene * mScene = scene();
        Scene * myScene = dynamic_cast<Scene *>(mScene);
        if(mScene){
            myScene->incrementScore();
        }
    }


    if(collision()){
        emit collideFail();
    }
    setPos(QPointF(0,0) + QPointF(x, yPos));
}

bool AlienItem::collision()
{
    QList<QGraphicsItem*> collidingItems = topAlien->collidingItems();
    collidingItems.append(bottomAlien->collidingItems());

    foreach (QGraphicsItem * item, collidingItems) {
        ShipItem * shipItem = dynamic_cast<ShipItem*>(item);
        if(shipItem){
            return true;
        }
    }
    return false;
}
