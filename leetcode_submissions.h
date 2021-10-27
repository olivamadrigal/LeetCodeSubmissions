
//#############################################################################
/**
 * Note: The returned array must be malloced, assume caller calls free().
 FizzBuzz:
8 / 8 test cases passed.
Status: Accepted
Runtime: 11 ms
Memory Usage: 7 MB
You are here!
Your runtime beats 29.44 % of c submissions.
You are here!
Your memory usage beats 70.13 % of c submissions.
 */
char **fizzBuzz(int n, int* returnSize){
    
    char **answer;//array of strings
    int divBy3, divBy5, strLen1, strLen2, idx1, idx2, charCount, temp;
    
    //check range
   if(!(n >= 1 && n <= (int)pow(10,4)))
        return NULL;
    
    strLen1 = strlen("FizzBuzz")+1;
    strLen2 = strlen("Fizz")+1;
    answer = (char**)malloc(n*sizeof(char*));
    for(idx1 = 1, idx2 = 0; idx1 <= n; idx1++, idx2++)
    {
         divBy3 = idx1%3; divBy5 = idx1%5;
         if(divBy3 == 0 && divBy5 == 0)
         {
             answer[idx2] = (char*)malloc(sizeof(char)*strLen1);
             strncpy(answer[idx2], "FizzBuzz", strLen1);
         }
         else if(divBy3 == 0)
         {
             answer[idx2] = (char*)malloc(sizeof(char)*strLen2);
             strncpy(answer[idx2], "Fizz", strLen2);
         }
         else if(divBy5 == 0)
         {
             answer[idx2] = (char*)malloc(sizeof(char)*strLen2);
             strncpy(answer[idx2], "Buzz", strLen2);
         }
        else
        {
             charCount = 0;
             temp = idx1;
             while(temp != 0)
             {
                temp /= 10;
                ++charCount;
             }
             ++charCount;//NULL terminating char
             answer[idx2] = (char*)malloc(charCount*sizeof(char));
             sprintf(answer[idx2], "%d", idx1);
        }
        
    }
    *returnSize = n;
    return answer;
}

//#############################################################################
//Find largest peak that follows the smallest valley
/*

Best Time to Buy and Sell Stock:
211 / 211 test cases passed.
Status: Accepted
Runtime: 108 ms
Memory Usage: 13.1 MB

You are here!
Your runtime beats 96.40 % of c submissions.
You are here!
Your memory usage beats 21.13 % of c submissions.

*/
#include <limits.h>

int maxProfit(int* prices, int pricesSize)
{
    int min, max;
    
    min = INT_MAX;
    max = 0;
    for(int i = 0; i < pricesSize; i++)
    {
        if(prices[i] < min)
            min = prices[i];
        if(prices[i] - min > max)
            max = prices[i] - min;
    }
    return max;
}


//#############################################################################
/*
bool binary_search(int *ary, int left, int right, int target)
{
    int mid;
 
    while(left <= right)
    {
        mid = (left + right)/2;
        if(target > ary[mid])
            left = mid + 1;
        else if(target < ary[mid])
            right = mid - 1;
        else
            left = right + 1;
    }
    //return (ary[mid] == target)? true:false;
    if(ary[mid] == target)
        return true;
    else
        return false;
}

void selection_sort(int *ary, int last)
{
    int cur, mov, smallest, hold;
 
    for(cur = 0; cur < last; cur++)
    {
        smallest = cur;
        for(mov = cur + 1; mov <= last; mov++)
            if(ary[mov] < ary[smallest])
                smallest = mov;
        hold =  ary[cur];
        ary[cur] = ary[smallest];
        ary[smallest] = hold;
    }
}

//HASHING APPROACH
//
//NOTE: in C langauge we can easily solve with hashing: but we need to use hash table
//of size 10^9 given constraints on values and how we built the hash table.
//Since at worst we can have numsSize values, we need to make this the hash table size.
//To resolve any collision we need to account for probing when we hash and do look ups.

//We also need to account for searching and sorting. We need to verify a compliment exists.

//speed will depend on hash function and resolving collisions; here I used division method
//with linear probing and a struct to create a nice hash map.

//since, cleary 10^9 entries in hash table => direct hashing, too large a hash table.

//But yet, there's a better solution than this.
//
typedef struct e{
    int val;
    int idx;
}E;
#define hash_func(m, k, i)((k+i)%m);
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    int *answer, nums_cpy[numsSize], comp, lower_bound, upper_bound, key, k ;
    bool found, hashed;
    E hash_table[numsSize];

    //check bounds
    lower_bound =  -(int)pow(10,9);
    upper_bound =  (int)pow(10,9);
    if(!(numsSize >= 2 && numsSize <= (int)pow(10,4)))
        return NULL;
    if(!(target >= lower_bound && target <= upper_bound))
        return NULL;
    answer = (int*)malloc(2*sizeof(int));
    //hash_table[numsSize] = calloc(numsSize, sizeof(E*));
    for(int i = 0; i < numsSize; i++)
    {
        hash_table[i].idx = -1;
        nums_cpy[i] = nums[i];//make a copy to sort and use for binary search
    }
    selection_sort(nums_cpy, numsSize - 1);
    //hash entries
    for(int i = 0; i < numsSize; i++)
    {
        hashed = false;
        k = nums[i];
        if(k < 0) //account for negative indecis
            k += upper_bound;
        for(int probe = 0; probe < numsSize && !hashed; probe++)
        {
            key = hash_func(numsSize, k, probe);
            if(hash_table[key].idx < 0)
            {
                hash_table[key].val = nums[i];
                hash_table[key].idx = i;
                hashed = true;

            }
        }
    }
    //search for compliment
    found = false;
    for(int i = 0; i < numsSize && !found; i++)
    {
        if(!(nums[i] >= lower_bound && nums[i] <= upper_bound))
            return NULL;
        comp = target - nums[i]; ////complement of value at nums[i]
        if(binary_search(nums_cpy, 0, numsSize-1, comp))
        {
            hashed = false;
            k = comp;
            if(k < 0)
                k += upper_bound;
            for(int p = 0; p < numsSize && !hashed; p++)
            {
                key = hash_func(numsSize, k, p);
                if(hash_table[key].idx >= 0 && hash_table[key].val == comp)
                {
                     hashed = true;
                    if(hash_table[key].idx != i)//found a complement
                    {
                        answer[0] = i;
                        answer[1] = hash_table[key].idx;
                        found = true; //breaks loop
                    }
                }
            }
 
        }
    }
    *returnSize = 2;//TWO INDECIS
    return answer;
}
*/

//OPTIMAL SOLUTION
//We can solve without hashing: making a copy of nums, sorting nums once,
//then 2 sequential searches on the copy to map to locate the corresponding indecis.

//We can do better: Does not require unsorted search but only sort and a datastrcutre.

//Optimality depends on: sort function used. This solutions requires 1 call to sort
//and a data structure and to preserve original indecis:value:sorted_idx map.
//int* twoSumLC_optimalV2(int* nums, int numsSize, int target, int* returnSize)

typedef struct sums
{
    int oidx;
    int sval;//sorted val & idx
}SUMS;

void selection_sort_map(SUMS *ary, int last)
{
    int cur, mov, smallest, hold, oidx;
    
    for(cur = 0; cur < last; cur++)
    {
        smallest = cur;
        for(mov = cur + 1; mov <= last; mov++)
            if(ary[mov].sval < ary[smallest].sval)
                smallest = mov;
        hold =  ary[cur].sval;
        oidx =  ary[cur].oidx;
        ary[cur].sval = ary[smallest].sval;
        ary[cur].oidx = ary[smallest].oidx;
        ary[smallest].sval = hold;
        ary[smallest].oidx = oidx;
    }
}

