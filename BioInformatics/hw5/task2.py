matrix_trans = [[0.9, 0.1], [0.2, 0.8]]
matrix_emissions = [{'T': 0.1, 'A': 0.1, 'C': 0.4, 'G': 0.4}, {'T': 0.3, 'A': 0.3, 'C': 0.2, 'G': 0.2}]
O = ' '


def calc_probs_moments():
    sig = [[0] * (len_s + 1) for _ in range(2)]
    for j in range(2):
        sig[j][1] = 0.5 * matrix_emissions[j][O[1]]

    for i in range(2, len_s + 1):
        for j in range(2):
            # максимум произведений вероятностей предыдущего состояния, вероятности перехода и вероятности эмиссии
            mult_prev = sig[0][i - 1] * matrix_trans[0][j] * matrix_emissions[j][O[i]]
            mult_next = sig[1][i - 1] * matrix_trans[1][j] * matrix_emissions[j][O[i]]
            sig[j][i] = max(mult_prev, mult_next)
    return sig


def calc_most_prob():
    fi = [['-'] * (len_s + 1) for _ in range(2)]
    for i in range(1, len_s):
        for j in range(2):
            mult_next = sig[0][i] * matrix_trans[0][j] * matrix_emissions[j][O[i]]
            mult_prev = sig[1][i] * matrix_trans[1][j] * matrix_emissions[j][O[i]]
            if mult_next > mult_prev:
                fi[j][i + 1] = 'P'
            else:
                fi[j][i + 1] = 'N'
    return fi


def get_answer():
    hid_states = ['-' for _ in range(1 + len_s)]

    if sig[0][len_s] > sig[1][len_s]:
        hid_states[len_s] = 'P'
    else:
        hid_states[len_s] = 'N'

    for i in range(len_s - 1, 0, -1):
        if hid_states[i + 1] == 'P':
            ind = 0
        else:
            ind = 1
        hid_states[i] = fi[ind][i + 1]
    return ''.join(hid_states[1:])


s = str(input())
O += s
len_s = len(s)
sig = calc_probs_moments()
fi = calc_most_prob()
answer = get_answer()
print(answer)
