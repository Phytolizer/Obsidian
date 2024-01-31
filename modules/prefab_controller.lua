------------------------------------------------------------------------
--  MODULE: Prefab Controller
------------------------------------------------------------------------
--
--  Copyright (C) 2019-2022 MsrSgtShooterPerson
--
--  This program is free software; you can redistribute it and/or
--  modify it under the terms of the GNU General Public License
--  as published by the Free Software Foundation; either version 2
--  of the License, or (at your option) any later version.
--
--  This program is distributed in the hope that it will be useful,
--  but WITHOUT ANY WARRANTY; without even the implied warranty of
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--  GNU General Public License for more details.
--
-------------------------------------------------------------------

PREFAB_CONTROL = { }

PREFAB_CONTROL.WALL_CHOICES =
{
  "fab_default", _("DEFAULT"),
  "fab_some",    _("Some"),
  "fab_less",    _("Less"),
  "fab_few",     _("Few"),
  "fab_rare",    _("Rare"),
  "fab_none",    _("NONE")
}

PREFAB_CONTROL.WALL_REDUCTION_ODDS =
{
  fab_some = 0.2,
  fab_less = 0.4,
  fab_few = 0.6,
  fab_rare = 0.8,
  fab_none = 1
}

PREFAB_CONTROL.POINT_CHOICES =
{
  "fab_none",    _("NONE"),
  "fab_rare",    _("Rare"),
  "fab_few",     _("Few"),
  "fab_default", _("DEFAULT"),
  "fab_more",    _("More"),
  "fab_heaps",   _("Heaps")
}

PREFAB_CONTROL.WALL_GROUP_ODDS =
{
  fab_always = 100,
  fab_heaps = 2.25,
  fab_lots = 1.8,
  fab_more = 1.35,
  fab_default = 1,
  fab_some = 0.8,
  fab_less = 0.6,
  fab_few = 0.4,
  fab_rare = 0.2,
  fab_none = 0,
}

PREFAB_CONTROL.WALL_GROUP_CHOICES =
{
  "fab_always",  _("Always"),
  "fab_heaps",   _("Heaps"),
  "fab_lots",    _("Lots"),
  "fab_more",    _("More"),
  "fab_default", _("DEFAULT"),
  "fab_some",    _("Some"),
  "fab_less",    _("Less"),
  "fab_few",     _("Few"),
  "fab_rare",    _("Rare"),
  "fab_none",    _("NONE")
}


PREFAB_CONTROL.DAMAGING_HALLWAY_CHOICES =
{
  "default", _("DEFAULT"),
  "no", _("Non-damaging")
}

PREFAB_CONTROL.FINE_TUNE_MULT_FACTORS =
{
  "0", _("NONE"),
  "0.33", _("Rare"),
  "0.5",  _("Few"),
  "0.75", _("Less"),
  "1", _("Default"),
  "2", _("More"),
  "4", _("Heaps"),
  "8", _("I LOVE IT")
}

PREFAB_CONTROL.FILTER_CATEGORIES =
{
  gamble = "pf_gamble",
  crushers = "pf_crushers",
  dexterity = "pf_dexterity",
  sight_ambush_cage = "pf_sight_ambushes",
  mirror_maze = "pf_mirror_mazes",
  dark_maze = "pf_dark_mazes",
  stair_ladder = "pf_stair_ladders"
}

function PREFAB_CONTROL.setup(self)
  
  module_param_up(self)

end