/*
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.


55 / 55 test cases passed.
Status: Accepted
Runtime: 299 ms
Memory Usage: 6.2 MB
Memory: beats 98.93% of C submissions
You are here!
Your runtime beats 5.02 % of c submissions.
You are here!
Your memory usage beats 98.79 % of c submissions.
*/
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    
    int *answer, sum, left, right;
    bool found;
    SUMS sorted[numsSize];
    
    //MAKE A COPY OF THE ARRAY & save the original index corresponding to each value.
    for(int i = 0; i < numsSize; i++)
    {
        sorted[i].oidx = i;
        sorted[i].sval = nums[i];
    }
    
    //SORT THE ARRAY AND PRESERVE original VALU:IDX mapping.
    selection_sort_map(sorted,numsSize-1);
    
    //TEST BOUNDS
    if(!(numsSize >= 2 && numsSize <= (int)pow(10,4)))
        return NULL;
    if(!(target >= -(int)pow(10,9) && target <= (int)pow(10,9)))
        return NULL;
    
    //set first and last index of array
    left = 0;
    right =  numsSize - 1;
    answer = (int*)malloc(2*sizeof(int));
    found = false;
    while(left < right && !found)  //travese the copy from both endpoints, inwards.
    {
        sum = sorted[left].sval + sorted[right].sval;
        if(sum == target)
            found = true;
        else if(sum < target)//move up from smaller #s
            left++;
        else //move down from larger #s
            right--;
    }
    
    if(found)
    {   //if found, return the original indecis corresponding to our solution.
        answer[0] = sorted[left].oidx;
        answer[1] = sorted[right].oidx;
    }
  
    *returnSize = 2;//TWO INDECIS
    return answer;
}

//o(N^2) + 0(n) => O(n^2) TIME => O(nlog(n)
//O(n) space


//#############################################################################
/*

// sort + O(n) time.
// worst O(n) space.
Contains Duplicate:
20 / 20 test cases passed.
Status: Accepted
Runtime: 32 ms
Memory Usage: 8.8 MB
You are here!
Your runtime beats 61.21 % of c submissions.
You are here!
Your memory usage beats 36.13 % of c submissions.

*/
#include <stdlib.h> //qsort

int int_cmp(const void *a, const void *b)
{
    int *c, *d;
    
    c = (int*)a;
    d = (int*)b;
    
    if(*c > *d)
        return +1;
    else if(*c < *d)
        return -1;
    else
        return 0;
}
bool containsDuplicate(int* nums, int numsSize)
{
    int upper_bound, lower_bound;
    
    if(!(numsSize >= 1 && numsSize <= (int)pow(10,5)))
        return true;
    
    upper_bound = (int)pow(10,9);
    lower_bound = -upper_bound;
    
    //sort array
    qsort(nums, numsSize, sizeof(int), int_cmp);
    for(int i = 0; i < numsSize-1; i++)
    {
        if(!(nums[i] >= lower_bound && nums[i] <= upper_bound))
            true;
        if(nums[i] == nums[i+1])
            return true;
    }
    return false;
}

/* ##############################################################*/
/*
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation
Product of Array Except Self:
20 / 20 test cases passed.
Status: Accepted
Runtime: 80 ms
Memory Usage: 18.9 MB

You are here!
Your runtime beats 99.62 % of c submissions
You are here!
Your memory usage beats 57.36 % of c submissions.
 
*/
int* productExceptSelf(int* nums, int numsSize, int* returnSize)
{
    int *answer;
    
    answer = (int*)malloc(numsSize*sizeof(int));
    memset(answer, 1, numsSize); //set all elements to 1.
    
    //from the left
    for(int i = 0, product = 1; i < numsSize; i++)
    {
        answer[i] = product;
        
        product *= nums[i];
    }
    
    //from the right
    for(int i = numsSize - 1, product = 1; i >= 0; i--)
    {
        answer[i] *= product;
        product *= nums[i];
    }
    
    *returnSize = numsSize;
    return answer;
}

/* ##############################################################*/
//MERGE K SORTED LISTS
/*
133 / 133 test cases passed.
Status: Accepted
Runtime: 201 ms
Memory Usage: 7.9 MB
You are here!
Your runtime beats 56.12 % of c submissions.
You are here!
Your memory usage beats 99.16 % of c submissions.
*/
int linked_list_compare(int a, int b)
{
    if(a > b)
        return +1;
    else if(a < b)
        return -1;
    else
        return 0;
}

//given NIL terminated ary
int _count_lists(struct ListNode **lists)
{
    int c = 0;
    while(lists[c])
        c++;
    return c;
}

bool _count_lists_length(struct ListNode **lists, int listsSize, int lower_bound, int upper_bound)
{
    int count;
    for(int i = 0;  i < listsSize; i++)//for each list
    {
        count = 0;
        for(struct ListNode *mov = lists[i]; mov; mov = mov->next)
            count++;
        if(!(count >= lower_bound && count <= upper_bound))//test count in bounds.
            return false;
    }
    return true;
}

bool _are_lists_sorted(struct ListNode **lists, int listsSize)
{
    struct ListNode *pre, *cur;
    for(int i = 0;  i < listsSize; i++)//for each list
    {
        pre = lists[i];
        if(pre)
        {
            for(cur = pre->next; cur; cur = cur->next)
            {
                if(pre->val > cur->val)
                    return false;
                pre = cur;
            }
         }
    }
    return true;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
    struct ListNode *merged, *e, *pre, *cur;
    int count, lower_bound, upper_bound;

    lower_bound = -(int)pow(10,4);
    upper_bound = (int)pow(10,4);
     //0 <= k <= 10^4
    if(listsSize == 0) return NULL; //EMPTY LIST
    if(!(listsSize > 0 && listsSize <= upper_bound)) return NULL;

    /*
    //k == lists.length
    count = _count_lists(lists);
    if(count != listsSize)
        return NULL;
    */
   // 0 <= lists[i].length <= 500
   if(!_count_lists_length(lists, listsSize, 0, 500))
        return NULL;
    
    //lists[i] is sorted in ascending
    if(!_are_lists_sorted(lists, listsSize))
        return NULL;
    
    merged = lists[0];
    for(int i = 1; i < listsSize; i++)
    {
         e = lists[i];
         while(e)
         {
            if(!(e->val >= lower_bound && e->val <= upper_bound)) //-10^4 <= lists[i][j] <= 10^4
                return NULL;
             pre = NULL;
             cur = merged;//start from front of list.
             if(e) //find correct insert loc for e.
             {
                 while(cur && linked_list_compare(cur->val, e->val) < 0)
                 {
                     pre = cur;
                     cur = cur->next;
                 }
                 lists[i] = lists[i]->next;//point around before move e.
                 if(!pre)//empty or at start
                 {
                     e->next = merged;
                     merged = e;
                 }
                 else
                 {
                     e->next = pre->next;
                     pre->next = e;
                 }
                 e = lists[i];
             }//
         }//next.
     }
     //for(struct ListNode *mov = merged; mov; mov = mov->next)
       // linked_list_process(mov->val);
    
     return merged;
}

/* ##############################################################*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/*
//ITERATIVE
struct ListNode* reverseList(struct ListNode* head)
{
    struct ListNode *pre, *cur, *hold;
    int count;
 
    pre = hold = NULL;
    cur = head;
 
    count = 0;
    while(cur)
    {
        if(!(cur->val >= -5000 && cur->val <= 5000)) return NULL;
 
        hold = cur->next;
        cur->next = pre;
        pre = cur;
        cur = hold;
        count++;
        if(count > 5000)
            return NULL;
    }
 
    return pre;
}
*/

//recursively build list
//same time O(n) and space O(1)
/*
28 / 28 test cases passed.
    Status: Accepted
Runtime: 10 ms
Memory Usage: 6.5 MB
You are here!
Your runtime beats 7.83 % of c submissions.
You are here!
Your memory usage beats 47.33 % of c submissions.
*/
struct ListNode* reverseList(struct ListNode* head)
{
    struct ListNode *list;
    
    if(!head || !head->next)
        return head;
    //reverse remainder, place cur at end.
    list = reverseList(head->next);
    head->next->next = head;
    head->next = NULL;
    return list;
}


/* ##############################################################*/
/*

Implement Trie (Prefix Tree):
15 / 15 test cases passed.
Status: Accepted
Runtime: 88 ms
Memory Usage: 38.8 MB

You are here!
Your runtime beats 30.81 % of c submissions.
You are here!
Your memory usage beats 64.83 % of c submissions.

IMPLEMENT A TRIE
simple tree, move thorugh it using char to index mapping:
a b c d e f g h i .... z
0 1 2 3 4 5 6 7 8 .... 25

for small alphabet {a,e,t} = {0,1,2}, let x = NIL.
"tea" would be constructed like this:

[(x)(x)(2)]
        \
    [(x)(1)(x)]
        \
    [(0)(x)(x)]
        \
    [(x)(x)(x)] EOW =true
*/

