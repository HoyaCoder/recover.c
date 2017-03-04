//* 
//  Author James Meehan
//  CS50 PSET4 Recover
//
//*

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// create a type of unsigned integers of length of 8 bits (1 byte)
typedef uint8_t BYTE;

int main (int argc, char *argv[])
{
      // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover imagefile\n");
        return 1;
    }
    
    // remember filename
    char *infile = argv[1];
    FILE *image = fopen(infile, "r");
    
    // open input file
     if (image == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
// name for jpgfiles 
char jpgname[8];
         
// create buffer array
BYTE buffer[512]; 
    
// create outfile
FILE *output = NULL;
    
// create counter to track name new image files
int count = 0;

//read into buffer until EOF    
while (fread(buffer, 512, 1, image) == 1 ) 
{

//read until jpeg is found
if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
    {
        //close file if one is open
        if (output != NULL) 
        { 
            fclose(output); 
        }

        //create a new file
        sprintf(jpgname, "%03i.jpg", count); 

        // open file and give write permissions
        output = fopen(jpgname, "wb"); 

        if (output == NULL)
        {   
            fprintf(stderr, "Error! Could not create the file!\n");
            return 1;
        }

        //write 512 bytes 
        fwrite(buffer, 512, 1, output);
        
        //increment jpeg count
        count++;
    }
    
else if(output != NULL)
    {
    //write 512 bytes
    fwrite(buffer, 512, 1, output);
    }

}
//close files
if (output != NULL)
{
fclose(output);
}

fclose(image);

return 0; 
}
