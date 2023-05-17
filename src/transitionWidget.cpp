#include "transitionWidget.h"

transitionwidget::transitionwidget()
{

}

transitionwidget::transitionwidget(StateWidget* state1, StateWidget* state2, QString label) {
    stateStart = state1;
    stateEnd = state2;
    this->label = label;
    pointStart = QPointF(state1->getX(), state1->getY());
    pointEnd = QPointF(state2->getX(), state2->getY());
}

transitionwidget::transitionwidget(const transitionwidget &tr)
{
   this->stateStart = tr.stateStart;
   this->stateEnd = tr.stateEnd;
   this->label = tr.label;
   pointStart = tr.pointStart;
   pointEnd = tr.pointEnd;
}

transitionwidget::~transitionwidget() {
    stateStart = nullptr;
    stateEnd = nullptr;
}

void transitionwidget::createPath() {

}

float transitionwidget::findDistance(QPoint qp) {
    return 9;
}

StateWidget& transitionwidget::getStart() {
    return *stateStart;
}

StateWidget& transitionwidget::getEnd() {
    return *stateEnd;
}

QString transitionwidget::getLabel() {
    return label;
}
bool transitionwidget::withinPoint(QPoint qp) {
    return true;
}

QRectF transitionwidget::boundingRect() const {
    return QRectF();
}

void transitionwidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QLineF trLine(pointStart, pointEnd);
    // fix later to prevent overlap with states
    double angle = atan2(trLine.dy(), -trLine.dx());

    // find alternative to pointAt if you intend to scale
    QPointF arrowP1 = trLine.pointAt(0.98) + QPointF(sin(angle + 1) * 30, cos(angle + 1) * 30);
    QPointF arrowP2 = trLine.pointAt(0.98) + QPointF(sin(angle + 2) * 30, cos(angle + 2) * 30);

    if (stateStart == stateEnd) {
    // modify rest of code to conserve space
        QRectF rectangle = QRectF(pointStart.x() - 45, pointStart.y(), 40, 40);
        double startAngle = 65 * 16 ;
        double spanAngle = 300 * 16 ;
        painter->drawArc(rectangle, startAngle, spanAngle);
        QRect trName(trLine.p2().x() - 50, trLine.p2().y() + 50, 20, 20);
        painter->setFont(QFont("times",15));
        painter->drawText(trName, Qt::AlignCenter, label);
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawLine(trLine);
        return;
    } else {
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(trLine);
    // condense this later
    QLineF trArrow(arrowP2, trLine.p2());
    QLineF trArrow2(arrowP1, trLine.p2());
    painter->drawLine(trArrow);
    painter->drawLine(trArrow2);

    }
    // too messy, create bound checking later
    if (((stateEnd->getX() - stateStart->getX()) / (stateEnd->getY() - stateStart->getY()) <= 1/25) && (
            (stateEnd->getX() - stateStart->getX()) / (stateEnd->getY() - stateStart->getY()) >= 2.5)) {
        if (stateStart->getX() < stateEnd->getX()) {
            QRectF trName(trLine.p2().x() - 20, trLine.p2().y() - 10, 20, 20);
            painter->setFont(QFont("times",15));
            painter->drawText(trName, Qt::AlignCenter, label);
        }
        else {
            QRectF trName(trLine.p2().x() - 20, trLine.p2().y() + 10, 20, 20);
            //QRectF trName(((stateStart->getX() + stateEnd->getX()) / 2), ((stateStart->getY() + stateEnd->getY()) / 2), 20, 20);
            painter->setFont(QFont("times",15));
            painter->drawText(trName, Qt::AlignCenter, label);
        }
    } else {
        if (stateEnd->getY() > stateStart->getY()) {
            QRectF trName(trLine.p2().x() - 25, trLine.p2().y() - 35, 20, 20);
            painter->setFont(QFont("times",15));
            painter->drawText(trName, Qt::AlignCenter, label);
        } else {
            QRect trName(trLine.p2().x() - 5, trLine.p2().y() + 15, 20, 20);
            painter->setFont(QFont("times",15));
            painter->drawText(trName, Qt::AlignCenter, label);
        }

    }

}
