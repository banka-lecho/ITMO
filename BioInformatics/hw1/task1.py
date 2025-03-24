class NWAlgorithm:
    matrix_f = None
    S, X, D = 0, 0, 0

    def __init__(self, missmatch=-1, gap=-2, match=1):
        self.S = match
        self.X = missmatch
        self.D = gap

    def calc_matrix_F(self, s: str, t: str, n: int, m: int) -> None:
        self.matrix_f[0][0] = 0
        for j in range(m + 1):
            self.matrix_f[0][j] = self.D * j

        for i in range(n + 1):
            self.matrix_f[i][0] = self.D * i

        for i in range(1, n + 1):
            for j in range(1, m + 1):
                self.matrix_f[i][j] = max(
                    self.matrix_f[i - 1][j - 1] + (self.S if s[i - 1] == t[j - 1] else self.X),
                    self.matrix_f[i][j - 1] + self.D,
                    self.matrix_f[i - 1][j] + self.D
                )

    def get_aligning(self, s: str, t: str, n: int, m: int):
        new_s, new_t = "", ""
        i, j = n, m
        while True:
            if i == 0 and j == 0:
                break
            elif i == 0:
                new_s += '-'
                new_t += t[j - 1]
                j -= 1
            elif j == 0:
                new_s += s[i - 1]
                new_t += '-'
                i -= 1
            else:
                if self.matrix_f[i][j] == self.matrix_f[i - 1][j - 1] + (self.S if s[i - 1] == t[j - 1] else self.X):
                    new_s += s[i - 1]
                    new_t += t[j - 1]
                    i -= 1
                    j -= 1
                elif self.matrix_f[i][j] == self.matrix_f[i][j - 1] + self.D:
                    new_s += '-'
                    new_t += t[j - 1]
                    j -= 1
                else:
                    new_s += s[i - 1]
                    new_t += '-'
                    i -= 1
        return new_s[::-1], new_t[::-1]

    def align(self, s, t):
        n, m = len(s), len(t)
        self.matrix_f = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
        self.calc_matrix_F(s, t, n, m)
        AlignmentA, AlignmentB = self.get_aligning(s, t, n, m)
        print(AlignmentA)
        print(AlignmentB)


s = str(input())
t = str(input())
if len(s) > len(t):
    temp = s
    s = t
    t = temp
NWAlgorithm().align(s, t)
