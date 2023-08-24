#ifndef FUNCIONES_H_
#define FUNCIONES_H

class Funciones {
	public: 
	
    long sumaIterativa(int n){
        int acum=0;
        for(int i=0; i<=n; i++){
            acum += i;
        }
        return acum;
    }
	
    long sumaRecursiva(int n){
        if(n==0) return 0;
	
	    else return n+sumaRecursiva(n-1);
    }
	
    long sumaDirecta(int n){
        int sum = n*(n+1)/2;
        return sum;

    }
};


#endif
