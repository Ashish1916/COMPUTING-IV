# PS1: LFSR / PhotoMagic

## Contact
Name:Ashish Kosana

Section:202

Time to Complete:8.5hours


## Description
Explain what the project does.
==>The main aim of the project is to generate a pseudo random bits by simulating a linear feedback shift register.

### Features
Describe the representation you used and why you did things that way as well as any other interesting design decisions you made.
==>I have used 11 test cases in the test.cpp ,these eleven test cases are running properly,the code also Calculates the next bit in the sequence,and Computes feedback by XOR-ing the bits from the specified tap positions and also Updates the internal register by shifting right and inserting the new feedback bit at the leftmost position.

#### Part a
==>The tap positions ({2, 3, 5})are used to compute feedback, defining the polynomial characteristic of the LFSR.
#### Part b

### Issues
What doesn't work.  Be honest.  You might be penalized if you claim something works and it doesn't.
==>The  eleven test cases are running properly.

### Tests
Describe what is being tested in your Boost unit tests.
==>The test focus on mainly Correctness of the step method by Ensuring that the LFSR behaves as expected,by producing the right feedback bits for different seeds.And also Functionality of the generate method by Confirming that it accurately generates a specified number of bits and combines them correctly into an integer output.

### Extra Credit
Anything special you did. This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
==>I have used the pdf provided by the proffessor to get grip over FIBLFSR https://learn-us-east-1-prod-fleet02-xythos.content.blackboardcdn.com/5f9c84db7d38a/28747351?X-Blackboard-S3-Bucket=learn-us-east-1-prod-fleet01-xythos&X-Blackboard-Expiration=1727146800000&X-Blackboard-Signature=tIovciB2aaUvvSKIvaz3JAvNZktWq46aO0RwqZiHL0k%3D&X-Blackboard-Client-Id=301799&X-Blackboard-S3-Region=us-east-1&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27ps1a.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEJD%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLWVhc3QtMSJIMEYCIQC7z0nmEWPVqf%2F29%2BHGPRjrPXaC8ZXM7%2FnLvcwZIsVx2QIhAIXhyi%2BN2PgrN7%2B3B9ZVwCWPfTRr0enEeivtO%2F1nlYdsKr0FCMj%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEQBBoMNjM1NTY3OTI0MTgzIgz6ab3gxgEIlyKYqZcqkQV0UtB8bpM1wrXfBwKmQ30A%2FSn2LEwgiYqA4fy1FNo0m54kVVfdmCrvJA%2BrrhosyBtqLm5lYcsMxsU6gX26qJ08zCZJwTI%2F5VmdWMQHkpRkpXCH%2Ba%2BfOEQ%2BEMH82ukwn2t%2BgV8HOV6Yg7Vt8CTPJCh6zTe2KSqkDgxxCxif97dT6tZPfBBvfzs1ROvPt4YD7dYQw%2BRHYjrezd9fowhVvdRYMlD7mcBrFpAI5tQXFknu3fvN%2Fy9kLdiiFfMv%2BvnuQ5bp90pq9CKHI9aYK3NpYXQQ2GeN8dj68du2QJASVct9xig7WUd8zuD%2Fv2vL0k9j6oxowkaLdVI2pvj92jMXvFq7w6aK2C9g516NnUgmXc%2BVPIK9vM1W%2BY1jwPvvwKVl5llSJKW6aq4umR0p80oJFSx2fjXMc7ZyVW5Ton5iDjG4kgryl49N3eJE7QNYSTqgnUTmY1oHtkXsaocQGTxv9Gd6iUjX0%2FfKEA32rN6OnJfNgM3gJSVX7ke9cXqf02FOu41jLvrldTkEbJ772Q3k%2Fjew75jWmRoXmJdNeaXSdTPgmga0oXMnaSfx4674lMFa3pBw9ReaH9VwTp2fD5ETLL0wvxuiXCG9qabS5qdgFb74NOW5vmWhCs87Ph2cJUqAINDn1x2PBs14jeKiaurze8JAo0EGBa0MY3X2zxW8egG%2FTScOwyc6ixIW3lYEyLirIDIm7DWsGOL%2B7J1WMKqqsdLkikEZDz%2BBxYdjjxfmLcr5NQo9aHrakFYtpb45UmwrTCSGxKvn36QDa%2FVVfe8sQ5sDRJO3pz8BOv%2F%2F%2FDhlxJpghH0I5%2BOu5UoWJOHqxlv7pwe%2FpyeXSu1VQ0fVInRMfguZHa8U2%2FZSAEuD%2FQ24uvTNfUIw6e3HtwY6sAEEhQ0c0arI3ywQlILfbyaxX%2BHTfxiFFYDqSi0tQ0DRKPCi4VOlmMC%2B338wdKomVJre1euDT90MSkpinhfF3A7t1VkbdxwMCclxi3uE1g%2Bmzw6kiuKCodekx1bYC2bATSecJjrhhbO5zceZ16nvVHCCHj3sPyCS4k7J1u2bLtW%2FuJqec1NHQxF%2FwLYrfFOBdz%2F0dWavDEwrSB9U6d8hZYHrs7tkLlok%2FG0bGh9CpOFLEA%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20240923T210000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAZH6WM4PL3GZSP2OC%2F20240923%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=20eabe128534078460ca883204006e415d665aefb0e66a628eed21c44d5b87cb.

### Credits
List where you got any images or other resources.
==>I have not used any images,but i have used a website to understand the LFSR concept https://vlsiverify.com/verilog/verilog-codes/lfsr/.
