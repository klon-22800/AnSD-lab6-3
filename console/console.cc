#include<graph/graph.h>
#include<string>
using namespace graph;
using namespace std;
using namespace graph;

int main(){

    //Graph<string> a;
    //a.add_vertex("A");
    //a.add_vertex("B");
    //a.add_vertex("C");

    //a.add_edge("A", "B", 10);
    //a.add_edge("A", "C", 20);
    //a.add_edge("C", "A", 20);
    //a.add_edge("C", "B", 30);
    //

    ////a.print();
    ///*cout << a.degree("Moscow");*/
    //cout << a.get_eccentricity("A")<<endl;
    //cout << a.get_eccentricity("B")<<endl;
    //cout << a.get_eccentricity("C")<<endl;
    //a.find_center();
    //return 0;

    Graph<string> G;
    G.add_vertex("Moscow");
    G.add_vertex("Samara");
    G.add_vertex("Togliatti");
    G.add_vertex("Peterburg");

    G.add_edge("Moscow", "Samara", 1060);
    G.add_edge("Moscow", "Togliatti", 800);
    G.add_edge("Moscow", "Peterburg", 700);

}