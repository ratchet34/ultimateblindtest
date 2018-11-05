/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *global_VLayout;
    QHBoxLayout *menuViewer_HLayout;
    QFrame *menuFrame;
    QVBoxLayout *verticalLayout_5;
    QLabel *categoryLabel;
    QComboBox *categoryCombo;
    QPushButton *startButton;
    QPushButton *stopButton;
    QWidget *verticalWidgetAnswers;
    QVBoxLayout *verticalLayoutAnswers;
    QLineEdit *answerArtist;
    QLineEdit *answerSong;
    QLineEdit *answerIn;
    QLineEdit *answerLink;
    QLineEdit *answerTime;
    QPushButton *editFieldsButton;
    QTextBrowser *playersList;
    QLineEdit *teamName;
    QGridLayout *gridLayout_2;
    QPushButton *resetScoreButton;
    QPushButton *resetDoneButton;
    QPushButton *addTeamButton;
    QPushButton *removeTeamButton;
    QPushButton *revealButton;
    QPushButton *addTimeButton;
    QVBoxLayout *verticalLayout;
    QFrame *viewerFrame;
    QProgressBar *progressBar;
    QHBoxLayout *cntdownScore_HLayout;
    QLabel *countdownLabel;
    QTableView *teamTable;
    QVBoxLayout *verticalLayout_3;
    QPushButton *manualCinemaButton;
    QPushButton *clickAdButton;
    QFrame *line;
    QPushButton *plusOneButton;
    QPushButton *minusOneButton;
    QPushButton *zeroPointButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1190, 810);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setEnabled(true);
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        global_VLayout = new QVBoxLayout();
        global_VLayout->setObjectName(QStringLiteral("global_VLayout"));
        menuViewer_HLayout = new QHBoxLayout();
        menuViewer_HLayout->setObjectName(QStringLiteral("menuViewer_HLayout"));
        menuFrame = new QFrame(centralwidget);
        menuFrame->setObjectName(QStringLiteral("menuFrame"));
        menuFrame->setMinimumSize(QSize(250, 0));
        menuFrame->setMaximumSize(QSize(250, 16777215));
        menuFrame->setFrameShape(QFrame::StyledPanel);
        menuFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_5 = new QVBoxLayout(menuFrame);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        categoryLabel = new QLabel(menuFrame);
        categoryLabel->setObjectName(QStringLiteral("categoryLabel"));

        verticalLayout_5->addWidget(categoryLabel);

        categoryCombo = new QComboBox(menuFrame);
        categoryCombo->setObjectName(QStringLiteral("categoryCombo"));

        verticalLayout_5->addWidget(categoryCombo);

        startButton = new QPushButton(menuFrame);
        startButton->setObjectName(QStringLiteral("startButton"));
        QPalette palette;
        QBrush brush(QColor(115, 210, 22, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        startButton->setPalette(palette);
        startButton->setAutoFillBackground(false);

        verticalLayout_5->addWidget(startButton);

        stopButton = new QPushButton(menuFrame);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        QPalette palette1;
        QBrush brush1(QColor(239, 41, 41, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        stopButton->setPalette(palette1);

        verticalLayout_5->addWidget(stopButton);

        verticalWidgetAnswers = new QWidget(menuFrame);
        verticalWidgetAnswers->setObjectName(QStringLiteral("verticalWidgetAnswers"));
        verticalLayoutAnswers = new QVBoxLayout(verticalWidgetAnswers);
        verticalLayoutAnswers->setObjectName(QStringLiteral("verticalLayoutAnswers"));
        answerArtist = new QLineEdit(verticalWidgetAnswers);
        answerArtist->setObjectName(QStringLiteral("answerArtist"));

        verticalLayoutAnswers->addWidget(answerArtist);

        answerSong = new QLineEdit(verticalWidgetAnswers);
        answerSong->setObjectName(QStringLiteral("answerSong"));

        verticalLayoutAnswers->addWidget(answerSong);

        answerIn = new QLineEdit(verticalWidgetAnswers);
        answerIn->setObjectName(QStringLiteral("answerIn"));

        verticalLayoutAnswers->addWidget(answerIn);

        answerLink = new QLineEdit(verticalWidgetAnswers);
        answerLink->setObjectName(QStringLiteral("answerLink"));

        verticalLayoutAnswers->addWidget(answerLink);

        answerTime = new QLineEdit(verticalWidgetAnswers);
        answerTime->setObjectName(QStringLiteral("answerTime"));

        verticalLayoutAnswers->addWidget(answerTime);

        editFieldsButton = new QPushButton(verticalWidgetAnswers);
        editFieldsButton->setObjectName(QStringLiteral("editFieldsButton"));

        verticalLayoutAnswers->addWidget(editFieldsButton);


        verticalLayout_5->addWidget(verticalWidgetAnswers);

        playersList = new QTextBrowser(menuFrame);
        playersList->setObjectName(QStringLiteral("playersList"));

        verticalLayout_5->addWidget(playersList);

        teamName = new QLineEdit(menuFrame);
        teamName->setObjectName(QStringLiteral("teamName"));

        verticalLayout_5->addWidget(teamName);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        resetScoreButton = new QPushButton(menuFrame);
        resetScoreButton->setObjectName(QStringLiteral("resetScoreButton"));

        gridLayout_2->addWidget(resetScoreButton, 2, 0, 1, 1);

        resetDoneButton = new QPushButton(menuFrame);
        resetDoneButton->setObjectName(QStringLiteral("resetDoneButton"));

        gridLayout_2->addWidget(resetDoneButton, 2, 1, 1, 1);

        addTeamButton = new QPushButton(menuFrame);
        addTeamButton->setObjectName(QStringLiteral("addTeamButton"));

        gridLayout_2->addWidget(addTeamButton, 0, 0, 1, 1);

        removeTeamButton = new QPushButton(menuFrame);
        removeTeamButton->setObjectName(QStringLiteral("removeTeamButton"));

        gridLayout_2->addWidget(removeTeamButton, 0, 1, 1, 1);

        revealButton = new QPushButton(menuFrame);
        revealButton->setObjectName(QStringLiteral("revealButton"));

        gridLayout_2->addWidget(revealButton, 1, 0, 1, 1);

        addTimeButton = new QPushButton(menuFrame);
        addTimeButton->setObjectName(QStringLiteral("addTimeButton"));

        gridLayout_2->addWidget(addTimeButton, 1, 1, 1, 1);


        verticalLayout_5->addLayout(gridLayout_2);


        menuViewer_HLayout->addWidget(menuFrame);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        viewerFrame = new QFrame(centralwidget);
        viewerFrame->setObjectName(QStringLiteral("viewerFrame"));
        viewerFrame->setFrameShape(QFrame::StyledPanel);
        viewerFrame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(viewerFrame);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setMaximum(30);
        progressBar->setValue(24);
        progressBar->setTextVisible(false);

        verticalLayout->addWidget(progressBar);


        menuViewer_HLayout->addLayout(verticalLayout);


        global_VLayout->addLayout(menuViewer_HLayout);

        cntdownScore_HLayout = new QHBoxLayout();
        cntdownScore_HLayout->setObjectName(QStringLiteral("cntdownScore_HLayout"));
        countdownLabel = new QLabel(centralwidget);
        countdownLabel->setObjectName(QStringLiteral("countdownLabel"));
        countdownLabel->setMinimumSize(QSize(250, 200));
        countdownLabel->setMaximumSize(QSize(250, 200));
        QFont font;
        font.setPointSize(150);
        countdownLabel->setFont(font);
        countdownLabel->setLayoutDirection(Qt::LeftToRight);
        countdownLabel->setFrameShape(QFrame::StyledPanel);
        countdownLabel->setAlignment(Qt::AlignCenter);

        cntdownScore_HLayout->addWidget(countdownLabel);

        teamTable = new QTableView(centralwidget);
        teamTable->setObjectName(QStringLiteral("teamTable"));
        teamTable->setMinimumSize(QSize(0, 200));
        teamTable->setMaximumSize(QSize(16777215, 200));
        teamTable->verticalHeader()->setVisible(false);

        cntdownScore_HLayout->addWidget(teamTable);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        manualCinemaButton = new QPushButton(centralwidget);
        manualCinemaButton->setObjectName(QStringLiteral("manualCinemaButton"));

        verticalLayout_3->addWidget(manualCinemaButton);

        clickAdButton = new QPushButton(centralwidget);
        clickAdButton->setObjectName(QStringLiteral("clickAdButton"));

        verticalLayout_3->addWidget(clickAdButton);

        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        plusOneButton = new QPushButton(centralwidget);
        plusOneButton->setObjectName(QStringLiteral("plusOneButton"));

        verticalLayout_3->addWidget(plusOneButton);

        minusOneButton = new QPushButton(centralwidget);
        minusOneButton->setObjectName(QStringLiteral("minusOneButton"));

        verticalLayout_3->addWidget(minusOneButton);

        zeroPointButton = new QPushButton(centralwidget);
        zeroPointButton->setObjectName(QStringLiteral("zeroPointButton"));

        verticalLayout_3->addWidget(zeroPointButton);


        cntdownScore_HLayout->addLayout(verticalLayout_3);


        global_VLayout->addLayout(cntdownScore_HLayout);


        verticalLayout_2->addLayout(global_VLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1190, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Ultimate Blindtest", Q_NULLPTR));
        categoryLabel->setText(QApplication::translate("MainWindow", "Select a category :", Q_NULLPTR));
        startButton->setText(QApplication::translate("MainWindow", "Start Game", Q_NULLPTR));
        stopButton->setText(QApplication::translate("MainWindow", "Stop Game", Q_NULLPTR));
        answerArtist->setPlaceholderText(QApplication::translate("MainWindow", "Artist", Q_NULLPTR));
        answerSong->setPlaceholderText(QApplication::translate("MainWindow", "Song name", Q_NULLPTR));
        answerIn->setPlaceholderText(QApplication::translate("MainWindow", "Heard in", Q_NULLPTR));
        answerLink->setPlaceholderText(QApplication::translate("MainWindow", "Youtube link", Q_NULLPTR));
        answerTime->setPlaceholderText(QApplication::translate("MainWindow", "Guess time", Q_NULLPTR));
        editFieldsButton->setText(QApplication::translate("MainWindow", "Edit song", Q_NULLPTR));
        teamName->setPlaceholderText(QApplication::translate("MainWindow", "Team name", Q_NULLPTR));
        resetScoreButton->setText(QApplication::translate("MainWindow", "Reset Scores", Q_NULLPTR));
        resetDoneButton->setText(QApplication::translate("MainWindow", "Reset Done", Q_NULLPTR));
        addTeamButton->setText(QApplication::translate("MainWindow", "Add Team", Q_NULLPTR));
        removeTeamButton->setText(QApplication::translate("MainWindow", "Remove Team", Q_NULLPTR));
        revealButton->setText(QApplication::translate("MainWindow", "Reveal Song", Q_NULLPTR));
        addTimeButton->setText(QApplication::translate("MainWindow", "Add 15sec", Q_NULLPTR));
        countdownLabel->setText(QApplication::translate("MainWindow", "30", Q_NULLPTR));
        manualCinemaButton->setText(QApplication::translate("MainWindow", "Cinema Mode", Q_NULLPTR));
        clickAdButton->setText(QApplication::translate("MainWindow", "Click Ad", Q_NULLPTR));
        plusOneButton->setText(QApplication::translate("MainWindow", "+1 Point", Q_NULLPTR));
        minusOneButton->setText(QApplication::translate("MainWindow", "-1 Point", Q_NULLPTR));
        zeroPointButton->setText(QApplication::translate("MainWindow", "Back to 0", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
