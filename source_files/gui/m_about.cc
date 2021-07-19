//------------------------------------------------------------------------
//  About Window
//------------------------------------------------------------------------
//
//  Oblige Level Maker
//
//  Copyright (C) 2006-2017 Andrew Apted
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//------------------------------------------------------------------------

#include "hdr_fltk.h"
#include "hdr_ui.h"
#include "headers.h"
#include "lib_util.h"
#include "main.h"

class UI_About : public Fl_Window {
   public:
    bool want_quit;

   public:
    UI_About(int W, int H, const char *label = NULL);

    virtual ~UI_About() {
        // nothing needed
    }

    bool WantQuit() const { return want_quit; }

   public:
    // FLTK virtual method for handling input events.
    int handle(int event) {
        if (event == FL_KEYDOWN || event == FL_SHORTCUT) {
            int key = Fl::event_key();

            if (key == FL_Escape) {
                want_quit = true;
                return 1;
            }

            // eat all other function keys
            if (FL_F + 1 <= key && key <= FL_F + 12) {
                return 1;
            }
        }

        return Fl_Window::handle(event);
    }

   private:
    static void callback_Quit(Fl_Widget *w, void *data) {
        UI_About *that = (UI_About *)data;

        that->want_quit = true;
    }

    static const char *Text;
    static const char *URL;
};

const char *UI_About::Text =
    N_("OBSIDIAN is a random level generator\n"
       "for classic FPS games like DOOM.\n"
       "It is a continuation of the OBLIGE Level Maker\n"
       "Copyright (C) 2006-2017 Andrew Apted, et al.\n"
       "This program is free software, and may be\n"
       "distributed and modified under the terms of\n"
       "the GNU General Public License.\n"
       "There is ABSOLUTELY NO WARRANTY!\n"
       "Use at your OWN RISK!");

const char *UI_About::URL = OBSIDIAN_WEBSITE;

//
// Constructor
//
UI_About::UI_About(int W, int H, const char *label)
    : Fl_Window(W, H, label), want_quit(false) {
    // non-resizable
    size_range(W, H, W, H);

    callback(callback_Quit, this);

    int cy = kf_h(6);

    // nice big logo text
    const char *logo_text =
        util::StringPrintf("%s %s", _(OBSIDIAN_TITLE), OBSIDIAN_VERSION);

    Fl_Box *box = new Fl_Box(0, cy, W, kf_h(50), logo_text);
    box->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_WRAP | FL_ALIGN_CLIP);
    box->labelsize(FL_NORMAL_SIZE * 5 / 3);
    box->labelfont(font_style);

    cy += box->h() + kf_h(6);

    // the very informative text
    int pad = kf_w(22);

    int text_h = H * 0.55;

    box = new Fl_Box(pad, cy, W - pad - pad, text_h, _(Text));
    box->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_CLIP);
    box->box(FL_UP_BOX);
    box->color(BUTTON_COLOR);
    box->labelfont(font_style);
    box->labelcolor(FONT2_COLOR);
    

    cy += box->h() + kf_h(10);

    // website address
    pad = kf_w(8);

    UI_HyperLink *link =
        new UI_HyperLink(pad, cy, W - pad * 2, kf_h(30), URL, URL);
    link->align(FL_ALIGN_CENTER);
    link->labelsize(FL_NORMAL_SIZE);
    link->labelfont(font_style);

    cy += link->h() + kf_h(16);

    SYS_ASSERT(cy < H);

    // finally add an "OK" button
    Fl_Group *darkish = new Fl_Group(0, cy, W, H - cy);
    darkish->box(FL_FLAT_BOX);
    {
        int bw = kf_w(60);
        int bh = kf_h(30);
        int by = H - (H - cy + bh) / 2;

        Fl_Button *button = new Fl_Button(W - bw * 2, by, bw, bh, fl_ok);
        button->box(button_style);
        button->visible_focus(0);
        button->color(BUTTON_COLOR);
        button->callback(callback_Quit, this);
        button->labelfont(font_style);
        button->labelcolor(FONT2_COLOR);
    }
    darkish->end();

    end();
}

void DLG_AboutText(void) {

    int about_w = kf_w(400);
    int about_h = kf_h(400) + KF * 20;

    UI_About *about_window = new UI_About(about_w, about_h, _("About OBSIDIAN"));

    about_window->want_quit = false;
    about_window->set_modal();
    about_window->show();

    // run the GUI until the user closes
    while (!about_window->WantQuit()) {
        Fl::wait();
    }

    delete about_window;
}

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
