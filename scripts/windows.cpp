/*

88 88b 88  dP""b8 88     88   88 8888b.  888888 .dP"Y8
88 88Yb88 dP   `" 88     88   88  8I  Yb 88__   `Ybo."
88 88 Y88 Yb      88  .o Y8   8P  8I  dY 88""   o.`Y8b
88 88  Y8  YboodP 88ood8 `YbodP' 8888Y"  888888 8bodP'

*/

#include <string>
#include <windows.h>
#include <filesystem>
#include <thread>


/*

.dP"Y8  dP""b8 88""Yb 88 88""Yb 888888 .dP"Y8
`Ybo." dP   `" 88__dP 88 88__dP   88   `Ybo."
o.`Y8b Yb      88"Yb  88 88"""    88   o.`Y8b
8bodP'  YboodP 88  Yb 88 88       88   8bodP'

*/
#include "windows.h"
#include "functions.h"


namespace fs = std::filesystem;


//
// others
//
void imageDesktop() // melhorar imagem -> sera adicionado na prox versão
{
    regset(HKEY_CURRENT_USER, L"Control Panel\\Desktop", L"JPEGImportQuality", 00000064);
}

void CleanFolder(const std::string& path, const std::string& name) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 8);
    std::cout << "[..] Limpando " << name << "...\n";
    SetConsoleTextAttribute(hConsole, 7);

    if (!fs::exists(path)) return;

    try {
        for (const auto& entry : fs::directory_iterator(path, fs::directory_options::skip_permission_denied)) {
            try {
                fs::remove_all(entry);
                SetConsoleTextAttribute(hConsole, 10);
                std::cout << "[+] Apagado: " << entry.path().string() << "\n";
                SetConsoleTextAttribute(hConsole, 7);
            }
            catch (...) {
            }
        }
    }
    catch (...) {
    }

    std::cout << "Concluído: " << name << "\n";
}

int clearTempFiles() {
    char temp[MAX_PATH], windir[MAX_PATH];
    GetEnvironmentVariableA("TEMP", temp, MAX_PATH);
    GetEnvironmentVariableA("WINDIR", windir, MAX_PATH);

    // Threads para cada pasta
    std::thread t1(CleanFolder, std::string(temp), "User TEMP");
    std::thread t2(CleanFolder, std::string(windir) + "\\Temp", "Windows TEMP");
    std::thread t3(CleanFolder, std::string(windir) + "\\Prefetch", "Prefetch");
    std::thread t4(CleanFolder, std::string(windir) + "\\SoftwareDistribution\\Download", "Windows Update Download");

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "Limpeza completa!\n";
    return 1;
}


