#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include <string>
#include <set> // For getNodes if ensuring unique nodes in return list is desired or for alternative adjList

/**
 * @class Graph
 * @brief A template class representing a graph
 * 
 * This class implements a graph data structure using an adjacency list representation.
 * It is designed to be efficient for graph traversal algorithms like BFS.
 * 
 * @tparam T The type of the nodes in the graph
 */
template <typename T>
class Graph {
private:
    std::map<T, std::vector<T>> adjList; ///< Adjacency list representation of the graph

public:
    /**
     * @brief Default constructor
     */
    Graph() = default;

    /**
     * @brief Adds a node to the graph
     * @param node The node to add
     * 
     * If the node already exists, this function does nothing.
     * Otherwise, it creates a new empty adjacency list for the node.
     */
    void addNode(const T& node) {
        // Add node only if it doesn't exist, ensuring adjList[node] is valid
        if (adjList.find(node) == adjList.end()) {
            adjList[node] = std::vector<T>();
        }
    }

    /**
     * @brief Adds an edge between two nodes
     * @param u The first node
     * @param v The second node
     * @param undirected Whether the edge should be undirected (default: true)
     * 
     * If undirected is true, adds edges in both directions.
     * If the nodes don't exist, they are created first.
     * Duplicate edges are not added.
     */
    void addEdge(const T& u, const T& v, bool undirected = true) {
        addNode(u); // Ensure u exists
        addNode(v); // Ensure v exists

        // Add edge u -> v
        // Check for duplicates before adding if necessary, though typically BFS handles visited nodes
        bool found = false;
        for(const T& neighbor : adjList[u]){
            if(neighbor == v){
                found = true;
                break;
            }
        }
        if(!found) {
            adjList[u].push_back(v);
        }

        if (undirected) {
            // Add edge v -> u
            found = false;
            for(const T& neighbor : adjList[v]){
                if(neighbor == u){
                    found = true;
                    break;
                }
            }
            if(!found){
                adjList[v].push_back(u);
            }
        }
    }

    /**
     * @brief Checks if a node exists in the graph
     * @param node The node to check
     * @return true if the node exists, false otherwise
     */
    bool hasNode(const T& node) const {
        return adjList.count(node);
    }

    /**
     * @brief Gets the neighbors of a node
     * @param node The node to get neighbors for
     * @return A const reference to the vector of neighbors
     * 
     * Returns an empty vector if the node doesn't exist.
     */
    const std::vector<T>& getNeighbors(const T& node) const {
        static const std::vector<T> empty_neighbors; // To return for non-existent nodes
        auto it = adjList.find(node);
        if (it != adjList.end()) {
            return it->second;
        }
        return empty_neighbors;
    }

    /**
     * @brief Gets all nodes in the graph
     * @return A vector containing all nodes
     */
    std::vector<T> getNodes() const {
        std::vector<T> nodes;
        for (const auto& pair : adjList) {
            nodes.push_back(pair.first);
        }
        return nodes;
    }

    /**
     * @brief Clears the graph
     * 
     * Removes all nodes and edges from the graph.
     */
    void clear() {
        adjList.clear();
    }
};

#endif // GRAPH_H
