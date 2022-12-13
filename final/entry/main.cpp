
#include "FlyNetwork.h"
#include <iostream>
int main(int argc, char* argv[]) {
    if (argc == 2) {
        FlyNetwork airports(argv[1]);
        std::map<std::string, std::list<std::pair<std::string, double>>> database = airports.Get_graph();
        std::ostream out (NULL);
        airports.print_graph(airports);
    }

    if (argc == 4) {
        FlyNetwork airports(argv[1]);
        std::string result = airports.FindMinPath(argv[2], argv[3]);
        std::cout << result << std::endl;
    }

    if (argc == 5) {
        std::string tag = argv[4];
        if (tag == "IDDS") {
            FlyNetwork testing(argv[1]);
            testing.tree_maker(argv[1]);
            std::string limitstr = argv[3];
            int limit = std::stoi(limitstr);
            auto z = testing.IDS(argv[2], limit);
            if(z) {
                std::cout << "Flights found under $" << limitstr << std::endl;
            } else {
                std::cout << "No Flights found under $" << limitstr << std::endl;
            }
        }
        
    }

    return 0;
}
