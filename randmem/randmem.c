/* 
 * RandMem Benchmark Version 2 Copyright (c) Roy Longbottom 2010 
 *
 * From: http://www.roylongbottom.org.uk/randmem%20results.htm
 *
 * Several modifications to run on RP2350, (c) Michael Bell 2024
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 #include <malloc.h>
 #include <pico/stdlib.h>
 
absolute_time_t abs_start_time;
uint64_t microsecs;
double secs;

  void start_time()
  {
      abs_start_time = get_absolute_time();
  }

  void end_time()
  {
      microsecs = absolute_time_diff_us(abs_start_time, get_absolute_time());
      secs = microsecs * 1e-6;
  }  

int    testII(int jmax, int arraymax);
int    testIIR(int jmax, int arraymax);
int    testJI(int jmax, int arraymax);    
int    testJIR(int jmax, int arraymax);    
   
double testID(int jmax, int arraymax);    
double testIDR(int jmax, int arraymax);    
double testJD(int jmax, int arraymax);    
double testJDR(int jmax, int arraymax);    

int checkTime(int jmax);

// ************* GLOBAL VARIABLES **********
 
int    * xi;
volatile double * xd;

  #define version  "Pico Version 2"

double results[100][10];


double   runTime = 0.1; // 100 ms;


unsigned int  ramKB;
unsigned int  ramKBused;
int  arraymax;
int  arraymax1;
int  darraymax;
int  passes = 1;
int  passesDone;
int   randNumbers;
int   randMax;
char  startRam[200];



int testJIR(int jmax, int arraymax)    
{
    int i, j;
    int toti;
    
    start_time();
    
    for (j=0; j<jmax; j++)
    {
        toti = 0;
        for (i=0; i<arraymax; i=i+32)
        {
            xi[xi[i+28]] = xi[xi[i+30]];
            xi[xi[i+24]] = xi[xi[i+26]];
            xi[xi[i+20]] = xi[xi[i+22]];
            xi[xi[i+16]] = xi[xi[i+18]];
            xi[xi[i+12]] = xi[xi[i+14]];
            xi[xi[i+ 8]] = xi[xi[i+10]];
            xi[xi[i+ 4]] = xi[xi[i+ 6]];
            xi[xi[i+ 0]] = xi[xi[i+ 2]];
        }
    }
    end_time();
        
    return toti;
}

int testJI(int jmax, int arraymax)    
{
    int i, j;
    int toti;
    
    start_time();

    
    for (j=0; j<jmax; j++)
    {
        toti = 0;
        for (i=0; i<arraymax; i=i+32)
        {
            xi[xi[i+ 2]] = xi[xi[i+ 0]];
            xi[xi[i+ 6]] = xi[xi[i+ 4]];
            xi[xi[i+10]] = xi[xi[i+ 8]];
            xi[xi[i+14]] = xi[xi[i+12]];
            xi[xi[i+18]] = xi[xi[i+16]];
            xi[xi[i+22]] = xi[xi[i+20]];
            xi[xi[i+26]] = xi[xi[i+24]];
            xi[xi[i+30]] = xi[xi[i+28]];
        }
    }
    end_time();
        

    return toti;
}

int testIIR(int jmax, int arraymax)    
{
    int i, j;
    int toti;
    
    start_time();
    
    for (j=0; j<jmax; j++)
    {
        toti = 0;
        for (i=0; i<arraymax; i=i+32)
        {
            toti = toti & xi[xi[i+30]] | xi[xi[i+28]]
                        & xi[xi[i+26]] | xi[xi[i+24]]
                        & xi[xi[i+22]] | xi[xi[i+20]]
                        & xi[xi[i+18]] | xi[xi[i+16]]
                        & xi[xi[i+14]] | xi[xi[i+12]]
                        & xi[xi[i+10]] | xi[xi[i+ 8]]
                        & xi[xi[i+ 6]] | xi[xi[i+ 4]]
                        & xi[xi[i+ 2]] | xi[xi[i+ 0]];
        }
    }
    end_time();
        
    return toti;
}

int testII(int jmax, int arraymax)    
{
    int i, j;
    int toti;
    
    start_time();
    
    for (j=0; j<jmax; j++)
    {
        toti = 0;
        for (i=0; i<arraymax; i=i+32)
        {
            toti = toti & xi[xi[i+ 0]] | xi[xi[i+ 2]]
                        & xi[xi[i+ 4]] | xi[xi[i+ 6]]
                        & xi[xi[i+ 8]] | xi[xi[i+10]]
                        & xi[xi[i+12]] | xi[xi[i+14]]
                        & xi[xi[i+16]] | xi[xi[i+18]]
                        & xi[xi[i+20]] | xi[xi[i+22]]
                        & xi[xi[i+24]] | xi[xi[i+26]]
                        & xi[xi[i+28]] | xi[xi[i+30]];
        }
    }
    end_time();
        
    return toti;
}

int testIR(int jmax, int arraymax)    
{
    int i, j;
    int toti;
    volatile int* xvi = xi;
    
    start_time();
    
    for (j=0; j<jmax; j++)
    {
        toti = 0;
        for (i=0; i<arraymax; i=i+16)
        {
            (void)xvi[i+15];
            (void)xvi[i+14];
            (void)xvi[i+13];
            (void)xvi[i+12];
            (void)xvi[i+11];
            (void)xvi[i+10];
            (void)xvi[i+9];
            (void)xvi[i+8];
            (void)xvi[i+7];
            (void)xvi[i+6];
            (void)xvi[i+5];
            (void)xvi[i+4];
            (void)xvi[i+3];
            (void)xvi[i+2];
            (void)xvi[i+1];
            (void)xvi[i+0];            
        }
    }
    end_time();
        
    return toti;
}

int testI(int jmax, int arraymax)    
{
    int i, j;
    int toti;
    volatile int* xvi = xi;
    
    start_time();
    
    for (j=0; j<jmax; j++)
    {
        toti = 0;
        for (i=0; i<arraymax; i=i+16)
        {
            (void)xvi[i+0];
            (void)xvi[i+1];
            (void)xvi[i+2];
            (void)xvi[i+3];
            (void)xvi[i+4];
            (void)xvi[i+5];
            (void)xvi[i+6];
            (void)xvi[i+7];
            (void)xvi[i+8];
            (void)xvi[i+9];
            (void)xvi[i+10];
            (void)xvi[i+11];
            (void)xvi[i+12];
            (void)xvi[i+13];
            (void)xvi[i+14];
            (void)xvi[i+15];            
        }
    }
    end_time();
        
    return toti;
}

double testJDR(int jmax, int darraymax)    
{
    int i, j;
    double totd;
        

    start_time();
    
    for (j=0; j<jmax; j++)
    {
        totd = 0.0;
        for (i=0; i<darraymax; i=i+16)
        {
            xd[xi[i+14]] = xd[xi[i+15]];
            xd[xi[i+12]] = xd[xi[i+13]];
            xd[xi[i+10]] = xd[xi[i+11]];
            xd[xi[i+ 8]] = xd[xi[i+ 9]];
            xd[xi[i+ 6]] = xd[xi[i+ 7]];
            xd[xi[i+ 4]] = xd[xi[i+ 5]];
            xd[xi[i+ 2]] = xd[xi[i+ 3]];
            xd[xi[i+ 0]] = xd[xi[i+ 1]];
        }
    }
    end_time();

    return totd;
}

double testJD(int jmax, int darraymax)    
{

    int i, j;
    double totd;
        
    start_time();
    
    for (j=0; j<jmax; j++)
    {
        totd = 0.0;
        for (i=0; i<darraymax; i=i+16)
        {
            xd[xi[i+ 1]] = xd[xi[i+ 0]];
            xd[xi[i+ 3]] = xd[xi[i+ 2]];
            xd[xi[i+ 5]] = xd[xi[i+ 4]];
            xd[xi[i+ 7]] = xd[xi[i+ 6]];
            xd[xi[i+ 9]] = xd[xi[i+ 8]];
            xd[xi[i+11]] = xd[xi[i+10]];
            xd[xi[i+13]] = xd[xi[i+12]];
            xd[xi[i+15]] = xd[xi[i+14]];
        }
    }
    end_time();

    return totd;
}

double testIDR(int jmax, int darraymax)    
{
    int i, j;
    double totd;
        
    start_time();
    
    for (j=0; j<jmax; j++)
    {
        totd = 0.0;
        for (i=0; i<darraymax; i=i+16)
        {
            (void)xd[xi[i+15]];
            (void)xd[xi[i+14]];
            (void)xd[xi[i+13]];
            (void)xd[xi[i+12]];
            (void)xd[xi[i+11]];
            (void)xd[xi[i+10]];
            (void)xd[xi[i+9]];
            (void)xd[xi[i+8]];
            (void)xd[xi[i+7]];
            (void)xd[xi[i+6]];
            (void)xd[xi[i+5]];
            (void)xd[xi[i+4]];
            (void)xd[xi[i+3]];
            (void)xd[xi[i+2]];
            (void)xd[xi[i+1]];
            (void)xd[xi[i+0]];
        }

    }
    end_time();

    return totd;
}

double testID(int jmax, int darraymax)    
{
    int i, j;
    double totd;
        
    start_time();
    
    for (j=0; j<jmax; j++)
    {
        totd = 0.0;
        for (i=0; i<darraymax; i=i+16)
        {
            (void)xd[xi[i+0]];
            (void)xd[xi[i+1]];
            (void)xd[xi[i+2]];
            (void)xd[xi[i+3]];
            (void)xd[xi[i+4]];
            (void)xd[xi[i+5]];
            (void)xd[xi[i+6]];
            (void)xd[xi[i+7]];
            (void)xd[xi[i+8]];
            (void)xd[xi[i+9]];
            (void)xd[xi[i+10]];
            (void)xd[xi[i+11]];
            (void)xd[xi[i+12]];
            (void)xd[xi[i+13]];
            (void)xd[xi[i+14]];
            (void)xd[xi[i+15]];
        }
    }
    end_time();

    return totd;
}


int run_mem_test()
{
    int i, g, k;
    int jmax;
    int toti;
    double totd;
    double sbytes;
    double mega = 1024.0 * 1024.0;

    ramKB = 0x800000;
    arraymax = 1536;
    arraymax1 = arraymax;
    passes = 10;

    printf("\n");

    printf("\n   Random/Serial Memory Test %s \n", version);
    printf("         Integer.......................  Double/Integer................\n");
    printf("         Serial........  Random........  Serial........  Random........\n");
    printf("    RAM   Read   Rd/Wrt   Read   Rd/Wrt   Read   Rd/Wrt   Read   Rd/Wrt\n");
    printf("     KB  MB/Sec  MB/Sec  MB/Sec  MB/Sec  MB/Sec  MB/Sec  MB/Sec  MB/Sec\n\n");
  
    passesDone = 0;
    for (k=0; k<passes; k++) // 11
    {
        for (i=0; i<10; i++)
        {
            results[k][i] = 0;
        }
    }
    for (k=0; k<passes; k++) // 11
    {
        passesDone = k + 1;
        printf("%7d ", arraymax * 4 / 1024);

        xi = (int *)0x11000000;
        if (xi == NULL)
        {
           printf(" ERROR WILL EXIT\n");
           printf(" Press Enter\n");
           g  = getchar();
           exit(1);
        }
    
        // Serial Read Integer *********************

        for (i=0; i<arraymax+1; i++)
        {
            xi[i] = i+1;
        }
        jmax = 1;
        sbytes = 4.0;
        do
        {
            toti = testI(jmax, arraymax);
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][0] =  (double)arraymax * (double)jmax * sbytes / mega / secs;

        printf("%7.0f ", results[k][0]);
        fflush(stdout);
 

        // Serial Read/Write Integer *********************

        for (i=0; i<arraymax+1; i++)
        {
            xi[i] = i+1;
        }

        jmax = 1;
        sbytes = 4.0;
        do
        {
            toti = testJI(jmax, arraymax);    
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][1] =  (double)arraymax * (double)jmax * sbytes / mega / secs;
 
        printf("%7.0f ", results[k][1]);
        fflush(stdout);


        // Random Read Integer *********************

        srand(123);

        for (i=0; i<arraymax+1; i++)
        {
           xi[i] = (int)((double)arraymax * ((double)(rand()) / (double)2147483648.0));
       }


        jmax = 1;
        sbytes = 4.0;
        do
        {
            toti = testIR(jmax, arraymax);    
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][2] =  (double)arraymax * (double)jmax * sbytes / mega / secs;

        printf("%7.0f ", results[k][2]);
        fflush(stdout);

        // Random Read/Write Integer *********************

        srand(123);
        for (i=0; i<arraymax+1; i++)
        {
           xi[i] = (int)((double)arraymax * ((double)(rand()) / (double)2147483648.0));
        }

        jmax = 1;
        sbytes = 4.0;
        do
        {
            toti = testJIR(jmax, arraymax);    
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][3] =  (double)arraymax * (double)jmax * sbytes / mega / secs;


        printf("%7.0f ", results[k][3]);
        fflush(stdout);


        // xxxxxxxx Double

        darraymax = arraymax / 3;

        if (xi == NULL)
        {
           printf(" ERROR WILL EXIT\n");
           printf(" Press Enter\n");
           g  = getchar();
           exit(1);
        }

        xd = (double *)0x11400200;
        if (xd == NULL)
        {
           printf(" ERROR WILL EXIT\n");
           printf(" Press Enter\n");
           g  = getchar();
           exit(1);
        }


        // Serial Read Double *********************

        for (i=0; i<darraymax+1; i++)
        {
            xd[i] = 1.0;
            xi[i] = i+1;
        }
        jmax = 1;
        sbytes = 12.0;
        do
        {
            totd = testID(jmax, darraymax);       
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][4] =  (double)darraymax * (double)jmax * sbytes / mega / secs;

        printf("%7.0f ", results[k][4]);
        fflush(stdout);


        // Serial Read/Write Double *********************

        for (i=0; i<darraymax+1; i++)
        {
            xd[i] = 1.0;
            xi[i] = i+1;
        }
        jmax = 1;
        sbytes = 12.0;
        do
        {
            totd = testJD(jmax, darraymax);    
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][5] =  (double)darraymax * (double)jmax * sbytes / mega / secs;


        printf("%7.0f ", results[k][5]);
        fflush(stdout);


        // Random Read Double *********************
        
        srand(123);
        for (i=0; i<darraymax+1; i++)
        {
            xi[i] = (int)((double)darraymax * ((double)(rand()) / (double)2147483648.0));
            xd[i] = 1.0;
        }

        jmax = 1;
        sbytes = 12.0;    
        do
        {
            totd = testIDR(jmax, darraymax); 
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][6] =  (double)darraymax * (double)jmax * sbytes / mega / secs;


        printf("%7.0f ", results[k][6]);
        fflush(stdout);


        // Random Read/Write Double *********************

        srand(123);
        for (i=0; i<darraymax+1; i++)
        {
            xi[i] = (int)((double)darraymax * ((double)(rand()) / (double)2147483648.0));
        }

        jmax = 1;
        sbytes = 12.0;    
        do
        {
            totd = testJDR(jmax, darraymax); 
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][7] =  (double)darraymax * (double)jmax * sbytes / mega / secs;


        printf("%7.0f ", results[k][7]);
        fflush(stdout);

        printf("\n");
        fflush(stdout);
        arraymax = arraymax * 2;
    }

    printf("\n");
    printf("  Press Enter\n");
    g  = getchar();
    return 1;
    
} // runTests


int checkTime(int jmax)
{
    if (secs < runTime)
    {
          if (secs < runTime / 8.0)
          {
                jmax = jmax * 10;
          }
          else
          {
                jmax = (int)(runTime * 1.25 / secs * (double)jmax+1);
          }
      }
      return jmax;
}


