#!/usr/bin/perl
use strict;
use warnings;

require "hw1.pl";

my $inFile;
my @linesOfText;

# store each line from the log file in an array
open $inFile, '<', "mklog";
@linesOfText = <$inFile>;
close $inFile;

printWarnings(@linesOfText);
