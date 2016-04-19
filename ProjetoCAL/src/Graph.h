/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <utility>
#include <boost/heap/fibonacci_heap.hpp>


using namespace std;



template <class T, class V> class Edge;
template <class T, class V> class Graph;
template <class T, class V> class Vertex;


const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;




template <class T, class V>
struct compareVertex {
	bool operator()(const Vertex<T, V>* v1, const Vertex<T, V>* v2) const {
		return v1->getDist() > v2->getDist();
	}
};


template <class T, class V>
using fibHeap = boost::heap::fibonacci_heap< Vertex<T,V>*, boost::heap::compare< compareVertex<T, V> > >;


/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template <class T, class V>
class Vertex {
	T info;
	vector<Edge<T,V>  > adj;
	bool visited;
	bool processing;
	int indegree;
	int dist;
public:

	Vertex(T in);
	friend class Graph<T,V>;

	void addEdge(Vertex<T,V> *dest, const V &info, double w);
	bool removeEdgeTo(Vertex<T,V> *d);

	T getInfo() const;
	void setInfo(T info);

	int getDist() const;
	int getIndegree() const;

	Vertex* path;
	V path_info;
	typename fibHeap<T,V>::handle_type handle;
};


template <class T, class V>
struct vertex_greater_than {
	bool operator()(Vertex<T,V> * a, Vertex<T,V> * b) const {
		return a->getDist() > b->getDist();
	}
};


template <class T, class V>
struct vertex_less_than {
	bool operator()(Vertex<T,V> * a, Vertex<T,V> * b) const {
		return a->getDist() < b->getDist();
	}
};


template <class T, class V>
bool Vertex<T,V>::removeEdgeTo(Vertex<T,V> *d) {
	d->indegree--;
	typename vector<Edge<T,V> >::iterator it= adj.begin();
	typename vector<Edge<T,V> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}


template <class T, class V>
Vertex<T,V>::Vertex(T in): info(in), visited(false), processing(false), indegree(0), dist(0) {
	path = NULL;
}


template <class T, class V>
void Vertex<T,V>::addEdge(Vertex<T,V> *dest, const V &info, double w) {
	Edge<T,V> edgeD(dest, info, w);
	adj.push_back(edgeD);
}


template <class T, class V>
T Vertex<T,V>::getInfo() const {
	return this->info;
}

template <class T, class V>
int Vertex<T,V>::getDist() const {
	return this->dist;
}


template <class T, class V>
void Vertex<T,V>::setInfo(T info) {
	this->info = info;
}

template <class T, class V>
int Vertex<T,V>::getIndegree() const {
	return this->indegree;
}




/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template <class T, class V>
class Edge {
	Vertex<T,V> * dest;
	V info;
	double weight;
public:
	Edge(Vertex<T,V> *d, V in, double w);
	friend class Graph<T,V>;
	friend class Vertex<T,V>;
};

template <class T, class V>
Edge<T,V>::Edge(Vertex<T,V> *d, V in, double w): dest(d), info(in), weight(w){}





/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T, class V>
class Graph {
	vector<Vertex<T,V> *> vertexSet;
	void dfs(Vertex<T,V> *v, vector<T> &res) const;

	vector < vector <int> > W;
	vector < vector <T> > P;

	//exercicio 5
	int numCycles;
	void dfsVisit(Vertex<T,V> *v);
	void dfsVisit();
	void getPathTo(Vertex<T,V> *origin, list<T> &res);
	int edgeCost(int i, int j);

public:
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, const V &info, double w);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T,V> *v) const;
	int maxNewChildren(Vertex<T,V> *v, T &inf) const;
	vector<Vertex<T,V> * > getVertexSet() const;
	int getNumVertex() const;

	//exercicio 5
	Vertex<T,V>* getVertex(const T &v) const;
	void resetIndegrees();
	vector<Vertex<T,V>*> getSources() const;
	int getNumCycles();
	vector<T> topologicalOrder();
	pair<vector<T>, vector<V>> getPath(const T &origin, const T &dest);
	void unweightedShortestPath(const T &v);
	bool isDAG();
	void bellmanFordShortestPath(const T &s);
	void dijkstraShortestPath(const T &s);
	bool dijkstraShortestPath(const T &s, const T &d);
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);
	void myDijkstraShortestPath(const T &s);
};


