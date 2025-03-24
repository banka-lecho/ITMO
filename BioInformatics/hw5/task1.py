def get_answer(s: str):
    len_s = len(s)
    # promoter between non-promoter
    A = [[0.9, 0.1], [0.2, 0.8]]
    # promoter/non-promoter to C, G, A, T
    probs = [{'T': 0.1, 'A': 0.1, 'C': 0.4, 'G': 0.4}, {'T': 0.3, 'A': 0.3, 'C': 0.2, 'G': 0.2}]
    O = ' ' + s
    sig = [[0] * (len_s + 1) for _ in range(2)]

    for j in range(2):
        sig[j][1] = probs[j][O[1]] * 0.5

    for i in range(2, len_s + 1):

        for j in range(2):
            sig[j][i] = sig[1][i - 1] * A[1][j] * probs[j][O[i]] + sig[0][i - 1] * A[0][j] * probs[j][O[i]]

    return sig[0][len_s] + sig[1][len_s]


s = str(input())
print(get_answer(s) + 0.00000000001)
