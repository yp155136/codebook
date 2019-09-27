struct Cost_Flow {
    void add_edge(int from, int to, int cap, int cost) {
        G[from].push_back(Edge(to, cap, SZ(G[to]), cost));
        G[to].push_back(Edge(from, 0, SZ(G[from]) - 1, -cost));
    }
    pii solve() {
        int flow = 0, cost = 0;
        while (true) {
            fill(dis, dis + N, INF); dis[s] = 0;
            queue<int> que; que.push(s);
            while (!que.empty()) {
                int t = que.front(); que.pop();
                in_que[t] = false; int id = 0;
                for (Edge e: G[t]) {
                    if (e.cap > 0 && dis[e.to] > dis[t] + e.cost) {
                        dis[e.to] = dis[t] + e.cost;
                        pre[e.to] = t; pre_id[e.to] = id;
                        if (!in_que[e.to]) {
                            in_que[e.to] = true; que.push(e.to);
                        }
                    }
                    ++id;
                }
            }
            if (dis[t] == INF) break;
            int mn_flow = INF;
            for (int i = t; i != s; i = pre[i]) {
                mn_flow = min(mn_flow, G[ pre[i] ][ pre_id[i] ].cap);
            }
            flow += mn_flow;
            cost += mn_flow * dis[t];
            for (int i = t; i != s; i = pre[i]) {
                G[ pre[i] ][ pre_id[i] ].cap -= mn_flow;
                G[ i ][ G[ pre[i] ][ pre_id[i] ].rev ].cap += mn_flow;
            }
        }
        return make_pair(flow, cost);
    }
} solver;


