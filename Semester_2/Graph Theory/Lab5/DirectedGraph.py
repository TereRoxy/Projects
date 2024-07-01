from copy import deepcopy
from random import randint


class DirectedGraph:
    """
    Class representing a directed graph.
    """
    def __init__(self, n=0):
        """
        Constructor for the DirectedGraph class.
        :param n: number of specified vertices
        :raises ValueError: if the number of vertices is negative or not an integer
        """
        if type(n) is not int or n < 0:
            raise ValueError("Invalid number of vertices")
        self.__vertices_nr = n  # number of vertices
        self.__edge_nr = 0
        self.__inbound_edges = {}   # key: vertex, value: list of inbound edges
        self.__outbound_edges = {}  # key: vertex, value: list of outbound edges
        self.__costs = {}        # key: tuple (source, target), value: cost of the edge
        self.__vertices = list(range(n))
        for i in range(n):
            self.__inbound_edges[i] = []
            self.__outbound_edges[i] = []

    def copy(self):
        """
        Creates and returns a deep copy of the graph.
        :return: Deep copy of the graph
        """
        copy = DirectedGraph(self.__vertices_nr)
        copy.__inbound_edges = deepcopy(self.__inbound_edges)
        copy.__outbound_edges = deepcopy(self.__outbound_edges)
        copy.__costs = deepcopy(self.__costs)
        copy.__edge_nr = self.__edge_nr
        copy.__vertices = deepcopy(self.__vertices)
        return copy

    def addVertex(self, vertex: int):
        """
        Adds a vertex to the graph.
        :Preconditions: vertex doesn't exist in the graph
        """
        self.__vertices_nr += 1
        self.__vertices.append(vertex)
        self.__inbound_edges[vertex] = []
        self.__outbound_edges[vertex] = []

    def removeVertex(self, vertex: int):
        """
        Removes a vertex from the graph. Also removes all edges that have the vertex as source or target
        (and updates the number of total edges). Decreases the number of vertices by 1.
        :Preconditions: vertex exists in the graph
        """
        for v in self.__vertices:
            if self.isEdge(v, vertex):
                self.removeEdge(v, vertex)
            if self.isEdge(vertex, v):
                self.removeEdge(vertex, v)
        exists = False
        self.__vertices.remove(vertex)
        if vertex in self.__inbound_edges.keys():
            del self.__inbound_edges[vertex]
            exists = True
        if vertex in self.__outbound_edges.keys():
            del self.__outbound_edges[vertex]
            exists = True
        if exists:
            self.__vertices_nr -= 1

    def isEdge(self, source: int, target: int):
        """
        Checks if there is an edge between source vertex and target vertex.
        Preconditions: source and target exist as vertices in the graph
        :return: True if there is an edge source->target, False otherwise
        """
        return target in self.__outbound_edges[source]

    def addEdge(self, source: int, target: int, cost=None):
        """
        Adds an edge to the graph if it doesn't exist. Increases the number of total edges by 1.
        :Preconditions: source and target exist as vertices in the graph, edge doesn't exist
        """
        self.__outbound_edges[source].append(target)
        self.__inbound_edges[target].append(source)
        self.__costs[(source, target)] = cost
        self.__edge_nr += 1

    def removeEdge(self, source: int, target: int):
        """
        Removes an edge from the graph if it exists.
        :Preconditions: source and target exist as vertices in the graph, edge exists
        """
        self.__outbound_edges[source].remove(target)
        self.__inbound_edges[target].remove(source)
        self.__edge_nr -= 1
        del self.__costs[(source, target)]

    def getNumVertices(self):
        """
        Returns the number of vertices in the graph.
        """
        return self.__vertices_nr

    def getTotalNumEdges(self):
        """
        Returns the total number of edges in the graph.
        """
        return self.__edge_nr

    def getCost(self, source: int, target: int):
        """
        Returns the cost of an edge.
        :Preconditions: source and target exist as vertices in the graph, the edge exists
        """
        return self.__costs[(source, target)]

    def setCost(self, source: int, target: int, cost: int):
        """
        Sets the cost of a specified edge.
        :Preconditions: source and target exist as vertices in the graph, the edge exists
        """
        self.__costs[(source, target)] = cost

    def getInDegree(self, vertex):
        """
        Gets the in-degree of a vertex.
        :Preconditions: vertex exists in the graph
        """
        return len(self.__inbound_edges[vertex])

    def getOutDegree(self, vertex):
        """
        Gets the out-degree of a vertex.
        :Preconditions: vertex exists in the graph
        """
        return len(self.__outbound_edges[vertex])

    def getVertices(self):
        """
        Returns an iterator for the vertices.
        :return: iterator for the vertices
        """
        return iter(self.__vertices)

    def getEdges(self):
        """
        Returns an iterator for the edges.
        :return: iterator for the edges
        """
        edges = []
        for source in self.__vertices:
            for target in self.__outbound_edges[source]:
                edges.append((source, target))
        return iter(edges)

    def getInboundEdges(self, vertex):
        """
        Gets the inbound edges of a vertex.
        :Preconditions: vertex exists in the graph
        :return: iterator for the inbound edges of a vertex
        """
        return iter(self.__inbound_edges[vertex])

    def getOutboundEdges(self, vertex):
        """
        Gets the outbound edges of a vertex.
        :Preconditions: vertex exists in the graph
        :return: iterator for the outbound edges of a vertex
        """
        return iter(self.__outbound_edges[vertex])


def load_from_file(filename):
    """
    Loads a graph from a specified file.
    :param filename: name of the file
    :return: the graph
    """
    with open(filename, 'r') as f:
        n = int(f.readline().split()[0])
        # m = int(f.readline().split()[1])
        graph = DirectedGraph(n)
        for line in f:
            source = int(line.split()[0])
            target = int(line.split()[1])
            cost = int(line.split()[2])
            graph.addEdge(source, target, cost)

        f.close()
        return graph


def save_to_file(graph, filename):
    """
    Saves a graph to a specified file.
    :param graph: the graph
    :param filename: name of the file
    """
    with open(filename, 'w') as f:
        f.write(str(graph.getNumVertices()) + ' ' + str(graph.getTotalNumEdges()) + '\n')
        for edge in graph.getEdges():
            source = edge[0]
            target = edge[1]
            cost = graph.getCost(source, target)
            f.write(str(source) + ' ' + str(target) + ' ' + str(cost) + '\n')

        f.close()


def generate_random_graph(n, m):
    """
    Generates a random graph with n vertices and m edges.
    :param n: number of vertices
    :param m: number of edges
    :return: the generated graph
    """
    graph = DirectedGraph(n)
    if m > n*(n-1):
        raise (ValueError("Too many edges"))
    for i in range(m):
        source = randint(0, n-1)
        target = randint(0, n-1)
        while graph.isEdge(source, target):
            source = randint(0, n-1)
            target = randint(0, n-1)
        cost = randint(1, 100)
        graph.addEdge(source, target, cost)
    return graph