template <class T, class V>
int Graph<T,V>::getNumVertex() const {
	return vertexSet.size();
}
template <class T, class V>
vector<Vertex<T,V> * > Graph<T,V>::getVertexSet() const {
	return vertexSet;
}

template <class T, class V>
int Graph<T,V>::getNumCycles() {
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}

template <class T, class V>
bool Graph<T,V>::isDAG() {
	return (getNumCycles() == 0);
}

template <class T, class V>
bool Graph<T,V>::addVertex(const T &in) {
	typename vector<Vertex<T,V>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T,V>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;
	Vertex<T,V> *v1 = new Vertex<T,V>(in);
	vertexSet.push_back(v1);
	return true;
}

template <class T, class V>
bool Graph<T,V>::removeVertex(const T &in) {
	typename vector<Vertex<T,V>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T,V>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex<T,V> * v= *it;
			vertexSet.erase(it);
			typename vector<Vertex<T,V>*>::iterator it1= vertexSet.begin();
			typename vector<Vertex<T,V>*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}

			typename vector<Edge<T,V> >::iterator itAdj= v->adj.begin();
			typename vector<Edge<T,V> >::iterator itAdje= v->adj.end();
			for (; itAdj!=itAdje; itAdj++) {
				itAdj->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}

template <class T, class V>
bool Graph<T,V>::addEdge(const T &sourc, const T &dest, const V &info, double w) {
	typename vector<Vertex<T,V>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T,V>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T,V> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vD->indegree++;
	vS->addEdge(vD, info, w);

	return true;
}

template <class T, class V>
bool Graph<T,V>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T,V>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T,V>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T,V> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	if (found!=2)
		return false;

	vD->indegree--;

	return vS->removeEdgeTo(vD);
}




template <class T, class V>
vector<T> Graph<T,V>::dfs() const {
	typename vector<Vertex<T,V>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T,V>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<T> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
		if ( (*it)->visited==false )
			dfs(*it,res);
	return res;
}

template <class T, class V>
void Graph<T,V>::dfs(Vertex<T,V> *v,vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T,V> >::iterator it= (v->adj).begin();
	typename vector<Edge<T,V> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
		if ( it->dest->visited == false ){
			dfs(it->dest, res);
		}
}

template <class T, class V>
vector<T> Graph<T,V>::bfs(Vertex<T,V> *v) const {
	vector<T> res;
	queue<Vertex<T,V> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T,V> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T,V> >::iterator it=v1->adj.begin();
		typename vector<Edge<T,V> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T,V> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}

template <class T, class V>
int Graph<T,V>::maxNewChildren(Vertex<T,V> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T,V> *> q;
	queue<int> level;
	int maxChildren=0;
	inf =v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T,V> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l=level.front();
		level.pop(); l++;
		int nChildren=0;
		typename vector<Edge<T,V> >::iterator it=v1->adj.begin();
		typename vector<Edge<T,V> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T,V> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren=nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}


template <class T, class V>
Vertex<T,V>* Graph<T,V>::getVertex(const T &v) const {
	for(unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v) return vertexSet[i];
	return NULL;
}

template <class T, class V>
void Graph<T,V>::resetIndegrees() {
	//colocar todos os indegree em 0;
	for(unsigned int i = 0; i < vertexSet.size(); i++) vertexSet[i]->indegree = 0;

	//actualizar os indegree
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		//percorrer o vector de Edges, e actualizar indegree
		for(unsigned int j = 0; j < vertexSet[i]->adj.size(); j++) {
			vertexSet[i]->adj[j].dest->indegree++;
		}
	}
}


template <class T, class V>
vector<Vertex<T,V>*> Graph<T,V>::getSources() const {
	vector< Vertex<T,V>* > buffer;
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		if( vertexSet[i]->indegree == 0 ) buffer.push_back( vertexSet[i] );
	}
	return buffer;
}


