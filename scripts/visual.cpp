#define _CRT_SECURE_NO_WARNINGS
#define _WIN32_WINNT 0x0602

/*

88 88b 88  dP""b8 88     88   88 8888b.  888888 .dP"Y8
88 88Yb88 dP   `" 88     88   88  8I  Yb 88__   `Ybo."
88 88 Y88 Yb      88  .o Y8   8P  8I  dY 88""   o.`Y8b
88 88  Y8  YboodP 88ood8 `YbodP' 8888Y"  888888 8bodP'

*/
#include <iostream>
#include <map>
#include <windows.h>
#include <stdio.h>
#include <Lmcons.h>
#include <filesystem>  
#include <shlobj.h>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")

#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

/*

.dP"Y8  dP""b8 88""Yb 88 88""Yb 888888 .dP"Y8
`Ybo." dP   `" 88__dP 88 88__dP   88   `Ybo."
o.`Y8b Yb      88"Yb  88 88"""    88   o.`Y8b
8bodP'  YboodP 88  Yb 88 88       88   8bodP'

*/
#include "windows.h"
#include "functions.h"




namespace fs = std::filesystem;
extern wchar_t aria2Folder[MAX_PATH];
int pagina = 0;
int loading = 0;

const char* art[] = {
    "  ,-.       _,---._ __  / \\",
    " /  )    .-'       `./ /   \\",
    "(  (   ,'            `/    /|                      catOOL",
    " \\  `-\"             \\\'\\   / |                     - alpha -",
    "  `.              ,  \\ \\ /  |",
    "   /`.          ,'-`----Y   |",
    "  (            ;        |   '",
    "  |  ,-.    ,-'         |  /",
    "  |  | (   |            | /",
    "  )  |  \\  `.___________|/",
    "  `--'   `--'"
};

const char* art_installer[] = {
    "        dP\"\"b8    db    888888  dP\"Yb   dP\"Yb  88         ",
    "       dP   `\"   dPYb     88   dP   Yb dP   Yb 88         ",
    "       Yb       dP__Yb    88   Yb   dP Yb   dP 88.o       ",
    "        YboodP dP\"\"\"\"Yb   88    YbodP   YbodP  88ood8     ",
    "                                                              ",
    " ____  ____   _____ ______   ____  _      _        ___  ____  ",
    "|    ||    \\ / ___/|      | /    || |    | |      /  _]|    \\ ",
    " |  | |  _  (   \\_ |      ||  o  || |    | |     /  [_ |  D  )",
    " |  | |  |  |\\__  ||_|  |_||     || |___ | |___ |    _]|    / ",
    " |  | |  |  |/  \\ |  |  |  |  _  ||     ||     ||   [_ |    \\ ",
    " |  | |  |  |\\    |  |  |  |  |  ||     ||     ||     ||  .  \\",
    "|____||__|__| \\___|  |__|  |__|__||_____||_____||_____||__|\\_|",
    "                                                              ",
};

