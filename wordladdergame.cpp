#include "wordladdergame.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

/**
 * @brief Constructs a new Word Ladder Game instance
 * 
 * Initializes the random number generator with a time-based seed.
 */
WordLadderGame::WordLadderGame() {
    // Initialize random number generator with time-based seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    randomEngine.seed(seed);
}

/**
 * @brief Loads a dictionary from a file
 * @param filename The path to the dictionary file
 * @return true if dictionary was loaded successfully, false otherwise
 * 
 * Reads words from the specified file and stores them in the dictionary.
 * All words are converted to lowercase for consistency.
 */
bool WordLadderGame::loadDictionary(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    dictionary.clear();
    std::string word;
    while (std::getline(file, word)) {
        // Convert to lowercase
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        dictionary.push_back(word);
    }

    // Sort and remove duplicates
    std::sort(dictionary.begin(), dictionary.end()); // Sorts the dictionary in alphabetical order
    dictionary.erase(std::unique(dictionary.begin(), dictionary.end()), dictionary.end()); // Removes duplicate words

    // Set word length based on first word (assuming all words have same length)
    if (!dictionary.empty()) {
        currentWordLength = dictionary[0].length();
    }

    return true;
}

/**
 * @brief Builds the word graph from the loaded dictionary
 * 
 * Creates edges between words that differ by exactly one letter.
 * The graph is built by comparing each word with every other word
 * in the dictionary.
 */
void WordLadderGame::buildGraph() {
    wordGraph.clear(); // Clears the graph before building a new one

    // Add all words as vertices
    for (const auto& word : dictionary) {
        wordGraph.addNode(word);
    }

    // Add edges between words that differ by one letter
    for (size_t i = 0; i < dictionary.size(); ++i) {
        for (size_t j = i + 1; j < dictionary.size(); ++j) {
            if (areWordsOneLetterApart(dictionary[i], dictionary[j])) {
                wordGraph.addEdge(dictionary[i], dictionary[j]);
            }
        }
    }
}

/**
 * @brief Finds the shortest path between two words
 * @param startWord The starting word
 * @param endWord The target word
 * @return A vector containing the words in the shortest path, or empty if no path exists
 * 
 * Uses breadth-first search to find the shortest path between the start and end words.
 * Returns an empty vector if either word is not in the dictionary or if no path exists.
 */
std::vector<std::string> WordLadderGame::findShortestPath(const std::string& startWord, const std::string& endWord) {
    if (!isValidWord(startWord) || !isValidWord(endWord)) {
        return {};
    }

    std::queue<std::string> queue; // Queue to store the words to be visited
    std::map<std::string, std::string> parent; // Maps each word to its parent in the shortest path
    std::set<std::string> visited; // Set to store visited words

    queue.push(startWord); // Adds the starting word to the queue
    visited.insert(startWord); // Adds the starting word to the visited set

    while (!queue.empty()) {
        std::string current = queue.front(); // Gets the first word in the queue
        queue.pop(); // Removes the first word from the queue

        if (current == endWord) {
            // Reconstruct path
            std::vector<std::string> path; // Vector to store the path
            std::string word = endWord; // Sets the end word as the current word    
            while (word != startWord) { // Reconstructs the path by backtracking from the end word to the start word
                path.push_back(word); // Adds the current word to the path
                word = parent[word]; // Sets the parent of the current word as the next word in the path
            }
            path.push_back(startWord); // Adds the starting word to the path
            std::reverse(path.begin(), path.end()); // Reverses the path to get the correct order
            return path; // Returns the path
        }

        for (const auto& neighbor : wordGraph.getNeighbors(current)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor); // Adds the neighbor to the visited set
                parent[neighbor] = current; // Sets the parent of the neighbor as the current word
                queue.push(neighbor); // Adds the neighbor to the queue
            }
        }
    }

    return {}; // No path found
}

/**
 * @brief Checks if a word is valid (exists in the dictionary)
 * @param word The word to check
 * @return true if the word is valid, false otherwise
 * 
 * Performs a binary search on the sorted dictionary to check if the word exists.
 */
bool WordLadderGame::isValidWord(const std::string& word) const {
    return std::binary_search(dictionary.begin(), dictionary.end(), word);
}

/**
 * @brief Checks if two words differ by exactly one letter
 * @param word1 The first word
 * @param word2 The second word
 * @return true if words differ by exactly one letter, false otherwise
 * 
 * Assumes both words are of the same length. Returns false if words
 * have different lengths.
 */
bool WordLadderGame::areWordsOneLetterApart(const std::string& word1, const std::string& word2) const {
    if (word1.length() != word2.length()) {
        return false;
    }

    int differences = 0;
    for (size_t i = 0; i < word1.length(); ++i) {
        if (word1[i] != word2[i]) {
            ++differences;
            if (differences > 1) {
                return false;
            }
        }
    }
    return differences == 1;
}

/**
 * @brief Gets a random word from the dictionary
 * @return A random word from the dictionary, or empty string if dictionary is empty
 * 
 * Uses the random number generator to select a random word from the dictionary.
 */
std::string WordLadderGame::getRandomWord() const {
    if (dictionary.empty()) {
        return "";
    }

    std::uniform_int_distribution<size_t> dist(0, dictionary.size() - 1);
    return dictionary[dist(randomEngine)];
}

/**
 * @brief Gets the current dictionary
 * @return A const reference to the vector of words in the dictionary
 */
const std::vector<std::string>& WordLadderGame::getDictionary() const {
    return dictionary;
}

/**
 * @brief Gets the current word length
 * @return The length of words in the current dictionary
 */
int WordLadderGame::getWordLength() const {
    return currentWordLength;
}
