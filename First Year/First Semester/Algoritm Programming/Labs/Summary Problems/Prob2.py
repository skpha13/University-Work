def deviruseaza(prop):
    prop = prop.split()
    
    def schimbare(cuv):
        temp = cuv[-1] + cuv[1:-1] + cuv[0] 
        cuv = temp
        return cuv

    for i in range(len(prop)//2 + 1):
        if i < len(prop)//2:
            temp = schimbare(prop[i])
            prop[i] = schimbare(prop[len(prop)-i-1])
            prop[len(prop)-i-1] = temp
    return prop

print(deviruseaza("aorectc aropozitip este aceasta"))
    