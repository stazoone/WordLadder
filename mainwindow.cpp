#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog> // Optional: for choosing dictionary file/dir
#include <set>         // For analytics unique words
#include <QStandardPaths> // To find a writable location
#include <QRegularExpression>
#include <QDir>
#include <QCoreApplication>
#include <QFileInfo>

/**
 * @brief Converts a std::string to QString
 * @param s The string to convert
 * @return The converted QString
 */
QString s2q(const std::string& s) { return QString::fromStdString(s); }

/**
 * @brief Converts a QString to std::string
 * @param qs The string to convert
 * @return The converted std::string
 */
std::string q2s(const QString& qs) { return qs.toStdString(); }

/**
 * @brief Constructs the main window
 * @param parent The parent widget
 * 
 * Initializes the UI and sets up initial states for all game modes.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dictionaryLoaded(false)
    , hintsUsed_play(0)
    , optimalMovesForCurrentGame_play(0)
{
    ui->setupUi(this);
    this->setWindowTitle("Word Ladder Game");

    // Initial UI states
    ui->findPathButton_auto->setEnabled(false);
    resetPlayModeUI(false); // Initially, no game is active in play mode

    // Default word length (can be adjusted)
    ui->wordLengthSpinBox_auto->setValue(4);
    ui->wordLengthSpinBox_play->setValue(4);
}

/**
 * @brief Destructor
 * 
 * Cleans up the UI resources.
 */
MainWindow::~MainWindow() {
    delete ui;
}

/**
 * @brief Loads and builds the dictionary for the specified word length
 * @param length The word length to load
 * @param statusLabelContext The context prefix for status messages
 * @return true if dictionary was loaded successfully, false otherwise
 * 
 * Attempts to load a dictionary file named "dict_[length].txt" from the application directory.
 * If successful, builds the word graph for path finding.
 */
bool MainWindow::loadAndBuildDictionary(int length, const QString& statusLabelContext) {
    QString dictFilename = QString("dict_%1.txt").arg(length);
    
    // Get the application's directory
    QString appDir = QCoreApplication::applicationDirPath();
    QString dictPath = QDir(appDir).absoluteFilePath(dictFilename);

    ui->statusLabel_auto->setText(statusLabelContext + "Loading dictionary " + dictFilename + "...");
    QApplication::processEvents(); // Allow UI to update

    // Try to open the file first to check for read access
    QFile file(dictPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString errorMsg = QString("Failed to open dictionary file: %1\nPath: %2\nError: %3")
            .arg(dictFilename)
            .arg(dictPath)
            .arg(file.errorString());
        ui->statusLabel_auto->setText(statusLabelContext + errorMsg);
        QMessageBox::warning(this, "Dictionary Error", 
            "Could not open dictionary file.\n\n" + errorMsg + 
            "\n\nPlease ensure:\n"
            "1. The file exists in the application directory\n"
            "2. The file is readable\n"
            "3. The file contains words of the specified length");
        dictionaryLoaded = false;
        return false;
    }
    file.close();

    if (game.loadDictionary(q2s(dictPath))) {
        ui->statusLabel_auto->setText(statusLabelContext + "Dictionary loaded. Building graph...");
        QApplication::processEvents();
        game.buildGraph();
        ui->statusLabel_auto->setText(statusLabelContext + "Dictionary and graph ready for " + QString::number(length) + "-letter words.");
        dictionaryLoaded = true;
        return true;
    } else {
        QString errorMsg = QString("Failed to load dictionary: %1\nPath: %2").arg(dictFilename).arg(dictPath);
        ui->statusLabel_auto->setText(statusLabelContext + errorMsg);
        QMessageBox::warning(this, "Dictionary Error", 
            "Could not process dictionary file.\n\n" + errorMsg + 
            "\n\nPlease ensure:\n"
            "1. The file exists in the application directory\n"
            "2. The file is readable\n"
            "3. The file contains words of the specified length");
        dictionaryLoaded = false;
        return false;
    }
}

/**
 * @brief Handles word length spinbox value changes in automatic mode
 * @param length The new word length value
 * 
 * Disables the find path button and requires dictionary reload when word length changes.
 */
