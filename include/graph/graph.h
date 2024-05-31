#pragma once
#include <iostream>
#include <functional>
#include <unordered_map>
#include <iterator>
#include <list>
#include <algorithm>
#include <vector>
#include <queue>
#include <exception>

using namespace std; 

namespace graph {
	template<typename V, typename Distance = double>
	class Graph {
	private:
		
		struct Edge {
			V _name;
			Distance _dist;

			friend ostream& operator<<(ostream& os, const Edge& E)
			{
				os << E._name<<" "<< E._dist<<" " << "-> ";

				return os;
			}

			friend ostream& operator<<(ostream& os, const list<Edge>& list)
			{
				for (Edge E : list)
					cout << E;

				return os;
			}
		};

		struct Vertex {
			V _name;
			list<Edge> _edge;	

			friend ostream& operator<<(ostream& os, const Vertex& V)
			{
				os << V._edge;
				return os;
			}
		};

		unordered_map<V, Vertex> G;

	public:
		//VERTEX
		bool has_vertex(const V& val) const {
			if (G.contains(val))
				return true;
			return false;
		}

		bool remove_vertex(const V& val) {
			if (G.contains(val)){
				for (const auto& [key, value] : G) {
					remove_edge(key, val);
				}
				G.erase(val);
				return true;
			}
			return false;
		}

		void add_vertex(const V& val) {
			G[val] = Vertex{ val, list<Edge>{} };
		}

		//EDGE
		bool add_edge(const V& from, const V& to, const Distance dist) {
			if (G.contains(from) && G.contains(to)) {
				Edge E{to, dist};
				G[from]._edge.push_back(E);
				return true;
			}
			return false;
		}

		bool has_edge(const V& from, const V& to) const {
			if (G.contains(from) && G.contains(to)) {
				for (Edge E : G.at(from)._edge) {
					if (E._name == to) {
						return true;
					}
				}
			}
			return false;
		}

		bool has_edge(const V& from, const V& to, Distance dist) const {
			if (G.contains(from) && G.contains(to)) {
				for (Edge E : G[from]._edge) {
					if (E._name == to && E._dist == dist) {
						return true;
					}
				}
			}
			return false;
		}

		bool remove_edge(const V& from, const V& to) {
			if (has_edge(from, to)) {
				for (typename list<Edge>::iterator it = ++G.at(from)._edge.begin(); it != G.at(from)._edge.end(); it++) {
					if (it->_name == to) {
						typename list<Edge>::iterator it_tmp = it;
						it = prev(it);
						G[from]._edge.erase(it_tmp);
					}
				}
				typename list<Edge>::iterator begin = G.at(from)._edge.begin();
				if (begin->_name == to) {
					G.at(from)._edge.erase(begin);
				}
				return true;
			}
			return false;
		}

		bool remove_edge(const V& from, const V& to, Distance dist) {
			if (has_edge(from, to, dist)) {
				for (typename list<Edge>::iterator it = ++G[from]._edge.begin(); it != G[from]._edge.end(); it++) {
					if (it->_name == to && it->_dist == dist) {
						typename list<Edge>::iterator it_tmp = it;
						it = prev(it);
						G[from]._edge.erase(it_tmp);
					}
				}
				typename list<Edge>::iterator begin = G[from]._edge.begin();
				if (begin->_name == to && begin->_dist == dist) {
					G[from]._edge.erase(begin);
				}
				return true;
			}
			return false;
		}

		//UTILS
		vector<pair<V, Distance>> edges_vector(const V& val) const {
			vector<pair<V, Distance>> edges;
			if (G.contains(val)) {
				for (typename list<Edge>::iterator it = G[val]._edge.begin(); it != G[val]._edge.end(); it++) {
					edges.push_back(pair{ it->_name, it->_dist });
				}
				return edges;
			}
			return edges;
		}

		list<Edge>::const_iterator edges_it(const V& val) {
			if (G.contains(val)) {
				return G[val]._edge.begin();
			}
		}

		unordered_map<V, Vertex>::const_iterator vertex_it() {
			if (order()) {
				return G.begin();
			}
		}

		list<Edge> edges_list(const V& val)const {
			if (G.contains(val)) {
				return G.at(val)._edge;
			}
		}

		unordered_map<V, Vertex> vertex_list() const {
			if (order()) {
				return G;
			}
		}


		size_t order() const {
			return G.size();
		}

		size_t degree(const V& V) {
			return G[V]._edge.size();
		}

		void bfs(const V& start) const{
			unordered_map<V, bool> visited;
			for (const auto& [key, val] : G) {
				visited[key] = false;
			}
			queue<V> q;

			visited[start] = true;
			q.push(start);

			while (!q.empty()) {
				V vertex = q.front();
				q.pop();
				cout << "Visited vertex " << G.at(vertex)._name << endl;

				for (Edge neighbor : G.at(vertex)._edge) {
					if (!visited[neighbor._name]) {
						visited[neighbor._name] = true;
						q.push(neighbor._name);
					}
				}
			}
		}

