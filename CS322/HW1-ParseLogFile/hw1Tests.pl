#!/usr/bin/perl
use strict;
use warnings;
use Test::Simple tests => 10;

require "hw1.pl";

my @warnings;

@warnings[0] = "src/ext/BitBltPlugin.c:2407: warning: ‘halt’ defined but not used";
@warnings[1] = "src/ext/BitBltPlugin.c:2408: warning: ‘halt’ defined but not used";
@warnings[2] = "src/ext/BitBltPlugin.c:2408: warning: ‘halt’ defined but not used";
@warnings[3] = "src/ext/BitBltPlugin.c:23: warning: ‘halt’ defined but not used";
@warnings[4] = "src/ext/BitBltPlugin.c:24: warning: ‘halt’ defined but not used";
@warnings[5] = "src/ext/BitBltPlugin.c:24: warning: ‘halt’ defined but not used";
@warnings[6] = "src/ext/Plugin.c:2408: warning: ‘halt’ defined but not used";

my $regularMsg = "gcc -arch i386 -isysroot /Developer/SDKs/MacOSX10.5.sdk";

# getFileAndLineNumber tests
my $fileAndLineNumber = getFileAndLineNumber($warnings[0]);
ok($fileAndLineNumber->[0] eq "src/ext/BitBltPlugin.c");
ok($fileAndLineNumber->[1] eq "2407");

$fileAndLineNumber = getFileAndLineNumber($regularMsg);
ok($fileAndLineNumber == 0);

# compareWarnings tests
my $comparedResult = compareWarnings(getFileAndLineNumber($warnings[0]), getFileAndLineNumber($warnings[6]));
ok($comparedResult == 0);

$comparedResult = compareWarnings(getFileAndLineNumber($warnings[0]), getFileAndLineNumber($warnings[1]));
ok($comparedResult == 1);

$comparedResult = compareWarnings(getFileAndLineNumber($warnings[4]), getFileAndLineNumber($warnings[5]));
ok($comparedResult == 2);

# combineWarnings tests
my $combinedWarnings = combineWarnings(@warnings);
ok($combinedWarnings > 0);
ok($combinedWarnings->[0][0] eq "src/ext/BitBltPlugin.c");
ok($combinedWarnings->[0][1] eq "2407, 2408, 23, 24");

# getNumberOfWarningLines tests
ok(getNumberOfWarningLines($combinedWarnings->[0][1]) == 4);