void MainWindow::on_wordLengthSpinBox_auto_valueChanged(int length) {
    // Automatically try to load dictionary when length changes
    // Or, require user to click "Load Dictionary"
    // For now, let's use a separate load button to avoid repeated loading during spin
    ui->findPathButton_auto->setEnabled(false); // Require reload if length changes
    ui->statusLabel_auto->setText("Word length changed. Click 'Load Dictionary'.");
    dictionaryLoaded = false;
}

/**
 * @brief Handles the load dictionary button click in automatic mode
 * 
 * Attempts to load the dictionary for the current word length and enables
 * the find path button if successful.
 */
void MainWindow::on_loadDictButton_auto_clicked() {
    int length = ui->wordLengthSpinBox_auto->value();
    if (loadAndBuildDictionary(length, "[Auto Mode] ")) {
        ui->findPathButton_auto->setEnabled(true);
    } else {
        ui->findPathButton_auto->setEnabled(false);
    }
}

/**
 * @brief Handles the find path button click in automatic mode
 * 
 * Attempts to find a path between the start and target words using the loaded dictionary.
 * Displays the path in the UI if found.
 */
void MainWindow::on_findPathButton_auto_clicked() {
    if (!dictionaryLoaded) {
        QMessageBox::information(this, "No Dictionary", "Please load a dictionary first.");
        return;
    }
    if (game.getWordLength() != ui->wordLengthSpinBox_auto->value()){
        QMessageBox::information(this, "Dictionary Mismatch", "Loaded dictionary is for a different word length. Please re-load.");
        ui->findPathButton_auto->setEnabled(false);
        return;
    }

    std::string startWord = q2s(ui->startWordLineEdit_auto->text().toLower());
    std::string targetWord = q2s(ui->targetWordLineEdit_auto->text().toLower());

    if (startWord.length() != game.getWordLength() || targetWord.length() != game.getWordLength()) {
        QMessageBox::warning(this, "Word Length Mismatch", QString("Words must be %1 letters long.").arg(game.getWordLength()));
        return;
    }

    if (!game.isValidWord(startWord) || !game.isValidWord(targetWord)) {
        QMessageBox::warning(this, "Invalid Word", "Start or target word not in the loaded dictionary.");
        return;
    }

    ui->pathListWidget_auto->clear();
    std::vector<std::string> path = game.findShortestPath(startWord, targetWord);

    if (path.empty()) {
        ui->pathListWidget_auto->addItem("No path found.");
    } else {
        for (const std::string& word : path) {
            ui->pathListWidget_auto->addItem(s2q(word));
        }
    }
}

/**
 * @brief Handles the start game button click in play mode
 * 
 * Validates player name and word length, then starts a new game with
 * randomly selected start and target words.
 */
void MainWindow::on_startGameButton_play_clicked() {
    currentPlayerName_play = ui->playerNameLineEdit_play->text().trimmed();
    if (currentPlayerName_play.isEmpty()) {
        QMessageBox::warning(this, "Player Name", "Please enter your name.");
        return;
    }
    // Sanitize player name for filename
    currentPlayerName_play.remove(QRegularExpression(QStringLiteral("[^a-zA-Z0-9_]")));
    if (currentPlayerName_play.isEmpty()) {
        QMessageBox::warning(this, "Player Name", "Player name invalid after sanitization. Use letters, numbers, or underscore.");
        return;
    }

    int length = ui->wordLengthSpinBox_play->value();
    if (!dictionaryLoaded || game.getWordLength() != length) { // Load/reload if needed
        if (!loadAndBuildDictionary(length, "[Play Mode] ")) {
            resetPlayModeUI(false);
            return;
        }
    }

    const int MAX_ATTEMPTS = 100;  // Prevent infinite loops
    int attempts = 0;
    bool foundValidPair = false;

    while (!foundValidPair && attempts < MAX_ATTEMPTS) {
        gameStartWord_play = game.getRandomWord();
        gameTargetWord_play = game.getRandomWord();

        // Make sure words are different
        if (gameStartWord_play == gameTargetWord_play) {
            attempts++;
            continue;
        }

        // Check if there's a valid path between the words
        std::vector<std::string> path = game.findShortestPath(gameStartWord_play, gameTargetWord_play);
        if (!path.empty()) {
            foundValidPair = true;
            optimalMovesForCurrentGame_play = path.size() - 1;
        }
        attempts++;
    }

    if (!foundValidPair) {
        QMessageBox::critical(this, "Game Error", 
            "Could not find a valid word pair with a possible path.\n"
            "The dictionary might be too small or disconnected.\n"
            "Try a different word length.");
        resetPlayModeUI(false);
        return;
    }

    playerMoves_play.clear();
    playerMoves_play.push_back(gameStartWord_play);
    hintsUsed_play = 0;
    gameStartTime_play = QDateTime::currentDateTime();

    ui->startWordLabel_play->setText(s2q("Start: " + gameStartWord_play));
    ui->targetWordLabel_play->setText(s2q("Target: " + gameTargetWord_play));
    updateCurrentWordDisplay(gameStartWord_play);
    ui->playerPathListWidget_play->clear();
    ui->playerPathListWidget_play->addItem(s2q(gameStartWord_play));
    ui->movesLabel_play->setText("Moves: 0");
    ui->hintsUsedLabel_play->setText("Hints: 0");
    ui->gameStatusLabel_play->setText("Game started! Good luck.");

    resetPlayModeUI(true); // Enable game controls
}

