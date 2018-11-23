# NetworkingGame
Integrating Networking and Game Development.

(C) ADITYA PREREPA and AKSHAY TRIVEDI

ALL CONTENT IS FOR FUN NOTHING ELSE
THERE IS THE USE OF AN AWS SERVER
Game for test purposes only, under construction.


PURPOSE : 

 - connect (for now) 2 computers across at any location and have them play a game.
 - the game is based off polytopia, WE DO NOT OWN POLYTOPIA AND HAVE NO INTENT OF SELLING THIS GAME.
 - the game is a turn based game, so there is room for a notification system and/or email system.
 
 SUMMARY: 
 
  Have our server assign a random number between 1-2 to both of the computers (non - repetitive). The machine
  assigned with 1 gets a go-ahead and generates the game map in C++. Note the user has no idea the map is being 
  generated. The user one machine 1 is prompted to make a move, and once the move is made, the image of the map after  
  alteration are saved to a file locally. Note that all the events that happened previously are in C++. A java pre- 
  compiled program is checking for the creation of the files saved above, and once they are, the files that are picked up by     this program are sent to the server. The server recieves the file and sends it to machine 2 for the second user to make
  a move. Machine 2 makes a move, alters the image, and sends it to the server. This happens until the game ends.
  
  AREAS FOR DEVELOPMENT : 
  
   - Possibly implement an encryption system to stop cheating?
   - Maybe clients send both files for server to calculate difference and decrease load?
   - Sockets in C++ on client instead of java?
   
   
 - ADITYA PREREPA 11/22/18
