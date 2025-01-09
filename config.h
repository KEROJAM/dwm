/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 3;/* horiz inner gap between windows */
static const unsigned int gappiv    = 2;       /* vert inner gap between windows */
static const unsigned int gappoh    = 2;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 2;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 0;       /*vertical padding of bar*/
static const int sidepad            = 0;       /*horizontal padding of bar*/
static const char *fonts[]          = { "mononoki Nerd Font:size=12" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#ECDBD6";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#000000";
static const char col_gray4[]       = "#000000";
static const char col_cyan[]        = "#ffc3a7";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeStatus] = { col_gray3, col_gray1, col_gray2 }, // Statusbar right
	[SchemeTagsSel] = { col_gray3, col_cyan, col_cyan }, // TagBar left selected
	[SchemeTagsNorm] = { col_gray3, col_gray1, col_gray2 }, // TagBar left unselected
	[SchemeInfoSel] = { col_gray3, col_gray1, col_gray2 }, // infobar middle selected
	[SchemeInfoNorm] = { col_gray3, col_gray1, col_gray2 }, // infobar middle unseleced
};

static const char *const autostart[] = {
    "dwmblocks", NULL,
    "dunst", NULL,
    "fcitx5", NULL,
    "udiskie", NULL,
    "picom", NULL,
    "redshift", NULL,
    "/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,
    "sh", "-c", "syncthing -no-browser", NULL,
/*    "sh", "-c", "xrandr --output HDMI-0 --mode 1920x1080 --rate 74.97", NULL,
 "sh", "-c", "xrandr --output HDMI-0 --rotate left --left-of HDMI-1 --pos 1080x1500", NULL,*/
    "sh", "-c", "feh --bg-fill /home/kerojam/Pictures/wallpapers/anime/BLIY/1178779.jpg", NULL,
    NULL /*termintate*/
};

/* tagging */
static const char *tags[] = { "百合", "伝え合う", "仕事", "エディター", "遊び", "動画制作", "ミスク" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance          title    tags mask     isfloating  monitor */
	{ "firefox",     "Toolkit", "Picture-in-Picture", 0,            1,         -1 },
	{ "Anki",           NULL,       "Statistics",     0,            1,         -1 },
	{ "Anki",           NULL,        "Preview",       0,            1,         -1 },
   	{ "Anki",           NULL,       "Edit Current",   0,            1,         -1 },
	{ "weston-1", "Weston Compositor",  NULL,         3,            0,         -1 },
	{ "vesktop", 	"vesktop",	        NULL,         2,            0,         -1 },
	{ "Signal",         NULL,           NULL,         2,            0,         -1 },
	{ "resolve",    "resolve",          NULL,         5,            0,         -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;   /* 1 means attach after the currently active window */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "| タイル |",    tile },/* first entry is default */
	{ "| ><> |",      NULL },
	{ "| [M] |",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", NULL };
static const char *rofipmcmd[] = { "/home/kerojam/.config/rofi/powermenu/type-2/powermenu.sh", NULL };
static const char *termcmd[] = { "kitty", NULL };
static const char *termfile[] = { "kitty", "yazi", NULL };
static const char *browser[] = { "firefox", NULL };
static const char *browser2[] = { "librewolf", NULL };
static const char *browser3[] = { "chromium", NULL };
static const char *file_browser[] = { "nemo", NULL };
static const char *anki_record[] = { "/home/kerojam/.config/ames/ames.sh", "-r", NULL };
static const char *anki_screen[] = { "/home/kerojam/.config/ames/ames.sh", "-s", NULL };
static const char *anki[] = { "anki", NULL };
static const char *emacs[] = { "emacs", NULL };
static const char *flameshot[] = { "flameshot", "gui", NULL };
static const Key keys[] = {
    /* modifier                     key        function        argument */
	
	{ MODKEY,                       XK_r,      spawn,          {.v = roficmd } },
	{ MODKEY|ShiftMask,             XK_y,      spawn,          {.v = rofipmcmd } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,	                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY, 		 	XK_b,	   spawn,	   {.v = browser } },
	{ MODKEY|ShiftMask,	        XK_b,	   spawn,	   {.v = browser2 } },
	{ MODKEY,                       XK_s,	   spawn,	   {.v = browser3 } },
	{ MODKEY,		        XK_e,	   spawn,    	   {.v = file_browser } },
	{ MODKEY,             XK_w,      spawn,          {.v = termfile } },
	{ MODKEY,                       XK_u,      spawn,          {.v = emacs } },
	{ MODKEY|ShiftMask,		XK_e,	   spawn, SHCMD("feh --bg-fill /home/kerojam/Pictures/wallpapers/anime/BLIY/1265356.jpg")},
	{ MODKEY|ShiftMask|ControlMask,		XK_e,	   spawn, SHCMD("feh --bg-fill /home/kerojam/Pictures/wallpapers/anime/BLIY/1178779.jpg")},
	{ MODKEY|ShiftMask|Mod1Mask,		XK_e,	   spawn,	SHCMD("feh --bg-fill /home/kerojam/Pictures/wallpapers/anime/normal/GKe-Pc3aoAAt-A1.jpg")},
	{ MODKEY|ControlMask,		XK_e,	   spawn,	SHCMD("feh --bg-fill /home/kerojam/Pictures/wallpapers/anime/BlueArchive/wallhaven-rdv5q7.jpg")},
	{ 0,                            XK_F7,     spawn,          {.v = flameshot } },
	{ 0,			XF86XK_MonBrightnessUp,		spawn, SHCMD ("brightnessctl s 10+")},
	{ ShiftMask,			XF86XK_MonBrightnessUp,		spawn, SHCMD ("brightnessctl s 400")},
	{ ShiftMask,			XF86XK_MonBrightnessDown,	spawn, SHCMD ("brightnessctl s 12000")},
	{ 0,			XF86XK_MonBrightnessDown,	spawn, SHCMD ("brightnessctl s 10-")},
	{ 0,			XF86XK_AudioLowerVolume,	spawn, SHCMD ("amixer sset Master 5%- unmute")},
	{ 0,			XF86XK_AudioMute,		spawn, SHCMD ("amixer sset Master $(amixer get Master | grep -q '\\[on\\]' && echo 'mute' || echo 'unmute')")},
	{ 0,			XF86XK_AudioRaiseVolume,	spawn, SHCMD ("amixer sset Master 5%+ unmute")},
	{ MODKEY,                       XK_a,      spawn,          {.v = anki } },
	{ ControlMask|ShiftMask,    	XK_F7,	   spawn,	   {.v = anki_record } },
	{ ShiftMask,  		        XK_F7,	   spawn,          {.v = anki_screen } },
	{ MODKEY,                       XK_y,      togglebar,      {0} },
	{ MODKEY,                       XK_n,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_m,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_j,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_k,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = +0.05} },
	{ MODKEY|Mod1Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrihgaps,     {.i = -1 } },
    
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY,   		        XK_l,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask|ControlMask, XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_v,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_i,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_o,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask|ControlMask,             XK_i,      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask|ControlMask,             XK_o,      tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

