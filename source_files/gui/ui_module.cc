//------------------------------------------------------------------------
//  Custom Module list
//------------------------------------------------------------------------
//
//  Oblige Level Maker
//
//  Copyright (C) 2006-2016 Andrew Apted
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
#include "hdr_lua.h"
#include "hdr_ui.h"
#include "headers.h"
#include "lib_util.h"
#include "m_lua.h"
#include "main.h"
#include <string>
#include <iostream>

UI_Module::UI_Module(int X, int Y, int W, int H, const char *id,
                     const char *label, const char *tip, int red, int green, int blue)
    : Fl_Group(X, Y, W, H), id_name(id), choice_map(), cur_opt_y(0) {       
       
    box(box_style);
    
    if ((red >= 0) && (green >= 0) && (blue >= 0)) {
        color(fl_rgb_color(red, green, blue));
    }

    mod_button =
        new UI_CustomCheckBox(X + kf_w(6), Y + kf_h(4), W - kf_w(12), kf_h(24));
    mod_button->visible_focus(0);
    mod_button->down_box(button_style);
    mod_button->selection_color(SELECTION);

    if (Is_UI()) {
        mod_button->value(1);
        mod_button->hide();
    }

    int tx = Is_UI() ? 8 : 28;

    heading = new Fl_Box(FL_NO_BOX, X + kf_w(tx), Y + kf_h(4),
                                 W - kf_w(tx + 4), kf_h(24), label);
    heading->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    heading->labelfont(use_system_fonts ? font_style : font_style | FL_BOLD);

    if (Is_UI()) {
        heading->labelsize(header_font_size);
    }

    if (tip) {
        mod_button->tooltip(tip);
        heading->tooltip(tip);
    }

    cur_opt_y += kf_h(32);

    end();

    resizable(NULL);

    hide();
}

UI_Module::~UI_Module() {}

bool UI_Module::Is_UI() const {
    return (id_name[0] == 'u' && id_name[1] == 'i' && id_name[2] == '_');
}

typedef struct {
    UI_RChoice *mod;
    const char *opt_name;
} opt_change_callback_data_t;

void UI_Module::AddOption(const char *opt, const char *label, const char *tip,
                          const char *longtip, int gap) {
    int nw = this->parent()->w();
    //	int nh = kf_h(30);

    int nx = x() + kf_w(6);
    int ny = y() + cur_opt_y - kf_h(15);

    // make label with ': ' suffixed
    int len = strlen(label);
    char *new_label = util::StringNew(len + 4);
    strcpy(new_label, label);
    strcat(new_label, ": ");

    if (!tip) {
        tip = "";
    }
    
    if (!longtip) {
    	longtip = "Detailed help not yet written for this setting. For quick help, hover over the option name to display a tooltip.";
    }

	UI_RChoice *rch =
		    new UI_RChoice(nx, ny + kf_h(15), nw * .95, (!single_pane ? kf_h(48) : kf_h(24)), NULL);

	rch->mod_label = 
			new Fl_Box(rch->x(), rch->y(), (!single_pane ? rch->w() * .95 : rch->w() * .40), kf_h(24), new_label);
	rch->mod_label->align((!single_pane ? (FL_ALIGN_LEFT | FL_ALIGN_INSIDE) : (FL_ALIGN_LEFT | FL_ALIGN_INSIDE | FL_ALIGN_CLIP)));
	rch->mod_label->labelfont(font_style);
	rch->mod_label->tooltip(tip);

	rch->mod_menu = 
		new UI_RChoiceMenu((!single_pane ? rch->x() : rch->x() + (rch->w() * .40)), (!single_pane ? rch->y() + rch->mod_label->h() : rch->y()), (single_pane ? rch->w() * .55 : rch->w()), kf_h(24), NULL);
	rch->mod_menu->textcolor(FONT2_COLOR);
	rch->mod_menu->selection_color(SELECTION);	

	rch->mod_help =
			new UI_HelpLink(rch->x() + (!single_pane ? (rch->w() * .9) : (rch->w() * .95)), rch->y(), rch->w() * .075, kf_h(24), "?");
	rch->mod_help->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER);
	rch->mod_help->labelfont(font_style);
	rch->mod_help->labelcolor(FONT_COLOR);
	rch->mod_help->help_text = longtip;
	rch->mod_help->help_title = label;
	rch->mod_help->callback(callback_ShowHelp, NULL);

    opt_change_callback_data_t *cb_data = new opt_change_callback_data_t;
    cb_data->mod = rch;
    cb_data->opt_name = util::StringDup(opt);

    rch->mod_menu->callback(callback_OptChange, cb_data);

    if (!mod_button->value()) {
        rch->hide();
    }

    add(rch);

    cur_opt_y += (!single_pane ? (gap ? kf_h(64) : kf_h(50)) : (gap ? kf_h(59) : kf_h(45)));

    resize(x(), y(), w(), CalcHeight());
    redraw();

    choice_map[opt] = rch;
}

