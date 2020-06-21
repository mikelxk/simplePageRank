#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
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
    void PageRank(int n)
    {
        vector<string> names = getAllVerticle();
        vector<vector<double>> M(numVerticle(), vector<double>(numVerticle()));
        vector<double> rank(numVerticle(), 1.0 / numVerticle());
        int index{};
        for (auto &&it : graph) {
            vector<string> tmp = getPageTo(it.first);
            for (auto &&str : tmp) {
                //find the str's index in the M and assign it to 1/d_j
                M[index][find(names.begin(), names.end(), str) - names.begin()] = 1.0 / getAdjacentSize(str);
            }
            ++index;
        }
        for (int num = 0; num < n - 1; ++num) {
            auto tmpVec = rank;
            fill(rank.begin(), rank.end(), 0.0);
            for (int i = 0; i < numVerticle(); ++i) {
                for (int j = 0; j < numVerticle(); ++j) {
                    rank[i] += M[i][j] * tmpVec[j];
                }
            }
        }
        index = {}; //re-initialize index to 0
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
    for (int i = 0; i < numLine; i++) {
        cin >> from >> to;
        adj.add(from, to);
    }
    adj.PageRank(powerIter);
}