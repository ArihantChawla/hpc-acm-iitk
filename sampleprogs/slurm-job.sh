#!/bin/bash

#SBATCH -N 2
#SBATCH --ntasks-per-node=8
#SBATCH --time=0:10:00
#SBATCH --job-name=Test
#SBATCH --error=job.%J.err
#SBATCH --output=job.%J.out

cd $SLURM_SUBMIT_DIR

mpiexec.hydra -n $SLURM_NTASKS ./a.out 

