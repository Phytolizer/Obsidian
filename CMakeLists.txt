cmake_minimum_required(VERSION 3.11.0)
project(obsidian VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wl,--warn-common")

include(CTest)
enable_testing()

find_package(FLTK REQUIRED)

execute_process(COMMAND fltk-config --use-images --ldflags OUTPUT_VARIABLE FLTK_LIBS)
string(REPLACE "\n" " " FLTK_LIBS ${FLTK_LIBS})
execute_process(COMMAND fltk-config --cxxflags OUTPUT_VARIABLE FLTK_FLAGS)
string(REPLACE "\n" " " FLTK_FLAGS ${FLTK_FLAGS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLTK_FLAGS}")

set(GUI_SRC
        gui/main.cc
        gui/m_about.cc
        gui/m_addons.cc
        gui/m_cookie.cc  
        gui/m_dialog.cc  
        gui/m_lua.cc     
        gui/m_manage.cc  
        gui/m_options.cc  
        gui/m_trans.cc  
        gui/lib_argv.cc  
        gui/lib_file.cc  
        gui/lib_signal.cc 
        gui/lib_util.cc  
        gui/lib_grp.cc   
        gui/lib_pak.cc   
        gui/lib_tga.cc   
        gui/lib_wad.cc   
        gui/lib_zip.cc   
        gui/sys_assert.cc 
        gui/sys_debug.cc 
        gui/img_bolt.cc  
        gui/img_pill.cc  
        gui/img_carve.cc 
        gui/img_relief.cc 
        gui/img_font1.cc  
        
        gui/csg_bsp.cc  
        gui/csg_clip.cc  
        gui/csg_main.cc  
        gui/csg_doom.cc  
        gui/csg_nukem.cc 
        gui/csg_quake.cc 
        gui/csg_shade.cc 
        gui/csg_spots.cc 
        gui/dm_extra.cc  
        gui/dm_prefab.cc 
        gui/g_doom.cc    
        gui/g_nukem.cc   
        gui/g_quake.cc   
        gui/g_quake2.cc  
        gui/g_quake3.cc  
        gui/g_wolf.cc    
        gui/q_common.cc  
        gui/q_light.cc   
        gui/q_tjuncs.cc  
        gui/q_vis.cc     
        gui/vis_buffer.cc 
        gui/vis_occlude.cc 
        
        gui/tx_forge.cc  
        gui/tx_skies.cc  
        gui/ui_build.cc  
        gui/ui_game.cc   
        gui/ui_hyper.cc  
        gui/ui_map.cc    
        gui/ui_module.cc 
        gui/ui_rchoice.cc 
        gui/ui_window.cc 
        
        gui/zf_menu.cc 
        gui/twister.cc
)

set(LUA_SRC
        lua_src/lapi.c   
        lua_src/lauxlib.c   
        lua_src/lbaselib.c   
        lua_src/lcode.c   
        lua_src/lcorolib.c   
        lua_src/lctype.c   
        lua_src/ldblib.c   
        lua_src/ldebug.c   
        lua_src/ldo.c   
        lua_src/ldump.c   
        lua_src/lfunc.c   
        lua_src/lgc.c   
        lua_src/linit.c   
        lua_src/liolib.c   
        lua_src/llex.c   
        lua_src/lmathlib.c   
        lua_src/lmem.c   
        lua_src/loadlib.c   
        lua_src/lobject.c   
        lua_src/lopcodes.c   
        lua_src/loslib.c   
        lua_src/lparser.c   
        lua_src/lstate.c   
        lua_src/lstring.c   
        lua_src/lstrlib.c   
        lua_src/ltable.c   
        lua_src/ltablib.c   
        lua_src/ltm.c   
        lua_src/lundump.c   
        lua_src/lutf8lib.c   
        lua_src/lvm.c   
        lua_src/lzio.c   
)

set(AJPOLY_SRC
        ajpoly_src/pl_map.cc
        ajpoly_src/pl_poly.cc
        ajpoly_src/pl_util.cc
        ajpoly_src/pl_wad.cc
        )

set(ZDBSP_SRC
        zdbsp_src/zdmain.cc  
        zdbsp_src/blockmapbuilder.cc 
        zdbsp_src/processor.cc     
        zdbsp_src/processor_udmf.cc     
        zdbsp_src/sc_man.cc  
        zdbsp_src/zdwad.cc 
        zdbsp_src/nodebuild.cc     
        zdbsp_src/rejectbuilder.cc  
        zdbsp_src/rejectbuilder_nogl.cc  
        zdbsp_src/vis.cc  
        zdbsp_src/visflow.cc  
        zdbsp_src/nodebuild_events.cc  
        zdbsp_src/nodebuild_extract.cc   
        zdbsp_src/nodebuild_gl.cc      
        zdbsp_src/nodebuild_utility.cc   
        zdbsp_src/nodebuild_classify_nosse2.cc   
)

set(PHYSFS_SRC
        physfs_src/physfs_byteorder.cc  
        physfs_src/physfs.cc  
        physfs_src/physfs_unicode.cc  
        physfs_src/physfs_archiver_7z.cc   
        physfs_src/physfs_archiver_grp.cc   
        physfs_src/physfs_archiver_dir.cc   
        physfs_src/physfs_archiver_qpak.cc   
        physfs_src/physfs_archiver_hog.cc   
        physfs_src/physfs_archiver_mvl.cc   
        physfs_src/physfs_archiver_wad.cc   
        physfs_src/physfs_archiver_slb.cc   
        physfs_src/physfs_archiver_iso9660.cc   
        physfs_src/physfs_archiver_unpacked.cc   
        physfs_src/physfs_archiver_vdf.cc   
        physfs_src/physfs_archiver_zip.cc   
        physfs_src/physfs_platform_unix.cc   
        physfs_src/physfs_platform_posix.cc 
)

add_executable(obsidian 
        ${LUA_SRC}
        ${ZDBSP_SRC}
        ${AJPOLY_SRC}
        ${PHYSFS_SRC}
        ${GUI_SRC}
        )

file(GLOB LANG_FILES CONFIGURE_DEPENDS
    "gui/*.cc"
    "gui/*.h"
    "scripts/*.lua"
    "engines/*.lua"
    "modules/*.lua"
    "games/*/*.lua"
)

if (UNIX)
    target_compile_definitions(obsidian PRIVATE UNIX)
endif ()

target_compile_definitions(obsidian PRIVATE LUA_ANSI LUA_USE_MKSTEMP INLINE_G=inline)
target_link_libraries(obsidian ${FLTK_LIBRARIES} m z)
target_link_directories(obsidian PRIVATE /usr/X11R6/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLTK_LIBS}")

target_include_directories(obsidian PRIVATE lua_src zdbsp_src ajpoly_src physfs_src gui lua_src acc_src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
