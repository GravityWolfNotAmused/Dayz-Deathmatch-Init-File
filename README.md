# Dayz Deathmatch Init File
## The creation of this file was simply to get my feet wet with EnforceScript API.
## Please feel free to ask questions, or post updates. I am trying to get things as simply written as possible.

[![GitHub version](https://badge.fury.io/gh/Naereen%2FStrapDown.js.svg)](https://github.com/GravityWolfNotAmused/Dayz-Deathmatch-Init-File/releases)

### Config:
####   In order for you to change the classes, change the string which are stored TStringArrays, and strings variables to match the items you wish for the class to spawn with.

### To Change Spawn Item Values:
1. Change the values between the "" to the names of items which you wish to replace.

  2. Anything with multiple items like Assault_Attachments, you should only replace one at a time. Make sure that it is seperated by a comma, only if there is an item that comes after it in the collection, and be sure that each item name is surrounded in "".
  
   Example:
    
(Before Change)
      
```c
autoptr TStringArray Assault_Clothing = {"BandanaMask_CamoPattern", "BallisticHelmet_Green", "USMCJacket_Woodland", "USMCPants_Woodland"};
string Assault_Gun = "M4A1";
string Assault_SideArm = "MakarovIJ70";
autoptr TStringArray Assault_SideArm_Attachments = {"MakarovPBSuppressor"};
autoptr TStringArray Assault_Attachments = {"M4_CQBBttstck_Black", "ACOGOptic", "M4_RISHndgrd_Black"};
autoptr TStringArray Assault_Mags = {"MAG_STANAG_30Rnd", "MAG_IJ70_8RND"};
```
      
(After change) 
```c
autoptr TStringArray Assault_Clothing = {"BandanaMask_CamoPattern", "BallisticHelmet_Green", "USMCJacket_Woodland", "USMCPants_Woodland"};
string Assault_Gun = "M4A1";
string Assault_SideArm = "MakarovIJ70";
autoptr TStringArray Assault_SideArm_Attachments = {"MakarovPBSuppressor"};
autoptr TStringArray Assault_Attachments = {"AK_Woodbttstck", "AK_RailHndgrd" };
autoptr TStringArray Assault_Mags = {"Mag_AKM_30Rnd", "MAG_IJ70_8RND"};
```

3. ...
4. Profit, it's that easy.

### Adding New Class:
1. In order to create a new type of class, you must create the same basic layout of TStringArrays, and strings; however, you must name the variable something different than the other classes.

```c
autoptr TStringArray new_class_clothes = {"BandanaMask_BlackPattern", "USMCJacket_Desert", "USMCPants_Desert", "DarkMotoHelmet_Black"};
string new_class_gun = "M4A1";
string new_class_sidearm = "MakarovIJ70";
autoptr TStringArray new_class_gun_sidearm_attachments = {"MakarovPBSuppressor"};
autoptr TStringArray new_class_gun_attachments = {"M4_CQBBttstck_Black", "ACOGOptic", "M4_RISHndgrd_Black"};
autoptr TStringArray new_class_mags = {"MAG_STANAG_30Rnd", "MAG_IJ70_8RND"};
```

2. You must add an additional case to the switch statement, change the 4 in Math.RandomInt(0,4) to how many classes you have in total.

3. Finally, you need to call dress_player(), arm_player(), and give_utilities() inside of the new case and pass the correct inputs into those functions.

  (Before Additional Class)
```c
switch (Math.RandomInt(0, 4)) {
	case 0: // Assault
		dress_player(player, Assault_Clothing, Uniform);
		primary = arm_player(player, Assault_Gun, Assault_Attachments);
		secondary = arm_player_secondary(player, Assault_SideArm, Assault_SideArm_Attachments);
		give_utilities(player, Utilities, bag_name);
		addMags(player, Assault_Mags, magCount, true);
		break;
	case 1: // Sniper
		dress_player(player, Sniper_Clothing, Uniform);
		primary = arm_player(player, Sniper_Gun, Sniper_Attachments);
		secondary = arm_player_secondary(player, Sniper_Sidearm, Sniper_SideArm_Attachments);
		give_utilities(player, Utilities, bag_name);
		addMags(player, Sniper_Mags, magCount, true);
		break;
	case 2: // Submachine Gun
		dress_player(player, Submachine_Clothing, Uniform);
		primary = arm_player(player, SubMachineGun_Gun, SubmachineGun_Attachments);
		secondary = arm_player_secondary(player, SubMachineGun_Sidearm, SubMachineGun_SideArm_Attachments);
		give_utilities(player, Utilities, bag_name);
		addMags(player, SubmachineGun_Mags, magCount, true);
		break;
	case 3: // Medic
		dress_player(player, Medic_Clothing, Uniform);
		primary = arm_player(player, Medic_Gun, Medic_Attachments);
		give_utilities(player, Utilities, bag_name);
		addMags(player, Medic_Mags, magCount, true);
		give_medical(player, Medical_Supply_Case, Medical_Supplies);
		break;
}
```

(After Additional Class)
```c
//Notice below: Math.RandomInt has change from 0,4 to 0,5. the last number should always be the amount of classes you have in total.
switch (Math.RandomInt(0, 5)) {
	case 0: // Assault
		dress_player(player, Assault_Clothing, Uniform);
		primary = arm_player(player, Assault_Gun, Assault_Attachments);
		secondary = arm_player_secondary(player, Assault_SideArm, Assault_SideArm_Attachments);
		give_utilities(player, Utilities, bag_name);
		addMags(player, Assault_Mags, magCount, true);
		break;
	case 1: // Sniper
		dress_player(player, Sniper_Clothing, Uniform);
		primary = arm_player(player, Sniper_Gun, Sniper_Attachments);
		secondary = arm_player_secondary(player, Sniper_Sidearm, Sniper_SideArm_Attachments);
		give_utilities(player, Utilities, bag_name);
		addMags(player, Sniper_Mags, magCount, true);
		break;
	case 2: // Submachine Gun
		dress_player(player, Submachine_Clothing, Uniform);
		primary = arm_player(player, SubMachineGun_Gun, SubmachineGun_Attachments);
		secondary = arm_player_secondary(player, SubMachineGun_Sidearm, SubMachineGun_SideArm_Attachments);
		give_utilities(player, Utilities, bag_name);
		addMags(player, SubmachineGun_Mags, magCount, true);
		break;
	case 3: // Medic
		dress_player(player, Medic_Clothing, Uniform);
		primary = arm_player(player, Medic_Gun, Medic_Attachments);
		give_utilities(player, Utilities, bag_name);
		addMags(player, Medic_Mags, magCount, true);
		give_medical(player, Medical_Supply_Case, Medical_Supplies);
		break;
	case 4: //New Class
		dress_player(player, new_class_clothes, Uniform);
		primary = new_class_gun(player, SubMachineGun_Gun, new_class_gun_attachments);
		secondary = arm_player_secondary(player, new_class_sidearm, new_class_gun_sidearm_attachments);
		give_utilities(player, Utilities, bag_name);
		addMags(player, new_class_mags, magCount, true);
		break;
}
 ```

### Reminder:
  Some items, which maybe provided by Item name lists, may not be completely integrated yet. I've had this issue testing the M249, and one AK, I believe it was the AK101; however, this could changed with DayZ Updates.

Special thanks to u/ThisAccountIs4Reddit for putting together a semi-complete item list: https://docs.google.com/spreadsheets/d/1jFQOkaU6kSZJFzMV4NHHgmi95htJzS0_1iM8aCWYCvI/edit?usp=sharing

# DO NOT FORGET TO CHANGE YOUR SPAWN POINTS TO A SINGLE TOWN/AREA INSIDE OF cfgplayerspawnpoints.xml
