# First, build orbitTools libraries.
# Read "../orbitTools/how_to_build.txt".

# type below command to set library files here.
cp ../orbitTools/lib* .

# type below command to build and link execute file.
g++ -c query_parser.cpp main.cpp
g++ -o main main.o query_parser.o liborbit.a libcore.a
rm *.o

# execute program.
./main

