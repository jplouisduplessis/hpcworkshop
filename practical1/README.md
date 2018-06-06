# Lab Activity - Linux Fundamentals
The purpose of this practical is to familiarise you with the Linux operating system and your most powerful tool: The Linux **shell**. In an HPC environment you will typically not have access to a graphical user interface, as this consumes uneccessary resources that could rather be spent on doing computations. Instead, you will be required to type many of the commands to install software and configure settings by hand. This is done in the Linux **shell**. It is therefore important that you learn how to use the **shell** effectively. To this end, there are several concepts that need to be mastered. They are the following:

* The Linux file system
* Environmental variables
* Users, groups and file permissions
* Packages, repositories and dependencies
* Retrieving files from different sources
* Modifying files from the **shell**
* Building software from source
* Basic **shell** commands and required applications relating to the concepts above
* Automating tasks

## Background
To complete this practical, you will need a little background on a few of the concepts listed above. Before attempting the practical, please work through the following sections and make sure you understand each one.
## Shell Commands
To run a command in the Linux terminal, simply type the name of the command/program followed by any arguments. For example, 

`ls -la`

The command in this example is **ls** and the argument *la*. This will list all files and folders in the current directory - including hidden files), along with information such as the size on disc (in blocks) and file permissions.
Refer to the __*Linux Command Cheatsheet*__ for a list of common commands. You can use the `man` command to get help for most of these functions. For example:

`man ls`

This will bring up a help file - sometimes called manual page - for the `ls` command. From here you can see that the *l* flag is for displaying the output in a long format, and the *a* is for including hidden files. They can also be used seperately.

`ls -l -a `

This is longer, but will have the same effect.

### Running as root
Some commands will require additional privileges. Examples include installing software and modifying configuration files located in folders such as */etc*. These commands will typically be run as the root user. We can switch to the root user with the folling command:

`sudo -s`

However, it is not good to work as root as any files created will only accessible by the root user by default. We will therefore execute commands as root temporarily using the `sudo` command. 

`sudo mkdir /var/soft`

This will run the `mkdir` command as root. Once the command has executed the shell will return to our current user. This way we only do things as root when absolutely necessary.

#### Side Note
If you run a command and find it it requires root permission, you can issue the following command:

`sudo !!`

This will run the previously issued command as root.

### Pipe commands
Output from the Linux terminal can be directed to annother program by using the pip (|) character followed by the program/command. A common example is to use `|less` to display the output in a scrollable way. For example, try running the follofing command:

`find /lib/`

This will print a long list of outputs displaying all files in the /lib directory. Suppose we wanted to scroll though this list? We can pipe the output to **less** to do this.

`find /lib/ | less`

Now we can use the arrow keys to scroll up and down through the output. Another command pipe is **grep**. This allows use to apply a *filter* to the output. Suppose we only want files that contain the word **linux**. We can use **grep** as follows:

`find /lib/ |grep linux`

Notice that the word "linux" is now displayed in colour to highlight the match. There is still a lot of output generated, so lets combine the **less** and **grep** commands:

`find /lib/ |grep linux |less`

First we apply the filter using **grep**, and then we pipe that output to the **less** command. The result is a scrollable output with only entries containing the word "linux". 

## Installing software
There are two ways of installing software in Linux. The first is by downloading and compiling source code files and moving them to a specified directory. This has the advantage of being optimised for your system, and is the way that you will install most of your HPC software.

The second (and easier) way is to make use of the package manager. Software is installed by the package manager out of repositores. You can add additional repositores for third-party software, though you should make sure that you can trust these repositories first. To install a package in CentOS, use the `yum` command. You will need to run the command as root.

`sudo yum install packagename`

### Side Note
When adding new repositories, you may need to run an update command first to determine which packages are available (not necessary on CentOS). 

Doing an update on CentOS will update all existing packages, so it can take a while to do. You can update individual packages by running `yum update packagename`.

There is also a `groupinstall` option that can be useful to install a number of related packages. You will see this in action when building your cluster.


While installing from packages is the preferred (and simpler) way to install software - it is the most stable - it can often times mean your software is slightly out of date as it depends on which version of the software is currently available in the repositories. This is another reason why we install our HPC software from source.

### The Linux file system
There are several key folders you need to be aware of.
1. The root (/)
2. User directories - sometimes referred to as the home directory  /home
3. Temp /tmp

