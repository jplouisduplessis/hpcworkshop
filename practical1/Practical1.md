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

### The Linux file system
There are several key folders you need to be aware of.
1. The root (/)
2. User directories - sometimes referred to as the home directory  /home
3. Temp /tmp
4. Other directories in root (etc, lib, usr)

#### Root
#### home

#### tmp Directory

#### etc
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

`find /lib`

This will print a long list of outputs displaying all files in the /lib directory. Suppose we wanted to scroll though this list? We can pipe the output to **less** to do this.

`find /lib | less`

Now we can use the arrow keys to scroll up and down through the output. Another command pipe is **grep**. This allows use to apply a *filter* to the output. Suppose we only want files that contain the word **linux**. We can use **grep** as follows:

`find /lib |grep linux`

Notice that the word "linux" is now displayed in colour to highlight the match. There is still a lot of output generated, so lets combine the **less** and **grep** commands:

`find /lib |grep linux |less`

First we apply the filter using **grep**, and then we pipe that output to the **less** command. The result is a scrollable output with only entries containing the word "linux". 
### Variables and environmental variables
The Linux shell allows you to create temporary variables. These can be very useful in scripts, allowing for things such as string manipulation and even some basic arithmetic. To declare a variable, simply user the following syntax:
```    
variable=value
```
The value can be a number, string or even the result of a Linux command. For example:

`contents=$(du /home -h)`

This will run the "du" command and store the output in a variable named *contents*. To access the value stored in the a variable, use `$variable`. For example, we can print the value of the *contents variable with the following command:

`echo $contents`


Environmental variables describe things such as where to look for programs or code libraries, proxy settings and the location of special locations such as the current user's home directory. You should be aware of the folowing variables:

* PATH
* HTTP_PROXY, HTTPS_PROXY, FTP_PROXY
* HOME

Later on in the workshop, you will learn how to use these variables to create powerful scripts that can be used to automate certain tasks. For the purpose of this practical, we will be focussing on the **PATH** variable.

#### The PATH variable
Roughly speeking, this variable indicates where the shell should look for program names. In other words, whenever you type a program name in the shell, it will look in all the directories included in **PATH** to find the program. You can check the current **PATH** variable by typing the following:

`echo $PATH`

### Automating tasks
If there are several tasks that need to be performed on all your nodes in exactly the same manner, it can be usefull to create a small script. This will save your time, and will ensure that each node is identical. In Linux, script files can be written in **bash** which basically lets as insert normal **shell** commands into a file, and then execute them all at once by running the script. Scripts are also useful for copying files accross the network onto all the nodes in our cluster. You can create a script for example that will copy the specified file to the specified directory to **all** nodes automatically. You will see an example of this in the Networking practical.


## Practical Instructions
Now that you have the required background, your can start with the practical.

### Step 1 - Extracting installation files
Often times software will come packages as a tar.gz file.
Create a directory in /tmp called *work*.


### Step 2 - Compiling the program


### Bonus Step
Create a script file called practical1.sh that will allow the user to specify the working directory to use, and will then execute steps 1 - 4 automatically using this directory.
