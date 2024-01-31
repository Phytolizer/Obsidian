---------------------------------------------------------------
--  MODULE: Hexen Control
----------------------------------------------------------------
--
--  Copyright (C) 2009-2010 Andrew Apted
--  Copyright (C) 2020-2021 MsrSgtShooterPerson
--  Copyright (C) 2021 Cubebert
--
--  This program is free software; you can redistribute it and/or
--  modify it under the terms of the GNU General Public License
--  as published by the Free Software Foundation; either version 2,
--  of the License, or (at your option) any later version.
--
--  This program is distributed in the hope that it will be useful,
--  but WITHOUT ANY WARRANTY; without even the implied warranty of
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--  GNU General Public License for more details.
--
----------------------------------------------------------------

CTL_HEXEN = {}

function CTL_HEXEN.monster_setup(self)

  module_param_up(self)

  for _,opt in pairs(self.options) do

    local M = GAME.MONSTERS[string.sub(opt.name, 7)]

    if M and PARAM[opt.name] ~= gui.gettext("Default") then
      M.prob    = PARAM[opt.name] * 100
      M.density = M.prob * .006 + .1

      -- allow Spectres to be controlled individually
      M.replaces = nil

      -- loosen some of the normal restrictions
      M.skip_prob = nil
      M.crazy_prob = nil

      if M.prob > 40 then
        M.level = 1
        M.weap_min_damage = nil
      end

      if M.prob > 200 then
        M.boss_type = nil
      end
    end
  end

end


