#!/usr/bin/perl
use strict;
use warnings;

my $warningPattern = qr/([a-zA-Z0-9\-\_\/]*\.[a-z]*)\:([0-9]*)\: [warning]*\:/;

# getFileAndLineNumber(aString);
#   Parses aString looking for a source file and line number.
#	Returns a reference to an array storing the source file in index 0 and the
#	line number in index 1.
#	Returns 0 if aString is not a warning message.
sub getFileAndLineNumber {
	my $aString = shift;
	my @result;
	
	if ($aString =~ $warningPattern) {
		@result[0] = $1;
		@result[1] = $2;
		return \@result;
	}
	
	return 0;
}

# compareWarnings(fileAndLineNumber1, fileAndLineNumber2);
#	Compares fileAndLineNumber1 with fileAndLineNumber2, checking if the file 
#	names and line numbers match.
#	Return values:
#	  0: File names do not match.
#	  1: File names do match.
#	  2: File names and line numbers match.
sub compareWarnings {
	my $fileAndLineNumber1 = shift;
	my $fileAndLineNumber2 = shift;
	
	if ($fileAndLineNumber1->[0] eq $fileAndLineNumber2->[0]) {
		if ($fileAndLineNumber1->[1] eq $fileAndLineNumber2->[1]) {
			return 2;
		} else {
			return 1;
		}
	}
	
	return 0;	
}

# combineWarnings(anArray);
#	Parses anArray, looking for warnings and combining them if necessary.
#	Returns a reference to an array storing all printable warning messages.
# 	Returns 0 if there are no printable warning messages.
sub combineWarnings {
	my @anArray = @_;
	my $prev = 0;
	my $tempResultIndex = 0;
	my $i = 0;
	my @result;
		
	for my $index (0 .. $#anArray) {
		my $fileAndLineNumber = getFileAndLineNumber($anArray[$index]);
		
		if ($fileAndLineNumber != 0) {
			if ($prev != 0) {
				my $comparedResult = compareWarnings($prev, $fileAndLineNumber);
				
				# no matches, add tempResultIndex to the actual result
				if ($comparedResult == 0) {
					@result[$i] = $tempResultIndex;
					$i++;
					
					$prev = $fileAndLineNumber;
					$tempResultIndex = $prev;
				}
				
				# file names match, append new line number to tempResultIndex
				elsif ($comparedResult == 1) {
					$tempResultIndex->[1] = 
					  $tempResultIndex->[1] . ", " . $fileAndLineNumber->[1];
					  
					$prev = $fileAndLineNumber;
				}
			
			# set prev if it hasn't already been set
			} else {
				$prev = $fileAndLineNumber;
				$tempResultIndex = $prev;
			}
		}
		
		# add the last stored tempResultIndex
		if ($index == $#anArray) {
			@result[$i] = $tempResultIndex;
		}
	}

	(@result > 0) ? return \@result : return 0;
}

# getNumberOfWarningLines(aString);
#	Returns how many line numbers are present in aString.
sub getNumberOfWarningLines {
	my $aString = shift;
	my $numberOfWarningLines = split(',', $aString);
	
	return $numberOfWarningLines;
}

# printWarnings(anArray);
#	Parses anArray and prints out one warning for each file, if necessary.
sub printWarnings {
	my $anArray = combineWarnings(@_);

	foreach (@$anArray) {
		my $numberOfWarningLines = getNumberOfWarningLines($_->[1]);
		print("$numberOfWarningLines: $_->[0]: $_->[1]\n");
	}
	
	return 1;
}

1