#define ALPHA_LEN 26
typedef struct trie{
    struct trie *chilren[ALPHA_LEN];
    bool EOW; //if node is the end of a word.
    int levels;
} Trie;

Trie* trieCreate(void) {

    Trie *root = (Trie*)malloc(sizeof(Trie));
    if(root)
    {
        root->EOW = false;
        for(int i = 0; i < ALPHA_LEN; i++)
            root->chilren[i] = NULL;
        root->levels = 0;
    }
    return root;
}

Trie *create_trie_node(void){

    Trie *new_node = (Trie*)malloc(sizeof(Trie));
    if(new_node)
    {
        new_node->EOW = false;
        for(int i = 0; i < ALPHA_LEN; i++)
            new_node->chilren[i] = NULL;
    }
    return new_node;
}

void trieInsert(Trie* obj, char * word)
{
    Trie *mov;
    int n, loc;
    
    mov = obj; //root;
    n = (int)strlen(word);
    for(int i = 0; i < n; i++)
    {
        loc = ((int)word[i] - (int)'a');//map char to idx
        if(!mov->chilren[loc])//if slot is NIL
        {
            mov->chilren[loc] = create_trie_node();//malloc node for it.
            //obj->levels++;
        }
        mov = mov->chilren[loc];//move down the tree
    }
    mov->EOW = true;//mark end of word for last char node.
}

bool trieSearch(Trie* obj, char * word) {

    Trie *mov;
    int n, loc;
    
    mov = obj; //root;
    n = (int)strlen(word);
    //traverse the tree for the word
    for(int i = 0; i < n; i++) // i <= obj->levels &&
    {
        loc = ((int)word[i] - (int)'a');//index:char mapping ex: 0:a, 1:b, 2:c, etc.
        if(!mov->chilren[loc])//if any char not found, return false
            return false;
        mov = mov->chilren[loc];
    }
    return mov->EOW;//if we reached end of word, we found it.
}

bool trieStartsWith(Trie* obj, char * prefix)
{
    Trie *mov;
    int n, loc, count;
    
    mov = obj; //root;
    n = (int)strlen(prefix);
    count = 0;
    //search the prefix down the tree
    for(int i = 0; i < n && mov; i++) //  i <= obj->levels &&
    {
        loc = ((int)prefix[i] - (int)'a');//index:char mapping ex: 0:a, 1:b, 2:c, etc.
        if(mov->chilren[loc])
            count++;
        mov = mov->chilren[loc];
    }
    return (count == n)?true:false;
}


void trieFree(Trie* obj)
{
    if(!obj)//hit the root
        return;
    
    //free all kids recursively
    for(int i = 0; i < ALPHA_LEN; i++)
        trieFree(obj->chilren[i]);
    free(obj);//base
}

/* ##############################################################*/
/*
MEDIAN OF TWO SORTED ARRAYS
#include "stdlib.h"
int int_cmp(const void *a, const void *b)
{
    int *c, *d;
 
    c = (int*)a;
    d = (int*)b;
 
    if(*c > *d)
        return +1;
    else if(*c < *d)
        return -1;
    else
        return 0;
}

//VERSION 2
// combine the two arys into 1 auxiliary array, sort it, and return the
// median based on the total length n.
// but... this is O(nlogn) because of quicksort and O(n) auxiliary space.
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
   int m, n;
   int aux[nums1Size + nums2Size];
 
    n = nums1Size + nums2Size;
    memcpy(aux, nums1, nums1Size*sizeof(int));//combine arrays
    memcpy(&aux[nums1Size], nums2, nums2Size*sizeof(int));
    qsort(aux, n, sizeof(int), int_cmp);//sort
 
    m = n/2;
    if(n % 2 == 1) //odd len
        return (double)aux[m];
    else//even len
        return (double)((aux[m-1] + aux[m])/2.0);
}
*/

/*
// O(n + m) time and O(1) space.
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    int i, j, n, m, mp, mid;
 
    n = nums1Size + nums2Size;
    mid = n/2;
    i = j = 0;
    //sort in the "air" up until mid index and keep track of mid value.
    for(int k = 0; k <= mid; k++)
    {
        mp = m;
        if(i < nums1Size && j <  nums2Size)
            m = nums1[i] > nums2[j]? nums2[j++] : nums1[i++];//m = smallest, update corresponding idx
        else if(i < nums1Size)//exhausted nums2
            m = nums1[i++];
        else//exhausted nums1
            m = nums2[j++];
    }
    if(n%2 == 1)
        return m;
    else
        return (m + mp)/2.0;
}
*/
/*
Median of Two Sorted Arrays:
2094 / 2094 test cases passed.
Status: Accepted
Runtime: 10 ms
Memory Usage: 6.8 MB
You are here!
Your runtime beats 87.22 % of c submissions.
You are here!
Your memory usage beats 23.16 % of c submissions

remember: macros are in assembly and faster.
*/
//space O(1), time MIN(log(n), log(m))
#define MAX(x, y) ((x) > (y) ? (x):(y))
#define MIN(x, y) ((x) < (y) ? (x):(y))
#define MID2(x, y) ((x + y)/2.0)
#define MID3(x, y, z)(x + y + z - MAX(x, MAX(y,z)) - MIN(x, MIN(y,z)))
#define MID4(x, y, z, r)((x + y + z + r - MAX(x, MAX(y, MAX(z,r))) - MIN(x, MIN(y, MIN(z,r))))/2.0)
#define MIDARY(a, n)((n%2==1) ? a[n/2] : (a[n/2-1]+a[n/2])/2.0)
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    int i, j;
    
    if(nums1Size > nums2Size)
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    
    
    switch(nums1Size)
    {
        case 0:
                return MIDARY(nums2, nums2Size);
                break;
        case 1:
                if(nums2Size == 1)
                    return MID2(nums1[0], nums2[0]);
                else if(nums2Size%2 == 1)
                    return MID2(nums2[nums2Size/2], MID3(nums1[0], nums2[nums2Size/2 - 1], nums2[nums2Size/2 + 1]));
                else
                    return MID3(nums2[nums2Size/2], nums2[nums2Size/2 - 1], nums1[0]);
                break;
        case 2:
                if(nums2Size == 2)
                    return MID4(nums1[0], nums1[1], nums2[0], nums2[1]);
                else if(nums2Size%2 == 1)
                    return MID3(nums2[nums2Size/2], MAX(nums1[0], nums2[nums2Size/2 - 1]), MIN(nums1[1], nums2[nums2Size/2 + 1]));
                else
                    return MID4(nums2[nums2Size/2], nums2[nums2Size/2 - 1], MAX(nums1[0], nums2[(nums2Size/2)-2]), MIN(nums1[1], nums2[nums2Size/2+1]));
                break;
    }

    i = (nums1Size - 1)/2;
    j = (nums2Size - 1)/2;
    //discard lower half of nums1 and find median in nums1[i, numsSize-1] and nums2[0, j]
    if (nums1[i] <= nums2[j] )
      return findMedianSortedArrays(nums1 + i, nums1Size/2 + 1, nums2, nums2Size - i);
    //discard lower half of nums2 and find median in nums1[0, i] and nums2[j, nums2Size-1]
    return findMedianSortedArrays(nums1, nums1Size/2 + 1, nums2 + i, nums2Size - i);
}


/* ##############################################################*/
/*
//O(n) heheh lol
//VERSION 1
int hammingWeight(uint32_t n)
{
    int i, count;
    i = count = 0;
    while(i < 32)
    {
        if(n & (0x0000 << i)) //if ith bit is set
            count++;
    }
    return count;
}*/


//iterative Brian Kerningan's algorithm
// log(n) time-- since int n has ~log(n) bits.
//if all bits are set, 32 iterations.
// VERSION 3
/*
int hammingWeight(uint32_t n)
{
        int count = 0;
        while (n)
        {
            n &= (n - 1);//clears least significant bits set all the way up to msb.
            count++;
        }
        return count;
}
*/


