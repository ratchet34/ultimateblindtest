#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ytb_viewer.h"
#include "database.h"
#include "song.h"

#include <string>

#include <QString>
#include <QTimer>
#include <QMessageBox>
#include <QTextCodec>
#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    yViewer(new ytb_viewer()),
    timer(new QTimer),
    teamModel(new QStandardItemModel(1,0))
{
    ui->setupUi(this);
    QHBoxLayout *layout = new QHBoxLayout();

    layout->addWidget(yViewer);
    layout->setMargin(0);

    ui->verticalWidgetAnswers->hide();
    ui->progressBar->setValue(0);
    ui->teamTable->setModel(teamModel);
    ui->teamTable->setRowHeight(0, 148);
    ui->viewerFrame->setLayout(layout);

    connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));
}

void MainWindow::setYtbUrl(QString url)
{
    yViewer->load(url);
}

void MainWindow::timerTick()
{
    ui->countdownLabel->setText(QString::number(ui->countdownLabel->text().toInt() - 1));
    ui->progressBar->setValue(ui->progressBar->value()+1);
    if (ui->countdownLabel->text().toInt() == 0)
    {
        reveal();
        setStatusMessage("Countdown finished");
    }
}

void MainWindow::reveal()
{
    yViewer->showYtbViewer();
    ui->verticalWidgetAnswers->show();
    timer->stop();
}

void MainWindow::startSong(int time, QString url)
{
    yViewer->hide();
    setYtbUrl(url);

    ui->countdownLabel->setText(QString::number(time));
    ui->progressBar->setMaximum(time);
    ui->progressBar->setValue(0);


    timer->start(1000);
    QString message = "Song started - Countdown of "+QString::number(time)+"sec started";
    setStatusMessage(message);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete yViewer;
    delete timer;
    delete teamModel;
}

void MainWindow::on_addTeamButton_clicked()
{
    if (ui->teamName->text() != "") {
        QStandardItem *team = new QStandardItem(ui->teamName->text());
        QFont font = team->font();
        font.setPointSize(30);
        team->setFont(font);
        team->setTextAlignment((Qt::AlignCenter));

        QStandardItem *teamScore = new QStandardItem(QString::number(0));
        font = teamScore->font();
        font.setPointSize(72);
        teamScore->setFont(font);
        teamScore->setTextAlignment((Qt::AlignCenter));

        teamModel->setHorizontalHeaderItem(teamModel->columnCount(), team);
        teamModel->setItem(0, teamModel->columnCount()-1, teamScore);

        ui->teamTable->resizeColumnsToContents();
        ui->teamTable->selectColumn(teamModel->columnCount()-1);
        setStatusMessage("Team \""+ui->teamName->text()+"\" added to the score board");
    }

}


void MainWindow::on_removeTeamButton_clicked()
{
    try
    {
        if (teamModel->columnCount() > 0) {
            teamModel->removeColumn(ui->teamTable->currentIndex().column());
            setStatusMessage("Selected team was removed from the score board");
        }
    }
    catch (const std::exception& e)
    {
        setStatusMessage("Team not removed due to error, please try again");
    }

}

void MainWindow::on_revealButton_clicked()
{
    reveal();
    setStatusMessage("Song revealed - Timer stoppped");
}

void MainWindow::on_resetDoneButton_clicked()
{
    setAllUndone();
    setStatusMessage("All \"done\" fields set to \"False\"");
}

void MainWindow::setStatusMessage(QString message)
{
    ui->statusbar->showMessage(message);
}

void MainWindow::setCategories(std::vector<std::string> categories)
{
    ui->categoryCombo->addItem("Global");
    foreach(std::string str, categories){
        ui->categoryCombo->addItem(QString::fromStdString(str));
    }
}

