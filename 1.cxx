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
		while(current != 0){
			pop();
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
	/*~Graph(){
		for(size_t i = 0; i < size; i++){
			delete []matrix[i];
		}
		delete []matrix;
		delete []colour;
	}*/
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

vector<Graph> segments(Graph G, vector<int> cycle){
	Graph Z(G.size);
	vector<Graph> seg;
	seg.reserve(30);
	for (size_t i = 0; i < 20; i++){
		seg.push_back(Z);
	}
	int count = 0;
	cycle.push_back(cycle.front());
	for(size_t i = 0; i < G.size; i++){
		int index = -1;
		for(size_t j = 0; j < cycle.size(); j++){
			if(cycle[j] == i){
				index = j;
				break;
			}
		}
		if(index >= 0){
			for(size_t j = 0; j < cycle.size() - 1; j++){
				if(G.matrix[i][cycle[j]] == 1){
					if(index == 0) {
						if((cycle[1] != cycle[j]) && (cycle[cycle.size() - 2] != cycle[j])) {
							G.matrix[i][cycle[j]] = 0;
							G.matrix[cycle[j]][i] = 0;
							Graph G_1(G.size);
							G_1.AddEdge(i, cycle[j]);
							seg[count] = G_1;
							count++;
						}
					}
					else {
						if((cycle[index + 1] != cycle[j]) && (cycle[index - 1] != cycle[j])) {
							G.matrix[i][cycle[j]] = 0;
							G.matrix[cycle[j]][i] = 0;
							Graph G_1(G.size);
							G_1.AddEdge(i, cycle[j]);
							seg[count] = G_1;
							count++;
						}
					}
				}
			}
		}
	}
	while(seg.size() > count){
		seg.pop_back();
	}
	return seg;
}

int main(int argc, char **argv)
{
	Graph A(7);
	A.AddEdge(0, 1);
	A.AddEdge(0, 3);
	A.AddEdge(0, 5);
	A.AddEdge(1, 2);
	A.AddEdge(1, 3);
	A.AddEdge(1, 4);
	A.AddEdge(2, 3);
	A.AddEdge(2, 4);
	A.AddEdge(3, 4);
	A.AddEdge(4, 6);
	A.AddEdge(4, 5);
	A.AddEdge(5, 6);
	/*Graph B(3);
	B.AddEdge(0,1);
	B.AddEdge(1, 2);
	B.AddEdge(2, 0);
	
	B.print();
	Graph C(8);
	C.AddEdge(0,1);
	C.AddEdge(0,6);
	C.AddEdge(6,7);
	C.AddEdge(1,2);
	C.AddEdge(2,3);
	C.AddEdge(3,4);
	C.AddEdge(4,5);
	C.AddEdge(5,2);
	*/
	Graph D(6);
	D.AddEdge(0, 1);
	D.AddEdge(1, 2);
	D.AddEdge(2, 3);
	D.AddEdge(3, 4);
	D.AddEdge(4, 5);
	D.AddEdge(5, 0);
	D.AddEdge(2, 5);
	D.AddEdge(1, 5);
	stack s(10);
	/*s.push(0);
	s.push(1);
	int a = s.val();
	cout << a << endl;
	a = s.pop();
	cout << a;*/
	D.find_cycle(0,&s);
	vector<int> cycl;
	cycl = D.cycle(&s);
	for(size_t i = 0; i < cycl.size(); i++){
		cout << cycl[i] << " ";
	}
	printf("\n");
	//vector<Graph> segmenti = segments(A, cycl);
	//printf("%d", segmenti.size());
	vector <Graph> segmenti;
	segmenti = segments(D, cycl);
	for (size_t i = 0; i < segmenti.size(); i++){
		segmenti[i].print();
		printf("\n");
	}
	return 0;
}
