#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ytb_viewer.h"
#include "database.h"
#include "song.h"

#include <string>

#include <QString>
#include <QTimer>
#include <QMessageBox>

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
    checkAnswers(m_song->getArtist(), m_song->getSongName(), m_song->getIn());
    std::string playersListText = getPlayerStatus();
    ui->playersList->setText(QString::fromStdString(playersListText));
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
    setSongRunning("false");
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
    setNotFoundAll();
    setSongRunning("True");

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
