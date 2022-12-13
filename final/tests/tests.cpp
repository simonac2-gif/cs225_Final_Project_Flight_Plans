#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include "/workspaces/CS225/release-f22/final/src/FlyNetwork.h"


TEST_CASE("file_to_V2D", "[v2d]")
{
    FlyNetwork testing("../tests/Sample/sample.csv");
    std::map<std::string, std::list<std::pair<std::string, double>>> database = testing.Get_graph();
    auto it = database.find("Kolkata");
    std::string tester1; 
    std::string valid; 
    std::list<std::pair<std::string, double>>::iterator it2;
    for (it2 = it->second.begin(); it2 != it->second.end(); it2++) {
        auto temp = it2;
        tester1 = temp->first; 
        valid = std::to_string(temp->second);
        valid.erase(valid.end() - 4, valid.end());
    }
    std::string tester = "Kolkata";
    REQUIRE(tester1 == "Banglore");
    REQUIRE(valid == "30.99");
}
TEST_CASE("file_to_V2D", "[v2d2]")
{
    FlyNetwork testing("../tests/Sample/sample.csv");
    std::map<std::string, std::list<std::pair<std::string, double>>> database = testing.Get_graph();
    auto it = database.find("New Delhi");
    std::string tester1; 
    double valid; 
    std::list<std::pair<std::string, double>>::iterator it2;
    int count = 0;
    for (it2 = it->second.begin(); it2 != it->second.end(); it2++) {
        auto temp = it2;
        tester1 = temp->first; 
        count++;
    }

    
    std::string tester = "New Delhi";
    REQUIRE(tester1 == "Cochin");
    REQUIRE(count == 7);
}
TEST_CASE("file_to_V2D", "[v2d3]") 
{
    FlyNetwork testing("../tests/Sample/sample.csv");
    std::map<std::string, std::list<std::pair<std::string, double>>> database = testing.Get_graph();
    std::string node = "Cochin";
    bool correct = testing.VertexInGraph(node);
    REQUIRE(correct == true);
}

TEST_CASE("Shortest Path: Correct", "[Dijkstra1]") 
{
    FlyNetwork testing("../tests/Sample/sample.csv");
    std::map<std::string, std::list<std::pair<std::string, double>>> database = testing.Get_graph();
    auto vertices = testing.Get_vertices();
    std::vector<double> dist;
    std::vector<std::string> prev;
    std::string start = "Kolkata";
    std::string end = "Banglore";
    std::string correct = "Kolkata to Banglore, Minimum Cost: $13.24 per minute, Path: Kolkata -> Banglore";
    std::string user = testing.FindMinPath(start, end);
    REQUIRE(user == correct);
}

TEST_CASE("Shortest Path: Multiple Path", "[Dijkstra2]") 
{
    FlyNetwork testing("../tests/Sample/sample.csv");
    std::map<std::string, std::list<std::pair<std::string, double>>> database = testing.Get_graph();
    auto vertices = testing.Get_vertices();
    std::vector<double> dist;
    std::vector<std::string> prev;
    std::string start = "Kolkata";
    std::string end = "New Delhi";
    std::string correct = "Kolkata to New Delhi, Minimum Cost: $20.49 per minute, Path: Kolkata -> Banglore -> New Delhi";
    std::string user = testing.FindMinPath(start, end);
    REQUIRE(user == correct);
}

TEST_CASE("Shortest Path: No Path", "[Dijkstra3]") 
{
    FlyNetwork testing("../tests/Sample/sample.csv");
    std::map<std::string, std::list<std::pair<std::string, double>>> database = testing.Get_graph();
    auto vertices = testing.Get_vertices();
    std::vector<double> dist;
    std::vector<std::string> prev;
    std::string start = "Kolkata";
    std::string end = "Chennai";
    std::string correct = "Kolkata to Chennai: No possible route.";
    std::string user = testing.FindMinPath(start, end);
    REQUIRE(user == correct);
}

TEST_CASE("IDS", "[ids1") {
    FlyNetwork testing("../tests/Sample/sample2.csv");
    testing.tree_maker("../tests/Sample/sample2.csv");
    auto z = testing.IDS("Banglore", 10000);
    auto zy = testing.IDS("New Delhi", 3000);
    REQUIRE(z == true);
    REQUIRE(zy == false);
}

