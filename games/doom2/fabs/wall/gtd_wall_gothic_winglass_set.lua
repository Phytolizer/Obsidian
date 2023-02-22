PREFABS.Wall_gtd_winglass_wall_edge =
{
  file   = "wall/gtd_wall_gothic_winglass_set.wad",
  map    = "MAP01",

  prob   = 50,
  group  = "gtd_winglass_wall",

  where  = "edge",

  deep   = 16,

  height = 224,

  bound_z1 = 0,
  bound_z2 = 224,

  z_fit = "top",

  tex_WINGLAS1 =
  {
    WINGLAS1=50,
    WINGLAS2=50,
    WINGLAS3=50,
    WINGLAS4=50,
  },
}

PREFABS.Wall_gtd_winglass_wall_diag =
{
  template = "Wall_gtd_winglass_wall_edge",
  map    = "MAP02",

  where  = "diagonal",

  height = 224,
}