template <class T, class V>
void Graph<T,V>::dfsVisit() {
	typename vector<Vertex<T,V>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T,V>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	it=vertexSet.begin();
	for (; it !=ite; it++)
		if ( (*it)->visited==false )
			dfsVisit(*it);
}

template <class T, class V>
void Graph<T,V>::dfsVisit(Vertex<T,V> *v) {
	v->processing = true;
	v->visited = true;
	typename vector<Edge<T,V> >::iterator it= (v->adj).begin();
	typename vector<Edge<T,V> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++) {
		if ( it->dest->processing == true) numCycles++;
		if ( it->dest->visited == false ){
			dfsVisit(it->dest);
		}
	}
	v->processing = false;
}

template <class T, class V>
vector<T> Graph<T,V>::topologicalOrder() {
	//vector com o resultado da ordenacao
	vector<T> res;

	//verificar se é um DAG
	if( getNumCycles() > 0 ) {
		cout << "Ordenacao Impossivel!" << endl;
		return res;
	}

	//garantir que os "indegree" estao inicializados corretamente
	this->resetIndegrees();

	queue<Vertex<T,V>*> q;

	vector<Vertex<T,V>*> sources = getSources();
	while( !sources.empty() ) {
		q.push( sources.back() );
		sources.pop_back();
	}

	//processar fontes
	while( !q.empty() ) {
		Vertex<T,V>* v = q.front();
		q.pop();

		res.push_back(v->info);

		for(unsigned int i = 0; i < v->adj.size(); i++) {
			v->adj[i].dest->indegree--;
			if( v->adj[i].dest->indegree == 0) q.push( v->adj[i].dest );
		}
	}

	//testar se o procedimento foi bem sucedido
	if ( res.size() != vertexSet.size() ) {
		while( !res.empty() ) res.pop_back();
	}

	//garantir que os "indegree" ficam atualizados ao final
	this->resetIndegrees();

	return res;
}



template <class T, class V>
pair<vector<T>, vector<V>> Graph<T,V>::getPath(const T &origin, const T &dest){

	list<T> buffer_vertex;
	list<V> buffer_path;

	Vertex<T,V>* v = getVertex(dest);

	buffer_vertex.push_front(v->info);
	buffer_path.push_front(v->path_info);

	while ( v->path != NULL &&  v->path->info != origin) {
		v = v->path;
		buffer_vertex.push_front(v->info);
		buffer_path.push_front(v->path_info);
	}
	if( v->path != NULL ) {
		buffer_vertex.push_front(v->path->info);
	}



	vector<T> node_info;
	vector<V> path_info;

	while( !buffer_vertex.empty() ) {
		node_info.push_back( buffer_vertex.front() );
		buffer_vertex.pop_front();
	}

	while ( !buffer_path.empty() ) {
		path_info.push_back( buffer_path.front() );
		buffer_path.pop_front();
	}

	return make_pair(node_info, path_info);
}


template <class T, class V>
void Graph<T,V>::unweightedShortestPath(const T &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T,V>* v = getVertex(s);
	v->dist = 0;
	queue< Vertex<T,V>* > q;
	q.push(v);

	while( !q.empty() ) {
		v = q.front(); q.pop();
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T,V>* w = v->adj[i].dest;
			if( w->dist == INT_INFINITY ) {
				w->dist = v->dist + 1;
				w->path = v;
				q.push(w);
			}
		}
	}
}




template <class T, class V>
void Graph<T,V>::bellmanFordShortestPath(const T &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T,V>* v = getVertex(s);
	v->dist = 0;
	queue< Vertex<T,V>* > q;
	q.push(v);

	while( !q.empty() ) {
		v = q.front(); q.pop();
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T,V>* w = v->adj[i].dest;
			if( v->dist + v->adj[i].weight < w->dist ) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				q.push(w);
			}
		}
	}
}




