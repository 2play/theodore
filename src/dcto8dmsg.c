//////////////////////////////////////////////////////////////////////////////
// DCTO8DMSG.C - message text used by dcto8d
// Author   : Daniel Coulom - danielcoulom@gmail.com
// Web site : http://dcto8.free.fr
//
// This file is part of DCTO8D.
//
// DCTO8D is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DCTO8D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DCTO8D. If not, see <http://www.gnu.org/licenses/>.
//
//////////////////////////////////////////////////////////////////////////////

#include "../config.h"
#include "dcto8dmsg.h"
#include "dcto8doptions.h"

// Renvoie la chaine de caracteres en fonction de la langue selectionnee.
const char* gettext(const char *msg[2])
{
 if ((options.language < 0) || (options.language >= LANGUAGE_MAX))
 {
  return msg[0];
 }
 return msg[options.language];
}

const char* MSG_ABOUT_TITLE[] = { "A propos de DCTO8D", "About DCTO8D" };
const char* MSG_ABOUT[] = { "Version : "VERSION"\n"
                            "Auteur : Daniel Coulom\n"
                            "Site internet : http://dcto8.free.fr\n\n"
                            "Ce programme est diffusé SANS AUCUNE GARANTIE.\n"
                            "C'est un logiciel libre, et vous êtes encouragés à le redistribuer\n"
                            "sous certaines conditions. Lire les détails dans dcto8d-licence.txt\n\n"
                            "Raccourcis clavier :\n"
                            "- ECHAP = initialisation programme\n"
                            "- PAUSE = arrêt processeur 6809\n"
                            "- F6    = plein écran\n\n"
                            "Lire la documentation pour d'autres informations..."
                          , "Version : "VERSION"\n"
                            "Author : Daniel Coulom\n"
                            "Web site : http://dcto8.free.fr\n\n"
                            "This program comes with ABSOLUTELY NO WARRANTY.\n"
                            "This is free software, and you are welcome to redistribute it under\n"
                            "certain conditions. More details in dcto8d-licence.txt\n\n"
                            "Raccourcis clavier :\n"
                            "- ESC   = reset TO8D program\n"
                            "- PAUSE = stop 6809 processor\n"
                            "- F6    = toggle fullscreen\n\n"
                            "Please check the documentation for more information." };
const char* MSG_PROGNAME[] = { "DCTO8D - Emulateur TO8D Thomson", "DCTO8D - Thomson TO8D emulator" };
const char* MSG_MENU_SETTINGS[] = { "Param""\xe8""tres", "Settings" };
const char* MSG_MENU_KEYBOARD[] = { "Clavier", "Keyboard" };
const char* MSG_MENU_JOYSTICKS[] = { "Manettes", "Joysticks" };
const char* MSG_MENU_DISASSEMBLY[] = { "D""\xe9""sassemblage", "Disassembly" };
const char* MSG_BTN_NONE[] = { "aucune", "none" };
const char* MSG_EMULATED_KEY[] = { "touche TO8D ""\xe9""mul""\xe9""e", "emulated TO8D key" };
const char* MSG_EMULATED_FUNC[] = { "fonction ""\xe9""mul""\xe9""e", "emulated function" };
const char* MSG_KEYBOARD_LAYOUT[] = { "Disposition du clavier TO8D", "TO8D keyboard layout" };
const char* MSG_PRESS_KEY[] = { "Appuyez sur une touche pour voir la ", "Press a key to show the " };
const char* MSG_CLICK_PICTURE[] = { "Cliquez sur l'image pour changer la correspondance.", "Click a button in the picture to make a change." };
const char* MSG_JOY_EMULATION[] = { "Emulation des manettes", "Joystick emulation" };
const char* MSG_UNLOAD[] = { "[d""\xe9""charger]", "[unload]" };
const char* MSG_BACK_TO_FIRST[] = { "[retour au d""\xe9""but...]", "[back to first...]" };
const char* MSG_NEXT[] = { "[suite...]", "[next...]" };
const char* MSG_SETTINGS_LANG_FR[] = { "Fran""\xe7""ais", "French" };
const char* MSG_SETTINGS_LANG_EN[] = { "Anglais", "English" };
const char* MSG_SETTINGS_FPS[] = { "Trames / s", "Frames /s" };
const char* MSG_SETTINGS_PROC[] = { "Processeur", "Processor" };
const char* MSG_SETTINGS_WRITE[] = { "Ecriture", "Write" };
const char* MSG_YES[] = { "oui", "yes" };
const char* MSG_NO[] = { "non", "no" };
const char* MSG_SETTINGS_NUMPAD[] = { "Pav\xe9"" num""\xe9""rique", "Numpad" };

const char *msg_btn[][2]={
  /*0*/{"D\xe9sassembler",
  /*0*/ "Disassemble"},
  /*1*/{"R""\xe9""tablir la disposition standard",
  /*1*/ "Restore standard layout"},
  /*2*/{"Sauver la disposition personnalis""\xe9""e",
  /*2*/ "Save customized layout"},
  /*3*/{"R""\xe9""tablir les valeurs par d""\xe9""faut",
  /*3*/ "Restore default values"}
};
