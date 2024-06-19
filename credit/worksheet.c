#include <cs50.h>
#include <stdio.h>
#include <math.h>

// function to find number of digits
int count (long number)
{

int count = 0;

while (number >= 1)
{
    number = number/10;
    count++;
}
return (count);
}

// function to check sum

long checksum (long number)

{
//CHECK SUM ALGO
long x;
long y;
int sum1 = 0;
int sum2 = 0;
int r1;
int r2;
int n;

for (n = -1; n > -18; n = n - 2) //taking the second to last digit
{
    x = (number * pow(10, n)); // the negative power of 10 is the iteration variable
    y = x % 10;
    y = y * 2;

    if (y < 9)
    {
        sum2 = sum2 + y;
    }
    else //making sure all values greater than 10 is added together
    {
        r1 = y % 10;
        r2 = (y / 10) % 10;
        sum2 = sum2 + r1 + r2;
        }
}

int i = 0;
long s = 0;
long z = 0;
int sumT = 0;

for (i = 0; i > -18; i = i - 2) //taking the last digit
{
    s = (number * pow(10, i)); // the negative power of 10 is the iteration variable
    z = s % 10;

    sum1 = sum1 + z;

}
//total of sum 1 and 2
sumT = (sum1 + sum2) % 10;
return (sumT);

}








int main(void)
{

// PROMPT USER TO ENTER NUMBER

long number;

do
{
    number = get_long("Number: \n");

}
while (number < 0);

//OBTAIN STARTING NUMBERS OF CREDIT CARD

long startNum;
startNum = number;

while (startNum > 100)
{
   startNum = startNum/10;
}


 // extracting the first and second digits of startNum
int fdig;
fdig = (startNum/10 % 10);
int sdig;
sdig = (startNum % 10);

// TEST 369421438430814 (invalid), 4062901840 (invalid), 5673598276138003 (invalid)
//CARD TYPE ID

// valid  if number's sumT % 10 == 0
// AMEX if number's count == 15 and digits start with 34, 347
// MASTER if number's count == 16 and starts with 51 - 55
// VISA if number's count == 13 or 16 and start with 4

int valid;
valid = checksum(number);

int c;
c = count(number);

if ((valid == 0) && ((fdig == 3 && sdig == 4) || (fdig == 3 && sdig == 7)))
{
    printf("AMEX\n");
}
else if ((valid == 0) && (c == 16) && (fdig == 5 && 0 < sdig && sdig <= 5))
{
    printf("MASTERCARD\n");
}

else if ((valid == 0) && (c == 13 || c == 16) && fdig == 4)
{
    printf("VISA\n");
}
else
{
    printf("INVALID\n");
}

}
// not registering on check 50 :( identifies 378282246310005 as AMEX expected "AMEX\n", not ""

