Timothy Rolich
Obfuscator write up

Design decisions:
When designing I started with my encoding strategy. I wanted my encoding to avoid xor’s and minimize entropy. I decided that to do this I would encode everything as character arrays, for this game that means floats, integers, and strings, and swivel the characters around in a fashion that would make it unreadable and difficult to decipher. Each parameter is encoded as 64 characters then each set of 4 characters are swiveled around. After this the sets of 4 characters are then swiveled around. This allows for unreadable numbers and strings. 
The next major decision was what the text file should look like. I decided that it should be structured such that values are consecutive and each value has a redundancy character preceding it to check for manipulations. The redundancy check is simple and easy to fool if you know how it works though. It is simply the character representation of the sum of all characters in the value mod 29. With enough playing around it would be easy to see that. Concerning the structure of the file it is simply:
1 char, redundancy
64 chars, value
repeated over and over for each value in the game. The text file is not perfect however since with a cursory search it is easy to tell that the number of chars is always divisible by 65. It is also not too difficult to distinguish between what would be a string, an int, or a float by some key factors including groups of letters or numbers and decimal points. But it is complex enough that you would not know what you were looking at unless you were really looking for something specific.
