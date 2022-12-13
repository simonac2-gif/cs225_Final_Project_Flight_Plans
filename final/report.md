

GOALS SUMMARY:
Our leading premise was to flight data between a mutlitude of airports to generate a recommendable route to a customer using Dijkstra's Algorithm using price and distance as the weights. 
We will use a weighted graph where each node represents an airport and the edges are weighted by price/distance to get price per unit of distance. We also implemented a BFS for 
graph traversal, as well as an iterative deepening-depth first search(IDDS). With an IDDFS Algorithm, we created a feature that would answer a customer's  yes or no question on is a 
particular destination reachable within a given budget x.

DEVELOPMENT AND TESTING: 
In the development phase, we encounted some difficulties in which structures we should use to store our graphs. We eventually settled on a graph holding nodes and its adjacency list in the format of 
std::map<std::string, std::list<std::pair<std::string, double>>>. Whereby the nodes were airports and the edges were destination airports connected by flights. The weights were a unit of price per minute; 
We developed a parsing funciton to distribute the appropriate data in our graph structure. We also created structs to hold other valuable flight information of the respective airports. As aforementioned to 
traverse the graph we employed a BFS algorithm. Given an input data as a CSV file, the outputs we were considering were a visual of the minimum path from one airport to another, as well as the cost in price
per minute. As well as an option to search if flights are available within a certain price point. To achieve this we implemented the Dijkstra's and IDDS respectively. 

To test our function, we created a seperate executable test file, which tested for the accuracy of our parsing algorithm, and tested the correctedness of our outputs. Our test suite included 7 test cases.
The first 3 test cases, ensured adjacency list were the correct sizes, and destination nodes were correctly added to graph structure. The next 2 cases tested the Dijkstra's algorithm given a start node and destination,
it requires that the minimum cost is accurate. It tested for a cases no connections, cases with multiple connections in between, as well a case of no match. 
The last tests were for the IDDS, which ensured the right output is given with an input of a price limit. 


