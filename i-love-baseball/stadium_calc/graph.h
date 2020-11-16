#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>


class Graph
{
private:
    /**********************
    ** PRIVATE VARIABLES **
    **********************/
    static const int MAXIMUM = 30;              // IN - maximum vertices
    int distance[MAXIMUM][MAXIMUM];             // IN - adjacency matrix
    std::string vertices[MAXIMUM];              // IN - vertex names
    std::size_t num_vertices;                   // IN - number of vertices
public:
    /*****************
    ** CONSTRUCTOR **
    *****************/
    Graph();

    /*****************
    **   MUTATORS  **
    *****************/
    void add_vertex(std::string city);
    void add_edge(std::string depart, std::string arrival, int dist);

    /*****************
    **   ACCESSORS  **
    *****************/
    int search_index(std::string city);
    int find_distance(int node, int connection);
    std::string get_vertex(int index);
    void dijkstras();
    void prims();
    void kruskals();
    int stadium_distance(std::string stadium_a, std::string stadium_b);
    std::vector<std::string> draw_distance(std::string stadium_a, std::string stadium_b);
    int shortest_path(std::vector<std::string> places);
    int is_cycle(bool (&connect)[MAXIMUM][MAXIMUM],
                 bool (&visited)[MAXIMUM],
                 int begin, int end);
    int search_node1(int weight);
    int search_node2(int weight);
    void read_stadiums();
    void read_distances();
    std::vector<std::string> national_teams;    // IN - vec of national teams
    std::vector<std::string> american_teams;    // IN - vec of american teams
};

#endif // GRAPH_H

/*****************************************************************
 *
 * GRAPH CLASS
 * _______________________________________________________________
 * The Graph class creates a basic graph with an adjacency matrix.
 * It manages the private attributes MAXIMUM, distance, vertices and
 * num_vertices.
 ******************************************************************/

/******************************
 **      CONSTRUCTOR       **
******************************/

/**************************************************************
* Graph();
*   Constructor; Initialize empty graph
*   Parameters: none
*   Return: none
***************************************************************/

/*******************
 **   MUTATORS    **
 *******************/

/****************************************************************
* void add_vertex(std::string city);
*   Mutator; The add_vertex function adds a vertex into the graph
*            give the number of vertices is less than max.
*   Parameters: city (string)
*   Return: none
***************************************************************/

/****************************************************************
* void add_edge(std::string depart, std::string arrival, int dist);
*   Mutator; The add_edge function adds a vertex into the graph.
*   Parameters: depart (string), arrival (string), dist (int)
*   Return: none
***************************************************************/

/*******************
 **   ACCESSORS   **
 *******************/

/**************************************************************
* int search_index(std::string city);
*   Accessor; returns index of given vertex
*   Parameters: city (string)
*   Return: int
***************************************************************/

/**************************************************************
* int find_distance(int node, int connection);
*   Accessor; returns distance between two vertices
*   Parameters: node (int), connection (int)
*   Return: int
***************************************************************/

/**************************************************************
* std::string get_vertex(int index);
*   Accessor; returns vertex name given the index
*   Parameters: index (int)
*   Return: string
***************************************************************/

/**************************************************************
* void dijkstras();
*   Accessor; performs dijkstra's algorithm on the graph,
*             displays results
*   Parameters: none
*   Return: none
***************************************************************/

/**************************************************************
* void prims();
*   Accessor; performs prim's algorithm on the graph,
*             displays results
*   Parameters: none
*   Return: none
***************************************************************/

/**************************************************************
* void kruskals();
*   Accessor; performs kruskal's algorithm on the graph,
*             displays results
*   Parameters: none
*   Return: none
***************************************************************/

/**************************************************************
* int is_cycle(bool (&connect)[MAXIMUM][MAXIMUM],
                 bool (&visited)[MAXIMUM],
                 int begin, int end);
*   Accessor; performs depth first search algorithm on graph,
*             returns 0 if no cycle, returns weight of edge if
*             there is a cycle
*   Parameters: connect(bool), visited(bool), begin(int), end(int)
*   Return: int
***************************************************************/

/**************************************************************
* int search_node1(int weight);
*   Accessor; returns vertex 1 associated with an edge weight
*   Parameters: weight (int)
*   Return: int
***************************************************************/

/**************************************************************
* int search_node2(int weight);
*   Accessor; returns vertex 2 associated with an edge weight
*   Parameters: weight (int)
*   Return: int
***************************************************************/
