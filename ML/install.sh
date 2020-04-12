#!/bin/bash

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

module list

# Setting ENV variables
# export HOROVOD_CUDA_HOME=$CUDA_HOME
# export HOROVOD_CUDA_INCLUDE=$CUDA_HOME/include
# export HOROVOD_CUDA_LIB=$CUDA_HOME/lib64
# export HOROVOD_NCCL_HOME=$EBROOTNCCL
# export HOROVOD_GPU_ALLREDUCE=NCCL


# Creating virtualenv
VIRTENV=UvA_Course
VIRTENV_ROOT=${HOME}/MLCourse/virtualenvs

rm -rf $VIRTENV_ROOT/$VIRTENV

echo "Creating virtual environment $VIRTENV_ROOT/$VIRTENV" # --system-site-packages"
python -m venv $VIRTENV_ROOT/$VIRTENV # --system-site-packages

# Sourcing virtualenv
echo "Sourcing virtual environment $VIRTENV_ROOT/$VIRTENV/bin/activate"
source $VIRTENV_ROOT/$VIRTENV/bin/activate

# Export MPICC
# export MPICC=mpicc
# export MPICXX=mpicxx
# export HOROVOD_MPICXX_SHOW="mpicxx --showme:link"

# Tensorflow
echo "Installing Tensorflow"
pip install --upgrade pip
pip install tensorflow-gpu==1.15.0 --no-cache-dir

# Horovod
echo "Installing Horovod"
pip install horovod --no-cache-dir

#Ipykernel
pip install ipykernel

# matplotlib
pip install matplotlib
pip install seaborn

# pandas
pip install pandas

# keras
pip install keras

cd $VIRTENV_ROOT
python -m ipykernel install --user --name=$VIRTENV