void UI_Module::AddSliderOption(const char *opt, const char *label, const char *tip,
                          const char *longtip, int gap, double min, double max, double inc,
                          const char *units, const char *presets, const char *nan) {
    int nw = this->parent()->w();
    //	int nh = kf_h(30);

    int nx = x() + kf_w(6);
    int ny = y() + cur_opt_y - kf_h(15);

    // make label with ': ' suffixed
    int len = strlen(label);
    char *new_label = util::StringNew(len + 4);
    strcpy(new_label, label);
    strcat(new_label, ": ");

    if (!tip) {
        tip = "";
    }
    
    if (!longtip) {
    	longtip = "Detailed help not yet written for this setting. For quick help, hover over the option name to display a tooltip.";
    }
    
	UI_RSlide *rsl =
		    new UI_RSlide(nx, ny + kf_h(15), nw * .95, (!single_pane ? kf_h(48) : kf_h(24)), NULL);

    // Populate the nan_options vector
	std::string temp_string = nan;
	std::string::size_type oldpos = 0;
	std::string::size_type pos = 0;
	while (pos != std::string::npos) {
		pos = temp_string.find(',', oldpos);
		if (pos != std::string::npos) {
			std::string nan_string = temp_string.substr(oldpos, pos-oldpos);			
			rsl->nan_choices.push_back(nan_string);
			oldpos = pos + 1;		
		}
	}

	rsl->mod_label = 
			new Fl_Box(rsl->x(), rsl->y(), (!single_pane ? rsl->w() * (rsl->nan_choices.size() > 0 ? .7 : .8) : rsl->w() * .40), kf_h(24), new_label);
	rsl->mod_label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE | FL_ALIGN_CLIP);
	rsl->mod_label->labelfont(font_style);
	rsl->mod_label->tooltip(tip);

    rsl->prev_button =
        new UI_CustomArrowButton((!single_pane ? rsl->x() : rsl->x() + (rsl->w() * .40)), (!single_pane ? rsl->y() + rsl->mod_label->h() : rsl->y()), (single_pane ? rsl->w() * .05 : rsl->w() * .10), kf_h(24), "@<");
    rsl->prev_button->visible_focus(0);
    rsl->prev_button->box(button_style);
    rsl->prev_button->color(BUTTON_COLOR);     
    rsl->prev_button->align(FL_ALIGN_INSIDE);   
    rsl->prev_button->labelcolor(SELECTION);
    rsl->prev_button->labelsize(rsl->prev_button->labelsize() * .80);
    rsl->prev_button->callback(callback_SliderPrevious, NULL);
    
    rsl->mod_slider =
        new Fl_Hor_Slider((!single_pane ? rsl->x() + rsl->w() * .10 : rsl->x() + rsl->w() * .45),  (!single_pane ? rsl->y() + rsl->mod_label->h() : rsl->y()), (!single_pane ? rsl->w() * .80 : rsl->w() * (rsl->nan_choices.size() > 0 ? .35 : .40)), kf_h(24), NULL);
    rsl->mod_slider->box(button_style);
    rsl->mod_slider->visible_focus(0);
    rsl->mod_slider->color(BUTTON_COLOR);
    rsl->mod_slider->selection_color(SELECTION);
    rsl->mod_slider->minimum(min);
    rsl->mod_slider->maximum(max);
    rsl->mod_slider->step(inc);
    rsl->mod_slider->callback(callback_PresetCheck, NULL);
    
    rsl->next_button =
        new UI_CustomArrowButton((!single_pane ? rsl->x() + rsl->w() * .90 : rsl->x() + rsl->w() * (rsl->nan_choices.size() > 0 ? .80 : .85)),  (!single_pane ? rsl->y() + rsl->mod_label->h() : rsl->y()), (single_pane ? rsl->w() * .05 : rsl->w() * .10), kf_h(24), "@>");
    rsl->next_button->box(button_style);
    rsl->next_button->color(BUTTON_COLOR);
    rsl->next_button->visible_focus(0);   
    rsl->next_button->align(FL_ALIGN_INSIDE);  
    rsl->next_button->labelcolor(SELECTION);
    rsl->next_button->labelsize(rsl->next_button->labelsize() * .80);
    rsl->next_button->callback(callback_SliderNext, NULL);

   
    if (rsl->nan_choices.size() > 0) {
        rsl->nan_options =
                new UI_CustomMenuButton(rsl->x() + (!single_pane ? (rsl->w() * .7) : (rsl->w() * .85)), rsl->y(), rsl->w() * .075, kf_h(24), "@2>");
        rsl->nan_options->box(FL_FLAT_BOX);
        rsl->nan_options->color(this->color());
        rsl->nan_options->selection_color(SELECTION);
        rsl->nan_options->add("Use Slider Value");
        for (int x = 0; x < rsl->nan_choices.size(); x++) {
        	rsl->nan_options->add(rsl->nan_choices[x].c_str());
        }
        rsl->nan_options->callback(callback_NanOptions, NULL);
    }
    
	rsl->mod_entry =
			new UI_ManualEntry(rsl->x() + (!single_pane ? (rsl->w() * .8) : (rsl->w() * .90)), rsl->y(), rsl->w() * .075, kf_h(24), "[ ]");
	rsl->mod_entry->box(FL_NO_BOX);
	rsl->mod_entry->labelcolor(FONT_COLOR);
	rsl->mod_entry->visible_focus(0);
	rsl->mod_entry->callback(callback_ManualEntry, NULL);

	rsl->mod_help =
			new UI_HelpLink(rsl->x() + (!single_pane ? (rsl->w() * .9) : (rsl->w() * .95)), rsl->y(), rsl->w() * .075, kf_h(24), "?");
	rsl->mod_help->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER);
	rsl->mod_help->labelfont(font_style);
	rsl->mod_help->labelcolor(FONT_COLOR);
	rsl->mod_help->help_text = longtip;
	rsl->mod_help->help_title = label;
	rsl->mod_help->callback(callback_ShowHelp, NULL);
	
    rsl->original_label = new_label;
    rsl->units = units;

   
    // Populate the preset_choices map
	temp_string = presets;
	oldpos = 0;
	pos = 0;
	std::setlocale(LC_NUMERIC, "C");
	while (pos != std::string::npos) {
		pos = temp_string.find(',', oldpos);
		if (pos != std::string::npos) {
			std::string map_string = temp_string.substr(oldpos, pos-oldpos);
			std::string::size_type temp_pos = map_string.find(':');
			double key;
			try {
				key = std::stod(map_string.substr(0, temp_pos));
				std::string value = map_string.substr(temp_pos + 1);			
				rsl->preset_choices[key] = value;
			} catch (std::invalid_argument &e) {
				fl_message("Invalid argument for preset slider value!");
				goto skippreset;
			} catch (std::out_of_range &e) {
				fl_message("Number out of range for preset slider value!");
				goto skippreset;
			} catch (std::exception &e) {
					std::cout << e.what();
			}
			skippreset:
			oldpos = pos + 1;		
		}
	}
	std::setlocale(LC_NUMERIC, numeric_locale);
	
    if (!mod_button->value()) {
        rsl->hide();
    }

    add(rsl);

    cur_opt_y += (!single_pane ? (gap ? kf_h(64) : kf_h(50)) : (gap ? kf_h(59) : kf_h(45)));

    resize(x(), y(), w(), CalcHeight());
    redraw();
    
    choice_map_slider[opt] = rsl;
}

