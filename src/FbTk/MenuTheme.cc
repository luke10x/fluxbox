// MenuTheme.cc for FbTk
// Copyright (c) 2002 Henrik Kinnunen (fluxgen at users.sourceforge.net)
// 
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

// $Id: MenuTheme.cc,v 1.1 2002/12/25 11:42:05 fluxgen Exp $

#include "MenuTheme.hh"

#include "Color.hh"
#include "Texture.hh"
#include "Font.hh"
#include "App.hh"
//TODO change this
#include "../StringUtil.hh"

namespace FbTk {

MenuTheme::MenuTheme(int screen_num):
    FbTk::Theme(screen_num), 
    t_text(*this, "menu.title.textColor", "Menu.Title.TextColor"),
    f_text(*this, "menu.frame.textColor", "Menu.Frame.TextColor"),
    h_text(*this, "menu.hilite.textColor", "Menu.Hilite.TextColor"),
    d_text(*this, "menu.frame.disableColor", "Menu.Frame.DisableColor"),
    title(*this, "menu.title", "Menu.Title"),
    frame(*this, "menu.frame", "Menu.Frame"),
    hilite(*this, "menu.hilite", "Menu.Hilite"),
    titlefont(*this, "menu.title.font", "Menu.Title.Font"),
    framefont(*this, "menu.frame.font", "Menu.Frame.Font"),
    framefont_justify(*this, "menu.frame.justify", "Menu.Frame.Justify"),
    titlefont_justify(*this, "menu.title.justify", "Menu.Title.Justify"),
    bullet_pos(*this, "menu.bulletPos", "Menu.BulletPos"),
    m_bullet(*this, "menu.bullet", "Menu.Bullet"),
    m_display(FbTk::App::instance()->display()) { 
	
    Window rootwindow = RootWindow(m_display, screen_num);

    XGCValues gcv;
    unsigned long gc_value_mask = GCForeground;
    gcv.foreground = t_text->pixel();

    t_text_gc = XCreateGC(m_display, rootwindow, gc_value_mask, &gcv);

    gcv.foreground = f_text->pixel();

    f_text_gc = XCreateGC(m_display, rootwindow, gc_value_mask, &gcv);

    gcv.foreground = h_text->pixel();
    h_text_gc =	XCreateGC(m_display, rootwindow, gc_value_mask, &gcv);

    gcv.foreground = d_text->pixel();
    d_text_gc =	XCreateGC(m_display, rootwindow, gc_value_mask, &gcv);

    gcv.foreground = hilite->color().pixel();
    hilite_gc =	XCreateGC(m_display, rootwindow, gc_value_mask, &gcv);
}

MenuTheme::~MenuTheme() {
    XFreeGC(m_display, t_text_gc);
    XFreeGC(m_display, f_text_gc);
    XFreeGC(m_display, h_text_gc);
    XFreeGC(m_display, d_text_gc);
    XFreeGC(m_display, hilite_gc);
}

void MenuTheme::reconfigTheme() {
	
    XGCValues gcv;
    unsigned long gc_value_mask = GCForeground;
	
    gcv.foreground = t_text->pixel();
	
    XChangeGC(m_display, t_text_gc,
              gc_value_mask, &gcv);

    gcv.foreground = f_text->pixel();	
	
    XChangeGC(m_display, f_text_gc,
              gc_value_mask, &gcv);

    gcv.foreground = h_text->pixel();
    XChangeGC(m_display, h_text_gc,
              gc_value_mask, &gcv);

    gcv.foreground = d_text->pixel();
    XChangeGC(m_display, d_text_gc,
              gc_value_mask, &gcv);

    gcv.foreground = hilite->color().pixel();
    XChangeGC(m_display, hilite_gc,
              gc_value_mask, &gcv);

}


template <>
void ThemeItem<MenuTheme::BulletType>::setDefaultValue() {
    m_value = MenuTheme::EMPTY;
}

template <>
void ThemeItem<MenuTheme::BulletType>::setFromString(const char *str) {
    // do nothing
    if (StringUtil::strcasestr(str, "EMPTY") == 0)
        m_value = MenuTheme::EMPTY;
    else if (StringUtil::strcasestr(str, "SQUARE") == 0)
        m_value = MenuTheme::SQUARE;
    else if (StringUtil::strcasestr(str, "TRIANGLE") == 0)
        m_value = MenuTheme::TRIANGLE;
    else
        setDefaultValue();
}

template <>
void ThemeItem<MenuTheme::BulletType>::load() {
    // do nothing, we don't have anything extra to load
}

}; // end namespace  FbTk
