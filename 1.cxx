#include <iostream>
using namespace std;

class Graph {
public:
	size_t size;
	int** matrix;
public:
	Graph(){}
    Graph(size_t n_vertex){
		size = n_vertex;
		matrix = new int* [size];
		for(size_t i = 0; i < size; i++){
			matrix[i] = new int [size];
		}
		for(size_t i = 0; i < size; i++){
			for(size_t j = 0; j <= i; j++){
				matrix[i][j] = 0;
				matrix[j][i] = matrix[i][j];
			}
		}
		for(size_t i = 0; i < size; i++){
			matrix[i][i] = 1;
		}
	}

	void print(){
		for(size_t i = 0; i < size; i++){
			for(size_t j = 0; j < size; j++){
				cout << matrix[i][j] << ", ";
			}
			cout << endl;
		}
	}
	
    void AddEdge(size_t from, size_t to){
			matrix[from][to] = 1;
			matrix[to][from] = matrix[from][to];
	};
	
};

int main(int argc, char **argv)
{
	Graph A(7);
	A.AddEdge(1, 2);
	A.AddEdge(1, 4);
	A.AddEdge(1, 6);
	A.AddEdge(2, 3);
	A.AddEdge(2, 4);
	A.AddEdge(2, 5);
	A.AddEdge(3, 4);
	A.AddEdge(3, 5);
	A.AddEdge(4, 5);
	A.AddEdge(5, 7);
	A.AddEdge(5, 6);
	A.AddEdge(6, 7);
	A.print();
	return 0;
}

