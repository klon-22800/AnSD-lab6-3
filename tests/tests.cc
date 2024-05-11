#include <gtest/gtest.h>
#include <graph/graph.h>

using namespace std;
using namespace graph;

TEST(Functions_test, constuct) {
	cout << "he";
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

