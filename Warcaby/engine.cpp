#include "engine.h"

void Engine::initializeBoard(int board_size)
{
    std::vector<tileState> wektor_t(board_size);
    std::vector<boardTile*> wektor_b(board_size);

    game_board_T = std::vector<std::vector<boardTile*>>(board_size);

    std::fill(wektor_t.begin(), wektor_t.end(), tileState::Empty);
    for (int i = 0; i <board_size; i++)
    {
        game_board_T[i] = std::vector<boardTile*>(board_size);
        for (int j = 0; j < board_size; j++)
        {
            game_board_T[i][j] = new boardTile();
        }
    }
    for (int i = 0; i < board_size; i++)
    {
        game_board_state.push_back(wektor_t);
        game_board_T.push_back(wektor_b);
    }
    //Rozmiesc plytki na scenie
    //szerokosc SCENY (nie okna) - ilosc plytek razy rozmiar plytek dzielone na dwa to srodek sceny
    int x = (this->scene->width()-board_size*BOARD_TILE_SIZE) / 2
      , y = (this->scene->height()-board_size*BOARD_TILE_SIZE) / 2;

    int parity = 1;
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            game_board_state[i][j] = tileState::Empty;
            game_board_T[i][j]->setPos(x + (BOARD_TILE_SIZE*i), y + (BOARD_TILE_SIZE*j));
            if (parity%2 == 0)  //jesli plytka parzysta pokoloruj na ciemno
            {
                game_board_T[i][j]->setTileColour(Colour::Black);
                game_board_T[i][j]->setPosition(QPoint(i, j));
            }
            else                //jesli nie pokoloruj na jasno
            {
                game_board_T[i][j]->setTileColour(Colour::White);
                game_board_T[i][j]->setPosition(QPoint(i, j));
            }

            //dodaj plytki do sceny
            scene->addItem(game_board_T[i][j]);
            parity++;
        }
        parity++;
    }
}

void Engine::placePawns(int pawns_count, int board_size)
{
    tileState actual_colour = tileState::BlackPawn;  //kolor na ktory sa kolorowane aktualnie pionki
    int x, y, pawns_placed = 0;
    bool jump = false;
    //iteruj po tablicy płytek
    //[c][r]
    for (int j = 0; j < board_size; j++)
    {
        for (int i = 0; i < board_size; i++)
        {
            if (pawns_placed != pawns_count)
            {
                //jesli plytka jest ciemna to daj na nią pionka
                if (this->game_board_T[i][j]->brush().color() == dark_tile)
                {
                    //ustal pozycje wzgledem aktualnie iterowanej plytki
                    x = game_board_T[i][j]->pos().x();
                    y = game_board_T[i][j]->pos().y();
                    Pawn *p = new Pawn(actual_colour);
                    p->setPosition(QPoint(i, j));
                    p->setPos(x + 5, y + 5);
                    //dodaj do sceny
                    this->scene->addItem(p);
                    //wprowadz do tablicy pionkow informacje ze jest tam pionek
                    if (actual_colour == tileState::BlackPawn)
                    {
                        this->player_2_pawns.push_back(p);
                        game_board_state[i][j] = tileState::BlackPawn;
                    }
                    else
                    {
                        this->player_1_pawns.push_back(p);
                        game_board_state[i][j] = tileState::WhitePawn;
                    }
                    //zwieksz licznik dodanych pionkow
                    ++pawns_placed;
                }
            }
            //jesli skok do drugiej strony (drugiego gracza) zostal wykonany to nie skacz
            //i nie resetuj pętli
            else if (jump == false)
            {
                actual_colour = tileState::WhitePawn;
                pawns_placed = 0;
                jump = true;
                if (board_size == 10)   //Jesli plansza jest 10x10 to zacznij klasc pionki wiersz dalej
                    j = 6;
                else
                    j = 5;
                i = 0;
                //te same instrukcje co wczesniej, poniewaz musimy dodac pionka na miejsce skoku
                if (this->game_board_T[i][j]->brush().color() == dark_tile)
                {
                    x = game_board_T[i][j]->pos().x();
                    y = game_board_T[i][j]->pos().y();
                    //wprowadz do tablicy pionkow informacje ze jest tam pionek
                    Pawn *p = new Pawn(actual_colour);
                    p->setPosition(QPoint(i, j));
                    p->setPos(x + 5, y + 5);
                    this->scene->addItem(p);
                    if (actual_colour == tileState::BlackPawn)
                    {
                        this->player_2_pawns.push_back(p);
                        game_board_state[i][j] = tileState::BlackPawn;
                    }
                    else
                    {
                        this->player_1_pawns.push_back(p);
                        game_board_state[i][j] = tileState::WhitePawn;
                    }

                    ++pawns_placed;
                }
            }
        }
    }
}