const char* options_art[] = { // 
    "\n\033[30;41m|-----------------------------------------------------------|\033[31;40m",
    "\033[30;41m| INSTALADOR                                                |\033[31;40m",
    "\033[30;41m|-----------------------------------------------------------|\033[31;40m\n",
    
    " \033[31;40mDrivers e Hardware                                         Navegadores",
    " \033[31;40m____________                                               ____________                                                 ",
    " \033[31;40m[1]\033[0m | Driver Booster \033[90m(OFF)                                 \033[31;40m[18]\033[0m | Google Chrome \033[90m(Navegador)",
    " \033[31;40m[2]\033[0m | Snappy Driver \033[90m(Baixar Drivers)                       \033[31;40m[19]\033[0m | Firefox \033[90m(Navegador)",
    " \033[31;40m[3]\033[0m | HWMonitor                                            \033[31;40m[20]\033[0m | Opera \033[90m(Navegador)",
    " \033[31;40m[4]\033[0m | CPU-Z                                                \033[31;40m[21]\033[0m | Brave \033[90m(Navegador)",
    " \033[31;40m[5]\033[0m |                                                      \033[31;40m[22]\033[0m | DuckDuckGo \033[90m(Navegador)",
    " \033[31;40m[6]\033[0m |                                                      \033[31;40m[23]\033[0m | Vivaldi \033[90m(Navegador)",
    " \033[31;40m[7]\033[0m |                                                      \033[31;40m[24]\033[0m | Tor \033[90m(Navegador / Portable)",
    " \033[31;40m[8]\033[0m | ",

    "\n \033[31;40mGame Launchers                                             Compactadores",
    " \033[31;40m____________                                               ____________                                                 ",
    " \033[31;40m[9]\033[0m  | Steam \033[90m(Game Launcher)                               \033[31;40m[25]\033[0m | WinRAR",
    " \033[31;40m[10]\033[0m | Epic Games \033[90m(Game Launcher)                          \033[31;40m[26]\033[0m | 7-Zip",

    "\n \033[31;40mAPPS VARIADOS                                            ",
    " \033[31;40m____________                                            ",
    " \033[31;40m[11]\033[0m  | Notepad++                                          \033[31;40m[27]\033[0m  | Visual Studio Code",
    " \033[31;40m[12]\033[0m  | TeamViewer                                         \033[31;40m[28]\033[0m  | AnyDesk",
    " \033[31;40m[13]\033[0m  | PuTTY                                              \033[31;40m[29]\033[0m  | OBS Studio",
    " \033[31;40m[14]\033[0m  | 7+ Taskbar Tweaker                                 \033[31;40m[30]\033[0m  | Process Explorer",
    " \033[31;40m[15]\033[0m  | VLC Media Player                                   \033[31;40m[31]\033[0m  | Sublime Text (setup)",
    " \033[31;40m[16]\033[0m  | Rufus 4.9p",


    "                                                            \033[30;41m[98]\033[0m | Voltar pagina <<",
    "                                                            \033[30;41m[99]\033[0m | Proxima pagina >>"
};

const char* options_art_3[] = { // 
    "\n\033[30;43m|-----------------------------------------------------------|\033[31;40m",
    "\033[30;43m| WINDOWS                                                   |\033[31;40m",
    "\033[30;43m|-----------------------------------------------------------|\033[31;40m\n",

    " \033[33;40mOPCOES",
    " \033[33;40m____________",
    " \033[33;40m[1]\033[0m  | Trocar Calculadora do W10 pela do W7                   ",
    " \033[33;40m[2]\033[0m  | Remover EDGE",
    " \033[33;40m[3]\033[0m  | Remover Apps Inuteis                                   ",
    " \033[33;40m[4]\033[0m  | Ativar Windows",
    " \033[33;40m[5]\033[0m  | Otimização na CPU, GPU, Power..                        ",
    " \033[33;40m[6]\033[0m  | Desabilitar as proteções do Meltdown ou Spectre",
    " \033[33;40m[7]\033[0m  | Correcao de Startup - Iniciar mais rapido              ",
    " \033[33;40m[8]\033[0m  | Remover Arquivos Temporarios (Temp, %Temp%, Prefetch)",
    " \033[33;40m[9]\033[0m  | Ativar Windows Defender                                ",
    " \033[33;40m[10]\033[0m | Desativar Windows Defender",
    " \033[33;40m[11]\033[0m | Ativar Firewall                                        ",
    " \033[33;40m[12]\033[0m | Desativar Firewall",
    " \033[33;40m[13]\033[0m | Plano de Energia em Alto Desempenho",
    

    "                                                            \033[30;41m[98]\033[0m | Voltar pagina <<",
    "                                                            \033[30;41m[99]\033[0m | Proxima pagina >>"
};

int linha = 11;
bool rodando;