//
// Apps Windows
//
void fuckUselessApps()
{
    std::vector<std::string> commands = {
        R"(schtasks /Change /TN "Microsoft\Windows\Application Experience\Microsoft Compatibility Appraiser" /Disable)",
        R"(schtasks /Change /TN "Microsoft\Windows\Application Experience\ProgramDataUpdater" /Disable)",
        R"(schtasks /Change /TN "Microsoft\Windows\Application Experience\StartupAppTask" /Disable)",
        R"(schtasks /Change /TN "Microsoft\Windows\Customer Experience Improvement Program\Consolidator" /Disable)",
        R"(schtasks /Change /TN "Microsoft\Windows\Customer Experience Improvement Program\KernelCeipTask" /Disable)",
        R"(schtasks /Change /TN "Microsoft\Windows\Customer Experience Improvement Program\UsbCeip" /Disable)",
        R"(schtasks /Change /TN "Microsoft\Windows\Customer Experience Improvement Program\Uploader" /Disable)",
        R"(schtasks /Change /TN "Microsoft\Windows\Shell\FamilySafetyUpload" /Disable)",
        R"(schtasks /Change /TN "Microsoft\Office\OfficeTelemetryAgentLogOn" /Disable)",
        R"(schtasks /Change /TN "Microsoft\Office\OfficeTelemetryAgentFallBack" /Disable)",
        R"(schtasks /Change /TN "Microsoft\Office\Office 15 Subscription Heartbeat" /Disable)",
        R"(schtasks /Change /DISABLE /TN "Microsoft\Windows\Setup\EOSNotify")",
        R"(schtasks /Change /DISABLE /TN "Microsoft\Windows\Setup\EOSNotify2")",
        R"(schtasks /Change /DISABLE /TN "Microsoft\Windows\End Of Support\Notify1")",
        R"(schtasks /Change /DISABLE /TN "Microsoft\Windows\End Of Support\Notify2")",
        R"(schtasks /Change /DISABLE /TN "Microsoft\Windows\SetupSQMTask")",
        R"(schtasks /Change /DISABLE /TN "Microsoft\Windows\Customer Experience Improvement Program\BthSQM")",
        R"(schtasks /Change /DISABLE /TN "Microsoft\Windows\Customer Experience Improvement Program\TelTask")",
        R"(schtasks /Change /DISABLE /TN "Microsoft\Windows\Application Experience\AitAgent")",
        R"(schtasks /Change /DISABLE /TN "Microsoft\Windows\PerfTrack\BackgroundConfigSurveyor")",

        // Delete tasks
        R"(schtasks /Delete /F /TN "Microsoft\Windows\Setup\EOSNotify")",
        R"(schtasks /Delete /F /TN "Microsoft\Windows\Setup\EOSNotify2")",
        R"(schtasks /Delete /F /TN "Microsoft\Windows\End Of Support\Notify1")",
        R"(schtasks /Delete /F /TN "Microsoft\Windows\End Of Support\Notify2")",
        R"(schtasks /Delete /F /TN "Microsoft\Windows\SetupSQMTask")",
        R"(schtasks /Delete /F /TN "Microsoft\Windows\Customer Experience Improvement Program\BthSQM")",
        R"(schtasks /Delete /F /TN "Microsoft\Windows\Customer Experience Improvement Program\Consolidator")",
        R"(schtasks /Delete /F /TN "Microsoft\Windows\Customer Experience Improvement Program\KernelCeipTask")",
        R"(schtasks /Delete /F /TN "Microsoft\Windows\Customer Experience Improvement Program\TelTask")",
        R"(schtasks /Delete /F /TN "Microsoft\Windows\Customer Experience Improvement Program\UsbCeip")",
        R"(schtasks /Delete /F /TN "Microsoft\Windows\Application Experience\Microsoft Compatibility Appraiser")",
        R"(schtasks /Delete /F /TN "Microsoft\Windows\Application Experience\ProgramDataUpdater")",
        R"(schtasks /Delete /F /TN "Microsoft\Windows\Application Experience\AitAgent")",
        R"(schtasks /Delete /F /TN "Microsoft\Windows\PerfTrack\BackgroundConfigSurveyor")"
    };

    int total = static_cast<int>(commands.size());
    for (int i = 0; i < total; ++i) {
        std::cout << "[" << (i + 1) << "/" << total << "] Executando...\r";
        system((commands[i] + " >nul 2>&1").c_str());
        std::cout << "[" << (i + 1) << "/" << total << "] Executando... OK\r";
    }
}

void fuckEdge()
{
    const std::wstring caminhoEdge = L"SOFTWARE\\Policies\\Microsoft\\Edge";

    std::cout << "[catool]: Fucking Edge .. 1/2 Remover botões e recursos" << std::endl;
    regset(HKEY_LOCAL_MACHINE, caminhoEdge, L"HubsSidebarEnabled", 0);
    regset(HKEY_LOCAL_MACHINE, caminhoEdge, L"BackgroundModeEnabled", 0);
    regset(HKEY_LOCAL_MACHINE, caminhoEdge, L"StartupBoostEnabled", 0);
    regset(HKEY_LOCAL_MACHINE, caminhoEdge, L"EfficiencyMode", 0);
    regset(HKEY_LOCAL_MACHINE, caminhoEdge, L"ShowAcrobatSubscriptionButton", 0);

    std::cout << "[catool]: Fucking Edge .. 2/2 Restringir permissões" << std::endl;
    regset(HKEY_LOCAL_MACHINE, caminhoEdge, L"DefaultGeolocationSetting", 2);
    regset(HKEY_LOCAL_MACHINE, caminhoEdge, L"DefaultSensorsSetting", 2);
    regset(HKEY_LOCAL_MACHINE, caminhoEdge, L"DefaultNotificationsSetting", 2);
    
    std::cout << "[catool]: Edge Fucked!" << std::endl;
}

//
// active windows
//
bool isWindowsActivated() {
    std::string output = exec("cscript //nologo %windir%\\system32\\slmgr.vbs /dli");
    if (output.find("License Status: Licensed") != std::string::npos ||
        output.find("Licensed") != std::string::npos) {
        return true;
    }
    return false;
}