void Engine::mousePressEvent(QMouseEvent *ev)
{
    QPoint pt(ev->x(), ev->y());
    QGraphicsItem *select = this->itemAt(pt);
    if (selected_pawn == nullptr)
    {
        Pawn *selected_pawn = dynamic_cast<Pawn*>(select);
        if (selected_pawn != nullptr)
        {
            this->selected_pawn = selected_pawn;
            this->selected_pawn->set_selected();
        }
    }
    else if (selected_pawn != nullptr && selected_boardTile == nullptr)
    {
        boardTile *selected_board_tile = dynamic_cast<boardTile*>(select);
        if (selected_board_tile != nullptr)
        {
            this->selected_boardTile = selected_board_tile;
            this->selected_boardTile->setSelected();
            lista *lista_mozliwych_ruchow = gr->giveAllPossibleMoves(selected_pawn, game_board_state);
            if (lista_mozliwych_ruchow != nullptr)
            {
                if (lista_mozliwych_ruchow->find(selected_pawn->getPosition(), selected_boardTile->getPosition()))      //jesli wskazany ruch znajduje sie w liscie mozliwych ruchow to go wykonaj
                    movePawn();
                else
                    wrongMove();
            }
        }

    }
}

void Engine::movePawn()
{
    //jesli pionek przeskoczyl o dwa miejsca to znaczy że zbija pionka drużyny przeciwnej
    if (std::abs(selected_pawn->getPosition().x() - selected_boardTile->getPosition().x()) == 2 || std::abs(selected_pawn->getPosition().y() - selected_boardTile->getPosition().y()) == 2)
    {
        QPoint pt = findDeletingPawn();
        //game_board_state[pt.x()][pt.y()] = tileState::Empty;
        printBoardState(8);
        printBoardWithPawns(8);

    }
    game_board_state[selected_pawn->getPosition().x()][selected_pawn->getPosition().y()] = tileState::Empty;  //Usun pionek ze starego miejsca
    selected_pawn->setPosition(selected_boardTile->getPosition());  //przypisz mu nowa pozycje
    this->game_board_state[selected_pawn->getPosition().x()][selected_pawn->getPosition().y()] = selected_pawn->pawn_state; //ustaw pionka na noawej pozycji
    selected_pawn->setPos(selected_boardTile->pos().x() + 5, selected_boardTile->pos().y() + 5);    //ustaw pionka na podanym kafelku z dodatkiem 5 px zeby byl po srodku
    clearPawnAndTileAfterTime(500);
}

void Engine::wrongMove()
{
    selected_pawn->setBrush(QBrush(wrong_pawn));
    selected_boardTile->setBrush(QBrush(wrong_tile));
    clearPawnAndTileAfterTime(1000);

}

void Engine::clearPawnAndTileAfterTime(int time)
{
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, selected_pawn, &Pawn::setDefaultColour);
    connect(timer, &QTimer::timeout, selected_boardTile, &boardTile::setDefaultColour);
    timer->start(time);
    selected_pawn = nullptr;
    selected_boardTile = nullptr;
}

QPoint Engine::findDeletingPawn()
{
    QPoint pt1 = selected_pawn->getPosition();
    QPoint pt2 = selected_boardTile->getPosition();
    QPoint deleted_pos;
    int x1 = pt1.x(), y1 = pt1.y();
    int x2 = pt2.x(), y2 = pt2.y();

    x1 += 2;
    y1 += 2;
    if (x1 == x2 && y1 == y2)
    {
        deleted_pos.setX(x1 - 1);
        deleted_pos.setY(y1 - 1);
    }

    x1 = pt1.x(), y1 = pt1.y();
    x1 -= 2;
    y1 -= 2;
    if (x1 == x2 && y1 == y2)
    {
        deleted_pos.setX(x1 + 1);
        deleted_pos.setY(y1 + 1);
    }

    x1 = pt1.x(), y1 = pt1.y();
    x1 -= 2;
    y1 += 2;
    if (x1 == x2 && y1 == y2)
    {
        deleted_pos.setX(x1 + 1);
        deleted_pos.setY(y1 - 1);
    }

    x1 = pt1.x(), y1 = pt1.y();
    x1 += 2;
    y1 -= 2;
    if (x1 == x2 && y1 == y2)
    {
        deleted_pos.setX(x1 - 1);
        deleted_pos.setY(y1 + 1);
    }
    return deleted_pos;
}


