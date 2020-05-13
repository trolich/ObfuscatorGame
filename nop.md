Reflection:

My solution has many strengths and many weaknesses. In terms of strength, encoded values are unintersting, they blend in with the background noise of the program. This was not shown enough since I didn't encode the default values or the armor and weapon lists within the code as I should've. Another strength is that the entropy of the program is nearly unaffected by my encoding mechanisms, leading to a lack of detection by cyber-security persons. In terms of weaknesses, the encoded values are fairly easy to reconstruct just by looking at them, especially the strings. Something that would help to make reconstruction harder would be to alter the values slightly, maybe by adding a Cesaer cypher to the strings, or by using some other encoding stategies on top of my own design. 

Future changes would involve encoding all of the strings contained within the program and not just those stored in the file. They would also include adding a secondary encoding scheme on top of mine that would help to obfuscate the values stored in the file.