/**
 * @brief Resets the play mode UI elements
 * @param gameOngoing Whether a game is currently in progress
 * 
 * Updates the enabled state of UI elements based on whether a game is in progress.
 * Also resets display values if no game is ongoing.
 */
void MainWindow::resetPlayModeUI(bool gameOngoing) {
    ui->playerNameLineEdit_play->setEnabled(!gameOngoing);
    ui->wordLengthSpinBox_play->setEnabled(!gameOngoing);
    ui->startGameButton_play->setEnabled(!gameOngoing);

    ui->nextWordLineEdit_play->setEnabled(gameOngoing);
    ui->submitWordButton_play->setEnabled(gameOngoing);
    ui->hintButton_play->setEnabled(gameOngoing);

    if (!gameOngoing) {
        ui->startWordLabel_play->setText("Start: -");
        ui->targetWordLabel_play->setText("Target: -");
        updateCurrentWordDisplay("-");
        ui->playerPathListWidget_play->clear();
        ui->movesLabel_play->setText("Moves: -");
        ui->hintsUsedLabel_play->setText("Hints: -");
        ui->gameStatusLabel_play->setText("Select word length and player name, then start game.");
        ui->nextWordLineEdit_play->clear();
    }
}

/**
 * @brief Handles the submit word button click in play mode
 * 
 * Validates the player's submitted word and updates the game state if valid.
 * Checks for win condition and saves game results if the game is complete.
 */
void MainWindow::on_submitWordButton_play_clicked() {
    std::string currentWord = playerMoves_play.back();
    std::string nextWord_s = q2s(ui->nextWordLineEdit_play->text().toLower());

    if (nextWord_s.length() != game.getWordLength()) {
        ui->gameStatusLabel_play->setText(QString("Invalid word length. Must be %1 letters.").arg(game.getWordLength()));
        return;
    }

    if (!game.areWordsOneLetterApart(currentWord, nextWord_s)) {
        ui->gameStatusLabel_play->setText("Invalid move: Words must differ by exactly one letter.");
        return;
    }

    if (!game.isValidWord(nextWord_s)) {
        ui->gameStatusLabel_play->setText("Invalid move: '" + s2q(nextWord_s) + "' is not in the dictionary.");
        return;
    }

    playerMoves_play.push_back(nextWord_s);
    ui->playerPathListWidget_play->addItem(s2q(nextWord_s));
    ui->movesLabel_play->setText(QString("Moves: %1").arg(playerMoves_play.size() - 1));
    updateCurrentWordDisplay(nextWord_s);
    ui->nextWordLineEdit_play->clear();
    ui->gameStatusLabel_play->setText("Good move!");


    if (nextWord_s == gameTargetWord_play) {
        ui->gameStatusLabel_play->setText(QString("Congratulations! You reached the target word '%1' in %2 moves.")
                                              .arg(s2q(gameTargetWord_play)).arg(playerMoves_play.size() - 1));
        saveGameResults();
        resetPlayModeUI(false);
    }
}

