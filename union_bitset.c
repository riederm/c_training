//gcc 5.4.0

#include  <stdio.h>


typedef struct {
   unsigned int hour    : 5;
   unsigned int minutes : 6;
   unsigned int seconds : 6;
   unsigned int day     : 5;
   unsigned int month   : 4;
   unsigned int year    : 12;
   int code    : 26;
} StampedErrorCode;

typedef union ErrorCode{
    long long int raw;
    StampedErrorCode code;
} ErrorCode;


int main(void)
{
    ErrorCode data;
    data.raw = 131809282883593;

    
    printf("%02d:%02d:%02d %02d.%02d.%d\n", 
         data.code.hour, 
         data.code.minutes, 
         data.code.seconds,
         data.code.day,
         data.code.month,
         data.code.year);
    
    printf("code:\t%d\n", data.code.code);
}
