#include <stdio.h>
#include <stdlib.h>
#include "Network Mapping.h"


int strchk(char* s1, char* s2) {
    int i = 0;
    while (!(i = *(unsigned char *) s1 - *(unsigned char *) s2) && *s2) {
        ++s1;
        ++s2;
    }
    if (i == 0)
        return 0;
    else 
        return 1;
}


void free_flatlist(Flat* head) {
    Flat *curr, *temp;
    curr = head;
    while (curr) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    return;
}


Apartment* add_apartment(Apartment* head, int index, char* apartment_name, int max_bandwidth) {
    int i;
    Apartment *entry, *curr,  *prev;
    if (!head) {
        entry = (Apartment*) malloc(sizeof(Apartment));
        entry->name = apartment_name;
        entry->max_bandwidth = max_bandwidth;        
        entry->flat_list = NULL;
        entry->next = entry;
        return entry;
    }
    curr = head;
    prev = NULL;
    for (i=0;i<index;i++) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == head) {
        prev = head;
        while (prev->next != head) 
            prev = prev->next;
        entry = (Apartment*) malloc(sizeof(Apartment));
        entry->name = apartment_name;
        entry->max_bandwidth = max_bandwidth;        
        entry->flat_list = NULL;
        entry->next = head;
        prev->next = entry;
        if (!i)
            return entry;
        else
            return head;
    }
    else {
        entry = (Apartment*) malloc(sizeof(Apartment));
        entry->name = apartment_name;
        entry->max_bandwidth = max_bandwidth;        
        entry->flat_list = NULL;
        entry->next = curr;
        prev->next = entry;
        return head;
    }
}


void add_flat(Apartment* head, char* apartment_name, int index, int flat_id, int initial_bandwidth) {
    int i, sum=0, max;
    Apartment *aprt;
    Flat *curr, *entry;
    aprt = head;
    while (strchk(aprt->name,apartment_name))  
        aprt = aprt->next;
    curr = aprt->flat_list;
    if (!curr) {
        entry = (Flat*) malloc(sizeof(Flat));
        entry->id = flat_id;
        entry->is_empty = 0;
        if (aprt->max_bandwidth < initial_bandwidth)    
            entry->initial_bandwidth = aprt->max_bandwidth;
        else
            entry->initial_bandwidth = initial_bandwidth;
        entry->prev = NULL;
        entry->next = NULL;
        aprt->flat_list = entry;
        return; 
    }
    while (curr) {
        sum += curr->initial_bandwidth;
        curr = curr->next;
    }
    max = aprt->max_bandwidth - sum;;
    curr = aprt->flat_list;
    for (i=0;i<index;i++)
        curr = curr->next;
    if (!curr) {
        curr = aprt->flat_list;
        while (curr->next)
            curr = curr->next;
        entry = (Flat*) malloc(sizeof(Flat));
        entry->id = flat_id;
        entry->is_empty = 0;
        if (max < initial_bandwidth)    
            entry->initial_bandwidth = max;
        else
            entry->initial_bandwidth = initial_bandwidth;
        entry->prev = curr;
        entry->next = NULL;
        curr->next = entry;
        return;
    }
    else if (curr == aprt->flat_list) {
        entry = (Flat*) malloc(sizeof(Flat));
        entry->id = flat_id;
        entry->is_empty = 0;
        if (max < initial_bandwidth)    
            entry->initial_bandwidth = max;
        else
            entry->initial_bandwidth = initial_bandwidth;
        entry->prev = NULL;
        entry->next = curr;
        curr->prev = entry;
        aprt->flat_list = entry;
        return;
    }
    else {
        entry = (Flat*) malloc(sizeof(Flat));
        entry->id = flat_id;
        entry->is_empty = 0;
        if (max < initial_bandwidth)    
            entry->initial_bandwidth = max;
        else
            entry->initial_bandwidth = initial_bandwidth;
        entry->prev = curr->prev;
        entry->next = curr;
        curr->prev->next = entry;
        curr->prev = entry;
        return;
    }
}


