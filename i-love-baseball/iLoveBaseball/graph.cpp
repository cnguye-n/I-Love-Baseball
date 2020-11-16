#include "graph.h"
#include <cassert>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <vector>
#include <climits>
#include <fstream>
using namespace std;

/*****************************************************************
 *
 *  DEFAULT CONSTRUCTOR Graph(): Class Graph
 *________________________________________________________________
 *  The default constructor for the Graph class initializes an empty
 *  Graph
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *
 *  POST-CONDITIONS
 *     Initialize Graph object
 *****************************************************************/
Graph::Graph()
{
    //PROC - initialize number of vertices to 0
    num_vertices = 0;

    //PROC - initialize vertices to empty strings
    for (int v = 0; v < MAXIMUM; v++)
    {
        vertices[v] = "";
    }

    //PROC - fill adjacency matrix
    for (int row = 0; row < MAXIMUM; row++)
    {
        for (int col = 0; col < MAXIMUM; col++)
        {
            distance[row][col] = INT_MAX;
            if (row == col)
            {
                distance[row][col] = 0;
            }
        }
    }

    // read in stadium names & edges
    read_stadiums();
    read_distances();
}

/*****************************************************************
 *
 *  METHOD add_vertex(): Class Graph
 *________________________________________________________________
 *  The add_vertex function adds a vertex into the graph
 *  give the number of vertices is less than max.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     city (string) - city name
 *     num_vertices is less than MAXIMUM
 *  POST-CONDITIONS
 *     Adds new vertex, or displays error message.
 *****************************************************************/
void Graph::add_vertex(std::string city) // IN - city name
{
    // PROC - add vertex and update vertices number
    assert(num_vertices < MAXIMUM);

    if (search_index(city) == -1)
    {
        vertices[num_vertices] = city;
        num_vertices++;
    }
    // OUT - error message if vertex exists
    else {
        std::cout << "City already exists in graph." << std::endl;
    }
}

/*****************************************************************
 *
 *  METHOD add_edge(): Class Graph
 *________________________________________________________________
 *  The add_edge function adds a vertex into the graph.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     depart (string) - edge origin
 *     arrival (string) - edge destination
 *     dist (int) - edge weight
 *  POST-CONDITIONS
 *     Adds new edge, or displays error message
 *****************************************************************/
void Graph::add_edge(std::string depart,   // IN - edge origin
                     std::string arrival,  // IN - edge destination
                     int dist)             // IN - edge weight
{
    // PROC - find index of cities
    int depart_v = search_index(depart);
    int arrive_v = search_index(arrival);

    // PROC - error message if it can't find the vertices
    //        otherwise add to graph
    if (depart_v == -1 || arrive_v == -1)
    {
        std::cout << "Could not find cities." << std::endl;
        if (depart_v == -1)
            std::cout << depart << std::endl;
        if (arrive_v == -1)
            std::cout << arrival << std::endl;
    }
    else {
        distance[depart_v][arrive_v] = dist;
        distance[arrive_v][depart_v] = dist;
    }
}

/*****************************************************************
 *
 *  METHOD search_index(): Class Graph
 *________________________________________________________________
 *  Returns index of given vertex.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     city (string) - vertex to search
 *  POST-CONDITIONS
 *     Returns int, index of search or -1 if not found
 *****************************************************************/
int Graph::search_index(std::string city) // IN - vertex to search
{
    // PROC - search for vertex
    // OUT  - return index
    for (size_t i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == city)
            return i;
    }

    // OUT - return -1 if can't find
    return -1;
}

/*****************************************************************
 *
 *  METHOD find_distance(): Class Graph
 *________________________________________________________________
 *  Returns distance/edge weight between two vertices
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     node (int) - vertex of departure
 *     connection (int) - vertex of arrival
 *  POST-CONDITIONS
 *     Returns an int, the edge weight or -1 if nodes are out of bounds
 *****************************************************************/
int Graph::find_distance(int node,        // IN - departing vertex
                         int connection)  // IN - arrival vertex
{
    // PROC - check to make sure vertices are within bounds
    // OUT  - return edge weight
    if (node < MAXIMUM && connection < MAXIMUM)
    {
        return distance[node][connection];
    }
    // OUT - return -1 if out of bounds
    else
        return -1;
}

