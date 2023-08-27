from TSP import *

class Christofides (TSP):
    
    def solve(self):
        root = 0
        MST = nx.minimum_spanning_tree(self.G, algorithm='prim')

        nodesWithOddDegree = []

        for i in range(self.numInstance):
            if MST.degree[i] % 2 != 0:
                nodesWithOddDegree.append(i)
        
        subGraph = self.G.subgraph(nodesWithOddDegree)
        
        # perfect matching
        M = nx.min_weight_matching(subGraph)

        # Transfor MST in multiGraph
        G_line = nx.MultiGraph(MST)
        
        # Add on G_line the edges from the perfect matching
        for edge in M:
            node_a = edge[0]
            node_b = edge[1]
            G_line.add_edge(node_a, node_b, weight = self.distanceMatrix[node_a, node_b])

        
        eulerianPath = nx.eulerian_path(G_line, root)
        eulerianPath = list(eulerianPath)

        # Get the nodes firt nodes from eulerianPath edges
        eulerianNodes = [edge[0] for edge in eulerianPath]
        eulerianNodes.append(0)

        nodes = set()
        lastNode = 0

        # Remove repetead nodes
        for i in range(len(eulerianNodes) - 1):
            node = eulerianNodes[i]
            if node in nodes:
                nextNode = eulerianNodes[i+1]                
                G_line.remove_edge(lastNode, node)
                G_line.remove_edge(node, nextNode)

                G_line.add_edge(lastNode, nextNode, weight= self.distanceMatrix[lastNode, nextNode])
            else:
                nodes.add(node)
                lastNode = node

        # Get the nodes in preorder
        hamiltonianNodes = nx.dfs_preorder_nodes(G_line, root)
        hamiltonianNodes = list(hamiltonianNodes)
        
        # Calculated the cost
        cost = 0
        for i in range(len(hamiltonianNodes) -1):
            cost += self.distanceMatrix[hamiltonianNodes[i], hamiltonianNodes[i+1]]
        # close the cycle
        cost += self.distanceMatrix[-1, 0]
        print(f'Solução Ótima: {cost}')

        