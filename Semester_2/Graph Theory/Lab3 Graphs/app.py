from DirectedGraph import *
from math import inf


def lowest_cost_walk(graph, source, target):
    """
    Finds the lowest cost walk between two vertices in a graph or prints a message if negative cost cycles are present.
    :param graph: DirectedGraph object representing the graph
    :param source: the starting vertex
    :param target: the target vertex
    """
    n = graph.getNumVertices()
    d = [[inf] * n for _ in range(n)]  # Initialize d matrix with infinity
    pred = [[None] * n for _ in range(n)]  # Initialize predecessor matrix

    # Initialize d matrix with edge costs and pred matrix
    for i in range(n):
        for j in graph.getOutboundEdges(i):
            d[i][j] = graph.getCost(i, j)
            pred[i][j] = i

    # Dynamic programming for finding the shortest paths and updating pred matrix
    for k in range(n):
        for i in range(n):
            for j in range(n):
                if d[i][k] != inf and d[k][j] != inf and d[i][j] > d[i][k] + d[k][j]:
                    d[i][j] = d[i][k] + d[k][j]
                    pred[i][j] = pred[k][j]

    # Check for negative cost cycles accessible from the starting vertex
    reachable = set()
    stack = [source]
    while stack:
        current = stack.pop()
        for neighbor in graph.getOutboundEdges(current):
            if neighbor not in reachable:
                reachable.add(neighbor)
                stack.append(neighbor)

    # Check for negative cost cycles accessible from the starting vertex
    for i in range(n):
        if i in reachable and d[i][i] < 0:
            print("Negative cost cycle detected, cannot find lowest cost walk.")
            return

    # Print the lowest cost walk and its cost
    min_cost = d[source][target]
    if min_cost == inf:
        print("No path exists from {} to {}".format(source, target))
    else:
        # Reconstruct the lowest cost walk
        walk = [target]
        current_vertex = target
        while current_vertex != source:
            current_vertex = pred[source][current_vertex]
            walk.append(current_vertex)
        walk.reverse()

        print("Lowest cost walk from {} to {}: {}".format(source, target, min_cost))
        print("Actual walk:", walk)


def main():
    graph = load_from_file("random_graph2.txt")
    while True:
        print("1. Find the lowest cost walk between 2 vertices")
        print("0. Exit")
        option = int(input(">>> "))
        if option == 1:
            source = int(input("Enter the source vertex: "))
            dest = int(input("Enter the destination vertex: "))
            lowest_cost_walk(graph, source, dest)
            # print(path)

        elif option == 0:
            break
        else:
            print("Invalid option. Please try again")


main()
