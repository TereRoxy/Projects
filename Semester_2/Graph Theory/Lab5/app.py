from DirectedGraph import *

INF = float('inf')


def compute(graph, start, mask, dp, parent):
    """
    Computes the minimum cost to visit all nodes in 'mask' starting from 'start'.
    :param graph: DirectedGraph object
    :param start: starting node
    :param mask: bitmask representing the set of nodes to visit
    :param dp: memoization table
    :param parent: table to store the parent node for path reconstruction
    :return: minimum cost
    """
    if dp[start][mask] != -1:
        return dp[start][mask]

    result = INF
    n = graph.getNumVertices()

    for i in range(n):
        if mask & (1 << i):  # Check if vertex 'i' is in the subset 'mask'
            new_mask = mask & ~(1 << i)  # Create a new mask with 'i' removed
            if graph.isEdge(start, i):  # Check if there is an edge from 'start' to 'i'
                temp = graph.getCost(start, i) + compute(graph, i, new_mask, dp, parent)
                if temp < result:   # if we get a new minimum path
                    result = temp
                    parent[start][mask] = i  # Record the parent for path reconstruction

    dp[start][mask] = result
    return result


def get_path(start, mask, parent):
    """
    Recursively reconstructs the path of the TSP.
    :param start: starting node
    :param mask: bitmask representing the set of nodes visited
    :param parent: table to store the parent node for path reconstruction
    :return: path as a list of nodes
    """
    path = []
    while parent[start][mask] != -1:
        next_vertex = parent[start][mask]
        path.append(next_vertex)
        mask &= ~(1 << next_vertex)  # Remove 'next_vertex' from the mask
        start = next_vertex
    return path


def tsp(graph):
    """
    Solves the TSP and prints the tour cost and path.
    :param graph: DirectedGraph object
    """
    n = graph.getNumVertices()
    npow = 1 << n  # 2^n, number of subsets
    dp = [[-1] * npow for _ in range(n)]  # Initialize DP table
    parent = [[-1] * npow for _ in range(n)]  # Initialize parent table

    # initialize the dp matrix with direct edge costs
    for i in range(n):
        if graph.isEdge(i, 0):  # Check if there is an edge from 'i' to '0'
            dp[i][0] = graph.getCost(i, 0)

    result = compute(graph, 0, npow - 2, dp, parent)  # Compute TSP starting from node 0

    if result == INF:
        print("There is no Hamiltonian cycle")

    else:
        print("Tour cost:", result)
        print("Tour path:")
        path = [0] + get_path(0, npow - 2, parent)  # Get the reconstructed path
        print(path + [0])  # Complete the cycle by returning to the starting node


def main():
    graph = load_from_file("random_graph1.txt")
    while True:
        print("1. Find a minimum cost Hamiltonian cycle (i.e., solve the TSP)")
        print("0. Exit")
        option = int(input(">>> "))
        if option == 1:
            tsp(graph)

        elif option == 0:
            break
        else:
            print("Invalid option. Please try again")


main()
