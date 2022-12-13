#include "FlyNetwork.h"
#include "utils.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>
#include <list>
using namespace std;
FlyNetwork::FlyNetwork() {
    //Empty constructor
}

std::vector<std::vector<std::string>> FlyNetwork::file_to_V2D(const std::string & filename){
    std::vector<std::vector<std::string>> database;
    std::string fname;
    std::vector<std::string> row;
    std::string line, word;
    int counter = 0;
    std::fstream file;
    file.open(filename);

    if(file.is_open())
    {
        while(std::getline(file, line) && (counter != 201))
        {
            counter++;
            row.clear();
            
            std::stringstream str(line);
            while(std::getline(str, word, ','))
            row.push_back(word);
            database.push_back(row);
        }
    }
    else {
        std::cout<<"Could not open the file\n";
    }

    for(unsigned i=0;i<database.size();i++)
    {
    for(unsigned  j=0;j< database[i].size();j++)
    {
        if (isspace(database[i][j].front())) {
            database[i][j].erase(database[i][j].begin());
        }
    }
    }
    return database;

}

FlyNetwork::FlyNetwork(const std::string & filename){
    std::vector<std::vector<std::string>> datasheet = file_to_V2D(filename);
    auto start_col = getcol("Source", filename);
    auto end_col = getcol("Destination", filename);


    auto price_col = getcol("Price", filename);
    auto dur_col = getcol("Duration", filename);

    //adding each flight(edge) to its corresponding starting node
    for (unsigned i = 1; i < datasheet.size(); i++) {

        //price divided by duration, determines if it is really worth the passengers investment
        double net_cost =   ((double)(stoi(datasheet[i][10])) / (double)(time_decypher(datasheet[i][7]))) ;
        double rounded_cost = round(net_cost / .01) * .01;
        std::string source = datasheet[i][2];
        std::string destination = datasheet[i][3];
        AddEdge(destination, source, rounded_cost);
        AddEdge(destination);
    }
    for (auto it = adjacency.begin(); it != adjacency.end(); it++) {
        vertices.push_back(it->first);
    } 
}

unsigned FlyNetwork::getcol(std::string col, const std::string & filename) {
        
    std::vector<std::vector<std::string>> datasheet = file_to_V2D(filename);
    for (unsigned i = 0; i < datasheet.at(0).size(); i++) {
        if (datasheet.at(0).at(i) == col)  {
            return i;


        } 

    }
    return -1;
}

std::vector<std::string> FlyNetwork::Get_vertices() { return vertices;}

void FlyNetwork::AddEdge(std::string& edge, std::string& source, double weight) {
    bool valid = VertexInGraph(source); //Check to see if node is in graph
    
    if(valid) {
        //Add destination to adjacency list 
        std::pair<std::string, double> p;
        p.first = edge;
        p.second = weight;
        auto iter = adjacency.find(source);
        auto item = iter->second.begin();
        if (item->first.empty()) {
            iter->second.erase(iter->second.begin());
        }
        iter->second.push_back(p);
    } else { 
        //Create new entry
        std::pair<std::string, std::list<std::pair<std::string, double>>> p;
        auto p2 = std::make_pair(edge, weight);
        std::list<std::pair<std::string, double>> p3;
        p3.push_back(p2);
        p.first = source;
        p.second = p3;
        adjacency.insert(p);
    }
    
}
void FlyNetwork::AddEdge(std::string& edge) {
    bool valid = VertexInGraph(edge); //Check to see if destination is in graph 
    if (!valid) {
        std::pair<std::string, double> p2;
        std::list<std::pair<std::string, double>> p3;
        p3.push_back(p2);
        adjacency.insert({edge, p3});
    }
}
bool FlyNetwork::VertexInGraph(const std::string& vertex) {
    bool valid = false;
    auto iter = adjacency.find(vertex);
    if (iter != adjacency.end()) {
        valid = true;
    }
    return valid; 
}
int FlyNetwork::time_decypher(std::string strand) {
    int hours = 0;
    int minutes = 0;
    if (strand.length() <= 3) {
        int h = 0;
        hours = stoi(strand.substr(0, h+1));
    }
    if (strand.length() > 3) {
        int h = 0;
        while (strand.at(h+1) != 'h') {
            h++;
        }
        int m = 0;
        while (strand.at(m+1) != 'm') {
            m++;
        }
        hours = stoi(strand.substr(0, h+1));
        minutes = stoi(strand.substr(h + 3, m + 1));
    }
    return 60 * hours + minutes;
}

