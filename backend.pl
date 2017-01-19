#!/usr/bin/perl
#This is a backend to sort the results into Missing, New and Changed categories.
#The starting points are the hash.log and delta.log files.
#If a changed md5 is noted in the delta.log it is checked against the original hash.log
#and if not found it is classified as an additional file, if it's not found in the file 
#system it is classified as a missing file.  All other enteries in the hash.log are 
#classified as changed files.  If there are lots with the same date code they are most
#likely due to a system update, but this may not apply to Microsoft software as 
#Microsoft seems to be forever updating each time power is applied.
#This backend can be run stand alone or be called from the watcher program../m	

opendir(PROJECT, $ARGV[0]) or die "ARGV[0] = $ARGV[0] \n";
@projdir = readdir(PROJECT);
closedir(PROJECT);

print "In backend.pl argv0 = $ARGV[0] \n";

open (CHANGED, ">$ARGV[0]/changed.log");
open (MISSING, ">$ARGV[0]/missing.log");
open (NEW, ">$ARGV[0]/new.log");
print(CHANGED "The changes between the hash.log and current state are listed here.\n");
print(MISSING "  Files missing between the hash.log and current state are listed here.\n");
print(NEW "  Additional files between the hash.log and current state are listed here.\n");

foreach $projdir (@projdir) {
	$temp = substr($projdir, 0, 1);
	if( $temp eq "_") {
#print "argv projdir $ARGV[0] $projdir \n";

		print (CHANGED "\n \t Present directory is $projdir \n");
		print (MISSING "\n \t Present directory is $projdir \n");
		print (NEW     "\n \t Present directory is $projdir \n");

			if( -e "$ARGV[0]$projdir/delta.log") {
				process();
				lostmissing();
			}
			else {
				print(CHANGED "There is no delta.log.\n");
				print(NEW "There is no delta.log.\n");
			}


	}
}
close (CHANGED);
close (MISSING);
close (NEW);
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sub process {
print "Starting process  $ARGV[0] / $projdir \n \n";
open (DELTA, "$ARGV[0]$projdir/delta.log");
	while(<DELTA>) {
		chomp;
		if($_ ne "") {			
			my @file = split(/ /, $_);
			my $deltafile = $file[2];
			if( -e $deltafile) {
				ckhash($deltafile);	# need to see if it's in hash.log.
			}
			else {
			print (MISSING "Missing file $deltafile is no longer prescent \n");
			}
			}
	}
close (DELTA);
print "Exit process\n";
}
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sub ckhash {
print "\n Start ckhash $_[0], $ARGV[0], $projdir \n \n";
$retval = system("grep $_[0] $ARGV[0]$projdir/hash.log" ); 
print "retval is $retval \n \n";
if ($retval) {
	print (NEW "$_[0]\t");
	my $temp = dateadd($_[0]);
	print (NEW "$temp\tnew file.\n");
}
else{
	print (CHANGED "$_[0]\t");
	my $temp = dateadd($_[0]);
	print (CHANGED "$temp\tchanged.\n");
}
}
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sub dateadd {
print "Start dateadd $_[0]\n";

my $date = `ls -l -G --time-style=+%Y-%m-%d  $_[0]`;
my @file = split (/ /, $date);
return $file[4];
}
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sub lostmissing {
print "\n \t In lostmissing\n";
open (HASH, "$ARGV[0]$projdir/hash.log");
	while(<HASH>) {
		chomp;
#print;
#print "\n";
		if($_ ne "") {
			@file = split(/ /, $_);
#print "$file[3] is in hash\n";
			if ( -e $file[3])
				{ }
			else {
				print (MISSING "$file[3]\tis missing \n");
			}
		}
	}
close (HASH);
print "\n\t Exit lostmissing \n";
}
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