template <class T, class V>
void Graph<T,V>::dijkstraShortestPath(const T &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
		vertexSet[i]->visited = false;
	}


	vector< Vertex<T,V>* > pq (vertexSet.begin(), vertexSet.end());
	Vertex<T,V> *v = getVertex(s);
	v->dist = 0;
	pq.push_back(v);

	while (! pq.empty()) {

		v = pq[pq.size() - 1]; pq.pop_back();
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T,V> *w = v->adj[i].dest;
			if (v->dist + v->adj[i].weight < w->dist) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				w->path_info = v->adj[i].info;

				if (! w->visited) {
					w->visited = true;
					pq.push_back(w);
				}
			}

			make_heap(pq.begin(), pq.end(), vertex_less_than<T,V>());
		}
	}
}





template <class T, class V>
bool Graph<T,V>::dijkstraShortestPath(const T &s, const T &d) {


	bool found_destination = false;


	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
		vertexSet[i]->visited = false;
	}


	vector< Vertex<T,V>* > pq;
	Vertex<T,V> *v = getVertex(s);
	v->dist = 0;
	pq.push_back(v);

	while (! pq.empty()) {

		v = pq[pq.size() - 1]; pq.pop_back();
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T,V> *w = v->adj[i].dest;

			if (v->dist + v->adj[i].weight < w->dist) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				w->path_info = v->adj[i].info;

				if (! w->visited) {
					if (w->info == d)
						found_destination = true;

					w->visited = true;
					pq.push_back(w);
				}
			}

			make_heap(pq.begin(), pq.end(), vertex_less_than<T,V>());
		}
	}


	return found_destination;
}




template <class T, class V>
void Graph<T,V>::myDijkstraShortestPath(const T &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
		vertexSet[i]->visited = false;
	}


	fibHeap<T,V> fh;

	Vertex<T,V> *v = getVertex(s);
	v->dist = 0;
	fh.push(v);

	while (! fh.empty()) {

		v = fh.top(); fh.pop();
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T,V> *w = v->adj[i].dest;
			if (v->dist + v->adj[i].weight < w->dist) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				w->path_info = v->adj[i].info;

				if (! w->visited) {
					w->visited = true;
					w->handle = fh.push(w);
				}
				else
					fh.decrease(w->handle);
			}
		}
	}
}


template <class T, class V>
int Graph<T,V>::edgeCost(int i, int j) {

	if (i == j)
		return 0;

	Vertex<T,V> *v = vertexSet[i];
	for(unsigned int k = 0; k < v->adj.size(); k++) {
		if (v->adj[k].dest == vertexSet[j])
			return v->adj[k].weight;
	}

	return INT_INFINITY;
}


template <class T, class V>
void Graph<T,V>::floydWarshallShortestPath() {

	unsigned numVerts = vertexSet.size();
	vector < vector<int> > W(numVerts, vector<int>(numVerts));
	vector < vector<T> > P(numVerts, vector<T>(numVerts));


	for (unsigned i = 0; i < numVerts; i++) {
		for (unsigned j = 0; j < numVerts; j++) {
			int cost = edgeCost(i, j);
			W[i][j] = cost;

			if (cost == INT_INFINITY)
				P[i][j] = NULL;
			else
				P[i][j] = vertexSet[i]->info;
		}
	}


	for (unsigned k = 0; k < numVerts; k++) {
		for (unsigned i = 0; i < numVerts; i++) {
			for (unsigned j = 0; j < numVerts; j++)  {

				int cost = edgeCost(i, k) + edgeCost(k, j);
				if (edgeCost(i, j) > cost) {
					W[i][j] = cost;
					P[i][j] = P[i][k];
				}
			}
		}
	}
}



template <class T, class V>
vector<T> Graph<T,V>::getfloydWarshallPath(const T &origin, const T &dest) {

	vector<T> res;

	int i = -1;
	int j = -1;
	for (unsigned k = 0; k < vertexSet.size(); k++) {
		if (vertexSet[k]->info == origin)
			i = k;
		else if (vertexSet[k]->info == dest)
			j = k;

		if (i != -1 && j != -1)
			break;
	}


	res.push_back(P[i][j]);
	while (!(P[i][j] == origin)) {
		for (unsigned k = 0; k < vertexSet.size(); k++) {
			if (vertexSet[k]->info == P[i][j])
				i = k;
		}

		res.push_back(P[i][j]);
	}

	return res;
}

#endif /* GRAPH_H_ */
