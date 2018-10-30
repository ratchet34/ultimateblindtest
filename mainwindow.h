#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QString>
#include <QTimer>
#include <QStandardItemModel>
#include <vector>
#include <string>

#include "ytb_viewer.h"
#include "song.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setYtbUrl(QString url);
    void startSong(int time, QString url);
    void setStatusMessage(QString message);
    void setCategories(std::vector<std::string> categories);
    void reveal();
    ~MainWindow();

public slots:
    void timerTick();

private slots:
    void on_addTeamButton_clicked();

    void on_revealButton_clicked();

    void on_removeTeamButton_clicked();

    void on_resetDoneButton_clicked();

    void on_startButton_clicked();

    void on_addTimeButton_clicked();

    void on_stopButton_clicked();

    void on_resetScoreButton_clicked();

    void on_clickAdButton_clicked();

    void on_editFieldsButton_clicked();

    void on_plusOneButton_clicked();

    void on_minusOneButton_clicked();

    void on_zeroPointButton_clicked();

    void on_manualCinemaButton_clicked();

private:
    Ui::MainWindow *ui;
    ytb_viewer *yViewer;
    QTimer *timer;
    QStandardItemModel *teamModel;
    song *m_song;
    int time;
};

#endif // MAINWINDOW_H