void UI_Module::AddButtonOption(const char *opt, const char *label, const char *tip,
                          const char* longtip, int gap) {
    int nw = this->parent()->w();
    //	int nh = kf_h(30);

    int nx = x() + kf_w(6);
    int ny = y() + cur_opt_y - kf_h(15);
    int len = strlen(label);
    char *new_label = util::StringNew(len + 4);
    strcpy(new_label, label);
    if (single_pane) {
    	strcat(new_label, ": ");
    }
	
    if (!tip) {
        tip = "";
    }
    
    if (!longtip) {
    	longtip = "Detailed help not yet written for this setting. For quick help, hover over the option name to display a tooltip.";
    }

	UI_RButton *rbt =
		    new UI_RButton(nx, ny + kf_h(15), nw * .95, kf_h(24), NULL);
	
	
	rbt->mod_label = 
			new Fl_Box(rbt->x() + (single_pane ? 0 : (rbt->w() * .075)), rbt->y(), rbt->w() * .30, kf_h(24), new_label);
	rbt->mod_label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
	rbt->mod_label->labelfont(font_style);
	rbt->mod_label->tooltip(tip);
	
	rbt->mod_check = 
			new UI_CustomCheckBox(rbt->x() + (!single_pane ? 0 : (rbt->w() * .40)), rbt->y(), rbt->w() * .10, kf_h(24), NULL);
	rbt->mod_check->selection_color(SELECTION);
	
	rbt->mod_help =
			new UI_HelpLink(rbt->x() + (!single_pane ? (rbt->w() * .9) : (rbt->w() * .95)), rbt->y(), rbt->w() * .075, kf_h(24), "?");
	rbt->mod_help->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER);
	rbt->mod_help->labelfont(font_style);
	rbt->mod_help->labelcolor(FONT_COLOR);
	rbt->mod_help->help_text = longtip;
	rbt->mod_help->help_title = label;
	rbt->mod_help->callback(callback_ShowHelp, NULL);

    if (!mod_button->value()) {
        rbt->hide();
    }

    add(rbt);

    cur_opt_y += gap ? kf_h(45) : kf_h(30);

    resize(x(), y(), w(), CalcHeight());
    redraw();
    
    choice_map_button[opt] = rbt;
}

