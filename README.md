# DirectoryWatch
This is more than a front end for md5deep.
Q What does md5deep do?
A It calculates the md5checksum for all files in the selected directories.  Using the appropriate flags
and redirection a file is generated listing all the checksums of all files including those in the 
subdirectories.  This hash.log file can be passed back to md5deep with appropriate flags and redirection 
at a later date to generate a difference or delt.log file between the present and previous state of the 
files in the selected directories.
Q So it is a simple GUI for md5deep.
A Not exactly.  Using the two log files a report is generated showing the date stamp and full path of 
CHANGED, NEW and MISSING files.
Q So it only does one directory
A Many can be specified (/bin, /boot, /sbin, /usr/bin /usr/sbin etc) all covered in the final report 
on changed, missing and new files.
