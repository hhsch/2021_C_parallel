#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <complex.h>

#include "mandelbrot.h"

void usage(char *pname) {
  printf("Usage: %s -m [num x grid pts] -n [num y grid pts] -o [output file]\n", pname);
  return;
}

// Mandelbrot iteration
double complex mandit(double complex zi, double complex c) {
  return zi*zi + c;
}

int main(int argc, char **argv) {
  int niters = 100;
  int M = 100, N = 100;
  char *fout = NULL;

  // Accept options from user
  int opt;
  while ((opt = getopt(argc, argv, "m:n:o:")) != -1) {
    switch(opt) {
    case 'm': // number x grid points
      M = atoi(optarg);
      break;
    case 'n': // number y grid points
      N = atoi(optarg);
      break;
    case 'o': // output file name
      fout = optarg;
      break;
    default:
      usage(argv[0]);
      exit(1);
    }
  }
  
  // decide grid spacing
  double dx = 4.0 / (M-1);
  double dy = 2.0 / (N-1);

  double x[M], y[N];

  // Initialize arrays
  for (int i = 0; i < M; i++) {
    x[i] = -2.0 + i*dx;
  }
  for (int i = 0; i < N; i++) {
    y[i] = -1.0 + i*dy;
  }

  // number grid points for calculating area
  int npts = M*N;
  int ncvgd = 0; // number converged

  // select output file
  if (!fout) {
    fout = "bounded.dat";
  }
  FILE *fp = fopen(fout, "w");

  // run mandelbrot iteration over each grid point
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {

      double complex c = x[i] + y[j]*I;
      double complex zi = 0.0 + .0*I;

      // mandelbrot iteration
      for (int k = 0; k < niters; k++) {
	zi = mandit(zi, c);
      }

      // Test for convergence and write to file if converged
      if (cabs(zi) < 2.0) {
        fprintf(fp, "%f %f\n", x[i], y[j]);
	ncvgd++;
      }

    }
  }

  printf("Area of set: %f\n", 8*((float) ncvgd) / ((float) npts));

  fflush(fp);

  return 0;
}
