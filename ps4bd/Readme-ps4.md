# PS4b: Sokoban

## Contact
Name:Ashish Kosana
Section:202
Time to Complete:7.5 hours.


## Description
Explain what the project does.
==>The main aim of the project is to develop a sokabon game using c++ and sfml libraries,and adding the gameplay features so that we can able to play the game,and also checks for win conditions.
### Features
Describe what your major decisions were and why you did things that way.
==>The features that i have implemented in this project are as follows:
#### Part a
==>The game loads levels from the text files given by the professor.
==>I have also implemented sfml graphics to display the game, the game also checks for win conditions.
#### Part b
==>I have added the gameplay features such that the player can play the game and also the player can able to know weather wins or loose.
==>I have also implemented another features ,they are time display and move counter.
### Memory
Describe how you decided to store the level data including whether you used smart pointers.
==>I have used sf::Texture and sf::Sprite in sokoban class to load the textures from the files.
==>I have used std::vector<char> to store both the current game grid and the initial grid state. And For the player's current positions and initial positions, I choose to use sf::Vector2i.
==>I have not used smart pointers.
### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.
==>I have used the following lambda expression [](char c) { return c == 'A' || c == 'B'; } ,this expression takes c as input and returns true if c is either A or B.
### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.
==>Everything is working properly which i have implemented in the code.
### Extra Credit
Anything special you did.  This is required to earn bonus points.
==>I have added the time in mm:ss by using arial font in the window.
==>I have implemented the undo system such that the player can undo their moves by pressing U key.
==>I have implemented the reset feature such that the game resets by pressing R key.
==>I have added a music feature such that the music plays after winning.
==>I have added the feature of changing the player direction such that the player faces the direction in their direction.
==>I have added real time move counter which counts the moves when moving the player.
==>I have also added best time tracker such that it displays best time in which the player completes the game in their best time.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.
==>I have took all the images from the zip file sokoban.zip provided by the professor.
Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
==>I have took the audio (victory.wav) from (https://eorzeasongbook.com/)