//if all bits are set, at most max_bits/4 calls.
//for 32-bit => 4 calls.
// nibble:(set bits) map
// nibble = 4 bits... enumerate over all values.
// 0000:0bits set, 0001:1bit set, 0010:1bit set, 0011:2bits set.
//log(n) time, O(1) constant space.
/*

Number of 1 Bits:
601 / 601 test cases passed.
Status: Accepted
Runtime: 0 ms
Memory Usage: 5.4 MB
 
Submitted: 1 month, 1 week ago
You are here!
Your runtime beats 100.00 % of c submissions.
You are here!
Your memory usage beats 95.39 % of c submissions.


*/
int map[16] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };
//VERSION 2
int hammingWeight(uint32_t n)
{
    int nib = 0;
    if (n == 0)
        return map[0];
 
    nib = n & 0x000f;//last nib
    //lookup table for previous values and add rest recursively (shift out last nib)
    return map[nib] + hammingWeight(n >> 4);
}


/* ##############################################################*/
// pattern recogniction + divide & conquer => log(n) solution.
// look at nums from 0 - 7 in binary form.
// Similar to how we generatre truth tables fast from right to left....
// every time we increcement the bits to represet variables.
// SIMPLEST CASE: 2 BITS
//    NUM    SET BITS      F(n)
// -------------------------------
//    0 0     0            0
//    0 1     1            1
//    1 0     1            2
//    1 1     2            4
// F(4) = F(2) + 1 when using 2 bits... (simplest case).
// if we go from using 2 bits to 3 bits, we can also see how
// 1st half MSb=0 and 2nd half has MSb=1.
// NOW CONSIDER 3 BITS:
/*
    NUM    SET BITS      F(n)
-------------------------------
    0 00     0            0
    0 01     1            1
    0 10     1            2
    0 11     2            4
    1 00     1            5
    1 01     2            7
    1 10     2            9
    1 11     3            12
// F(12) = F(4) + 1 when using 3 bits.
// we can see that as we increment bits, they can all be expressed in terms of the simplest case.
// we can write a recursive formula for this: F(n) in O(log(n)) time: recurse all the way down to
// the simplest case and unwind populating the incrementing bit cases based off the smallest one.
// let f[0] = 0, f[1] = 1
// let x = floor(log(i))
// let a = pow(2, x)
// LOOP for i = 0 to n
//      f[i] = f[a - 1] + f[n-a] + (n-a+1);
//However, we are looking to compute a mapping between the leftmost column and the middle one.
//that is our problem. Let's get an O(n) meaning we must compute each entry in O(1) time deriving forumula
//from #s aboves.

DEC#   BIN     f(i)         FORMULA TO COMPUTE f(i)
0    "0000"    0           f(0)
1    "0001"    1            f(1)
-----------------------------------------------------1bit mark
2    "0010"    1            f(2) = f(0) + 1 = 1       // f(2) = f(2-2) + 1
3    "0011"    2            f(3) = f(1) + 1 = 2       // f(3) = f(3-2) + 1
----------------------------------------------------2bit mark (subtractor was 2^1=2)
4    "0100"    1            f(4) = f(0) + 1 = 1       //f(4) = f(4-4) + 1
5    "0101"    2            f(5) = f(1) + 1 = 2       //f(5) = f(5-4) + 1
6    "0110"    2            f(6) = f(2) + 1 = 2       //f(6) = f(6-4) + 1
7    "0111"    3            f(7) = f(3) + 1 = 3       //f(7) = f(7-4) + 1
----------------------------------------------------3bit mark (subtractor was 2^2=4)
8    "1000"    1            f(8) = f(0) + 1 = 1      //f(8) = f(8-8) + 1
9    "1001"    2            f(9) = f(1) + 1 = 2      //f(9) = f(9-8) + 1
10    "1010"    2           f(10) = f(2) + 1 = 2     //f(10) = f(10-8) + 1
11    "1011"    3           f(11) = f(3) + 1 = 3     //f(11) = f(11-8) + 1
12    "1100"    2           f(12) = f(4) + 1 = 2     //f(12) = f(12-8) + 1
13    "1101"    3           f(13) = f(5) + 1 = 3     //f(13) = f(13-8) + 1
14    "1110"    3           f(14) = f(6) + 1 = 3     //f(14) = f(14-8) + 1
15    "1111"    4           f(15) = f(7) + 1 = 4     //f(15) = f(15-8) + 1
----------------------------------------------------4bit mark (subtractor was 2^3=8)
SEE HOW we compute from f(0)+1 up to f(max) + 1 of previous mark?
now we just need to find some relationships with those #s.

0,1(1)--> 2,3(2) [2] -->4,5,6,7(3) [4]

n=2, s=2
n=4, s=4
n=8, s=8

s = f(n)
*/
//for this problem 10^5 = 100000.
//this lists all powers of 2 of form 2^n for n >=0.

/*
15 / 15 test cases passed.
Status: Accepted
Runtime: 74 ms
Memory Usage: 10.4 MB
You are here!
Your runtime beats 23.33 % of c submissions.
You are here!
Your memory usage beats 62.38 % of c submissions.
*/
int pows[] = {16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072};

int* countBits(int n, int* returnSize)
{
    int *f, s, inc, idx;
    
    *returnSize = n + 1;
    f = (int*)malloc(sizeof(int)*(*returnSize));
    //table up to 1st byte
    switch(n)
    {
        case 0: f[0] = 0;break;
        case 1: f[0] = 0;f[1] = 1;break;
        case 2: f[0] = 0;f[1] = 1;f[2]=1;break;
        case 3: f[0] = 0;f[1] = 1;f[2]=1;f[3]=2;break;
        case 4: f[0] = 0;f[1] = 1;f[2]=1;f[3]=2;f[4]=1;break;
        case 5: f[0] = 0;f[1] = 1;f[2]=1;f[3]=2;f[4]=1;f[5]=2;break;
        case 6: f[0] = 0;f[1] = 1;f[2]=1;f[3]=2;f[4]=1;f[5]=2;f[6]=2;break;
        case 7: f[0] = 0;f[1] = 1;f[2]=1;f[3]=2;f[4]=1;f[5]=2;f[6]=2;f[7]=3;break;
        default:
            break;
    }
    if(n > 7) //weight depend on number of bits to represent n.
    {
        f[0] = 0;f[1] = 1;f[2]=1;f[3]=2;f[4]=1;f[5]=2;f[6]=2;f[7]=3;
        //subtractor, reset everytime s hits a perfect power of 2.
        s = inc = 8; idx=0;
        for(int i = 8; i <= n; i++)
        {
            //if i is perfect pow 2, s = that perfecgt pow 2.
            //also, you can just use an incremetor with direct lookup table.
            f[i] = f[i-s] + 1; inc++;
            if(inc == pows[idx])
            {
                s = inc;
                idx++;
            }
          }
    }
    return f;
}

/* ##############################################################*/
/*
we can solve in different ways, use Gauss formula and compute sum from 1 to numsSize,
sum all elements in ary and subtract it from the first sum. O(n) time, O(1) space
we can also use XOR technique which is bitwise and there is no overflow risk for large
values of n.

//O(n) time and O(1) USING GAUSSIAN FORMULA
int find_missing_number(int *nums, int n)
{
    //gauss sum n(n+1)/2 => n:=(N+1)
    //(n^2 + n)/2 => ((n+1)^2 + (n+1))/2
    int S, SP;
    S = (int)(((n+1)*(n+1) + (n+1))/2);
    SP = nums[0];
    for(int i = 1; i < n; i++)
        SP += nums[i];
    return S - SP;
}
*/


//O(n) time and O(1) WITHOUT INT OVERFLOW
//compute the sums using XOR (addition/subtraction mod 2 no carries)
/*

Missing Number:
122 / 122 test cases passed.
Status: Accepted
Runtime: 31 ms
Memory Usage: 6.5 MB
You are here!
Your runtime beats 22.43 % of c submissions.
You are here!
Your memory usage beats 94.99 % of c submissions.
*/
int missingNumber(int* nums, int numsSize)
{
    int x, y;
    
    //COMPUTE THE BIT-WISE XOR MOD 2 SUM OF ALL ELEMENTS IN THE ARRAY
    x = nums[0];
    for(int i = 1; i < numsSize; i++)
        x ^= nums[i];
    //COMPUTE THE BIT-WISE XOR MOD 2 SUM OF ALL INTS FROM 1 TO N+1
    //SINCE THE FULL ARRAY WITH MISSING NUMBER IS OF SIZE N+1
    y = 1;
    for(int i = 2; i <= numsSize + 1; i++)
        y ^= i;
    
    return x ^ y; //BECAUSE +/- are the same, XOR in mod 2.
}

