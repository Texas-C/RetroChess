#include "tile.h"
#include "chess.h"
#include "../interface/rsRetroChess.h"

/*extern int count,turn;
extern QWidget *myWidget;
extern Tile *click1;
extern Tile *tile[8][8];
*/

void validate(Tile *tile_p,int c);
void disOrange();

Tile::Tile(QWidget* pParent, Qt::WindowFlags f) : QLabel(pParent, f)
{}

Tile::Tile(const QString& text, QWidget* pParent, Qt::WindowFlags f) : QLabel(text, pParent, f)
{}

void Tile::mousePressEvent(QMouseEvent *event)
{
    RetroChessWindow *chess_window_p = dynamic_cast<RetroChessWindow*>(m_chess_window_p );

    validate(++(chess_window_p)->count);
    std::string peer_id = (chess_window_p)->mPeerId;
    rsRetroChess->chess_click(peer_id, this->row,this->col,(chess_window_p)->count);

	QLabel::mousePressEvent( event );
}

void Tile::display(char elem)
{
	this->pieceName=elem;

	if(this->pieceColor && this->piece)
	{
		switch(elem)
		{
		case 'P':
			this->setPixmap(QPixmap(":/images/pawn_white.svg"));
			break;
		case 'R':
			this->setPixmap(QPixmap(":/images/rook_white.svg"));
			break;
		case 'H':
			this->setPixmap(QPixmap(":/images/knight_white.svg"));
			break;
		case 'K':
			this->setPixmap(QPixmap(":/images/king_white.svg"));
			break;
		case 'Q':
			this->setPixmap(QPixmap(":/images/queen_white.svg"));
			break;
		case 'B':
			this->setPixmap(QPixmap(":/images/bishop_white.svg"));
			break;
		}
	}

	else if(this->piece)
	{
		switch(elem)
		{
		case 'P':
			this->setPixmap(QPixmap(":/images/pawn_black.svg"));
			break;
		case 'R':
			this->setPixmap(QPixmap(":/images/rook_black.svg"));
			break;
		case 'H':
			this->setPixmap(QPixmap(":/images/knight_black.svg"));
			break;
		case 'K':
			this->setPixmap(QPixmap(":/images/king_black.svg"));
			break;
		case 'Q':
			this->setPixmap(QPixmap(":/images/queen_black.svg"));
			break;
		case 'B':
			this->setPixmap(QPixmap(":/images/bishop_black.svg"));
			break;
		}
	}
	else
		this->clear();
}

// check single/double click
void Tile::validate(int c)
{
	Tile *tile_p = this;

	int retValue,i;

    RetroChessWindow *chess_window_p = dynamic_cast< RetroChessWindow*> (m_chess_window_p );

	// click 1
	if(c == 1)
	{
		// clicked current player's piece
		if(tile_p->piece && (tile_p->pieceColor==(chess_window_p)->turn))
		{
			//texp[max++]=tile_p->tileNum;
			retValue = (chess_window_p)->chooser(tile_p);	// paint piece's next availalbe position

			if(retValue)
			{
				(chess_window_p)->click1= new Tile();
				tile_p->setStyleSheet("QLabel {background-color: green;}");
				(chess_window_p)->click1=tile_p;
			}
			else
			{
				//tile_p->setStyleSheet("QLabel {background-color: red;}");
				(chess_window_p)->count=0;
			}
		}

		// didn't clicked current player's piece
		else
		{
			//qDebug()<<"Rascel, clicking anywhere";
			(chess_window_p)->count=0;
		}
	}

    // click 0 or 2 times
	else
	{

		if(tile_p->tileNum==(chess_window_p)->click1->tileNum)
		{
			(chess_window_p)->click1->tileDisplay();
			(chess_window_p)->disOrange();
			(chess_window_p)->max=0;
			(chess_window_p)->count=0;
		}

		for(i=0; i<(chess_window_p)->max; i++)
		{
			if(tile_p->tileNum==(chess_window_p)->texp[i])
			{
				(chess_window_p)->click1->piece=0;
				tile_p->piece=1;

				tile_p->pieceColor=(chess_window_p)->click1->pieceColor;
				tile_p->pieceName=(chess_window_p)->click1->pieceName;

				(chess_window_p)->click1->display((chess_window_p)->click1->pieceName);
				tile_p->display((chess_window_p)->click1->pieceName);

				(chess_window_p)->click1->tileDisplay();
				tile_p->tileDisplay();

				retValue=(chess_window_p)->check((chess_window_p)->click1);
				/*
				if(retValue)
				{
				    tile[wR][wC]->setStyleSheet("QLabel {background-color: red;}");
				}
				*/

				(chess_window_p)->disOrange();

				(chess_window_p)->max=0;

				(chess_window_p)->turn=((chess_window_p)->turn+1)%2;
				(chess_window_p)->count=0;
			}

			else
				(chess_window_p)->count=1;
		}
	}
}

void Tile::tileDisplay()
{

	if(this->tileColor)
		this->setStyleSheet("QLabel {background-color: rgb(120, 120, 90);}:hover{background-color: rgb(170,85,127);}");
	else
		this->setStyleSheet("QLabel {background-color: rgb(211, 211, 158);}:hover{background-color: rgb(170,95,127);}");
}


void Tile::setChessWindow(QWidget *board)
{
    m_chess_window_p = board;
}

QWidget* Tile::getChessWindow() const
{
    return m_chess_window_p;
}