void activeWindows()
{
    std::string commands[] = {
        "cscript //nologo c:\\windows\\system32\\slmgr.vbs /ipk TX9XD-98N7V-6WMQ6-BX7FG-H8Q99 >nul",
        "cscript //nologo c:\\windows\\system32\\slmgr.vbs /ipk 3KHY7-WNT83-DGQKR-F7HPR-844BM >nul",
        "cscript //nologo c:\\windows\\system32\\slmgr.vbs /ipk 7HNRX-D7KGG-3K4RQ-4WPJ4-YTDFH >nul",
        "cscript //nologo c:\\windows\\system32\\slmgr.vbs /ipk PVMJN-6DFY6-9CCP6-7BKTT-D3WVR >nul",
        "cscript //nologo c:\\windows\\system32\\slmgr.vbs /ipk W269N-WFGWX-YVC9B-4J6C9-T83GX >nul",
        "cscript //nologo c:\\windows\\system32\\slmgr.vbs /ipk MH37W-N47XK-V7XM9-C7227-GCQG9 >nul",
        "cscript //nologo c:\\windows\\system32\\slmgr.vbs /ipk NW6C2-QMPVW-D7KKK-3GKT6-VCFB2 >nul",
        "cscript //nologo c:\\windows\\system32\\slmgr.vbs /ipk 2WH4N-8QGBV-H22JP-CT43Q-MDWWJ >nul",
        "cscript //nologo c:\\windows\\system32\\slmgr.vbs /ipk NPPR9-FWDCX-D2C8J-H872K-2YT43 >nul",
        "cscript //nologo c:\\windows\\system32\\slmgr.vbs /ipk DPH2V-TTNVB-4X9Q3-TJR4H-KHJW4 >nul",
        "cscript //nologo c:\\windows\\system32\\slmgr.vbs /ipk WNMTR-4C88C-JK8YV-HQ7T2-76DF9 >nul",
        "cscript //nologo c:\\windows\\system32\\slmgr.vbs /ipk 2F77B-TNFGY-69QQF-B8YKP-D69TJ >nul"
    };
    std::string kmsServers[] = { "kms.shuax.com", "NextLevel.uk.to", "GuangPeng.uk.to", "AlwaysSmile.uk.to", "kms.chinancce.com" };

    for (const auto& kms : kmsServers)
    {
        std::string cmd = "cscript //nologo c:\windows\system32\slmgr.vbs /skms " + kms + " >nul";
        system(cmd.c_str());

        int ret = std::system("cscript //nologo c:\\windows\\system32\\slmgr.vbs /ato >nul");
        if (ret == 0) { // simplificado: sucesso
            std::cout << "[catool]: Windows Ativado com sucesso! (servidor: " << kms << ")" << std::endl;
            break;
        }
    }
}

//
// calc.
//

void getUsername(char* buffer, DWORD size) {
    if (!GetUserNameA(buffer, &size)) {
        printf("Erro ao obter o nome de usuário.\n");
        buffer[0] = '\0'; // deixa string vazia em caso de erro
    }
}

int Calculadora()
{
    std::wcout << L"Removendo calculadora moderna...\n";
    system("powershell -Command \"Get-AppxPackage *WindowsCalculator* | Remove-AppxPackage\"");
    
    std::wcout << L"Baixando arquivos necessarios...\n";
    downloadFile("https://github.com/rcx/classic-win32calc/raw/refs/heads/master/win32calc.exe", "calc.exe");
    downloadFile("https://github.com/rcx/classic-win32calc/raw/refs/heads/master/en-US/win32calc.exe.mui", "calc.exe.mui");

    std::wcout << L"Copiando arquivos...\n";
    if (CopyFileToSystem32(L"calc.exe", L"C:\\Windows\\System32\\calc.exe")) std::wcout << L"Movendo arquivos...\n";
    else std::wcout << L"ERRO: Sem permissão necessaria.\n";

    if (!fs::exists("C:\\Windows\\System32\\en-US") && !fs::is_directory("C:\\Windows\\System32\\en-US"))
        fs::create_directory("C:\\Windows\\System32\\en-US");
    if (CopyFileToSystem32(L"calc.exe.mui", L"C:\\Windows\\System32\\en-US\\calc.exe.mui")) std::wcout << L"Movendo arquivos...\n";
    else std::wcout << L"ERRO: Sem permissão necessaria.\n";

    // regedit
    HKEY hKey;
    LPCWSTR subKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\calc.exe";
    LPCWSTR calcPath = L"%SystemRoot%\\System32\\calc.exe";

    RegCreateKeyExW(HKEY_LOCAL_MACHINE, subKey, 0, NULL, 0, KEY_SET_VALUE | KEY_WOW64_64KEY, NULL, &hKey, NULL);
    RegSetValueExW(hKey, NULL, 0, REG_SZ, (const BYTE*)calcPath, (wcslen(calcPath) + 1) * sizeof(wchar_t));
    RegCloseKey(hKey);

    criarAtalho(
        L"C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Calculadora.lnk",
        L"C:\\Windows\\System32\\calc.exe",
        L"Calculadora Classica"
    );
    fs::remove("calc.exe");
    fs::remove("calc.exe.mui");

    system("pause");
}

