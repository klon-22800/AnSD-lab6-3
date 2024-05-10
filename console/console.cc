#include<graph/graph.h>
#include<string>
using namespace graph;

using namespace std;
using namespace graph;

int main(){

    Graph<string> a;
    a.add_vertex("Moscow");
    a.add_vertex("Samara");
    a.add_edge("Moscow", "Samara", 150);
    a.add_edge("Moscow", "Samara", 150);
    a.add_edge("Moscow", "Samara", 150);
    a.print();
    cout << a.degree("Moscow");
    return 0;
}