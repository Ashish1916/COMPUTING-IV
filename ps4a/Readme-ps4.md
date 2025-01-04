# PS4: Sokoban

## Contact
Name:Ashish Kosana
Section:202
Time to Complete:6 hours.


## Description
Explain what the project does.
==>The main aim of the project is to develop a sokabon game using c++ and sfml libraries.
### Features
Describe what your major decisions were and why you did things that way.
==>The features that i have implemented in this project are as follows:
#### Part a
==>The game loads levels from the text files given by the professor.
==>I have also implemented sfml graphics to display the game, the game also checks for win conditions.
#### Part b

### Memory
Describe how you decided to store the level data including whether you used smart pointers.
==>I have used std::vector<char> to store both the current game grid and the initial grid state. And For the player's current positions and initial positions, I choose to use sf::Vector2i.
### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.
==>The isWon() function can be optimized using std::any_of with a lambda, but I didn't implement this in my current version of the code.
### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.
==>Everything is working properly which i have implemented in the code.
### Extra Credit
Anything special you did.  This is required to earn bonus points.
==>I have added the time in mm:ss by using arial font in the window.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.
==>I have took all the images from the zip file sokoban.zip provided by the professor.
Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
