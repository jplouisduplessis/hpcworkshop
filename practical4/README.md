# Optimisation and automation
This practical will deal with how to squeeze out extra performance from your cluster. We will also look at how to write and utilise scripts to automate certain parts of the cluster configuration process.


# Installing Gromacs
**Note:** Before proceeding, make sure you can execute and mpi job on your cluster.

In this example, you will see that we make use of the module for GCC and OpenMPI. It is important to first install GCC like discussed above and to install openmpi-devel before continuing. 

The code section below will allow you to install a basic compiled version of Gromacs. Note that there are some optimization options such as the -DGMX_SIMD option, that needs to be set according to you CPU's optimal optimization flags:

` cat   /proc/cpuinfo | grep flags | tail -n 1`

If your Processor supports a higher level of optimization such as AVX, AVX2, AVX128, AVX256, AVX512 etc. make sure to use those. YOu should also check the requirements and dependencies.

<!-- As mentioned before, I would compile my own GCC, LAPACK and FFTW; create and load their module files, before continuing. -->
```
Install_Ver=2018.1
Install_Dest=/soft/gromacs/$Install_Ver

module load mpi

cd /tmp
wget ftp://ftp.gromacs.org/pub/gromacs/gromacs-${Install_Ver}.tar.gz \
       -O gromacs-${Install_Ver}.tar.gz

tar -zxvf gromacs-${Install_Ver}.tar.gz
cd /tmp/gromacs-${Install_Ver}
rm -rf my_build
mkdir my_build && cd my_build
cmake ../ \
	-DCMAKE_INSTALL_PREFIX=$Install_Dest \
	-DGMX_MPI=ON \
	-DGMX_OPENMP=OFF \
	-DGMX_THREAD_MPI=OFF \
	-DGMX_OPENMP_MAX_THREADS=1

make -j  &&   sudo make install
```
After installing Gromacs, you can download and test the installation using the following method:

```
#Execute the following as a normal user:

module load gromacs

#Go to your home directory
cd

#Download the example:
wget http://grid.ufs.ac.za/public/examples/gromacs_test.tar.gz

tar -zxvf gromacs_test.tar.gz
cd gromacs_test

#There are two scripts 00prepare_input.sh and 01submit.pbs
#The first script that generates the input files can be executed as:
#     ./00prepare_input.sh
#After the script ran (about 1.5 hours on a VM), the input files should be
#generated
#You can submit the script 01submit.pbs


#Modify the script to reflect the number of nodes etc. before submitting.
#On 3 virtual machines with 16 cores each, this runs for about 25mins.


bash 01submit.pbs

```
