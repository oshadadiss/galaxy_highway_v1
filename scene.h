#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "alienitem.h"
#include <QTimer>
#include "shipitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QString>
#include <QFont>


class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void addShip();

    void startGame();

    bool getGameOn() const;
    void setGameOn(bool value);
    void incrementScore();

signals:

private:
    void showGameOver();
    void hideGameOver();
    void cleanAliens();
    void setUpAlienTimer();
    void freezShipAndAlien();

    QTimer * alienTimer;
    ShipItem * ship;

    bool gameOn;

    int score;
    int bestScore;

    QGraphicsPixmapItem * gameOverPix;
    QGraphicsTextItem * scoreTextItem;


    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