int UI_Module::CalcHeight() const {
    if (mod_button->value()) {
        return cur_opt_y + kf_h(6);
    } else {
        return kf_h(34);
    }
}

void UI_Module::update_Enable() {
    std::map<std::string, UI_RChoice *>::const_iterator IT;
    std::map<std::string, UI_RSlide *>::const_iterator IT2;
    std::map<std::string, UI_RButton *>::const_iterator IT3;

    for (IT = choice_map.begin(); IT != choice_map.end(); IT++) {
        UI_RChoice *M = IT->second;

        if (mod_button->value()) {
            M->show();
        } else {
            M->hide();
        }
    }
    
    for (IT2 = choice_map_slider.begin(); IT2 != choice_map_slider.end(); IT2++) {
        UI_RSlide *M = IT2->second;

        if (mod_button->value()) {
            M->show();
        } else {
            M->hide();
        }
    }
    
    for (IT3 = choice_map_button.begin(); IT3 != choice_map_button.end(); IT3++) {
        UI_RButton *M = IT3->second;
        if (mod_button->value()) {
            M->show();
        } else {
            M->hide();
        }
    }
}

void UI_Module::AddOptionChoice(const char *option, const char *id,
                                const char *label) {
    UI_RChoice *rch = FindOpt(option);

    if (!rch) {
        LogPrintf("Warning: module '%s' lacks option '%s' (for choice '%s')\n",
                  id_name.c_str(), option, id);
        return;
    }

    rch->mod_menu->AddChoice(id, label);
    rch->mod_menu->EnableChoice(id, 1);
}

bool UI_Module::SetOption(const char *option, const char *value) {
    UI_RChoice *rch = FindOpt(option);

    if (!rch) {
        return false;
    }

    rch->mod_menu->ChangeTo(value);

    return true;
}

bool UI_Module::SetSliderOption(const char *option, const char *value) {
    UI_RSlide *rsl = FindSliderOpt(option);

    if (!rsl) {
        return false;
    }
	std::string string_value = value;
	double double_value;
    try {
        double_value = std::stod(string_value);
        rsl->mod_slider->value(double_value);
		rsl->mod_slider->do_callback();
		if (rsl->nan_choices.size() > 0) {
			rsl->nan_options->value(0);
			rsl->nan_options->do_callback();
		}
    } catch (std::invalid_argument &e) {
    	// If it is a nan value instead
        rsl->nan_options->value(rsl->nan_options->find_index(value));
        rsl->nan_options->do_callback();
    } catch (std::out_of_range &e) {
    	// This shouldn't happen
        std::cout << e.what();
    } catch (std::exception &e) {
    	// This shouldn't happen either
        std::cout << e.what();
    }
    return true;
}

bool UI_Module::SetButtonOption(const char *option, int value) {
    UI_RButton *rbt = FindButtonOpt(option);

    if (!rbt) {
        return false;
    }

    rbt->mod_check->value(value);
	return true;
}

UI_RChoice *UI_Module::FindOpt(const char *option) {
    if (choice_map.find(option) == choice_map.end()) {
        return NULL;
    }

    return choice_map[option];
}

UI_RSlide *UI_Module::FindSliderOpt(const char *option) {
    if (choice_map_slider.find(option) == choice_map_slider.end()) {
        return NULL;
    }

    return choice_map_slider[option];
}

UI_RButton *UI_Module::FindButtonOpt(const char *option) {
    if (choice_map_button.find(option) == choice_map_button.end()) {
        return NULL;
    }

    return choice_map_button[option];
}

void UI_Module::callback_OptChange(Fl_Widget *w, void *data) {
    UI_RChoiceMenu *rch = (UI_RChoiceMenu *)w;

    opt_change_callback_data_t *cb_data = (opt_change_callback_data_t *)data;

    SYS_ASSERT(rch);
    SYS_ASSERT(cb_data);

    UI_RChoice *M = cb_data->mod;
    
    UI_Module *parent = (UI_Module*)M->parent();

    ob_set_mod_option(parent->id_name.c_str(), cb_data->opt_name, rch->GetID());
}

void UI_Module::callback_PresetCheck(Fl_Widget *w, void *data) {
    Fl_Hor_Slider *mod_slider = (Fl_Hor_Slider *)w;

    SYS_ASSERT(mod_slider);
    
    UI_RSlide *current_slider = (UI_RSlide*)mod_slider->parent();
   
	double value = mod_slider->value();
	
	if (value == -0) {
		value = 0; // Silly, but keeps "negative zero" from being show on the label
	}

	std::string new_label = current_slider->original_label;
	
	current_slider->mod_label->copy_label(new_label.append(50, ' ').c_str()); // To prevent visual errors with labels of different lengths

	new_label = current_slider->original_label;

	// Check against the preset_choices map

	if (current_slider->preset_choices.count(value) == 1) {
		current_slider->mod_label->copy_label(new_label.append(current_slider->preset_choices[value].c_str()).c_str());
	} else {
		char value_string[20];
		sprintf(value_string, "%g", value);
		current_slider->mod_label->copy_label(new_label.append((const char*)value_string).append(current_slider->units).c_str());
	}
}

