#include "circular_buffer_queue.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>

void Bubble_sort(size_t* q, int lenght) {
    for (int i = 0; i < lenght-1; i++) {
        for (int j = i + 1; j < lenght; j++) {
            if (q[i] > q[j]) { int tmp=q[i]; q[i]=q[j]; q[j]=tmp;}
        }
    }
}



//Refaire Insetion sort
void Insertion_sort(size_t* q, int lenght, int k) {
    for (int i = k ; i < lenght; i++) {
        for (int j = 0; j < k; j++) {
            if ((q[i - 1 - j] ) > *(q + i - j)) {
                std::swap(*(q + i - 1 - j), *(q + i - j));
            }
        }
    }
}

void Merge(size_t* In, size_t* Out, int p, int q, int r) {
    int i = p;
    int j = q+1;
    for (int k = p; k < r; ++k) {
        if (j == r || (i <= q && In[i]<=In[j])) {
            Out[k]=In[i++];    
        } else {
            Out[k]=In[j++];
        }
    }
    
}

void Merge_sort(size_t* In, size_t* Out, int p, int r) {
    if (p+1 < r) {
        int q = (p + r) / 2;
        Merge_sort(Out, In, p, q);
        Merge_sort(Out, In, q + 1, r);
        Merge(In, Out, p, q, r);
    }
}



int main() {
    int n = 8;
    int l_max = 0;
    size_t elem_size_ = sizeof(size_t);
    size_t capacity_ = 10;
    Queue* q = queue_init(elem_size_, capacity_);
    for (int i=0; i < n; i++) {
        size_t p(rand());
        
        if (p % 2 == 0) { queue_enqueue(q, &p); }
        else { queue_dequeue(q, &p); }
        if (queue_length(q) > l_max) { l_max = queue_length(q); }
    }
    
    
    
    //Test Bubble sort
    Queue* q2 = queue_init(elem_size_, capacity_);
    for (int i=0; i<n; i++){
        size_t p(rand()%10);
        queue_enqueue(q2, &p);
    }
     std::cout <<"q2:    ";
    for(int i = 0 ; i < q2->length ; i++){
        
        std::cout<<*((size_t*)(q2->data)+i)<<" ";
    }
    std::cout <<"\n";
    Bubble_sort((size_t*)q2->data,n);
    std::cout <<"q2:    ";
    for(int i = 0 ; i < q2->length ; i++){
        std::cout<<*((size_t*)(q2->data)+i)<<" ";
    }
    std::cout <<"\n";
    
    
    //Test Bubble Insertion sort
    Queue* q3 = queue_init(elem_size_, capacity_);
    for (int i=0; i<n; i++){
        size_t p(rand()%10);
        queue_enqueue(q3, &p);
    }
     std::cout <<"q3:    ";
    for(int i = 0 ; i < q3->length ; i++){
        
        std::cout<<*((size_t*)(q3->data)+i)<<" ";
    }
    std::cout <<"\n";
    Bubble_sort((size_t*)q3->data,2);
    Bubble_sort((size_t*)q3->data+2,3);
    Insertion_sort((size_t*)q3->data,n,3);
    std::cout <<"q3:    ";
    for(int i = 0 ; i < q3->length ; i++){
        std::cout<<*((size_t*)(q3->data)+i)<<" ";
    }
    std::cout <<"\n";
    
    
    //Test Merge sort
    Queue* q4 = queue_init(elem_size_, capacity_);
    for (int i=0; i<n; i++){
        size_t p(rand()%10);
        queue_enqueue(q4, &p);
    }
     std::cout <<"q4:    ";
    for(int i = 0 ; i < q4->length ; i++){
        
        std::cout<<*((size_t*)(q4->data)+i)<<" ";
    }
    std::cout <<"\n";
    Bubble_sort((size_t*)q4->data,2);
    Bubble_sort((size_t*)q4->data+2,3);
    Queue* q4_1 = queue_init(elem_size_, capacity_);
    memcpy(q4_1->data,q4->data,n*sizeof(size_t));
    Merge_sort((size_t*)q4_1->data,(size_t*)q4->data,0,n);
    std::cout <<"q4:    ";
    for(int i = 0 ; i < q4->length ; i++){
        std::cout<<*((size_t*)(q4->data)+i)<<" ";
    }
    std::cout <<"\n";






    std::cout <<"q1:    "<< l_max << "     "<<*( (size_t*)(q->data)) << "\n";
    return l_max;
}