/**
 * @brief Handles the hint button click in play mode
 * 
 * Provides a hint by showing the next word in the optimal path.
 * Increments the hints used counter.
 */
void MainWindow::on_hintButton_play_clicked() {
    if (playerMoves_play.empty()) return;
    std::string currentWord = playerMoves_play.back();
    if (currentWord == gameTargetWord_play) {
        ui->gameStatusLabel_play->setText("You are already at the target word!");
        return;
    }

    hintsUsed_play++;
    ui->hintsUsedLabel_play->setText(QString("Hints: %1").arg(hintsUsed_play));

    std::vector<std::string> optimalPath = game.findShortestPath(currentWord, gameTargetWord_play);

    if (optimalPath.size() < 2) { // Path is just currentWord or empty
        ui->gameStatusLabel_play->setText("Hint: No further path found or already at target.");
        updateCurrentWordDisplay(currentWord); // No specific letter to highlight
        return;
    }

    std::string optimalNextWord = optimalPath[1];
    int diffIndex = -1;
    for (int i = 0; i < game.getWordLength(); ++i) {
        if (currentWord[i] != optimalNextWord[i]) {
            diffIndex = i;
            break;
        }
    }

    if (diffIndex != -1) {
        updateCurrentWordDisplay(currentWord, diffIndex);
        ui->gameStatusLabel_play->setText(QString("Hint: Try changing the letter '%1' (to '%2').")
                                              .arg(currentWord[diffIndex])
                                              .arg(optimalNextWord[diffIndex]));
    } else {
        // Should not happen if optimalNextWord is different and one letter apart
        updateCurrentWordDisplay(currentWord);
        ui->gameStatusLabel_play->setText("Hint: Could not determine specific letter to change.");
    }
}

/**
 * @brief Updates the current word display in the UI
 * @param word The word to display
 * @param highlightIndex The index of the letter to highlight (-1 for no highlight)
 * 
 * Updates the current word label and optionally highlights a specific letter.
 */
void MainWindow::updateCurrentWordDisplay(const std::string& word, int highlightIndex) {
    if (word == "-") {
        ui->currentWordLabel_play->setText("Current: -");
        return;
    }
    if (highlightIndex < 0 || highlightIndex >= static_cast<int>(word.length())) {
        ui->currentWordLabel_play->setText("Current: " + s2q(word));
    } else {
        QString richText = "Current: ";
        for (int i = 0; i < static_cast<int>(word.length()); ++i) {
            if (i == highlightIndex) {
                richText += "<font color='red'><b>" + QString(word[i]) + "</b></font>";
            } else {
                richText += QString(word[i]);
            }
        }
        ui->currentWordLabel_play->setText(richText);
    }
}

/**
 * @brief Saves the current game results to a CSV file
 * 
 * Saves game statistics including start word, target word, number of moves,
 * optimal moves, hints used, and the complete path taken by the player.
 */
void MainWindow::saveGameResults() {
    if (currentPlayerName_play.isEmpty()) return;

    QString filename = currentPlayerName_play + ".csv";
    // For bundled apps, use QStandardPaths to find a writable location
    // QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    // QFile file(dataPath + "/" + filename);
    // For simplicity now, current directory:
    QFile file(filename);

    bool fileExists = file.exists();
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Save Error", "Could not open file to save game data: " + filename);
        return;
    }

    QTextStream out(&file);
    if (!fileExists) { // Add header if file is new
        out << "DateTime,StartWord,TargetWord,UserMovesCount,OptimalMoves,HintsUsed,UserPath\n";
    }

    QStringList userPathList;
    for(const std::string& move : playerMoves_play) {
        userPathList.append(s2q(move));
    }

    out << gameStartTime_play.toString(Qt::ISODate) << ", Starting word: "
        << s2q(gameStartWord_play) << ", Target word: "
        << s2q(gameTargetWord_play) << ", Moves used: "
        << playerMoves_play.size() - 1 << ", Optimal Moves: "
        << optimalMovesForCurrentGame_play << ", Hints used: "
        << hintsUsed_play << ","
        << "\"" << userPathList.join(" -> ") << "\"\n"; // Enclose path in quotes if it contains commas

    file.close();
    ui->gameStatusLabel_play->setText(ui->gameStatusLabel_play->text() + " Game data saved.");
}

