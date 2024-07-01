from collections import deque
from DirectedGraph import *


def find_shortest_path(graph, start, end):
    # Check if start and end vertices are in the graph
    if start not in graph.getVertices() or end not in graph.getVertices():
        raise ValueError("Start or end vertex not in graph")

    # Initialize a set to keep track of visited vertices
    visited = {start}

    # Initialize a queue with a tuple containing the start vertex and its path
    queue = deque([(start, [start])])

    # Continue BFS until the queue is empty
    while queue:
        # Pop the leftmost vertex and its path from the queue
        current, path = queue.popleft()

        # If the current vertex is the end vertex, return the path
        if current == end:
            return path

        # Explore neighbors of the current vertex
        for neighbor in graph.getOutboundEdges(current):
            # If neighbor hasn't been visited, mark it as visited and add it to the queue
            if neighbor not in visited:
                visited.add(neighbor)
                # Append neighbor to the path and enqueue it along with the updated path
                queue.append((neighbor, path + [neighbor]))

    # If end vertex is not reachable from start vertex, return None
    return None


def kosaraju(graph):
    # Step 1: Perform DFS on the original graph and get the finishing times
    finishing_times = []  # List to store finishing times of vertices
    visited = set()  # Set to keep track of visited vertices

    # Depth-first search function for the first pass
    def dfs1(vertex):
        visited.add(vertex)
        for neighbor in graph.getOutboundEdges(vertex):
            if neighbor not in visited:
                dfs1(neighbor)
        finishing_times.append(vertex)  # Add vertex to finishing times after exploration

    # Perform DFS for each vertex that hasn't been visited yet
    for vertex in graph.getVertices():
        if vertex not in visited:
            dfs1(vertex)

    # Step 2: Transpose the graph
    transposed_graph = transpose(graph)

    # Step 3: Perform DFS on the transposed graph in the reverse order of finishing times
    visited.clear()  # Clear visited set for the second pass
    components = []  # List to store strongly connected components

    # Depth-first search function for the second pass
    def dfs2(vertex, component):
        visited.add(vertex)
        component.append(vertex)
        for neighbor in transposed_graph.getOutboundEdges(vertex):
            if neighbor not in visited:
                dfs2(neighbor, component)

    # Perform DFS on transposed graph starting from vertices with highest finishing times
    while finishing_times:
        vertex = finishing_times.pop()  # Start DFS from vertex with highest finishing time
        if vertex not in visited:  # We have a new SCC
            component = []  # Initialize a new component
            dfs2(vertex, component)  # Perform DFS to find all vertices in this SCC
            components.append(component)  # Add the found component to the list of SCCs

    return components


def transpose(graph):
    # Create a new graph with edges reversed (transpose)
    transposed_graph = DirectedGraph(graph.getNumVertices())
    for edge in graph.getEdges():
        # Reverse the direction of each edge
        transposed_graph.addEdge(edge[1], edge[0])
    return transposed_graph


def main():
    graph = load_from_file("random_graph1.txt")
    # undirected_graph = load_from_file("graph2.txt")
    while True:
        print("This algorithm finds the shortest path in a directed graph between 2 nodes")
        print("1. Print the shortest path")
        print("2. Print the strongly-connected components")
        # print("3. Print the bi-connected components")
        print("0. Exit")
        option = int(input(">>> "))
        if option == 1:
            start = int(input("Enter the starting node: "))
            end = int(input("Enter the end node: "))
            path = find_shortest_path(graph, start, end)
            if path is None:
                print("There is no path between the given vertices")
            else:
                print_string = ""
                for node in path:
                    print_string += str(node)
                    if node != path[-1]:
                        print_string += "->"

                print(print_string)
        elif option == 2:
            SCC = kosaraju(graph)
            print("Strongly connected components are: ", SCC)
        elif option == 0:
            break
        else:
            print("Invalid option")


main()
