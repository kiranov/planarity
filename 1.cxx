#include <iostream>
#include <vector>
using namespace std;

class stack {
public:
	int current;
	int size;
	int * arr;
public:
	stack(int size){
		this->size = size;
		arr = new int [size];
		for(int i = 0; i < size; i++){
			arr[i] = -1;
		}
		current = 0;
	}
	~stack(){
		delete []arr;
	}
	void push(int v){
		arr[current] = v;
		current++;
	}
	int pop(){
		int ret = arr[current-1];
		current--;
		return ret;
	}
	void del(){
		int v;
		while(current != 0){
			v = pop();
		}
	}
	int val(){
		return arr[current-1];
	}
};

class Graph {
public:
	size_t size;
	int** matrix;
	int * colour;
	int flag = 0;
public:
	//Graph(){}
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
		colour = new int [size];
		for(size_t i = 0; i < size; i++){
			colour[i] = 0;
		}
		//colour[0] = 1;
		/*for(size_t i = 0; i < size; i++){
			matrix[i][i] = 1;
		}*/
		//stack s(size);
	}
	~Graph(){
		for(size_t i = 0; i < size; i++){
			delete []matrix[i];
		}
		delete []matrix;
		delete []colour;
	}
	void print(){
		for(size_t i = 0; i < size; i++){
			for(size_t j = 0; j < size; j++){
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	
	void AddEdge(size_t from, size_t to){
			matrix[from][to] = 1;
			matrix[to][from] = matrix[from][to];
	}
	void find_cycle(size_t v, stack * s){
		//cout << "vertex: " << v << endl;
		size_t previous = s->val();
		colour[v] = 1;
		//cout << v << endl;
		s->push(v);
		size_t i = 0;
		for(i = 0; i < size; i++){
			if(i != previous){
				if(this->matrix[v][i] == 1){
					if(colour[i] == 0){
						//cout << "go to: " << i << endl; 
						find_cycle(i, s);
					}
					if(flag == 1){
						break;
					}
					if((colour[i] == 1) && (i != v)){
						s->push(i);
						//cout << i << endl;
						flag++;
						break;
					}
				}
			}
		}
		colour[v] = 2;
		if(flag == 0){
			s->pop();
		}
	}
	vector<int> cycle(stack * s){
		vector<int> cycl;
		int n = s->pop();
		//cout << n << " ";
		cycl.push_back(n);
		int t;
		while((t = s->pop()) != n){
			cycl.push_back(t);
		}
		return cycl;
	}
};

int main(int argc, char **argv)
{
	/*Graph A(7);
	A.AddEdge(0, 1);
	A.AddEdge(0, 3);
	A.AddEdge(0, 5);
	A.AddEdge(0, 2);
	A.AddEdge(1, 2);
	A.AddEdge(1, 3);
	A.AddEdge(1, 4);
	A.AddEdge(2, 3);
	A.AddEdge(2, 4);
	A.AddEdge(3, 4);
	A.AddEdge(4, 6);
	A.AddEdge(4, 5);
	A.AddEdge(5, 6);
	Graph B(3);
	B.AddEdge(0,1);
	B.AddEdge(1, 2);
	B.AddEdge(2, 0);
	
	B.print();*/
	Graph C(8);
	C.AddEdge(0,1);
	C.AddEdge(0,6);
	C.AddEdge(6,7);
	C.AddEdge(1,2);
	C.AddEdge(2,3);
	C.AddEdge(3,4);
	C.AddEdge(4,5);
	C.AddEdge(5,2);
	
	stack s(8);
	/*s.push(0);
	s.push(1);
	int a = s.val();
	cout << a << endl;
	a = s.pop();
	cout << a;*/
	C.find_cycle(0,&s);
	vector<int> cycl;
	cycl = C.cycle(&s);
	for(size_t i = 0; i < cycl.size(); i++){
		cout << cycl[i] << " ";
	}
	return 0;
}