void Engine::handleExitButton()
{
    this->close();
    this->destroy();
    Menu *menu = new Menu();
    menu->show();
}

Engine::Engine(gameType gT) :
    selected_pawn(nullptr), selected_boardTile(nullptr)
{
    this->gr = new GameRules(gT);
    //ustal rozmiar sceny
    scene = new QGraphicsScene(0, 0, 800, 600, this);

    //*****Ustala przezroczystosc tla
    QImage image(":/new/backgrounds/background_army.jpg");
    QPixmap transparent(image.size());
    transparent.fill(Qt::transparent);
    QPainter p;
    p.begin(&transparent);
    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.drawPixmap(0, 0, QPixmap::fromImage(image));
    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p.fillRect(transparent.rect(), QColor(0, 0, 0, 100));
    p.end();
    //******

    this->scene->setBackgroundBrush(QBrush(transparent));
    //wygladzanie krawedzi
    this->setRenderHints(QPainter::Antialiasing);
    this->setScene(scene);

    //wylacz paski przesuwania
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //ustaw scene do tego okna (widgetu)

    //Zainicjalizuj tablice plytek
    this->initializeBoard(8);
    //Stworz pionki
    this->placePawns(12, 8);

    //Dodaj przycisk wyjścia
    QPushButton * exitButton = new QPushButton("Wyjdź", this);
    this->scene->addWidget(exitButton);
    exitButton->setGeometry(650, 550, 100, 30);
    QObject::connect(exitButton, SIGNAL(released()), this, SLOT(handleExitButton()));

    printBoardState(8);
    printBoardWithPawns(8);


    /*
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
    freopen("CON", "r", stdin);
    /*


    lista *lista = new class lista();
    lista->add(QPoint(1,2), QPoint 3, 4);
    lista->add(QPoint(4,4), QPoint 8, 8);
    lista->add(QPoint(0,0), QPoint 1, 2);
    lista->print();
    lista->print();
    lista->print();
    lista->print();

    std::cout << '\n';
    std::cout << lista->find(6, 9, 6, 6);
    */

    /*
    printBoardWithPawns(8);
    printBoardState(8);
    printPawns(4);
    */



}

void Engine::printBoardState(int board_size)
{
    for (int j = 0; j < board_size; j++)
    {
        //szeregi
        for (int i = 0; i < board_size; i++)
        {
            std::cout << (int)this->game_board_state[i][j] << "     ";
        }
        std::cout << '\n';
        std::cout << "Kolejny szereg stanow" << std::endl;
    }
}

void Engine::printBoardWithPawns(int board_size)
{
    for (int j = 0; j < board_size; j++)
    {
        //szeregi
        for (int i = 0; i < board_size; i++)
        {
            if (game_board_state[i][j] == tileState::WhitePawn || game_board_state[i][j] == tileState::BlackPawn)
            {
                std::cout << game_board_T[i][j]->getPosition().x() << ";" << game_board_T[i][j]->getPosition().y() << ",      ";
            }
        }
        std::cout << '\n';
        std::cout << "Kolejny szereg" << std::endl;
    }
}

void Engine::printPawns(int pawns_in_row)
{
    int licznik = 0;
    std::cout << "Pionki gracza nr 1:" << std::endl;
    for (unsigned int i = 0; i < this->player_1_pawns.size(); i++)
    {
        if (licznik % pawns_in_row == 0)
            std::cout << '\n';
        std::cout << player_1_pawns[i]->getPosition().x() << ";" << player_1_pawns[i]->getPosition().y() << ",     ";
        licznik++;
    }
    std::cout << std::endl << "Pionki gracza nr 2:" << std::endl;
    for (unsigned int i = 0; i < this->player_2_pawns.size(); i++)
    {
        if (licznik % pawns_in_row == 0)
            std::cout << '\n';
        std::cout << player_2_pawns[i]->getPosition().x() << ";" << player_2_pawns[i]->getPosition().y() << ",     ";
        licznik++;
    }
}

