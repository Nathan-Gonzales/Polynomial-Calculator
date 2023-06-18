#include <cstdlib>
#include <iostream>

#include "term.h"



void release(term *t){
    term* temp1 = t;
    term* temp2;
    while(temp1 != NULL){
        temp2 = temp1->next;
        delete temp1;
        temp1 = temp2;
    }//end while
    t = NULL;
}//end release

void print_terms(term *t){
    term* temp = t;

    while(temp != NULL){
        
        if(temp->exp == 0 || temp->coe == 0){
            std::cout << temp->coe;
            
        }
        else{
            std::cout << temp->coe << "x^" << temp->exp << " + ";
        }
        temp = temp->next;
    }//end while
    std::cout << std::endl;
    
}


term* dup_terms(term *t){
    term* temp1 = t;
    term* head = new term(temp1->exp, temp1->coe);
    term* temp2;
    temp2 = head;
    temp1 = temp1->next;
    while(temp1 != NULL){
        term* temp3 = new term(temp1->exp, temp1->coe);
        temp2->next = temp3;
        temp2 = temp3;
        temp1 = temp1->next;
    }//end while
    return head;
}//end dup_terms

term* add(term* a, term* b){
    term* head = new term(0, 0);
    term* temp1 = head;
    term* temp2;
    term* temp3;
    term* tempa = a;
    term* tempb = b;

    while(tempa != NULL && tempb != NULL){
        if(tempa->exp == tempb->exp){
            temp2 = new term(tempb->exp, (tempa->coe + tempb->coe));
            tempa = tempa->next;
            tempb = tempb->next;
        }//end if
        else if(tempa->exp > tempb->exp){
            temp2 = new term(tempa->exp, tempa->coe);
            tempa = tempa->next;
        }//end else if
        else{ //if a->exp < b->exp only possible case left
            temp2 = new term(tempb->exp, tempb->coe);
            tempb = tempb->next;
        }//end else
        temp1->next = temp2;
        temp1 = temp2;
    }//end first while
    
    while(tempa != NULL){
        temp3 = new term(tempa->exp, tempa->coe);
        temp2->next = temp3;
        temp2 = temp3;
        tempa = tempa->next;
    }//end second while
    
    while(tempb != NULL){
        temp3 = new term(tempb->exp, tempb->coe);
        temp2->next = temp3;
        temp2 = temp3;
        tempb = tempb->next;
    }//end second while
    temp2 = head;
    temp1 = temp2->next;
    delete temp2;
    head = temp1;
    return head;
    
}//end add

term* build_poly(int size, double coef[], int expon[]){
    term* temp1 = new term(expon[0], coef[0]);
    
    for(int i = 1; i < size ; i++){
        term* temp2 = new term(expon[i], coef[i], temp1);
        temp1 = temp2;
    }
    return temp1;
    
}//end build_poly


term* combineLikeTerms(term* t){
    term* head = new term(0, 0);
    term* temp1 = head;
    term* temp2 = t;
    term* temp3;
    term* temp4;
    
    
    while(temp2 != NULL){
        temp3 = temp2->next;
        temp4 = temp2;
        double tempCoefSum = temp2->coe;
        
        while(temp3 != NULL){
            if(temp2->exp == temp3->exp){
                tempCoefSum += temp3->coe;
                temp4->next = temp3->next;
                delete temp3;
                temp3 = temp4->next;
            }//end if
            else{
                temp4 = temp4->next;
                temp3 = temp3->next;
            }//end else
        }//end inner while
        
        temp1->next = new term(temp2->exp, tempCoefSum);
        temp2 = temp2->next;
        temp1 = temp1->next;
    }//end outer while
    
    release(t);
    
    temp2 = head;
    temp1 = temp2->next;
    delete temp2;
    head = temp1;
    
    return head;
    
    
}//end combineLikeTerms

term* sort(term* a){
    term* temp = a;
    int lenCount = 0;
    
    while(temp != NULL){
        temp = temp->next;
        lenCount++;
    }//end count while
    
    int everyExp[lenCount];
    temp = a;
    
    int i = 0;
    while(temp != NULL){
        everyExp[i] = temp->exp;
        temp = temp->next;
        i++;
    }//end store while
    
    
    int compare = 0;
    int tempExp = 0;
    bool correct = false;
    while(!correct){
        i = 0;
        compare = 1;
        correct = true;
        while(compare < lenCount){
            if(everyExp[i] < everyExp[compare]){
                tempExp = everyExp[compare];
                everyExp[compare] = everyExp[i];
                everyExp[i] = tempExp;
                correct = false;
            }//end if
            i++;
            compare++;
        }//end inner while
    }//end outer while
    
    
    term* head = new term(0, 0);
    term* temp1;
    term* temp2 = head;
    term* temp3;
    int j = 0;
    while(j < lenCount){
        temp1 = a;
        while(temp1 != NULL){
            if(everyExp[j] == temp1->exp){
                temp3 = new term(temp1->exp, temp1->coe);
                temp2->next = temp3;
                temp2 = temp3;
                break;
            }//end if
            temp1 = temp1->next;
        }//end inner while
        j++;
    }//end outer while
    
    
    release(a);
    
    temp2 = head;
    temp1 = temp2->next;
    delete temp2;
    head = temp1;
    
    return head;
    
    
}//end sort


term* mult(term *t, double coef, int expon){
    term* temp1 = new term((expon + t->exp), (coef * t->coe));
    return temp1;
}//end mult


term* mult_terms(term *a, term *b){
    term* head = new term(0, 0);
    term* temp1 = head;
    term* temp2;
    term* tempa = a;
    term* tempb;
    
    while(tempa != NULL){
        tempb = b;
        while(tempb != NULL){
            temp2 = mult(tempa, tempb->coe, tempb->exp);
            tempb = tempb->next;
            temp1->next = temp2;
            temp1 = temp2;
        }//end inner while
        tempa = tempa->next;
    }//end outer while
    
    //moves head to beginning of list
    temp2 = head;
    temp1 = temp2->next;
    delete temp2;
    head = temp1;
    
    
    //combines like terms
    head = combineLikeTerms(temp1);
    
    //sort in ascending order
    head = sort(head);
    
    return head;
    
}//end mult_terms


