#!/bin/bash
#SBATCH -N ???
#SBATCH -t ???
#SBATCH -p ???

module purge
module load 2019
module load Python/3.6.6-foss-2018b
module load CUDA/10.0.130
module load cuDNN/7.6.3-CUDA-10.0.130
module load NCCL/2.4.7-CUDA-10.0.130
module unload GCC
module unload GCCcore
module unload binutils
module unload zlib
module load GCC/8.2.0-2.31.1
module unload compilerwrappers

# Activating virtualenv
VIRTENV=UvA_Course
VIRTENV_ROOT=${HOME}/MLCourse/virtualenvs

source $VIRTENV_ROOT/$VIRTENV/bin/activate

echo "Performing Training..."

mpirun -map-by ppr:4:node -np 1 -x LD_LIBRARY_PATH -x PATH -mca pml ob1 -mca btl ^openib python mnist_horovod.py

