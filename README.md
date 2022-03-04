# Network-Mapping-
The project deals with creating a network mapping for a residential street using structs and linked lists.

For this implementation, internet comes with cables until the wireless modem in the apartment, and there is a bandwidth value which
is related to how much money one pays for their internet connection for each month. The program are creates a
basic internet connection mapping in a sample street.


---**Specifications**
In every street, there are many apartments next to each other and an internal Internet connection of one of these streets is designed.
• There is a circular linked list for the street which is called as apartment linked list.
• Every apartment in a street should be considered as a node in the apartment linked list.
• Every apartment consist of flats, so there is a doubly linked list for each apartment in the street. 
  Every apartment has its own doubly linked list which is called flat linked list for the flats in that apartment.
• Every flat in an apartment should be considered as a node in the apartment’s flat linked list.
• Total bandwidth of the apartment is shared between the flats in the apartment and the sum of the
  initial bandwidth values of the flats cannot be more than max bandwidth value of the apartment.
  
In the street,
• Every apartment has
– its own unique name (char* name), which is used to distinguish an apartment from other apartments,
– max bandwidth value (int max bandwidth), which shows the maximum bandwidth value of the sum
  of flats’ initial bandwidth values.
• Every house (flat) has
– a unique ID in the entire street (int id), which is used to distinguish a flat from other flats (ID of a
flat is NOT related to the index in the flat list.),
Important Note 1: IDs of the flats must be unique for the whole street not only for the apartment.
Important Note 2: ID of a flat must always be a positive integer (1, 2, 3, ...).
– initial bandwidth value (int initial bandwidth), which shows the initial bandwidth of the flat,
– is empty flag (int is empty), which shows whether there are residents or the flat is empty.


---**Implementation and Functions**

You can see the structs that will be used in the Network Mapping.h file. 

-- **add_apartment**
Function Declaration:
Apartment* add_apartment(Apartment* head, int index, char* apartment_name,
int max_bandwidth);
Explanation:
- This function adds a new apartment at required index in the apartment linked list. If there is an apartment
  at the given index, it shifts it forward.
- The newly created apartment’s name and max bandwidth values must be apartment name and max bandwidth
  as given in the arguments respectively.
- Given index should always be 0 ≤ index ≤ initial apartment count.
- Given apartment name should be unique in the apartment linked list.
- flat list of newly added apartment is NULL.
- If initially there is no apartment in the apartment linked list, given head argument will be NULL.
- It returns the head of changed apartment linked list.

--  **add_flat**
Function Declaration:
void add_flat(Apartment* head, char* apartment_name, int index, int flat_id,
int initial_bandwidth);
Explanation:
- This function adds a new flat at required index in the flat linked list of the apartment whose name is given
  apartment name. If there is a flat at the given index, it shiftss shift it forward.
- ID of the newly created flat must be flat id as given in the arguments.
- initial bandwidth value of the flat must be initial bandwidth as given in the arguments. However, as you can
  understand, sum of the flat’s bandwidth values for an apartment cannot be more than max bandwidth value
  of that apartment. Therefore, before assigning the initial bandwidth value to new flat, it calculates
  the maximum bandwidth of the newly added flat can have. If it is less than the given initial bandwidth
  value, it assigns the calculated maximum bandwidth value to the new flat instead of the given
  initial bandwidth.
- Initially, is empty flag of the new flat must be 0.
- Given index will always be 0 ≤ index ≤ initial flat count of given apartment.
- Given flat id will be unique in the entire street.

-- **remove_apartment**
Function Declaration:
Apartment* remove_apartment(Apartment* head, char* apartment_name);
Explanation:
- This function removes the apartment whose name is equal to given apartment name from the apartment
  linked list.
- It frees the memory allocated for the apartment and its flat-list.
- After the freeing operations, it returns the changed apartment linked list.
- After remove operation, if there is not any apartment in the apartment linked list, this function returns NULL.

-- **make_flat_empty **
Function Declaration:
void make_flat_empty(Apartment* head, char* apartment_name, int flat_id);
Explanation:
- This function finds the flat whose ID is equal to given flat id of the apartment whose name is equal
  to given apartment name. However, it does not remove the flat from the flat linked list, it only changes its
  is empty flag to 1 and initial bandwidth to 0.
  
-- **find_sum_of_max_bandwidths**
Function Declaration:
int find_sum_of_max_bandwidths(Apartment* head);
Explanation:
- This function sums the max bandwidth values of the apartments in the given apartment linked list, then
  returns the sum.
- If there is not any apartment in the given apartment linked list, it returns 0. 

-- **merge_two_apartments **
Function Declaration:
Apartment* merge_two_apartments(Apartment* head, char* apartment_name_1,
char* apartment_name_2);
Explanation:
- This function appends the flats of the second apartment whose name is apartment name 2 to the end of the
  first apartment whose name is apartment name 1 (by repositioning the actual nodes).
- It adds the second apartment’s max bandwidth value to the first apartment’s max bandwidth value.
- Finally, it removes the second apartment from the apartment linked list, then it returns the changed apartment linked list.

-- **relocate_flats_to_same_apartment**
Function Declaration:
void relocate_flats_to_same_apartment(Apartment* head, char* new_apartment_name,
int flat_id_to_shift, int* flat_id_list);
Explanation:
- This function relocates the different flats in different apartments to a specific place at the same apartment
  consecutively. new_apartment_name is the name of the apartment which different flats in different apartments
  should be moved in. It locates them at the place of the flat whose id is flat_id_to_shift by shifting
  it to forward. IDs of the flats that need to their apartments changed are given with flat_id_list. Flats’
  apartment_name information is not given and they will be in different apartments. Therefore,  it
  traverses the entire street to find flats’ locations. After it finds the locations, while relocating the flats, it
  preserves their order in the flat id list. In other words, it places them to flat linked list of the
  new apartment one by one in the same order at the flat id list.
- As you can understand, max bandwidth value of the new apartment and the old apartment of each flat
   must be updated. For each relocated flat, it subtracts the flat’s initial bandwidth value from the
   old apartment and adds it to the new apartment.
- There will always be at least one flat to shift in the flat list of the given apartment whose name is
  new apartment name.
- It is guarantied that given flats in the flat id list will not be in the apartment whose name is new apartment name.


May the C gods be in your favor :)