/* ##############################################################*/
//can use similar approach to reverse a string.
/*
Reverse Bits:
600 / 600 test cases passed.
Status: Accepted
Runtime: 3 ms
Memory Usage: 5.6 MB
You are here!
Your runtime beats 37.27 % of c submissions.
*/
uint32_t reverseBits(uint32_t n)
{
    uint32_t rev = 0;
    uint32_t msb, lsb, setm, setl;
    
    //msb=i= 31 to 16, lsb=j= 0 to 15
    for(int i=31, j=0; j < 16; i--, j++)
    {
        msb = 0x0001; msb <<= i;
        lsb = 0x0001; lsb <<=j;
        if(msb & n) //if MSb set
        {
            setl = 0x0001; setl <<= j;
            rev |= setl;//set the corresponding LSb. else, leave as 0.
        }
        if(lsb & n) //if LSb set
        {
            setm = 0x0001; setm <<= i;//set corresponding MSb.
            rev |= setm;
        }
    }
    return rev;
}


/* ##############################################################*/
/*
example of 4x4:
right, down, left, up: (1 ieration)
TIMES    R     C
c       0      0:c-1
r-1    1:r-1   c-1
c-1    r-1     c-2:0
r-2    r-2:1    0
right, down, left, up: (2nd ieration)
c-2     1       1:c-2
r-3    2:r-2    c-2
c-3    r-2    c-3:1
r-4    r-3:2    1
right, down, left, up: (3rd ieration)
c-4    2    2:c-3
r-5    3:r-3    c-3
c-5    r-3    c-4:2
r-6    r-4:3    2
right, down, left, up: (last ieration)
c-6    3    3:c-4
r-7    4    4
c-7    4    3

we have 4 loops with total TIME O(row*col)
right:
for(i=0; i < r/2; i++)
     for(j=i; j < c-(i+1) ;j++)
      {move right}
down:
for(j=c-1, s=1; j >= c/2; j--, s++;)
      for(i=s;  i < r - s ; i++)
           {move down}
left: e=0;
for(i=r-1, s=c-2; i >= 0; i--, s--)
     for(j=s; j >= e; j--)
          {move left}
e++;
e=1
for(j=0, s=r-2; j < r/2; j++,s--)
     for(i = s; i <= e; i++)
          {move up}
e++;

interconnect indecis; very clear to see thinking of bounded segments that decrease in size as we spiral in clockwise.



23 / 23 test cases passed.
Status: Accepted
Runtime: 0 ms
Memory Usage: 5.9 MB
 
You are here!
Your runtime beats 100.00 % of c submissions
You are here!
Your memory usage beats 48.40 % of c submissions.

*/
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
    int *ary, row_start, row_end, col_start, col_end, i, j;
    
    *returnSize = (*matrixColSize)*matrixSize;
    ary = (int*)malloc((*returnSize)*sizeof(int));//1 row len initially
    
    if(matrixSize == 1)
    {
        memcpy(ary, matrix[0], (*matrixColSize)*sizeof(int));
        return ary;
    }
    
    if(*matrixColSize == 1)
    {
        for(i = 0; i < matrixSize; i++)
            ary[i] = matrix[i][0];
        return ary;
    }
    
    i = row_start = col_start = 0;
    row_end = matrixSize;
    col_end = *matrixColSize;
    while(row_start < row_end && col_start < col_end)
    {
        for(j = col_start; j < col_end; j++)
            ary[i++] = matrix[row_start][j];//move right across colums; cols dec in lenght from boths end.
        row_start++;
        
        for(j = row_start; j < row_end; j++)//move down, col fixed, rows dec from both ends
            ary[i++] = matrix[j][col_end-1];
        col_end--;
        
        if(row_start < row_end)
        {
            for(j = col_end - 1; j >= col_start; j--)///move left from col
                ary[i++] = matrix[row_end-1][j];//starting at row r-1.
            row_end--;
        }
        if(col_start < col_end)
        {
            for(j = row_end - 1; j >= row_start; j--)//move up
                ary[i++] = matrix[j][col_start];
            col_start++;
        }
    }
    return ary;
}


/* ##############################################################*/
/*
Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's, and return the matrix.
164 / 164 test cases passed.
Status: Accepted
Runtime: 46 ms
Memory Usage: 10.9 MB
You are here!
Your runtime beats 38.78 % of c submissions.
You are here!
Your memory usage beats 95.41 % of c submissions.

*/
void setZeroes(int** matrix, int matrixSize, int* matrixColSize)
{
    bool row_zero[matrixSize];
    bool col_zero[*matrixColSize];
    int r, c;

    //arys that represent all rows and cols respectively
    memset(row_zero, false, matrixSize*(sizeof(bool)));
    memset(col_zero, false, (*matrixColSize)*(sizeof(bool)));

    for (r = 0; r < matrixSize; r++)
    {
        for (c = 0; c < *matrixColSize; c++)
        {
            if (matrix[r][c] == 0) //if element is zero
            {                      //mark the corresponding row AND col to true
                row_zero[r] = true;//to zero out each row and col ONLY once.
                col_zero[c] = true;
            }
        }
    }
    for (int r = 0; r < matrixSize; r++)
    {
        if(row_zero[r])
        {
            //do memset OR loop depending on performance optimization.
            memset(matrix[r], 0, (*matrixColSize)*(sizeof(int)));//faster because in assembler
            //for (int c = 0; c < *matrixColSize; c++) //VS loop
                //matrix[r][c] = 0;
        }
    }
    for (int c = 0; c < *matrixColSize; c++)
    {
        if (col_zero[c])
        {
            for (int r = 0; r < matrixSize; r++)
                matrix[r][c] = 0;
        }
    }
}



/* ##############################################################*/
/*
We are given a square matrix.
1) determine how many square there are, that is just floor(n/2)
2) figure out the indecis for each corner as a function of n.
3) determine the loop bounds, for how much you need to move per cycle.
21 / 21 test cases passed.
Rotate Image:
Status: Accepted
Runtime: 0 ms
Memory Usage: 6.4 MB
You are here!
Your runtime beats 100.00 % of c submissions.
You are here!
Your memory usage beats 46.59 % of c submissions.
*/
void rotate(int** matrix, int matrixSize, int* matrixColSize)
{
    int square_cycles, clockwise_steps, temp;
    
    square_cycles = matrixSize/2;
    for (int i = 0; i < square_cycles; i++)
    {
        clockwise_steps = matrixSize - i - 1; //this is the # of elements we need to move down clockwise
        for (int j = i; j < clockwise_steps; j++) //matrixSize - i - 1 = CLOCKWISE STEPS.
        {
        //swap corner elements 90 degrees, and continue loop to swap inner elemnts.
            temp = matrix[i][j];
            matrix[i][j] = matrix[matrixSize - 1 - j][i];
            matrix[matrixSize - 1 - j][i] = matrix[clockwise_steps][matrixSize - 1 - j];
            matrix[clockwise_steps][matrixSize - 1 - j] = matrix[j][clockwise_steps];
            matrix[j][clockwise_steps] = temp;
        }
    }
}

