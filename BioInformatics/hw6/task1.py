def get_theoretical_spectrum():
    for i in range(1, n):
        pref_mass[i] = pref_mass[i - 1] + calc_mass(s[i])

    suf_mass = [0 for _ in range(n)]
    suf_mass[-1] = calc_mass(s[-1])
    for i in range(n - 2, -1, -1):
        suf_mass[i] = suf_mass[i + 1] + calc_mass(s[i])

    spectrum.update(pref_mass)
    spectrum.update(suf_mass)
    return sorted(spectrum)


def calc_mass(acid):
    ind = alphabet.index(acid)
    return masses[ind]


alphabet = ['A', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'Y']
masses = [71, 103, 115, 129, 147, 57, 137, 113, 128, 113, 131, 114, 97, 128, 156, 87, 101, 99, 186, 163]
s = str(input())
n = len(s)
spectrum = {0}
pref_mass = [0 for _ in range(n)]
pref_mass[0] = calc_mass(s[0])
ideal_spec = get_theoretical_spectrum()
print(*ideal_spec)
