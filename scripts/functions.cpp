#define _CRT_SECURE_NO_WARNINGS
#define _POSIX_C_SOURCE 200809L

/*

88 88b 88  dP""b8 88     88   88 8888b.  888888 .dP"Y8
88 88Yb88 dP   `" 88     88   88  8I  Yb 88__   `Ybo."
88 88 Y88 Yb      88  .o Y8   8P  8I  dY 88""   o.`Y8b
88 88  Y8  YboodP 88ood8 `YbodP' 8888Y"  888888 8bodP'

*/


#include <windows.h>
#include <comdef.h>
#include <map>
#include <filesystem>  
#include <cctype>
#include <shobjidl.h>

#include <Wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")


/*

.dP"Y8  dP""b8 88""Yb 88 88""Yb 888888 .dP"Y8
`Ybo." dP   `" 88__dP 88 88__dP   88   `Ybo."
o.`Y8b Yb      88"Yb  88 88"""    88   o.`Y8b
8bodP'  YboodP 88  Yb 88 88       88   8bodP'

*/
#include "windows.h"


namespace fs = std::filesystem;

const std::map<std::string, std::string> browsers = {
    { "Chrome",     "https://dl.google.com/chrome/install/latest/chrome_installer.exe" },
    { "Firefox",    "https://download.mozilla.org/?product=firefox-latest&os=win&lang=pt-BR" },
    { "Opera",      "https://net.geo.opera.com/opera/stable/windows?utm_tryagain=yes" },
    { "Brave",      "https://laptop-updates.brave.com/latest/winx64" },
    { "DuckDuckGo", "https://duckduckgo.com/windows?origin=funnel_home_website__hero"},
    { "Vivaldi",    "https://downloads.vivaldi.com/stable/Vivaldi.7.5.3735.64.x64.exe"},
    { "Tor",        "https://dist.torproject.org/torbrowser/13.5.21/tor-browser-windows-i686-portable-13.5.21.exe"}
};



bool askYN(const std::string& message) {
    std::string input;

    while (true) {
        std::cout << message << " (Y/N) [Default: Y]: ";
        std::getline(std::cin, input);

        if (input.empty()) return true;  // Enter sem nada = YES

        if (input.size() == 1) {
            char c = std::toupper(static_cast<unsigned char>(input[0]));
            if (c == 'Y') return true;
            if (c == 'N') return false;
        }

        std::cout << "Entrada invalida. Tente novamente.\n";
    }
}

int downloadFile(const char* url, const char* outFile) {
    char wgetPath[MAX_PATH];
    if (GetFullPathNameA("essencial\\wget.exe", MAX_PATH, wgetPath, NULL) == 0) {
        printf("wget.exe não encontrado!\n");
        return 1;
    }

    fs::path p(outFile);
    if (!fs::exists(p.parent_path()))
        fs::create_directories(p.parent_path());

    std::string cmd = std::string("\"") + wgetPath + "\" -q --show-progress "
        "--load-cookies cookies.txt --save-cookies cookies.txt --keep-session-cookie "
        "-c --no-check-certificate \"" + url + "\" -t 5 -O \"" + outFile + "\"";


    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    if (!CreateProcessA(NULL, cmd.data(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Falha ao iniciar wget.exe\n");
        return 2;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

int extrairZIPcsenha(const char* zip, const char* senha, const char* destino)
{
    std::string cmd = std::string("powershell -Command \"& '7za.exe' x '")
        + zip + "' -p'" + senha + "' -o'" + destino + "' -y\"";
    return system(cmd.c_str());
}


void executar(const std::wstring& caminhoExe) {
    ShellExecuteW(NULL, L"open", caminhoExe.c_str(), NULL, NULL, 1);
}

std::wstring stringToWString(const std::string& s) {
    if (s.empty()) return L"";
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), NULL, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), &wstr[0], size_needed);
    return wstr;
}

std::string exec(const char* cmd) {
    std::string result;
    char buffer[128];
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) return "ERROR";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) result += buffer;
    _pclose(pipe);
    return result;
}

void installApp(const char* url, const char* nome)
{
    if (!fs::exists("apps") && !fs::is_directory("apps")) fs::create_directory("apps");
    std::string path = std::string("apps/") + nome;
    
    std::cout << ">> Downloading " << nome << " ...\n";
    downloadFile(url, path.c_str());

    std::cout << ">> Opening " << nome << " ...\n";
    executar(stringToWString(fs::absolute(path).string()));
}

void InstallBrowser(std::string browser)
{
    fs::path dir("browsers");
    if (!fs::exists(dir)) fs::create_directory(dir);

    auto it = browsers.find(browser);
    if (it != browsers.end())
    {
        fs::path filePath = dir / (it->first + ".exe");

        std::cout << ">> Downloading " << it->first << " browser...\n";
        downloadFile(it->second.c_str(), filePath.string().c_str());

        std::cout << ">> Opening " << it->first << " browser...\n";
        executar(stringToWString(fs::absolute(filePath).string()));
    }
}

bool CopyFileToSystem32(const std::wstring& source, const std::wstring& destination) {
    if (!CopyFileW(source.c_str(), destination.c_str(), FALSE)) {
        std::wcerr << L"Erro ao copiar " << source << L" para " << destination << std::endl;
        return false;
    }
    return true;
}


