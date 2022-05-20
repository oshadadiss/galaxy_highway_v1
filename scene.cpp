#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QString>
#include <QFont>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    gameOn(false),
    score(0),
    bestScore(0)
{
    setUpAlienTimer();
}

void Scene::addShip()
{
    ship = new ShipItem(QPixmap(":/Images/ship_middle.png"));
    addItem(ship);
}

void Scene::startGame()
{
    //ship
    ship->startFlight();
    //aliens
    if(!alienTimer->isActive()){
        cleanAliens();
        setGameOn(true);
        hideGameOver();
        alienTimer->start(1000);
    }
}

void Scene::setUpAlienTimer()
{
    alienTimer = new QTimer(this);
    connect(alienTimer,&QTimer::timeout,[=](){


        AlienItem * alienItem = new AlienItem();
        connect(alienItem,&AlienItem::collideFail,[=](){
            alienTimer->stop();
            freezShipAndAlien();
            setGameOn(false);
            showGameOver();

        });
        addItem(alienItem);

    });

    //alienTimer->start(1000);
}

void Scene::freezShipAndAlien()
{
    // freez ship
    ship->freezInPlace();
    //freez aliens
    QList<QGraphicsItem*> sceneItems = items();
    foreach (QGraphicsItem * item, sceneItems) {
        AlienItem * alien = dynamic_cast<AlienItem *>(item);
        if(alien){
            alien->freezInPlace();
        }
    }
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool value)
{
    gameOn = value;
}

void Scene::incrementScore()
{
    score++;
    if(score > bestScore){
        bestScore = score;
    }
}

void Scene::showGameOver()
{
    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/Images/game_over.png"));
    addItem(gameOverPix);
    gameOverPix->setPos(QPointF(0,0) - QPointF(gameOverPix->boundingRect().width()/2,
                                               gameOverPix->boundingRect().height()/2));
    
    scoreTextItem = new QGraphicsTextItem();
    
    QString htmlString = "<p> Score : " + QString::number(score) + "</p>"
            + "<p> Best Score : " + QString::number(bestScore) + "</p>";

    //QFont mFont("Consolas", 30, QFont::bold);

    scoreTextItem->setHtml(htmlString);
    //scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::yellow);
    addItem(scoreTextItem);

    scoreTextItem->setPos(QPointF(0,0) - QPointF(scoreTextItem->boundingRect().width()/2,
                                                 -gameOverPix->boundingRect().height()/2));

}

void Scene::hideGameOver()
{
    if(gameOverPix){
        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix = nullptr;
    }
    if(scoreTextItem){
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }
}

void Scene::cleanAliens()
{
    QList<QGraphicsItem*> sceneItems = items();
    foreach (QGraphicsItem * item, sceneItems) {
        AlienItem * alien = dynamic_cast<AlienItem *>(item);
        if(alien){
            removeItem(alien);
            delete alien;
        }
    }
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        if(gameOn){
            ship->shootUp();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(gameOn){
            ship->shootUp();
        }
    }
    QGraphicsScene::mousePressEvent(event);
}
