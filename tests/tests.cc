#include <gtest/gtest.h>
#include <graph/graph.h>
#include<functional>
using namespace std;
using namespace graph;



TEST(Functions_test, construct_and_size) {
	Graph<string> G;
	G.add_vertex("Moscow");
	G.add_vertex("Samara");
	G.add_vertex("Togliatti");
	G.add_vertex("Peterburg");

	G.add_edge("Moscow", "Samara", 1060);
	G.add_edge("Moscow", "Togliatti", 800);
	G.add_edge("Moscow", "Peterburg", 700);

	G.add_edge("Samara", "Moscow", 1060);
	G.add_edge("Samara", "Togliatti", 90);
	G.add_edge("Samara", "Peterburg", 1700);

	G.add_edge("Togliatti", "Moscow", 800);
	G.add_edge("Togliatti", "Samara", 90);
	G.add_edge("Togliatti", "Peterburg", 1690);

	G.add_edge("Peterburg", "Moscow", 700);
	G.add_edge("Peterburg", "Samara", 1700);
	G.add_edge("Peterburg", "Togliatti", 1690);
	EXPECT_EQ(G.order(), 4);
}
TEST(Functions_test, removing) {
	Graph<string> G;
	G.add_vertex("Moscow");
	G.add_vertex("Samara");
	G.add_vertex("Togliatti");
	G.add_vertex("Peterburg");

	G.add_edge("Moscow", "Samara", 1060);
	G.add_edge("Moscow", "Togliatti", 800);
	G.add_edge("Moscow", "Peterburg", 700);

	G.add_edge("Samara", "Moscow", 1060);
	G.add_edge("Samara", "Togliatti", 90);
	G.add_edge("Samara", "Peterburg", 1700);

	G.add_edge("Togliatti", "Moscow", 800);
	G.add_edge("Togliatti", "Samara", 90);
	G.add_edge("Togliatti", "Peterburg", 1690);

	G.add_edge("Peterburg", "Moscow", 700);
	G.add_edge("Peterburg", "Samara", 1700);
	G.add_edge("Peterburg", "Togliatti", 1690);

	G.remove_edge("Peterburg", "Togliatti");
	G.print();
	EXPECT_EQ(G.has_edge("Peterburg", "Togliatti"), false);
}

TEST(Functions_test, BFS) {
	Graph<string> G;
	G.add_vertex("Moscow");
	G.add_vertex("Samara");
	G.add_vertex("Togliatti");
	G.add_vertex("Peterburg");

	G.add_edge("Moscow", "Samara", 1060);
	G.add_edge("Moscow", "Togliatti", 800);
	G.add_edge("Moscow", "Peterburg", 700);

	G.add_edge("Samara", "Moscow", 1060);
	G.add_edge("Samara", "Togliatti", 90);
	G.add_edge("Samara", "Peterburg", 1700);

	G.add_edge("Togliatti", "Moscow", 800);
	G.add_edge("Togliatti", "Samara", 90);
	G.add_edge("Togliatti", "Peterburg", 1690);

	G.add_edge("Peterburg", "Moscow", 700);
	G.add_edge("Peterburg", "Samara", 1700);
	G.add_edge("Peterburg", "Togliatti", 1690);

	
	G.bfs("Samara");
}

TEST(Functions_test, Bellman_Ford_cycled_graph) {
	Graph<string> G;
	G.add_vertex("Moscow");
	G.add_vertex("Samara");
	G.add_vertex("Togliatti");
	G.add_vertex("Peterburg");
	G.add_vertex("o");


	G.add_edge("Moscow", "Peterburg", 700);

	G.add_edge("Samara", "Togliatti", 90);
	G.add_edge("Samara", "Peterburg", 1700);

	G.add_edge("Togliatti", "Moscow", 800);

	G.add_edge("o", "Peterburg", 200);
	G.add_edge("Peterburg", "o", 100);



	unordered_map <string, double> shortest_path = G.BellmanFord("Samara");
	double res = shortest_path["o"];
	//s->t->m->p->o
	EXPECT_EQ(res, 1690);
}

TEST(Functions_test, Bellman_Ford_negative_cycles) {
	Graph<string> G;
	G.add_vertex("Moscow");
	G.add_vertex("Samara");
	G.add_vertex("Togliatti");
	G.add_vertex("Peterburg");

	G.add_edge("Moscow", "Samara", 1060);
	G.add_edge("Moscow", "Togliatti", 800);
	G.add_edge("Moscow", "Peterburg", 700);

	G.add_edge("Samara", "Moscow", 1060);
	G.add_edge("Samara", "Togliatti", 90);
	G.add_edge("Samara", "Peterburg", 1700);

	G.add_edge("Togliatti", "Moscow", 800);
	G.add_edge("Togliatti", "Samara", 90);
	G.add_edge("Togliatti", "Peterburg", 1690);

	G.add_edge("Peterburg", "Moscow", -700);
	G.add_edge("Peterburg", "Samara", -1700);
	G.add_edge("Peterburg", "Togliatti", -1690);

	EXPECT_ANY_THROW(G.BellmanFord("Togliatti"), invalid_argument("negative cycles"));
}

