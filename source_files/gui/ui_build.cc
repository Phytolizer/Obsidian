//------------------------------------------------------------------------
//  Build panel
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

UI_Build::UI_Build(int X, int Y, int W, int H, const char *label)
    : Fl_Group(X, Y, W, H, label) {
    box(box_style);
    tooltip(
        "Progress and minimap display.\nMinimap Legend:\nWhite - Regular "
        "rooms\nBrown - Caves\nBlue - Outdoors\nGreen - Parks");

    status_label[0] = 0;

    int pad = kf_w(12);

    int mini_w = W * .80;
    int mini_h = mini_w;

    int cy = Y + kf_h(12);

    /* --- Status Area --- */

    mini_map = new UI_MiniMap(X + (W * .10), cy, mini_w, mini_h);

    seed_disp = new Fl_Box(X + (W * .10), cy, mini_w, mini_h);
    seed_disp->box(FL_NO_BOX);
    seed_disp->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP_LEFT | FL_ALIGN_CLIP);
    seed_disp->labelcolor(FL_WHITE);
    seed_disp->labelsize(small_font_size);
    seed_disp->labelfont(font_style);
    seed_disp->copy_label("Seed: -");

    name_disp = new Fl_Box(X + (W * .10), cy, mini_w, mini_h);
    name_disp->box(FL_NO_BOX);
    name_disp->align(FL_ALIGN_INSIDE | FL_ALIGN_BOTTOM_LEFT | FL_ALIGN_CLIP);
    name_disp->labelcolor(FL_WHITE);
    name_disp->labelfont(font_style);
    name_disp->labelsize(small_font_size);

    cy += mini_map->h() + kf_h(6);

    status = new Fl_Box(FL_FLAT_BOX, X + pad, cy, W - pad * 2, kf_h(26),
                        _("Ready to go!"));
    status->box(FL_NO_BOX);
    status->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
    status->labelfont(font_style);

    cy += status->h() + kf_h(6);

    progress = new Fl_Progress(X + pad, cy, W - pad * 2, kf_h(26));
    progress->align(FL_ALIGN_INSIDE);
    progress->box(FL_FLAT_BOX);
    progress->color(GAP_COLOR, GAP_COLOR);
    progress->value(0.0);
    progress->labelsize(header_font_size);
    progress->labelfont(font_style);

    cy = cy + progress->h() + kf_h(4);

    resizable(mini_map);

    end();
}

UI_Build::~UI_Build() {}

// Same as regular Fl_Group resize with the exception of calling the minimap to
// redraw afterwards
void UI_Build::resize(int X, int Y, int W, int H) {
    int dx = X - x();
    int dy = Y - y();
    int dw = W - w();
    int dh = H - h();

    int *p = sizes();  // save initial sizes and positions

    Fl_Widget::resize(X, Y, W, H);  // make new xywh values visible for children

    if (!resizable() || (dw == 0 && dh == 0)) {
        if (type() < FL_WINDOW) {
            Fl_Widget *const *a = array();
            for (int i = this->children(); i--;) {
                Fl_Widget *o = *a++;
                o->resize(o->x() + dx, o->y() + dy, o->w(), o->h());
            }
        }

    } else if (this->children()) {
        // get changes in size/position from the initial size:
        dx = X - p[0];
        dw = W - (p[1] - p[0]);
        dy = Y - p[2];
        dh = H - (p[3] - p[2]);
        if (type() >= FL_WINDOW) {
            dx = dy = 0;
        }
        p += 4;

        // get initial size of resizable():
        int IX = *p++;
        int IR = *p++;
        int IY = *p++;
        int IB = *p++;

        Fl_Widget *const *a = array();
        for (int i = this->children(); i--;) {
            Fl_Widget *o = *a++;
#if 1
            int XX = *p++;
            if (XX >= IR) {
                XX += dw;
            } else if (XX > IX) {
                XX = IX +
                     ((XX - IX) * (IR + dw - IX) + (IR - IX) / 2) / (IR - IX);
            }
            int R = *p++;
            if (R >= IR) {
                R += dw;
            } else if (R > IX) {
                R = IX +
                    ((R - IX) * (IR + dw - IX) + (IR - IX) / 2) / (IR - IX);
            }

            int YY = *p++;
            if (YY >= IB) {
                YY += dh;
            } else if (YY > IY) {
                YY = IY +
                     ((YY - IY) * (IB + dh - IY) + (IB - IY) / 2) / (IB - IY);
            }
            int B = *p++;
            if (B >= IB) {
                B += dh;
            } else if (B > IY) {
                B = IY +
                    ((B - IY) * (IB + dh - IY) + (IB - IY) / 2) / (IB - IY);
            }
#else  // much simpler code from Francois Ostiguy:
            int XX = *p++;
            if (XX >= IR)
                XX += dw;
            else if (XX > IX)
                XX += dw * (XX - IX) / (IR - IX);
            int R = *p++;
            if (R >= IR)
                R += dw;
            else if (R > IX)
                R = R + dw * (R - IX) / (IR - IX);

            int YY = *p++;
            if (YY >= IB)
                YY += dh;
            else if (YY > IY)
                YY = YY + dh * (YY - IY) / (IB - IY);
            int B = *p++;
            if (B >= IB)
                B += dh;
            else if (B > IY)
                B = B + dh * (B - IY) / (IB - IY);
#endif
            o->resize(XX + dx, YY + dy, R - XX, B - YY);
        }
    }
    this->mini_map->EmptyMap();
}