/*****************************************************************
 *
 *  METHOD get_vertex(): Class Graph
 *________________________________________________________________
 *  Returns vertex name given the index
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     index (int) - index of vertex
 *  POST-CONDITIONS
 *     Adds new edge, or displays error message
 *****************************************************************/
std::string Graph::get_vertex(int index) // IN - index of vertex
{
    // PROC - check that index is not out of bounds
    // OUT  - return vertex name
    assert(index < MAXIMUM);
    return vertices[index];
}

/*****************************************************************
 *
 *  METHOD dijkstras(): Class Graph
 *________________________________________________________________
 *  Perform's Dijkstra's algorithm on the graph, displays results
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Displays results of Dijkstra's
 *****************************************************************/
void Graph::dijkstras()
{
    int cost[MAXIMUM];               // Keeps track of cost
    int predecessor[MAXIMUM];        // Keeps track of predecessors

    // EMPTY SET of nodes visited
    std::set <int> visited;

    // PROC - INITIALIZE COST ARRAY with infinite distances
    //        Predecessor array to 0
    for (int i = 0; i < MAXIMUM; i++)
    {
        cost[i] = INT_MAX;
        predecessor[i] = -1;
    }

    // PROC - start with Seattle at 0, cost is 0
    cost[0] = 0;

    // MAIN LOOP
    // PROC - WHILE NOT ALL NODES ARE IN THE VISITED SET
    while (visited.size() < MAXIMUM)
    {
        int min = INT_MAX;
        int index;

        // PROC - find minimum cost node in cost array not in set
        for (int i = 0; i < MAXIMUM; i++)
        {
            if (!visited.count(i) && cost[i] <= min)
            {
                index = i;
                min = cost[i];
            }
        }

        // PROC -  add that node to set of visited nodes
        visited.insert(index);

        // PROC - update costs for nodes adjacent to nodes visited
        //        if new cost is less than old cost
        for (int i = 0; i < MAXIMUM; i++)
        {
            if (!visited.count(i) &&
                    (find_distance(index, i) != INT_MAX) &&
                    (find_distance(index, i) + cost[index] < cost[i]))
            {
                cost[i] = find_distance(index, i) + cost[index];
                predecessor[i] = index;
            }
        }
    }

    // OUT - PRINT OUT ALL DISTANCES
    std::cout << "---Dijkstra's Algorithm (starting from Seattle)---"
              << std::endl;

    // OUT - use stack to print out until stack is empty
    for (int i = 0; i < MAXIMUM; i++)
    {
        std::cout << get_vertex(i) << ": ";
        std::cout << cost[i] << " { Seattle, ";

        int j = i;

        std::stack<std::string> s;

        while (predecessor[j] != -1)
        {
            s.push(get_vertex(j));
            j = predecessor[j];
        }

        while (!s.empty())
        {
            std::cout << s.top() << ", ";
            s.pop();
        }

        std::cout << "}" << std::endl;
    }
}

/*****************************************************************
 *
 *  METHOD prims(): Class Graph
 *________________________________________________________________
 *  Perform's Prim's algorithm on the graph, displays results
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Displays results
 *****************************************************************/