/**
 * @brief Handles word length spinbox value changes in play mode
 * @param length The new word length value
 * 
 * Disables game controls and requires dictionary reload when word length changes.
 */
void MainWindow::on_wordLengthSpinBox_play_valueChanged(int arg1) {
    // Similar to auto mode, changing length should ideally reload dictionary
    // For simplicity, we'll enforce "Start Game" to handle dictionary loading
    resetPlayModeUI(false); // Reset UI if length changes before starting
    ui->gameStatusLabel_play->setText("Word length selected. Click 'Start Game'.");
    dictionaryLoaded = false; // Force reload on new game start
}

/**
 * @brief Handles the load stats button click in analytics mode
 * 
 * Loads and displays game statistics for the specified player.
 */
void MainWindow::on_loadStatsButton_analytics_clicked() {
    QString playerName = ui->playerNameLineEdit_analytics->text().trimmed();
    if (playerName.isEmpty()) {
        QMessageBox::warning(this, "Player Name", "Please enter a player name to load stats.");
        return;
    }
    playerName.remove(QRegularExpression(QStringLiteral("[^a-zA-Z0-9_]")));


    QString filename = playerName + ".csv";
    QFile file(filename);

    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->statsTextEdit_analytics->setText("No data found for player: " + playerName);
        QMessageBox::information(this, "No Data", "No data file found or cannot read file for player: " + playerName);
        return;
    }

    QTextStream in(&file);
    QString allStatsContent = "Game History for " + playerName + ":\n\n";
    std::set<std::string> uniqueWordsUsed; // Justification: std::set for automatic uniqueness of words.

    int gamesPlayed = 0;
    int totalUserMoves = 0;
    int totalOptimalMoves = 0;
    int totalHints = 0;

    QString headerLine = in.readLine(); // Skip header
    allStatsContent += headerLine + "\n-------------------------------------\n";


    while (!in.atEnd()) {
        QString line = in.readLine();
        allStatsContent += line + "\n";
        QStringList fields = line.split(','); // Simple CSV parsing, assumes no commas in quoted fields for now

        if (fields.size() >= 7) { // DateTime,Start,Target,UserMoves,OptimalMoves,Hints,Path
            gamesPlayed++;
            totalUserMoves += fields[3].toInt();
            totalOptimalMoves += fields[4].toInt();
            totalHints += fields[5].toInt();

            // Parse user path for unique words
            // Assuming path is fields[6] and looks like "\"WORD1 -> WORD2 -> WORD3\""
            QString pathField = fields[6];
            pathField.remove('\"'); // Remove quotes
            QStringList pathWords = pathField.split(" -> ");
            for (const QString& word : pathWords) {
                if (!word.trimmed().isEmpty()) {
                    uniqueWordsUsed.insert(q2s(word.trimmed().toLower()));
                }
            }
        }
    }
    file.close();

    QString summary = QString("\n--- Summary for %1 ---\n").arg(playerName);
    summary += QString("Total Games Played: %1\n").arg(gamesPlayed);
    summary += QString("Total Moves Made by User: %1\n").arg(totalUserMoves);
    summary += QString("Total Optimal Moves Possible: %1\n").arg(totalOptimalMoves);
    summary += QString("Total Hints Used: %1\n").arg(totalHints);
    if (gamesPlayed > 0) {
        summary += QString("Average Moves per Game: %1\n").arg(static_cast<double>(totalUserMoves) / gamesPlayed, 0, 'f', 2);
        summary += QString("Average Hints per Game: %1\n").arg(static_cast<double>(totalHints) / gamesPlayed, 0, 'f', 2);
    }
    summary += QString("Unique Words Encountered by User: %1\n").arg(uniqueWordsUsed.size());


    ui->statsTextEdit_analytics->setText(summary + "\n\n--- Full Game Log ---\n" + allStatsContent);
}