void UI_Module::callback_SliderPrevious(Fl_Widget *w, void *data) {
    Fl_Button *prev_button = (Fl_Button *)w;

    SYS_ASSERT(prev_button);
    
    UI_RSlide *current_slider = (UI_RSlide*)prev_button->parent();
   
	double value = current_slider->mod_slider->value();
	
	if (current_slider->preset_choices.empty()) {
		int steps = (int)((current_slider->mod_slider->maximum() / current_slider->mod_slider->step()) * .10);
        if (steps < current_slider->mod_slider->step()) {
            steps = current_slider->mod_slider->step();
        }  
		double temp_value = current_slider->mod_slider->increment(value, -steps);
		if (temp_value < current_slider->mod_slider->minimum()) {
			current_slider->mod_slider->value(current_slider->mod_slider->minimum());
			current_slider->mod_slider->do_callback();
		} else {
			current_slider->mod_slider->value(temp_value);
			current_slider->mod_slider->do_callback();		
		}
	} else {
		int match = 0;	
		do {
			double temp_value = current_slider->mod_slider->increment(value, -1);
			if (temp_value >= current_slider->mod_slider->minimum()) {
				value = temp_value;
			} else {
				break;
			}
			match = current_slider->preset_choices.count(value);
		} while (match == 0);
		
		if (match == 1) {
			current_slider->mod_slider->value(value);
			current_slider->mod_slider->do_callback();
		}	
	}
}

void UI_Module::callback_SliderNext(Fl_Widget *w, void *data) {
    Fl_Button *next_button = (Fl_Button *)w;

    SYS_ASSERT(next_button);
    
    UI_RSlide *current_slider = (UI_RSlide*)next_button->parent();
   
	double value = current_slider->mod_slider->value();
	
	if (current_slider->preset_choices.empty()) {
		int steps = (int)((current_slider->mod_slider->maximum() / current_slider->mod_slider->step()) * .10);
        if (steps < current_slider->mod_slider->step()) {
            steps = current_slider->mod_slider->step();
        }        
		double temp_value = current_slider->mod_slider->increment(value, steps);
		if (temp_value > current_slider->mod_slider->maximum()) {
			current_slider->mod_slider->value(current_slider->mod_slider->maximum());
			current_slider->mod_slider->do_callback();
		} else {
			current_slider->mod_slider->value(temp_value);
			current_slider->mod_slider->do_callback();		
		}
	} else {
		int match = 0;	
		do {
			double temp_value = current_slider->mod_slider->increment(value, 1);
			if (temp_value <= current_slider->mod_slider->maximum()) {
				value = temp_value;
			} else {
				break;
			}
			match = current_slider->preset_choices.count(value);
		} while (match == 0);
		
		if (match == 1) {
			current_slider->mod_slider->value(value);
			current_slider->mod_slider->do_callback();
		}
	}
}

void UI_Module::callback_ShowHelp(Fl_Widget *w, void *data) {
    UI_HelpLink *mod_help = (UI_HelpLink *)w;

    SYS_ASSERT(mod_help);
    fl_cursor(FL_CURSOR_DEFAULT);
    Fl_Window *win = new Fl_Window(640, 480, mod_help->help_title);
    Fl_Text_Buffer *buff = new Fl_Text_Buffer();
    Fl_Text_Display *disp = new Fl_Text_Display(20, 20, 640-40, 480-40, NULL);
    disp->buffer(buff);
    disp->wrap_mode(Fl_Text_Display::WRAP_AT_BOUNDS, 0);
    win->resizable(*disp);
    win->hotspot(0, 0, 0);
    win->set_modal();
    win->show();
    buff->text(mod_help->help_text); 
	
}

void UI_Module::callback_ManualEntry(Fl_Widget *w, void *data) {
    UI_ManualEntry *mod_entry = (UI_ManualEntry *)w;

	UI_RSlide *current_slider = (UI_RSlide*)mod_entry->parent();

	char float_buf[1000];
	double new_value = 0;
    std::string string_value;
	
	sprintf(float_buf, "%g", current_slider->mod_slider->value());
	
	tryagain:

    const char *value_buf = fl_input(_("Enter Value:"), float_buf);

    // cancelled?
    if (!value_buf) {
        goto end;
    }
    
    string_value = value_buf;

    try {
        new_value = std::stod(string_value);
    } catch (std::invalid_argument &e) {
        fl_message("Invalid argument! Try again!");
        goto tryagain;
    } catch (std::out_of_range &e) {
        fl_message("Number out of range! Try again!");
        goto tryagain;
    } catch (std::exception &e) {
        std::cout << e.what();
    }
    
    current_slider->mod_slider->value(current_slider->mod_slider->clamp(current_slider->mod_slider->round(new_value)));
    current_slider->mod_slider->do_callback();
    
    end: ;
	
}