void Graph::prims()
{
    int cost_p[MAXIMUM];    // cost array
    int pre_p[MAXIMUM];     // predecessor array

    // EMPTY SET of nodes visited
    std::set <int> visit_p;

    // PROC - INITIALIZE COST ARRAY with infinite distances
    //        Predecessor array to 0
    for (int i = 0; i < MAXIMUM; i++)
    {
        cost_p[i] = INT_MAX;
        pre_p[i] = -1;
    }

    int smallest_edge, start_index;

    smallest_edge = INT_MAX;
    start_index = 0;

    // PROC - find the smallest edge, use that as starting pt
    for (int i = 0; i < MAXIMUM; i++)
    {
        for (int j = 0; j < MAXIMUM; j++)
        {
            if (find_distance(i,j) != 0 &&
                    find_distance(i,j) < smallest_edge)
            {
                smallest_edge = find_distance(i,j);
                start_index = i;
            }
        }
    }

    // PROC - set starting point cost to 0
    cost_p[start_index] = 0;

    // PROC - use queue to print out results
    std::queue<int> order;

    // MAIN LOOP
    // PROC - WHILE NOT ALL NODES ARE IN THE VISITED SET
    while (visit_p.size() < MAXIMUM)
    {
        int min = INT_MAX;
        int index;

        // PROC - find minimum cost node in cost array not in set
        for (int i = 0; i < MAXIMUM; i++)
        {
            if (!visit_p.count(i) && cost_p[i] <= min
                    && find_distance(pre_p[i], i) != INT_MAX)
            {
                index = i;
                min = cost_p[i];
            }
        }

        // PROC - add that node to set of visited nodes
        visit_p.insert(index);
        // PROC - push order into queue
        order.push(index);

        // PROC - update costs for nodes adjacent to nodes visited
        for (int i = 0; i < MAXIMUM; i++)
        {
            if (find_distance(index, i) != INT_MAX &&
                    !visit_p.count(i) &&
                    (find_distance(index, i) < cost_p[i]))
            {
                cost_p[i] = find_distance(index, i);
                pre_p[i] = index;
            }
        }
    }

    // OUT - PRINT OUT ALL DISTANCES
    std::cout << std::endl;
    std::cout << "---Minimum Spanning Tree (Prim's Algorithm)---"
              << std::endl;

    //PROC - find start point
    int counter = 1;
    order.pop();

    //PROC & OUT - print out from queue + pop until empty
    while(!order.empty())
    {
        std::cout << counter << ": (";
        std::cout << get_vertex(pre_p[order.front()]) << ", "
             << get_vertex(order.front());
        std::cout << ") ";
        std::cout << find_distance(pre_p[order.front()], order.front())
             << std::endl;


        order.pop();
        counter++;
    }
}

/*****************************************************************
 *
 *  METHOD kruskals(): Class Graph
 *________________________________________________________________
 *  Perform's Kruskal's algorithm on the graph, displays results
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Displays results
 *****************************************************************/
void Graph::kruskals()
{
    std::vector<int> tree;       // tree vector
                                 // keeps track of number of edges in tree
    std::vector<int> edges;      // vector of sorted edges
    std::vector<int> copy;       // intermediate container
    bool visited[MAXIMUM];       // array of visited nodes for DFS
    bool matr[MAXIMUM][MAXIMUM]; // adjacency matrix #2
                                 // keeps track of connections in tree

    // PROC - initialize adj matrix 2
    for (int i = 0; i < MAXIMUM; i++)
    {
        for (int j = 0; j < MAXIMUM; j++)
        {
            matr[i][j] = false;
        }
    }

    // PROC - sort edges by weight, insert into copy vector
    for (size_t i = 0; i < MAXIMUM; i++)
    {
        for (size_t j = 0; j < MAXIMUM; j++)
        {
            if (find_distance(i,j) != 0 && find_distance(i,j) != INT_MAX)
            {
                copy.push_back(find_distance(i,j));
            }
        }
    }

    // PROC - sort copy vector (it has duplicates)
    sort(copy.begin(), copy.end());

    int counter = 0;

    // PROC - push single copy into edges vector
    for (std::vector<int>::iterator it = copy.begin() ;
         it != copy.end(); ++it)
    {
        if (counter % 2 == 0)
        {
            edges.push_back(*it);
        }
        counter++;
    }

    // numbers the edges visited
    int bullet = 1;

    // OUT - title
    std::cout << std::endl;
    std::cout << "---Minimum Spanning Tree (Kruskal's Algorithm)---"
              << std::endl;

    // PROC - main loop, for each edge
    for (size_t edg = 0; edg < edges.size(); edg++)
    {
        // PROC - stop when tree has N-1 vertices
        if (tree.size() == num_vertices - 1)
        {
            break;
        }

        // PROC - find the vertices associated with the edge
        int node1, node2;
        node1 = search_node1(edges.at(edg));
        node2 = search_node2(edges.at(edg));

        // PROC - zero out visited node array to pass into DFS
        for (int i = 0; i < MAXIMUM; i++)
        {
            visited[i] = false;
        }

        // PROCESSING - DEPTH FIRST SEARCH TO FIND CYCLES
        if(!is_cycle(matr, visited, node1, node2))
        {
            // PROC - if no cycle, add to adj matrix 2
            matr[node1][node2] = true;
            matr[node2][node1] = true;

            // OUT - print out edge visited
            std::cout << bullet << ". ";
            std::cout << "(" << get_vertex(node1) << ", "
                      << get_vertex(node2) << "): "
                      << edges.at(edg) << std::endl;

            // PROC - add edge to tree
            tree.push_back(edges.at(edg));
            bullet++;
        }


    }
}

