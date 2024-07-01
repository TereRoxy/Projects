import DirectedGraph as DG


class UI:
    def __init__(self):
        self.__graph = DG.DirectedGraph()

    def run(self):
        while True:
            self.print_menu()
            option = UI.choose_option()
            if option == 0:
                break
            if option == 1:
                self.add_vertex()
            if option == 2:
                self.remove_vertex()
            if option == 3:
                self.add_edge()
            if option == 4:
                self.remove_edge()
            if option == 5:
                print("Number of vertices: ", self.__graph.getNumVertices())
            if option == 6:
                print("Number of edges: ", self.__graph.getTotalNumEdges())
            if option == 7:
                self.check_edge()
            if option == 8:
                self.get_in_degree()
            if option == 9:
                self.get_out_degree()
            if option == 10:
                self.get_outbound_edges()
            if option == 11:
                self.get_inbound_edges()
            if option == 12:
                self.get_cost()
            if option == 13:
                self.set_cost()
            if option == 14:
                self.print_vertices()
            if option == 15:
                self.print_edges()
            if option == 16:
                self.load_graph()
            if option == 17:
                self.save_graph()

    @staticmethod
    def print_menu():
        print("Directed Graph")
        print("1. Add vertex")
        print("2. Remove vertex")
        print("3. Add edge")
        print("4. Remove edge")
        print("5. Get number of vertices")
        print("6. Get number of edges")
        print("7. Check if there is an edge between two vertices")
        print("8. Get in degree of a vertex")
        print("9. Get out degree of a vertex")
        print("10. Get outbound edges of a vertex")
        print("11. Get inbound edges of a vertex")
        print("12. Get the cost of an edge")
        print("13. Set the cost of an edge")
        print("14. Print vertices")
        print("15. Print all edges")
        print("16. Load graph from file")
        print("17. Save graph to file")
        print("0. Exit")

    @staticmethod
    def file_submenu():
        print("ATTENTION! THIS WILL OVERWRITE THE CURRENT GRAPH!")
        print("Choose a file to import the graph from: ")
        print("1. graph1k.txt")
        print("2. graph10k.txt")
        print("3. graph100k.txt")
        print("4. graph1m.txt")
        print("0. Back")

    @staticmethod
    def file_save_submenu():
        print("1. graph1k_modif.txt")
        print("2. graph10k_modif.txt")
        print("3. graph100k_modif.txt")
        print("4. graph1m_modif.txt")
        print("0. Back")

    @staticmethod
    def choose_option(max_option=17):
        while True:
            try:
                option = int(input("Choose an option: "))
                if option < 0 or option > max_option:
                    raise ValueError
                return option
            except ValueError:
                print("Invalid option. Please try again.")

    @staticmethod
    def is_valid_vertex(vertex):
        return 0 <= vertex

    def vertex_exists(self, vertex):
        return vertex in self.__graph.getVertices()

    def add_vertex(self):
        try:
            vertex = int(input("Vertex: "))
            if self.is_valid_vertex(vertex):
                print("Invalid vertex.")
                return
            if not self.vertex_exists(vertex):
                self.__graph.addVertex(vertex)
                print("Vertex added successfully.")
            else:
                print("Vertex already exists.")
        except ValueError:
            print("Invalid input.")

    def remove_vertex(self):
        try:
            vertex = int(input("Vertex: "))
            if self.is_valid_vertex(vertex) and self.vertex_exists(vertex):
                self.__graph.removeVertex(vertex)
                print("Vertex removed successfully.")
            else:
                print("Invalid vertex.")
        except ValueError:
            print("Invalid input.")

    def add_edge(self):
        try:
            source = int(input("Source: "))
            target = int(input("Target: "))
            if not self.vertex_exists(source) or not self.vertex_exists(target):
                print("Invalid edge ends.")
                return
            if self.__graph.isEdge(source, target):
                print("Edge already exists.")
                return
            self.__graph.addEdge(source, target)
            print("Edge added successfully.")
        except ValueError:
            print("Invalid input.")

    def remove_edge(self):
        try:
            source = int(input("Source: "))
            target = int(input("Target: "))
            if not self.vertex_exists(source) or not self.vertex_exists(target):
                print("Invalid edge ends.")
                return
            if not self.__graph.isEdge(source, target):
                print("Edge doesn't exist.")
                return
            self.__graph.removeEdge(source, target)
            print("Edge removed successfully.")
        except ValueError:
            print("Invalid input.")

    def check_edge(self):
        try:
            source = int(input("Source: "))
            target = int(input("Target: "))
            if not self.vertex_exists(source) or not self.vertex_exists(target):
                print("Invalid edge ends.")
                return
            if self.__graph.isEdge(source, target):
                print("There is an edge between the two vertices.")
            else:
                print("There is no edge between the two vertices.")
        except ValueError:
            print("Invalid input.")

    def get_in_degree(self):
        try:
            vertex = int(input("Vertex: "))
            if not self.vertex_exists(vertex):
                print("Invalid vertex.")
                return
            print("In degree:", self.__graph.getInDegree(vertex))
        except ValueError:
            print("Invalid input.")

    def get_out_degree(self):
        try:
            vertex = int(input("Vertex: "))
            if not self.vertex_exists(vertex):
                print("Invalid vertex.")
                return
            print("Out degree:", self.__graph.getOutDegree(vertex))
        except ValueError:
            print("Invalid input.")

    def get_outbound_edges(self):
        try:
            vertex = int(input("Vertex: "))
            if not self.vertex_exists(vertex):
                print("Invalid vertex.")
                return
            print("Outbound edges:")
            for edge in self.__graph.getOutboundEdges(vertex):
                print(vertex, " ", edge)
        except ValueError:
            print("Invalid input.")

    def get_inbound_edges(self):
        try:
            vertex = int(input("Vertex: "))
            if not self.vertex_exists(vertex):
                print("Invalid vertex.")
                return
            print("Inbound edges:")
            for edge in self.__graph.getInboundEdges(vertex):
                print(edge, " ", vertex)
        except ValueError:
            print("Invalid input.")

    def get_cost(self):
        try:
            source = int(input("Source: "))
            target = int(input("Target: "))
            if not self.vertex_exists(source) or not self.vertex_exists(target):
                print("Invalid edge ends.")
                return
            if not self.__graph.isEdge(source, target):
                print("Edge doesn't exist.")
                return
            print("Cost:", self.__graph.getCost(source, target))
        except ValueError:
            print("Invalid input.")

    def set_cost(self):
        try:
            source = int(input("Source: "))
            target = int(input("Target: "))
            cost = int(input("Cost: "))
            if not self.vertex_exists(source) or not self.vertex_exists(target):
                print("Invalid edge ends.")
                return
            if not self.__graph.isEdge(source, target):
                print("Edge doesn't exist.")
                return
            self.__graph.setCost(source, target, cost)
            print("Cost modified successfully.")
        except ValueError:
            print("Invalid input.")

    def print_vertices(self):
        for vertex in self.__graph.getVertices():
            print(vertex)

    def print_edges(self):
        for edge in self.__graph.getEdges():
            source, target = edge
            print(source, " -> ", target, "cost: ", self.__graph.getCost(source, target))

    def load_graph(self):
        self.file_submenu()
        file_option = self.choose_option(4)
        file_name = ""
        if file_option == 0:
            return
        if file_option == 1:
            file_name = "graph1k.txt"
        if file_option == 2:
            file_name = "graph10k.txt"
        if file_option == 3:
            file_name = "graph100k.txt"
        if file_option == 4:
            file_name = "graph1m.txt"
        self.__graph = DG.load_from_file(file_name)
        print("Graph loaded successfully.")

    def save_graph(self):
        self.file_save_submenu()
        file_option = self.choose_option(4)
        file_name = ""
        if file_option == 0:
            return
        if file_option == 1:
            file_name = "graph1k_modif.txt"
        if file_option == 2:
            file_name = "graph10k_modif.txt"
        if file_option == 3:
            file_name = "graph100k_modif.txt"
        if file_option == 4:
            file_name = "graph1m_modif.txt"
        DG.save_to_file(self.__graph, file_name)
        print("Graph saved successfully.")


graph1 = DG.generate_random_graph(7, 20)
#graph2 = DG.generate_random_graph(6, 40)

DG.save_to_file(graph1, "random_graph1.txt")
#DG.save_to_file(graph2, "random_graph2.txt")

ui = UI()
ui.run()
