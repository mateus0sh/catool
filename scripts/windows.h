#ifndef WINDOWS_HACK_H
#define WINDOWS_HACK_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>


std::string exec(const char* cmd);
void getUsername(char* buffer, DWORD size);


/*

 dP"Yb  88""Yb  dP""b8  dP"Yb  888888 .dP"Y8
dP   Yb 88__dP dP   `" dP   Yb 88__   `Ybo."
Yb   dP 88"""  Yb      Yb   dP 88""   o.`Y8b
 YbodP  88      YboodP  YbodP  888888 8bodP'

*/
void Meltdown();
void fastStartup();
int hardware_speed();
int clearTempFiles();

/*

   db    888888 88 Yb    dP    db    88""Yb     Yb        dP 88 88b 88 8888b.   dP"Yb  Yb        dP .dP"Y8
  dPYb     88   88  Yb  dP    dPYb   88__dP      Yb  db  dP  88 88Yb88  8I  Yb dP   Yb  Yb  db  dP  `Ybo."
 dP__Yb    88   88   YbdP    dP__Yb  88"Yb        YbdPYbdP   88 88 Y88  8I  dY Yb   dP   YbdPYbdP   o.`Y8b
dP""""Yb   88   88    YP    dP""""Yb 88  Yb        YP  YP    88 88  Y8 8888Y"   YbodP     YP  YP    8bodP'

*/
bool isWindowsActivated();
void activeWindows();

//

/*

   db    88""Yb 88""Yb .dP"Y8
  dPYb   88__dP 88__dP `Ybo."
 dP__Yb  88"""  88"""  o.`Y8b
dP""""Yb 88     88     8bodP'

*/
void fuckEdge();
void fuckUselessApps();
int Calculadora();

#endif