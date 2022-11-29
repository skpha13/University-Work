def function(x,*args):
    nr = 0
    for i in args:
        if x in i:
            nr += 1
    return nr

print(function(3,[1,5,7],[3],[1,8,3],[]))