#### Root (/)
This is the mounting point of your Linux system and is the top-most level in the directory structure. To write to this directory will require root privileges ( See [file permissions](#file-permissions) ).
#### /home
By default, all the home directories of your users will be created here. You are able to change this however, as you will see in later practicals. The home directory is located in / by default. The user that owns the directory can modify this directory. A user can access his or her directory with the following path:

`/home/username/`

There is also a shortcut using the `~/` syntax. For example: `~/Documents` will refer to the *Documents* folder of the current user.

Depending on the system, the home directory will containg the following structure be default:

- /home
  - /user
    * Downloads
    * Documents
    * Pictures
    * Videos

#### /tmp Directory
This directory will get cleaned periodically. It is a useful directory to put things you don't want to keep. i.e. temporary installation files while compiling and so on. It is also located in /.

## File paths
There three ways to refer to paths. The first is through absolute paths. Absolute paths will always start at root. For example, the absolute path to the *Documents* folder of the current user would be `/home/user/Documents`, where *user* is the name of the current user.

Relative paths on the other hand work according to the current directory. So, for example, assuming I am currently in my home directory, I would be able to access the *Documents* directory simply by using "Documents".

The third way is through [environmental variables](#Environmental-variables). There is a special variable called `HOME` that refers to the current user's home directory. You can use this in scripts to copy/create files in a user's home directory.


You can change your current directory using the `cd` command. For example: `cd ~/Documents` would change the current directory to the *Documents* folder of the current user. 

To move back one directory in a relative path, simply use the **../** path. So suppose I want to access the *Picture* directory in my home directory, and I am currently in *Documents', I would be able to user `../Pictures`. In other words, go back on directory, and from there find the Pictures directory.

## File permissions
Linux allows really fine control over who may access a file. You can specify read (r), write (w) and execute (x) permissions. A common use case in a cluster is to give execute privileges to user on software, while only allowing the root user too make changes to the program. File permissions consist of two categories namely - the user and the group. We can display the file permission of all files in a folder using the `ls -la /folderorpath` command. Read the following link for more information on how to interpret the results: https://en.wikipedia.org/wiki/Ls

You can modify the permissions on a file using the `chmod` (see [this link](https://en.wikipedia.org/wiki/Chmod) for a summary)  and `chown` commands.

## Variables
The Linux shell allows you to create temporary variables. These can be very useful in scripts, allowing for things such as string manipulation and even some basic arithmetic. To declare a variable, simply user the following syntax:
```    
variable=value
```
The value can be a number, string or even the result of a Linux command. For example:

`contents=$(du /home -h)`

This will run the "du" command and store the output in a variable named *contents*. To access the value stored in the a variable, use `$variable`. For example, we can print the value of the *contents variable with the following command:

`echo $contents`

### Environmental variables
Environmental variables describe things such as where to look for programs or code libraries, proxy settings and the location of special locations such as the current user's home directory. You should be aware of the following variables:

* PATH
* HTTP_PROXY, HTTPS_PROXY, FTP_PROXY
* HOME

Later on in the workshop, you will learn how to use these variables to create powerful scripts that can be used to automate certain tasks. For the purpose of this practical, we will be focussing on the **PATH** variable.

To set an environmental variable, user the `export` command. This will make the variable globally available in the current termiinal session. To make a variable permanent (i.e. exist after logout), you will need to add it to the */etc/profile* or *~/.bash_profile* files. For example, to create a variable called MYDIR that refers to some useful diretory on the machine, use the following:

`export MYPATH=/pathtowhatever`

To make it permanent, add `export MYPATH/pathtowhatever'` to the */etc/profile* file. This will set the variable for **all** user when they log in.
#### The PATH variable
Roughly speeking, this variable indicates where the shell should look for program names. In other words, whenever you type a program name in the shell, it will look in all the directories included in **PATH** to find the program. You can check the current **PATH** variable by typing the following:

`echo $PATH`


#### Prepending or appending paths to PATH
You can add a path to PATH using the following syntax. For example, suppose we want to add */somepath/* to our **PATH** variable:

`PATH=/somepath/:$PATH`

## Automating tasks
If there are several tasks that need to be performed on all your nodes in exactly the same manner, it can be useful to create a small script. This will save your time, and will ensure that each node is identical. In Linux, script files can be written in **bash** which basically lets as insert normal **shell** commands into a file, and then execute them all at once by running the script. Scripts are also useful for copying files accross the network onto all the nodes in our cluster. You can create a script for example that will copy the specified file to the specified directory to **all** nodes automatically. You will see an example of this in the Networking practical.

## Editing files
By default, there are two programs that can be used to edit files in the terminal. These two programs are **nano** and **vi**. You can open a file for editing in **nano** by typing the following command:

`nano /pathtofile`

For example, suppose we want to print a message when the user logs in. To do that, we can edit the /etc/profile file.

`nano /etc/profile`

To navigate, use the arrow keys. To save changes, type `ctrl+X`. Try adding the following command to the file:

`printf "********Welcome\033[0;32m $USER! \033[0m"********`

This will print the current user's username (can you see why?) in green whenever he or she logs in to the terminal.
### vi editor
Nano is a very simple tool to use. **vi** by contrast, is a lot harder to learn, but offers additional features such as being able to search for text, replace words, copy and paste. Though it falls outside the scope of this course, it is worth spending some time trying to learn it. 

### Side Note
There is an extended version of **vi** called **vim** that I would recommend using instead. It has numerous useful plugins and has syntax highlighting for common source and config files. You can install it by running `yum install vim` on CentOS or `apt install vim` on Ubuntu. To install plugins, look at [the following](https://github.com/VundleVim/Vundle.vim) link.

## Practical Instructions
You have been given an virtual machine with a minimal installation of CentOS 7. In this practical, you will get this virtual machine up and running. 



### Step 1 - Getting your bearings
Two user accounts have been created, *root* and and an admin account called *hpc*. The details of each are listed in the table below.

Username | Password
------------ | -------------
root| hpcworkshop
hpc | hpc2018

Make use of the *hpc* user and login to your machine.

Once you are logged in, lets get some information about our machine. 
Start by printing the full path of your current directory, and list all the files and directories along with their permissions.

<!-- Solution: `pwd; ls -la` -->

Next, print a summary of what will happen automatically each time your **current** user logs in.

<!-- Solution: `cat .bashrc` -->

Next, append a custom welcome message for your current user. Hint: you can echo a string to the .bashrc file as follows:

`echo "echo some message..." >> .bashrc`

Make sure you use **>>** and not **>**, as this will replace the contents of the *.bashrc* file!

Check that your message is working by logging out and back in again.

<!-- Solution: Add the following to *.bashrc*. `echo Welcome admin user. Have a great day` -->

Next, we need to check that the **nano** program is installed. If it is not installed, you need to install it (unless you want to try to use **vi** for the remainder of this practical).
<!-- Solution: `which nano` or just try running **nano**. To install run `sudo yum install nano` -->
At this point, your installation will probably fail. This is because we are behind a proxy. We will need to set an environmental variable called `HTTP_PROXY` in order to proceed. Create a file called `ufs.sh` in the `/etc/profile.d/` folder. Inside this folder, add the following three environmental variables:

Variable | Value
---------|-------
HTTP_PROXY | http://196.255.243.15:3128
HTTPS_PROXY | http://196.255.243.15.3128
FTP_PROXY| http://196.255.243.15:3128

<!-- Solution: `touch /etc/profile.d/ufs.sh` and add `sudo echo 'export http_proxy=http://196.255.243.15:3128' >> /etc/profile.d/ufs.sh` -->
Now, switch to the root user and install nano.
<!-- Solution: sudo -s; yum install nano -->

As a final step, we will create a small script and make it accessible throught the system. First, create a file in your home directory and add the following to it:

`du -h -d 1 $HOME`

Now, move this file to the following folder: `/var/soft/`. **Note: ** You will need to create this folder.
<!-- Solution: `sudo mkdir -p /var/soft; sudo mv filename /var/soft/filename` -->

Check the permissions that are currently present on this file.

<!-- Solution: ls -l /var/soft/filename -->
At this stage, only your user can read and write to this file. However, we would like everyone on the system to be able to execute this file. Modify this file so that it is executable by all users, and then try to execute this file. What is the output you get?

<!-- Solution: sudo chmod 755 /var/soft/filename -->

Finally, we need to add this program to the **$PATH** variable. You can modify the variable, but we will make use of another technique. 

Recall that linux software is located in /bin. However, we don't want to put our program there directly. Instead, we will make use of linking. Linux allows us to create links between folders using the `ln` command. Let's make use of this to add our "program" to `/bin`.

`sudo ln -s /var/soft/filename /bin`

Check that the link was created by running the following:

`ls -l /bin |grep filename`

Notice that the `ls` command shows the link. Now we can run our "program" from anywhere. Try it out.

### Section 2 - Working with services
Start by checking which services are currently running. You should check specifically whether or not the **NetworkManager** services is running.


<!-- Solution: `ps -ax |grep NetworkManager` or `systemctl status NetworkManager` -->

As you will see in later practicals, some services will need to be restarted after making changes to their configuration files. We will also disable some service. Try to restart the NetworkManager service.

<!-- Solution: `systemctl restart NetworkManager` -->

Finally, stop the NetworkManger service, and then disable it.

<!-- Solution: `systemctl stop NetworkManager; systemctl disable NetworkManager`; -->

### Section 3 - Installing from source
Download the tarball from the following link using the **wget** command:

`https://github.com/jplouisduplessis/hpcworkshop/blob/master/practical1/textgen.tar.gz`

Much of the software you will get off the internet will be packaged in this format. You need to extract these files to proceed. After you have downloaded the files, follow the instructions in README.md and build and install this program into the `/var/soft/ directory and make the program accessible throughout the system. Be sure to set the correct permissions.

Once you have installed the software, run it with two arguments: 100000000 test.txt. This will create a file called *test.txt* in the current directory that contains 10000000 characters.
<!-- Solution: `tar  -->
### Section 4 Automating tasks
Create a script called **summary.sh**. The script should do the following:
1. Display the current working directory and user.
2. Display a summary of the current users' home directory's files and directories.
3. Display the disc usage of the user's home directory.

Make sure that this script gets run each time any user logs in.