/*****************************************************************
 *
 *  METHOD is_cycle(): Class Graph
 *________________________________________________________________
 *  Performs Depth First Search DFS algorithm on graph to determine
 *  if adding a new edge will create a cycle
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     matr (bool) - adjacency matrix 2
 *     visited (bool) - stores visited nodes in DFS
 *     start (int) - starting vertex/node
 *     end (int) - end vertex/node
 *  POST-CONDITIONS
 *     Returns 0 if no cycle, weight of edge if there is a cycle
 *****************************************************************/
int Graph::is_cycle(bool (&matr)[MAXIMUM][MAXIMUM],
                 bool (&visited)[MAXIMUM], int start, int end)
{
    // PROC - initialize weight to 0
    int weight;
    weight = 0;

    // PROC - mark start node as visited
    visited[start] = true;

    // PROC - if there is edge from start to end,
    //        return weight, there's a cycle
    if (matr[start][end])
        return find_distance(start, end);

    // PROC - go through all adjacent nodes
    for (int node = 0; node < MAXIMUM; node++)
    {
        // PROC - if there is edge in tree from start to node
        //        and node hasn't been visited
        //        perform DFS on that node as start node
        if (matr[start][node] && !visited[node])
             weight = is_cycle(matr, visited, node, end);

        // PROC - if weight > 0, return distance
        if (weight)
        {
            return find_distance(start, node);
        }
    }

    // OUT - return weight
    //       0 if no cycle, >0 if there is
    return weight;

}

/*****************************************************************
 *
 *  METHOD search_node1(): Class Graph
 *________________________________________________________________
 *  Returns vertex 1 associated with an edge weight
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     weight (int) - edge weight
 *  POST-CONDITIONS
 *     Returns vertex 1 associated with edge weight,
 *     -1 if not found
 *****************************************************************/
int Graph::search_node1(int weight) // IN - edge weight
{
    // PROC - traverse thru adj matrix to find matching weight
    // OUT  - return vertex 1
    for (int i = 0; i < MAXIMUM; i++)
    {
        for (int j = 0; j < MAXIMUM; j++)
        {
            if (find_distance(i,j) == weight)
            {
                return i;
            }
        }
    }
    // OUT - return -1 if not found
    return -1;
}

/*****************************************************************
 *
 *  METHOD search_node2(): Class Graph
 *________________________________________________________________
 *  Returns vertex 2 associated with an edge weight
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     weight (int) - edge weight
 *  POST-CONDITIONS
 *     Returns vertex 1 associated with edge weight,
 *     -2 if not found
 *****************************************************************/
int Graph::search_node2(int weight) // IN - edge weight
{
    // PROC - traverse thru adj matrix to find matching weight
    // OUT  - return vertex 2
    for (int i = 0; i < MAXIMUM; i++)
    {
        for (int j = 0; j < MAXIMUM; j++)
        {
            if (find_distance(i,j) == weight)
            {
                return j;
            }
        }
    }
    // OUT - return -1 if not found
    return -1;
}

/*****************************************************************
 *
 *  METHOD stadium_distance(): Class Graph
 *________________________________________________________________
 * Finds shortest distance between two stadiums using Dijkstra's algorithm
 * THIS FUNCTION RETURNS THE TOTAL DISTANCE TRAVELED
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     stadium_a (string) - source
 *     stadium_b (string) - destination
 *  POST-CONDITIONS
 *     Finds shortest distance between two stadiums using Dijkstra's algorithm,
 *     returns total distance traveled
 *****************************************************************/
