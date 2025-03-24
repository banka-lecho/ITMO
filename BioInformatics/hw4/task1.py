class Finder:
    def __init__(self, count_of_vertexes, count_of_edges):
        self.graph = []
        for i in range(count_of_vertexes):
            self.graph.append([])

        self.vertex_count = count_of_vertexes
        self.count_of_edges = count_of_edges

    def find_cycle(self):
        stack, result = [0], []
        while len(stack) != 0:
            neighs = self.graph[stack[-1]]
            if len(neighs) == 0:
                if stack[-1] == 6:
                    stack[-1] = 5
                result.append(stack[-1])
                stack.pop()
            else:
                to = neighs.pop()
                stack.append(to)

        return [result[i] + 1 for i in range(len(result) - 1, -1, -1)]

    def init_edges(self, edges):
        for edge in edges:
            v, to = edge
            v -= 1
            to -= 1
            self.graph[v].append(to)


def get_answer(count_of_vertexes, count_of_edges):
    edges = []
    for _ in range(count_of_edges):
        v, to = map(int, input().split())
        edges.append([v, to])

    finder = Finder(count_of_vertexes, count_of_edges)
    finder.init_edges(edges)
    cycle = finder.find_cycle()
    [print(c, end=" ") for c in cycle[:-1]]


count_of_vertexes, count_of_edges = map(int, input().split())
get_answer(count_of_vertexes, count_of_edges)
