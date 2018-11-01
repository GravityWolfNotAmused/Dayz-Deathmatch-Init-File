# Dayz Deathmatch Init File
## The creation of this file was simply to get my feet wet with EnforceScript API.
## Please feel free to ask questions, or post updates. I am trying to get things as simply written as possible.

### Config:
####   In order for you to change the classes, change the string which are stored TStringArrays, and strings to match the items you wish for the class to spawn with.

### To Change Spawn Item Values:
1. Change the values between the "" to the names of items which you wish to replace. 
  1.Anything with multiple items like Assault_Attachments, you should only replace one time. Make sure that it is seperated by a comma, only if there is an item that comes after it in the collection.
    Example:
(Before Change)
```c
    autoptr TStringArray Assault_Clothing = {"BandanaMask_CamoPattern", "BallisticHelmet_Green", "USMCJacket_Woodland", "USMCPants_Woodland"};
    string Assault_Gun = "M4A1";
    string Assault_SideArm = "MakarovIJ70";
    autoptr TStringArray Assault_SideArm_Attachments = {"MakarovPBSuppressor"};
    autoptr TStringArray Assault_Attachments = {"M4_CQBBttstck_Black", "ACOGOptic", "M4_RISHndgrd_Black"};
    string Assault_Mag = "MAG_STANAG_30Rnd";
```
      
(After change)
```c
    autoptr TStringArray Assault_Clothing = {"BandanaMask_CamoPattern", "BallisticHelmet_Green", "USMCJacket_Woodland", "USMCPants_Woodland"};
    string Assault_Gun = "AK74";
    string Assault_SideArm = "MakarovIJ70";
    autoptr TStringArray Assault_SideArm_Attachments = {"MakarovPBSuppressor"};
    autoptr TStringArray Assault_Attachments = {"AK74_Hndgrd", "AK74_WoodBttstck"};
    string Assault_Mag = "Mag_AK74_30Rnd";
```
2. ...
3. Profit, it's that easy.

### Adding New Class:
1. In order to create a new type of class, you must create the same basic layout of TStringArrays, and strings; however, you must name the variable something different than the other classes.
2. You must add an additional case to the switch statement, change the max/4 for Math.RandomInt(0,4) to how many classes you have in total.
3. Finally, you need to call dress_player(), arm_player(), and give_utilities() inside of the new case and pass the correct inputs into those functions.

### Reminder:
  Some items, which maybe provided by Item name lists, may not be completely integrated yet. I've had this issue testing the M249, and one AK; however, this could change when version 1.0 is released.

# DO NOT FORGET TO CHANGE YOUR SPAWN POINTS TO A SINGLE TOWN/AREA INSIDE OF cfgplayerspawnpoints.xml
