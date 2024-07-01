from UndirectedGraph import *
from heapq import heappop, heappush


def prim(g):
    # Choose an arbitrary starting vertex
    s = next(g.getVertices())
    pq = []     # priority queue
    for x in g.getOutboundEdges(s):  # Iterate through neighbors of start vertex
        heappush(pq, (g.getCost(s, x), s, x))

    treeVertices = set()    # Set of vertices in the minimum spanning tree
    treeVertices.add(s)     # Add start vertex to the tree
    treeEdges = []          # List of edges in the minimum spanning tree
    treeCost = 0

    while pq:   # while we have edges
        cost, x, y = heappop(pq)    # pop the edge with the minimum cost from the heap
        if y in treeVertices:      # skip the vertex if it is already in the tree
            continue

        treeVertices.add(y)    # if not, add it to the tree
        treeEdges.append((x, y))    # add the edge to the tree
        treeCost += cost    # increase the total cost
        for neighbour in g.getOutboundEdges(y):    # parse the neighbours of the dest vertex
            if neighbour not in treeVertices:   # add the vertex if not already in the tree
                heappush(pq, (g.getCost(y, neighbour), y, neighbour))   # add all the edges to the pq
    return treeEdges, treeCost


def main():
    graph = load_from_file("random_graph1.txt")
    while True:
        print("1. Find the minimum spanning tree using Prim's algorithm.")
        print("0. Exit")
        option = int(input(">>> "))
        if option == 1:
            treeEdges, treeCost = prim(graph)
            for edge in treeEdges:
                x, y = edge
                print(x, y)
            print("Tree cost: ", treeCost)

        elif option == 0:
            break
        else:
            print("Invalid option. Please try again")


main()
