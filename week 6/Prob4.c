#include <stdio.h>
int *p;
int val;
void foo(int a, int *b_ptr){
  p = &a; // Keep p = &a for consistency, though unused here
  val = *b_ptr; // Directly read b’s value
  printf("In foo\n");
}
void bar(int b, int *a_ptr){
  p = &b; // Keep p = &b for consistency, though unused here
  *a_ptr = val; // Directly set a to val
  printf("In bar\n");
}
int main(){
  int a = 1, b = 2;
  foo(a, &b); // Pass b’s address to foo
  bar(b, &a); // Pass a’s address to bar
  printf("a = %d, b = %d\n", a, b);
  return 0;
}