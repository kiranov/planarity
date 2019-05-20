#include <iostream>
#include <vector>
#include <algorithm>
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
		//int v;
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
	//free - понадобиться далее для освобождения памяти: графы и веторы из графов
	void free(){
		for(size_t i = 0; i < size; i++){
			delete []matrix[i];
		}
		cout << "delete" << endl;
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
	//метод ищет цикл, кладет его в стек снимая сверху вершины до первой повторяющейся, найдем цикл
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
	//преобразование стека-цикла в вектор-цикл
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
	//перед первым запуском dfs нужно очистить массив colour после поиска цикла
	//обычный поиск в глубину
	void dfs (int v, vector<int> & comp) {
			colour[v] = 1;
			comp.push_back (v);
			for (size_t i=0; i<size; i++) {
				if(matrix[v][i] == 1){ 
					int to = i;
					if (! colour[to])
						dfs (to, comp);
				}
			}
	}
	//ищет компоненты связности - сегменты 2-го типа(нужно подавать граф без циклов и сегментов 1-го типа)
	vector<Graph> find_comps(vector<int> & comp) {
		vector<Graph> segment2;
		for (size_t i=0; i<size; ++i)
			colour[i] = 0;
		for (size_t i=0; i<size; ++i)
			if (! colour[i]) {
				comp.clear();
				dfs (i, comp);
				cout << "Component:";
				for (size_t j=0; j<comp.size(); ++j)
					cout << ' ' << comp[j];
				if(comp.empty() != 1){
					Graph * A = new Graph(size);
					for(size_t x = 0; x < comp.size(); ++x){
						for(size_t y = 0; y < comp.size(); ++y){
							if(matrix[comp[x]][comp[y]] == 1){
								A->AddEdge(comp[x], comp[y]);
							}
						}
					}
					cout << endl;
					//A->print();
					segment2.push_back(*A);
					//A->~Graph();
					//cout << " SAUL " << endl;
				}
			}
		return segment2;
	}
	//подготовка к поиску сегментов 2-го типа, удяляет цикл из графа и сегменты 1-го типа. Процедура мега-тупая, тройной цикл это ......
	void segment_2(Graph * A, vector<Graph> seg1, vector<int> cycle){
		for(size_t i = 0; i < cycle.size(); i++){
			for(size_t j = 0; j < cycle.size(); j++){
				if(A->matrix[cycle[i]][cycle[j]] == 1){
					A->matrix[cycle[i]][cycle[j]] = 0;
				}
			}
		}
		for(size_t k = 0; k < seg1.size(); k++){
			for(size_t i = 0; i < seg1[k].size; i++){
				for(size_t j = 0; j < seg1[k].size; j++){
					if(seg1[k].matrix[i][j] == 1){
						A->matrix[i][j] = 0;
					}
				}
			}
		}
	}
	//копирование графа в граф B
	void copy(Graph * B){
		for(size_t i = 0; i < size; i++){
			for(size_t j = 0; j < size; j++){
				B->matrix[i][j] = matrix[i][j];
			}
		}
	}  
	/*void find_comps(vector<int> & comp) {
		//vector<Graph> segment2;
		for (size_t i=0; i<size; ++i)
			colour[i] = 0;
		for (size_t i=0; i<size; ++i)
			if (! colour[i]) {
				comp.clear();
				dfs (i, comp);
				cout << "Component:";
				for (size_t j=0; j<comp.size(); ++j)
					cout << ' ' << comp[j];
				Graph A(size);
				for(size_t x = 0; x < comp.size(); ++x){
					for(size_t y = 0; y < comp.size(); ++y){
						if(matrix[comp[x]][comp[y]] ==1){
							A.AddEdge(comp[x], comp[y]);
						}
					}
				}
				cout << endl;
				A.print();
				segment2.push_back(A);
			cout << " SAUL " << endl;
			}
		//return segment2;
	}*/
};


//процедура поиска сегментов 1-го типа, возвращает вектор графов
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

int main(int argc, char **argv){
	Graph A(7);
	A.AddEdge(0, 1);
	A.AddEdge(0, 3);
	A.AddEdge(0, 5);
	//A.AddEdge(0, 2);
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
	A.print();
	stack s(7);
	/*s.push(0);
	s.push(1);
	int a = s.val();
	cout << a << endl;
	a = s.pop();
	cout << a;*/
	A.find_cycle(0,&s);
	vector<int> cycl;
	cycl = A.cycle(&s);
	for(size_t i = 0; i < cycl.size(); i++){
		cout << cycl[i] << " ";
	}
	cout << endl;
	for(size_t i = 0; i < A.size; i++){
		A.colour[i] = 0;
	}
	vector <Graph> segmenti;
	segmenti = segments(A, cycl);
	for (size_t i = 0; i < segmenti.size(); i++){
		segmenti[i].print();
		cout << endl;
	}
	Graph * D = new Graph (A.size);
	A.copy(D);
	cout << "Graph D" << endl;
	D->print();
	A.segment_2(D, segmenti, cycl);
	cout << "Graph without cycle and seg1" << endl;
	D->print();
	vector<int> comp;
	vector<Graph> segment2;
	segment2 = D->find_comps(comp);
	for(size_t i = 0; i < segment2.size(); i++){
		segment2[i].print();
		cout << endl;
	}
	//cout << "finish";
	//C.find_comps(comp);
	return 0;
}

