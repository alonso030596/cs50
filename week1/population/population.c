#include <cs50.h>
#include <stdio.h>

int main(void)
{
  int n, m, llamas, years = 0;

  do
  {
      n = get_int("Enter start size: ");
  }
  while (n < 9);

  do
  {
      m = get_int("Enter end size: ");
  }
  while (m < n);

  llamas = n;

  while(llamas < m){
  llamas = llamas + (llamas/3) - (llamas/4);
  ++years;
  }

  printf("It will take %i years", years);

}