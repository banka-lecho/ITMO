def comp(a, b):
    d1 = {'A': 'U', 'U': 'A', 'G': 'C', 'C': 'G'}
    if d1[a] == b:
        return 1
    return 0


def RNA():
    s = input()
    n = len(s)
    if n == 1:
        print('.')
        return
    if n == 2:
        if comp(s[0], s[1]):
            print("()")
        else:
            print("..")
        return
    if n == 3:
        if comp(s[0], s[1]):
            print("().")
            return
        if comp(s[1], s[2]):
            print(".()")
            return
    N = [[0] * n for _ in range(n)]
    path = [[-3] * n for _ in range(n)]
    for i in range(n - 1):
        N[i][i + 1] = 0
    i = 0
    j = 2
    prev_j = 2
    while not (i == 0 and j == n):
        d = 0
        k_ind = -2
        for k in range(i, j):
            if N[i][k] + N[k + 1][j] > d:
                d = N[i][k] + N[k + 1][j]
                k_ind = k
        e = N[i + 1][j - 1] + comp(s[i], s[j])
        if e > d:
            N[i][j] = e
            if comp(s[i], s[j]):
                path[i][j] = -1
        else:
            N[i][j] = d
            path[i][j] = k_ind
        i += 1
        j += 1
        if j == n:
            i = 0
            j = prev_j + 1
            prev_j += 1
    # for i in range(n):
    #     print(*N[i])
    # print(N[0][n-1])
    # for i in range(n):
    #     print(*path[i])
    res = restore_path(path=path, s=s, n=n, i=0, j=n - 1)
    print(res)


# TODO: using N restore the answer


def restore_path(path, s, n, i, j):
    if path[i][j] == -3 or path[i][j] == -2:
        return '.' * (j - i + 1)
    if path[i][j] == -1:
        return '(' + restore_path(path, s, n, i + 1, j - 1) + ')'
    assert path[i][j] >= 0
    k = path[i][j]
    return restore_path(path, s, n, i, k) + restore_path(path, s, n, k + 1, j)


RNA()
