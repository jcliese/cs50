#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //check for right amount of command-line arguments
    if (argc != 2)
    {
        //print help
        printf("Usage: ./recover image\n");
        return 1;
    }
    else
    {
        //open file for reading with command-line argument
        FILE *file = fopen(argv[1], "r");
        //check for opening error
        if (file == NULL)
        {
            printf("Unable to open file.");
            return 1;
        }
        else
        {
            //init byte type
            typedef uint8_t BYTE;
            BYTE buf[512];
            int count = 0;
            char filename[8];
            FILE *img = NULL;
            //read file in 512 byte chunks
            while (fread(buf, sizeof(BYTE), 512, file) == 512)
            {
                //check for new jpeg
                if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff && (buf[3] & 0xf0) == 0xe0)
                {
                    //check whether init jpeg or additional
                    if (count == 0)
                    {
                        sprintf(filename, "%03i.jpg", count);
                        img = fopen(filename, "a");
                        if (img == NULL)
                        {
                            printf("Unable to open file.");
                            return 1;
                        }
                        fwrite(buf, sizeof(BYTE), 512, img);
                        count++;
                    }
                    else
                    {
                        fclose(img);
                        sprintf(filename, "%03i.jpg", count);
                        img = fopen(filename, "a");
                        if (img == NULL)
                        {
                            printf("Unable to open file.");
                            return 1;
                        }
                        fwrite(buf, sizeof(BYTE), 512, img);
                        count++;
                    }
                }
                //append data to jpeg
                else if (count > 0)
                {
                    fwrite(buf, sizeof(BYTE), 512, img);
                }
            }
            //close open img file
            fclose(img);
        }
        //close open reading file
        fclose(file);
    }

}
