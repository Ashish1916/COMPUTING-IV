# PS5: DNA Alignment

## Contact
Name:Ashish Kosana
Section:202
Time to Complete:6.5 hours

Partner:None

## Description
Explain what the project does
==>The main aim of the project is to generate a program that computes the edit distance between two strings by using insertion,deletion,substitution approaches by using dynamic programming approach.

### Features
Explain how you did the actual alignment including the data structures used.
==>Edit Distance Calculation: The program calculates the minimum number of operations to transform one string into another using dynamic programming.
==>Penalty Function: It defines a penalty of 0 for matching characters and 1 for non-matching characters.
==>Alignment Generation: The program generates an alignment showing matching characters and gaps between the strings.
==>Performance Measurement: The program measures memory usage and execution time. It calculates memory usage by reading from system files and measures time using the SFML library.
==>

### Testing
Describe what the unit tests you wrote check for and why you picked them.
The tests are as follows:
==>Penalty Function: Validates the penalty for matching and non-matching characters.
==>Min3 Function: Tests the helper function that finds the minimum of three integers.
==>Edit Distance: Verifies the computed edit distance between two strings.
==>Alignment: Ensures the alignment generation is correct.
==>Exception Handling: Checks if exceptions are thrown when invalid inputs (empty strings) are provided.
==>Complex Test Cases: Tests the algorithm with larger and more complex string pairs.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.
==>Memory Usage: The program's memory consumption increases quadratically with the size of the input strings,from ecoli50000 i am not getting the output,i am just getting killed as the output.
## Analysis

### Example
Do one additional test case by hand. It should be constructed in such a way that you know the correct  output before running your program on it, and it should be a "corner case" that helps check if your program handles all special situations correctly. 

Please list:
 - a copy of the test case input
 ==>ABCDE
 ==>ABCDEF
 - the expected test case output
 ==>Edit Distance=2
 - whether your program ran correctly on it or not
 ==>Yes my program ran correctly.
 - optionally, any other remarks

### Specs
Your Computer
Memory: (8gb, DDR4)
Processors: (ex: i5-1240 @ 1.70 GHz x64)

Partner's Computer
Memory: (ex: 8gb, DDR4)
Processors: (ex: i5-8500 @ 3.00 GHz x6)

### Runs
Fill in the table with the results of running your code on both your and your partner's computers.

| data file     | distance | memory (mb) | time (seconds) | partner time |
|---------------|----------|-------------|----------------|--------------|
|ecoli2500.txt  |  118     |      25.43  | 0.3971         |              |
|ecoli5000.txt  | 160      |     97.02   | 1.494923       |              |
|ecoli10000.txt |     223  |     383.70  |  5.783447      |              |
|ecoli20000.txt |   3135   |    1527.08  | 28.102600      |              |
|ecoli50000.txt |  killed  |             |                |              |
|ecoli100000.txt|  killed  |             |                |              |

Here is an example from another computer for some of the files.

| data file    | distance | time (s) |
|--------------|----------|----------|
|ecoli2500.txt |      118 |    0.171 |
|ecoli5000.txt |      160 |    0.529 |
|ecoli7000.txt |      194 |    0.990 |
|ecoli10000.txt|      223 |    1.972 |
|ecoli20000.txt|     3135 |    7.730 |

### Time
Assume the two strings are the same length (M = N).  By applying the doubling method to the data points that you obtained, estimate the running time of youu program in seconds as a polynomial function of N, in the form a * N^b for some constants a and b.  Determine the largest input your program can handle if it is limited to one day of computation.

Provide a brief justification/explanation of how you applied the doubling method, and if you data seems not to work, describe what went wrong and use the sample data instead.
==>Firstly  I am comparing how the execution times change when I double the input size. I have calculated the ratios between these times specifically T(2N) divided by T(N) for each doubling of N. If these ratios are consistent,then it tells about the time complexity of the algorithm.

By looking at these ratios, I am trying to calculate the exponent (b). If the ratio is close to 2, it suggests linear time complexity, which means b is around 1.If it is close to 4, that indicates quadratic time complexity, which means b is around 2. In my case, the ratios were overing around 4, so I'm concluding that b is approximately 2.
To find the coefficient (a), I have used the formula: T(N) = a · N^b. then,I have  picked a known data point - in this i have considered, N is 10000 and the time is 5.783447. By solving the equation, I have calculated that a is approximately 5.783447e-8.
Now I can express  that my time complexity function as T(N) = 5.783447e-8 · N^2. This gives me a way to predict how the time will grow with input size.
To determine the maximum input size, I have set a time constraint,in this case, one day, which is 86400 seconds. Then i have solved the equation 86400 = 5.783447e-8 · N^2 to find N. This provides  me that I can process an input of about 386,515 within one day.
 - a = 5.783447e-8
 - b = 2
 - largest N = 386,515

### Memory
Assume the two strings are the same length (M = N).  Look at your code and determine how much memory it requires as a polynomial function of N, in the form a * N^b for some constants a and b.  Determine the largest input size your computer can handle if limited to 8GiB of RAM.
 - a = 4
 - b = 2
 - largest N = 46,340

### Valgrind
    Run valgrind and list any errors you see.  Identify whether the memory usage reported by valgrind almost matches the calculations in the previous section.
    ==>I am not getting any errors,and the memory also matches almost to the previous calculations for this i have calculated for ecoil2500 and the memory i got for this is 25.02MB.
    Memory used: 25.01 MB
    ==>This is the output i have got in valgrind analysis.
    Edit distance after sequence = 118
    Execution time is 1.404394 seconds
    ==1084== 

--------------------------------------------------------------------------------
Command:            ./EDistance
Massif arguments:   (none)
ms_print arguments: massif.out.910
--------------------------------------------------------------------------------


    MB
95.75^                                                                       :
     |#######################################################################:
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
     |#                                                                      :
   0 +----------------------------------------------------------------------->Gi
     0                                                                   10.90

Number of snapshots: 82
 Detailed snapshots: [2, 3, 16, 31, 52, 62, 72, 74 (peak)]

## Pair Programming
If you worked with a partner, do you have any remarks on the pair programming method? E.g., how many times did you switch, what are the tradeoffs of driving vs. navigating, etc.?
==>I have not worked with any partner.
## Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
==>I have downloaded all the text files from the zip file sequence.zip provided by the professor.
==>I have also refered to the dynamic programming notes provided by the professor.

## Changes
==>I have added the valgrind analysis output in readme.