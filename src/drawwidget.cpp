#include "drawwidget.h"
#include "qapplication.h"

drawWidget::drawWidget(QWidget *parent) : QGraphicsView(parent) {

    //this->sceneRect();
    setMouseTracking(true);
    sc = new QGraphicsScene(this);

    sc->setSceneRect(0, 0, this->width() - 1, this->height() - 1);
    setScene(sc);
    setFrameShape(QGraphicsView::NoFrame);

    //this->
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->fitInView(sc->sceneRect(), Qt::KeepAspectRatio);

    //this->setStyleSheet("border: 5px solid red");
    /*QGraphicsRectItem *rect_item = sc->addRect(sc->sceneRect());
        QPen pen = QPen(Qt::black);
        pen.setWidth(10);
        rect_item->setPen(pen); */

        this->show();

    counter = 0;

   // newGraphicalStates
    // timer for state control
  /*  QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(setCurrentState()));
    // in milliseconds
    timer->start(1500); */

}

drawWidget::~drawWidget() {
    states.clear();
    states.squeeze();
    transitions.clear();
    transitions.squeeze();
}

void drawWidget::saveToFile(QFile& file)
{
    QTextStream outFile(&file);
    for (auto& state : states) {
        outFile << state->getId() << Qt::endl << state->getX() << Qt::endl << state->getY() << Qt::endl;
    }
    outFile << "#" << Qt::endl;
    for (auto& transition : transitions) {
        outFile << transition->getStart().getId() << Qt::endl << transition->getLabel() << Qt::endl << transition->getEnd().getId() << Qt::endl;
    }
    outFile << "#" << Qt::endl;
    for (auto& state : states) {
        if (state->getInit() == true) {
            outFile << state->getInit() << Qt::endl;
            outFile << "#" << Qt::endl;
            break;
        }
    }
    for (auto& state : states) {
        if (state->getAccept() == true) {
            outFile << state->getId() << Qt::endl;
        }
    }

}

void drawWidget::loadFromFile(QFile &file)
{
    clearAll();

    QTextStream inFile(&file);

    QString temp = "";
    QString temp1 = "";
    QString temp2 = "";

    // getting states

    while (temp.contains("#", Qt::CaseInsensitive) == false && !inFile.atEnd()) {
        temp = inFile.readLine(10);
        if (!temp.contains("#", Qt::CaseInsensitive)) {
            temp1 = inFile.readLine(10);
            temp2 = inFile.readLine(10);
            State idState(temp.toInt());
            StateWidget * st = new StateWidget(idState, temp1.toFloat(), temp2.toFloat());
            states.push_back(st);
            counter++;
        }
    }

    // resetting temp
    temp = "";
    // getting transitions
    StateWidget * tempState = NULL;
    StateWidget * tempState2 = NULL;
    while (!temp.contains('#') && !inFile.atEnd()) {
        temp = inFile.readLine();
        if (!temp.contains('#')) {
            temp1 = inFile.readLine();
            temp2 = inFile.readLine();
            for (auto& st : states) {
               if (st->getId() == temp.toInt()) {
                   tempState = st;
               }
               if (st->getId() == temp2.toInt()) {
                   tempState2 = st;
               }
            }
            if (tempState != NULL && tempState2 != NULL) {
                transitionwidget * tr = new transitionwidget(tempState, tempState2, temp1);
                transitions.push_back(tr);
            }
        }

    }
    for (auto & s : states) {
        sc->addItem(s);
    }
    for (auto & t : transitions) {
        sc->addItem(t);
    }
    update();
    // getting starting state
    if (!inFile.atEnd()) {
        temp = inFile.readLine();
        for (auto& st : states) {
            if (st->getId() == temp.toInt()) {
                st->setInit(true);
            }
        }
    }
    if (!inFile.atEnd()) {
    // getting accepting states
        QVector<int> tempV;
        while (!inFile.atEnd()) {
            temp = inFile.readLine();
            if (!temp.contains('#')) {
                tempV.push_back(temp.toInt());
            }
        }
        for (auto& st : states) {
            for (int i : tempV) {
                if (st->getId() == i) {
                    st->setAccept(true);
                }
            }
        }
    }
}

