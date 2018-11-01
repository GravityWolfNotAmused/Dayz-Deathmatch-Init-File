
void main() {

    Hive ce = CreateHive();
    if (ce)
        ce.InitOffline();

    Weather weather = g_Game.GetWeather();

    weather.GetOvercast().SetLimits(0.0, 1.0);
    weather.GetRain().SetLimits(0.0, 1.0);
    weather.GetFog().SetLimits(0.0, 0.25);

    weather.GetOvercast().SetForecastChangeLimits(0.0, 0.2);
    weather.GetRain().SetForecastChangeLimits(0.0, 0.1);
    weather.GetFog().SetForecastChangeLimits(0.15, 0.45);

    weather.GetOvercast().SetForecastTimeLimits(1800, 1800);
    weather.GetRain().SetForecastTimeLimits(600, 600);
    weather.GetFog().SetForecastTimeLimits(1800, 1800);

    weather.GetOvercast().Set(Math.RandomFloatInclusive(0.0, 0.3), 0, 0);
    weather.GetRain().Set(Math.RandomFloatInclusive(0.0, 0.2), 0, 0);
    weather.GetFog().Set(Math.RandomFloatInclusive(0.0, 0.1), 0, 0);

    weather.SetWindMaximumSpeed(15);
    weather.SetWindFunctionParams(0.1, 0.3, 50);
}

class CustomMission : MissionServer {
    int magCount = 2;
    /*
     *  Bag Name
     */
    string bag_name = "SmershBag";
    /*
     *  Assault Class
     */
    autoptr TStringArray Assault_Clothing = {"BandanaMask_CamoPattern", "BallisticHelmet_Green", "USMCJacket_Woodland", "USMCPants_Woodland"};
    string Assault_Gun = "M4A1";
    string Assault_SideArm = "MakarovIJ70";
    autoptr TStringArray Assault_SideArm_Attachments = {"MakarovPBSuppressor"};
    autoptr TStringArray Assault_Attachments = {"M4_CQBBttstck_Black", "ACOGOptic", "M4_RISHndgrd_Black"};
    string Assault_Mag = "MAG_STANAG_30Rnd";

    /*
     *  Submachine Gun Class
     */
    autoptr TStringArray Submachine_Clothing = {"M65Jacket_Black", "SlacksPants_Black", "RocketAviators", "BalaclavaMask_Blackskull"};
    string SubMachineGun_Gun = "MP5K";
    autoptr TStringArray SubmachineGun_Attachments = {"MP5_PRailHndgrd", "MP5k_StockBttstck"};
    string SubmachineGun_Mag = "MAG_MP5_15Rnd";

    /*
     *  Sniper Class
     */

    autoptr TStringArray Sniper_Clothing = {"GhillieHood_Mossy", "GhillieSuit_Mossy", "GhillieTop_Mossy"};
    string Sniper_Gun = "MOSIN9130_CAMO";
    autoptr TStringArray Sniper_Attachments = {"PUScopeOptic"};
    string Sniper_Mag = "Mag_CLIP762x54_5Rnd";

    /*
     *  Medic Class
     */
    autoptr TStringArray Medic_Clothing = {"BallisticHelmet_Green", "GasMask", "ParamedicJacket_Green", "ParamedicPants_Green"};
    string Medic_Gun = "MakarovIJ70";
    autoptr TStringArray Medic_Attachments = {"MakarovPBSuppressor"};
    string Medical_Supply_Case = "FIRSTAIDKIT";
    autoptr TStringArray Medical_Supplies = {"BANDAGEDRESSING", "MORPHINE", "SALINEBAGIV", "PAINKILLERTABLETS"};
    string Medic_Mag = "MAG_IJ70_8RND";

    /*
     *  General Items which everyone will receive on spawn; regardless of class.
     */
    autoptr TStringArray Utilities = {"TacticalBaconCan", "Canteen", "CanOpener"};
    autoptr TStringArray Uniform = {"SmershVest", "TacticalGloves_Green", "CombatBoots_Black"};

    /*
     *  Melee Weapons
     */
    autoptr TStringArray oneHanders = {"Machete", "HuntingKnife", "KitchenKnife"};

    void addMags(PlayerBase player, string mag_type, int count) {
        if (count < 1)
            return;

        if(mag_type.Length() == 0) {
            return;
        }

        EntityAI mag;

        for (int i = 0; i < count; i++) {
            mag = player.GetInventory().CreateInInventory(mag_type);
        }
    }
    void dress_player(PlayerBase player, TStringArray class_clothes, TStringArray general_items){
        EntityAI wearable;
        for(int i = 0; i < class_clothes.Count(); i++){
            wearable = player.GetInventory().CreateAttachment(class_clothes.Get(i));
        }
        for(int x = 0; x < general_items.Count(); x++){
            wearable = player.GetInventory().CreateAttachment(general_items.Get(x));
        }
    }
    void arm_player(PlayerBase player, string weapon_name, TStringArray gunAttachments){
        EntityAI weapon = player.GetHumanInventory().CreateInHands(weapon_name);
        for(int i = 0; i < gunAttachments.Count(); i++){
            EntityAI attachment = weapon.GetInventory().CreateAttachment(gunAttachments.Get(i));
        }
    }
    void give_utilities(PlayerBase player, TStringArray util, string backpack, string mag){
        EntityAI backpackEnt = player.GetInventory().CreateAttachment(backpack);
        for (int i = 0; i < util.Count(); i++) {
            EntityAI contents = backpackEnt.GetInventory().CreateInInventory(util.Get(i));
        }
        addMags(player, mag, magCount);
    }
    void give_medical(PlayerBase player, string bag_name, TStringArray supplies) {
        EntityAI medickit = player.GetInventory().CreateInInventory(bag_name);

        for (int i = 0; i < supplies.Count(); i++) {
            medickit.GetInventory().CreateInInventory(supplies.Get(i));
        }
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

        EntityAI meleeWeapon;

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
    }
};

Mission CreateCustomMission(string path) {
    return new CustomMission();
}
