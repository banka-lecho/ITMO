# версия указанного пакета устарела. я попробовала еще пару вариантов, но их нельзя импортировать на степике
matrix = [
    [4, 0, -2, -1, -2, 0, -2, -1, -1, -1, -1, -2, -1, -1, -1, 1, 0, 0, -3, -2],
    [0, 9, -3, -4, -2, -3, -3, -1, -3, -1, -1, -3, -3, -3, -3, -1, -1, -1, -2, -2],
    [-2, -3, 6, 2, -3, -1, -1, -3, -1, -4, -3, 1, -1, 0, -2, 0, -1, -3, -4, -3],
    [-1, -4, 2, 5, -3, -2, 0, -3, 1, -3, -2, 0, -1, 2, 0, 0, -1, -2, -3, -2],
    [-2, -2, -3, -3, 6, -3, -1, 0, -3, 0, 0, -3, -4, -3, -3, -2, -2, -1, 1, 3],
    [0, -3, -1, -2, -3, 6, -2, -4, -2, -4, -3, 0, -2, -2, -2, 0, -2, -3, -2, -3],
    [-2, -3, -1, 0, -1, -2, 8, -3, -1, -3, -2, 1, -2, 0, 0, -1, -2, -3, -2, 2],
    [-1, -1, -3, -3, 0, -4, -3, 4, -3, 2, 1, -3, -3, -3, -3, -2, -1, 3, -3, -1],
    [-1, -3, -1, 1, -3, -2, -1, -3, 5, -2, -1, 0, -1, 1, 2, 0, -1, -2, -3, -2],
    [-1, -1, -4, -3, 0, -4, -3, 2, -2, 4, 2, -3, -3, -2, -2, -2, -1, 1, -2, -1],
    [-1, -1, -3, -2, 0, -3, -2, 1, -1, 2, 5, -2, -2, 0, -1, -1, -1, 1, -1, -1],
    [-2, -3, 1, 0, -3, 0, 1, -3, 0, -3, -2, 6, -2, 0, 0, 1, 0, -3, -4, -2],
    [-1, -3, -1, -1, -4, -2, -2, -3, -1, -3, -2, -2, 7, -1, -2, -1, -1, -2, -4, -3],
    [-1, -3, 0, 2, -3, -2, 0, -3, 1, -2, 0, 0, -1, 5, 1, 0, -1, -2, -2, -1],
    [-1, -3, -2, 0, -3, -2, 0, -3, 2, -2, -1, 0, -2, 1, 5, -1, -1, -3, -3, -2],
    [1, -1, 0, 0, -2, 0, -1, -2, 0, -2, -1, 1, -1, 0, -1, 4, 1, -2, -3, -2],
    [0, -1, -1, -1, -2, -2, -2, -1, -1, -1, -1, 0, -1, -1, -1, 1, 5, 0, -2, -2],
    [0, -1, -3, -2, -1, -3, -3, 3, -2, 1, 1, -3, -2, -2, -3, -2, 0, 4, -3, -1],
    [-3, -2, -4, -3, 1, -2, -2, -3, -3, -2, -1, -4, -4, -2, -3, -3, -2, -3, 11, 2],
    [-2, -2, -3, -2, 3, -3, 2, -1, -2, -1, -1, -2, -3, -1, -2, -2, -2, -1, 2, 7]
]
score_gap = -5


class NWBlossumAlgorithm:
    matrix_f = None
    matrix = None
    S, X, D = 0, 0, 0

    def __init__(self, missmatch=-1, gap=-2, match=1, matrix=None):
        self.S = match
        self.X = missmatch
        self.D = gap
        self.matrix = matrix

    def update_matrix(self, i: int, j: int, s: str, t: str):
        if self.matrix is None:
            return self.S if s[i - 1] == t[j - 1] else self.X
        else:
            letters = 'ACDEFGHIKLMNPQRSTVWY'
            indices = range(20)
            get_ind = dict(zip(letters, indices))

            s_indexes = get_ind[s[i - 1]]
            t_indexes = get_ind[t[j - 1]]
            return self.matrix[s_indexes][t_indexes]

    def calc_matrix_F(self, n: int, m: int, s: str, t: str):
        self.matrix_f[0][0] = 0
        for j in range(m + 1):
            self.matrix_f[0][j] = self.D * j

        for i in range(n + 1):
            self.matrix_f[i][0] = self.D * i

        for i in range(1, n + 1):
            for j in range(1, m + 1):
                self.matrix_f[i][j] = max(
                    self.matrix_f[i - 1][j - 1] + self.update_matrix(i, j, s, t),
                    self.matrix_f[i][j - 1] + self.D,
                    self.matrix_f[i - 1][j] + self.D
                )

    def get_aligning(self, n: int, m: int, s: str, t: str):
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
                if self.matrix_f[i][j] == self.matrix_f[i - 1][j - 1] + self.update_matrix(i, j, s, t):
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

    def align(self, s: str, t: str):
        n, m = len(s), len(t)
        self.matrix_f = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
        self.calc_matrix_F(n, m, s, t)
        AlignmentA, AlignmentB = self.get_aligning(n, m, s, t)
        print(AlignmentA)
        print(AlignmentB)


s = str(input())
t = str(input())
if len(s) < len(t):
    temp = s
    s = t
    t = temp
NWBlossumAlgorithm(matrix=matrix, gap=score_gap).align(s, t)
