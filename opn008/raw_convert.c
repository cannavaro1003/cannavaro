
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define WIDTH   (328)
#define HEIGHT  (248 * 3)
#else
#define WIDTH   (5)
#define HEIGHT  (10)
#endif

typedef unsigned short  PIXEL_DATA;    /* define pixel data, 16 bit per pixel */


int main(void)
{
    FILE *fp_input = NULL;
    FILE *fp_output = NULL;
    int file_size = 0;
    int frame_count = 0;
    
    PIXEL_DATA B[HEIGHT][WIDTH];
    
    char path[256];
    char outpath[256];
    
    int i,j,k;
    

    printf("Please input the file path: ");
    scanf("%s",path);
    if((fp_input = fopen( path, "rb" )) == NULL){
        printf("can not open the image \n" );
        return;
    } else {
        fseek(fp_input,0L,SEEK_END);

        /* get the size of file */
        file_size = ftell(fp_input);       
        if ((file_size % (WIDTH * HEIGHT * 2)) || (0 == file_size)) {
            printf("file size is %d, date formate mismatch \n", file_size);
            return;
        } 
 
        frame_count = file_size / (WIDTH * HEIGHT * 2);
        printf("read file OK, file size: %d, frame count: %d \n", file_size, frame_count);
    } 

    /* save the date */
    printf("Please input the file path for save: ");
    scanf("%s",outpath);
    if (( fp_output = fopen( outpath, "wb" ) ) == NULL )
    {
        printf("can not create the file : %s\n", outpath );
        return;
    }


#if 1
   
    fseek(fp_input,0L,SEEK_SET);
            
    for( k = 0; k < frame_count; k++ ){
        for( i = 0; i < HEIGHT; i++ ){
            for( j = 0; j < WIDTH ; j ++ ){
                fread( &B[i][j], 2, 1, fp_input );
                //printf("PIXEL[%d][%d]  %x; ", i, j, B[i][j]);
                B[i][j] = (((B[i][j] & 0x000f) << 12) | ((B[i][j] & 0xfff0) >> 4));    
                //printf("PIXEL[%d][%d]  %x; \n ", i, j, B[i][j]);
            }
        }

        for( i = 0; i < HEIGHT; i++ ) {
            for( j = 0; j < WIDTH ; j ++ ) {
                fwrite( &B[i][j], 2 , 1, fp_output );
                //printf("write PIXEL[%d][%d]  %x; \n ", i, j, B[i][j]);
            }
        }       
    }
    fclose(fp_input);
    fclose(fp_output);


#endif    
 
}

