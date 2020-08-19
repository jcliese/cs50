#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    else
    {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
            printf("Unable to open file.");
            return 1;
        }
        else
        {
            typedef uint8_t BYTE;
            BYTE buf[512];
            int count = 0;
            char filename[8];
            FILE *img = NULL;
            while(fread(buf, sizeof(BYTE), 512, file) == 512)
            {
                if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff && (buf[3] & 0xf0) == 0xe0)
                {
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
                        count++;
                        fclose(img);
                        sprintf(filename, "%03i.jpg", count);
                        img = fopen(filename, "a");
                        if (img == NULL)
                        {
                            printf("Unable to open file.");
                            return 1;
                        }
                        fwrite(buf, sizeof(BYTE), 512, img);
                    }
                }
                else if (count > 0)
                {
                    fwrite(buf, sizeof(BYTE), 512, img);
                }
            }
            fclose(img);
        }
        fclose(file);
    }

}
