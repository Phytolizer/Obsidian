------------------------------------------------------------------------
--  MODULE: Miscellaneous Stuff
------------------------------------------------------------------------
--
--  Copyright (C) 2009      Enhas
--  Copyright (C) 2009-2016 Andrew Apted
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
------------------------------------------------------------------------

MISC_STUFF = { }

MISC_STUFF.YES_NO =
{
  "no",  _("No"),
  "yes", _("Yes"),
}


MISC_STUFF.variety_tip = _(
    "Affects how many different monster types can "..
    "appear in each room.  "..
    "Setting this to NONE will make each level use a single monster type")


function MISC_STUFF.begin_level(self)
  for name,opt in pairs(self.options) do
    local value = self.options[name].value

    if opt.choices == STYLE_CHOICES then
      if value != "mixed" then
        STYLE[name] = value
      end

    else
      -- pistol_starts, or other YES/NO stuff

      if value != "no" then
        PARAM[name] = value
      end
    end
  end
end


OB_MODULES["miscellaneous"] =
{
  label = _("Miscellaneous")

  side = "left"
  priority = 70

  hooks =
  {
    begin_level = MISC_STUFF.begin_level
  }

  options =
  {
    pistol_starts =
    {
      label=_("Pistol Starts")
      choices=EXTRA_SETTINGS.YES_NO
      tooltip=_("Ensure every map can be completed from a pistol start (ignore weapons obtained from earlier maps)")
    }

    start_together =
    {
      label=_("Start Together")
      choices=EXTRA_SETTINGS.YES_NO
      tooltip=_("For Co-operative games, ensure all players start in the same room (disable the separated start rooms)")
    }

    big_rooms   = { label=_("Big Rooms"),      choices=STYLE_CHOICES }
    darkness    = { label=_("Dark Outdoors"),  choices=STYLE_CHOICES }
    doors       = { label=_("Doors"),          choices=STYLE_CHOICES }

    keys        = { label=_("Keyed Doors"),    choices=STYLE_CHOICES }
    mon_variety = { label=_("Monster Variety"),choices=STYLE_CHOICES, tooltip=MISC_STUFF.variety_tip }

    switches    = { label=_("Switched Doors"), choices=STYLE_CHOICES }

    windows     = { label=_("Windows"),        choices=STYLE_CHOICES }

---- PLANNED (UNFINISHED) STUFF ----

--  symmetry    = { label=_("Symmetry"),       choices=STYLE_CHOICES }
--  pictures    = { label=_("Pictures"),       choices=STYLE_CHOICES }
--  cycles      = { label=_("Multiple Paths"), choices=STYLE_CHOICES }
--  ex_floors   = { label=_("3D Floors"),      choices=STYLE_CHOICES }

--  barrels     = { label=_("Barrels"),        choices=STYLE_CHOICES }
--  porches     = { label=_("Porches"),        choices=STYLE_CHOICES }
--  lakes       = { label=_("Lakes"),          choices=STYLE_CHOICES }
  }
}

