#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  // Use first command line argument as a seed.
  srand(atoi(argv[1]));

  int n = rand() % 999;
  int k = rand() % n ;
  int x = rand() % n ;
  int y = rand() % n;
  printf("%d %d %d %d\n",n,k,x,y);
  return 0;
}