int Graph::stadium_distance(std::string stadium_a, // IN - source
                            std::string stadium_b) // IN - destination
{
    int cost[MAXIMUM];               // Keeps track of cost
    int predecessor[MAXIMUM];        // Keeps track of predecessors

    // EMPTY SET of nodes visited
    std::set <int> visited;

    // PROC - INITIALIZE COST ARRAY with infinite distances
    //        Predecessor array to 0
    for (int i = 0; i < MAXIMUM; i++)
    {
        cost[i] = INT_MAX;
        predecessor[i] = -1;
    }

    // PROC - start with stadium A at 0, cost is 0
    cost[search_index(stadium_a)] = 0;

    // MAIN LOOP
    // PROC - WHILE NOT ALL NODES ARE IN THE VISITED SET
    while (visited.size() < MAXIMUM)
    {
        int min = INT_MAX;
        int index;

        // PROC - find minimum cost node in cost array not in set
        for (int i = 0; i < MAXIMUM; i++)
        {
            if (!visited.count(i) && cost[i] <= min)
            {
                index = i;
                min = cost[i];
            }
        }

        // PROC -  add that node to set of visited nodes
        visited.insert(index);

        // PROC - update costs for nodes adjacent to nodes visited
        //        if new cost is less than old cost
        for (int i = 0; i < MAXIMUM; i++)
        {
            if (!visited.count(i) &&
                    (find_distance(index, i) != INT_MAX) &&
                    (find_distance(index, i) + cost[index] < cost[i]))
            {
                cost[i] = find_distance(index, i) + cost[index];
                predecessor[i] = index;
            }
        }
    }

    //cout << "Start: " << stadium_a << endl;
    //cout << "Distance: " << cost[search_index(stadium_b)] << endl;
    //cout << "End: " << stadium_b << endl;

    return cost[search_index(stadium_b)];
}

/*****************************************************************
 *
 *  METHOD draw_distance(): Class Graph
 *________________________________________________________________
 * RETURNS VECTOR OF STADIUMS TRAVELED WHEN FINDING DISTANCE
 * BETWEEN TWO STADIUMS - shortest path
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     stadium_a (string) - source
 *     stadium_b (string) - destination
 *  POST-CONDITIONS
 *     Finds shortest distance between two stadiums using Dijkstra's algorithm,
 *     returns vector of stadiums traveled in order
 *****************************************************************/
std::vector<std::string> Graph::draw_distance(std::string stadium_a,
                                              // IN - source
                                              std::string stadium_b)
                                              // IN - destination
{
    int cost[MAXIMUM];               // Keeps track of cost
    int predecessor[MAXIMUM];        // Keeps track of predecessors
    vector<string> path;

    // EMPTY SET of nodes visited
    std::set <int> visited;

    // PROC - INITIALIZE COST ARRAY with infinite distances
    //        Predecessor array to -1
    for (int i = 0; i < MAXIMUM; i++)
    {
        cost[i] = INT_MAX;
        predecessor[i] = -1;
    }

    // PROC - start with stadium A at 0, cost is 0
    cost[search_index(stadium_a)] = 0;

    // MAIN LOOP
    // PROC - WHILE NOT ALL NODES ARE IN THE VISITED SET
    while (visited.size() < MAXIMUM)
    {
        int min = INT_MAX;
        int index;

        // PROC - find minimum cost node in cost array not in set
        for (int i = 0; i < MAXIMUM; i++)
        {
            if (!visited.count(i) && cost[i] <= min)
            {
                index = i;
                min = cost[i];
            }
        }

        // PROC -  add that node to set of visited nodes
        visited.insert(index);

        // PROC - update costs for nodes adjacent to nodes visited
        //        if new cost is less than old cost
        for (int i = 0; i < MAXIMUM; i++)
        {
            if (!visited.count(i) &&
                    (find_distance(index, i) != INT_MAX) &&
                    (find_distance(index, i) + cost[index] < cost[i]))
            {
                cost[i] = find_distance(index, i) + cost[index];
                predecessor[i] = index;
            }
        }
    }

    // PROC - use predecessor array to backtrack and find order
    int travel;
    travel = search_index(stadium_b);

    std::stack<std::string> s;
    path.push_back(stadium_a);

    //cout << stadium_a << endl;

    while (predecessor[travel] != -1)
    {
        s.push(get_vertex(travel));
        travel = predecessor[travel];
    }

    while (!s.empty())
    {
        //std::cout << s.top() << " ";
        path.push_back(s.top());
        s.pop();
    }

    // OUT - return vector of stadiums visited in order
    return path;
}

/*****************************************************************
 *
 *  METHOD dream(): Class Graph
 *________________________________________________________________
 * Returns shortest distance path including a set of nodes
 * Only works for up to 8 nodes because of O(n!) complexity
 * otherwise takes a long while to run
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     vector<string> places - vector of nodes
 *  POST-CONDITIONS
 *     Finds shortest distance path that covers a specific set of nodes
 *     Returns distance and updates the path (dreamPath variable)
 *****************************************************************/