		void bfs_func(const V& start, const std::function<void(V)>& func){
			unordered_map<V, bool> visited;
			for (const auto& [key, val] : G) {
				visited[key] = false;
			}
			queue<V> q;

			visited[start] = true;
			q.push(start);

			while (!q.empty()) {
				V vertex = q.front();
				q.pop();
				func(vertex);

				for (Edge neighbor : G[vertex]._edge) {
					if (!visited[neighbor._name]) {
						visited[neighbor._name] = true;
						q.push(neighbor._name);
					}
				}
			}
		}

		unordered_map<V, Distance>  BellmanFord(const V& start) {
			if (G.contains(start)) {
				size_t size = G.size();
				unordered_map<V, Distance> distance;
				for (const auto& [key, val] : G) {
					distance[key] = numeric_limits<Distance>::max();
				}
				unordered_map<V, size_t> visited;
				for (const auto& [key, val] : G) {
					visited[key] = 0;
				}
				queue<V> q;
				distance[start] = 0;
				q.push(start);

				while (!q.empty()) {
					V vertex = q.front();
					q.pop();

					for (Edge neighbor : G[vertex]._edge) {
						if (visited[neighbor._name] == size) {
							break;
						}
						V name = neighbor._name;
						Distance dist = neighbor._dist;
						if (distance[vertex] + dist < distance[name]) {
							distance[name] = distance[vertex] + dist;
							visited[name]++;
							q.push(name);

						}
					}

				}

				//Негативные велосипеды (cycles = велосипед типа)
				for (const auto& [key, val] : G) {
					for (Edge neighbor : G[key]._edge) {
						V name = neighbor._name;
						Distance dist = neighbor._dist;

						if (distance[key] + dist < distance[name]) {
							cout << "That is, you, dear user, in all seriousness, launched a function called BellmanFord,\n which implements the Belman Ford algorithm for finding the shortest paths in a graph.\n At the same time, I did not think about the limitations of this algorithm.\n You made a terrible mistake, your graph contains so-called NEGATIVE cycles\n, in your opinion this algorithm should at least calculate something for you, if you can’t even keep such\n a small thought in your head, !===JUST REMOVE THE NEGATIVE CYCLES===!. Thanks for understanding."<<endl;
							cout << "/$$$$$$$  /$$$$$$$$ /$$       /$$       /$$      /$$  /$$$$$$  /$$   /$$       /$$$$$$$$ /$$$$$$  /$$$$$$$  /$$$$$$$\n"
								<< "| $$__  $$| $$_____/| $$      | $$      | $$$    /$$$ /$$__  $$| $$$ | $$      | $$_____//$$__  $$| $$__  $$| $$__  $$\n"
								<< "| $$  | $$| $$      | $$      | $$      | $$$$  /$$$$| $$  | $$| $$$$| $$      | $$     | $$  | $$| $$  | $$| $$  | $$\n"
								<< "| $$$$$$$ | $$$$$   | $$      | $$      | $$ $$/$$ $$| $$$$$$$$| $$ $$ $$      | $$$$$  | $$  | $$| $$$$$$$/| $$  | $$\n"
								<< "| $$__  $$| $$__/   | $$      | $$      | $$  $$$| $$| $$__  $$| $$  $$$$      | $$__/  | $$  | $$| $$__  $$| $$  | $$\n"
								<< "| $$  | $$| $$      | $$      | $$      | $$|  $ | $$| $$  | $$| $$|  $$$      | $$     | $$  | $$| $$  | $$| $$  | $$\n"
								<< "| $$$$$$$/| $$$$$$$$| $$$$$$$$| $$$$$$$$| $$ |/  | $$| $$  | $$| $$ |  $$      | $$     |  $$$$$$/| $$  | $$| $$$$$$$/\n"
								<< "|_______/ |________/|________/|________/|__/     |__/|__/  |__/|__/  |__/      |__/      |______/ |__/  |__/|_______/";
							throw std::invalid_argument("negative cycles");
						}
					}
				}
				return distance;
			}
			else {
				cout << "This Vertex doesnt exist, sorry bro"<<endl;
				throw std::invalid_argument("Incorrect input vertex");
			}
		}

