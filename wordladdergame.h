#ifndef WORDLADDERGAME_H
#define WORDLADDERGAME_H

#include "graph.h"
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <fstream>
#include <algorithm> // For std::shuffle, std::remove
#include <random>    // For std::mt19937, std::uniform_int_distribution

/**
 * @class WordLadderGame
 * @brief Core game logic class for the Word Ladder Game
 * 
 * This class handles the dictionary management, graph building, and path finding
 * functionality for the word ladder game.
 */
class WordLadderGame {
public:
    /**
     * @brief Constructs a new Word Ladder Game instance
     */
    WordLadderGame();

    /**
     * @brief Loads a dictionary from a file
     * @param filename The path to the dictionary file
     * @return true if dictionary was loaded successfully, false otherwise
     */
    bool loadDictionary(const std::string& filename);

    /**
     * @brief Builds the word graph from the loaded dictionary
     * 
     * Creates edges between words that differ by exactly one letter.
     */
    void buildGraph();

    /**
     * @brief Finds the shortest path between two words
     * @param startWord The starting word
     * @param endWord The target word
     * @return A vector containing the words in the shortest path, or empty if no path exists
     */
    std::vector<std::string> findShortestPath(const std::string& startWord, const std::string& endWord);

    /**
     * @brief Checks if a word is valid (exists in the dictionary)
     * @param word The word to check
     * @return true if the word is valid, false otherwise
     */
    bool isValidWord(const std::string& word) const;

    /**
     * @brief Checks if two words differ by exactly one letter
     * @param word1 The first word
     * @param word2 The second word
     * @return true if words differ by exactly one letter, false otherwise
     */
    bool areWordsOneLetterApart(const std::string& word1, const std::string& word2) const;

    /**
     * @brief Gets a random word from the dictionary
     * @return A random word from the dictionary, or empty string if dictionary is empty
     */
    std::string getRandomWord() const;

    /**
     * @brief Gets the current dictionary
     * @return A const reference to the vector of words in the dictionary
     */
    const std::vector<std::string>& getDictionary() const;

    /**
     * @brief Gets the current word length
     * @return The length of words in the current dictionary
     */
    int getWordLength() const;

private:
    Graph<std::string> wordGraph;        ///< Graph representation of word connections
    std::vector<std::string> dictionary; ///< List of valid words
    int currentWordLength;               ///< Length of words in current dictionary
    mutable std::mt19937 randomEngine;   ///< Random number generator for word selection
};

#endif // WORDLADDERGAME_H