typedef LONG(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOEXW);
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int Inicial() {

    if (!InternetCheckConnection(L"http://www.msftconnecttest.com/redirect", FLAG_ICC_FORCE_CONNECTION, 0)) {
        MessageBoxA(NULL, "Sem acesso à internet. O programa sera fechado.", "Erro de Conexao", MB_ICONERROR);
        exit(0);
        return 0;
    }

    if (!fs::exists("essencial") && !fs::is_directory("essencial"))
    {
        system("color 4f");
        int n = sizeof(art_installer) / sizeof(art_installer[0]); // número de linhas
        for (int i = 0; i < n; i++) {
            printf("%s\n", art_installer[i]);
        }
    }
    else
    {
        int n = sizeof(art) / sizeof(art[0]); // número de linhas
        for (int i = 0; i < n; i++) {
            printf("%s\n", art[i]);
        }
        if (!loading)
        {
            loading = true;
            Sleep(2000);
        }
    }

    // 
    // info
    // 
    HMODULE hMod; //ntdll
    RtlGetVersionPtr rtlGetVersion; //rtl
    RTL_OSVERSIONINFOEXW osInfo = { 0 };
    osInfo.dwOSVersionInfoSize = sizeof(osInfo);

    // 
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = MAX_COMPUTERNAME_LENGTH + 1;

    // 
    char username[UNLEN + 1];
    getUsername(username, UNLEN + 1);

    // 
    // admin
    // 
    BOOL isAdmin = FALSE;
    PSID adminGroup = NULL;
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;

    if (!(hMod = GetModuleHandleW(L"ntdll.dll"))) {
        printf("Erro carregando ntdll.dll\n");
        return 1;
    }

    if (!(rtlGetVersion = (RtlGetVersionPtr)GetProcAddress(hMod, "RtlGetVersion"))) {
        printf("Erro obtendo RtlGetVersion\n");
        return 1;
    }


    if (rtlGetVersion(&osInfo) != 0) {
        printf("Erro obtendo versão do Windows\n");
        return 1;
    }



    if (AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminGroup)) {
        if (!CheckTokenMembership(NULL, adminGroup, &isAdmin)) isAdmin = FALSE;
        FreeSid(adminGroup);
    }

    if (!fs::exists("essencial") && !fs::is_directory("essencial"))
    {
        fs::create_directory("essencial");

        printf("\r%s, espere alguns segundos, iremos baixar arquivos essenciais!", username);
        fflush(stdout);

        HRESULT hr = URLDownloadToFileW(NULL, L"https://eternallybored.org/misc/wget/1.21.4/32/wget.exe", L"essencial/wget.exe", 0, NULL);
        if (SUCCEEDED(hr)) std::wcout << L"\n[+] Iniciando o Download!" << std::endl;
        else std::wcout << L"\n[-] Falha no download: " << hr << std::endl;
        Sleep(1000);
        
        downloadFile("https://www.7-zip.org/a/7za920.zip", "essencial/7z.zip");
        system("powershell -Command \"Expand-Archive -Path 'essencial/7z.zip' -DestinationPath 'essencial/' -Force\"");
        printf("\033[2K\r");
        fflush(stdout);

        addEssencialToPath();
        char path[MAX_PATH];
        GetModuleFileNameA(NULL, path, MAX_PATH);
        system("del /Q \"essencial/7z.zip\"");
        
        system("color 0F");
        wchar_t caminhoExe[MAX_PATH];
        GetModuleFileNameW(NULL, caminhoExe, MAX_PATH);

        STARTUPINFOW si = { sizeof(si) };
        PROCESS_INFORMATION pi;

        if (CreateProcessW(caminhoExe, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
        {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }

        HANDLE hProcess = GetCurrentProcess();
        TerminateProcess(hProcess, 0);
    }


    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n USER: ");

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf(username);



    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("  | COMPUTERNAME: ");
    if (GetComputerNameA(computerName, &size)) { 
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf(computerName);
    }
    else {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf(computerName);
    }

    // 
    // ADMIN
    //
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("  | ADMIN: ");
    if (isAdmin) SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY), printf("SIM");
    else SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY), printf("NAO");

    // 
    // TEMPO
    //
    TIME_ZONE_INFORMATION tzInfo;
    DWORD tz = GetTimeZoneInformation(&tzInfo);
    LONG bias = tzInfo.Bias;
    SYSTEMTIME st;
    GetLocalTime(&st);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n Fuso horario: ");

    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("%ls", tzInfo.StandardName);


    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("  | Deslocamento UTC: ");

    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("%ld horas", -bias / 60);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("  | Hora: ");

    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("%02d/%02d/%04d %02d:%02d:%02d.%03d\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

    //
    // Informacoes do Windows
    //
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf(" Windows: ");

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("%d.%d ", osInfo.dwMajorVersion, osInfo.dwMinorVersion);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("(Build %d)", osInfo.dwBuildNumber);

    //
    // Informacoes da Arquitetura
    //
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    //
    // --- Arquitetura ---
    //
    SYSTEM_INFO si;
    GetSystemInfo(&si);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("  | Arquitetura da CPU: ");

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    switch (si.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_AMD64: printf("x64"); break;
    case PROCESSOR_ARCHITECTURE_INTEL: printf("x86"); break;
    case PROCESSOR_ARCHITECTURE_ARM64: printf("ARM64"); break;
    default: printf("Desconhecida");
    }

    //
    // --- Núcleos ---
    //
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("  | Numero de nucleos: ");

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("%u", si.dwNumberOfProcessors);

    printf("\n\n");

    // Volta para cor branca
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    return 1;
}



