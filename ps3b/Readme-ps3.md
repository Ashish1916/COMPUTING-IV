# PS3: N-Body Simulation

## Contact
Name:Ashish Kosana
Section:202
Time to Complete:7.5 hours.


## Description
Explain what the project does.
==>This program simulates a solar system using celestial body physics and renders it graphically using SFML. It creates an interactive universe visualization with background music and a digital clock display.
### Features
Describe what your major decisions were and why you did things that way.
==>I have made the changes to the  planets to rotate in clock wise direction so that they look like a proper solar system.
### Memory
Describe how you managed the lifetimes of your objects, including if you used smart pointers.
==>I have used stack based and dynamic memory allocation for celestial bodies through std::unique_ptr in the Universe class. This ensures proper memory management and prevents memory leaks. SFML resources like textures and sprites are managed internally by the library.
### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.
==>Everything is working properly which i have included in the code.
### Extra Credit
Anything special you did.  This is required to earn bonus points.
If you created your own universe file.  Describe it here and explain why it is interesting.
==>I have  implemented a custom digital clock display using rectangle shapes instead of relying on pre-rendered fonts. This demonstrates a creative approach to UI elements using basic graphical primitives.and also rotated the planets in clock wise direction so that it will be effective.
## Data structures
==>1. std::vector<std::unique_ptr<CelestialBody>>
This is the primary data structure I have used in the Universe class to store celestial bodies.
Implementation: std::vector from the C++ Standard Template Library.
Usage: Stores std::unique_ptr to CelestialBody objects.
Features:
>Dynamic sizing: Allows for easy addition and removal of celestial bodies.
>Contiguous memory: Provides efficient iteration and access by index.
>Automatic memory management: unique_ptr ensures proper deletion of CelestialBody objects.
==>I have also used different types of datastructures like 
2.sf::Vector2f
Used to represent 2D vectors for position and velocity of celestial bodies.
Implementation: Part of the SFML library.
Usage: Stores x and y components as float values.
Features:
>Provides vector arithmetic operations.
>Used for both position and velocity calculations.
3.std::string 
Used for storing filenames and other text data.
Implementation: C++ Standard Library string class.
Usage: Stores texture filenames and possibly other textual data.
## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.
==>I have collected all the images and music's from the Folder "nbody.zip" provided by the professor.And i have also referred the following pdf https://learn-us-east-1-prod-fleet02-xythos.content.blackboardcdn.com/5f9c84db7d38a/18670770?X-Blackboard-S3-Bucket=learn-us-east-1-prod-fleet01-xythos&X-Blackboard-Expiration=1728982800000&X-Blackboard-Signature=WxsgrZdPc4cQTzJ4Y1i1bc7NOgGWdCZUkLG5p9Tehwk%3D&X-Blackboard-Client-Id=301799&X-Blackboard-S3-Region=us-east-1&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%2712%2520Resource%2520Management.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEIz%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLWVhc3QtMSJHMEUCIGbp60bTTZDn4SQJjs3sYar%2BjP7uN2dUDb4cBHwuKSNwAiEAoGSIOP7YwCcZIczaSaZx31blGZGIu71dM7A3sw0ci%2F4qvQUI5f%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FARAEGgw2MzU1Njc5MjQxODMiDFkFtkjSLQle0n2yHyqRBcztRlefELbJziOZOJW5kCI6r5V4zewrLWYHxbd%2FfFlou%2BzOAjiWKEL3uipI5Dq5atkPP26bvWxWM2Yuq%2BU2PuxpHghi0rcoU73m4jZLX9dG2JfhLBeE4YTUCydE5YDx7zXVDgXdiZvhuBUhZnt2iezo%2FSuf6ZuyVkotOor0lJuWZ0Cmy3xF6aCcHUPn80H0fmyjajw9jUNKya5krCvUncxwQ2bgLSu9sUAagmgntE5Uafs1yCq465154ehNm8RUsMuimJCGz5ezdttfT%2BEm9vWFW8hCf%2Bna4vETlqGd8CA%2FPm%2F%2BMJBGDsXyJPOcnDLvRgWZJQ9cJRTdyVLsdoBQz7HGu7OfJGf2rPBePgFv2GiZhhbZBGYdn14kJCq4xoDK%2FNPPeYQRsbIe99RwRwzUSALBUSFDOdHELB6uQGqA0rlGEsYl0gPBfeiF01KHHR%2BIq7s%2FHS1Ra8DowkpHYHQJLdcDLdf11meqgnwtaLagbLmLgGcBk7e51GPFvurbeBRlljx7MiEF%2B6zYSlHNDwLmTdZEQGgIn5%2BGHMdXDHc12e3LNWjmef0oHV4vcz8S1Q2KNLCNcLejn8xk%2BEIO%2B2F2eYbK6Nd0vAetTG1JkoFa8a0f6SUgWUj8wriGDfYnTvu7qgi1oKQOmYD9X95ejATCCR2tNk6sApEf8jCZ%2BcFzyneM54suQcQRW3l19q7aWoxzbwWNCgjsIeuz0hoFy8Th7o5BLOuqyKHABTGf1F%2BYSB%2Bq848yYcrIWa4zNGXnN7jXcO4CDTCSsuQngGl37bFwRLO%2BfpZP8CPIWIpa50UZaO%2FbXnL5z9%2FkQOKf9U1oWDIPzwGYO8mxhlBLPifAd%2F6JqUU%2BkoMeYOyosZ0m9VxHdbtC7jCzybe4BjqxAY%2BlV8G7rqBPDelB0DUc3XlKRBFlQqyBZJnIGDqWs%2BwtAQYLlFZO9068JJt2QAcfI1fxISYjlgsywrU2Dxb%2B9aaZFvswssWkIQPHgJ7R%2FeF%2FfuNKl99uYvXmN40CRLpcbFIugwT2wMJd0gvuZhsKIO%2BKk3BSH%2B%2B6TZaQ3ofVasy8bgRwvHrRg2yeuouP42osCcMugeoaruyfXVdsgxPAkO907i2go3aX8weSf5n6WPIiew%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20241015T030000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAZH6WM4PLQCJXDEGL%2F20241015%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=7d0a0b397e4f8a9d80aede02388ab09f3b25a3f7263514534d8875a2f3904e79 to understand memory management provided by the professor.
I have also used sfml main website to learn how to draw shapes using rectangles https://www.sfml-dev.org/tutorials/2.6/.