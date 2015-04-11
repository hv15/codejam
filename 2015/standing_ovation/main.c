#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#define LARGE 0

struct test_case {
    int s_max;
    int * aud;
};

void free_test_cases(struct test_case * N, int size)
{
    for(int j = 0; j < size; j++){
        free(N[j].aud);
    }
    free(N);
}

/* Return the number of digits in the decimal representation of n.
 * Taken from: http://stackoverflow.com/a/9721570/1203078
 */
unsigned digits(uint32_t n) {
    //static uint32_t powers[10] = {
    //    0, 10, 100, 1000, 10000, 100000, 1000000,
    //    10000000, 100000000, 1000000000,
    //};
    static unsigned maxdigits[33] = {
        1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5,
        5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 
    };
    unsigned bits = sizeof(n) * CHAR_BIT - __builtin_clz(n);
    unsigned digits = maxdigits[bits];
    //if (n < powers[digits - 1]) {
    //    --digits;
    //}
    return digits;
}

void digits_array(struct test_case * test, int N, int size)
{
    while (size--)
    {
        test->aud[size] = N % 10;
        N /= 10;
    }
}

int sum(int * N, int size)
{
    int sum = 0;
    for(int i = 0; i < size; i++)
    {
        sum += N[i];
    }
    return sum;
}

int main()
{
    // Main vars
    int T;
    struct test_case * test_cases;

    // Temp vars
    int i, j, s_max_temp, aud_temp;

    // Get number of test cases and ensure sanity
    scanf("%d", &T);
    if (T < 0 || T > 100)
    {
        return EXIT_FAILURE;
    }

    test_cases = (struct test_case *) malloc(sizeof(struct test_case) * T);

    for(i = 0; i < T; i++)
    {
        // Get S_max value and check sanity
        scanf("%d %d", &s_max_temp, &aud_temp);
        if (s_max_temp < 0 || (!LARGE && s_max_temp > 6) || (LARGE && s_max_temp > 1000))
        {
            free_test_cases(test_cases, T);
            return EXIT_FAILURE;      
        }

        // Sanity check audiance info
        if(s_max_temp + 1 != digits(aud_temp) || aud_temp % 10 == 0 )
        {  
            free_test_cases(test_cases, T);
            return EXIT_FAILURE;      
        }

        test_cases[i].s_max = s_max_temp;
        test_cases[i].aud = (int *) malloc(sizeof(int) * (s_max_temp + 1));
        digits_array(&test_cases[i], aud_temp, s_max_temp + 1);
    }

    for(i = 0; i < T; i++)
    {
        //int total = sum(test_cases[i].aud, test_cases[i].s_max + 1);
        int standing = test_cases[i].aud[0];
        int missing = 0;

        for(j = 1; j < test_cases[i].s_max + 1; j++)
        {
            if(j <= standing)
            {
                standing += test_cases[i].aud[j];
            } else {
                missing = j - standing - missing;       
            }
        }

        printf("Case #%d: %d\n", i, missing);
    }

    free_test_cases(test_cases, T);
    return EXIT_SUCCESS;
}
