def remplireAtome(N):
    f = open('Atomes.txt', 'a')
    for i in range(N):
        atome = input('saisir le nom d’atome')
        masse = input('saisir la masse molaire')
        ligne = atome+'*'+masse + '\n'
        f.write(ligne)
    f.close()

def dictionnaire(fichier):
    code = open(fichier,'r')
    dic = {}
    tout = code.read()
    lignes = tout.split('\n')
    for i in lignes:
        c = i.strip()
        l = c.split('*')
        cle = l[0]
        dic[cle] = l[1]
    code.close()
    return dic

def massAtome():
    dic = dictionnaire('Atomes.txt')
    source = open('Molecules.txt','r')
    dest = open('Resultats.txt', 'a')
    tout = source.read()
    lignes = tout.split('\n')
    for ligne in lignes:
        c = ligne.strip()
        l = c.split('*')
        atome = ''
        nb = ''
        estnombre = False
        masse = 0
        for lettre in l[1]:
            if 'A' <= lettre <= 'Z' or 'a' <= lettre <= 'z':
                if (atome != '') and ('A' <= lettre <= 'Z') and not estnombre:
                    masse += int(dic[atome])
                    atome = ''
                    nb = ''
                    estnombre = False
                if estnombre == True:
                    masse += int(dic[atome])*int(nb)
                    atome = ''
                    nb = ''
                    estnombre = False
                atome += lettre
            else:
                estnombre = True
                nb += lettre
        if 'A' <= l[1][-1] <= 'Z':
            nb = '1'
        masse += int(dic[atome])*int(nb)
        dest.write(l[1]+':'+str(masse)+'\n')

if __name__ == '__main__':
    #remplireAtome(4)
    massAtome()