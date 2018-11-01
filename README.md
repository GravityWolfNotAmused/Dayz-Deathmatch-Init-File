# Dayz Deathmatch Init File
## The creation of this file was simply to get my feet wet with EnforceScript API.
## Please feel free to ask questions, or post updates. I am trying to get things as simply written as possible.

### Config:
####   In order for you to change the classes, change the string which are stored TStringArrays, and strings to match the items you wish for the class to spawn with.

### Adding New Class:
1. In order to create a new type of class, you must create the same basic layout of TStringArrays, and strings; however, you must name the variable something different than the other classes.
2. You must add an additional case to the switch statement, change the max/4 for Math.RandomInt(0,4) to how many classes you have in total.
3. Finally, you need to call dress_player(), arm_player(), and give_utilities() inside of the new case and pass the correct inputs into those functions.

# DO NOT FORGET TO CHANGE YOUR SPAWN POINTS TO A SINGLE TOWN/AREA INSIDE OF cfgplayerspawnpoints.xml