/* ##############################################################*/
/*
    DYNAMIC PROGRAMMING
    We can see that this problem exhibits 2 key attributes, basically the longest subsequence problem
    with a matrix body and ints.
    1) because the problem has OPTMIMAL SUBSTRUCTURE
    2) OVERLAPPING SUBPROBLEMS => WE CAN SOLVE IT RECURSIVELY (WE TABULATE THE OVERLAPPING SUBPROBLEMS)
 
    THIS HAS TIME O(N * M)
    SPACE IS O(N * M)
 
    138 / 138 test cases passed.
    Status: Accepted
    Runtime: 40 ms
    Memory Usage: 7.6 MB
    You are here!
    Your runtime beats 66.67 % of c submissions.
    You are here!
    Your memory usage beats 96.30 % of c submissions.
*/
#define MAX(x, y) ((x) > (y) ? (x):(y))
//dfs approach.
int dfs(int** matrix, int matrixSize, int* matrixColSize, int lip[][*matrixColSize], int *x_cord, int *y_cord, int i, int j)
{
    int x, y;
    
    if(lip[i][j] != 0) //if we have computed from this position, just return cache value.
        return lip[i][j];
    
    //else compute this position i,j and check all paths from our 4 neighbors
    for(int k = 0; k <  4; k++)
    {
            //update cordinates to move in all 4.
            x = i + x_cord[k];//update row-index
            y = j + y_cord[k];//update col-index.
        
            //if new coordinates valid, check paths recursively
            if((x >=0 && y >=0) && (x < matrixSize && y < *matrixColSize) && (matrix[x][y] > matrix[i][j])) ////if in bounds and if greater than previous position
                lip[i][j] = MAX(lip[i][j], dfs(matrix, matrixSize, matrixColSize, lip, x_cord, y_cord, x, y));
        
    }
    return ++lip[i][j];// max + 1 since we count path up to current cell be of lenght 1.
}

int longestIncreasingPath(int** matrix, int matrixSize, int* matrixColSize)
{
    // tabulate results in lip cache and lookup overlapping subproblems (MEMOIZATION => optimizes our solution.)
    int lip[matrixSize][*matrixColSize], path_len;
    
    //positions arrays to define our move  left, right, up, or down.
    //to move left from a cell: 0,-1 to the x,y coords...
    //to move right: 0, 1
    //to move up:-1,0
    //to move down:1,0
    int x_cord[] = {-1,0,1,0};
    int y_cord[] = {0,-1,0,1};
    
    memset(lip,0,sizeof(lip));
    path_len = 0;
    
    //for consider LIP for each cell and tabulate for cells as we visit.
    for(int i = 0; i <matrixSize; i++)
        for(int j =0; j < *matrixColSize; j++)
            path_len = MAX(path_len, dfs(matrix, matrixSize, matrixColSize, lip, x_cord, y_cord, i, j));

    printf("path len:  %d\n", path_len);
    return path_len;
}


/* ##############################################################*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 20 / 20 test cases passed.
Linked List Cycle:
Status: Accepted
Runtime: 8 ms
Memory Usage: 8 MB
You are here!
Your runtime beats 89.02 % of c submissions.
 */
// we can simply use Floyd’s Cycle-Finding Algorithm.
// O(n) time and O(1) Space
bool hasCycle(struct ListNode *head) {
    
    struct ListNode *slow, *fast;
    
    slow = fast = head;
    while(slow && fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast)
            return true;
    }
    
    return false;
}


/* ##############################################################*/
// 13 = 1^2 + 3^2 = 1 + 9 = 10 = 1^2 + 0^2 = 1, therefore 13 is happy. :)
/*
402 / 402 test cases passed.
Status: Accepted
Runtime: 0 ms
Memory Usage: 5.4 MB
You are here!
Your runtime beats 100.00 % of c submissions.
You are here!
Your memory usage beats 71.18 % of c submissions.


*/
bool isHappy(int n)
{
    int sum, d_i;

    sum = 0;
    while(n > 0)
    {
        //break up digits
        d_i = n % 10;
        n = floor(n / 10);
        sum += d_i * d_i;
        
    }
    if(sum > 1 && sum <= 4)
        return false;
    if(sum == 1)
        return true;
    return isHappy(sum);
    
}

/* ##############################################################*/
// DYNAMIC PROGRAMMING - ITERATIVE BOTTOM UP APPROACH
//((2^32)-1) - 2147483647
//4294967295 uint
//2147483647 sint
//2147483647-- error
//The answer is guaranteed to fit in a 32-bit integer.
/*
15 / 15 test cases passed.
Status: Accepted
Runtime: 5 ms
Memory Usage: 5.8 MB
 
You are here!
Your runtime beats 12.50 % of c submissions
You are here!
Your memory usage beats 18.75 % of c submissions.


*/
int combinationSum4(int* nums, int numsSize, int target)
{
        uint32_t s_i[target + 1];
    
        s_i[0] = 1;
        for(int i = 1; i <= target; i++)//sum to 1, 2, 3, 4.
        {
            s_i[i] = 0;
            for(int j = 0; j < numsSize; j++)
            {
                if(i - nums[j] >= 0)//if it's a combination
                    s_i[i] += s_i[i - nums[j]];
            }
        }
        return s_i[target];//final solution
}

/* ##############################################################*/
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numNeighbors;
 *     struct Node** neighbors;
 * };
 */

/*
consider simplest cases as usual:

G.nodes     adj list
-----------------
(1)         [2,3]
(2)         [1,4]
(3)         [1,4]
(4)         [2,3]

DFS and copy as we go. traverse the neighbors recursively.
keep processed flags as usual to avoid any loops.

we are given an arbitrary node to the graph.

TIME O(n) because we traverse each node once,
SPACE O(n) because we clone each node.


22 / 22 test cases passed.
Status: Accepted
Runtime: 5 ms
Memory Usage: 6.8 MB
You are here!
Your runtime beats 9.30 % of c submissions.
You are here!
Your memory usage beats 72.09 % of c submissions.
*/
struct Node *clone_with_DFS(struct Node *random, struct Node **map)
{
    struct Node *neighbor, *clone;
    
    if(map[random->val-1] != NULL)
        return map[random->val-1];
    
    clone = malloc(sizeof(struct Node));
    clone->val = random->val;
    map[random->val - 1] = clone;
    //printf("~%d", clone->val);
    
    if(random->numNeighbors > 0)
    {
        clone->numNeighbors = random->numNeighbors;
        clone->neighbors = calloc(random->numNeighbors, sizeof(struct Node *));
        for(int i = 0; i < random->numNeighbors; i++)
            clone->neighbors[i] = clone_with_DFS(random->neighbors[i], map);
    }
    else
    {
      clone->numNeighbors = 0;
      clone->neighbors = NULL;
    }
    return clone;
}

struct Node *cloneGraph(struct Node *s)
{
    struct Node *map[100] = {0};
    
    if(s == NULL)
        return NULL;
    
   return clone_with_DFS(s, map);
}

//printf("%d ", s->neighbors[0]->val);
//printf("%d ", s->neighbors[0]->neighbors[0]->val);
//map = calloc(100, sizeof(struct Node *));


/* ##############################################################*/
/*
    0 1 2 3 4    0 1
    p p p l e    p l
 
    5, 2

    tar: traverse max 4m times = n-m+1 times.
    str: traverse 2m times:
 
    (n-m+1 + 2m) => n + m + 1
 
 
    one very simple approach is just to point to the haystack,
    each time we are at an index where it matches the first character
    of the target, we can compare up to targetLen chars and break at the
    first != instance.
    we only increment pstr.
    if we find an occurence, we will know at what index. else we return 1.
 
    we compare up to valid possible index: targetLen < strLen - idx+ 1.
    after that str would not be long enough for the target to exist.
 
    strcmp will compare until it hits a char that does not match and returns,
    so we can implement that or use strcmp.
 
    there are also more advanced string matching algorithms we can use.
 
    n = str; m = target.
    we move only pstr and compare 1 char of target, break when char does not match.
    move across n up to n-m idx where we do last possible comparison.
 
 
    Time O(m+n)
    Space O(1)
 
    80 / 80 test cases passed.
    Status: Accepted
    Runtime: 260 ms
    Memory Usage: 6.3 MB
    Submitted: 1 month, 1 week ago
 
    You are here!
    Your runtime beats 80.44 % of c submissions.
    You are here!
    Your memory usage beats 40.34 % of c submissions.


 
*/
int strStr(char *haystack, char *needle)
{
    char *pstr;
    int strLen, tarLen;
    
    if(!*needle) return 0;
    
    strLen = (int)strlen(haystack);
    tarLen = (int)strlen(needle);
    pstr = haystack;
    for(int idx = 0; tarLen < strLen-idx+1; idx++)
    {
        if(*pstr == *needle)
        {
            if(strncmp(pstr, needle, tarLen) == 0)
                return idx;
        }
        pstr++;
    }
    return -1;
}