OB_MODULES["hexen_mon_control"] =
{

  name = "hexen_mon_control",

  label = _("Hexen Monster Control"),

  game = "hexen",
  engine = "idtech_1",
  port = "!limit_enforcing",
  where = "combat",

  hooks =
  {
    setup = CTL_HEXEN.monster_setup
  },

  options =
  {

     {
      name = "float_ettin",
      label = _("Ettin"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Ettins."), 
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },

     {
      name = "float_afrit",
      label = _("Afrit"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Afrits."), 
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },

     {
      name = "float_centaur1",
      label = _("Centaur"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Centaurs."), 
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },

     {
      name = "float_centaur2",
      label = _("Slaughtaur"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Slaughtaurs."), 
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },

     {
      name = "float_serpent1",
      label = _("Stalker"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Stalkers."), 
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },

     {
      name = "float_serpent2",
      label = _("Stalker w/ projectile"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Projectile Stalkers."), 
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },

     {
      name = "float_wendigo",
      label = _("Wendigo"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Wendigos."),
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },

     {
      name = "float_demon1",
      label = _("Green Serpent"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Green Serpents."), 
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },
	 
     {
      name = "float_demon2",
      label = _("Brown Serpent"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Brown Serpents."), 
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },
	 
     {
      name = "float_bishop",
      label = _("Bishop"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Bishops."), 
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },
	 
     {
      name = "float_reiver",
      label = _("Reiver"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"), 
      tooltip = _("Control the amount of Reivers."),
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },
	 
     {
      name = "float_reiver_b",
      label = _("Buried Reiver"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"), 
      tooltip = _("Control the amount of Buried Reivers."),
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },
	  
     {
      name = "float_Heresiarch",
      label = _("Heresiarch"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Heresiarchs."), 
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },
	 
     {
      name = "float_Zedek",
      label = _("Zedek"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Zedeks."), 
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },
	 
     {
      name = "float_Traductus",
      label = _("Traductus"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Traducti."), 
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },
	 
     {
      name = "float_Menelkir",
      label = _("Menelkir"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Menelkirs."), 
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },

     {
      name = "float_Korax",
      label = _("Korax"),
      valuator = "slider",
      min = 0,
      max = 20,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Koraxes."), 
      presets = _("0:0 (None at all),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),20:20 (INSANE)"),
      
     },
  },
}

function CTL_HEXEN.item_setup(self)

  module_param_up(self)

  local function change_probz(name, info)
    if PARAM[name] and PARAM[name] ~= gui.gettext("Default") then
      local mult = PARAM[name] or 0

      if info.add_prob then info.add_prob = info.add_prob * mult end
      if info.start_prob then info.start_prob = info.start_prob * mult end
      if info.crazy_prob then info.crazy_prob = info.crazy_prob * mult end
      if info.closet_prob then info.closet_prob = info.closet_prob * mult end
      if info.secret_prob then info.secret_prob = info.secret_prob * mult end
      if info.storage_prob then info.storage_prob = info.storage_prob * mult end
    end
  end

  for name, info in pairs(GAME.PICKUPS) do
    float_name = "float_" .. name
    change_probz(float_name, info)
  end

  for name, info in pairs(GAME.NICE_ITEMS) do
    float_name = "float_" .. name
    change_probz(float_name, info)
  end

  if PARAM["float_ultimate_weapon_pieces"] ~= gui.gettext("Default") then
    local mult = PARAM["float_ultimate_weapon_pieces"] or 0
    local info = GAME.NICE_ITEMS["h_ultimate_piece_one"]
    if info.add_prob then info.add_prob = info.add_prob * mult end
    if info.start_prob then info.start_prob = info.start_prob * mult end
    if info.crazy_prob then info.crazy_prob = info.crazy_prob * mult end
    if info.closet_prob then info.closet_prob = info.closet_prob * mult end
    if info.secret_prob then info.secret_prob = info.secret_prob * mult end
    if info.storage_prob then info.storage_prob = info.storage_prob * mult end
    info = GAME.NICE_ITEMS["h_ultimate_piece_two"]
    if info.add_prob then info.add_prob = info.add_prob * mult end
    if info.start_prob then info.start_prob = info.start_prob * mult end
    if info.crazy_prob then info.crazy_prob = info.crazy_prob * mult end
    if info.closet_prob then info.closet_prob = info.closet_prob * mult end
    if info.secret_prob then info.secret_prob = info.secret_prob * mult end
    if info.storage_prob then info.storage_prob = info.storage_prob * mult end
    info = GAME.NICE_ITEMS["h_ultimate_piece_three"]
    if info.add_prob then info.add_prob = info.add_prob * mult end
    if info.start_prob then info.start_prob = info.start_prob * mult end
    if info.crazy_prob then info.crazy_prob = info.crazy_prob * mult end
    if info.closet_prob then info.closet_prob = info.closet_prob * mult end
    if info.secret_prob then info.secret_prob = info.secret_prob * mult end
    if info.storage_prob then info.storage_prob = info.storage_prob * mult end
  end

end

OB_MODULES["hexen_item_control"] =
{

  name = "hexen_item_control",

  label = _("Hexen Item Control"),

  game = "hexen",
  engine = "idtech_1",
  port = "!limit_enforcing",
  where = "pickup",

  hooks =
  {
    get_levels = CTL_HEXEN.item_setup
  },

  options =
  {

     {
      name = "float_h_vial",
      label = _("Crystal Vial"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Crystal Vials."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      priority = 100,
      
     },
     
     {
      name = "float_h_flask",
      label = _("Quartz Flask"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Quartz Flasks."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      priority = 99,
      
     },
    
     {
      name = "float_h_urn",
      label = _("Mystic Urn"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Mystic Urns."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      priority = 93,
      gap = 1,
      
     },

     {
      name = "float_blue_mana",
      label = _("Blue Mana"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Blue Mana."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      priority = 98,
      
     },
     
     {
      name = "float_green_mana",
      label = _("Green Mana"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Green Mana."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      priority = 95,
      
     },    
  
     {
      name = "float_dual_mana",
      label = _("Dual Mana"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Dual Mana."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      
      gap = 1
     },

     {
      name = "float_ar_helmet",
      label = _("Platinum Helm"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Platinum Helms."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      priority = 94,
      
     },

     {
      name = "float_ar_mesh",
      label = _("Mesh Armor"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Mesh Armors."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      
     },

     {
      name = "float_ar_shield",
      label = _("Falcon Shield"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Falcon Shields."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      
     },

     {
      name = "float_ar_amulet",
      label = _("Amulet of Warding"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Amulets of Warding."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      
     },

     {
      name = "float_dragonskin_bracers",
      label = _("Dragonskin Bracers"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Dragonskin Bracers."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      
      gap = 1
     },
     
     {
      name = "float_krater_of_might",
      label = _("Krater of Might"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Kraters of Might."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      
     },

     {
      name = "float_banishment_device",
      label = _("Banishment Device"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Banishment Devices."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      
     },

     {
      name = "float_boots_of_speed",
      label = _("Boots of Speed"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Boots of Speed."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      
     },
    
     {
      name = "float_chaos_device",
      label = _("Chaos Device"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Chaos Devices."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      
      priority = 75,
     },

     {
      name = "float_dark_servant",
      label = _("Dark Servant"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Dark Servants."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      
      priority = 74,
     },

     {
      name = "float_disc_of_repulsion",
      label = _("Disc of Repulsion"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Discs of Repulsion."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      
      priority = 73,
     },

     {
      name = "float_flechette",
      label = _("Flechette"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Flechettes."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      
      priority = 72,
     },

     {
      name = "float_icon_of_the_defender",
      label = _("Icon of the Defender"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"), 
      tooltip = _("Control the amount of Icons of the Defender."),
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      
      priority = 71,
     },

     {
      name = "float_mystic_ambit_incant",
      label = _("Mystic Ambit Incant"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Mystic Ambit Incants."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      
      priority = 70,
     },

     {
      name = "float_porkalator",
      label = _("Porkalator"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Porkalators."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      
      priority = 69,
     },

     {
      name = "float_torch",
      label = _("Torch"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Torches."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      priority = 68,
      
     },

     {
      name = "float_wings_of_wrath",
      label = _("Wings of Wrath"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"),
      tooltip = _("Control the amount of Wings of Wrath."), 
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      priority = 68,
      
     },

     {
      name = "float_ultimate_weapon_pieces",
      label = _("Ultimate Weapon Pieces"),
      valuator = "slider",
      min = 0,
      max = 10,
      increment = .02,
      default = _("Default"),
      nan = _("Default"), 
      tooltip = _("Control the likelihood of finding Ultimate Weapon Pieces."),
      presets = _("0:0 (None),.02:0.02 (Scarce),.14:0.14 (Less),.5:0.5 (Plenty),1.2:1.2 (More),3:3 (Heaps),10:10 (I LOVE IT)"),
      priority = 68,
      
     },

  },
}