void MainWindow::on_startButton_clicked()
{
    if (ui->startButton->text() == "Next Song") {
        yViewer->blockCinema();
    }

    std::string s_id;
    if (ui->categoryCombo->currentText() == "Global") {
        s_id = getGlobalRandomId();
    }
    else {
        std::string catTable = getCatTable(ui->categoryCombo->currentText().toStdString());
        s_id = getCatRandomId(catTable);
    }

    ui->playersList->setText("");
    resetPlayers();

    ui->verticalWidgetAnswers->hide();

    std::string s_time = getFieldFromId("time", s_id);
    int i_time = std::stoi(s_time);

    m_song = new song(s_id, getFieldFromId("artist", s_id), getFieldFromId("song", s_id), getFieldFromId("in", s_id), getFieldFromId("link", s_id), i_time);

    ui->answerArtist->setText(QString::fromStdString(m_song->getArtist()));
    ui->answerArtist->setCursorPosition(0);
    ui->answerSong->setText(QString::fromStdString(m_song->getSongName()));
    ui->answerSong->setCursorPosition(0);
    ui->answerIn->setText(QString::fromStdString(m_song->getIn()));
    ui->answerIn->setCursorPosition(0);
    ui->answerLink->setText(QString::fromStdString(m_song->getLink()));
    ui->answerLink->setCursorPosition(0);
    ui->answerTime->setText(QString::fromStdString(s_time));

    startSong(m_song->getTime(), QString::fromStdString(m_song->getLink()));

    ui->startButton->setText("Next Song");
}

void MainWindow::on_addTimeButton_clicked()
{
    ui->progressBar->setMaximum(ui->progressBar->maximum()+15);
    ui->countdownLabel->setText(QString::number(ui->countdownLabel->text().toInt()+15));
}

void MainWindow::on_stopButton_clicked()
{
    timer->stop();

    ui->startButton->setText("Start Game");

    ui->verticalWidgetAnswers->hide();

    ui->answerArtist->setText("");
    ui->answerSong->setText("");
    ui->answerIn->setText("");
    ui->answerLink->setText("");
    ui->answerTime->setText("");

    ui->countdownLabel->setText("30");
    ui->progressBar->setValue(0);

    yViewer->hide();
    yViewer->setUrl(QUrl("https://www.youtube.com/"));

    delete m_song;
}

void MainWindow::on_resetScoreButton_clicked()
{
    int i(0);

    for(i = 0 ; i < teamModel->columnCount()-1 ; i++)
    {
        QStandardItem *teamScore = new QStandardItem(QString::number(0));
        QFont font = teamScore->font();
        font.setPointSize(72);
        teamScore->setFont(font);
        teamScore->setTextAlignment((Qt::AlignCenter));
        teamModel->setItem(0, i, teamScore);
    }
}

void MainWindow::on_clickAdButton_clicked()
{
    yViewer->clickAd();
}

void MainWindow::on_editFieldsButton_clicked()
{
    updateSong(m_song->getId(), ui->answerArtist->text().toStdString(), ui->answerSong->text().toStdString(), ui->answerIn->text().toStdString(), ui->answerLink->text().toStdString(), ui->answerTime->text().toStdString());
}

void MainWindow::on_plusOneButton_clicked()
{
    try
    {
        if (teamModel->columnCount() > 0) {
            teamModel->item(0, ui->teamTable->currentIndex().column())->setText(QString::number(teamModel->item(0, ui->teamTable->currentIndex().column())->text().toInt()+1));
            setStatusMessage("Point substracted");
        }
    }
    catch (const std::exception& e)
    {
        setStatusMessage("Point not added due to error, please try again");
    }
}

void MainWindow::on_minusOneButton_clicked()
{
    try
    {
        if (teamModel->columnCount() > 0 && teamModel->item(0, ui->teamTable->currentIndex().column())->text().toInt() > 0) {
            teamModel->item(0, ui->teamTable->currentIndex().column())->setText(QString::number(teamModel->item(0, ui->teamTable->currentIndex().column())->text().toInt()-1));
            setStatusMessage("Point substracted");
        }
    }
    catch (const std::exception& e)
    {
        setStatusMessage("Point not substracted due to error, please try again");
    }
}

