#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class AdjacencyList {
private:
    map<string, vector<string>> graph;

public:
    void add(const string &from, const string &to)
    {
        graph[from].push_back(to);
        if (graph.find(to) == graph.end()) {
            graph[to] = {};
        }
    }
    //get all vertices in the map return a vector
    vector<string> getAllVertices()
    {
        vector<string> vertices;
        for (auto &&p : graph) {
            vertices.push_back(p.first);
        }
        return vertices;
    }
    int numVertices()
    {
        return graph.size();
    }
    vector<string> getPageTo(const string &to)
    {
        vector<string> pageTo;
        for (auto &&p : graph) {
            if (find(p.second.begin(), p.second.end(), to) != p.second.end()) {
                pageTo.push_back(p.first);
            }
        }
        return pageTo;
    }
    //get the number of vertices which has a point to the given vertex
    int getAdjacentSize(const string &vertex)
    {
        return graph[vertex].size();
    }
    int getIndex(const string &str, vector<string> &vec)
    {
        return find(vec.begin(), vec.end(), str) - vec.begin();
    }
    double reciprocal(double arg)
    {
        return 1.0 / arg;
    }
    void PageRank(int n)
    {
        vector<string> names = getAllVertices();
        vector<double> rank(numVertices(), reciprocal(numVertices()));
        for (; n > 1; --n) {
            auto tmpVec = rank;
            fill(rank.begin(), rank.end(), 0.0);
            for (int i = 0; i < numVertices(); ++i) {
                for (auto &&j : getPageTo(names[i])) {
                    rank[i] += tmpVec[getIndex(j, names)] * reciprocal(getAdjacentSize(j));
                }
            }
        }
        int index = {};
        //print the name and its rank
        for (auto &&ele : graph) {
            cout << ele.first << " " << fixed << setprecision(2) << rank[index++] << '\n';
        }
    }
};
int main()
{
    AdjacencyList adj;
    int numLine, powerIter;
    cin >> numLine >> powerIter;
    string from, to;
    for (int i = 0; i < numLine; ++i) {
        cin >> from >> to;
        adj.add(from, to);
    }
    adj.PageRank(powerIter);
}