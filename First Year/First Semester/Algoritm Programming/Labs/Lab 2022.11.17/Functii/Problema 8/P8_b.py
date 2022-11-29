def function(x,*args):
    global rez
    rez = 0
    for i in args:
        if x in i:
            rez += 1
    return rez 

rez = None
function(3,[1,5,7],[3],[1,8,3],[])
print(rez)
