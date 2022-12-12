#pragma once

#include <map>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <iostream>

class FlyNetwork {
public:
    FlyNetwork();
    std::vector<std::vector<std::string>>  file_to_V2D(const std::string & filename);
    int time_decypher(std::string strand);
    unsigned getcol(std::string col, const std::string & filename);
    FlyNetwork(const std::string & filename);
    std::map<std::string, std::list<std::pair<std::string, double>>> Get_graph();
    int getIndex(std::vector<std::string> v, std::string k);
    std::string FindMinPath(std::string start, std::string end);
    bool VertexInGraph(const std::string& vertex);
    void AddEdge(std::string& edge, std::string& source, double weight);
    void AddEdge(std::string& edge);
    std::vector<std::string> Get_vertices();
    std::vector<std::vector<std::string>> parse_for_iddfs(const std::string & filename);
    std::string idfs_cost_calculator(const std::string & filename, std::string start, std::string finish, std::string limit);
    void BFS(std::string node);
    struct Flight {
        std::string address;
        std::string airline;
        std::string departure;
        std::string arrival;
        int price;
        bool is_leaf;
        Flight() {
            address = "";
            airline = "";
            departure = "";
            arrival = "";
            price = 0;
            bool is_leaf = false;
        }

        Flight(std::string a, std::string b, std::string c, std::string d, int e, bool f) {
            address = a;
            airline = b; 
            departure = c;
            arrival = d;
            price = e;
            is_leaf = f;
        }
        bool operator<(const FlyNetwork::Flight& other) const {return  (price < other.price);}
        bool operator==(const FlyNetwork::Flight& other) const {
            return (address == other.address) && (airline == other.airline) && (departure == other.departure) && (arrival == arrival) && (price == other.price);
        }
    };
    bool IDS( std::string destination, int depth);
    bool DFS(Flight curr, int depth);
    void tree_maker(const std::string & filename);
    Flight max_cost(std::string dest, const std::string & filename);
    std::map<FlyNetwork::Flight, std::set<FlyNetwork::Flight>> r;
    void print_graph(FlyNetwork graph);
    
    
private:
    double rounder(double value, double precision);
    //data members
    std::map<std::string, std::list<std::pair<std::string, double>>> adjacency;
    std::vector<std::string> vertices;
};

