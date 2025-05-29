#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <vector>
#include <string>
#include <QDateTime>
#include "wordladdergame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief The main window class for the Word Ladder Game application
 * 
 * This class handles the user interface and game logic for both automatic and play modes.
 * It manages dictionary loading, word path finding, and game state.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs the main window
     * @param parent The parent widget
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~MainWindow();

private slots:
    // Automatic Mode
    /**
     * @brief Handles the load dictionary button click in automatic mode
     */
    void on_loadDictButton_auto_clicked();

    /**
     * @brief Handles the find path button click in automatic mode
     */
    void on_findPathButton_auto_clicked();

    /**
     * @brief Handles word length spinbox value changes in automatic mode
     * @param arg1 The new word length value
     */
    void on_wordLengthSpinBox_auto_valueChanged(int arg1);

    // Play Mode
    /**
     * @brief Handles the start game button click in play mode
     */
    void on_startGameButton_play_clicked();

    /**
     * @brief Handles the submit word button click in play mode
     */
    void on_submitWordButton_play_clicked();

    /**
     * @brief Handles the hint button click in play mode
     */
    void on_hintButton_play_clicked();

    /**
     * @brief Handles word length spinbox value changes in play mode
     * @param arg1 The new word length value
     */
    void on_wordLengthSpinBox_play_valueChanged(int arg1);

    // Analytics Mode
    /**
     * @brief Handles the load stats button click in analytics mode
     */
    void on_loadStatsButton_analytics_clicked();

private:
    Ui::MainWindow *ui;
    WordLadderGame game;
    bool dictionaryLoaded; // Flag to track if a dictionary is loaded for current game logic

    // Game state for Play Mode
    QString currentPlayerName_play;
    std::string gameStartWord_play;
    std::string gameTargetWord_play;
    std::vector<std::string> playerMoves_play;
    int hintsUsed_play;
    QDateTime gameStartTime_play;
    int optimalMovesForCurrentGame_play;

    /**
     * @brief Updates the current word display in the UI
     * @param word The word to display
     * @param highlightIndex The index of the letter to highlight (-1 for no highlight)
     */
    void updateCurrentWordDisplay(const std::string& word, int highlightIndex = -1);

    /**
     * @brief Saves the current game results to a CSV file
     */
    void saveGameResults();

    /**
     * @brief Resets the play mode UI elements
     * @param gameOngoing Whether a game is currently in progress
     */
    void resetPlayModeUI(bool gameOngoing);

    /**
     * @brief Loads and builds the dictionary for the specified word length
     * @param length The word length to load
     * @param modePrefix The prefix for status messages
     * @return true if dictionary was loaded successfully, false otherwise
     */
    bool loadAndBuildDictionary(int length, const QString& modePrefix);
};

#endif // MAINWINDOW_H