TEST(Functions_test, find_center) {
	Graph<string> G;
	G.add_vertex("Moscow");
	G.add_vertex("Samara");
	G.add_vertex("Togliatti");
	G.add_vertex("Peterburg");

	G.add_edge("Moscow", "Samara", 1060);
	G.add_edge("Moscow", "Togliatti", 800);
	G.add_edge("Moscow", "Peterburg", 700);

	G.add_edge("Samara", "Moscow", 1060);
	G.add_edge("Samara", "Togliatti", 90);
	G.add_edge("Samara", "Peterburg", 1700);

	G.add_edge("Togliatti", "Moscow", 800);
	G.add_edge("Togliatti", "Samara", 90);
	G.add_edge("Togliatti", "Peterburg", 1690);

	G.add_edge("Peterburg", "Moscow", 700);
	G.add_edge("Peterburg", "Samara", 1700);
	G.add_edge("Peterburg", "Togliatti", 1690);

	vector<string> centers = G.find_center();
	string center = centers[0];
	EXPECT_EQ(center, "Moscow");
}
TEST(Functions_test, iter) {
	Graph<string> G;
	G.add_vertex("Moscow");
	G.add_vertex("Samara");
	G.add_vertex("Togliatti");
	G.add_vertex("Peterburg");

	G.add_edge("Moscow", "Samara", 1060);
	G.add_edge("Moscow", "Togliatti", 800);
	G.add_edge("Moscow", "Peterburg", 700);

	G.add_edge("Samara", "Moscow", 1060);
	G.add_edge("Samara", "Togliatti", 90);
	G.add_edge("Samara", "Peterburg", 1700);

	G.add_edge("Togliatti", "Moscow", 800);
	G.add_edge("Togliatti", "Samara", 90);
	G.add_edge("Togliatti", "Peterburg", 1690);

	G.add_edge("Peterburg", "Moscow", 700);
	G.add_edge("Peterburg", "Samara", 1700);
	G.add_edge("Peterburg", "Togliatti", 1690);
}
TEST(Functions_test, remove_vert) {
	Graph<string> G;
	G.add_vertex("Moscow");
	G.add_vertex("Samara");
	G.add_vertex("Togliatti");
	G.add_vertex("Peterburg");

	G.add_edge("Moscow", "Samara", 1060);
	G.add_edge("Moscow", "Togliatti", 800);
	G.add_edge("Moscow", "Peterburg", 700);
	
	G.remove_vertex("Samara");
	
	G.print();
}

TEST(Functions_test, edge_list) {
	Graph<string> G;
	G.add_vertex("Moscow");
	G.add_vertex("Samara");
	G.add_vertex("Togliatti");
	G.add_vertex("Peterburg");

	G.add_edge("Moscow", "Samara", 1060);
	G.add_edge("Moscow", "Togliatti", 800);
	G.add_edge("Moscow", "Peterburg", 700);

	auto a = G.edges_list("Moscow");
	cout << a;
}

TEST(Functions_test, vertex_list) {
	Graph<string> G;
	G.add_vertex("Moscow");
	G.add_vertex("Samara");
	G.add_vertex("Togliatti");
	G.add_vertex("Peterburg");

	G.add_edge("Moscow", "Samara", 1060);
	G.add_edge("Moscow", "Togliatti", 800);
	G.add_edge("Moscow", "Peterburg", 700);

	auto a = G.vertex_list();
	cout << a;

}

TEST(Functions_test, bfs_func) {
	Graph<string> G;
	G.add_vertex("Moscow");
	G.add_vertex("Samara");
	G.add_vertex("Togliatti");
	G.add_vertex("Peterburg");

	G.add_edge("Moscow", "Samara", 1060);
	G.add_edge("Moscow", "Togliatti", 800);
	G.add_edge("Moscow", "Peterburg", 700);

	/*G.bfs_func("Moscow", std::function<void(const string&)>(printVertex<string>));*/
}
TEST(Functions_test, bell) {
	Graph<string> G;
	G.add_vertex("1");
	G.add_vertex("2");
	G.add_vertex("3");
	G.add_vertex("4");
	G.add_vertex("5");

	G.add_edge("1", "2", 5);
	G.add_edge("1", "3", 10);
	G.add_edge("1", "4", 12);
	G.add_edge("1", "5", 14);

	G.add_edge("3", "4", 1);
	G.add_edge("3", "5", 2);

	G.add_edge("4", "2", 1);


	unordered_map<string,vector<string>> a = G.huyomoyo("1");
	for (const auto& [key, val] : a) {
		for (int i = 0; i < a[key].size(); i++) {
			cout << a[key][i] << "->";
		}
		cout << endl;
	}

}