std::map<std::string, std::list<std::pair<std::string, double>>> FlyNetwork::Get_graph() {
    return adjacency;
}

double FlyNetwork::rounder(double value, double precision) {
    return std::round(value / precision) * precision;
}

int FlyNetwork::getIndex(vector<std::string> v, std::string k) {
    auto it = find(v.begin(), v.end(), k);
    int index = -1;
    if (it != v.end()) {
        index = it - v.begin();
    }
    return index;
}

void FlyNetwork::BFS(std::string node) {

    // Mark all the vertices as not visited
    vector<bool> visited;
    int V = vertices.size();
    visited.resize(V, false);

    int index = getIndex(vertices, node);
 
    // Create a queue for BFS
    list<int> queue;
 
    // Mark the current node as visited and enqueue it
    visited[index] = true;
    queue.push_back(index);
 
    while(!queue.empty())
    {
        // Dequeue a vertex from queue
        index = queue.front();
        queue.pop_front();
 
        //Marking visited Nodes
        auto temp = vertices[index];
        auto temp2 = adjacency.find(temp);

        for (auto adjecent: temp2->second)
        {
            int adj_index = getIndex(vertices, adjecent.first);
            if (!visited[adj_index])
            {
                visited[adj_index] = true;
                queue.push_back(adj_index);
            }
        }
    }
}

std::string FlyNetwork::FindMinPath(std::string start, std::string end) {
    int n = vertices.size();
    std::vector<double> dist(n, 9999.0);
    std::vector<std::vector<std::string>> prev(n);
    std::vector<std::string> paths;
    std::set<std::pair<double, int>> st; 
    int index = getIndex(vertices,start);
    int end_index = getIndex(vertices,end);
    if (start == end) {
        return "Invalid. Start and End points are the same.";
    }
    if (index == -1 || end_index == -1) {
        return "One ore more entries are invalid.";
    }
    //Using set as priority queue
    st.insert(make_pair(0.0, index));
    dist[index] = 0.0;
    while(!st.empty()) {
        std::pair<double, int> now = *st.begin();
        st.erase(st.begin());
        double v = now.first;
        int w = now.second;
        auto temp = vertices[w];
        int temp2 = -1;
        auto iter = adjacency.find(temp);
        auto it = iter->second.begin();
        
        for (it = iter->second.begin(); it != iter->second.end(); it++) {
            temp2 = getIndex(vertices, it->first);
            if (temp2 != -1) {
                //Checking weights of each connected node to derive minimum
                if (v + it->second < dist[temp2]) {
                    st.erase(std::make_pair(dist[temp2], temp2));
                    dist[temp2] = v + it->second;
                    st.insert(std::make_pair(dist[temp2], temp2));
                    prev[temp2].push_back(it->first);
                    std::vector<std::string>::iterator temp_el;
                    temp_el = std::find(paths.begin(), paths.end(), it->first);
                    // Add the node with the smallest weight to the path list
                    if (temp_el == paths.end()) {
                        paths.push_back(it->first);
                    }
                }
            }
        }
    }
    // Printing pathway by appending vector elements to string
    std::string returner;
    std::string price_per = std::to_string(dist[end_index]);
    price_per.erase(price_per.end() - 4, price_per.end());
    returner.append(start);
    int path_index = getIndex(paths, end);

    if (!prev[end_index].empty()) {
        returner += " to " + vertices[end_index] + ", Minimum Cost: $" + price_per + " per minute, Path: " + start;
        for (int i = 0; i < path_index + 1; i++) {
            returner += " -> " + paths[i];
        }
    } else if(prev[end_index].empty())  {
        returner += " to " + vertices[end_index] + ": No possible route."; 
    }
    return returner;
}

