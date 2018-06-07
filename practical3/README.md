# Practical 3 - Scientific software
In this practical you will learn how to configure and install scientific software from source files.

Many scientifict packages make use of OpenMP and MPI to parallelise their workflows. In practical 1 we build and executed a program that makes use of OpenMP. We now need to do the same for MPI.

## Installation files
Head over to the [OpenMPI website](https://www.open-mpi.org/software/ompi/v3.1/) and grab the latest version of the OpenMPI source files. I used the `.tar.gz` version. Extract these files and take a look inside the directory.

### Generating the makefile

You should notice a `configure` program. This program will perform a number of tests of our system and build a suitable makefile for use to use. We can then use this makefile to build OpenMPI. Take a look in the README under the installation options for all the different flag you can supply. We will need to specify at least a prefix. Run the following:

`./configure --prefix=/soft/openmpi`

This will take several minutes to complete. If it completes succesfully we will have a makefile to run.

### Building the source

Let's run the makefile. We will run the make command over numerous cores. In practice, it is a good idea to build your software on a powerful machine with many cores.

`make all -j`

Again, this will take several minutes to complete. If everything works, we can install to the directory specified (in prefix).

`make install`

## Monitoring progress
It can be useful to monitor the utilisation of your system during task execution. This will allow you to spot potential issues early on. For example, you might have specified the number of cores to use incorrectly, causing your job to run on fewer nodes that possible.

We will be installing a program called **htop**. This program is not in our current repositories, so we need to add the `epel-release` repository. This is a very useful repository full of tools needed for debugging, compiling programs and so on. You should install it right from the start. **Note:** it is a large repository.

`yum -y install epel-release`

Once this is done, install the **htop** program.

`yum install htop`

This will give us a nice representation of our system usage, as well as all processes active on our node. You can filter processes by user by adding the `-u` flag.

`htop -u hpc`

This will show only the processes used by the *hpc* user.



