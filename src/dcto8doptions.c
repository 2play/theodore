//////////////////////////////////////////////////////////////////////////////
// DCTO8DOPTIONS.C - Option setting, save & restore
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

#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "dcto8dglobal.h"
#include "dcto8dinterface.h"
#include "dcto8dmsg.h"
#include "dcto8ddevices.h"
#include "dcto8dvideo.h"
#include "dcto8demulation.h"
#include "dcto8dkeyb.h"

#define OPTIONBUTTON_MAX 8   //nombre de boutons boite de dialogue options

const dialogbutton optionbutton[OPTIONBUTTON_MAX] = {
{108,  32,  3}, //langue
{108,  52,  3}, //zoom
{108,  72,  3}, //processeur
{108,  92,  3}, //affichage
{108, 112,  3}, //protection k7
{108, 132,  3}, //protection fd
{108, 152,  3}, //emulation manettes
{ 10, 180, 18}  //valeurs par defaut
};

//variables globales
FILE *fpi;     //fichier dcto8d.ini
int language;  //0=francais 1=anglais
int frequency; //frequence 6809 en kHz

//Draw option box ////////////////////////////////////////////////////////////
void Drawoptionbox()
{
 SDL_Rect rect;
 int i;
 char string[50];
 if(dialog != 2)
 {
  Createdialogbox(172, 216);
  rect.x = 10; rect.w = dialogbox->w - 32;
  rect.y = 5; rect.h = 15;
  Drawtextbox(dialogbox, _(MSG_MENU_SETTINGS), rect, 1, bleu, 0); //titre
  dialog = 2;
 }
 //options
 rect.x = 10; rect.w = 94;
 rect.y = 32; rect.h = 15;
 Drawtextbox(dialogbox, language ? _(MSG_SETTINGS_LANG_EN) : _(MSG_SETTINGS_LANG_FR), rect, 0, blanc, -1);
 sprintf(string, "Zoom : %i%s", 100 * xclient / XBITMAP, "%");
 rect.y += 20;
 Drawtextbox(dialogbox, string, rect, 0, blanc, -1);
 sprintf(string, "%s : %i%s", _(MSG_SETTINGS_PROC), frequency / 10, "%");
 rect.y += 20;
 Drawtextbox(dialogbox, string, rect, 0, blanc, -1);
 sprintf(string, "%s : %i%s", _(MSG_SETTINGS_FPS), 100 / vblnumbermax, "%");
 rect.y += 20;
 Drawtextbox(dialogbox, string, rect, 0, blanc, -1);
 sprintf(string, "%s k7 : %s", _(MSG_SETTINGS_WRITE),
         k7protection ? _(MSG_NO) : _(MSG_YES));
 rect.y += 20;
 Drawtextbox(dialogbox, string, rect, 0, blanc, -1);
 sprintf(string, "%s fd : %s", _(MSG_SETTINGS_WRITE),
         fdprotection ? _(MSG_NO) : _(MSG_YES));
 rect.y += 20;
 Drawtextbox(dialogbox, string, rect, 0, blanc, -1);
 sprintf(string, "%s", keybpriority ? _(MSG_SETTINGS_NUMPAD) : _(MSG_MENU_JOYSTICKS));
 rect.y += 20;
 Drawtextbox(dialogbox, string, rect, 0, blanc, -1);
 //dessin des boutons
 for(i = 0; i < OPTIONBUTTON_MAX; i++) Drawbutton(&optionbutton[i], 0);
}

//Initialisation des valeurs par defaut //////////////////////////////////////
void Initdefault()
{
 language = 0;          //francais
 xclient = XBITMAP;     //zoomx 2
 yclient = 2 * YBITMAP; //zoomy 2
 frequency = 1000;      //1000 kHz
 vblnumbermax = 2;      //nombre de vbl entre deux affichages
 k7protection = 1;      //protection cassette
 fdprotection = 1;      //protection disquette
 keybpriority = 0;      //manettes prioritaires
}

//Mise a jour d'un parametre avec la valeur i de la popuptable////////////////
void Setoption(int i)
{
 int f[5] = {100, 500, 1000, 2000, 5000}; //frequences processeur
 int v[4] = {10, 4, 2, 1}; //nombre de vbl entre deux trames affichees
 if(i >= 0) switch(popuptable)
 {
  case 1: language = i; break;
  case 2: Resizescreen(XBITMAP * (i + 1) / 2, YSTATUS + YBITMAP * (i + 1)); break;
  case 3: frequency = f[i]; break;
  case 4: vblnumbermax = v[i]; break;
  case 5: k7protection = i; break;
  case 6: fdprotection = i; break;
  case 7: keybpriority = i; break;
 }
 dialog = 0;
 popuptable = 0;
 Drawoptionbox();
}

