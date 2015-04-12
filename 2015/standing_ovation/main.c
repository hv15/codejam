#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

#define LARGE 1

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

// Silly, I know...
unsigned int count(int N)
{
    if (N < 10)
        return 1;
    if (N < 100)
        return 2;
    if (N < 1000)
        return 3;
    if (N < 10000)
        return 4;
    if (N < 100000)
        return 5;
    if (N < 1000000)
        return 6;
    if (N < 10000000)
        return 7;
    return 0;
}

void digits_array(struct test_case * test, char * N, int size)
{
    while (size--)
    {
        test->aud[size] = N[size] - '0';
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

int main(int argc, char ** argv)
{
    // Main vars
    int T;
    struct test_case * test_cases;
    char * file;
    FILE * fp;

    // Temp vars
    char aud_temp[1024];
    int i, j, s_max_temp, count_temp;

    // Open file
    if (argc > 1)
        file = argv[1];

    if ((fp = fopen(file, "r")) == 0)
    {
        return EXIT_FAILURE;
    }

    // Get number of test cases and ensure sanity
    fscanf(fp, "%d", &T);
    if (T < 0 || T > 100)
    {
        fclose(fp);
        return EXIT_FAILURE;
    }

    test_cases = (struct test_case *) malloc(sizeof(struct test_case) * T);

    for(i = 0; i < T; i++)
    {
        // Get S_max value and check sanity
        fscanf(fp, "%d %s", &s_max_temp, aud_temp);
        if (s_max_temp < 0 || (!LARGE && s_max_temp > 6) || (LARGE && s_max_temp > 1000))
        {
            printf("s_max %d\n", s_max_temp);
            fclose(fp);
            free_test_cases(test_cases, T);
            return EXIT_FAILURE;      
        }

        count_temp = strlen(aud_temp);

        // Sanity check audiance info
        if(s_max_temp + 1 != count_temp || (aud_temp[count_temp - 1] - '0') % 10 == 0 )
        {
            printf("aud %s %d %d\n", aud_temp, count_temp, s_max_temp);
            fclose(fp);
            free_test_cases(test_cases, T);
            return EXIT_FAILURE;      
        }

        test_cases[i].s_max = s_max_temp;
        test_cases[i].aud = (int *) malloc(sizeof(int) * count_temp);
        digits_array(&test_cases[i], aud_temp, count_temp);
    }

    for(i = 0; i < T; i++)
    {
        int standing = test_cases[i].aud[0];
        int missing = 0;

        for(j = 1; j < test_cases[i].s_max + 1; j++)
        {
            if (standing < j && test_cases[i].aud[j] != 0)
            {
                missing += j - standing;
                standing += missing;
            }
            standing += test_cases[i].aud[j];
        }

        printf("Case #%d: %d\n", i + 1, missing);
    }

    fclose(fp);
    free_test_cases(test_cases, T);
    return EXIT_SUCCESS;
}
