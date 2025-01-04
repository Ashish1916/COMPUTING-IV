# PS7: Kronos Log Parsing

## Contact
Name:Ashish Kosana
Section:202
Time to Complete:6 hours.


## Description
Explain what the project does.
The main aim of the project is to read log files to identify server boot events,and calculate the time taken for successful boots.

### Features
Describe what your major decisions were and why you did things that way.
==>The features i have implemented in this project are as follows:
==>Detects boot start and end using specific log patterns.
==>Calculates boot durations accurately for completed events.
==>Flags incomplete boots and lists them separately.
==>Saves results in a clear, formatted report file.

### Approach
Describe your overall approach to solving this problem.
==>The approach is as follows
==>Read the log file line by line.
==>Use regex to match patterns for boot start and completion.
==>Store boot details in a structured format.
==>Calculate time for completed boots and generate a report.

### Regex
What regular expressions did you use?  Explain what each one does.
==>The Regex expressions i have used are as follows
==>Start Regex: \(log\.c\.166\) server started – Matches log lines indicating that a server boot start.
==>End Regex: oejs\.AbstractConnector:Started .+ – Matches lines confirming that the server boot is complete.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.
==>Everything is working properly which i have implemented in the code.

### Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
==>I have downloaded all the log files provided by the professor.
