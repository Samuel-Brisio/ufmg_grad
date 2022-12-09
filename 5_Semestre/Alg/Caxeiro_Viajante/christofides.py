from TSP import *

class Christofides (TSP):
    
    def solve(self):
        root = 0
        MST = nx.minimum_spanning_tree(self.G, algorithm='prim')
        print(self.G.degree[0])

        nodesWithOddDegree = []

        for i in range(self.numInstance):
            if MST.degree[i] % 2 != 0:
                nodesWithOddDegree.append(i)
        
        subGraph = self.G.subgraph(nodesWithOddDegree)
        
        M = nx.min_weight_matching(subGraph)

        G_line = nx.MultiGraph(MST)
        
        for edge in M:
            node_a = edge[0]
            node_b = edge[1]
            G_line.add_edge(node_a, node_b, weight = self.distanceMatrix[node_a, node_b])

        eulerianPath = nx.eulerian_path(G_line, root)

        print(list(eulerianPath))

        # nx.draw_networkx_nodes(G_line, pos=nx.circular_layout(G_line))
        # nx.draw_networkx_edges(G_line, pos=nx.circular_layout(G_line))
        # nx.draw_networkx_edge_labels(G_line, pos=nx.circular_layout(G_line))

        print(M)
        # nx.draw_networkx(G_line)
        # plt.show()


        pos = nx.random_layout(G_line)
        nx.draw_networkx_nodes(G_line, pos, node_color = 'r', node_size = 100, alpha = 1)
        ax = plt.gca()
        for e in G_line.edges:
            ax.annotate("",
                        xy=pos[e[0]], xycoords='data',
                        xytext=pos[e[1]], textcoords='data',
                        arrowprops=dict(arrowstyle="->", color="0.5",
                                        shrinkA=5, shrinkB=5,
                                        patchA=None, patchB=None,
                                        connectionstyle="arc3,rad=rrr".replace('rrr',str(0.3*e[2])
                                        ),
                                        ),
                        )
        plt.axis('off')
        plt.show()
        

        