int Graph::dream(std::vector<std::string> places) // IN - nodes of interest
{
    vector<string> path, miniPath;
    int min, cost;
    min = INT_MAX;
    dreamPath.clear();

    // sort vector alphabetical order so we can find all permutations
    // using next_permutation
    sort(places.begin(), places.end());

    // PROC - DO FOR EVERY PERMUTATION OF THE VECTOR OF NODES
    do
    {
        // PROC - INSIDE LOOP TO FIND PATH COST OF EACH PERMUTATION
        // clear cost and path every loop
        cost = 0;
        path.clear();

        // PROC - add costs, push into path vector
        for (size_t i = 0; i < places.size() - 1; i++)
        {
            cost += stadium_distance(places[i], places[i+1]);
            miniPath = draw_distance(places[i], places[i+1]);

            for (size_t i = 0; i < miniPath.size()-1; i++)
                path.push_back(miniPath[i]);
        }
        // push final stadium
        path.push_back(miniPath[miniPath.size()-1]);

        // PROC - take shortest path, store into dreamPath variable
        if (cost < min)
        {
            min = cost;
            dreamPath = path;
        }
    } while (std::next_permutation(places.begin(), places.end()));

    // PROC - return shortest path cost
    return min;
}

/*****************************************************************
 *
 *  METHOD major(): Class Graph
 *________________________________________________________________
 * Algorithm returning shortest (or trying to) path containing all
 * nodes/stadiums
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     start (int) - start node
 *  POST-CONDITIONS
 *     Returns shortest (or trying to) path value containing all
 *     nodes/stadiums, updates majorPath variable
 *****************************************************************/
int Graph::major(int start) // IN - starting node
{
    // PROC - check that start city is within nodes
    assert(start < MAXIMUM);

    // clear majorPath vector
    majorPath.clear();

    int totalCost, startIndex; // total cost, starting index
    vector<string> path;       // intermediate path
    set<string> visited;       // visited nodes

    // start at At&T park or whatever passed in
    startIndex = start;
    totalCost = 0;

    // insert into visited nodes
    visited.insert(get_vertex(startIndex));

    // PROC - keep running until all nodes are visited
    while (visited.size() < MAXIMUM)
    {
        int min, newNode;
        min = INT_MAX;

        // PROC - find node not visited that has shortest path from current vertex
        for (int i = 0; i < MAXIMUM; i++)
        {
            if(!visited.count(get_vertex(i))
                    && stadium_distance(get_vertex(startIndex), get_vertex(i)) < min)
            {
                newNode = i;
                min = stadium_distance(get_vertex(startIndex), get_vertex(i));
            }
        }

        // PROC - add to path vector
        path = draw_distance(get_vertex(startIndex), get_vertex(newNode));
        for (size_t i = 0; i < path.size()-1; i++)
        {
            majorPath.push_back(path[i]);
        }

        // PROC - add path to total cost
        totalCost += stadium_distance(get_vertex(startIndex), get_vertex(newNode));

        // PROC - insert into visited nodes
        // set new node as new start node
        visited.insert(get_vertex(startIndex));
        startIndex = newNode;

    }

    // PROC - when while loop done, add last stadium visited
    majorPath.push_back(path[path.size()-1]);

    // OUT - return total cost
    return totalCost;

}

/*****************************************************************
 *
 *  METHOD national(): Class Graph
 *________________________________________________________________
 * Algorithm returning shortest (or trying to) path containing all
 * national nodes/stadiums
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     start (int) - start node
 *  POST-CONDITIONS
 *     Returns shortest (or trying to) path value containing all
 *     national nodes/stadiums, updates nPath variable
 *****************************************************************/
