#/bin/sh
echo Welcome, $USER
# Display working directory
pwd
# Display summary of files
ls -l -h
# Display summary of home usage
du -h -d 1 $HOME