		unordered_map<V, vector<V>> BellmanFord_path(const V& start) {
			if (G.contains(start)) {
				unordered_map<V, vector<V>> path;
				for (const auto& [key, val] : G) {
					path[key] = vector<V>{};
				}

				size_t size = G.size();
				unordered_map<V, Distance> distance;
				for (const auto& [key, val] : G) {
					distance[key] = numeric_limits<Distance>::max();
				}
				unordered_map<V, size_t> visited;
				for (const auto& [key, val] : G) {
					visited[key] = 0;
				}
				queue<V> q;
				distance[start] = 0;
				q.push(start);

				while (!q.empty()) {
					V vertex = q.front();
					q.pop();

					for (Edge neighbor : G[vertex]._edge) {
						if (visited[neighbor._name] == size) {
							break;
						}
						V name = neighbor._name;
						Distance dist = neighbor._dist;
						if (distance[vertex] + dist < distance[name]) {
							distance[name] = distance[vertex] + dist;
							visited[name]++;
							q.push(name);
							if (path[name].size() > 0 && path[name].back() != vertex) {
								/*Я в своем познании настолько преисполнился, что я как будто бы уже
								сто триллионов миллиардов лет проживаю на триллионах и
									триллионах таких же планет, как эта Земля, мне этот мир абсолютно
									понятен, и я здесь ищу только одного - покоя, умиротворения и
									вот этой гармонии, от слияния с бесконечно вечным, от созерцания
									великого фрактального подобия*/
								path[name].erase(path[name].begin(), path[name].end());
								for (int i = 0; i < path[vertex].size(); i++) {
									path[name].push_back(path[vertex][i]);
								}
								path[name].push_back(vertex);
							}
							else {
								path[name].push_back(vertex);
							}
						}
					}
				}

				//Негативные велосипеды (cycles = велосипед типа)
				for (const auto& [key, val] : G) {
					for (Edge neighbor : G[key]._edge) {
						V name = neighbor._name;
						Distance dist = neighbor._dist;

						if (distance[key] + dist < distance[name]) {
							cout << "That is, you, dear user, in all seriousness, launched a function called BellmanFord,\n which implements the Belman Ford algorithm for finding the shortest paths in a graph.\n At the same time, I did not think about the limitations of this algorithm.\n You made a terrible mistake, your graph contains so-called NEGATIVE cycles\n, in your opinion this algorithm should at least calculate something for you, if you can’t even keep such\n a small thought in your head, !===JUST REMOVE THE NEGATIVE CYCLES===!. Thanks for understanding." << endl;
							cout << "/$$$$$$$  /$$$$$$$$ /$$       /$$       /$$      /$$  /$$$$$$  /$$   /$$       /$$$$$$$$ /$$$$$$  /$$$$$$$  /$$$$$$$\n"
								<< "| $$__  $$| $$_____/| $$      | $$      | $$$    /$$$ /$$__  $$| $$$ | $$      | $$_____//$$__  $$| $$__  $$| $$__  $$\n"
								<< "| $$  | $$| $$      | $$      | $$      | $$$$  /$$$$| $$  | $$| $$$$| $$      | $$     | $$  | $$| $$  | $$| $$  | $$\n"
								<< "| $$$$$$$ | $$$$$   | $$      | $$      | $$ $$/$$ $$| $$$$$$$$| $$ $$ $$      | $$$$$  | $$  | $$| $$$$$$$/| $$  | $$\n"
								<< "| $$__  $$| $$__/   | $$      | $$      | $$  $$$| $$| $$__  $$| $$  $$$$      | $$__/  | $$  | $$| $$__  $$| $$  | $$\n"
								<< "| $$  | $$| $$      | $$      | $$      | $$|  $ | $$| $$  | $$| $$|  $$$      | $$     | $$  | $$| $$  | $$| $$  | $$\n"
								<< "| $$$$$$$/| $$$$$$$$| $$$$$$$$| $$$$$$$$| $$ |/  | $$| $$  | $$| $$ |  $$      | $$     |  $$$$$$/| $$  | $$| $$$$$$$/\n"
								<< "|_______/ |________/|________/|________/|__/     |__/|__/  |__/|__/  |__/      |__/      |______/ |__/  |__/|_______/";
							throw std::invalid_argument("negative cycles");
						}
					}
				}
				for (const auto& [key, val] : path) {
					path[key].push_back(key);
				}
				return path;
			}
			else {
				cout << "This Vertex doesnt exist, sorry bro" << endl;
				throw std::invalid_argument("Incorrect input vertex");
			}
		}

		Distance get_eccentricity(const V& vertex) {
			unordered_map<V, Distance> min_distance= BellmanFord(vertex);
			Distance ecc = -1;
			for (const auto& [key, val] : min_distance) {
				if (val > ecc) {
					ecc = val;
				}
			}
			return ecc;
		}

		vector<V> find_center() {
			Distance center = numeric_limits<Distance>::max();
			vector<V> names;
			for (const auto& [key, val] : G) {
				Distance ecc = get_eccentricity(key);
				if (ecc <= center) {
					center = ecc;
					names.push_back(key);
				}
			}
			return names;
		}

		void print() {
			for (const auto& [key, V] : G)
				std::cout << key <<"->" << " " << V << std::endl;
		}
		
	};


	template <typename V, typename Vertex>
	ostream& operator<<(ostream& os, const unordered_map<V, Vertex>& map)
	{
		for (const auto& [key, V] : map)
			os << key << "->" << " " << V << std::endl;
		return os;
	}
}