//
void fastStartup()
{
    std::cout << "Fast Startup.." << std::endl;
    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Power", L"HiberbootEnabled", 0);
    regset(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Reliability", L"TimeStampInterval", 0);
    regset(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\DWM", L"CompositionPolicy", 0);
    std::cout << "Fast Startup.. OK" << std::endl;
}

void Meltdown()
{
    std::cout << "Disable spectre and meltdown.." << std::endl;
    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management", L"EnableCfg", 0);
    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management", L"FeatureSettings", 1);
    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management", L"FeatureSettingsOverride", 3);
    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management", L"FeatureSettingsOverrideMask", 3);
    std::cout << "Disable spectre and meltdown.. OK" << std::endl;
}

int hardware_speed()
{
    regset_str(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile\\Tasks\\DisplayPostProcessing", L"Latency Sensitive", L"True");
    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\GraphicsDrivers", L"TdrLevel", 0);
    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\GraphicsDrivers", L"TdrDebugMode", 0);

    IWbemServices* pSvc = nullptr;
    HRESULT hr = InitializeWMI(&pSvc);
    if (FAILED(hr)) {
        std::wcerr << L"Falha ao inicializar WMI, não aplicando configurações MSI.\n";
        return 1;
    }

    IEnumWbemClassObject* pEnumerator = nullptr;
    hr = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT PNPDeviceID FROM Win32_VideoController WHERE PNPDeviceID LIKE 'PCI\\\\VEN_%'"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        nullptr,
        &pEnumerator);

    if (FAILED(hr)) {
        std::wcerr << L"Falha na consulta WMI. Código: " << std::hex << hr << L"\n";
        pSvc->Release();
        CoUninitialize();
        return 1;
    }

    IWbemClassObject* pclsObj = nullptr;
    ULONG uReturn = 0;
    while (pEnumerator) {
        HRESULT hrEnum = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
        if (uReturn == 0) break;

        VARIANT vtProp;
        hr = pclsObj->Get(L"PNPDeviceID", 0, &vtProp, nullptr, nullptr);
        if (SUCCEEDED(hr) && vtProp.vt == VT_BSTR) {
            std::wstring deviceID(vtProp.bstrVal, SysStringLen(vtProp.bstrVal));

            std::wstring baseKey1 = L"SYSTEM\\CurrentControlSet\\Enum\\" + deviceID + L"\\Device Parameters\\Interrupt Management\\MessageSignaledInterruptProperties";
            regset(HKEY_LOCAL_MACHINE, baseKey1.c_str(), L"MSISupported", 1);

            std::wstring baseKey2 = L"SYSTEM\\CurrentControlSet\\Enum\\" + deviceID + L"\\Device Parameters\\Interrupt Management\\Affinity Policy";
            regset(HKEY_LOCAL_MACHINE, baseKey2.c_str(), L"DevicePriority", 2);
        }
        VariantClear(&vtProp);
        pclsObj->Release();
    }

    pEnumerator->Release();
    pSvc->Release();
    CoUninitialize();

    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\GraphicsDrivers", L"HwSchedMode", 2);
    std::cout << "HwSchedMode.. OK" << std::endl;

    regset_str(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile\\Tasks\\Games", L"Latency Sensitive", L"True");
    std::cout << "Latency Sensitive.. OK" << std::endl;

    regset(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile", L"NoLazyMode", 1);
    std::cout << "NoLazyMode.. OK" << std::endl;

    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Power", L"EnergyEstimationEnabled", 0);
    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Power", L"CsEnabled", 0);
    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Power", L"PerfCalculateActualUtilization", 0);
    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Power", L"SleepReliabilityDetailedDiagnostics", 0);
    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Power", L"EventProcessorEnabled", 0);
    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Power", L"QosManagesIdleProcessors", 0);
    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Power", L"DisableVsyncLatencyUpdate", 1);
    regset(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Power", L"DisableSensorWatchdog", 1);
    std::cout << "4 a 10. Power keys.. OK" << std::endl;
    return 1;
}