function PREFAB_CONTROL.fine_tune_filters()
  for _,fab in pairs(PREFABS) do

    for filter,pname in pairs(PREFAB_CONTROL.FILTER_CATEGORIES) do
      if fab.filter == filter then
        fab.prob = fab.prob * tonumber(PARAM[pname])
        fab.use_prob = fab.use_prob * tonumber(PARAM[pname])
  
        if fab.skip_prob then
          fab.skip_prob = math.clamp(0,fab.skip_prob / tonumber(PARAM[pname]), 100)
        end
      end
    end

  end

  if PARAM.bool_jump_crouch == 0 then
    if PARAM.obsidian_resource_pack_active then
      if GAME.THEMES.hell and GAME.THEMES.hell.wide_halls then
        GAME.THEMES.hell.wide_halls.organs = 0
        GAME.THEMES.hell.wide_halls.conveyorh = 0
      end
    end
  end

  local new_fabs_multipliers =
  {

  }
  local new_fab_groups_multipliers =
  {
    tech_o_letter_F = 1.25,
    tech_o_letter_G = 1.25,
    tech_o_letter_H = 1.25,
    tech_o_letter_I = 1.25,
    tech_o_letter_J = 1.25,
    tech_o_letter_K = 1.5,
    tech_o_letter_L = 1.5,
    tech_o_letter_M = 1.5,
    tech_o_letter_N = 3,
    tech_o_letter_O = 3,
    tech_o_letter_P = 3,
    tech_o_letter_Q = 3,
    --
    gtd_prison_A = 1.25,
    --
    gtd_bathwater = 1.25
  }
  local new_themes_multipliers =
  {
    any_copperRust = 2,

    tech_AITextures = 1.25,
    tech_goth_tech = 1.25,
    tech_wood_lab = 1.5,
    tech_dk_green_tech = 1.5,
    tech_copper_steampunk = 1.5,
    tech_wood_lab = 1.75,
    tech_wood_comp = 1.75,
    tech_silver_grate = 1.75,
    tech_bumblebee = 2,

    urban_dk_green_tech = 1.25,
    urban_wood_lab = 1.25,
    urban_wood_comp = 1.5,
    urban_silver_grate = 1.5,
    urban_evil_mansion = 1.75,
    urban_kievan_rus = 2,
    urban_new_york_art_deco = 2,
    urban_computerCatacombs = 2,

    hell_gilded_bricks = 1.2,
    hell_copper_steampunk = 1.2,
    hell_AztecClay = 1.25,
    hell_babylonian = 1.25,
    hell_green_tk = 1.25,
    hell_evil_mansion = 1.75,
    hell_kievan_rus = 2,
    hell_new_york_art_deco = 2,
    hell_computerCatacombs = 2
  }
  local themes =
  {
    "tech",
    "urban",
    "hell",
    "deimos"
  }

  if PARAM.bool_more_new_content == 1 then
    for WG,mult in pairs(new_fab_groups_multipliers) do
      for _,theme_name in pairs(themes) do
        if GAME.THEMES[theme_name] then
          if GAME.THEMES[theme_name].wall_groups and 
          GAME.THEMES[theme_name].wall_groups[WG] then
            GAME.THEMES[theme_name].wall_groups[WG] =
            GAME.THEMES[theme_name].wall_groups[WG] * 
            mult
          end

          if GAME.THEMES[theme_name].outdoor_wall_groups 
          and GAME.THEMES[theme_name].outdoor_wall_groups[WG] then
            GAME.THEMES[theme_name].outdoor_wall_groups[WG] =
            GAME.THEMES[theme_name].outdoor_wall_groups[WG] * 2
          end
        end
      end
    end

    for RT,mult in pairs(new_themes_multipliers) do
      if GAME.ROOM_THEMES[RT] then 
        GAME.ROOM_THEMES[RT].prob = GAME.ROOM_THEMES[RT].prob * mult
      end
    end
  end

  local db_tab = ""
  --[[for _,RT in pairs(GAME.ROOM_THEMES) do
    db_tab = db_tab .. RT.name .. ": " .. RT.prob .. "\n"
  end
  db_tab = db_tab .. table.tostr(GAME.THEMES["tech"].wall_groups, 2)
  gui.printf(db_tab)
  error()]]
end

