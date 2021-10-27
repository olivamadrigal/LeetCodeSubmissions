# LeetCodeSubmissions
My solutions to various problems in C submitted ~1 month ago in September 2021.
Clean and efficient code: several submissions beat 60, 90, up to 100 of C submissions in time and memory.
If you are learning C or working on solving these problems, I hope this repository is a helpful reference.
Note: each problem is separated by a hastag line with required libraries, etc.

Ideally, you can make a library file test.h and put all included libraries at the top (remove duplicates).
Ensure you have one copy of functions called for several problems, like the int compare required for
qsort. Feel free to improvise and improve where possible. You can just used:


int int_cmp(const void *a, const void *b)
{
  return (*((int*)(a)) - *(int*(b))); // CAST, THEN DEREFERENCE.
}


