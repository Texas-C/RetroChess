/* This is the main page displayed by the plugin
 *
 * For:
 * 	event handle
 * 	peer check
 *  game launching
*/

#ifndef NEMAINPAGE_H
#define NEMAINPAGE_H

#include <retroshare-gui/mainpage.h>
#include <retroshare/rsfiles.h>
#include <retroshare/rspeers.h>
#include "gui/RetroChessNotify.h"

#include "gui/chess.h"

#include <QWidget>

class QAction;

namespace Ui
{
class NEMainpage;
}

class NEMainpage : public MainPage
{
	Q_OBJECT

public:
	explicit NEMainpage(QWidget *parent, RetroChessNotify *notify);
	~NEMainpage();

private slots:
	void setupMenuActions();
	void friendSelectionChanged();
	void NeMsgArrived(const RsPeerId &peer_id, QString str);
	void chessStart(const RsPeerId &peer_id);

	void on_broadcastButton_clicked();

    //--- test invite button, try to invite p2p friend
    void enable_inviteButton();	// enable the invite button when selected a friend

    void on_inviteButton_clicked();

	void on_filterPeersButton_clicked();


private:
	Ui::NEMainpage *ui;
	RetroChessNotify *mNotify;

	QAction *mActionPlayChess;
	//RetroChessWindow *tempwindow;

	QMap<std::string, RetroChessWindow*> activeGames;
	void create_chess_window(std::string peer_id, int player_id);
};

#endif // NEMAINPAGE_H