void MainWindow::on_zeroPointButton_clicked()
{
    try
    {
        if (teamModel->columnCount() > 0) {
            teamModel->item(0, ui->teamTable->currentIndex().column())->setText("0");
            setStatusMessage("Point substracted");
        }
    }
    catch (const std::exception& e)
    {
        setStatusMessage("Score not resetted due to error, please try again");
    }
}

void MainWindow::on_manualCinemaButton_clicked()
{
    yViewer->clickCinema();
}

void MainWindow::connectTcp()
{
    serveur = new QTcpServer(this);
    if (!serveur->listen(QHostAddress::Any, 50885)) // Démarrage du serveur sur toutes les IP disponibles et sur le port 50585
    {
        // Si le serveur n'a pas été démarré correctement
        setStatusMessage(tr("Le serveur n'a pas pu être démarré. Raison :<br />") + serveur->errorString());
    }
    else
    {
        // Si le serveur a été démarré correctement
        setStatusMessage(tr("Le serveur a été démarré sur le port <strong>") + QString::number(serveur->serverPort()) + tr("</strong>.<br />Des clients peuvent maintenant se connecter."));
        connect(serveur, SIGNAL(newConnection()), this, SLOT(nouvelleConnexion()));
    }

    tailleMessage = 0;
}

void MainWindow::testerror(QAbstractSocket::SocketError socketError)
{
    //setStatusMessage(socketError.);
    qDebug() << socketError;
}

void MainWindow::nouvelleConnexion()
{
    setStatusMessage(tr("<em>Un nouveau client vient de se connecter</em>"));

    QTcpSocket *nouveauClient = serveur->nextPendingConnection();
    clients << nouveauClient;

    connect(nouveauClient, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(nouveauClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));
    connect (nouveauClient, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &MainWindow::testerror);
}

void MainWindow::donneesRecues()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    socket->waitForBytesWritten(3000);
    if (socket == 0)
        return;

    QByteArray readtest = socket->readAll();

    std::string message(readtest);
    if (message.length() > 0) {
    char *mess = &message[0u];
    checkAnswer(mess);
    }
}

void MainWindow::deconnexionClient()
{

    // On détermine quel client se déconnecte
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;

    clients.removeOne(socket);

    socket->deleteLater();
}

size_t MainWindow::levenshtein_distance(const char* s, size_t n, const char* t, size_t m)
{
   ++n; ++m;
   size_t* d = new size_t[n * m];

   memset(d, 0, sizeof(size_t) * n * m);

   for (size_t i = 1, im = 0; i < m; ++i, ++im)
   {
      for (size_t j = 1, jn = 0; j < n; ++j, ++jn)
      {
         if (s[jn] == t[im])
         {
            d[(i * n) + j] = d[((i - 1) * n) + (j - 1)];
         }
         else
         {
            d[(i * n) + j] = std::min(d[(i - 1) * n + j] + 1, /* A deletion. */
                                 std::min(d[i * n + (j - 1)] + 1, /* An insertion. */
                                     d[(i - 1) * n + (j - 1)] + 1)); /* A substitution. */
         }
      }
   }

#ifdef DEBUG_PRINT
   for (size_t i = 0; i < m; ++i)
   {
      for (size_t j = 0; j < n; ++j)
      {
         cout << d[(i * n) + j] << " ";
      }
      cout << endl;
   }
#endif

   size_t r = d[n * m - 1];

   delete [] d;

   return r;
}

