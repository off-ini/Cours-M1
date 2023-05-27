import string

liste = ["Fr2","O4"] 

def atomeOBJ():
    ligne=" "
    tab = []
    with open('Atomes.txt','r') as atomeFile:
        while ligne !="":
            if(ligne !=' '):
                ligne.strip()
                tab.append(ligne.split('*'))
            ligne = atomeFile.readline() 
    return tab


def giveAtomeFormule():
    Obj = {}
    tab = atomeOBJ()
    for i in range(len(tab)):
        MasseAtomique = tab[i][1]
        Obj[tab[i][0]]=MasseAtomique.replace('\n','')
    return Obj


def moleculeOBJ():
    tab =[]
    ligne =" "
    with open('Molecules.txt','r') as moleculeFile:
        while ligne !="":
            if(ligne !=' '):
                ligne.strip()
                tab.append(ligne.split('*'))
            ligne = moleculeFile.readline()
    return tab    

def giveMoleculeFormule():
    tabfor = []
    tabMolecule = moleculeOBJ()

    for i in range(len(tabMolecule)):
        tabfor.append(tabMolecule[i][1])
    return tabfor[0]

def isMaj(j):
    boo = False
    for i in string.ascii_uppercase:
        if(j==i):
            boo = True

    return boo

def isInt(j):
    boo = False
    for i in string.digits:
        if(j==i):
            boo = True

    return boo

def spliteFormule():
    formule = giveMoleculeFormule()
    tabformule = []
    j=0
    for i in formule:
        if(isMaj(i)):
            j= len(tabformule)
            tabformule.append(i)
        else:
            tabformule[j]=""+tabformule[j]+i+""
    return tabformule

def compteNbr():
        dic = {}
        tab = spliteFormule()
        i:str
        for i in tab:
            if(isInt(i[-1])):
                dic[i.replace(i[-1],'')] = i[-1]
               
        return dic            


def massseMoleculaire():
    dic = compteNbr()
    Atome  = giveAtomeFormule()
    M = 0
    for i in dic :
        if((i in dic.keys())and (i in Atome.keys())):
            # print(dic[i]+"*"+Atome[i])
            M+= (int(dic[i])*int(Atome[i]))
            
    return M

print(massseMoleculaire())
print(compteNbr())
print(giveAtomeFormule())