void drawWidget::setMode(int m) {
    mMode = m;
}

void drawWidget::setFA(QString text)
{
    if (text.compare("DFA", "DFA", Qt::CaseInsensitive) == 0) {
        nfaMode = false;
        dfaMode = true;
    }
    else if (text.compare("NFA", "NFA", Qt::CaseInsensitive) == 0) {
        dfaMode = false;
        nfaMode = true;
    }
}

void drawWidget::reverse()
{
    for (auto& state : states) {
        if (state->getInit() == true) {
            state->setInit(false);
            state->setAccept(true);
        } else if (state->getAccept() == true) {
            state->setAccept(false);
            state->setInit(true);
        }
    }
    for (auto& tr : transitions) {
        StateWidget temp = tr->getStart();
        //start = end
        // end = temp
    }
    int count = 0;
    for (auto& state : states) {
        if (state->getInit() == true) {
            count++;
        }
        if (count > 1) {
            //StateWidget newStart((State(), ));
            break;
        }
    }
}

void drawWidget::setCurrentState(StateWidget * current)
{
    current->setCurrent(true);
    this->viewport()->repaint();
    QEventLoop loop;

    QTimer t;

    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(1000);
    loop.exec();
    qDebug("Test");
}

void drawWidget::setCurrentStateSet(QVector<StateWidget *> current)
{
    for (auto & st : current) {
        st->setCurrent(true);
        this->viewport()->repaint();
    }
    QApplication::processEvents();
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(1500);
    loop.exec();
    qDebug("Test");
}

void drawWidget::addState() {
    //new StateWidget(this);
    if (mMode != 1) {
        setMode(1);
    }
  /*  if (mMode == 1) {
        State state(counter);
        StateWidget *stWdg = new StateWidget(state, mouseX, mouseY);
        counter++;
        this->scene()->addItem(stWdg);
        setCursor(QCursor(Qt::ArrowCursor));
    } */
}

void drawWidget::addTransition() {
    if (mMode != 2) {
        setMode(2);
        QString state1 = QInputDialog::getText(0, "Input", "State1:", QLineEdit::Normal, "");
        QString state2 = QInputDialog::getText(0, "Input", "State2:", QLineEdit::Normal, "");
        QString counter2 = QInputDialog::getText(0, "Input", "Label (Use = for epsilon):", QLineEdit::Normal, "");
  //      QVectorIterator<StateWidget *> itSt(states);
        if (counter2 == '=') {
            counter2 = "ε";
        }
        StateWidget *temp1;
        StateWidget *temp2;
        int check = 0;
        for (auto& state : states) {
            if (state->getId() == state1.toInt()) {
                temp1 = state;
                check++;
            }
            if (state->getId() == state2.toInt()) {
                temp2 = state;
                check++;
        }
  //      while (itSt.hasNext()) {
   //        if (itSt->getId())
        }
        if (check == 2) {
            transitionwidget *t = new transitionwidget(temp1, temp2, counter2);
            transitions.push_back(t);
            this->scene()->addItem(t);
            check = 0;
            update();
        }
        setCursor(QCursor(Qt::ArrowCursor));
        mMode = 0;
    }
 //   if (mMode == 2) {
//
 //   }

}

void drawWidget::moveState() {

}

void drawWidget::removeState() {
    if (mMode != 5) {
        setMode(5);
        QString state1 = QInputDialog::getText(0, "Input", "State To Be Removed:", QLineEdit::Normal, "");
        for (auto& state : states) {
            if (state->getId() == state1.toInt()) {
                for (auto& transition : transitions) {
                    if (transition->getStart().getId() == state1.toInt() ||
                            transition->getEnd().getId() == state1.toInt()) {
                        //transition = transitions.erase(transition);
                        //delete transition;
                        sc->removeItem(transition);
                        transitions.erase(std::remove_if(transitions.begin(),
                                                        transitions.end(),
                                                         [&](transitionwidget *tr)-> bool
                                                         { return tr == transition; }),
                                         transitions.end());
                       // delete transition;
                        //transitions.erase(std::remove_if(transitions.begin(), transitions.end(), transition), transitions.end());
                    }

                }
                sc->removeItem(state);
                states.erase(std::remove_if(states.begin(),
                                                states.end(),
                                            [&](StateWidget *st)-> bool
                                                 { return st == state; }),
                                 states.end());
                //delete state;

            }
        }
        mMode = 0;
    }
}

