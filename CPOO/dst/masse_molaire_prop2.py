# Auteur : Sémiat Oyénikè Olaitan
# Date : 15 Février 2022
#
# Ce programme décompose la formule d'une molécule
# En atome et indice pour d'autes utilisations





def decomposition(mol: str):
    mol.strip()
    mol += '*'
    i = 0
    l = {}
    while i < len(mol) - 1:
        nb = 1
        if mol[i].isupper():
            ch = mol[i]
            if mol[i+1].islower():
                ch += mol[i+1]
                i += 1
            if mol[i+1].isdigit():
                a = mol[i+1]
                i += 1
                if mol[i + 1].isdigit():
                    a += mol[i + 1]
                    i += 1

                nb = int(a)

            l[ch] = nb

        i += 1
    return l


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    print('Fe2O4', decomposition('Fe2O4'))
    print('CH4', decomposition('CH4'))
    print('CH42O', decomposition('CH42O'))