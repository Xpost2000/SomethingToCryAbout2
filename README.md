# SomethingToCryAbout2
The sequel to SomethingToCryAbout. and definitely better than the original :)
## How is it better than the original one??
- AI is seemingly smarter ( It's definitely more difficult )
- Less glitchy ( especially since I fixed the timestep issues from the original )
- Less renderer glitches.
- Improved loading performance ( all assests preloaded and used when needed ).
- Better graphics ( using some OpenGL things like Framebuffers to create some nice post processing effects)
### You said it's pretty much complete. How much is missing?
Ok... Maybe I should be more specific. The gameplay aspect is complete. Content wise it's probably
drier than most deserts right now.
 - 2 / 5 levels (planned to add later on).
 ~~- A main menu ( Again I plan to add pretty soon ).~~
 - Sound ( This is probably the last thing I'll ever do. )
 
I made this sequel to (hopefully) learn to make better video games.
I made sure it was at least more difficult and more fun than the original.
The gameplay is fairly arcade style and it's essentially bullet hell.

The game is not particularly difficult but in a tight area with multiple enemies it's pretty difficult.

# This one uses a custom OpenGL framework!
The original game used SDL renderer. Which ment I could focus more on the game but I instead ended up rushing it and not
exactly planning anything. I learned from some of the mistakes in the original game and fixed most of the main ones.

I made this to practice my OpenGL skills but primarily to make better video games.

The framework can indeed be used outside of developing the game and is ment to be general purpose ( but explicitly 2D,
since it is OpenGL however. you can modify it to work with a 3D environment ). The engine sort of like the game had no real
design plan ( I did everything as I went ) and it really does show since the class interfaces are either semi working or 
don't do 100% what they should be doing etc.

## Issues ( That I will manually add to the issues section ) 
  - Oatsframework's window class does not work when explicitly called (default constructor works which delegates) [SIGNIFICANT]