void UI_Module::callback_NanOptions(Fl_Widget *w, void *data) {
    UI_CustomMenuButton *nan_options = (UI_CustomMenuButton *)w;
    UI_RSlide *current_slider = (UI_RSlide*)nan_options->parent();
    
    int temp_value = nan_options->value();
    
    if (temp_value > 0) {
    	std::string new_label = current_slider->original_label;
		current_slider->mod_label->copy_label(new_label.append(50, ' ').c_str()); // To prevent visual errors with labels of different lengths
		new_label = current_slider->original_label;
    	current_slider->mod_label->copy_label(new_label.append(nan_options->text(temp_value)).c_str());
    	current_slider->prev_button->deactivate();
    	current_slider->mod_slider->deactivate();
    	current_slider->next_button->deactivate();
    	current_slider->mod_entry->deactivate();
    } else {
    	current_slider->prev_button->activate();
    	current_slider->mod_slider->activate();
    	current_slider->next_button->activate();
    	current_slider->mod_entry->activate();
    	current_slider->mod_slider->do_callback();
    }
}

//----------------------------------------------------------------

UI_CustomMods::UI_CustomMods(int X, int Y, int W, int H)
    : Fl_Group(X, Y, W, H) {
    box(FL_FLAT_BOX);

    color(GAP_COLOR, GAP_COLOR);

    int cy = Y;

    // area for module list
    mx = X;
    my = cy;
    mw = W - Fl::scrollbar_size();
    mh = Y + H - cy;

    offset_y = 0;
    total_h = 0;

    sbar = new Fl_Scrollbar(mx + mw, my, Fl::scrollbar_size(), mh);
    sbar->callback(callback_Scroll, this);
    sbar->slider(button_style);
    sbar->color(GAP_COLOR, BUTTON_COLOR);
    sbar->labelcolor(SELECTION);

    mod_pack_group = new Fl_Group(mx, my, mw, mh);
    mod_pack_group->box(FL_NO_BOX);

    mod_pack = new Fl_Group(mx, my, mw, mh);
    mod_pack->clip_children(1);
    mod_pack->end();

    mod_pack->align(FL_ALIGN_INSIDE | FL_ALIGN_BOTTOM);
    mod_pack->labeltype(FL_NORMAL_LABEL);
    mod_pack->labelsize(FL_NORMAL_SIZE * 3 / 2);

    mod_pack->box(FL_FLAT_BOX);
    mod_pack->color(GAP_COLOR);
    mod_pack->resizable(mod_pack);

    end();

    resizable(mod_pack_group);

    end();
}

UI_CustomMods::~UI_CustomMods() {}

typedef struct {
    UI_Module *mod;
    UI_CustomMods *parent;
} mod_enable_callback_data_t;

void UI_CustomMods::AddModule(const char *id, const char *label,
                              const char *tip, int red, int green, int blue) {
    UI_Module *M = new UI_Module(mx, my, mw - 4, kf_h(34), id, label, tip, red, green, blue);

    mod_enable_callback_data_t *cb_data = new mod_enable_callback_data_t;
    cb_data->mod = M;
    cb_data->parent = this;

    if (!M->Is_UI()) {
        M->mod_button->callback(callback_ModEnable, cb_data);
    }

    mod_pack->add(M);

    PositionAll();
}

bool UI_CustomMods::AddOption(const char *module, const char *option,
                              const char *label, const char *tip, const char* longtip, int gap) {
    UI_Module *M = FindID(module);

    if (!M) {
        return false;
    }

    M->AddOption(option, label, tip, longtip, gap);

    PositionAll();

    return true;
}

bool UI_CustomMods::AddSliderOption(const char *module, const char *option,
                              const char *label, const char *tip, const char* longtip, int gap, double min, 
                              double max, double inc, const char *units, const char *presets, const char *nan) {
    UI_Module *M = FindID(module);

    if (!M) {
        return false;
    }

    M->AddSliderOption(option, label, tip, longtip, gap, min, max, inc, units, presets, nan);

    PositionAll();

    return true;
}

bool UI_CustomMods::AddButtonOption(const char *module, const char *option,
                              const char *label, const char *tip, const char* longtip, int gap) {
    UI_Module *M = FindID(module);

    if (!M) {
        return false;
    }

    M->AddButtonOption(option, label, tip, longtip, gap);

    PositionAll();

    return true;
}

void UI_CustomMods::AddOptionChoice(const char *module, const char *option,
                                    const char *id, const char *label) {
    UI_Module *M = FindID(module);

    if (!M) {
        return;
    }

    M->AddOptionChoice(option, id, label);
}

