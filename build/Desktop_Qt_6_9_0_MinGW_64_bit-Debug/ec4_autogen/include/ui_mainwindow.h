/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *autoTab;
    QVBoxLayout *verticalLayout_auto;
    QHBoxLayout *horizontalLayout_auto;
    QLabel *label;
    QSpinBox *wordLengthSpinBox_auto;
    QPushButton *loadDictButton_auto;
    QHBoxLayout *horizontalLayout_auto_2;
    QLabel *label_2;
    QLineEdit *startWordLineEdit_auto;
    QLabel *label_3;
    QLineEdit *targetWordLineEdit_auto;
    QPushButton *findPathButton_auto;
    QLabel *statusLabel_auto;
    QListWidget *pathListWidget_auto;
    QWidget *playTab;
    QVBoxLayout *verticalLayout_play;
    QHBoxLayout *horizontalLayout_play;
    QLabel *label_4;
    QLineEdit *playerNameLineEdit_play;
    QLabel *label_5;
    QSpinBox *wordLengthSpinBox_play;
    QPushButton *startGameButton_play;
    QHBoxLayout *horizontalLayout_play_2;
    QLabel *startWordLabel_play;
    QLabel *targetWordLabel_play;
    QLabel *currentWordLabel_play;
    QHBoxLayout *horizontalLayout_play_3;
    QLabel *movesLabel_play;
    QLabel *hintsUsedLabel_play;
    QHBoxLayout *horizontalLayout_play_4;
    QLabel *label_6;
    QLineEdit *nextWordLineEdit_play;
    QPushButton *submitWordButton_play;
    QPushButton *hintButton_play;
    QLabel *gameStatusLabel_play;
    QListWidget *playerPathListWidget_play;
    QWidget *analyticsTab;
    QVBoxLayout *verticalLayout_analytics;
    QHBoxLayout *horizontalLayout_analytics;
    QLabel *label_7;
    QLineEdit *playerNameLineEdit_analytics;
    QPushButton *loadStatsButton_analytics;
    QTextEdit *statsTextEdit_analytics;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        autoTab = new QWidget();
        autoTab->setObjectName("autoTab");
        verticalLayout_auto = new QVBoxLayout(autoTab);
        verticalLayout_auto->setObjectName("verticalLayout_auto");
        horizontalLayout_auto = new QHBoxLayout();
        horizontalLayout_auto->setObjectName("horizontalLayout_auto");
        label = new QLabel(autoTab);
        label->setObjectName("label");

        horizontalLayout_auto->addWidget(label);

        wordLengthSpinBox_auto = new QSpinBox(autoTab);
        wordLengthSpinBox_auto->setObjectName("wordLengthSpinBox_auto");
        wordLengthSpinBox_auto->setMinimum(3);
        wordLengthSpinBox_auto->setMaximum(10);
        wordLengthSpinBox_auto->setValue(4);

        horizontalLayout_auto->addWidget(wordLengthSpinBox_auto);

        loadDictButton_auto = new QPushButton(autoTab);
        loadDictButton_auto->setObjectName("loadDictButton_auto");

        horizontalLayout_auto->addWidget(loadDictButton_auto);


        verticalLayout_auto->addLayout(horizontalLayout_auto);

        horizontalLayout_auto_2 = new QHBoxLayout();
        horizontalLayout_auto_2->setObjectName("horizontalLayout_auto_2");
        label_2 = new QLabel(autoTab);
        label_2->setObjectName("label_2");

        horizontalLayout_auto_2->addWidget(label_2);

        startWordLineEdit_auto = new QLineEdit(autoTab);
        startWordLineEdit_auto->setObjectName("startWordLineEdit_auto");

        horizontalLayout_auto_2->addWidget(startWordLineEdit_auto);

        label_3 = new QLabel(autoTab);
        label_3->setObjectName("label_3");

        horizontalLayout_auto_2->addWidget(label_3);

        targetWordLineEdit_auto = new QLineEdit(autoTab);
        targetWordLineEdit_auto->setObjectName("targetWordLineEdit_auto");

        horizontalLayout_auto_2->addWidget(targetWordLineEdit_auto);

        findPathButton_auto = new QPushButton(autoTab);
        findPathButton_auto->setObjectName("findPathButton_auto");

        horizontalLayout_auto_2->addWidget(findPathButton_auto);


        verticalLayout_auto->addLayout(horizontalLayout_auto_2);

        statusLabel_auto = new QLabel(autoTab);
        statusLabel_auto->setObjectName("statusLabel_auto");

        verticalLayout_auto->addWidget(statusLabel_auto);

        pathListWidget_auto = new QListWidget(autoTab);
        pathListWidget_auto->setObjectName("pathListWidget_auto");

        verticalLayout_auto->addWidget(pathListWidget_auto);

        tabWidget->addTab(autoTab, QString());
        playTab = new QWidget();
        playTab->setObjectName("playTab");
        verticalLayout_play = new QVBoxLayout(playTab);
        verticalLayout_play->setObjectName("verticalLayout_play");
        horizontalLayout_play = new QHBoxLayout();
        horizontalLayout_play->setObjectName("horizontalLayout_play");
        label_4 = new QLabel(playTab);
        label_4->setObjectName("label_4");

        horizontalLayout_play->addWidget(label_4);

        playerNameLineEdit_play = new QLineEdit(playTab);
        playerNameLineEdit_play->setObjectName("playerNameLineEdit_play");

        horizontalLayout_play->addWidget(playerNameLineEdit_play);

        label_5 = new QLabel(playTab);
        label_5->setObjectName("label_5");

        horizontalLayout_play->addWidget(label_5);

        wordLengthSpinBox_play = new QSpinBox(playTab);
        wordLengthSpinBox_play->setObjectName("wordLengthSpinBox_play");
        wordLengthSpinBox_play->setMinimum(3);
        wordLengthSpinBox_play->setMaximum(10);
        wordLengthSpinBox_play->setValue(4);

        horizontalLayout_play->addWidget(wordLengthSpinBox_play);

        startGameButton_play = new QPushButton(playTab);
        startGameButton_play->setObjectName("startGameButton_play");

        horizontalLayout_play->addWidget(startGameButton_play);


        verticalLayout_play->addLayout(horizontalLayout_play);

        horizontalLayout_play_2 = new QHBoxLayout();
        horizontalLayout_play_2->setObjectName("horizontalLayout_play_2");
        startWordLabel_play = new QLabel(playTab);
        startWordLabel_play->setObjectName("startWordLabel_play");

        horizontalLayout_play_2->addWidget(startWordLabel_play);

        targetWordLabel_play = new QLabel(playTab);
        targetWordLabel_play->setObjectName("targetWordLabel_play");

        horizontalLayout_play_2->addWidget(targetWordLabel_play);

        currentWordLabel_play = new QLabel(playTab);
        currentWordLabel_play->setObjectName("currentWordLabel_play");

        horizontalLayout_play_2->addWidget(currentWordLabel_play);


        verticalLayout_play->addLayout(horizontalLayout_play_2);

        horizontalLayout_play_3 = new QHBoxLayout();
        horizontalLayout_play_3->setObjectName("horizontalLayout_play_3");
        movesLabel_play = new QLabel(playTab);
        movesLabel_play->setObjectName("movesLabel_play");

        horizontalLayout_play_3->addWidget(movesLabel_play);

        hintsUsedLabel_play = new QLabel(playTab);
        hintsUsedLabel_play->setObjectName("hintsUsedLabel_play");

        horizontalLayout_play_3->addWidget(hintsUsedLabel_play);


        verticalLayout_play->addLayout(horizontalLayout_play_3);

        horizontalLayout_play_4 = new QHBoxLayout();
        horizontalLayout_play_4->setObjectName("horizontalLayout_play_4");
        label_6 = new QLabel(playTab);
        label_6->setObjectName("label_6");

        horizontalLayout_play_4->addWidget(label_6);

        nextWordLineEdit_play = new QLineEdit(playTab);
        nextWordLineEdit_play->setObjectName("nextWordLineEdit_play");

        horizontalLayout_play_4->addWidget(nextWordLineEdit_play);

        submitWordButton_play = new QPushButton(playTab);
        submitWordButton_play->setObjectName("submitWordButton_play");

        horizontalLayout_play_4->addWidget(submitWordButton_play);

        hintButton_play = new QPushButton(playTab);
        hintButton_play->setObjectName("hintButton_play");

        horizontalLayout_play_4->addWidget(hintButton_play);


        verticalLayout_play->addLayout(horizontalLayout_play_4);

        gameStatusLabel_play = new QLabel(playTab);
        gameStatusLabel_play->setObjectName("gameStatusLabel_play");

        verticalLayout_play->addWidget(gameStatusLabel_play);

        playerPathListWidget_play = new QListWidget(playTab);
        playerPathListWidget_play->setObjectName("playerPathListWidget_play");

        verticalLayout_play->addWidget(playerPathListWidget_play);

        tabWidget->addTab(playTab, QString());
        analyticsTab = new QWidget();
        analyticsTab->setObjectName("analyticsTab");
        verticalLayout_analytics = new QVBoxLayout(analyticsTab);
        verticalLayout_analytics->setObjectName("verticalLayout_analytics");
        horizontalLayout_analytics = new QHBoxLayout();
        horizontalLayout_analytics->setObjectName("horizontalLayout_analytics");
        label_7 = new QLabel(analyticsTab);
        label_7->setObjectName("label_7");

        horizontalLayout_analytics->addWidget(label_7);

        playerNameLineEdit_analytics = new QLineEdit(analyticsTab);
        playerNameLineEdit_analytics->setObjectName("playerNameLineEdit_analytics");

        horizontalLayout_analytics->addWidget(playerNameLineEdit_analytics);

        loadStatsButton_analytics = new QPushButton(analyticsTab);
        loadStatsButton_analytics->setObjectName("loadStatsButton_analytics");

        horizontalLayout_analytics->addWidget(loadStatsButton_analytics);


        verticalLayout_analytics->addLayout(horizontalLayout_analytics);

        statsTextEdit_analytics = new QTextEdit(analyticsTab);
        statsTextEdit_analytics->setObjectName("statsTextEdit_analytics");
        statsTextEdit_analytics->setReadOnly(true);

        verticalLayout_analytics->addWidget(statsTextEdit_analytics);

        tabWidget->addTab(analyticsTab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Word Ladder Game", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Word Length:", nullptr));
        loadDictButton_auto->setText(QCoreApplication::translate("MainWindow", "Load Dictionary", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Start Word:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Target Word:", nullptr));
        findPathButton_auto->setText(QCoreApplication::translate("MainWindow", "Find Path", nullptr));
        statusLabel_auto->setText(QCoreApplication::translate("MainWindow", "Ready", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(autoTab), QCoreApplication::translate("MainWindow", "Auto Mode", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Player Name:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Word Length:", nullptr));
        startGameButton_play->setText(QCoreApplication::translate("MainWindow", "Start Game", nullptr));
        startWordLabel_play->setText(QCoreApplication::translate("MainWindow", "Start: -", nullptr));
        targetWordLabel_play->setText(QCoreApplication::translate("MainWindow", "Target: -", nullptr));
        currentWordLabel_play->setText(QCoreApplication::translate("MainWindow", "Current: -", nullptr));
        movesLabel_play->setText(QCoreApplication::translate("MainWindow", "Moves: -", nullptr));
        hintsUsedLabel_play->setText(QCoreApplication::translate("MainWindow", "Hints: -", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Next Word:", nullptr));
        submitWordButton_play->setText(QCoreApplication::translate("MainWindow", "Submit", nullptr));
        hintButton_play->setText(QCoreApplication::translate("MainWindow", "Hint", nullptr));
        gameStatusLabel_play->setText(QCoreApplication::translate("MainWindow", "Select word length and player name, then start game.", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(playTab), QCoreApplication::translate("MainWindow", "Play Mode", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Player Name:", nullptr));
        loadStatsButton_analytics->setText(QCoreApplication::translate("MainWindow", "Load Stats", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(analyticsTab), QCoreApplication::translate("MainWindow", "Analytics", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
