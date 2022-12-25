#include "./../include/processB_utilities.h"

#include <stdio.h>
#include <bmpfile.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

/*
Simply accessing the shared memory (BitMap) and performing some feature extraction to display trajectory.
Step 0:
    Reduce teh pixels again with the factor of 20x so that we get normal circled value that we gave
    in the process A.

Step 1:
    We will get the pixels from the shared memory which is the bitmap by scanning the pixels
    using the function (bmp_get_pixel()) more details in header file of the bitmap
    /usr/local/include -> file containing the functions
    Which return the pixels that we had set in the process A 

Step 2:
    Scan whole pixels and do some feature extraction like Comparing each line passing from the circle
    to compute the length of the line and if length is equal to the diameter of the circle then the
    centered point of the circle is the mid point of the circle

Step 3:
Taking that mid point we draw the trajectory:
    BY storing all the mid points to an array and display these centre points(Pixels) along with the realtime
    coming centered pixels in to the screen
*/

// Data structure for storing the bitmap file
bmpfile_t *bmp;

// rgb_pixel_t pixel;
int red;
int blue;
int green;
int alpha;

int main(int argc, char const *argv[])
{
    /*
    int height = 600;
    int width = 1600;
    for(int x = 0; x <= height; x++) {
        for(int y = 0; y <= width; y++) {
            red = (bmp_get_pixel(bmp, x, y))->red;
            blue = (bmp_get_pixel(bmp, x, y))->blue;
            green = (bmp_get_pixel(bmp, x, y))->green;
            alpha = (bmp_get_pixel(bmp, x, y))->alpha;
            if(red == 255 && blue == 0 && green ==0 && alpha == 0){
                int first_colored_pixel[2] = {x, y};
                int count = 0;
                count++;
                if(count == 60){
                    printf("Middle of the cicle found\n");
                    //int centre = count/2;
                }
            }
            if(red == 255 && blue == 255 && green ==255 && alpha == 255){

            }
        }
    }*/
    
    // Utility variable to avoid trigger resize event on launch
    int first_resize = TRUE;

    // Initialize UI
    init_console_ui();

    // Infinite loop
    while (TRUE) {

        // Get input in non-blocking mode
        int cmd = getch();

        // If user resizes screen, re-draw UI...
        if(cmd == KEY_RESIZE) {
            if(first_resize) {
                first_resize = FALSE;
            }
            else {
                reset_console_ui();
            }
        }

        else {
            mvaddch(LINES/2, COLS/2, '0');
            refresh();
        }
    }

    endwin();
    return 0;
}
