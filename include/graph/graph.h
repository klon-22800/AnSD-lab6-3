#pragma once
#include <iostream>
#include <unordered_map>
#include <iterator>
#include <list>
#include <algorithm>
#include <vector>

using namespace std; 

namespace graph {
	template<typename V, typename Distance = double>
	class Graph {
	private:
		
		struct Edge {
			size_t _num;
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
			size_t _num = 0;
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
		Graph() = default;

		//VERTEX
		bool has_vertex(const V& val) const {
			if (G.contains(val))
				return true;
			return false;
		}

		bool remove_vertex(const V& val) {
			if (G.contains(val)){
				G.erase(val);
				return true;
			}
			return false;
		}

		void add_vertex(const V& val) {
			G[val] = Vertex{ 0, val, list<Edge>{} };
		}

		//EDGE
		bool add_edge(const V& from, const V& to, const Distance dist) {
			if (G.contains(from) && G.contains(to)) {
				Edge E{0, to, dist};
				G[from]._edge.push_back(E);
				return true;
			}
			return false;
		}

		bool has_edge(const V& from, const V& to) {
			if (G.contains(from) && G.contains(to)) {
				for (Edge E : G[from]._edge) {
					if (E._name == to) {
						return true;
					}
				}
			}
			return false;
		}

		bool has_edge(const V& from, const V& to, Distance dist) {
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
				for (typename list<Edge>::iterator it = ++G[from]._edge.begin(); it != G[from]._edge.end(); it++) {
					if (it->_name == to) {
						typename list<Edge>::iterator it_tmp = it;
						it = prev(it);
						G[from]._edge.erase(it_tmp);
					}
				}
				typename list<Edge>::iterator begin = G[from]._edge.begin();
				if (begin->_name == to) {
					G[from]._edge.erase(begin);
				}
				return true;
			}
			return false;
		}

		bool remove_edge(const V& from, const V& to, Distance dist) {
			if (has_edge(from, to)) {
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
		vector<pair<V, Distance>> edges_list(const V& val) {
			vector<pair<V, Distance>> edges;
			if (G.contains(val)) {
				for (typename list<Edge>::iterator it = G[val]._edge.begin(); it != G[val]._edge.end(); it++) {
					edges.push_back(pair{ it->_name, it->_dist });
				}
				return edges;
			}
			return edges;
		}

		size_t order() const {
			return G.size();
		}

		size_t degree(const V& V) {
			return G[V]._edge.size();
		}

		void print() {
			for (const auto& [key, V] : G)
				std::cout << key <<"->" << " " << V << std::endl;
		}
	};

}