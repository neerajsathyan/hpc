  #include <stdio.h>
  #include <stdlib.h>
  #include <mpi.h>
  #include <omp.h>

  #define SIZE 3  // Size of matrix and vector
  #define R 10 //Iterations
  //mtx_t lock;
  #define chunk 10

  int matrix[SIZE*SIZE], vector[SIZE], result[SIZE];

  int main(int argc, char *argv[])
  {
    
    int rank, size, matrix_start, matrix_end, n;
    double maxtime;
    n = SIZE;
    //MPI_Status status;
    omp_set_num_threads(4);  //Setting pre-defined threads
    
    MPI_Init (&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);	/* who am i */
    MPI_Comm_size(MPI_COMM_WORLD, &size); /* number of processors */
    MPI_Barrier(MPI_COMM_WORLD);  /*synchronize all processes*/
    double mytime = MPI_Wtime();  /*get time just before work section */
    if (n%size != 0 || n<size) {
      printf("%d %d",n,size);
      if (rank==0) printf("Number of processors not divisible by matrix size.\n");
      MPI_Finalize();
      exit(-1);
    }

    if (rank==0) {
      printf("Inserting Matrix : \n");
              #pragma omp parallel for
              for (int i=0; i<n*n; i++) {
                  matrix[i] = i;
              }

              #pragma omp parallel for
              for (int i=0; i<n; i++)
                vector[i] = i;
    }

    matrix_start = rank * (SIZE*SIZE)/size;  //Split up of rows, starting row index for processor rank
    matrix_end = (rank+1) * (SIZE*SIZE)/size; //Split up of rows, ending row index for processor rank

    //Local variable to store the scatterd array sub sections..
    int *procRow = malloc(sizeof(int) * n*n/size);
    if (procRow == NULL) {
        printf("Error in malloc for procRow in proc: %d",rank);
        exit(1);
    }
    //Local variable storing the result within a processor..
    int *procResult = malloc(sizeof(int) * n/size);
    if (procResult == NULL) {
        printf("Error in malloc for procResult in proc: %d",rank);
    }

    #pragma omp parallel for
    for (int i=0;i<n/size;++i) {
      procResult[i] = 0;
    }

    //Broadcast the vector to all size processors..
    MPI_Bcast(vector, n, MPI_INT, 0, MPI_COMM_WORLD);
    
    //Scatter the array with proportion of n/P rows where P is the numner of processors and n is the rows.
    MPI_Scatter(matrix, n*n/size, MPI_INT, procRow, n*n/size, MPI_INT, 0, MPI_COMM_WORLD);

    //MPI_Barrier(MPI_COMM_WORLD);
    printf("computing slice %d (from element %d to %d)\n", rank, matrix_start+1, matrix_end);
    printf("\n");
        int i,j;
        for (int p =0; p<R; ++p) {
          #pragma omp parallel shared(procRow,n,size,vector) private(i,j) 
          {
            #pragma omp for schedule(static)
            for (i=0; i<n/size; i++) { // Rows.. 
              int res = 0;
              for (j=0;j<n;++j) {
                //res += procRow[v_index++]*vector[j];
                res += procRow[i*(n/size)+j]*vector[j];  
              }
              procResult[i] = res;
            } 
          }
        }


    //Gather the results from each processor to the master processor to stitch it together..
    MPI_Gather(procResult, n/size, MPI_INT, result, n/size, MPI_INT, 0, MPI_COMM_WORLD);
    
    mytime = MPI_Wtime() - mytime;  /*get time just after work section*/

    //Get the maximum execution time between the processors..
    MPI_Reduce(&mytime, &maxtime, 1, MPI_DOUBLE,MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank==0) {

      printf("Matrix: \n");
      for(int i=0;i<n*n;++i) {
          if(i%n == 0)
              printf("\n");
          printf("%d\t",matrix[i]);
      }

      printf("\nVector: \n");
      for(int i=0;i<n;++i){
          printf("%d\t",vector[i]);
      }
      printf("\n");
      printf("\nResult: \n");
      for(int i=0;i<n;++i){
          printf("%d\t",result[i]);
      }
      printf("\n");
      printf("Running Time: %lf seconds\n",maxtime);

    }

    MPI_Finalize();
    return 0;
  }