void drawWidget::removeTransition() {
//    if (mMode != 5) {
//        setMode(5);
    QString trSt = QInputDialog::getText(0, "Input", "Name the transition's start:", QLineEdit::Normal, "");
    QString trEnd = QInputDialog::getText(0, "Input", "Name the transition's end:", QLineEdit::Normal, "");
    QString trId = QInputDialog::getText(0, "Input", "Name the transition's accepting input. Use = for epsilon:", QLineEdit::Normal, "");
    if (trId == "=") {
        trId = "ε";
    }
    for (auto& tr : transitions) {
        if (tr->getStart().getId() == trSt.toInt() &&
                tr->getEnd().getId() == trEnd.toInt() &&
                tr->getLabel() == trId) {
            sc->removeItem(tr);
            transitions.erase(std::remove_if(transitions.begin(), transitions.end(),
                [&](transitionwidget *transition)-> bool { return transition == tr; }),
                transitions.end());
        }

    }
}


void drawWidget::setStart() {
    if (mMode != 3) {
        setMode(3);
        QString starting = QInputDialog::getText(0, "Input", "Set Starting State:", QLineEdit::Normal, "");
//        StateWidget *temp1;
        for (auto& state : states) {
            if (state->getInit() == true) {
                state->setInit(false);
            }
            if (state->getId() == starting.toInt()) {
                if (state->getInit() == true) {
                    state->setInit(false);
                } else {
                    state->setInit(true);
                }
            }
        } /*
        for (auto& state : states) {
            if (state->getId() == starting.toInt()) {
                state->setInit(true);
            }
        } */
        mMode = 0;
    }
}

void drawWidget::setAccept() {
    if (mMode != 4) {

        setMode(4);

        QString starting = QInputDialog::getText(0, "Input", "Set Accepting State:", QLineEdit::Normal, "");

        for (auto& state : states) {
            if (state->getId() == starting.toInt()) {
                if (state->getAccept() == true) {
                    state->setAccept(false);

                } else {
                    state->setAccept(true);
                }
            }
        } /*
        for (auto& state : states) {
            if (state->getId() == starting.toInt()) {
                state->setAccept(true);
            }
        } */
        mMode = 0;
    }
}

