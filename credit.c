#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long number = get_long("Number:\n");
    int length=0;
    string output = "INVALID\n";
    bool valid = false;
    long second_to_last = number/10;
    int sum = 0;
    while (second_to_last > 0) {
        int digit = second_to_last % 10;
        if(digit*2 >= 10) {
            sum += (digit*2 % 10) + 1;
        } else {
            sum += digit*2;
        }
        second_to_last /= 100;
    }
    long num = number;
    while (num > 0) {
        int digit = num % 10;
        sum += digit;
        num /= 100;
    }
    if(sum % 10 == 0) {
        valid = true;
    }
    //calc first numbers
    int amex = (number / 10000000000000);
    int mastercard = (number / 100000000000000);
    int visa_short = (number / 1000000000000);
    int visa_long = (number / 1000000000000000);
    if (valid && (amex == 34 || amex == 37)) {
        output = "AMEX\n";
    } else if (valid && (mastercard == 51 || mastercard == 52 || mastercard == 53 || mastercard == 54 || mastercard == 55)) {
        output = "MASTERCARD\n";
    }else if (valid && (visa_short == 4 || visa_long == 4)) {
        output = "VISA\n";
    }
    printf("%s", output);
}