function PREFAB_CONTROL.set_damaging_hallways()
  if PARAM.pf_damaging_halls == "default" then return end

  for name,fab in pairs(PREFABS) do
    if fab.group == "hellcata" then
      fab.flat_LAVA1 = "BLOOD1"
      fab.tex_LFALL1 = "BFALL1"
      fab.tex_FF2200 = "BF0526" -- top lighting
      fab.tex_FF8629 = "130406" -- liquid fog color
      fab.sector_5 = 0 -- nullify damaging sectors
      fab.thing_2025 = 0
    end

    if fab.group == "pipeline" then
      fab.flat_NUKAGE1 = "FWATER1"
      fab.tex_SFALL1 = "FWATER1"
      fab.tex_1F4525 = "4548BA" -- top lighting
      fab.tex_041C08 = "13131C" -- liquid fog color
      fab.sector_7 = 0 -- nullify damaging sectors
      fab.thing_2025 = 0
    end
  end
end

function PREFAB_CONTROL.get_levels()
  PREFAB_CONTROL.fine_tune_filters()
  PREFAB_CONTROL.set_damaging_hallways()
end

----------------------------------------------------------------

OB_MODULES["prefab_control"] =
{

  name = "prefab_control",

  label = _("Advanced Level Control"),

  where = "arch",
  priority = 95,

  engine = "idtech_1",
  port = "!limit_enforcing",

  hooks =
  {
    setup = PREFAB_CONTROL.setup,
    get_levels = PREFAB_CONTROL.get_levels
  },

  options =
  {
    {
      name="bool_alt_starts",
      label=_("Alt-start Rooms"),
      valuator = "button",
      default = 0,
      tooltip=_("For Co-operative games, sometimes have players start in different rooms"),
    },
    {
      name = "bool_foreshadowing_exit",
      label = _("Foreshadowing Exit"),
      valuator = "button",
      default = 1,
      tooltip = _("Gets exit room theme to follow the theme of the next level, if different."),
      gap=1,
    },

    {
      name = "bool_autodetail",
      label=_("Auto Detailing"),
      valuator = "button",
      default = 1,
      tooltip = _("Reduces the amount of complex architecture in a map based on its size. Default is on in binary map format, off in UDMF map format."),
      priority = 150,
      gap = 1,
    },

    {
      name = "point_prob",
      label=_("Point Decor"),
      choices=PREFAB_CONTROL.POINT_CHOICES,
      tooltip = _("Decor prefabs are prefabs placed along the floors such as crates, pillars, and other decorative elements which aren't tied to walls. This directly modifies probabilities on a per-room basis, not the density for decor prefabs in any given room.\n\nNote: DEFAULT actually behaves like Mix-It-Up."),
      default = "fab_default",
      priority = 101,
    },


    {
      name = "wall_prob",
      label=_("Wall Decor"),
      choices=PREFAB_CONTROL.WALL_CHOICES,
      tooltip = _("Determines the odds for decorated wall junctions in a map versus plain ones."),
      default = "fab_default",
      priority = 100,
    },


    {
      name = "group_wall_prob",
      label = _("Group Walls"),
      choices = PREFAB_CONTROL.WALL_GROUP_CHOICES,
      tooltip = _("Determines the percentage at which grouped walls are applied to rooms."),
      default = "fab_heaps",
      priority = 99,
      gap = 1,
    },

    --


    {
      name = "float_max_room_themes",
      label = _("Max Room Themes Per Level"),
      valuator = "slider",
      units = "",
      min = 1,
      max = 8,
      increment = 1,
      default = 1,
      tooltip = _("Determines the maximum number of distinct indoor room themes used per level. Default is 1."),
      priority = 100,
    },

    {
      name = "bool_avoid_room_theme_reuse",
      label = _("Avoid Room Theme Re-Use"),
      valuator = "button",
      default = 1,
      priority = 48,
      tooltip = _("Attempt to use unique room themes for each generated level, unless the pool of available themes is exhausted."),
    },

    {
      name = "float_max_indoor_wall_groups",
      label = _("Max Indoor Wall Groups Per Level"),
      valuator = "slider",
      units = "",
      min = 1,
      max = 8,
      increment = 1,
      default = 2,
      tooltip = _("Determines the maximum number of distinct indoor wall groups used per level. Default is 2."),
      priority = 50,
    },

    {
      name = "bool_avoid_wall_group_reuse",
      label = _("Avoid Wall Group Re-Use"),
      valuator = "button",
      default = 1,
      priority = 48,
      tooltip = _("Attempt to use unique indoor wall groups for each generated level, unless the pool of available groups is exhausted."),
      gap = 1,
    },
    --


    {
      name = "bool_peered_exits",
      label = _("Peered Starts/Exits"),
      valuator = "button",
      default = 1,
      priority = 48,
      tooltip = _("Attempt to use matched start and exit fabs for a level (if a matched set is possible)."),
    },


    {
      name = "steppy_caves",
      label = _("Steppy Caves"),
      choices =
      {
        "always", _("Always"),
        "yes", _("Yes"),
        "no", _("No"),
      },
      tooltip = _("Disables or enables caves with height variations."),
      default = "yes",
      priority = 47,
    },

    --


    {
      name="pf_crushers", 
      label=_("Crushers"), 
      choices=PREFAB_CONTROL.FINE_TUNE_MULT_FACTORS,
      tooltip=_("Changes probabilities for fabs with crushing sectors. Default is on."),
      default="1",
      priority = 14,
    },


    {
      name="pf_dexterity", 
      label=_("Dexterity Fabs"), 
      choices=PREFAB_CONTROL.FINE_TUNE_MULT_FACTORS,
      tooltip=_("Changes probabilities for fabs featuring Chasm-ish navigation. Default is on."),
      default="1",
      priority = 13,
    },

    {
      name="pf_gamble", 
      label=_("Gambling Fabs"), 
      choices=PREFAB_CONTROL.FINE_TUNE_MULT_FACTORS,
      tooltip=_("Changes probabilities for fabs that may lockout a player on items. Default is on."),
      default="1",
      priority = 12,
    },


    {
      name="pf_sight_ambushes", 
      label=_("Sight Ambush Cages"), 
      choices=PREFAB_CONTROL.FINE_TUNE_MULT_FACTORS,
      tooltip=_("Changes probabilities for cages that unleash its monsters when player is in sight. Default is on."),
      default="1",
      priority = 11,
    },


    {
      name = "pf_mirror_mazes", 
      label=_("Mirror Mazes"), 
      choices=PREFAB_CONTROL.FINE_TUNE_MULT_FACTORS,
      tooltip=_("Changes probabilities for hell mirror maze closets and joiners."),
      default="1",
      priority = 10,
    },


    {
      name = "pf_dark_mazes", 
      label=_("Dark Mazes"), 
      choices=PREFAB_CONTROL.FINE_TUNE_MULT_FACTORS,
      tooltip=_("Changes probabilities for dark/eye maze joiners in hell theme."),
      default="1",
      priority = 9,
    },
    

    {
      name = "pf_stair_ladders", 
      label=_("Stair Ladders"), 
      choices=PREFAB_CONTROL.FINE_TUNE_MULT_FACTORS,
      tooltip=_("Changes probabilities for high-step ladders (stairs)."),
      default="1",
      priority = 8,
      gap = 1,
    },


    {
      name = "bool_jump_crouch",
      label=_("Jump/Crouch Fabs"),
      valuator = "button",
      default = 1,
      tooltip = _("Enables or disables prefabs that require jumping or crouching to navigate."),
      priority = 7,
      gap = 1
    },

    --


    {
      name = "pf_damaging_halls", 
      label = _("Damaging Hallways"), 
      choices=PREFAB_CONTROL.DAMAGING_HALLWAY_CHOICES,
      tooltip = _("Changes the liquids on hallways with damaging floors to either be damaging (default) or non-damaging."),
      default = "default",
      priority = 5,
      gap = 1,
    },

    --

    {
      name = "bool_more_new_content",
      label = _("Test New Content"),
      valuator = "button",
      default = 0,
      tooltip = _("Greatly increase probability for recent added content for testing purposes. " .. 
      "Changes in content is expected and some assets will be gradually removed from this option's effects."),
      priority = 4,
    },


    {
      name = "bool_fab_match_theme",
      label=_("Match Theme"),
      valuator = "button",
      default = 1,
      tooltip = _("Ensures that prefabs selected match their intended Theme."),
      priority = 1,
    }
  }
}