void MainWindow::checkAnswer(char* answer)
{
    char *player = "nothing";
    size_t playerId;
    char *name = "nothing";
    char *artist = "nothing";
    char *heard = "nothing";

    bool newPlayer = true;

    char * pch;
    int i = 0;
    pch = strtok (answer,"|");
    while (pch != NULL)
    {
        if (i == 0)
        {
            player = pch;
        }
        else if (i == 1)
        {
            artist = pch;
        }
        else if (i == 2)
        {
            name = pch;
        }
        else if (i == 3)
        {
            heard = pch;
        }

        i++;
      pch = strtok (NULL, "|");
    }


    if (players.size() > 0)
    {
        for(size_t j = 0; j<players.size(); j++)
        {
            if (players[j][0] == player)
            {
                newPlayer = false;
                playerId = j;
            }
        }
    }

    if (newPlayer)
    {
        std::vector<QString> nplayer;
        nplayer.push_back(player);

        double artistDist = static_cast<double>(levenshtein_distance(artist, strlen(artist),m_song->getArtist().c_str(),m_song->getArtist().length()))/static_cast<double>(m_song->getArtist().length());
        if (artistDist < 0.2 and m_song->getArtist() != "")
        {
            nplayer.push_back("Artist found");
        }
        else
        {
            nplayer.push_back("");
        }

        double nameDist = static_cast<double>(levenshtein_distance(name, strlen(name),m_song->getSongName().c_str(),m_song->getSongName().length()))/static_cast<double>(m_song->getSongName().length());
        if (nameDist < 0.2 and m_song->getSongName() != "")
        {
            nplayer.push_back("Song name found");
        }
        else
        {
            nplayer.push_back("");
        }

        double heardDist = static_cast<double>(levenshtein_distance(heard, strlen(heard),m_song->getIn().c_str(),m_song->getIn().length()))/static_cast<double>(m_song->getIn().length());
        if (heardDist < 0.2 and m_song->getIn() != "")
        {
            nplayer.push_back("Heard in found");
        }
        else
        {
            nplayer.push_back("");
        }

        players.push_back(nplayer);

    }
    else
    {
        if (players[playerId][1] != "Artist found")
        {
            double artistDist = static_cast<double>(levenshtein_distance(artist, strlen(artist),m_song->getArtist().c_str(),m_song->getArtist().length()))/static_cast<double>(m_song->getArtist().length());
            if (artistDist < 0.2 and m_song->getArtist() != "")
            {
                players[playerId][1] = "Artist found";
            }
            else
            {
                players[playerId][1] = "";
            }
        }

        if (players[playerId][2] != "Song name found")
        {
            double nameDist = static_cast<double>(levenshtein_distance(name, strlen(name),m_song->getSongName().c_str(),m_song->getSongName().length()))/static_cast<double>(m_song->getSongName().length());
            if (nameDist < 0.2 and m_song->getSongName() != "")
            {
                players[playerId][2] = "Song name found";
            }
            else
            {
                players[playerId][2] = "";
            }
        }


        if (players[playerId][3] != "Heard in found")
        {
            double heardDist = static_cast<double>(levenshtein_distance(heard, strlen(heard),m_song->getIn().c_str(),m_song->getIn().length()))/static_cast<double>(m_song->getIn().length());
            if (heardDist < 0.2 and m_song->getIn() != "")
            {
                players[playerId][3] = "Heard in found";
            }
            else
            {
                players[playerId][3] = "";
            }
        }
    }
    updatePlayers();
}

void MainWindow::updatePlayers()
{
    ui->playersList->clear();
    if (players.size() > 0) {
        for(size_t i = 0; i<players.size(); i++)
        {
            ui->playersList->append(players[i][0] + " - " + players[i][1] + " - " + players[i][2] + " - " + players[i][3] + "\n");
        }
    }

}

void MainWindow::resetPlayers()
{
    ui->playersList->clear();
    if (players.size() > 0) {
        for(size_t i = 0; i<players.size(); i++)
        {
            for(size_t j = 1; j<players[i].size(); j++)
            {
                players[i][j] = "";
            }
        }
    }
}


