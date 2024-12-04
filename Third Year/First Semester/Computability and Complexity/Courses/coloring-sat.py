from pysat.solvers import Minisat22
from pysat.formula import CNF, CNFPlus, IDPool


def main():
   
    vertices= [1,2,3]
    edges=[[1,2],[2,3],[1,3]]
    #vertices = [1,2,3,4]
    #edges=[[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
    no_colors=3



    cnf = CNF()
    vpool = IDPool(start_from=1)

    
    colors = lambda i,j: vpool.id('x{0}@{1}'.format(i,j))

    for i in vertices:
        cnf.append([colors(i,j) for j in range(no_colors)])

    for i in vertices:
        for j in range(no_colors):
            for k in range(j+1,no_colors):
                cnf.append([-colors(i,j),-colors(i,k)])  

    for [i,j] in edges:
        for k in range(no_colors):
            cnf.append([-colors(i,k),-colors(j,k)])
                                  
    print("formula:")
    print(cnf.clauses)
    
    with Minisat22(bootstrap_with=cnf.clauses) as l:  

        if l.solve()== True: 
            print("colorable.")
            print(l.get_model())
            m=l.get_model()
            print("coloring:")

            for i in vertices:
                for j in range(no_colors):
                    if(colors(i,j) in m):
                        print("color of ",i,": ",j)
        else:
            print("uncolorable.")

#g.add_clause([1,2])
#g.add_clause([-1,-2])

#print(g.solve())

#print(g.get_model())

#if __name__ == '__main__':
main()
