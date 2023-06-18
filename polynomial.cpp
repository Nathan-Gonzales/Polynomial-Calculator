#include "polynomial.h"
#include <iostream>


polynomial::polynomial() : h(NULL) {
    
}

polynomial::polynomial(const polynomial& p){
    h = dup_terms(p.h);
}

polynomial::polynomial(int size, double coef[], int expon[]){
    // possibly add check here for if expon[0] not < expon[1] etc
    h = build_poly(size, coef, expon);
}


polynomial::~polynomial(){
    release(h);
}


void polynomial::plus(polynomial a, polynomial b){
    h = add(a.h, b.h);
}


void polynomial::multiply(polynomial a, polynomial b){
    h = mult_terms(a.h, b.h);
}

int polynomial::degree() const{
    return h->exp;
}

bool polynomial::isZero() const{
    term* temp = h;

    bool zero = true;
    int count = 0;
    int totCount = 0;
    while(temp != NULL){
        totCount++;
        if(temp->coe == 0){
            count++;
        }
        temp = temp->next;
    }//end while
    if(count == totCount){
        zero = true;
    }
    else{
        zero = false;
    }
    return zero;
}

void polynomial::print()  const{
    if(this->isZero()){
        std::cout << "0" << std::endl;
    }
    else{
        print_terms(h);
    }
}//end print()


