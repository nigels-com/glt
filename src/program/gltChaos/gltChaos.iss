; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=GltChaos
AppVerName=GltChaos 0.4
AppPublisher=Nigel Stewart
AppPublisherURL=http://www.nigels.com/glt/gltchaos/
AppSupportURL=http://www.nigels.com/glt/gltchaos/
AppUpdatesURL=http://www.nigels.com/glt/gltchaos/
DefaultDirName={pf}\GltChaos
DefaultGroupName=GltChaos
AllowNoIcons=yes
Uninstallable=yes
; uncomment the following line if you want your installation to run on NT 3.51 too.
; MinVersion=4,3.51

[Tasks]

[Files]
Source: "..\..\..\msvc\Release\gltChaos.exe"; DestDir: "{app}"; CopyMode: alwaysoverwrite
Source: "..\..\..\msvc\Release\gltChaos.scr"; DestDir: "{sys}"; CopyMode: alwaysoverwrite

[INI]
Filename: "{app}\gltChaos.url"; Section: "InternetShortcut"; Key: "URL"; String: "http://www.nigels.com/glt/gltchaos/"

[Icons]
Name: "{group}\GltChaos"; Filename: "{app}\gltChaos.exe"
Name: "{group}\GltChaos on the Web"; Filename: "{app}\gltChaos.url"
Name: "{userdesktop}\GltChaos"; Filename: "{app}\gltChaos.exe"; MinVersion: 4,4;
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\GltChaos"; Filename: "{app}\gltChaos.exe"; MinVersion: 4,4;

[Run]
Filename: "{app}\gltChaos.exe"; Description: "Launch GltChaos"; Flags: nowait postinstall skipifsilent

[UninstallDelete]
Type: files; Name: "{app}\gltChaos.url"