//Traitement des clics des boutons d'options /////////////////////////////////
void Optionclick()
{
 int i, x, y;

 //recherche du bouton du clic
 for(i = 0; i < OPTIONBUTTON_MAX; i++)
 {
  x = dialogrect.x + optionbutton[i].x;
  y = dialogrect.y + optionbutton[i].y;
  if(xmouse > x) if(xmouse < (x + bouton[optionbutton[i].n].w))
  if(ymouse > y) if(ymouse < (y + bouton[optionbutton[i].n].h))
  break;
 }
 if(i >= OPTIONBUTTON_MAX) return;
 //dessin du bouton enfonce
 Drawbutton(&optionbutton[i], 1);
 Displayscreen(); SDL_Delay(200);
 //traitement en fonction du bouton
 x = optionbutton[i].x;
 y = optionbutton[i].y;
 switch(i)
 {
  case 0: popuptabletext[0] = _(MSG_SETTINGS_LANG_FR); //langue
          popuptabletext[1] = _(MSG_SETTINGS_LANG_EN);
          popuptabletext[2] = "";
          Drawpopuptable(1, x, y);
          break;
  case 1: popuptabletext[0] = "  50%"; //zoom
          popuptabletext[1] = "100%";
          popuptabletext[2] = "150%";
          popuptabletext[3] = "200%";
          popuptabletext[4] = "";
          Drawpopuptable(2, x, y);
          break;
  case 2: popuptabletext[0] = "  10%"; //processeur
          popuptabletext[1] = "  50%";
          popuptabletext[2] = "100%";
          popuptabletext[3] = "200%";
          popuptabletext[4] = "500%";
          popuptabletext[5] = "";
          Drawpopuptable(3, x, y);
          break;
  case 3: popuptabletext[0] = "  10%"; //affichage
          popuptabletext[1] = "  25%";
          popuptabletext[2] = "  50%";
          popuptabletext[3] = "100%";
          popuptabletext[4] = "";
          Drawpopuptable(4, x, y);
          break;
  case 4: popuptabletext[0] = _(MSG_YES); //ecriture k7
          popuptabletext[1] = _(MSG_NO);
          popuptabletext[2] = "";
          Drawpopuptable(5, x, y);
          break;
  case 5: popuptabletext[0] = _(MSG_YES); //ecriture fd
          popuptabletext[1] = _(MSG_NO);
          popuptabletext[2] = "";
          Drawpopuptable(6, x, y);
          break;
  case 6: popuptabletext[0] = _(MSG_MENU_JOYSTICKS); //manettes ou clavier numerique
          popuptabletext[1] = _(MSG_SETTINGS_NUMPAD);
          popuptabletext[2] = "";
          Drawpopuptable(7, x, y);
          break;
  case 7: Initdefault();    //restore default values
          //Restorewindow(); //lire les commentaires de cette fonction
          Resizescreen(xclient, YSTATUS + yclient);
          dialog = 0;
          Drawoptionbox();
          break;
 }
 if(dialog == 2) if(popuptable == 0) Drawoptionbox();
}

//Option initialization //////////////////////////////////////////////////////
void Initoptions()
{
 int r;
 char string[256];
 char currentdir[256];
 memset(string, 0, 256);
 memset(currentdir, 0, 256);
 Initdefault();
 //chemins d'acces
 if (getcwd(currentdir, 256) == NULL) return;
 strcat(currentdir, "/");
 strcpy(path[0], currentdir);
 strcpy(path[1], currentdir);
 strcpy(path[2], currentdir);
 //ouverture fichier dcto8d.ini
 fpi = fopen("dcto8d.ini", "rb+");                 //s'il existe ouverture
 if(fpi == NULL) fpi = fopen("dcto8d.ini", "wb+"); //s'il n'existe pas : creation
 r = fread(string, 12, 1, fpi);                    //lecture identifiant
 if(r != 1 || strcmp("dcto8dini-01", string) != 0) return;
 //initialisation des options
 r = fread(&language, 4, 1, fpi);  //langue
 r = fread(&frequency, 4, 1, fpi); //frequence 6809
 r = fread(&xclient, 4, 1, fpi);   //largeur ecran
 r = fread(&yclient, 4, 1, fpi);   //hauteur ecran
 r = fread(&vblnumbermax, 4, 1, fpi);
 r = fread(&k7protection, 4, 1, fpi);
 r = fread(&fdprotection, 4, 1, fpi);
 r = fread(&keybpriority, 4, 1, fpi);
 //controle
 if(language < 0) language = 0;
 if(language > (LANGUAGE_MAX - 1)) language = LANGUAGE_MAX - 1;
 if(frequency < 100) frequency = 100;
 if(frequency > 9000) frequency = 9000;
 if(xclient < (XBITMAP / 2)) xclient = XBITMAP / 2;
 if(xclient > (2 * XBITMAP)) xclient = 2 * XBITMAP;
 if(yclient < YBITMAP) yclient = YBITMAP;
 if(yclient > (4 * YBITMAP)) yclient = 4 * YBITMAP;
 if(vblnumbermax < 1) vblnumbermax = 1;
 if(vblnumbermax > 64) vblnumbermax = 64;
 if(k7protection) k7protection = 1;
 if(fdprotection) fdprotection = 1;
 if(keybpriority) keybpriority = 1;
}

//Option save ////////////////////////////////////////////////////////////////
void Saveoptions()
{
 int i;
 i = 0;
 fseek(fpi, 0, SEEK_SET);
 fwrite("dcto8dini-01", 12, 1, fpi);
 fwrite(&language, 4, 1, fpi);  //langue
 fwrite(&frequency, 4, 1, fpi); //frequence 6809
 fwrite(&xclient, 4, 1, fpi);   //largeur ecran
 fwrite(&yclient, 4, 1, fpi);   //hauteur ecran
 fwrite(&vblnumbermax, 4, 1, fpi);
 fwrite(&k7protection, 4, 1, fpi);
 fwrite(&fdprotection, 4, 1, fpi);
 fwrite(&keybpriority, 4, 1, fpi);
 fwrite(&i, 4, 1, fpi);         //reserve
 fwrite(&i, 4, 1, fpi);         //reserve
 fwrite(&i, 4, 1, fpi);         //reserve
 fwrite(&i, 4, 1, fpi);         //reserve
 fwrite(&i, 4, 1, fpi);         //reserve
 fclose(fpi);
}