std::vector<std::vector<std::string>> FlyNetwork::parse_for_iddfs(const std::string & filename) {
    auto start_col = getcol("Source", filename);
    auto end_col = getcol("Destination", filename);
    auto price_col = getcol("Price", filename);
    auto airline_col = getcol("Airline", filename);
    std::vector<std::vector<std::string>> the_data;
    the_data.resize(file_to_V2D(filename).size());
    for (unsigned i = 0; i < the_data.size(); i++) {
        the_data[i].resize(5);

    }
    the_data[0][0] = "Address";
    the_data[0][1] = "Airline";
    the_data[0][2] = "Source";
    the_data[0][3] = "Destination";
    the_data[0][4] = "Price";
    for (unsigned i = 1; i < the_data.size(); i++) {
        the_data[i][0] = "0xooo" + to_string(i);
        the_data[i][1] = file_to_V2D(filename)[i][getcol("Airline", filename)];
        the_data[i][2] = file_to_V2D(filename)[i][getcol("Source", filename)];
        the_data[i][3] = file_to_V2D(filename)[i][getcol("Destination", filename)];
      
      
        the_data[i][4] = file_to_V2D(filename)[i][getcol("Price", filename)]; 
        
        
      
    }
    return the_data;
}

std::string FlyNetwork::idfs_cost_calculator(const std::string & filename, std::string start, std::string finish, std::string limit) {

    auto flights = parse_for_iddfs(filename);
    return "returning soon...";
}

FlyNetwork::Flight FlyNetwork::max_cost(std::string dest, const std::string & filename) {
    std::vector<std::vector<std::string>> flights = parse_for_iddfs(filename);
    int max_price = 0;
    std::string address = "";
    std::string airline = ""; 
    std::string  departure = "";
    std::string arrival = "";
    bool il = false;

    for (unsigned i = 0; i < flights.size(); i++ ) {
        if (flights[i][3] == dest) {
            if (stoi(flights[i][4]) > max_price) {
                address = flights[i][0];
                airline = flights[i][1];
                departure = flights[i][2];
                arrival = flights[i][3];
                max_price = stoi(flights[i][4]);
                
            }

        }
        
    }
    FlyNetwork::Flight f(address, airline, departure, arrival, max_price, il);
    return f;
}

void FlyNetwork::tree_maker(const std::string & filename) {
    std::map<std::string, bool> touched;
    std::vector<std::vector<std::string>> flights = parse_for_iddfs(filename);
    std::vector<std::string> destinations = Get_vertices();

    for (unsigned i = 0; i < destinations.size(); i++) {
        std::set<FlyNetwork::Flight> s;
        s.clear();
        r.insert(std::make_pair(max_cost(destinations[i], filename), s));
        touched.insert(std::make_pair(max_cost(destinations[i], filename).address, true));
    }
    for (unsigned j = 1; j < flights.size(); j++ ) {
        if (touched.find(flights[j][0]) == touched.end()) {
            FlyNetwork::Flight fl(flights[j][0], flights[j][1], flights[j][2], flights[j][3], std::stoi(flights[j][4]), true);

            for (auto k = r.begin(); k != r.end(); k++) {
                if (flights[j][3] == k->first.arrival) {
                    k->second.insert(fl);
                    touched.insert(std::make_pair(fl.address, true));
                }
            }
        
        }     
    }
}

bool FlyNetwork::DFS(Flight curr, int depth) {
   if (curr.price <= depth) {
    return true;

   }
   if (depth == 0) {
    return false;
   }

    if (curr.is_leaf == true) {
        return false;
    }
    if (r.find(curr)->second.size() != 0) {



    for (auto it = r.find(curr)->second.begin(); it != r.find(curr)->second.end(); it++) {
                    if (DFS(*it, depth)) {
                        return true;
                    }
                }
    }
    return false;

}

bool FlyNetwork::IDS(std::string destination, int depth) {

    for (auto it = r.begin(); it != r.end(); it++) {
         
           if (it->first.arrival == destination) {
            for (int i = 0; i < depth; i++) {
                if (DFS(it->first, i)) {
                    return true;
                }

    }
  
            
        }
    }
      return false;

}

void FlyNetwork::print_graph(FlyNetwork graph) {
    std::map<std::string, std::list<std::pair<std::string, double>>> database = graph.Get_graph();
    std::map<std::string, std::list<std::pair<std::string, double>>>::iterator iter;
    for (iter = database.begin(); iter != database.end(); iter++) {
        std::string tester1;
        double valid;
        std::list<std::pair<std::string, double>>::iterator it2;
        std::cout << "{Node: " << iter->first << " , Edges|Weigth: ";
        for (it2 = iter->second.begin(); it2 != iter->second.end(); it2++) {
            auto temp = it2;
            tester1 = temp->first; 
            valid = temp->second;
            std::cout << "(" << tester1 << "|" << valid << ")";
        }
        std::cout << "}" << std::endl;
        std::cout <<"\n" << std::endl;
    }
}
