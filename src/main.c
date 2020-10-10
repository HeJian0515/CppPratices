#include <stdio.h>

int main(int argc, char *argv[], char **env) {
  
  int hoge = 5;
  void* hoge_p;
  hoge_p = &hoge;
  printf("%d", hoge_p);
    
    return 0;
}
