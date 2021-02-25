#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include <WROVER_KIT_LCD.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

// Controller Class
WROVER_KIT_LCD tft;
#define SPDP double
static int taskCore = 0;
unsigned long start;
unsigned long end;
unsigned long execTimeOneTask, execTimeTwoTask, execTimeFourTask ;

void swapping(int &a, int &b) { 
   int temp;
   temp = a;
   a = b;
   b = temp;
}

void merge(int *array, int l, int m, int r) {
     int i, j, k, nl, nr;
     
     //size of left and right sub-arrays
     nl = m-l+1; 
     nr = r-m;
     int larr[nl], rarr[nr];
     
     //fill left and right sub-arrays
     for(i = 0; i<nl; i++)
        larr[i] = array[l+i];
     for(j = 0; j<nr; j++)
        rarr[j] = array[m+1+j];
     i = 0; j = 0; k = l;
     
     //marge temp arrays to real array
     while(i < nl && j<nr) {
        if(larr[i] <= rarr[j]) {
           array[k] = larr[i];
           i++;
        }else{
           array[k] = rarr[j];
           j++;
        }
        k++;
     }
     
     //extra element in left array
     while(i<nl) {       
        array[k] = larr[i];
        i++; k++;
     }
     
     //extra element in right array
     while(j<nr) {     
        array[k] = rarr[j];
        j++; k++;
     }
  }
  void mergeSort(int *array, int l, int r) {
     int m;
     if(l < r) {
        int m = l+(r-l)/2;
        // Sort first and second arrays
        mergeSort(array, l, m);
        mergeSort(array, m+1, r);
        merge(array, l, m, r);
     }
  }

void taskOne( void * parameter)
{
  String taskMessage = "Task running on core ";
  taskMessage = taskMessage + xPortGetCoreID();
  tft.println(taskMessage);
  
  // Random
  srand (time(NULL));  
  
  // Fill Array
  int size = rand() % 10;
  int array [size] = {};
  int x = 0;
  int y = 0;
  
  for(int i = 0; i<size; i++){
    x = sqrt(rand() % 100 + 1);
    y = sqrt(rand() % 100 + 1);
    array[i] = x*y;
  }
    
  // Bubble Sort
  for(int i = 0; i<size; i++) {
    int swaps = 0;         //flag to detect any swap is there or not
    for(int j = 0; j<size-i-1; j++) {
       if(array[j] > array[j+1]) {       //when the current item is bigger than next
          swapping(array[j], array[j+1]);
          swaps = 1;    //set swap flag
           }
       }
    if(!swaps)
       break;       // No swap in this pass, so array is sorted

  }
   
  // Merge Sort  
  mergeSort(array, 0, size-1);
    
    // Delete Task
    vTaskDelete( NULL );
 
}

void setup() {
  tft.begin();
  tft.fillScreen(WROVER_BLACK); //Clear screen
  tft.setCursor(0, 0); //Set upper left corner
  tft.setTextColor(WROVER_WHITE); //Set text colour
  tft.setTextSize(3); 
  
  double DMIPS, flops;
  start = micros();
  
  xTaskCreatePinnedToCore(
                    taskOne,          /* Task function. */
                    "TaskOne",        /* String with name of task. */
                    100000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL,
                    0);            /* Task handle. */
                    
  end = micros();
  execTimeOneTask = end - start;
  delay(1000);
  tft.println((int) execTimeOneTask);
  
  DMIPS = (100.0*1*1000)/execTimeOneTask;
  DMIPS = (DMIPS/1757)*100;
  tft.println("Dhrystone: MIPS");
  tft.println((int)DMIPS);
	flops = DMIPS*1000;
	tft.println("FLOPS");
	tft.println((int)flops,8);

}
 
void loop() {
  delay(1000);
}