//----------------------------------------------------------------

void UI_Build::Prog_Init(int node_perc, const char *extra_steps) {
    level_index = 0;
    level_total = 0;

    node_begun = false;
    node_ratio = node_perc / 100.0;
    node_along = 0;

    ParseSteps(extra_steps);

    progress->minimum(0.0);
    progress->maximum(1.0);

    progress->value(0.0);
    progress->color(GAP_COLOR, SELECTION);
    progress->labelcolor(fl_contrast(FONT_COLOR, GAP_COLOR));
}

void UI_Build::Prog_Finish() {
    progress->color(GAP_COLOR, GAP_COLOR);
    progress->value(0.0);
    progress->label("");
}

void UI_Build::Prog_AtLevel(int index, int total) {
    level_index = index;
    level_total = total;

    Prog_Step(N_("Plan"));
}

void UI_Build::Prog_Step(const char *step_name) {
    int pos = FindStep(step_name);

    if (pos < 0) {
        return;
    }

    SYS_ASSERT(level_total > 0);

    float val = level_index - 1;

    val = val + pos / (float)step_names.size();

    val = (val / (float)level_total) * (1 - node_ratio);

    if (val < 0) {
        val = 0;
    }
    if (val > 1) {
        val = 1;
    }

    sprintf(prog_label, "%d%%", int(val * 100));

    progress->value(val);
    progress->label(prog_label);
    std::string newtitle = "[ ";
    newtitle.append(prog_label);
    newtitle.append(" ] ");
    newtitle.append(util::StringPrintf("%s %s", _(OBSIDIAN_TITLE), OBSIDIAN_VERSION));
    newtitle.append(" - ");
    newtitle.append(status_label);
    main_win->label(newtitle.c_str());

    AddStatusStep(_(step_name));

    Main_Ticker();
}

void UI_Build::Prog_Nodes(int pos, int limit) {
    SYS_ASSERT(limit > 0);

    if (!node_begun) {
        node_begun = true;
        progress->selection_color(SELECTION);
    }

    float val = pos / (float)limit;

    val = 1 + node_ratio * (val - 1);

    if (val < 0) {
        val = 0;
    }
    if (val > 1) {
        val = 1;
    }

    sprintf(prog_label, "%d%%", int(val * 100));

    progress->value(val);
    progress->label(prog_label);

    Main_Ticker();
}

void UI_Build::SetStatus(const char *msg) {
    int limit = (int)sizeof(status_label);

    strncpy(status_label, msg, limit);

    status_label[limit - 1] = 0;

    if (util::StringCaseCmp(status_label, "Success") == 0) {
        main_win->label(
            util::StringPrintf("%s %s", _(OBSIDIAN_TITLE), OBSIDIAN_VERSION));
    }

    status->label(status_label);
    status->redraw();
}

void UI_Build::ParseSteps(const char *names) {
    step_names.clear();

    // these three are done by Lua (no variation)
    step_names.push_back(N_("Plan"));
    step_names.push_back(N_("Rooms"));
    step_names.push_back(N_("Mons"));

    while (*names) {
        const char *comma = strchr(names, ',');

        if (!comma) {
            step_names.push_back(names);
            break;
        }

        SYS_ASSERT(comma > names);

        step_names.push_back(std::string(names, comma - names));

        names = comma + 1;
    }
}

int UI_Build::FindStep(const char *name) {
    for (int i = 0; i < (int)step_names.size(); i++) {
        if (util::StringCaseCmp(step_names[i].c_str(), name) == 0) {
            return i;
        }
    }

    return -1;  // not found
}

void UI_Build::AddStatusStep(const char *name) {
    // modifies the current status string to show the current step

    char *pos = strchr(status_label, ':');

    if (pos) {
        pos[1] = 0;
    } else {
        strcat(status_label, " :");
    }

    strcat(status_label, " ");
    strcat(status_label, name);

    status->label(status_label);
    status->redraw();
}

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
