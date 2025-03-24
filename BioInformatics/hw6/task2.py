alphabet = ['A', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'Y']
masses = [71, 103, 115, 129, 147, 57, 137, 113, 128, 113, 131, 114, 97, 128, 156, 87, 101, 99, 186, 163]


class FindPeptide:
    def __init__(self, spectrum, g):
        self.g = g
        self.paths = []
        self.spectrum = spectrum

    def comp_a_b(self, a, b):
        if len(a) != len(b):
            return False

        for i in range(len(a)):
            if a[i] != b[i]:
                return False
        return True

    @staticmethod
    def calc_mass(acid):
        ind = alphabet.index(acid)
        return masses[ind]

    def get_spectrum(self, s):
        n = len(s)
        spec = {0}
        mass_pref = [0 for _ in range(n)]
        mass_pref[0] = self.calc_mass(s[0])

        for i in range(1, n):
            mass_pref[i] = mass_pref[i - 1] + self.calc_mass(s[i])
        mass_suff = [0 for _ in range(n)]
        mass_suff[-1] = self.calc_mass(s[-1])

        for i in range(n - 2, -1, -1):
            mass_suff[i] = mass_suff[i + 1] + self.calc_mass(s[i])

        spec.update(mass_pref)
        spec.update(mass_suff)
        return sorted(spec)

    def dfs(self, v, cur_path):
        if v == len(self.g) - 1:
            peptide = cur_path
            if self.comp_a_b(list(self.get_spectrum(peptide)), self.spectrum):
                return peptide
            return None

        for to, acid in self.g[v]:
            new_path = cur_path + acid
            self.paths.append(new_path)
            out = self.dfs(to, new_path)
            if out is not None:
                return out

    def run_finder(self):
        return self.dfs(0, '')


spectrum = list(map(int, input().split()))
n = len(spectrum)
g = [[] for _ in range(n)]
for i in range(n - 1):
    for j in range(i + 1, n):
        diff = spectrum[j] - spectrum[i]
        try:
            ind = masses.index(diff)
        except ValueError:
            continue
        acid = alphabet[ind]
        g[i].append((j, acid))

finder = FindPeptide(spectrum, g)
pep = finder.run_finder()
print(pep)
