# Dayz Deathmatch Init File
## The creation of this file was simply to get my feet wet with EnforceScript API.
## Please feel free to ask questions, or post updates. I am trying to get things as simply written as possible.

### Config:
####   In order for you to change the classes, change the string which are stored TStringArrays, and strings to match the items you wish for the class to spawn with.

### To Change Spawn Item Values:
1. Change the values between the "" to the names of items which you wish to replace.

  2. Anything with multiple items like Assault_Attachments, you should only replace one at a time. Make sure that it is seperated by a comma, only if there is an item that comes after it in the collection, and be sure that each item name is surrounded in "".
    Example:
    
      (Before Change)
      
```c
  autoptr TStringArray Assault_Clothing = {"BandanaMask_CamoPattern", "BallisticHelmet_Green", "USMCJacket_Woodland", "USMCPants_Woodland"};
  string Assault_Gun = "M4A1";
  autoptr TStringArray Assault_Attachments = {"M4_CQBBttstck_Black", "ACOGOptic", "M4_RISHndgrd_Black"};
  string Assault_Mag = "MAG_STANAG_30Rnd";
```
      
(After change) 
```c
  autoptr TStringArray Assault_Clothing = {"BandanaMask_CamoPattern", "BallisticHelmet_Green", "USMCJacket_Woodland", "USMCPants_Woodland"};
  string Assault_Gun = "AK74";
  autoptr TStringArray Assault_Attachments = {"AK74_Hndgrd", "AK74_WoodBttstck"};
  string Assault_Mag = "Mag_AK74_30Rnd";
```

3. ...
4. Profit, it's that easy.

### Adding New Class:
1. In order to create a new type of class, you must create the same basic layout of TStringArrays, and strings; however, you must name the variable something different than the other classes.

```c
  autoptr TStringArray new_class = {"BandanaMask_CamoPattern", "BallisticHelmet_Green", "USMCJacket_Woodland", "USMCPants_Woodland"};
  string new_class_gun = "AK74";
  autoptr TStringArray new_class_gun = {"AK74_Hndgrd", "AK74_WoodBttstck"};
  string new_class_mag = "Mag_AK74_30Rnd";
```

2. You must add an additional case to the switch statement, change the 4 in Math.RandomInt(0,4) to how many classes you have in total.

  (Before Additional Class)
```c
switch (Math.RandomInt(0, 4)) {
        case 0:
          dress_player(player, Assault_Clothing, Uniform);
          arm_player(player, Assault_Gun, Assault_Attachments);
          give_utilities(player, Utilities, bag_name, Assault_Mag);
          meleeWeapon = player.GetInventory().CreateInInventory(oneHanders.GetRandomElement());
          break;
        case 1:
          dress_player(player, Sniper_Clothing, Uniform);
          arm_player(player, Sniper_Gun, Sniper_Attachments);
          give_utilities(player, Utilities, bag_name, Sniper_Mag);
          meleeWeapon = player.GetInventory().CreateInInventory(oneHanders.GetRandomElement());
          break;
        case 2:
          dress_player(player, Submachine_Clothing, Uniform);
          arm_player(player, SubMachineGun_Gun, SubmachineGun_Attachments);
          give_utilities(player, Utilities, bag_name, SubmachineGun_Mag);
          meleeWeapon = player.GetInventory().CreateInInventory(oneHanders.GetRandomElement());
          break;
        case 3:
          dress_player(player, Medic_Clothing, Uniform);
          arm_player(player, Medic_Gun, Medic_Attachments);
          give_utilities(player, Utilities, bag_name, Medic_Mag);
          meleeWeapon = player.GetInventory().CreateInInventory(oneHanders.GetRandomElement());
          break;
      }
```

(After Additional Class)
```c
      switch (Math.RandomInt(0, 5) {
        case 0:
          dress_player(player, Assault_Clothing, Uniform);
          arm_player(player, Assault_Gun, Assault_Attachments);
          give_utilities(player, Utilities, bag_name, Assault_Mag);
          meleeWeapon = player.GetInventory().CreateInInventory(oneHanders.GetRandomElement());
          break;
        case 1:
          dress_player(player, Sniper_Clothing, Uniform);
          arm_player(player, Sniper_Gun, Sniper_Attachments);
          give_utilities(player, Utilities, bag_name, Sniper_Mag);
          meleeWeapon = player.GetInventory().CreateInInventory(oneHanders.GetRandomElement());
          break;
        case 2:
          dress_player(player, Submachine_Clothing, Uniform);
          arm_player(player, SubMachineGun_Gun, SubmachineGun_Attachments);
          give_utilities(player, Utilities, bag_name, SubmachineGun_Mag);
          meleeWeapon = player.GetInventory().CreateInInventory(oneHanders.GetRandomElement());
          break;
        case 3:
          dress_player(player, Medic_Clothing, Uniform);
          arm_player(player, Medic_Gun, Medic_Attachments);
          give_utilities(player, Utilities, bag_name, Medic_Mag);
          meleeWeapon = player.GetInventory().CreateInInventory(oneHanders.GetRandomElement());
          break;
        case 4:
          dress_player(player, new_class_clothing, Uniform);
          arm_player(player, new_class_gun, new_class_attachments);
          give_utilities(player, Utilities, bag_name, new_class_mag);
          meleeWeapon = player.GetInventory().CreateInInventory(oneHanders.GetRandomElement());
          break;
      }
 ```
3. Finally, you need to call dress_player(), arm_player(), and give_utilities() inside of the new case and pass the correct inputs into those functions.

### Reminder:
  Some items, which maybe provided by Item name lists, may not be completely integrated yet. I've had this issue testing the M249, and one AK, I believe it was the AK101; however, this could changed with DayZ Updates.

# DO NOT FORGET TO CHANGE YOUR SPAWN POINTS TO A SINGLE TOWN/AREA INSIDE OF cfgplayerspawnpoints.xml
