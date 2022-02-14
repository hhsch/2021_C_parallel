#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv) {
  int n = 100;
  int nproc = 1;
  char *fout = NULL;

  int mpi_id;

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

  double dx = 1.0 / (n - 1);

  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_id);

  // All tasks total up their own portion round-robin style
  double integral = 0;
  for (int i = mpi_id; i < n; i += nproc) {
	  double x_i = (dx*i + dx*(i+1)) / 2;
	  double f_i = (4 / (1+x_i*x_i));
	  integral += f_i * dx;
  }

  // Send local integral to first process if not first
  if (mpi_id != 0) {
	  MPI_Send(&integral, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }
  if (mpi_id == 0) {
	  double part_int;
	  for (int i = 0; i < nproc - 1; i++) {
		  MPI_Recv(&part_int, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		  integral += part_int;
	  }

  	printf("Estimate of pi: %f\n", integral);
  }

  MPI_Finalize();
}