HRESULT InitializeWMI(IWbemServices** pSvc) {
    HRESULT hres = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        std::wcerr << L"Falha ao inicializar COM. Código: " << std::hex << hres << L"\n";
        return hres;
    }
    hres = CoInitializeSecurity(nullptr, -1, nullptr, nullptr,
        RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE,
        nullptr, EOAC_NONE, nullptr);
    if (FAILED(hres)) {
        std::wcerr << L"Falha na segurança COM. Código: " << std::hex << hres << L"\n";
        CoUninitialize();
        return hres;
    }

    IWbemLocator* pLoc = nullptr;
    hres = CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&pLoc);
    if (FAILED(hres)) {
        std::wcerr << L"Falha criando WbemLocator. Código: " << std::hex << hres << L"\n";
        CoUninitialize();
        return hres;
    }

    hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), nullptr, nullptr, nullptr, 0, nullptr, nullptr, pSvc);
    pLoc->Release();
    if (FAILED(hres)) {
        std::wcerr << L"Falha ao conectar ROOT\\CIMV2. Código: " << std::hex << hres << L"\n";
        CoUninitialize();
        return hres;
    }

    hres = CoSetProxyBlanket(*pSvc,
        RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr,
        RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE,
        nullptr, EOAC_NONE);
    if (FAILED(hres)) {
        std::wcerr << L"Falha ao configurar proxy WMI. Código: " << std::hex << hres << L"\n";
        (*pSvc)->Release();
        CoUninitialize();
        return hres;
    }

    return S_OK;
}

//
void regset(HKEY raiz, const std::wstring& caminho, const std::wstring& nomeValor, DWORD dado) {
    HKEY chave;
    LONG status = RegCreateKeyExW(raiz,caminho.c_str(),0,NULL,REG_OPTION_NON_VOLATILE,KEY_SET_VALUE,NULL,&chave,NULL);
    if (status == ERROR_SUCCESS) {
        status = RegSetValueExW(chave, nomeValor.c_str(), 0, REG_DWORD, reinterpret_cast<const BYTE*>(&dado), sizeof(dado) );
        if (status == ERROR_SUCCESS) std::wcout << L">> " << nomeValor << L" definido como " << dado << L"\n";
        else std::wcerr << L"ERRO: Erro ao definir " << nomeValor << L"\n";
        RegCloseKey(chave);
    }
    else std::wcerr << L"ERRO: Erro ao abrir/criar a chave de registro.\n";
}


bool regset_str(HKEY root, const wchar_t* subKey, const wchar_t* valueName, const wchar_t* data) {
    HKEY hKey;
    LONG res = RegOpenKeyExW(root, subKey, 0, KEY_SET_VALUE, &hKey);
    if (res != ERROR_SUCCESS) {
        res = RegCreateKeyExW(root, subKey, 0, nullptr, 0, KEY_SET_VALUE, nullptr, &hKey, nullptr);
        if (res != ERROR_SUCCESS) {
            std::wcerr << L"Erro abrindo/criando chave: " << subKey << L" Código: " << res << L"\n";
            return false;
        }
    }

    res = RegSetValueExW(hKey, valueName, 0, REG_SZ, reinterpret_cast<const BYTE*>(data), (DWORD)((wcslen(data) + 1) * sizeof(wchar_t)));
    RegCloseKey(hKey);

    if (res != ERROR_SUCCESS) {
        std::wcerr << L"Erro definindo valor string: " << valueName << L" Código: " << res << L"\n";
        return false;
    }

    return true;
}

bool criarAtalho(const std::wstring& destino, const std::wstring& caminhoExe, const std::wstring& argumentos = L"", const std::wstring& descricao = L"")
{
    HRESULT hres;
    IShellLinkW* psl;

    if (FAILED((hres = CoInitialize(NULL)))) return false;
    if (SUCCEEDED((hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (LPVOID*)&psl))))
    {
        psl->SetPath(caminhoExe.c_str());
        psl->SetArguments(argumentos.c_str());
        psl->SetDescription(descricao.c_str());

        IPersistFile* ppf;
        if (SUCCEEDED((hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf))))
        {
            hres = ppf->Save(destino.c_str(), TRUE);
            ppf->Release();
        }
        psl->Release();
    }
    CoUninitialize();
    return SUCCEEDED(hres);
}

bool addEssencialToPath()
{
    char exePath[MAX_PATH];
    if (!GetModuleFileNameA(NULL, exePath, MAX_PATH)) return false;

    std::filesystem::path projectDir = std::filesystem::path(exePath).parent_path();
    std::string essencialPath = (projectDir / "essencial").string();

    HKEY hKey;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Environment", 0, KEY_READ | KEY_WRITE, &hKey) != ERROR_SUCCESS) return false;

    char currentPath[32767];
    DWORD bufSize = sizeof(currentPath);
    DWORD type = REG_EXPAND_SZ;
    if (RegQueryValueExA(hKey, "Path", nullptr, &type, (LPBYTE)currentPath, &bufSize) != ERROR_SUCCESS) currentPath[0] = '\0';

    std::string newPath = currentPath;
    std::string currentLower = newPath;
    std::string essencialLower = essencialPath;
    std::transform(currentLower.begin(), currentLower.end(), currentLower.begin(), ::tolower);
    std::transform(essencialLower.begin(), essencialLower.end(), essencialLower.begin(), ::tolower);

    if (currentLower.find(essencialLower) == std::string::npos) {
        if (!newPath.empty() && newPath.back() != ';')
            newPath += ";";
        newPath += essencialPath;
        if (RegSetValueExA(hKey, "Path", 0, REG_EXPAND_SZ, (const BYTE*)newPath.c_str(), (DWORD)(newPath.size() + 1)) != ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return false;
        }
        SendMessageTimeoutA(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)"Environment", SMTO_ABORTIFHUNG, 5000, nullptr);
    }

    RegCloseKey(hKey);
    return true;
}


