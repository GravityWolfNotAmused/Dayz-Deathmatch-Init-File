void main() {

    Hive ce = CreateHive();
    if (ce)
        ce.InitOffline();

    Weather weather = g_Game.GetWeather();

    weather.GetOvercast().SetLimits(0.0, 0.0);
    weather.GetRain().SetLimits(0.0, 0.0);
    weather.GetFog().SetLimits(0.0, 0.0);

    weather.GetOvercast().SetForecastChangeLimits(0.0, 0.0);
    weather.GetRain().SetForecastChangeLimits(0.0, 0.0);
    weather.GetFog().SetForecastChangeLimits(0.0, 0.0);

    weather.GetOvercast().SetForecastTimeLimits(0, 0);
    weather.GetRain().SetForecastTimeLimits(0,0);
    weather.GetFog().SetForecastTimeLimits(0,0);

    weather.GetOvercast().Set(Math.RandomFloatInclusive(0.0, 0.3), 0, 0);
    weather.GetRain().Set(Math.RandomFloatInclusive(0.0, 0.2), 0, 0);
    weather.GetFog().Set(Math.RandomFloatInclusive(0.0, 0.1), 0, 0);

    weather.SetWindMaximumSpeed(0);
    weather.SetWindFunctionParams(0, 0, 0);
}

class CustomMission : MissionServer {
    /*
     *  Config:
     *      This area is the only area in which users should change any information/variables.
     *      If you do not understand what something is being used for please read the comments above every function.
    */

    //Bag Name
    string bag_name = "SmershBag";

    /*
     * Name: Assault Class
     * Primary Weapon: M4A1
     * Weapon Attachments: CQB Buttstock, ACOG Scope, RIS Handguard
     * Sidearm Weapon: IJ70
     * Sidearm Attachments: Suppressor
    */
    autoptr TStringArray Assault_Clothing = {"BandanaMask_CamoPattern", "BallisticHelmet_Green", "USMCJacket_Woodland", "USMCPants_Woodland"};
    string Assault_Gun = "M4A1";
    string Assault_SideArm = "MakarovIJ70";
    autoptr TStringArray Assault_SideArm_Attachments = {"MakarovPBSuppressor"};
    autoptr TStringArray Assault_Attachments = {"M4_CQBBttstck_Black", "ACOGOptic", "M4_RISHndgrd_Black"};
    autoptr TStringArray Assault_Mags = {"MAG_STANAG_30Rnd", "MAG_IJ70_8RND"}

    /*
     * Name: Submachine Gun Class
     * Primary Weapon: MP5K
     * Weapon Attachments: Rail Handguard, Buttstock, M69 Optic
     * Sidearm Weapon: IJ70
     * Sidearm Attachments: Suppressor
    */
    autoptr TStringArray Submachine_Clothing = {"M65Jacket_Black", "SlacksPants_Black", "RocketAviators", "BalaclavaMask_Blackskull"};
    string SubMachineGun_Gun = "MP5K";
    string SubMachineGun_Sidearm = "MakarovIJ70";
    autoptr TStringArray SubMachineGun_SideArm_Attachments = {"MakarovPBSuppressor"};
    autoptr TStringArray SubmachineGun_Attachments = {"MP5_PRailHndgrd", "MP5k_StockBttstck", "M68Optic"};
    autoptr TStringArray SubmachineGun_Mags = {"MAG_MP5_15Rnd", "MAG_IJ70_8RND"};

    /*
     * Name: Sniper Class
     * Primary Weapon: Mosin
     * Weapon Attachments: PU Scope
     * Sidearm Weapon: IJ70
     * Sidearm Attachments: Suppressor
    */
    autoptr TStringArray Sniper_Clothing = {"BalaclavaMask_Black", "BallisticHelmet_Black", "TShirt_Black", "Jeans_Black", "UKAssVest_Black"};
    string Sniper_Gun = "SVD";
    string Sniper_Sidearm = "MakarovIJ70";
    autoptr TStringArray Sniper_SideArm_Attachments = {"MakarovPBSuppressor"};
    autoptr TStringArray Sniper_Attachments = {"PSO11Optic"};
    autoptr TStringArray Sniper_Mags = {"Mag_SVD_10Rnd", "MAG_IJ70_8RND"};

    /*
      * Name: Medic Class
      * Primary Weapon: None
      * Weapon Attachments: None
      * Sidearm Weapon: IJ70
      * Sidearm Attachments: Suppressor
      * Medical Kit: Bandage, Morphine, Saline, Painkillers
     */
    autoptr TStringArray Medic_Clothing = {"BallisticHelmet_Green", "GasMask", "ParamedicJacket_Green", "ParamedicPants_Green"};
    string Medic_Gun = "MakarovIJ70";
    autoptr TStringArray Medic_Attachments = {"MakarovPBSuppressor"};
    string Medical_Supply_Case = "FIRSTAIDKIT";
    autoptr TStringArray Medical_Supplies = {"BANDAGEDRESSING", "MORPHINE", "SALINEBAGIV", "PAINKILLERTABLETS"};
    autoptr TStringArray Medic_Mags = {"MAG_IJ70_8RND"};

    //  General Items which everyone will receive on spawn; regardless of class.
    autoptr TStringArray Utilities = {"TacticalBaconCan", "Canteen", "CanOpener"};
    autoptr TStringArray Uniform = {"SmershVest", "TacticalGloves_Green", "CombatBoots_Black"};

    // Melee Weapons
    autoptr TStringArray oneHanders = {"Machete", "HuntingKnife", "KitchenKnife"};

