#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <comdef.h>
#include <Wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>

/*

88   88 888888 88 88     88 888888    db    88""Yb 88  dP"Yb  .dP"Y8
88   88   88   88 88     88   88     dPYb   88__dP 88 dP   Yb `Ybo."
Y8   8P   88   88 88  .o 88   88    dP__Yb  88"Yb  88 Yb   dP o.`Y8b
`YbodP'   88   88 88ood8 88   88   dP""""Yb 88  Yb 88  YbodP  8bodP'

*/
std::wstring stringToWString(const std::string& s);
bool askYN(const std::string& message);

/*

Yb        dP 88 88b 88 8888b.   dP"Yb  Yb        dP .dP"Y8
 Yb  db  dP  88 88Yb88  8I  Yb dP   Yb  Yb  db  dP  `Ybo."
  YbdPYbdP   88 88 Y88  8I  dY Yb   dP   YbdPYbdP   o.`Y8b
   YP  YP    88 88  Y8 8888Y"   YbodP     YP  YP    8bodP'

*/
bool criarAtalho(const std::wstring& destino, const std::wstring& caminhoExe, const std::wstring& argumentos = L"", const std::wstring& descricao = L"");
void InstallBrowser(std::string browser);
HRESULT InitializeWMI(IWbemServices** pSvc);
bool addEssencialToPath();
bool CopyFileToSystem32(const std::wstring& source, const std::wstring& destination);

/*

888888 Yb  dP 888888  dP""b8
88__    YbdP  88__   dP   `"
88""    dPYb  88""   Yb
888888 dP  Yb 888888  YboodP

*/

std::string exec(const char* cmd);
void executar(const std::wstring& caminhoExe);

/*

   db    88""Yb  dP"Yb  88   88 88 Yb    dP  dP"Yb  .dP"Y8
  dPYb   88__dP dP   Yb 88   88 88  Yb  dP  dP   Yb `Ybo."
 dP__Yb  88"Yb  Yb b dP Y8   8P 88   YbdP   Yb   dP o.`Y8b
dP""""Yb 88  Yb  `"YoYo `YbodP' 88    YP     YbodP  8bodP'

*/
int downloadFile(const char* url, const char* outFile);
void installApp(const char* url, const char* nome);
int extrairZIPcsenha(const char* zip, const char* senha, const char* destino);

/*

88""Yb 888888  dP""b8 888888 8888b.  88 888888
88__dP 88__   dP   `" 88__    8I  Yb 88   88
88"Yb  88""   Yb  "88 88""    8I  dY 88   88
88  Yb 888888  YboodP 888888 8888Y"  88   88

*/
void regset(HKEY raiz, const std::wstring& caminho, const std::wstring& nomeValor, DWORD dado);
bool regset_str(HKEY root, const wchar_t* subKey, const wchar_t* valueName, const wchar_t* data);

#endif