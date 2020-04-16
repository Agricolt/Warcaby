#include "engine.h"

void Engine::initializeBoard(int board_size)
{
    game_board_T = new boardTile*[board_size];
    game_board_state = new tileState*[board_size];
    for (int i = 0; i < board_size; i++)
    {
        this->game_board_state[i] = new tileState[board_size];
        game_board_T[i] = new boardTile[board_size];
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
            game_board_T[i][j].setPos(x + BOARD_TILE_SIZE*i, y + BOARD_TILE_SIZE*j);
            if (parity%2 == 0)  //jesli plytka parzysta pokoloruj na ciemno
            {
                game_board_T[i][j].setTileColour(Colour::Black);
                game_board_T[i][j].setPosition(QPoint(i, j));
            }
            else                //jesli nie pokoloruj na jasno
            {
                game_board_T[i][j].setTileColour(Colour::White);
                game_board_T[i][j].setPosition(QPoint(i, j));
            }

            //dodaj plytki do sceny
            scene->addItem(&game_board_T[i][j]);
            parity++;
        }
        parity++;
    }
}

void Engine::placePawns(int pawns_count, int board_size)
{
    Colour actual_colour = Colour::Black;  //kolor na ktory sa kolorowane aktualnie pionki
    int x, y, pawns_placed = 0;
    bool jump = false;
    //iteruj po tablicy płytek
    //[c][r]
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            if (pawns_placed != pawns_count)
            {
                //jesli plytka jest ciemna to daj na nią pionka
                if (this->game_board_T[j][i].brush().color() == dark_tile)
                {
                    //wprowadz do tablicy pionkow informacje ze jest tam pionek
                    if (actual_colour == Colour::Black)
                        game_board_state[i][j] = tileState::BlackPawn;
                    else
                        game_board_state[i][j] = tileState::WhitePawn;

                    //ustal pozycje wzgledem aktualnie iterowanej plytki
                    x = game_board_T[j][i].pos().x();
                    y = game_board_T[j][i].pos().y(); 
                    QRect rect(x + 5, y + 5, 40, 40);
                    Pawn *p = new Pawn(actual_colour, pawnType::Normal, rect, this);

                    //dodaj do sceny
                    this->scene->addItem(p);
                    //zwieksz licznik dodanych pionkow
                    ++pawns_placed;
                }
            }
            //jesli skok do drugiej strony (drugiego gracza) zostal wykonany to nie skacz
            //i nie resetuj pętli
            else if (jump == false)
            {
                actual_colour = Colour::White;
                pawns_placed = 0;
                jump = true;
                if (board_size == 10)   //Jesli plansza jest 10x10 to zacznij klasc pionki wiersz dalej
                    i = 6;
                else
                    i = 5;
                j = 0;
                //te same instrukcje co wczesniej, poniewaz musimy dodac pionka na miejsce skoku
                if (this->game_board_T[j][i].brush().color() == dark_tile)
                {
                    x = game_board_T[j][i].pos().x();
                    y = game_board_T[j][i].pos().y();
                    //wprowadz do tablicy pionkow informacje ze jest tam pionek
                    if (actual_colour == Colour::Black)
                        game_board_state[i][j] = tileState::BlackPawn;
                    else
                        game_board_state[i][j] = tileState::WhitePawn;

                    QRect rect(x + 5, y + 5, 40, 40);
                    Pawn *p = new Pawn(actual_colour, pawnType::Normal, rect, this);
                    this->scene->addItem(p);
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
    if ((selected_pawn == nullptr || selected_boardTile == nullptr))  //jesli nie ma zaznaczonego pionka lub plytki
    {
        Pawn *selected_pawn = dynamic_cast<Pawn*>(select);      //Sprobuj scastowac na pionka
        if (selected_pawn != nullptr)                           //jesli sie udalo to znaczy ze gracz zaznaczyl pionka
        {
           this->selected_pawn = selected_pawn;
           selected_pawn->set_selected();
        }

        boardTile *selected_tile = dynamic_cast<boardTile*>(select);    //sprobuj scastowac na plytke planszy
        if (selected_tile != nullptr)                                   //jesli sie udalo to znaczy ze gracz znzaczyl plytke
        {
            selected_boardTile = selected_tile;
            selected_tile->setSelected();
        }
    }
    else        //jesli i plytka i pionek jest zaznaczony to sprobuj wykonac wskazany ruch
    {
        checkMove();
    }
}

bool Engine::checkMove()
{
    return 1;
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
    //ustal rozmiar sceny
    scene = new QGraphicsScene(0, 0, 800, 600);

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

    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
    freopen("CON", "r", stdin);

    list lista_jeden{};
    lista_jeden.add(1,1,2,2);
    lista_jeden.add(3,4,5,6);
    lista_jeden.print();



}

void Engine::printIntTable(int board_size)
{
    std::string string;
    //kolumny
    for (int i = 0; i < board_size; i++)
    {
        //szeregi
        for (int j = 0; j < board_size; j++)
        {
            qDebug() << (int)this->game_board_state[i][j];
        }
        qDebug() << "Kolejny szereg";
    }
}
