def max_paired_bases(rna_sequence: str):
    n = len(rna_sequence)
    matrix_f = [[0] * n for _ in range(n)]
    return matrix_f


def compare(dict_base: dict, a: int, b: int) -> int:
    if dict_base[a] == b:
        return 1
    else:
        return 0


def fill_matrix_f(dict_base: dict, n: int, matrix_f, rna_sequence: str) -> None:
    previous_j = 2
    for i in range(n - 1):
        matrix_f[i][i + 1] = 0
    i, j = 0, 2
    while not (j == n and i == 0):
        d = 0
        for k in range(i, j):
            d = max(d, matrix_f[i][k] + matrix_f[k + 1][j])
        matrix_f[i][j] = max(matrix_f[i + 1][j - 1] + compare(dict_base, rna_sequence[i], rna_sequence[j]), d)
        j += 1
        i += 1
        if j == n:
            j = previous_j + 1
            i = 0
            previous_j += 1
    print(matrix_f[0][n - 1])


dict_base = {'G': 'C', 'A': 'U', 'C': 'G', 'U': 'A'}
rna_sequence = str(input())
n = len(rna_sequence)
matrix_f = max_paired_bases(rna_sequence)
fill_matrix_f(dict_base, n, matrix_f, rna_sequence)