Apartment* remove_apartment(Apartment* head, char* apartment_name) {
    Apartment *curr, *prev, *temp;
    curr = head;
    if (!(strchk(curr->name,apartment_name))) {
        if (strchk(curr->next->name,apartment_name)) {
            curr = curr->next;
            while (strchk(curr->next->name,apartment_name))
                curr = curr->next;
            curr->next = head->next;
            temp = head->next;
            free_flatlist(head->flat_list);
            free(head);
            return temp;
        }
        else {
            free_flatlist(head->flat_list);
            free(head);
            return NULL;
        }
    }
    else {
        prev = curr;
        curr = curr->next;
        while (strchk(curr->name,apartment_name)) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        free_flatlist(curr->flat_list);
        free(curr);
        return head;
    }
}


void make_flat_empty(Apartment* head, char* apartment_name, int flat_id) {
    Apartment *aprt;
    Flat *curr;
    aprt = head;
    while (strchk(aprt->name,apartment_name))  
        aprt = aprt->next;
    curr = aprt->flat_list;
    while (curr->id != flat_id)
        curr = curr->next;
    curr->is_empty = 1;
    curr->initial_bandwidth = 0;
    return;
}


int find_sum_of_max_bandwidths(Apartment* head) {
    Apartment *curr;
    int sum=0;
    if (!head)
        return 0;
    sum += head->max_bandwidth;
    curr = head->next;
    while (strchk(curr->name,head->name)) {
        sum += curr->max_bandwidth;
        curr = curr->next;
    }
    return sum;
}


Apartment* merge_two_apartments(Apartment* head, char* apartment_name_1, char* apartment_name_2) {
    Apartment *aprt1, *aprt2;
    Flat *tail, *hed;
    aprt1 = head;
    while (strchk(aprt1->name,apartment_name_1))  
        aprt1 = aprt1->next;
    aprt2 = head;
    while (strchk(aprt2->name,apartment_name_2))  
        aprt2 = aprt2->next;
    tail = aprt1->flat_list;
    hed = aprt2->flat_list;
    if (!hed) {
        aprt1->max_bandwidth += aprt2->max_bandwidth; 
        return remove_apartment(head,apartment_name_2);
    }
    else if (!tail) {
        aprt1->flat_list = hed;
        aprt2->flat_list = NULL;
        aprt1->max_bandwidth += aprt2->max_bandwidth; 
        return remove_apartment(head,apartment_name_2);
    } 
    else {
        while (tail->next) 
            tail = tail->next;
        tail->next = hed;
        hed->prev = tail;
        aprt2->flat_list = NULL;
        aprt1->max_bandwidth += aprt2->max_bandwidth; 
        return remove_apartment(head,apartment_name_2);
    }
}

void relocate_flats_to_same_apartment(Apartment* head, char* new_apartment_name, int flat_id_to_shift, int* flat_id_list) {
    Apartment *current, *apart;
    Flat *temp, *flist;
    int *list, i=0;

    list = flat_id_list;
    while (list[i] != 0) {
        current = head;
        while (strchk(current -> name, new_apartment_name)) {
            current = current -> next;
        }
        apart = current;
        
        current = current -> next;
        while (strchk(current -> name, new_apartment_name)) {
            flist = current -> flat_list;
            if (flist && (flist -> id == list[i])) {
                temp = flist;
                flist -> next -> prev = NULL;
                current -> flat_list = flist -> next;
                current -> max_bandwidth -= temp -> initial_bandwidth;
                apart -> max_bandwidth += temp -> initial_bandwidth;
                break;
            }
            else {
                while (flist && (flist -> id != list[i])) {
                    flist = flist -> next;
                }
                if (flist) {
                    temp = flist;
                    flist -> next -> prev = flist -> prev;
                    flist -> prev -> next = flist -> next;
                    current -> max_bandwidth -= temp -> initial_bandwidth;
                    apart -> max_bandwidth += temp -> initial_bandwidth;
                    break;
                }
            }
            current = current -> next;
        }

        flist = apart -> flat_list;
        if (flist -> id == flat_id_to_shift) {
            temp -> next = flist;
            temp -> prev = NULL;
            flist -> prev = temp;
            apart -> flat_list = temp;
        }

        else {
            while (flist -> id != flat_id_to_shift) {
                flist = flist -> next;
            }
            temp -> next = flist;
            temp -> prev = flist -> prev;
            flist -> prev -> next = temp;
            flist -> prev = temp;
        }
    i++;
    }
}