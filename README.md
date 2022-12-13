GitHub Organization  

*Physical locations of all major files and deliverables*
- Code: https://github.com/simonac2-gif/cs225_Final_Project_Flight_Plans/
- Tests: https://github.com/simonac2-gif/cs225_Final_Project_Flight_Plans/tree/main/final/tests
- Data: https://github.com/simonac2-gif/cs225_Final_Project_Flight_Plans/tree/main/final/data
- Written Report:
- Presentation Video:

*----------------------*

Running Instructions 
- Full instructions on how to build and run our executable.

*Defining Input Data (every method)*
- The default input data is a CSV file that you input within 'main' with command line arguments. 
- This CSV is then inputted into the FLyNetwork constructor and parsed into graph structure.
- For the Dijkstra's algorithm the inputs are a source city and destination city in string format with command line arguments.
- For the IDDS algorithm the inputs are destination city, and budget as an integer value. Executable with command line. 

*Defning Output Location (every method)*
- The location for all outputs is the Terminal.

*Instructions to Install*
1. Open VS code and navigate to the terminal. 
2. To install into the CS225 workspace, run the command: `git clone https://github.com/simonac2-gif/cs225_Final_Project_Flight_Plans.git`.

*Instructions to Build and Run*
You will be using simple command line arguments in Terminal.
1. Using the GitHub link that we provided, you have downloaded our code repository.
2. You will need to run the following in the base directory of our project, which in this case is the 'final' directory. 
   - In order to reach the base directory (the project folder "final"), run the command line `cd cs225_Final_Project_Flight_Plans/final`.
3. Next, run the command line `mkdir build`.
4. Change your directory to this newly created build folder by running `cd build`.
5. Run the commmand line `cmake ..` to finish calibrating the build folder.
6. Finally, run `make` in order to compile 'FlyNetwork'.
7. In order to run executable, there are different command line arguments to run depending on which function to employ:
   - To print the graphy in adjacency list format, simply run `./main` and include in parenthesis  the file path i.e :
      `./main "/workspaces/CS225/release-f22/final/tests/Sample/sample2.csv"` .

   - For finding shortest path between two cities, run `./main` and include in parenthesis file path, source city, and 
   destination city i.e :
      `./main "/workspaces/CS225/release-f22/final/tests/Sample/sample2.csv" "Kolkata" "Cochin"` .

   - For finding whether a destination is reachable within a certain budget, run `./main` and include in parenthesis file path,
   destination city, price and the tag IDDS i.e :
      `./main "/workspaces/CS225/release-f22/final/tests/Sample/sample2.csv" "Banglore" "10000" "IDDS"` .

*Instructions to build and run Test Suite*
The test file is included in the "tests" folder.
1. First, run the command line `make test` in the Terminal.
2. Secondly, run `./test` to check for each test case.

*General Description of the tests created*
- Test 1: Tests the parsing function; requiring that the appropriate edges and weights are correctly distributed.
- Test 2: Also tests the parsing function; requires that the adjacency list is the correct size.
- Test 3: Tests the parsing function to assert that destination nodes are correctly added to the graph structure. 
- Test 4: Tests for the Dijkstra algorithm; from a start node to a destination node, it requires that the minimum cost is accurate.
- Test 5: This test also tests the Dijkstra algorithm; except for a start node to a destination node with connections in between.
- Test 6: Also tests for the the Dijkstra algorithm, accurately outputs for the case of 'no possible path'.
- Test 7: Tests for the IDDS algorithm, which checks whether a flight can be found within a certain price limit (outputs a boolean).


