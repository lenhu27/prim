#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <limits>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int n = 7;
    vector<vector<pair<int, int>>> adj(n + 1);

    auto addEdge = [&](int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
        };

    // 12 canh theo hinh
    addEdge(1, 2, 9);
    addEdge(2, 6, 10);
    addEdge(3, 5, 11);
    addEdge(1, 4, 16);
    addEdge(1, 7, 17);
    addEdge(1, 3, 18);
    addEdge(4, 3, 19);
    addEdge(6, 7, 25);
    addEdge(2, 3, 27);
    addEdge(4, 5, 28);
    addEdge(2, 4, 30);
    addEdge(7, 5, 30);

    cout << "=========================================\n";
    cout << "   PRIM - TIM CAY KHUNG NHO NHAT (MST)\n";
    cout << "   Do thi: 7 dinh (1..7)\n";
    cout << "=========================================\n";
    cout << "Nhap dinh bat dau (1..7): ";

    int start;
    cin >> start;
    if (start < 1 || start > n) {
        cout << "Dinh bat dau KHONG hop le!\n";
        return 0;
    }

    const long long INF = numeric_limits<long long>::max();
    vector<long long> key(n + 1, INF);
    vector<int> parent(n + 1, -1);
    vector<bool> inMST(n + 1, false);

    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>
    > pq;

    key[start] = 0;
    pq.push(make_pair(0LL, start));

    long long total = 0;
    int picked = 0;

    while (!pq.empty() && picked < n) {
        // ✅ FIX: copy top ra bien, KHONG lay reference
        pair<long long, int> top = pq.top();
        pq.pop();

        long long curKey = top.first;
        int u = top.second;

        if (inMST[u]) continue;

        inMST[u] = true;
        picked++;
        total += curKey;

        for (const auto& e : adj[u]) {
            int v = e.first;
            int w = e.second;

            if (!inMST[v] && (long long)w < key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.push(make_pair(key[v], v));
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!inMST[i]) {
            cout << "\nDo thi KHONG lien thong (hoac thuat toan chay sai).\n";
            return 0;
        }
    }

    cout << "\n========== KET QUA MST (Prim) ==========\n";
    cout << left << setw(12) << "Canh" << setw(10) << "Trong so" << "\n";
    cout << "---------------------------------------\n";

    for (int v = 1; v <= n; v++) {
        if (v == start) continue;
        cout << parent[v] << " - " << v << setw(6) << " " << key[v] << "\n";
    }

    cout << "---------------------------------------\n";
    cout << "Tong trong so MST = " << total << "\n";
    cout << "=======================================\n";

    return 0;
}
