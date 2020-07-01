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
    vector<string> getAllVerticle()
    {
        vector<string> verticles;
        for (auto &&p : graph) {
            verticles.push_back(p.first);
        }
        return verticles;
    }
    int numVerticle()
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
        auto names = getAllVerticle();
        vector<double> rank(numVerticle(), reciprocal(numVerticle()));
        for (int num = 0; num < n - 1; ++num) {
            auto tmpVec = rank;
            auto it = graph.begin();
            fill(rank.begin(), rank.end(), 0.0);
            for (auto &&i : rank) {
                for (auto &&j : getPageTo(it->first)) {
                    i += tmpVec[getIndex(j, names)] * reciprocal(getAdjacentSize(j));
                } 
                ++it;
            }
        }
        int index = {};
        for (auto &&ele : graph) {
            cout << ele.first << " " << fixed << setprecision(2) << rank[index] << '\n';
            ++index;
        }
    }
};
int main()
{
    int numLine, powerIter;
    string from, to;
    cin >> numLine >> powerIter;
    AdjacencyList adj;
    for (int i = 0; i < numLine; ++i) {
        cin >> from >> to;
        adj.add(from, to);
    }
    adj.PageRank(powerIter);
}