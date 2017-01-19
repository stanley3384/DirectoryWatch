DirectoryWatch is intended to give an assurance that nothing suspicious has been changed, added or deleted from one or many selected directories. (ie /bin, /usr, /boot, /etc or whatever is choosen.).
The engine used to record the state of the directories is md5deep which generates a hash (hash.log) file for each watched directory.  This engine is also able to detect changes to the hash file and they are held in delta.log in the watched directory.  Finally, a pearl script is run to generate changed.log, new.log and missing.log files that are displayed with date stamps.
This is cobbled into a gui using glade and Gtk3+ to make it simple to use by less than expert linux home user.
It is intended that a flash stick be dedicated to hold the software, log files and selection information.
This flash stick should not be left in the system and the program only needs to be used as assurance after a suspicious event.  The flash stick is intended to be used to watch over multiple systems.  It may be possible to run DirectoryWatch from the data part of Knoppix live distro enabling DirectoryWatch to watch over any live bootable hardware.
To be continued.
again continue

# test line