void Options()
{
    system("cls");
    Inicial();
    int choice = 0, n = 0;
    
    if (pagina == 0) for (int i = 0; i < (sizeof(options_art) / sizeof(options_art[0])); i++) printf("%s\n", options_art[i]), Sleep(50);
    else if (pagina == 1) for (int i = 0; i < (sizeof(options_art_3) / sizeof(options_art_3[0])); i++) printf("%s\n", options_art_3[i]), Sleep(50);

    printf(" \033[31;40m>>\033[0m ");
    scanf("%d", &choice);

    if (choice == 99) // >>
        if (pagina == 1) pagina = 0;
        else pagina++;

    else if (choice == 98) // <<
        if (pagina == 0) pagina = 1;
        else pagina--;

    PWSTR path_dek = nullptr;
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (pagina == 0)
    {
        switch (choice)
        {
            case 1: // driver booster
            {
            }
            case 2: // sdi
            {
                downloadFile("https://driveroff.net/drv/SDI_1.25.3.7z", "apps/SDI_1.25.3.7z");
                system("essencial\\7za.exe x \".\\apps\\SDI_1.25.3.7z\" -o\".\\apps\\SDI\" -y");
                system("del /Q \"apps/SDI_1.25.3.7z\"");
                
                fs::path pasta = fs::absolute(fs::path("apps/SDI") / "SDI-drv.exe");
                ShellExecuteA(NULL, "open", pasta.string().c_str(), NULL, pasta.parent_path().string().c_str(), SW_SHOWNORMAL);
                break;
            }
            case 3: // hwmonitor
            {
                downloadFile("https://download.cpuid.com/hwmonitor/hwmonitor_1.58.exe", "apps/hwmonitor_1.58.exe");
                printf("[+] HWMonitor Instalado com sucesso.");
                executar(fs::absolute(std::filesystem::path("apps") / "hwmonitor_1.58.exe"));
                break;
            }
            case 4: // cpu-z
                downloadFile("https://download.cpuid.com/cpu-z/cpu-z_1.04-win9x.zip", "apps/z.zip");
                system("powershell -Command \"Expand-Archive -Path 'apps/z.zip' -DestinationPath 'apps/' -Force\"");
                system("del /Q \"apps/z.zip\"");
                system("del /Q \"apps/cpuz_w9x_readme.txt\"");

                printf("[+] CPU-Z Instalado com sucesso.");

                if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &path_dek))) {
                    std::wstring desktopPath(path_dek);
                    CoTaskMemFree(path_dek);
                    criarAtalho(desktopPath + L"\\cpuz.lnk", fs::absolute(std::filesystem::path("apps") / "cpuz_w9x.exe"), L"CPU-Z");
                    printf("[+] CPU-Z foi adicionado ao DESKTOP.");
                }
                executar(fs::absolute(std::filesystem::path("apps") / "cpuz_w9x.exe"));
                break;
            case 8:
                installApp("https://download.anydesk.com/AnyDesk.exe", "AnyDesk.exe");
                break;
            case 9: // steam
                installApp("https://cdn.cloudflare.steamstatic.com/client/installer/SteamSetup.exe", "steam.exe");
                break;
            case 10: // epic
                installApp("https://launcher-public-service-prod06.ol.epicgames.com/launcher/api/installer/download/EpicGamesLauncherInstaller.msi", "epic.exe");
                break;

            // apps variados
            case 11:
                installApp("https://github.com/notepad-plus-plus/notepad-plus-plus/releases/download/v8.6.9/npp.8.6.9.Installer.x64.exe", "notepad.exe");
                break;
            case 12:
                installApp("https://download.teamviewer.com/download/TeamViewer_Setup.exe", "teamviewer.exe");
                break;
            case 13:
                installApp("https://the.earth.li/~sgtatham/putty/latest/w64/putty.exe", "PuTTY.exe");
                break;
            case 14:
                installApp("https://ramensoftware.com/downloads/7tt_setup.exe", "taskbar.exe");
                break;
            case 15:
                installApp("https://mirror.turbozoneinternet.net.br/videolan/vlc/3.0.18/win64/vlc-3.0.18-win64.exe", "vlc.exe");
                break;
            case 16:
                downloadFile("https://github.com/pbatard/rufus/releases/download/v4.9/rufus-4.9p.exe", "apps/rufus.exe");
                if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &path_dek))) {
                    std::wstring desktopPath(path_dek);
                    CoTaskMemFree(path_dek);
                    criarAtalho(desktopPath + L"\\rufus.lnk", fs::absolute(std::filesystem::path("apps") / "rufus.exe"), L"rufus");
                    printf("[+] rufus foi adicionado ao DESKTOP.");
                    Sleep(2000);
                }
                break;
            case 25: // winrar
                installApp("https://www.win-rar.com/fileadmin/winrar-versions/winrar/winrar-x64-713.exe", "winrar.exe");
                break;
            case 26: // zip
                installApp("https://www.7-zip.org/a/7z2301-x64.exe", "7z.exe");
                break;
            case 27:
                installApp("https://code.visualstudio.com/sha/download?build=stable&os=win32-x64-user", "vscode.exe");
                break;
            case 29:
                installApp("https://cdn-fastly.obsproject.com/downloads/OBS-Studio-31.1.2-Windows-x64-Installer.exe", "obs.exe");
                break;
            case 30:
                downloadFile("https://download.sysinternals.com/files/ProcessExplorer.zip", "apps/process.zip");
                system("powershell -Command \"Expand-Archive -Path 'apps/process.zip' -DestinationPath 'apps/' -Force\"");
                system("del /Q \"apps/process.zip\"");

                if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &path_dek))) {
                    std::wstring desktopPath(path_dek);
                    CoTaskMemFree(path_dek);
                    criarAtalho(desktopPath + L"\\procexp.lnk", fs::absolute(std::filesystem::path("apps") / "procexp.exe"), L"procexp");
                    criarAtalho(desktopPath + L"\\procexp64.lnk", fs::absolute(std::filesystem::path("apps") / "procexp64.exe"), L"procexp64");
                    printf("[+] Process Explorer foi adicionado ao DESKTOP.");
                }
                Sleep(2000);
                break;
            case 31:
                installApp("https://download.sublimetext.com/Sublime%20Text%20Build%203211%20x64%20Setup.exe", "sublimetext.exe");
                break;





            default:
                if (choice >= 18 && choice <= 24)
                {
                    std::map<int, std::string> browserOptions = { 
                        {18, "Chrome"},
                        {19, "Firefox"},
                        {20, "Opera"},
                        {21, "Brave"},
                        {22, "DuckDuckGo"},
                        {23, "Vivaldi"},
                        {24, "Tor"} 
                    };
                    if (browserOptions.count(choice)) {
                        InstallBrowser(browserOptions[choice]);
                    }
                    break;
                }
        }
    }
    else if (pagina == 1)
    {
        switch (choice)
        {

            case 1: 
                if (askYN("Voce deseja substituir sua Calculadora pela versao do W7 ?")) Calculadora();
                break;
            case 2: 
                if (askYN("Voce deseja remover o Edge?")) fuckEdge();
                break;
            case 3:
                if (askYN("Voce deseja remover apps inuteis do windows?")) fuckUselessApps();
                break;
            case 4:
                if (askYN("Voce deseja mesmo ativar o windows?")) activeWindows();
                break;
            case 5:
                if (askYN("Voce deseja habilitar otimização na CPU, GPU, Power..?")) hardware_speed();
                break;
            case 6:
                if (askYN("Voce deseja desabilitar as proteções do Meltdown ou Spectre?")) Meltdown();
                else fastStartup();
                break;
            case 7:
                if (askYN("Voce deseja habilitar otimizaçôes de boot (iniciar mais rapido)?"))
                {
                    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control", L"WaitToKillServiceTimeout", 2000);
                    regset(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"DisableLogonBackgroundImage", 1);
                    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management\\PrefetchParameters", L"EnablePrefetcher", 3);
                    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management\\PrefetchParameters", L"EnableSuperfetch", 3);
                }
                break;
            case 8:
                clearTempFiles();
                break;
            case 9: // ativar
                printf("[+] Ativando via PowerShell...\n");
                system("powershell -Command \"Set-MpPreference -DisableRealtimeMonitoring $false\"");

                printf("[+] Tentando iniciar o servico WinDefend...\n");
                system("sc start WinDefend");

                printf("[+] Removendo chave de registro DisableAntiSpyware...\n");
                system("reg delete \"HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows Defender\" /v DisableAntiSpyware /f");

                printf("\nWindows Defender ativado (pode exigir reinicio).\n");
                Sleep(2000);
                break;
            case 10: // desativar
                printf("[+] Desativando via PowerShell...\n");
                system("powershell -Command \"Set-MpPreference -DisableRealtimeMonitoring $true\"");

                printf("[+] Tentando parar o servico WinDefend...\n");
                system("sc stop WinDefend");

                printf("[+] Alterando registro (DisableAntiSpyware=1)...\n");
                system("reg add \"HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows Defender\" /v DisableAntiSpyware /t REG_DWORD /d 1 /f");

                printf("\nWindows Defender desativado (pode exigir reinicio).\n");
                Sleep(2000);
                break;

            case 11: // ativar firewall
                system("netsh advfirewall set allprofiles state on");
                printf("[+] Firewall ativado!\n");
                Sleep(2000);
                break;

            case 12: // desativar firewall
                system("netsh advfirewall set allprofiles state off");
                printf("[+] Firewall desativado!\n");
                Sleep(2000);
                break;
            case 13: 
                system("powercfg /setactive 8c5e7fda-e8bf-4a96-9a85-a6e23a8c635c");
                printf("[+] Plano de energia alterado para Alto Desempenho!\n");
                Sleep(2000);
                break;
        }
    }
}
