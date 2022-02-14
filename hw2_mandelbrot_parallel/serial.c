#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int n = 100;
  char *fout = NULL;

  // Accept options from user
  int opt;
  while ((opt = getopt(argc, argv, "n:o:")) != -1) {
    switch(opt) {
    case 'n': // number of bins
      n = atoi(optarg);
      break;
    case 'o': // output file name
      fout = optarg;
      break;
    default:
      exit(1);
    }
  }

  double integral = 0;
  double dx = 1.0 / (n - 1);
  for (int i = 0; i < n; i++) {
	  double x_i = (dx*i + dx*(i+1)) / 2;
	  double f_i = (4 / (1+x_i*x_i));
	  integral += f_i * dx;
  }

  printf("Estimate of pi: %f\n", integral);

}