    /*
     * End of Config:
     *   Do not change anything below unless you understand what you are doing....
    */

    autoptr TStringArray batteryCompatible = {"UniversalLight", "ReflexOptic", "M68Optic", "M4_T3NRDSOptic"};

    /*
     * @function addMags
     * @discussion Adds mags to players inventory
     *
     * @param    player: Instance Of Player
     * @param    magArray: Collection mag names
     * @param    count: Number of each mag which needs to be given.
     * @param    toQuickBar: Should be added to the quick bar, or not.
     */
    int magCount = 2;
    void addMags(PlayerBase player, TStringArray magArray, int count, bool toQuickBar) {
        if (count < 1 || magArray.Count() < 1)
            return;

        for(int x = 0; x < magArray.Count(); x++) {
            for (int i = 0; i < count; i++) {
                EntityAI mag = player.GetInventory().CreateInInventory(magArray.Get(x));
                if (toQuickBar)
                    if(x != 1) {
                        player.SetQuickBarEntityShortcut(mag, x + i + 2, true);
                    }else{
                        player.SetQuickBarEntityShortcut(mag, x + i + 3, true);
                    }
            }
        }
    }

    /*
     * @function dress_player
     * @abstract Gives player class related clothing.
     * @discussion This function puts choosen class clothing on the player.
     *
     * @param    player: Instance Of Player
     * @param    class_clothes: Collection of class clothing names
     * @param    general_items: Collection of general items which will also be given to the player
     */
    void dress_player(PlayerBase player, TStringArray class_clothes, TStringArray general_items){
        for(int i = 0; i < class_clothes.Count(); i++)
            player.GetInventory().CreateAttachment(class_clothes.Get(i));

        for(int x = 0; x < general_items.Count(); x++)
            player.GetInventory().CreateAttachment(general_items.Get(x));
    }
    
    /*
     *  @function   arm_player
     *  @abstract   Arms player with weapon, and adds attachments to weapon.
     *  @discussion This function creates a weapon, goes through all the attachments and attaches them,
     *                while checking if it needs a battery.
     *  @param      player: Instance of Player
     *  @param      weapon_name: Name of weapon to be given
     *  @param      gunAttachments: Collection of attachment names to be added to weapon
     *  @result     EntityAI: weapon
     */
    EntityAI arm_player(PlayerBase player, string weapon_name, TStringArray gunAttachments){
        EntityAI weapon = player.GetHumanInventory().CreateInHands(weapon_name);
        for(int i = 0; i < gunAttachments.Count(); i++){
            EntityAI attachment = weapon.GetInventory().CreateAttachment(gunAttachments.Get(i));
            for (int x = 0; x < batteryCompatible.Count(); x++){
                if(batteryCompatible.Get(x).Contains(gunAttachments.Get(i)))
                    attachment.GetInventory().CreateAttachment("Battery9V");
            }
        }
        return weapon;
    }

    EntityAI arm_player_secondary(PlayerBase player, string weapon_name, TStringArray secondaryAttachments){
        EntityAI weapon = player.GetInventory().CreateInInventory(weapon_name);
        for(int i = 0; i < secondaryAttachments.Count(); i++){
            EntityAI attachment = weapon.GetInventory().CreateAttachment(secondaryAttachments.Get(i));
            for (int x = 0; x < batteryCompatible.Count(); x++){
                if(batteryCompatible.Get(x).Contains(secondaryAttachments.Get(i)))
                    attachment.GetInventory().CreateAttachment("Battery9V");
            }
        }
        return weapon;
    }

    /*
     *  @function   give_utilities
     *  @discussion Added a backpack to the players back and fills it with provided items.
     *
     *  @param      player: Instance of Player
     *  @param      util: Collection of utility items names to be added to the backpack
     *  @param      backpack: Backpack item name which items will be stored, and will be added to players back.
     */
    void give_utilities(PlayerBase player, TStringArray util, string backpack){
        EntityAI backpackEnt = player.GetInventory().CreateAttachment(backpack);
        for (int i = 0; i < util.Count(); i++)
            backpackEnt.GetInventory().CreateInInventory(util.Get(i));
    }

    /*
    *  @function   give_medical
    *  @discussion Puts a bag into players inventory and adds items into the bag.
    *                  This is NOT the same as give_utilities, one adds bag to inventory, one adds bag to player.
    *  @param      player: Instance of Player
    *  @param      bag_name: Name of the bag which will be added to the players inventory and filled with items.
    *  @param      supplies: Collection of items which will be added to the bag.
    */
    void give_medical(PlayerBase player, string bag_name, TStringArray supplies) {
        EntityAI medickit = player.GetInventory().CreateInInventory(bag_name);

        for (int i = 0; i < supplies.Count(); i++)
            medickit.GetInventory().CreateInInventory(supplies.Get(i));
    }

    override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName){
        Entity playerEnt;
        playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");//Creates random player
        Class.CastTo(m_player, playerEnt);

        GetGame().SelectPlayer(identity, m_player);

        return m_player;
    }

    override void StartingEquipSetup(PlayerBase player, bool clothesChosen) {
        player.RemoveAllItems();

        EntityAI primary;
        EntityAI secondary;

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
        player.GetInventory().CreateInInventory(oneHanders.GetRandomElement());
        player.SetQuickBarEntityShortcut(primary, 0, true);

        if(secondary != null){
            player.SetQuickBarEntityShortcut(secondary, 1, true);
        }
    }
};

Mission CreateCustomMission(string path) {
    return new CustomMission();
}