/* ##############################################################*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/*
pick any traversal, if there are any hickups (NULL right/left child)
from one but not the other, break and return false.

preferable NLR or NRL, so we check val at each point; process each side in "parallel"

else continue moving and comparing values.

traverse the trees in "parallel"...
time O(n); space Olog(n) best; O(n) worst.

60 / 60 test cases passed.
Status: Accepted
Runtime: 0 ms
Memory Usage: 5.9 MB

You are here!
Your runtime beats 100.00 % of c submissions.
You are here!
Your memory usage beats 21.97 % of c submissions.

*/
bool isSameTree(struct TreeNode* p, struct TreeNode* q)
{
   if(!p && !q) return true; //base: when we hit leafs
   if(!(p && q)) return false;//if one is null but not the other
   if(p->val != q->val) return false;//if values differ
   return isSameTree(p->left, q->left) && isSameTree(p->right, q->right) ;
}


/* ##############################################################*/
/*
318 / 318 test cases passed.
Status: Accepted
Runtime: 151 ms
Memory Usage: 21.2 MB
You are here!
Your runtime beats 61.40 % of c submissions.
You are here!
Your memory usage beats 65.12 % of c submissions.
*/
#include "math.h"
#include <stdlib.h>
int int_cmp(const void *a, const void *b)
{
    int *c, *d;
    
    c = (int*)a;
    d = (int*)b;
    
    if(*c > *d)
        return +1;
    else if(*c < *d)
        return -1;
    else
        return 0;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    int **answer, sum, left, right, base_size, lower_bound, upper_bound;
    
    //set a basic size start size
    base_size = 10;
    
    //bounds
    upper_bound = (int)pow(10,5);
    lower_bound = -upper_bound;
   
    //array of arrays
    answer = (int**)malloc(base_size*sizeof(int*));
    
    //we can just use quicksort since we don't care about the original indecis.
    qsort(nums, numsSize, sizeof(int), int_cmp);//sort
    
    //for each row in the answer, we store the col size (just an int = 3)
    *returnColumnSizes = malloc(base_size*sizeof(int));//array of ints

    //TEST BOUNDS
    if(!(numsSize >= 0 && numsSize <= 3000)) return NULL;

    //modification of the twoSum solution: we skip over any duplicates
    //and now, we want triplets.
    *returnSize = 0;//row idx and row count
    for(int i = 0; i < numsSize; i++)
    {
        if(!(nums[i] >= lower_bound && nums[i] <= upper_bound)) return NULL;
        
        if(nums[i] > 0)////nums_i must be <= 0
            break;
        if(i == 0 || nums[i-1] != nums[i])  // check for duplicates
        {
            left = i + 1;
            right =  numsSize - 1;
            while(left < right)  //travese the copy from both endpoints, inwards.
            {
                sum = nums[i] + nums[left] + nums[right];
                if(sum < 0)
                    left++;
                else if(sum > 0)
                    right--;
                else
                {
                    //save the triplet
                    answer[*returnSize] = calloc(3, sizeof(int));
                    answer[*returnSize][0] = nums[i];
                    answer[*returnSize][1] = nums[left];
                    answer[*returnSize][2] = nums[right];
                    left++; right--;
                    (*returnColumnSizes)[*returnSize] = 3;
                    (*returnSize)++;
                    while((left < right) && nums[left] == nums[left - 1])
                        left++;
                    if(*returnSize == base_size)
                    {
                        base_size *= 2;//doble each time
                        answer = realloc(answer, base_size*sizeof(int*));
                        *returnColumnSizes = realloc(*returnColumnSizes, base_size*sizeof(int*));
                    }
                    
                }
            }//while
     
        }//if
    }//for
    
    if(*returnSize < base_size)//shrink the array
    {
        answer = realloc(answer, (*returnSize)*sizeof(int*));
        *returnColumnSizes = realloc(*returnColumnSizes, (*returnSize)*sizeof(int*));
    }
    
    return answer;
}




/* ##############################################################*/
/*
we can observe from brute force recursive solution
that there are overlapping substructure and we
can use dynamic programming. however we can further observe that to reach the ith step, the ith entry which is the sum of the number of ways to take 1 + to take 2 steps,

we use fib as our start base:

=> f(3) = f(2) + f(1) = 3 (3rd fib number were each is sum of previous 2.)
=> and continue, until we compute f(n) for given n.

we can code this in a few lines using the 1/√5 formula.
however, a cleaner way with respect to time and without
deriving such a formula, is te matrix version:
to comput nth fibonacci number we just do:

Q^(n-1)[0][0] - the 0th entry of such a matrix. where

Q = [ F_n+1, F_n]
    [ F_n,  F_n-1]


*/

/*
//VERSION 1: very intutitive fibonacci
//TIME = O(n)
//SPACE = O(1)
int climbStairs(int n)
{
    int first, second, third;
 
    if(n == 1) return 1;
    first = 1; second=2;
    for(int i = 3; i <= n; i++)
    {
        third = first + second;
        first = second;
        second = third;
    }
    return second;
 
}
*/

//VERSION 2 & 3: these are more specilized solutions.
//direct formula application in equation and matrix form
//TIME log(n)*(exponentiation_cost)
//SPACE O(1)
/*
45 / 45 test cases passed.
Status: Accepted
Runtime: 0 ms
Memory Usage: 5.9 MB

You are here!
Your runtime beats 100.00 % of c submissions.
*/
int climbStairs(int n)
{
    double a, b, c, f_n;
    
    if(n == 1) return 1;
    c = 1/sqrt(5);//for readability
    a = (1+sqrt(5))/2;
    b = (1-sqrt(5))/2;
    //pure mathematical equation to solve f_n
    f_n = c*(pow(a,n+1) - pow(b, n+1));
    
    return (int)f_n;

}


/* ##############################################################*/
//DYNAMIC BOTTOM UP APPROACH:
/*

Least # coins that sum to amount. Repeated coin values allowed.

We compute bottom up, so for target value of say x
and n different coins with values 1, 2, ... n=x.
x = min{f(x-c1), f(x-c2), ..., f(x-cn)} + 1...

for x = 3:
  = min{f(3-c1), f(3-c2), f(3-c3)} + 1.
  = min{f(3-1), f(3-2), f(3-3)} + 1.
  = min{f(2), f(1), f(0)} + 1.
  = min{1, 1, 0} + 1= 1
 
  f(2) = min{f(2-1), f(2-2)} + 1 = min{f(1),f(0)} + 1 = f(0) + 1=0+1 = 1.
  f(1) = min{f(1-1)} + 1 = min{f(0)} + 1 = f(0) + 1 = 0 + 1 = 1.
  f(0) = 1.
 
 
  Submission Detail
188 / 188 test cases passed.
Status: Accepted
Runtime: 53 ms
Memory Usage: 5.7 MB
 
You are here!
Your runtime beats 37.02 % of c submissions.

You are here!
Your memory usage beats 78.45 % of c submissions.
*/

// TIME O(A*n): for i in [1,A], each F_i requires n iterations (coinsSize)
//Space O(A).
// A = the amount.
#define MIN(x, y) ((x) < (y) ? (x):(y))
int coinChange(int* coins, int coinsSize, int amount)
{
    int max;
    int f[amount + 1];
    
    max = amount + 1;
    f[0] = 0;
    for(int i = 1; i < max; i++)
        f[i] = max;
    
    for(int x = 1; x < max; x++)//bottom up, for each amount x
    {
        for(int i = 0; i < coinsSize; i++)//compute f(x)=min{f(x-c1),f(x-c2), etc.}
         {
            if(coins[i] <= x)//assuming coins not sorted.
                f[x] = MIN(f[x], f[x - coins[i]] + 1);
        }
        
    }
    return f[amount] > amount ? -1: f[amount];
}



/* ##############################################################*/
/* intutive 1st thing: but time exceeded. boo
bool wordBreak(char * s, char ** wordDict, int wordDictSize)
{
    char *pstr;
    int str_count;
    int strLen;
 
    strLen = strlen(s);
    str_count = 0;
    for(int i = 0; i < wordDictSize && (str_count <  strLen); i++)
    {
        pstr = strstr(s, wordDict[i]);
        while(pstr)
        {
            str_count += strlen(wordDict[i]);
            pstr += strlen(wordDict[i]);
        }
    }
    return (str_count == strLen)? true:  false;
 
}*/