bool UI_CustomMods::ShowModule(const char *id, bool new_shown) {
    SYS_ASSERT(id);

    UI_Module *M = FindID(id);

    if (!M) {
        return false;
    }

    if ((M->visible() ? 1 : 0) == (new_shown ? 1 : 0)) {
        return true;
    }

    // visibility definitely changed

    if (new_shown) {
        M->show();
    } else {
        M->hide();
    }

    PositionAll();

    return true;
}

bool UI_CustomMods::SetOption(const char *module, const char *option,
                              const char *value) {
    UI_Module *M = FindID(module);

    if (!M) {
        return false;
    }

    return M->SetOption(option, value);
}

bool UI_CustomMods::SetSliderOption(const char *module, const char *option, const char *value) {
    UI_Module *M = FindID(module);

    if (!M) {
        return false;
    }

    return M->SetSliderOption(option, value);
}

bool UI_CustomMods::SetButtonOption(const char *module, const char *option, int value) {
    UI_Module *M = FindID(module);

    if (!M) {
        return false;
    }

    return M->SetButtonOption(option, value);
}

bool UI_CustomMods::EnableMod(const char *id, bool enable) {
    SYS_ASSERT(id);

    UI_Module *M = FindID(id);

    if (!M) {
        return false;
    }

    if ((M->mod_button->value() ? 1 : 0) == (enable ? 1 : 0)) {
        return true;  // no change
    }

    M->mod_button->value(enable ? 1 : 0);
    M->update_Enable();

    // no options => no height change => no need to reposition
    if (M->choice_map.size() > 0 || M->choice_map_slider.size() > 0 || M->choice_map_button.size() > 0) {
        PositionAll();
    }

    return true;
}

void UI_CustomMods::PositionAll(UI_Module *focus) {
    // determine focus [closest to top without going past it]
    if (!focus) {
        int best_dist = 9999;

        for (int j = 0; j < mod_pack->children(); j++) {
            UI_Module *M = (UI_Module *)mod_pack->child(j);
            SYS_ASSERT(M);

            if (!M->visible() || M->y() < my || M->y() >= my + mh) {
                continue;
            }

            int dist = M->y() - my;

            if (dist < best_dist) {
                focus = M;
                best_dist = dist;
            }
        }
    }

    // calculate new total height
    int new_height = 0;
    int spacing = 4;

    for (int k = 0; k < mod_pack->children(); k++) {
        UI_Module *M = (UI_Module *)mod_pack->child(k);
        SYS_ASSERT(M);

        if (M->visible()) {
            new_height += M->CalcHeight() + spacing;
        }
    }

    // determine new offset_y
    if (new_height <= mh) {
        offset_y = 0;
    } else if (focus) {
        int focus_oy = focus->y() - my;

        int above_h = 0;
        for (int k = 0; k < mod_pack->children(); k++) {
            UI_Module *M = (UI_Module *)mod_pack->child(k);
            if (M->visible() && M->y() < focus->y()) {
                above_h += M->CalcHeight() + spacing;
            }
        }

        offset_y = above_h - focus_oy;

        offset_y = MAX(offset_y, 0);
        offset_y = MIN(offset_y, new_height - mh);
    } else {
        // when not shrinking, offset_y will remain valid
        if (new_height < total_h) {
            offset_y = 0;
        }
    }

    total_h = new_height;

    SYS_ASSERT(offset_y >= 0);
    SYS_ASSERT(offset_y <= total_h);

    // reposition all the modules
    int ny = my - offset_y;

    for (int j = 0; j < mod_pack->children(); j++) {
        UI_Module *M = (UI_Module *)mod_pack->child(j);
        SYS_ASSERT(M);

        int nh = M->visible() ? M->CalcHeight() : 1;

        if (ny != M->y() || nh != M->h()) {
            M->resize(M->x(), ny, M->w(), nh);
        }

        if (M->visible()) {
            ny += M->CalcHeight() + spacing;
        }
    }

    // p = position, first line displayed
    // w = window, number of lines displayed
    // t = top, number of first line
    // l = length, total number of lines
    sbar->value(offset_y, mh, 0, total_h);

    mod_pack->redraw();
}

