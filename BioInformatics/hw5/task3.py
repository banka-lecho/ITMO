# промоутер/непромоутер
A = [[0.9, 0.1], [0.2, 0.8]]
B = [{'C': 0.4, 'G': 0.4, 'T': 0.1, 'A': 0.1}, {'C': 0.2, 'G': 0.2, 'T': 0.3, 'A': 0.3}]


def fill_alpha(A, B, times):
    alpha = [[0] * (times + 1) for _ in range(2)]
    for j in range(2):
        alpha[j][1] = 0.5 * B[j][O[1]]

    for t in range(2, times + 1):
        for j in range(2):
            for i in range(2):
                alpha[j][t] += alpha[i][t - 1] * A[i][j] * B[j][O[t]]
    return alpha


def fill_beta(A, B, times):
    beta = [[0] * (times + 1) for _ in range(2)]

    beta[0][times], beta[1][times] = 1, 1
    for i in range(2):
        beta[i][times - 1] = B[0][O[times]] * A[i][0] + B[1][O[times]] * A[i][1]

    for t in range(times - 2, 0, -1):
        for j in range(2):
            for i in range(2):
                beta[j][t] += beta[i][t + 1] * B[i][O[t + 1]] * A[j][i]
    # return beta


def fill_rho(beta, alpha, times):
    summ = alpha[0][times] + alpha[1][times]
    rho = [[0] * (times + 1) for _ in range(2)]
    for t in range(1, times + 1):
        for j in range(2):
            rho[j][t] = beta[j][t] * alpha[j][t] / summ
    return rho


def print_result(rho, times):
    for i in range(2):
        for t in range(1, times + 1):
            print(f'{rho[i][t]:.2f}', end=' ')
        print()


s = str(input())
T = len(s)
O = ' ' + s

alpha = fill_alpha(A, B, T)
beta = fill_beta(A, B, T)
rho = fill_rho(beta, alpha, T)
print_result(rho, T)