int Graph::national(int start) // IN - starting node
{
    // PROC - check that it's a national stadium index
    assert(start < MAXIMUM && start >= 15);

    // clear previous data
    nPath.clear();

    int totalCost, startIndex; // total trip cost, start node index
    vector<string> path; // intermediate path
    set<string> visited; // set of visited nodes

    // start at At&T park or whatever passed in, has to be national
    startIndex = start;
    totalCost = 0;

    // add first node to visited set
    visited.insert(get_vertex(startIndex));

    // PROC - loop runs until we visit all national nodes
    while (visited.size() < national_teams.size())
    {
        int min, newNode;
        min = INT_MAX;

        // PROC - find node not visited that has shortest path from current vertex
        for (int i = 15; i < MAXIMUM; i++)
        {
            if(!visited.count(get_vertex(i))
                    && stadium_distance(get_vertex(startIndex), get_vertex(i)) < min)
            {
                newNode = i;
                min = stadium_distance(get_vertex(startIndex), get_vertex(i));
            }
        }

        // PROC - add to National vector (nPath)
        path = draw_distance(get_vertex(startIndex), get_vertex(newNode));
        for (size_t i = 0; i < path.size()-1; i++)
        {
            nPath.push_back(path[i]);
        }

        // PROC - add to total cost
        totalCost += stadium_distance(get_vertex(startIndex), get_vertex(newNode));

        // insert into visited nodes
        // set new node as new start node
        visited.insert(get_vertex(startIndex));
        startIndex = newNode;

    }

    // PROC - add last stadium into path
    nPath.push_back(path[path.size()-1]);

    // OUT - return total cost
    return totalCost;
}


/*****************************************************************
 *
 *  METHOD american(): Class Graph
 *________________________________________________________________
 * Algorithm returning shortest (or trying to) path containing all
 * american nodes/stadiums
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     start (int) - start node
 *  POST-CONDITIONS
 *     Returns shortest (or trying to) path value containing all
 *     american nodes/stadiums, updates nPath variable
 *****************************************************************/
int Graph::american(int start) // IN -  start node
{
    // PROC - check start node is a american stadium index
    assert(start < 15);

    // clear path from prev runs
    aPath.clear();

    int totalCost, startIndex; // total cost, start node
    vector<string> path; // intermediate path
    set<string> visited; // set of visited nodes

    // start at Dodger Stadium or whichever passed in, must be american
    startIndex = start;
    totalCost = 0;

    // PROC - insert first stadium into path
    visited.insert(get_vertex(startIndex));

    // PROC - keep looping until all american teams are added in visited
    //        set
    while (visited.size() < american_teams.size())
    {
        int min, newNode;
        min = INT_MAX;

        // PROC- Find node not visited that has shortest path from current vertex
        for (int i = 0; i < american_teams.size(); i++)
        {
            if(!visited.count(get_vertex(i))
                    && stadium_distance(get_vertex(startIndex), get_vertex(i)) < min)
            {
                newNode = i;
                min = stadium_distance(get_vertex(startIndex), get_vertex(i));
            }
        }

        // PROC - add to American vector (aPath)
        path = draw_distance(get_vertex(startIndex), get_vertex(newNode));
        for (size_t i = 0; i < path.size()-1; i++)
        {
            aPath.push_back(path[i]);
        }

        // PROC- add to total cost
        totalCost += stadium_distance(get_vertex(startIndex), get_vertex(newNode));

        // PROC - insert into visited nodes
        visited.insert(get_vertex(startIndex));
        startIndex = newNode;

    }

    // PROC - add last stadium into vector
    aPath.push_back(path[path.size()-1]);

    // OUT - return total cost of american trip
    return totalCost;

}

/*****************************************************************
 *
 *  METHOD read_stadiums(): Class Graph
 *________________________________________________________________
 * Adds vertices into graph
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Adds vertices into graph and vertices into specific vectors
 *****************************************************************/
void Graph::read_stadiums()
{
    std::string stadium_name;
    std::string type;

    // PROC - open txt file for vertices
    std::ifstream reading;
    reading.open("vertices.txt");

    // OUT - error if cant read
    if (!reading)
        std::cout << "Error." << std::endl;

    // PROC - while reading, add vertices and push into vectors
    while (!reading.eof())
    {
        getline(reading, stadium_name);
        getline(reading, type);

        if (type == "1")
            american_teams.push_back(stadium_name);
        else
            national_teams.push_back(stadium_name);

        add_vertex(stadium_name);
    }

    reading.close();
}


/*****************************************************************
 *
 *  METHOD read_distances(): Class Graph
 *________________________________________________________________
 * Adds edges into graph
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Adds edges into graph
 *****************************************************************/
void Graph::read_distances()
{
    std::ifstream read;
    std::string a, b, d;
    int dist;

    // PROC - open file
    read.open("edges.txt");

    // OUT - error if cant read
    if (!read)
        std::cout << "Error." << std::endl;

    // PROC - add edges while reading
    while (!read.eof())
    {
        getline(read, a);
        getline(read, b);
        getline(read, d);

        dist = stoi(d);

        add_edge(a, b, dist);
    }

    // close file
    read.close();
}
