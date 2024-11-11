#include <iostream>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

using std::pair;
using std::vector;
using std::wcout;
using std::wstring;

#include "WinReg.hpp"

using winreg::RegKey;
using winreg::RegException;
using winreg::RegExpected;

auto hkeys = {
    HKEY_CLASSES_ROOT,
    HKEY_CURRENT_CONFIG,
    HKEY_CURRENT_USER,
    HKEY_LOCAL_MACHINE,
    HKEY_USERS
};

class options {
    options() = default;

public:
    virtual ~options() {}
    static options parse(int argc, char** argv) {
        options opt;

        return opt;
    }
};

void search(RegKey & regkey, wstring subkey, const wstring & value) {
    // wcout << "Processing subkey: " << subkey << "\n";
    // if (regkey.ContainsValue(value)) {
    //     wcout << "Value " << value << " was found for subkey: " << subkey << "\n";
    // } else {
    //     // wcout << "Value " << value << " was not found for subkey: " << subkey << "\n";
    // }

    for (const auto & [vname, vtype] : regkey.EnumValues()) {
        if (vtype == REG_SZ) {
            wstring & data = regkey.GetStringValue(vname);
            // wcout << "Data: " << data << "\n";
            if (data.find(value) != data.npos )
                wcout << "Found value " << vname << " that contains " << value << " in data " << data << "\n";
        }
        // wcout << "Value: " << vname << ", subkey: " << subkey << "\n";
        // if (vname.find(value) > -1) {
        //     wcout << "Found value " << vname << " that contains " << value << "\n";
        // }
    }

    vector<wstring> subKeyNames = regkey.EnumSubKeys();
    for (const auto& s : subKeyNames)
    {
        wstring sub = subkey + L"\\" + s;
        // wcout << "subkey: " << subkey << ", s: " << s << ", sub: " << sub << "\n";
        try {
            RegKey subkeyreg{ regkey.Get(), sub };
            search(subkeyreg, sub, value);
        } catch( RegException & exc ) {
            wcout << "Unable to open key: " << sub << " " << exc.what() << "\n";
        } catch( std::exception & ex ) {
            wcout << ex.what() << "\n";
        }
    }
}

int main(int argc, char** argv) {
    for(int idx = 0 ; idx < argc ; idx++)
        std::cout << "Arg " << idx << " == " << argv[idx] << "\n";
    std::cout << "Hello, from registry!\n";

    // vector<HKEY> hkeys = { /* HKEY_USERS, HKEY_CLASSES_ROOT, HKEY_CURRENT_USER, HKEY_CURRENT_CONFIG, */ HKEY_LOCAL_MACHINE };

    // wstring ws;

    // if (ws.find(L"C:\\tools\\swift\\6.0.1") > -1) {
    //     wcout << "Found substr\n";
    // } else {
    //     wcout << "Substring was not found\n";
    // }

    // for(const auto & hkey : hkeys) {
    //     // wcout << "HKEY: " << hkey << "\n";
    //     RegKey key{ hkey };

    //     if (key.ContainsValue(L"C:\\tools\\swift\\6.0.1")) {
    //         wcout << "Found value\n";
    //     } else {
    //         wcout << "Value not found\n";
    //     }

    //     HKEY ckey = key.Get();

    //     vector<wstring> subKeyNames = key.EnumSubKeys();
    //     wcout << L"Subkeys:\n";
    //     for (const auto& s : subKeyNames)
    //     {
    //         wcout << L"  [" << s << L"]\n";
    //     }
    //     wcout << L'\n';

    //     vector<pair<wstring, DWORD>> values = key.EnumValues();
    //     wcout << L"Values:\n";
    //     for (const auto& [valueName, valueType] : values)
    //     {
    //         wcout << L"  [" << valueName << L"](" << RegKey::RegTypeToString(valueType) << L")\n";
    //     }
    //     wcout << L'\n';

    //     key.Close();

    // }

    try {
        RegKey key{HKEY_LOCAL_MACHINE, L"SOFTWARE" };
        const wstring VALUE = L"C:\\tools\\swift\\6.0.1";

        // vector<wstring> subkeys = key.EnumSubKeys();
        // for (const auto & subkey : subkeys) {
        //     search(key, subkey, VALUE) ;
        // }
    } catch( RegException & exc ) {
        wcout << exc.what() << "\n";
    } catch( std::exception & ex ) {
        wcout << ex.what() << "\n";
    }

    try {
        // wstring top = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\S-1-5-21-2556836214-3306548245-4195300345-1001\\Components\\D4B0BEFFB792D5554BAF151B6269FB73";
        wstring top = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\S-1-5-21-2556836214-3306548245-4195300345-1001\\Components";
        // wstring top = L"SOFTWARE";
        RegKey key{HKEY_LOCAL_MACHINE, top };
        const wstring VALUE = L"C:\\tools\\swift\\6.0.1";

        // for (const auto & [vname, vtype] : key.EnumValues()) {
        //     wcout << "Value: " << vname << "\n";
        //     if (vtype == REG_SZ) {
        //         wcout << "Data: " << key.GetStringValue(vname) << "\n";
        //     }
        // }

        vector<wstring> subkeys = key.EnumSubKeys();
        for (const auto & subkey : subkeys) {
            // wcout << "Creating subkeyreg: " << top << L"\\" << subkey << "\n";
            wstring name = top + L"\\" + subkey;
            // wcout << "Creating subkeyreg: " << name << "\n";
            try {
                RegKey subkeyreg{HKEY_LOCAL_MACHINE, name };
                search(subkeyreg, name, VALUE);
            } catch (RegException & regexc ) {
                wcout << "An RegException was raised when trying to open subkey: " << name << " with error: " << regexc.what() << "\n";
            } catch (std::exception & exc ) {
                wcout << "An exception was raised when trying to open subkey: " << name << " with error: " << exc.what() << "\n";
            }
        }
    } catch( RegException & exc ) {
        wcout << exc.what() << "\n";
    } catch( std::exception & ex ) {
        wcout << ex.what() << "\n";
    }
}
