# images
this is a program to take observations and sort them by satellite number

The input file has satellite number, date, time, Right Ascension, Declination, and some other numbers that I need to look up
this was started from "observations" which I thought was sorting observations but the other files
were attempts that were not successful. The Right Ascension and Declination have understood colons (they are Hours, Minutes, Seconds and decimal Seconds) so they look like enormous numbers. I need to put in some fix for that, maybe just read them as characters since I don't think that I will use them as numbers. 

the idea is to sort various days of observations, where various satellites are imaged, and compile
a number of total observations of each satellite

Uses Qsort

The line of each observation is read in and then scanned, the line is read in as a string of characters
Output is not yet correct
