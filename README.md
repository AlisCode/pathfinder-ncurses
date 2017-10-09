# NCurses Pathfinding

What is this ? 
* A* Pathfinding implementation in C  
* /!\ Highly unoptimized code because I lack time and knowledge  
* Ncurses for the front-end (because SDL is way too easy. Trust me. It is.) Also, screw Windows.
* School Project @ CPE Lyon, France

# Compile from source code :  
*   Clone the repo 
`git clone https://github.com/AlisCode/pathfinder-ncurses`
*   CD in the repo and compile everything
`cd pathfinder-ncurses && make`
*   Launch the app using ./src/main  
  
 
# Usage: 
*  `./src/main` launches the app
*  `./src/main mapname.map` to open a specific map
* Everything else will not work

# How to use
* When the app is launched, it is automatically in Visual Mode
* Press m to open the menu, then use the arrow key to do anything
* While in edit mode, press E to select what type of bloc you would like to place
* While in edit mode, press Space to place a bloc of the type you selected
* While in any mode, press ESC to return to Visual Mode
* A map needs a starting point and an ending point to be resolved, otherwise you'll be warned that there's no path to be solved
* Again, this is highly unoptimized, but still efficient because written in C :)
* If you want to make a map bigger, sorry but [ain't nobody got time for that](https://www.google.fr/url?sa=i&rct=j&q=&esrc=s&source=images&cd=&cad=rja&uact=8&ved=0ahUKEwju7-y6v-TWAhVRI1AKHXVSDNMQjRwIBw&url=http%3A%2F%2Fcohort21.com%2Fjasonbornstein%2F2016%2F10%2F25%2Faint-nobody-got-time-for-that%2F&psig=AOvVaw2aweVR1jTsfoTUnVblBN5m&ust=1507671313155909), you'll have to open the map in your favorite text editor. Thankfully the map format is really straightforward

# TODO List ?

Even though this is not going to be maintained because time & reasons., there are things left to do : 

* ## A menu to create a map!
yep, that'd be useful

* ## Optimize the damn thing!
yep, but this is fast enough already

* ## Comment it!
Even though it's pretty much all commented already, I agree that some effort could go into commenting this so it's more readable ... kind of. 
