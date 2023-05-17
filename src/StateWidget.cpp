#include "StateWidget.h"
#include <QtWidgets>

StateWidget::StateWidget() {
    id = -1;
    name = NULL;
    start = false;
    final = false;
    current = 0;
    stColor = Qt::yellow;
    stateX = 0;
    stateY = 0;
}

StateWidget::StateWidget(State st, float x, float y) {
    id = st.getId();
    State state(st);
    name = QString::fromStdString(state.getName());
    start = 0;
    stColor = Qt::yellow;
    final = st.getAccept();
    current = 0;

    stateX = x;
    stateY = y;
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    this->setAcceptHoverEvents(true);

}

StateWidget::StateWidget(State st) {
    id = st.getId();
    State state(st);
    name = QString::fromStdString(state.getName());
    start = 0;
    stColor = Qt::yellow;
    final = st.getAccept();
    current = 0;
    }

StateWidget::~StateWidget() {

}

StateWidget::StateWidget(const StateWidget &st) {
    id = st.getId();
    state = st.getState();
    name = st.name;
    start = st.start;
    stColor = st.stColor;
    current = st.current;
    final = st.getState().getAccept();
    this->stateX = st.stateY;
    this->stateY = st.stateY;

}

bool StateWidget::getAccept() {
    return final;
}

State StateWidget::getState() const {
    return state;
}

int StateWidget::getId() const {
    return id;
}

bool StateWidget::getInit() {
    return start;
}

bool StateWidget::getCurrent() {
    return current;
}

float StateWidget::getX() {
    return stateX;
}

float StateWidget::getY() {
    return stateY;
}

void StateWidget::relocate(QPointF pos) {
    stateX = pos.x();
    stateY = pos.y();
    update();
}

void StateWidget::setInit(bool init) {
    start = init;
    update();
}

void StateWidget::setAccept(bool accept) {
    final = accept;
    state.setAccept(accept);
    update();
}

void StateWidget::setCurrent(bool cur) {
    current = cur;
    update();
}

void StateWidget::setPosition(float x, float y){
    stateX = x;
    stateY = y;
    update();
}

QRectF StateWidget::boundingRect() const {
    return QRectF(0, 0, 20, 20);
   /*
    float radius = 2.0; */
}

void StateWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    float x = stateX;
    float y = stateY;
    float radius = 15.0;
    // creating state shape
    if (this->getInit() == false){
        painter->setBrush(Qt::yellow);
    } else if (this->getInit() == true) {
        painter->setBrush(Qt::blue);
    }
    if (this->getAccept() == true) {
        painter->setBrush(Qt::red);
    }
    if (this->getCurrent() == true) {
        painter->setBrush(Qt::green);
    }

    painter->drawEllipse(QPointF(x, y), radius, radius);
    // creating state name
    painter->setPen(Qt::black);
    QRectF stateName(stateX - 2, stateY - 2, 10, 10);
    painter->drawText(stateName, Qt::AlignCenter, QString::number(this->id));
    //update();

}
/*
void StateWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    held = true;
    setAccept(true);
//    update();
    QGraphicsItem::mousePressEvent(event);
}

void StateWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    held = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
*/