bool drawWidget::execFA() {
    // validate
    QString alphabet = "";
    StateWidget * current = nullptr;
    StateWidget * prev = nullptr;

    for (auto& state : states) {
        if (state->getInit() == true) {
            current = state;
            break;
        }
    }

    if (current == nullptr) {
        return false;
    }
    if (alphabet == "") {
        for (auto& transition : transitions) {
            if (!alphabet.contains(transition->getLabel())) {
                alphabet.append(transition->getLabel());
            }
            if (transition->getLabel() == "delta") {
                ;
            }
        }
    }
    QString mode = QInputDialog::getText(0, "Input", "Is this a DFA or a NFA?", QLineEdit::Normal, "");
    if (mode.contains("D") || mode.contains("d")) {
        dfaMode = true;
        nfaMode = false;
    }
    if (mode.contains("N") || mode.contains("n")) {
        nfaMode = true;
        dfaMode = false;
    }
        // parse transitions along the way to create alphabet
        // reject if invalid
        // convert into nfa or dfa if valid
    // request input

    QString input = QInputDialog::getText(0, "Input", "Enter your input string: ", QLineEdit::Normal, "");

    if (dfaMode == true) {
     /*   runAutomaton dfa(alphabet, input, states, transitions, 1, this);
        return true;
    }*/

    for (unsigned int i = 0; i < input.length(); i++) {
        for (auto& transition : transitions) {
           // current->setCurrent(true);
            if (prev != nullptr) {
                prev = current;
                prev->setCurrent(false);
            }

            setCurrentState(current);

            if (current->getId() == transition->getStart().getId()) {

                // if state and symbol match, go to next state
                if (input[i] == transition->getLabel()) {
                    //cout << "Step 3" << endl;
                    prev = current;
                    prev->setCurrent(false);
                    current = &transition->getEnd();
                    setCurrentState(current);

                    break;
                }
            }
        }

        // if end of input and in accept state, DFA accepts input

        if ((input[i + 1] == '\0') && (current->getAccept() == true)) {
            current->setCurrent(false);
            return true;

            break;
        }
    }

    current->setCurrent(false);
    return false;
    }
    // run fa
        // accept if valid
        // reject if invalid ie no accepting state reached or string is longer than automaton


    if (nfaMode == true) {

        QVector<StateWidget *> currentSet;
        QVector<StateWidget *> stateSet;
        currentSet.push_back(current);

        for (auto& transition : transitions) {
            if ((current->getId() == transition->getStart().getId()) && (transition->getLabel() == "ε")) {
                currentSet.push_back(&transition->getEnd());
            }
        }

        for (unsigned int i = 0; i < input.length(); i++) {
            stateSet.clear();

            for (auto it : currentSet) {
                for (auto& transition : transitions) {

                    if ((it->getId() == transition->getStart().getId()) && (transition->getLabel() == "ε")) {
                        stateSet.push_back(&transition->getEnd());
                    }
                    if ((it->getId() == transition->getStart().getId()) && (transition->getLabel() == input[i])) {
                        stateSet.push_back(&transition->getEnd());
                    }
                }

                for (auto& it : stateSet) {
                    for (auto& transition : transitions) {

                        if ((it->getId() == transition->getStart().getId()) && (transition->getLabel() == "ε")) {
                            stateSet.push_back(&transition->getEnd());
                        }
                    }
                }


            }

            currentSet = stateSet;
            if (!currentSet.empty()) {

                setCurrentStateSet(stateSet);
            }
            for (auto& st : stateSet) {
                if (st->getCurrent() == true) {
                    st->setCurrent(false);

                }
            }
            this->viewport()->update();
        }

        for (auto it : currentSet) {
            if (it->getAccept() == true) {
                return true;
            }
        }

    }
    return false;
}

StateWidget * drawWidget::obtainState() {
    StateWidget *temp = nullptr;
    for (auto &st : states) {
        if (st != nullptr) {
            if (st->isUnderMouse()) {
                temp = st;
                return temp;
            }
        }
    }

    return nullptr;
}

/* controls the mode upon left click
 * 0 = regular actions
 * 1 = add new state
 * */
void drawWidget::mousePressEvent(QMouseEvent *event) {
        // Obtain mouse's current position of x and y upon left click
    QPointF scenePos = event->position();

    //scenePosition().x();
    mouseX = scenePos.x();
    mouseY = scenePos.y();
    //mouseX = event->pos().x();
    //mouseY = event->pos().y();
    switch (this->mMode) {
            case 0:
            {
                stateCopy = obtainState();
                event->accept();
                QGraphicsView::mousePressEvent(event);
                break;
            }
            case 1:
            {
                if (mMode == 1) {
                State state(counter);
                StateWidget *stWdg = new StateWidget(state, mouseX, mouseY);
                counter++;
                this->scene()->addItem(stWdg);
                //stWdg->setPos(mapToScene(event->pos()));
                //stWdg->setPos(mouseX, mouseY);
                states.push_back(stWdg);
                this->viewport()->update();

                setCursor(QCursor(Qt::ArrowCursor));
                mMode = 0;

                break;
                }
            }
        }
    }


void drawWidget::mouseMoveEvent(QMouseEvent *event) {
    event->accept();
}

