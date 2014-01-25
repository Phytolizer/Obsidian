--------------------------------------------------------------------
--------------------------------------------------------------------
--  DOOM 1 / Ultimate DOOM
--------------------------------------------------------------------

--Fixed up for future use in V6 -Chris


DOOM1.THEMES =
{

------ EPISODE 1 : Tech Bases ----------------------

  tech_DEFAULTS =
  {
    liquids =
    {
      nukage=90
      water=15
      lava=10
    }

    facades =
    {
      BROWN1=50
      BROWNGRN=20
      BROWN96=5
      STONE2=10
      STONE3=10
      STARTAN3=30
      STARG3=20
    }

    style_list =
    {
      naturals = { none=30, few=70, some=30, heaps=2 }
    }

    ---!!!  TEMPORARY V3 CRUD  !!!---

    doors =
    {
      silver=20
      silver_fast=2
      silver_once=5
      bigdoor2=20
      bigdoor2_fast=2
      bigdoor2_once=5
      bigdoor3=5
      bigdoor4=10
      bigdoor4_fast=2
      bigdoor4_once=5
    }
  }


  tech_room =
  {
    walls =
    {
      STARTAN3=25
      STARTAN2=12
      STARTAN1=5
      STARG1=5
      STARG2=15
      STARG3=15
      STARBR2=5
      STARGR2=10
      METAL1=2
    }

    floors =
    {
      FLOOR0_1=30
      FLOOR0_2=20
      FLOOR0_3=30
      FLOOR0_7=20
      FLOOR3_3=15
      FLOOR7_1=10
      FLOOR4_5=30
      FLOOR4_6=20
      FLOOR4_8=50
      FLOOR5_1=35
      FLOOR5_2=30
      FLAT1=10
      FLAT5=20
      FLAT14=20
      FLAT5_4=20
    }

    ceilings =
    {
      CEIL5_1=20
      CEIL3_3=15
      CEIL3_5=50
      FLAT1=20
      FLAT4=15
      FLAT18=20
      FLOOR0_2=10
      FLOOR4_1=30
      FLOOR5_1=15
      FLOOR5_4=10
      CEIL4_1=15
      CEIL4_2=15
    }
  }


  tech_brown =
  {
    walls =
    {
      BROWN1=30
      BROWNGRN=20
      BROWN96=10
      BROVINE=5
      BROVINE2=5
    }

    floors =
    {
      FLOOR0_1=30
      FLOOR0_2=20
      FLOOR3_3=20
      FLOOR7_1=15
      FLOOR4_5=30
      FLOOR4_6=30
      FLOOR5_2=30
      FLAT5=20
      FLAT14=10
      FLAT5_4=10
    }

    ceilings =
    {
      CEIL5_1=20
      CEIL3_3=15
      CEIL3_5=50
      FLAT1=20
      FLOOR4_1=30
      FLAT5_4=10
      FLOOR5_4=10
    }
  }


  tech_Computer =
  {
    prob = 10

    walls =
    {
      COMPSPAN=30
      COMPOHSO=10
      COMPTILE=15
      COMPBLUE=15
      TEKWALL4=3
    }

    floors =
    {
      FLAT14=50
      FLOOR1_1=15
      FLAT4=10
      CEIL4_1=20
      CEIL4_2=20
      CEIL5_1=20
    }


    ceilings =
    {
      CEIL5_1=50
      CEIL4_1=15
      CEIL4_2=15
    }
  }


  tech_Shiny =
  {
    prob = 10

    walls =
    {
      SHAWN2=50
      METAL1=5
    }

    floors =
    {
      FLOOR4_8=10
      FLAT14=10
      FLOOR1_1=5
      FLAT23=60
    }

    ceilings =
    {
      FLAT23=50
    }
  }


  tech_Hallway =
  {
    walls =
    {
      BROWN1=33
      BROWNGRN=50
      STARBR2=15
      STARTAN3=30
      STARG3=30
      TEKWALL4=5
    }

    floors =
    {
      FLOOR0_1=30
      FLOOR0_2=20
      FLOOR0_3=30
      FLOOR0_7=20
      FLOOR3_3=15
      FLOOR7_1=15
      FLOOR4_5=30
      FLOOR4_6=20
      FLOOR4_8=30
      FLOOR5_1=35
      FLOOR5_2=30
      FLAT1=10
      FLAT4=20
      FLAT5=20
      FLAT9=5
      FLAT14=20
      FLAT5_4=20
      CEIL5_1=30
      CEIL4_1=10
      CEIL4_2=10
    }

    ceilings =
    {
      FLAT4=20
      CEIL5_1=35
      CEIL3_5=50
      CEIL3_3=20
      FLAT19=20
      FLAT23=20
      FLAT5_4=15
      CEIL4_1=20
      CEIL4_2=20
    }
  }


  tech_Cave =
  {
    naturals =
    {
      ASHWALL=30
      SP_ROCK1=60
      GRAYVINE=20
      TEKWALL4=3
    }
  }


  tech_Outdoors =
  {
    floors =
    {
      BROWN144=30
      BROWN1=20
      STONE=20
      ASHWALL=5
      FLAT10=5
    }

    naturals =
    {
      ASHWALL=35
      SP_ROCK1=70
      GRAYVINE=20
      STONE=30
    }
  }


----- EPISODE 3 : Hell ---------------------------

  hell_DEFAULTS =
  {
    --  Water is seen in a few locations in episode 3 -Chris

    liquids =
    {
      lava=30
      blood=90
      nukage=5
      water=10
    }

    keys =
    {
      ks_red=50
      ks_blue=50
      ks_yellow=50
    }

    facades =
    {
      STONE2=10
      STONE3=15
      WOOD1=50
      GSTONE1=45
      MARBLE1=30
      BROWN1=5
      BROWNGRN=5
      WOOD5=25
      SP_HOT1=10
      SKINMET1=10
      SKINMET2=10
      SKINTEK1=10
    }

    monster_prefs = { zombie=0.3, shooter=0.6, skull=2.0 }

    ---!!!  TEMPORARY V3 CRUD  !!!---

    doors =
    {
      wooden=20
      wooden_fast=2
      wooden_once=5
      wooden2=20
      wooden2_fast=2
      wooden2_once=5
    }
  }

  hell_Marble =
  {
    walls =
    {
      MARBLE1=30
      MARBLE2=15
      MARBLE3=20
      GSTVINE1=20
      GSTVINE2=20
      SKINMET1=3
      SKINMET2=3
      SKINTEK1=5
      SKINTEK2=5
    }

    floors =
    {
      DEM1_5=30
      DEM1_6=30
      FLAT5_7=10
      FLAT5_8=5
      FLAT10=10
      FLOOR7_1=10
      FLOOR7_2=30
      FLAT1=10
      FLAT5=5
      FLAT8=5
      FLOOR5_2=10
    }

    ceilings =
    {
      FLAT1=10
      FLAT10=10
      FLAT5_5=5
      FLOOR7_2=30
      DEM1_5=30
      DEM1_6=30
      FLOOR6_2=5
      FLAT5_1=5
      FLAT5_2=5
      CEIL1_1=5
    }

    corners =
    {
      SKULWALL=8
      SKULWAL3=7
    }
  }


  hell_Wood =
  {
    prob = 20

    walls =
    {
      WOOD1=50
      WOOD3=30
      WOOD5=20
    }

    floors =
    {
      FLAT5_1=30
      FLAT5_2=50
      FLAT5_5=15
    }

    ceilings =
    {
      CEIL1_1=50
      FLAT5_2=30
      FLAT5_1=15
    }
  }


  hell_Skin =
  {
    prob = 20

    walls =
    {
      SKIN2=15
      SKINFACE=20
      SKSNAKE2=20
      SKINTEK1=10
      SKINTEK2=10
      SKINMET1=50
      SKINMET2=40
      SKINCUT=10
      SKINSYMB=5
    }

    floors =
    {
      SFLR6_1=10
      FLOOR7_1=20
      FLAT5_5=10
      FLOOR6_1=40
      MFLR8_2=10
      MFLR8_4=10
    }

    ceilings =
    {
      SFLR6_1=30
      SFLR6_4=10
      FLOOR6_1=20
    }
  }


  hell_Hot =
  {
    walls =
    {
      SP_HOT1=70
      GSTVINE1=15
      GSTVINE2=15
      STONE=10
      STONE3=5
      SKINMET2=5
      BROWN1=2
      SKINCUT=2
      SKINTEK1=5
      SKINTEK2=5
    }

    floors =
    {
      FLAT5_7=10
      FLAT5_8=10
      FLAT10=10
      FLAT5_3=30
      FLOOR7_1=15
      FLAT1=10
      FLOOR5_2=10
      FLOOR6_1=35
      FLAT8=15
      FLAT5=15
    }

    ceilings =
    {
      FLAT1=15
      FLOOR6_1=30
      FLOOR6_2=15
      FLAT10=10
      FLAT8=5
      FLAT5_3=20
      FLAT5_1=5
      FLAT5_2=5
      CEIL1_1=5
    }

    corners =
    {
      SKULWALL=10
      SKULWAL3=10
      REDWALL1=15
    }
  }


  hell_Outdoors =
  {
    kind = "outdoors"

    floors =
    {
      ASHWALL=30
      FLAT5_4=5
      FLAT10=20
      FLOOR6_1=40
      SFLR6_1=10
      SFLR6_4=10
      MFLR8_2=15
      MFLR8_4=10
      FLAT5_2=5
      FLAT5=5
    }

    naturals =
    {
      ASHWALL=50
      GRAYVINE=20
      SP_ROCK1=50
      ROCKRED1=90
      SKSNAKE1=10
      SKSNAKE2=10
    }
  }


  hell_Outdoors_hot =
  {
    kind = "outdoors"

    floors =
    {
      FLAT5_6=5
      ASHWALL=10
      FLAT10=20
      DEM1_5=15
      DEM1_6=15
      FLOOR7_2=20
      FLOOR7_1=15
      SFLR6_1=10
      SFLR6_4=15
      MFLR8_2=10
      FLAT5_2=5
    }

    naturals =
    {
      ASHWALL=30
      GRAYVINE=15
      SP_ROCK1=50
      ROCKRED1=90
      SKSNAKE1=10
      SKSNAKE2=10
      FIREBLU1=70
    }
  }


  hell_Cave =
  {
    kind = "cave"

    naturals =
    {
      ROCKRED1=90
      SKIN2=30
      SKINFACE=25
      SKSNAKE1=35
      SKSNAKE2=35
      FIREBLU1=50
      FIRELAVA=50
    }
  }


------ EPISODE 2 ------------------------------

  -- Deimos theme by Mr. Chris

  deimos_DEFAULTS =
  {
    liquids =
    {
      nukage=60
      blood=20
      water=10
    }

    -- Best facades would be STONE/2/3, BROVINE/2, BROWN1 and maybe a few others as I have not seen many
    -- other textures on the episode 2 exterior.
    facades =
    {
      STONE2=40
      STONE3=60
      BROVINE=30
      BROVINE2=25
      BROWN1=50
      BROWNGRN=20
    }

    style_list =
    {
      naturals = { none=40, few=70, some=20, heaps=2 }
    }

    ---!!!  TEMPORARY V3 CRUD  !!!---

    doors =
    {
      silver=20
      silver_fast=2
      silver_once=5
      bigdoor2=20
      bigdoor2_fast=2
      bigdoor2_once=5
      bigdoor3=5
      bigdoor4=10
      bigdoor4_fast=2
      bigdoor4_once=5
    }
  }


  deimos_Room =
  {
    walls =
    {
      STARTAN3=10
      STARTAN2=5
      STARTAN1=5
      STARG2=15
      ICKWALL1=15
      STARBR2=15
      STARGR2=10
      STARG1=5
      STARG2=5
      STARG3=7
      ICKWALL3=30
      GRAY7=20
      GRAY5=15
      GRAY1=15
      BROWN1=5
      BROWNGRN=10
      BROWN96=5
      STONE2=30
      STONE3=20
    }

    floors =
    {
      FLOOR0_1=30
      FLOOR0_2=40
      FLOOR0_3=30
      CEIL4_1=5
      FLOOR0_7=10
      FLOOR3_3=20
      FLOOR7_1=20
      CEIL_4_2=10
      FLOOR4_1=30
      FLOOR4_6=20
      FLOOR4_8=50
      FLOOR5_2=35
      FLAT1=40
      FLAT5=30
      FLAT14=10
      FLAT1_1=30
      FLOOR1_6=3
      FLAT1_2=30
      FLOOR5_1=50
      FLAT3=15
      FLAT5_4=15
    }

    ceilings =
    {
      CEIL5_1=30
      CEIL3_3=70
      CEIL3_5=50
      CEIL4_1=10
      CEIL4_2=10
      FLAT1=30
      FLAT4=20
      FLAT19=30
      FLAT8=15
      FLAT5_4=20
      FLOOR0_2=20
      FLOOR4_1=50
      FLOOR5_1=50
      FLOOR5_4=10
    }
  }

  deimos_Hellish =
  {
    walls =
    {
      MARBLE1=15
      MARBLE2=15
      MARBLE3=15
      BROWNGRN=15
      COMPTILE=15
      BROWN1=15
      STARTAN3=15
      STARG3=15
      WOOD1=15
      WOOD3=15
      WOOD5=15
      BROVINE=15
      BROVINE2=15
      ICKWALL3=15
      GRAY7=15
    }

    floors =
    {
      DEM1_5=30
      DEM1_6=50
      FLAT10=5
      FLOOR7_1=5
      FLOOR7_2=50
      FLOOR4_1=30
      FLOOR4_6=20
      FLOOR4_8=50
      FLOOR5_2=35
      FLAT1=40
      FLAT5=30
      FLAT14=10
    }

    ceilings =
    {
      FLOOR7_2=50
      DEM1_5=50
      DEM1_6=30
      FLOOR6_2=5
      CEIL5_1=30
      CEIL3_3=50
      CEIL3_5=30
      CEIL4_1=10
      CEIL4_2=10
    }
  }


  deimos_Lab =
  {
    prob = 10

    walls =
    {
      COMPTILE=40
      COMPBLUE=10
      COMPSPAN=15
      METAL1=20
    }

    floors =
    {
      FLOOR4_8=15
      FLOOR5_1=15
      FLAT14=40
      FLOOR1_1=30
      CEIL4_2=20
      CEIL4_1=20
    }

    ceilings =
    {
      CEIL5_1=30
      CEIL4_1=10
      CEIL4_2=15
      FLOOR4_8=15
      FLAT14=10
    }
  }


  deimos_Hallway =
  {
    kind = "hallway"

    walls =
    {
      BROWN1=33
      BROWNGRN=50
      BROVINE=20
      BROVINE2=15
      GRAY1=50
      GRAY5=33
      ICKWALL1=30
      ICKWALL3=30
      STONE2=40
      STONE3=50
      METAL1=30
    }

    floors =
    {
      FLAT4=30
      CEIL4_1=15
      CEIl4_2=15
      CEIL5_1=30
      FLAT14=20
      FLAT5_4=20
      FLOOR3_3=30
      FLOOR4_8=40
      FLOOR5_1=25
      FLOOR5_2=10
      FLAT5=20
      FLOOR1_6=4
      FLOOR7_2=3
      FLAT5_1=3
      FLAT5_2=3
      DEM1_5=3
      DEM1_6=3
    }

    ceilings =
    {
      FLAT4=20
      CEIL4_1=15
      CEIl4_2=15
      CEIL5_1=30
      CEIL3_5=25
      CEIL3_3=50
      FLAT18=15
      FLAT19=20
      FLAT5_4=10
      FLOOR4_8=25
      FLOOR5_1=20
      FLOOR7_1=15
      FLOOR7_2=2
      FLAT5_1=2
      FLAT5_2=2
      DEM1_5=2
      DEM1_6=2
    }
  }


  deimos_Hallway_hell =
  {
    kind = "hallway"

    walls =
    {
      MARBLE1=20
      MARBLE2=20
      MARBLE3=20
      GSTONE1=20
      BROVINE=20
      COMPTILE=20
    }

    floors =
    {
      FLAT4=30
      CEIL4_1=15
      CEIl4_2=15
      CEIL5_1=30
      FLAT14=20
      FLAT5_4=20
      FLOOR3_3=30
      FLOOR4_8=40
      FLOOR5_1=25
      FLOOR5_2=10
      FLAT5=20
      FLOOR1_6=4
      FLOOR7_2=15
      FLAT5_1=15
      FLAT5_2=15
      DEM1_5=15
      DEM1_6=15
    }

    ceilings =
    {
      FLAT4=20
      CEIL4_1=15
      CEIl4_2=15
      CEIL5_1=30
      CEIL3_5=25
      CEIL3_3=20
      FLAT18=15
      FLAT19=20
      FLAT5_4=10
      FLOOR4_8=15
      FLOOR5_1=20
      FLOOR7_1=15
      FLOOR7_2=15
      FLAT5_1=15
      FLAT5_2=15
      DEM1_5=15
      DEM1_6=15
    }
  }


  deimos_Cave =
  {
    kind = "cave"

    naturals =
    {
      SP_ROCK1=90
      ASHWALL=20
      BROWNHUG=15
      GRAYVINE=10
    }
  }


  deimos_Outdoors =
  {
    kind = "outdoors"

--Makes sense for high prob for SP_ROCK1 because the intermission screen shows
--Deimos has a desolate, gray ground.
    floors = 
    { 
      BROWN144=30
      BROWN1=10
      STONE=10 
    }

    naturals = 
    { 
      SP_ROCK1=60
      ASHWALL=2
      FLAT10=3 
    }
  }


----- EPISODE 4 -------------------------------

  -- Thy Flesh Consumed by Mr. Chris
  -- Basically a modified version of doom_hell1 to match id's E4 better

  flesh_DEFAULTS =
  {
    liquids =
    {
      lava=30
      blood=50
      nukage=10
      water=20
    }

    keys =
    {
      ks_red=50
      ks_blue=50
      ks_yellow=50
    }

    facades =
    {
      STONE2=20
      STONE3=15
      WOOD1=50
      GSTONE1=30
      MARBLE1=20
      BROWN1=10
      BROWNGRN=10
      WOOD5=40
      SP_HOT1=5
      SKINMET1=10
      SKINMET2=10
    }

    monster_prefs =
    {
      zombie=0.6
      shooter=0.8
      skull=1.2
      demon=1.5
    }
  }


  flesh_Room =
  {
    walls =
    {
      BROWNGRN=20
      BROVINE2=15
      WOOD5=10
      GSTONE1=20
      STONE=10
      STONE2=5
      STONE3=10
    }

    floors =
    {
      DEM1_5=10
      DEM1_6=10
      FLAT5_5=10
      FLAT5_7=7
      FLAT5_8=7
      FLAT10=12
      FLOOR7_1=10
      FLOOR7_2=10
      FLOOR5_2=10
      FLOOR5_3=10
      FLOOR5_4=10
      FLAT5=10
      FLAT8=10
      SFLR6_1=5
      SFLR6_4=5
      MFLR8_1=5
      MFLR8_2=10
    }

    ceilings =
    {
      FLAT1=10
      FLAT10=10
      FLAT5_5=10
      FLOOR7_2=15
      DEM1_6=10
      FLOOR6_1=10
      FLOOR6_2=10
      MFLR8_1=12
      FLAT5_4=10
      SFLR6_1=5
      SFLR6_4=5
      CEIL1_1=10
      FLAT5_1=5
      FLAT5_2=5
      FLAT8=8
    }
  }


  flesh_Wood =
  {
    walls =
    {
      WOOD1=50
      WOOD3=30
      WOOD5=20
      SKINMET1=15
      SKINMET2=15
      SKINTEK1=6
      SKINTEK2=6
    }

    floors =
    {
      FLAT5_1=30
      FLAT5_2=50
      FLAT5_5=15
      FLAT5=7
      FLAT8=7
    }

    ceilings =
    {
      CEIL1_1=50
      FLAT5_2=30
      FLAT5_1=15
      FLOOR7_1=10
    }
  }
 

  flesh_Marble =
  {
    walls =
    {
      MARBLE1=50
      MARBLE2=25
      MARBLE3=20
    }

    floors =
    {
      DEM1_5=30
      DEM1_6=50
      FLAT10=5
      FLOOR7_1=5
      FLOOR7_2=50
    }

    ceilings =
    {
      FLOOR7_2=50
      DEM1_5=50
      DEM1_6=50
      FLOOR6_2=5
    }
  }


  -- andrewj: this is a straight copy of deimos_Hallway_hell
  flesh_Hallway_hell =
  {
    kind = "hallway"

    walls =
    {
      MARBLE1=20
      MARBLE2=20
      MARBLE3=20
      GSTONE1=20
      BROVINE=20
      COMPTILE=20
    }

    floors =
    {
      FLAT4=30
      CEIL4_1=15
      CEIl4_2=15
      CEIL5_1=30
      FLAT14=20
      FLAT5_4=20
      FLOOR3_3=30
      FLOOR4_8=40
      FLOOR5_1=25
      FLOOR5_2=10
      FLAT5=20
      FLOOR1_6=4
      FLOOR7_2=15
      FLAT5_1=15
      FLAT5_2=15
      DEM1_5=15
      DEM1_6=15
    }

    ceilings =
    {
      FLAT4=20
      CEIL4_1=15
      CEIl4_2=15
      CEIL5_1=30
      CEIL3_5=25
      CEIL3_3=20
      FLAT18=15
      FLAT19=20
      FLAT5_4=10
      FLOOR4_8=15
      FLOOR5_1=20
      FLOOR7_1=15
      FLOOR7_2=15
      FLAT5_1=15
      FLAT5_2=15
      DEM1_5=15
      DEM1_6=15
    }
  }


  flesh_Cave =
  {
    kind = "cave"

    naturals =
    {
      ROCKRED1=70
      SP_ROCK1=50
      BROWNHUG=15
      SKIN2=10
      SKINFACE=20
      SKSNAKE1=5
      SKSNAKE2=5
      FIREBLU1=10
      FIRELAVA=10
    }
  }


  flesh_Outdoors =
  {
    kind = "outdoors"

    floors =
    {
      ASHWALL=12
      FLAT1_1=15
      FLAT5_4=10
      FLAT10=20
      FLAT5_7=10
      FLAT5_8=10
      MFLR8_4=10
      FLOOR7_1=15
      SFLR6_1=8
      SFLR6_4=8
      FLAT5=7
      MFLR8_2=5
      FLAT1_1=10
      FLAT1_2=10
      MFLR8_3=10
      FLAT5_2=20
    }

    naturals =
    {
      ASHWALL=30
      GRAYVINE=20
      SP_ROCK2=15
      SP_ROCK1=70
      ROCKRED1=70
      BROWNHUG=20
      SKSNAKE1=10
      SKSNAKE2=10
    }
  }
}


-- themes specific to Doom 1 / Ultimate DOOM

OB_THEMES["deimos"] =
{
  label = "Deimos"
  priority = 6
  game = "doom1"
  name_theme = "TECH"
  mixed_prob = 30
}


OB_THEMES["flesh"] =
{
  label = "Thy Flesh"
  priority = 2
  game = "ultdoom"
  name_theme = "GOTHIC"
  mixed_prob = 20
}