#define hash_func(k, i, n)((k+i)%n)
char **build_set(char **data, int size)
{
     int key, idx;
     char **set;
    
     set = calloc(size, sizeof(char*));
     for(int i = 0; i < size; i++)
     {
        key = *data[i] + 997;
        for(int probe = 0; probe < size; probe++) //LINEAR PROBING
        {
            idx = hash_func(key, probe, size);
            if(!set[idx])
            {
                set[idx] = data[i];
                probe = size;
            }
        }
     }
     return set;
}


bool in_set(char **set, int size, char *s)
{
    int key, idx;
    bool found;
    
    found = false;
    for(int probe = 0; probe < size && !found; probe++)
    {
         key = *s + (int)strlen(s);
         idx = hash_func(key, probe, size);
         if(set[idx] && strcmp(set[idx], s) == 0)
            found = true;
    }
    return found;
}

//recurisve or dynamic programming
/*

45 / 45 test cases passed.
Status: Accepted
Runtime: 52 ms
Memory Usage: 13.2 MB
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool wordBreak(char * s, char ** wordDict, int wordDictSize)
{
    bool dp[strlen(s) + 1];
    int  strLen;
    char **set, *sp, *p;
    
    strLen = (int)strlen(s);
    memset(dp, false, strLen + 1);
    set = build_set(wordDict, wordDictSize);
    dp[0] = true;
    for(int i = 1; i <= strLen; i++)
    {
        for(int j = 0; j < i; j++)
        {
            //sub string sp
            p = s + j;
            sp = malloc((i - j + 1)*sizeof(char));
            strncpy(sp, p, i - j);
            *(sp + i - j) = '\0';
            if(dp[j] && in_set(set,wordDictSize,sp))
            {
                dp[i] = true;
                break;
            }
            free(sp);
        }
    }
    
    free(set);
    return dp[strLen];
    
}

/* ##############################################################*/
/*
you have to skip one each time. find which order to skip that
gives you max profit.
series: 0, 2, 4, ...,
or: 1, 3, 5 etc.
point is no adjacent ones.
even 2, 4, etc.
need to try all possible subsets such that no two houses are ajacent.

"DP" solution

68 / 68 test cases passed.
Status: Accepted
Runtime: 4 ms
Memory Usage: 6.1 MB

You are here!
Your runtime beats 13.37 % of c submissions.
*/

#define MAX(x,y)(x > y? x:y)
int rob(int* nums, int numsSize)
{
    if(numsSize == 0) return 0;
    
    int i_1, i_2, cmax;
    
    i_1 = nums[numsSize - 1];
    i_2 = 0;
   
    for(int i = numsSize - 2; i >=0; i--)
    {
        //printf("i=%d, i+1=%d, i+2=%d\n", i, i_1, i_2);
        //cmax to keep track of current max.
        cmax = MAX(i_1, nums[i] + i_2);//skip i & rob i+1 OR rob i and i+2
        //printf("cmax=%d\n",cmax);
        i_2 = i_1;
        i_1 = cmax;
    }
    return i_1;
}

/* ##############################################################*/
#include <string.h>
//given a string of ints  s: how many ways you decode it?
/*
A->1
B->2
....
Z->26

1108912... -> ???

12: 1, 2 OR 12. => 2 ways


O(1) space; O(n) time.

Decode Ways:
269 / 269 test cases passed.
Status: Accepted
Runtime: 0 ms
Memory Usage: 5.8 MB

You are here!
Your runtime beats 100.00 % of c submissions.
*/
int numDecodings(char * s)
{
    int i_1, i_2, count, strLen, two_digits, c;
    char *si, *sub_str, *p;
    
    if(*s == '0') return 0; //discard anything with leading zeros.
    
    strLen = strlen(s);
    i_1 = 1;
    i_2 = 1;
    si = s + 1;
    for(int i = 1; i < strLen; i++)
    {
        count = 0;
        if(*si != '0')
            count = i_1;
        
        p = si - 1;
        c = (i+1)-(i-1);
        sub_str = (char*)malloc((c+1)*sizeof(char));//i-1:i
        strncpy(sub_str, p, c);
        *(sub_str + c) = '\0';
        two_digits = (int)strtol(sub_str, (char**)NULL, 10);
        
        if(two_digits >= 10 && two_digits <= 26)
            count += i_2;
        
        i_2 = i_1;
        i_1 = count;
        si++;
    }
    return i_1;
    
}


/* ##############################################################*/
/*
    ways(i,j) = ways(i-1,j) + ways(i,j-1)

    time = O(mxn);
    space = O(mxn) because of dp array
 
    Unique Paths:
    62 / 62 test cases passed.
    Status: Accepted
    Runtime: 0 ms
    Memory Usage: 5.6 MB
 
    You are here!
    Your runtime beats 100.00 % of c submissions.
 
    You are here!
    Your memory usage beats 67.09 % of c submissions.
*/
int uniquePaths(int m, int n) //m x n
{
    int dp[m][n];
    
    for(int j = 0; j < n; j++)//init row0
        dp[0][j] = 1;
    for(int i = 0; i < m; i++)//init col0
        dp[i][0] = 1;
    
    //go over all inner cells.
    //d_cr = d_c-1,r + d_c,r-1
    for(int r = 1; r < m; r++)
        for(int c = 1; c < n; c++)
            dp[r][c] = dp[r-1][c] + dp[r][c-1];
    
    return dp[m-1][n-1];
}


/* ##############################################################*/

/*
O(n) time.

O(n) space for set.


Watch out for: the hash function. that's the time complexity
determinant here. TEST for negative hash indecis and fix accordingly....

we just want a sequence of consecutive numbers...
if we sort => at least nlog(n) for quicksort
if we hash: we can get O(n)

IDENTIFIED TWO PROBLEMS: hashing with negative #s.
NEED BETTER HASH FUNCT :) LOL.

needed good hash func that performs well with small and large inputs

Longest Consecutive Sequence:
70 / 70 test cases passed.
    Status: Accepted
Runtime: 1608 ms
Memory Usage: 10.5 MB

You are here!
Your runtime beats 7.50 % of c submissions.

You are here!
Your memory usage beats 92.50 % of c submissions.
*/

#include <math.h>
#include <string.h>

#define NIL -1000000001 //-(10^9) - 1.
//#define C1 2
//#define C2 5
#define hash_func(k, i, m)((k+i) %m)
//#define hash_func(k, i, m)(((k%m) + C1*i + C2*i)%m)
int *build_hash_table(int *nums, int n)
{
    int key, idx, *set;
    
    set = (int*)malloc(n*sizeof(int));
    for(int i = 0; i < n; i++)
        set[i] = NIL;
    for(int i = 0; i < n; i++)
    {
        key = nums[i];
        for(int probe = 0; probe < n; probe++)
        {
            idx = hash_func(key, probe, n);
            if(idx < 0)
                while(idx < 0)
                    idx += n;
            if(set[idx] == NIL)
            {
                set[idx] = nums[i];
                probe = n;
            }
        }
    }
    return set;
}

bool hash_table_lookup(int *set, int n, int target)
{
    int idx, key;
    bool found;
    
    found = false;
    key = target;
    for(int probe = 0; probe < n; probe++)
    {
        idx = hash_func(key, probe, n);
        if(idx < 0)
            while(idx < 0)
                idx += n;
        if(set[idx] == target)
        {
                found = true;
                probe = n;
        }
        
    }
    return found;
}

#define MAX(x, y)(x > y ? x : y)
int longestConsecutive(int* nums, int numsSize)
{
    int *set, lis, e, cur, cur_count;
    
    if(numsSize == 1) return 1;
    
    set = build_hash_table(nums, numsSize);
    lis = 0;
    for(int i = 0; i < numsSize; i++)
    {
        e = set[i];
        if(!hash_table_lookup(set, numsSize, e-1))
           {
               cur = e;
               cur_count = 1;
               while(hash_table_lookup(set, numsSize, cur + 1))
               {
                   cur += 1;
                   cur_count += 1;
               }
               lis = MAX(lis, cur_count);
           }
    }
    free(set);
    return lis;
}