// Normal FLTK resize except it will resize the module options as well
void UI_Module::resize(int X, int Y, int W, int H) {
    int dx = X - x();
    int dy = Y - y();
    int dw = W - w();
    int dh = H - h();

    int *p = sizes();  // save initial sizes and positions

    Fl_Widget::resize(X, Y, W, H);  // make new xywh values visible for children

    if (!resizable() || (dw == 0 && dh == 0)) {
        if (type() < FL_WINDOW) {
            Fl_Widget *const *a = array();
            for (int i = children(); i--;) {
                Fl_Widget *o = *a++;
                o->resize(o->x() + dx, o->y() + dy, o->w(), o->h());
            }
        }

    } else if (children()) {
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
        for (int i = children(); i--;) {
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

	if (!single_pane) {
		for (int i = 0; i < this->children(); i++) {
		    this->child(i)->resize(this->child(i)->x(), this->child(i)->y(),
		                           w() * .95, this->child(i)->h());
		    this->child(i)->redraw();
		}
	} else {
		for (int i = 0; i < this->children(); i++) {
		    this->child(i)->resize(this->child(i)->x(), this->child(i)->y(),
		                           w() * .95, this->child(i)->h());
		    this->child(i)->redraw();
		}	
	}
}

// Normal FLTK resize except it will reset the scrollbar to the top
void UI_CustomMods::resize(int X, int Y, int W, int H) {
    int dx = X - x();
    int dy = Y - y();
    int dw = W - w();
    int dh = H - h();

    int *p = sizes();  // save initial sizes and positions

    Fl_Widget::resize(X, Y, W, H);  // make new xywh values visible for children

    if (!resizable() || (dw == 0 && dh == 0)) {
        if (type() < FL_WINDOW) {
            Fl_Widget *const *a = array();
            for (int i = children(); i--;) {
                Fl_Widget *o = *a++;
                o->resize(o->x() + dx, o->y() + dy, o->w(), o->h());
            }
        }

    } else if (children()) {
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
        for (int i = children(); i--;) {
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

    // calculate new total height
    int new_height = 0;
    int spacing = 4;

    for (int k = 0; k < this->mod_pack->children(); k++) {
        UI_Module *M = (UI_Module *)mod_pack->child(k);
        SYS_ASSERT(M);

        if (M->visible()) {
            new_height += M->CalcHeight() + spacing;
        }
    }

    // determine new offset_y
    if (new_height <= mh) {
        offset_y = 0;
    }

    total_h = new_height;

    SYS_ASSERT(offset_y >= 0);
    SYS_ASSERT(offset_y <= total_h);

    // reposition all the modules
    int ny = my - offset_y;

    for (int j = 0; j < mod_pack->children(); j++) {
        UI_Module *M = (UI_Module *)mod_pack->child(j);
        SYS_ASSERT(M);

        int nh = M->visible() ? M->CalcHeight() : 1;

        if (ny != M->y() || nh != M->h()) {
            M->resize(M->x(), ny, M->w(), nh);
        }

        if (M->visible()) {
            ny += M->CalcHeight() + spacing;
        }
    }

    // p = position, first line displayed
    // w = window, number of lines displayed
    // t = top, number of first line
    // l = length, total number of lines
    this->sbar->value(offset_y, mh, 0, total_h);

    this->mod_pack->redraw();
}

void UI_CustomMods::callback_Scroll(Fl_Widget *w, void *data) {
    UI_CustomMods *that = (UI_CustomMods *)data;

    Fl_Scrollbar *sbar = (Fl_Scrollbar *)w;

    int previous_y = that->offset_y;

    that->offset_y = sbar->value();

    int dy = that->offset_y - previous_y;

    // simply reposition all the UI_Module widgets
    for (int j = 0; j < that->mod_pack->children(); j++) {
        Fl_Widget *F = that->mod_pack->child(j);
        SYS_ASSERT(F);

        F->resize(F->x(), F->y() - dy, F->w(), F->h());
    }

    that->mod_pack->redraw();
}

void UI_CustomMods::callback_ModEnable(Fl_Widget *w, void *data) {
    mod_enable_callback_data_t *cb_data = (mod_enable_callback_data_t *)data;
    SYS_ASSERT(cb_data);

    UI_Module *M = cb_data->mod;

    M->update_Enable();

    // no options => no height change => no need to reposition
    if (M->choice_map.size() > 0 || M->choice_map_slider.size() > 0 || M->choice_map_button.size() > 0) {
        cb_data->parent->PositionAll(M);
    }

    ob_set_mod_option(M->id_name.c_str(), "self",
                      M->mod_button->value() ? "true" : "false");
}

UI_Module *UI_CustomMods::FindID(const char *id) const {
    for (int j = 0; j < mod_pack->children(); j++) {
        UI_Module *M = (UI_Module *)mod_pack->child(j);
        SYS_ASSERT(M);

        if (strcmp(M->id_name.c_str(), id) == 0) {
            return M;
        }
    }

    return NULL;
}

void UI_CustomMods::Locked(bool value) {
    if (value) {
		for (int j = 0; j < mod_pack->children(); j++) {
		    UI_Module *M = (UI_Module *)mod_pack->child(j);
		    SYS_ASSERT(M);
		    M->deactivate();
		}
    } else {
		for (int j = 0; j < mod_pack->children(); j++) {
		    UI_Module *M = (UI_Module *)mod_pack->child(j);
		    SYS_ASSERT(M);
		    M->activate();
		}
    }
}

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
