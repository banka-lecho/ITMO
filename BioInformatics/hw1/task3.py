class WeighteNWBlossumAlgorithm:
    def __init__(self, match=1, missmatch=-1, count_open=0, count_cont=0):
        self._match = match
        self.missmatch = missmatch
        self.main = None
        self.upper = None
        self.lower = None
        self.count_open = count_open
        self.count_cont = count_cont

    def init_parts_matrix(self, n: int, m: int) -> None:
        self.lower = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
        self.main = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
        self.upper = [[0 for _ in range(m + 1)] for _ in range(n + 1)]

    def update_upper_lower_matrix(self, i: int, j: int) -> None:
        # Обработка верхней матрицы
        inf = 1e9
        if i == 0:
            self.upper[i][j] = -inf
        else:
            self.upper[i][j] = max(
                self.upper[i - 1][j] + self.count_cont,
                self.main[i - 1][j] + self.count_open + self.count_cont
            )

        # Обработка нижней матрицы
        if j == 0:
            self.lower[i][j] = -inf
        else:
            self.lower[i][j] = max(
                self.lower[i][j - 1] + self.count_cont,
                self.main[i][j - 1] + self.count_open + self.count_cont
            )

    def calc_matrix_F(self, n: int, m: int, s: str, t: str) -> None:
        self.main[0][0] = 0
        for i in range(n + 1):
            for j in range(m + 1):
                self.update_upper_lower_matrix(i, j)
                # Обработка основной матрицы
                if i == 0 and j == 0:
                    continue
                self.main[i][j] = (self.lower[i][j] if i == 0 else
                                   self.upper[i][j] if j == 0 else
                                   max(
                                       self.main[i - 1][j - 1] + (
                                           self._match if s[i - 1] == t[j - 1] else self.missmatch),
                                       self.upper[i][j],
                                       self.lower[i][j]
                                   ))

    def align(self, s, t) -> None:
        n, m = len(s), len(t)
        self.init_parts_matrix(n, m)
        self.calc_matrix_F(n, m, s, t)


s = str(input())
t = str(input())
if len(s) < len(t):
    temp = s
    s = t
    t = temp

gap_open, gap_cont = map(int, input().split())
solver = WeighteNWBlossumAlgorithm(match=1, missmatch=-1, count_open=gap_open, count_cont=gap_cont)
solver.align(s, t)
print(solver.main[-1][-1])
