#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

double basic_calc(double a, double b, char mode){
  switch (mode) {
    case '+':
      return a+b;
    case '-':
      return a-b;
    case '*':
      return a*b;
    case '/':
      if(b!=0)
        return a/b;
      else{
        printf("Can't divide by 0\n");
        exit(1);
      }
    default:
      printf("Error, operator not in list\n");
        exit(1);
  }
}

// Fancy comp function to make qsort() work.
// Too much pointer action for my understanding
// and is shamelessly adapted from online documentation
// Returns if a is smaller, equal or bigger than b,. which qsort() needs
int comp(const void *a, const void *b) {
    return (*(double *)a - *(double *)b);
}

// Strips string so only wanted characters remain
void clean_string(char* s) {
    char* d = s;
    do {
        while (*d == ' ' || isalpha(*d)) { // isalpha() returns 0 if d is alphabet (not +-*/ etc...)

            ++d;
        }
    } while (*s++ = *d++);
}


int main(int argc, char *argv[]){

  // Repeat until user exits
  while (true)  {
    // Variables
    double avg_sum = 0,avg = -1,med[100],med_calc = -1;
    int increments = 0,mode;
    char num1[256],num2[256],ch_input[5],input[5],avg_input_char[100],med_input[100];
    char operators[5] = {'n','+','-','*','/'};
    // n for prettier operator function
    // otherwise input-1
    // UGLY!
    char freetext[1024]; // 1 Kbit



    printf("Basic calculator. Please select a mode\n");
    printf("1. Sum\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Square root\n");
    printf("6. Power\n");
    printf("7. Average\n");
    printf("8. Median\n"); // TODO
    printf("9. Free text\n"); // TODO
    printf("0. Exit\n");

    fgets(ch_input, sizeof(ch_input), stdin);
    sscanf(ch_input, "%s ", input);
    //input[strcspn(input, "\n")] = 0;
    // atoi() converts string to int, returns 0 if not a number
    // Works well when reading input and makes input filtering easy
    mode = atoi(input);
    switch (mode) {
      default:
        printf("Improper input. Enter only a number in the given range\n");
        break;
      case 1 ... 4: // If input in range 1-4
        printf("Enter 2 numbers to compute\n");
        fgets(num1, sizeof(num1), stdin);
        fgets(num2, sizeof(num2), stdin);
        printf("Result: %lf\n", basic_calc(atoi(num1),atoi(num2),operators[mode]));
        break;
      case 5:
        printf("Enter a number to compute\n");
        fgets(num1, sizeof(num1), stdin);
        if(num1 >= 0){
          printf("Result: %lf\n", sqrt(atoi(num1)));
        }
        else {
          printf("No support for imaginary numbers in this calc. Don't make dev rant.\n");
        }
        break;
      case 6:
        printf("Enter 2 numbers to compute\n");
        fgets(num1, sizeof(num1), stdin);
        fgets(num2, sizeof(num2), stdin);
        printf("Result: %lf\n", pow(atoi(num1),atoi(num2)));
        break;
      case 7:
        printf("Calculatinga average. Press enter to calculate\n");
        while (avg == -1) {
          printf("Enter a number\n");
          fgets(avg_input_char, 99, stdin);
          if(strcspn(avg_input_char, "\n") == 0 && increments != 0){ // If user only clicked enter
            avg = avg_sum/increments;
          }
          else{
            avg_sum+=atoi(avg_input_char);
            if(atoi(avg_input_char) != 0) increments++;
          }
        }
        printf("Result: %lf\n", avg);
        break;
      case 8:
        printf("Calculating median. Press enter to calculate\n");
        double med_num;
        while (increments < 100){
          printf("Enter a number\n");
          fgets(med_input, 99, stdin);
          med_num = atoi(med_input);
          if(strcspn(med_input, "\n") == 0 && increments != 0){
            break;
          }
          else if(med_num != 0){
            med[increments++] = med_num;
          }
        }
        qsort(med, increments, sizeof(med[0]), comp);
        if(increments % 2 != 0){
          med_calc = med[increments / 2];
        }
        else med_calc = (med[increments / 2] + med[increments / 2 - 1]) / 2;
        printf("Result: %lf\n", med_calc);
        break;
      case 9:
        printf("Enter formula to calculate\n");
        fgets(freetext, sizeof(freetext), stdin);
        freetext[strcspn(freetext, "\n")] = 0; // Manually set where formula ends
        clean_string(freetext);
        printf("%s\n", freetext);
        for(int i = 0;freetext[i] != 0;i++) printf("%c\n", freetext[i]);
        break;
      case 0:
        printf("Exiting...\n");
        exit(0);
    }
  }
}
