/* standard stuff
 as of 4 aug 2021
written to count up observations and sort by satellite number
 based on "observations", this is the one that I really wanted these are real observations
 better output, columns have labels
 this sort of works so far
 */

#include <stdio.h>
#include <ctype.h>  // page 1062 in book
#include <string.h> // strtok, strcpy stuff not even used yet
#include <stdlib.h> // atoi, atof not used yet
#include <math.h>  // math functions
#include <wordexp.h>

#include <fstream>  // moving towards better C++ file handling
// does NOT like fstream.h!!

#define SATELLITE_LENGTH 80  // length of each line of satellite report

using namespace std;

FILE* fileOpen(const char* filename, const char* openmode)
{
    wordexp_t expandedName;
    FILE* fileHandle; // output points to file to write calculate results to
    wordexp(filename, &expandedName, 0);
    fileHandle = fopen(expandedName.we_wordv[0], openmode);
    wordfree(&expandedName);
    return fileHandle;
}  // this apparently lets ~/ work

class Image  // this is what is in each Image line
{
public:
    // three fields: satellite number, telescope, # obs
    char line[SATELLITE_LENGTH];  // this is an Image line
    int satno;  // satellite number
    int date;  // date of image
    int time;
    int right_ascension; // of observation
    int declination; // of observation
    int column_six; // ?
    int magnitude; // magnitude maybe?
    int column_eight; // ?
    
  /*  float tleStrToFloat(char * in)  // need this for anything? sense text in file?
    {
        char temp[10];
        if(in[0] == '-') temp[0] = '-';
        else temp[0] = ' ';
        int offset = 1;
        if(isdigit(in[0])) offset = 0;
        temp[1] = '.';
        for (int i = 0; i < 4; i++){
            temp[2+i] = in[offset+i];
        };
        temp[6] = 'e';
        temp[7] = in[offset+5];
        temp[8] = in[offset+6];
        temp[9] = '\0'; // null character
        float b = atof(temp);
        return(b);
    }
   */
    
    Image(){}; // empty constructor
    Image(char *ob_line)  // fill in Image structure - event is one Image
    {
        strncpy(line, ob_line, sizeof(line));  // what is ob_line vs line?
        //strncpy(satnumber, line, sizeof(satnumber));
       
       // scan Image line
        sscanf(line, "%d   %d %d %d %d %d %d   %d", &satno, &date, &time, &right_ascension, &declination, &column_six, &magnitude, &column_eight);
     
    }  // end Image definition
    
   void print(FILE* spOutputObs)  // print to output file for parameters
    { //if no file given prints to stdout (i.e. terminal)
        fprintf(spOutputObs, "Satno \t Images \n");
        fprintf(spOutputObs, "%d\n", satno);
        fprintf(spOutputObs, "%d\n", date);
        fprintf(spOutputObs, "%d\n", time);
        fprintf(spOutputObs, "%d\n", right_ascension);
        fprintf(spOutputObs, "%d\n", declination);
        fprintf(spOutputObs, "%d\n", column_six);
        fprintf(spOutputObs, "%d\n", magnitude);
        fprintf(spOutputObs, "%d\n", column_eight);
        
        //        fprintf(stdout, "", );
    }  // end of print function
    
    
}; // odd to see } then ; end of Tle thing
 
int compareImagesSatelliteNumber(const void * a, const void * b) // sort satellite number
{
    if (((Image*)a)->satno  < ((Image*)b)->satno) return -1;
    if (((Image*)a)->satno == ((Image*)b)->satno) return  0;
    if (((Image*)a)->satno  > ((Image*)b)->satno) return  1;
/** MSM - satnumber is an array of char's  NOT a number so < and > aren't really valid.  need to use strcmp instead **/
  //  return strcmp((const char*)(((Image*)a)->satno), (const char*)(((Image*)b)->satno));
    return 0;
}

int main()
{
    FILE* spInputObs;  // a file of all the Images
    FILE* spOutputObs; // output points to file to write calculate results to
 
    spInputObs = fileOpen("/Users/Charles/Desktop/analyses/input_obs2.txt", "r");
    spOutputObs = fileOpen("/Users/Charles/Desktop/analyses/output_observations.txt", "w");
    
   // /Users/Charles/Desktop/analyses/input_obs.txt
    char line[SATELLITE_LENGTH];
    
    Image satellites[500];  // fill structure named satellites of 500 lines?
    
    int i = 0;
    while (feof(spInputObs) == 0) // read in all Images
    {
        fgets(line, sizeof(line), spInputObs);  // get first line of Images
        printf("the line: %s\n", line);  // debug
     
        satellites[i] = Image(line); //
          //printf("satnumber %s\t", satellites[i].satnumber);
        
        i++;   // increment i
        
    }  // end of while loop, reads Images
 printf("\n");
    
    int numObs = i;
    qsort(&satellites[0], numObs, sizeof(Image), compareImagesSatelliteNumber);
    
      fprintf(spOutputObs, "Satno \t Date \t Time \t Right Ascension \t Declination\n"); // not the final desired information
    
    for(int i = 0; i < numObs; i++)
        fprintf(spOutputObs, "%d\t %d\t %d\t %d\t %d\n", satellites[i].satno, satellites[i].date, satellites[i].time, satellites[i].right_ascension, satellites[i].declination);
    
    fclose(spInputObs);
    fclose(spOutputObs);
    // close all inputs and outputs, did not have that before

    }  // end of main
