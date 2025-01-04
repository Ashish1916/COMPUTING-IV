# PS6: RandWriter

## Contact
Name:Ashish Kosana
Section:202
Time to Complete:8 hours


## Description
Explain what the project does.
==>The main aim of the project is to generate a text generation tool that analyzes the properties of an input text and generates new text sequences based on the frequency of character sequences .

### Features
Describe what your major decisions were and why you did things that way.
==>The features i have implemented are as follows:
==>order K implementation:
The program models k-order Markov chains, where k determines the size of "k-grams".
==>Frequency Analysis:
freq(kgram) and freq(kgram, char) provide detailed statistics about k-grams and character distributions.
==>Text Generation:
The generate() function uses the k-grams to produce random text of length L.
==>Random character Generation:
The kRand() function generates a random character weighted by the frequency distribution of characters following a given k-gram.

### Testing
What tests did you write?  What exceptions did you use?  Does your code pass the tests?
==>Test constructor:
Validates the construction of a RandWriter object under various conditions.
==>Test order K:
Verifies that the orderK() method correctly returns the value of k used during construction.
==>Test Frequency:
Tests the freq method to count the frequency of k-grams and specific characters following a k-gram.
==>Test K rand:
Tests the kRand method to ensure it selects a random character based on the distribution following a valid k-gram.
==>Test Geneerate:
Tests the generate method for creating a string of specified length starting from a valid k-gram.

### Lambda
What does your lambda expression do?  What function did you pass it to?
==>I have used the following lambda expression "auto generateKgram = [& text, k]() { return text.substr(0, k); };"
### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.
==>Everything is working properly which i have implemented in the code.
### Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
==>I have downloaded the text files romeo.txt,input17.txt,tomsawyer.txt provided by the professor.