void drawWidget::mouseReleaseEvent(QMouseEvent *event) {
    QPointF scenePos = event->scenePosition();
    mouseX = scenePos.x();
    mouseY = scenePos.y();


    if (stateCopy != nullptr) {
        {
            for (auto& state : states) {
                if (state->getId() == stateCopy->getId()) {
                    state->relocate(scenePos);
                    stateCopy = nullptr;
                    break;
                }
            }
        }
    }
    event->accept();
    QGraphicsView::mouseReleaseEvent(event);

}
void drawWidget::mouseDoubleClickEvent(QMouseEvent *event) {
}

void drawWidget::resizeEvent(QResizeEvent* event)
{

    sc->setSceneRect(0, 0, this->width(), this->height());
    QRectF bounds = sc->itemsBoundingRect();
    setScene(sc);
    this->fitInView(bounds, Qt::IgnoreAspectRatio);
}


void drawWidget::showEvent(QShowEvent* event)
{
    QRectF bounds = sc->itemsBoundingRect();
    this->fitInView(bounds, Qt::IgnoreAspectRatio);
}

void drawWidget::clearAll()
{
    states.clear();
    transitions.clear();
    sc->clear();
    counter = 0;
    this->autoFillBackground();
    update();
}

void drawWidget::convertFA()
{
    bool checkStart = false;
    bool checkAccept = false;
    bool first = true;

    // error checking before running converter
    for (auto& st : states) {
        if (st->getInit() == true) {
            checkStart = true;
        }
        if (st->getAccept() == true) {
            checkAccept = true;
        }
    }

    if (checkStart == false || checkAccept == false) {
        QMessageBox::information(this, "NFA To DFA Conversion", "Error: The automaton lacks either a starting state or an accepting state.");
    } else {
        // running conversion process
        automatonConverter converter(states, transitions);
        converter.convertNFA();
        QVector<State> newStates;
        for (auto& st : converter.getStates()) {
            State state2 = st;
            newStates.push_back(state2);
            qDebug("adding item");
        }
        QVector<Transition> newTransitions;
        for (auto tr : converter.getTransitions()) {
            newTransitions.push_back(tr);
        }

        //QVector<StateWidget *> newGraphicalStates;

        for (auto& state : states) {
            sc->removeItem(state);
            delete state;
        }
         states.clear();

        // converting states into graphical objects
        for (auto& st : newStates) {

            //StateWidget state(states);
            //StateWidget *stWdg = new StateWidget(state, counter + 20, counter + 20);
            StateWidget *state = new StateWidget(st, ((rand() % 600) + 100), ((rand() % 600) + 100));
            if (first == true) {
                state->setInit(true);
                first = false;
            }
            if (st.getAccept() == true) {
                state->setAccept(true);
            }
            states.push_back(state);
        }

        /*for (auto& state : states) {
            sc->removeItem(state);
            delete state;
        }*/
        for (auto& tr : transitions) {
            sc->removeItem(tr);
            delete tr;
        }
        // clearing current objects from scene
        //this->setAutoFillBackground(true);

        //states.clear();

        transitions.clear();

        // adding new DFA to scene
        //for (auto& st : newGraphicalStates) {
        //    states.push_back(st);
        //}

        for (auto& st : states) {
            //if (st->getInit() == true) {
            sc->addItem(st);
            //st->setPosition(counter + 20, counter + 20); //rand() % (800 - 0 + 1)
            //}
        }




        // converting transitions into graphical objects
        StateWidget *temp1 = nullptr;
        StateWidget *temp2 = nullptr;
        //QVector<transitionwidget *> newGraphicalTransitions;
        for (auto& tr : newTransitions) {
            for (auto& st : states) {
                if (tr.getSrc().getId() == st->getId()) {
                    temp1 = st;
                }
                if (tr.getDest().getId() == st->getId()) {
                    temp2 = st;
                }
            }
            if (temp1 != nullptr && temp2 != nullptr ) {
                transitionwidget *newTr = new transitionwidget(temp1, temp2, QString(tr.getName()));
                transitions.push_back(newTr);

            }
        }
        for (auto& tr : transitions) {
            sc->addItem(tr);
        }

    }

}
