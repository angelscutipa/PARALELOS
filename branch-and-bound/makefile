all:
	g++ -std=c++17 -O3 branchAndBound4x4.cc -o branchAndBound4x4
	g++ -std=c++17 -O3 branchAndBound10x10.cc -o branchAndBound10x10
	g++ -std=c++17 -O3 branchAndBound20x20.cc -o branchAndBound20x20
	rm branchAndBound4x4.txt
	rm branchAndBound10x10.txt
	rm branchAndBound20x20.txt
	./branchAndBound4x4 >> branchAndBound4x4.txt
	./branchAndBound10x10 >> branchAndBound10x10.txt
	./branchAndBound20x20 >> branchAndBound20x20.txt
	rm branchAndBound4x4
	rm branchAndBound10x10
	rm branchAndBound20x20