#include "engine.h"

void Engine::initializeBoard(int board_size)
{
    game_board_T = new boardTile*[board_size];
    game_board_int = new int*[board_size];
    for (int i = 0; i < board_size; i++)
    {
        this->game_board_int[i] = new int[board_size];
        game_board_T[i] = new boardTile[board_size];
    }
    //Rozmiesc plytki na scenie
    //szerokosc SCENY (nie okna) - ilosc plytek razy rozmiar plytek dzielone na dwa to srodek sceny
    int x = (this->scene->width()-board_size*BOARD_TILE_SIZE) / 2, y = (this->scene->height()-board_size*BOARD_TILE_SIZE) / 2;


    int parity = 1;
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            game_board_int[i][j] = 0;
            game_board_T[i][j].setPos(x + BOARD_TILE_SIZE*i, y + BOARD_TILE_SIZE*j);

            //ustala wartosc piora na 0 (bez ramki)
            game_board_T[i][j].setPen(QPen(QBrush(), 0));

            if (parity%2 == 0)  //jesli plytka parzysta pokoloruj na ciemno
                game_board_T[i][j].setBrush(dark_tile);
            else                //jesli nie pokoloruj na jasno
                game_board_T[i][j].setBrush(light_tile);

            //dodaj plytki do sceny
            scene->addItem(&game_board_T[i][j]);
            parity++;
        }
        parity++;
    }
}

void Engine::placePawns(int pawns_count, int board_size)
{
    QColor actual_pawn_colour = dark_pawn;  //kolor na ktory sa kolorowane aktualnie pionki
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
                    game_board_int[i][j] = 1;

                    //ustal pozycje wzgledem aktualnie iterowanej plytki
                    x = game_board_T[j][i].pos().x();
                    y = game_board_T[j][i].pos().y();

                    Pawn *p = new Pawn(this);
                    p->setRect(x + 5, y + 5, 40, 40);
                    p->setBrush(actual_pawn_colour);
                    //ustala wartosc piora na 0 (bez ramki)
                    p->setPen(QPen(QBrush(), 0));

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
                actual_pawn_colour = light_pawn;
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
                    game_board_int[i][j] = 1;

                    Pawn *p = new Pawn(this);
                    //ustala wartosc piora na 0 (bez ramki)
                    p->setPen(QPen(QBrush(), 0));
                    p->setRect(x + 5, y + 5, 40, 40);
                    p->setBrush(actual_pawn_colour);

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
    if (select != nullptr)
    {
        Pawn *selected_pawn = dynamic_cast<Pawn*>(select);
        if (selected_pawn != nullptr)
        {
             if (typeid (*selected_pawn) == typeid(Pawn))
            {
                selected_pawn->setBrush(QBrush(QColor(34, 177, 76)));
                qDebug() << "Poprawnie zrzutowano";
             }
        }
    }

}

void Engine::handleExitButton()
{
    this->close();
    this->destroy();
    Menu *menu = new Menu();
    menu->show();
}

Engine::Engine()
{
    //ustal rozmiar sceny
    scene = new QGraphicsScene(0, 0, 800, 600);
    this->setScene(scene);
    //wygladzanie krawedzi
    this->setRenderHints(QPainter::Antialiasing);

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
            qDebug() << this->game_board_int[i][j];
        }
        qDebug() << "Kolejny szereg";
    }
}
