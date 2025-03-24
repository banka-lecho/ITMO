dict_base = {'G': 'C', 'A': 'U', 'C': 'G', 'U': 'A'}


def update_path(path, s, n, i, j):
    if path[i][j] == -1:
        return '(' + update_path(path, s, n, i + 1, j - 1) + ')'

    if path[i][j] == -3 or path[i][j] == -2:
        return (j - i + 1) * '.'

    k = path[i][j]
    return update_path(path, s, n, i, k) + update_path(path, s, n, k + 1, j)


def compare(a: int, b: int) -> int:
    if dict_base[a] == b:
        return 1
    else:
        return 0


def update_d(i: int, j: int, d: int, matrix_f):
    index_k = -2
    for k in range(i, j):
        if matrix_f[i][k] + matrix_f[k + 1][j] > d:
            index_k = k
            d = matrix_f[i][k] + matrix_f[k + 1][j]

    return d, matrix_f, index_k


def update_e(i, j, d, index_k, matrix_f, path):
    e = matrix_f[i + 1][j - 1] + compare(s[i], s[j])
    if e > d:
        matrix_f[i][j] = e
        if compare(s[i], s[j]):
            path[i][j] = -1
    else:
        matrix_f[i][j] = d
        path[i][j] = index_k
    return matrix_f, path, e, d


def get_RNA(s, n, matrix_f, path):
    i, j, prev_j = 0, 2, 2
    while not (i == 0 and j == n):
        d = 0
        d, matrix_f, index_k = update_d(i, j, d, matrix_f)
        matrix_f, path, e, d = update_e(i, j, d, index_k, matrix_f, path)

        i += 1
        j += 1
        if j == n:
            i = 0
            j = prev_j + 1
            prev_j += 1

    res = update_path(path, s, n, 0, n - 1)
    print(res)


def init_matrix_f_and_paths(n: int):
    p = [[-3] * n for _ in range(n)]
    matrix_f = [[0] * n for _ in range(n)]
    for i in range(n - 1):
        matrix_f[i][i + 1] = 0
    return matrix_f, p


s = str(input())
n = len(s)
matrix_f, path = init_matrix_f_and_paths(n)
get_RNA(s, n, matrix_f, path)
