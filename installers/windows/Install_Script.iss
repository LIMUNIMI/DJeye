#define MyAppPublisher "LIMUNIMI"
#define MyAppURL "https://lim.di.unimi.it"
#define MyAppName "djeye"
#define MyAppVersion "##APPVERSION##"

[Setup]
AppName="{#MyAppName} {#MyAppVersion}"
AppVersion={#MyAppVersion}
AppVerName={#MyAppName}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={commonpf64}\LIMUNIMI\
DefaultGroupName={#MyAppName}
DisableProgramGroupPage=yes
DisableDirPage=yes
DisableWelcomePage=no
LicenseFile=../../LICENSE
OutputBaseFilename="djeye-Win-{#MyAppVersion}"
OutputDir=.
; SetupIconFile=myicon.ico
; UninstallDisplayIcon=myicon.ico
UninstallFilesDir={commonpf64}\LIMUNIMI\{#MyAppName}
Compression=lzma
SolidCompression=yes

[Types]
Name: "full"; Description: "Full installation"
Name: "custom"; Description: "Custom installation"; Flags: iscustom

[Components]
Name: "Standalone"; Description: "Standalone application 64-bit"; Types: full

[Files]
Source: "../../bin/Win64/djeye.exe"; DestDir: "{code:GetDir|VST3_64}"; Components: VST3_64; Flags: ignoreversion recursesubdirs createallsubdirs
[Icons]
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"

[Code]
var
  Vst3_64DirPage: TinputDirWizardPage;

procedure InitializeWizard;
begin
  Log('Initializing extra pages')

  //VST3 64-bit Dir Page
  Vst3_64DirPage := CreateInputDirPage(AAXDirPage.ID,
    'Select Install Location for VST3 64-bit', 'Where would you like to install the plugin?',
    'VST3 64-bit plugin will be installed in the following folder.'#13#10#13#10 +
    'To continue, click Next. If you would like to select a different folder, click Browse.',
    False, 'New Folder');

  Vst3_64DirPage.add('');
  Vst3_64DirPage.values[0] := ExpandConstant('{commoncf64}\VST3');

end;

function IsSelected(Param: String) : Boolean;
begin
  if not (Pos(Param, WizardSelectedComponents(False)) = 0) then // WizardSelectedComponents(False)) then
    Result := True
end;

function ShouldSkipPage(PageID: Integer): Boolean;
begin
  { Skip pages that shouldn't be shown }
  Result := False;

  else if (PageID = Vst3_64DirPage.ID) then
  begin
      Result := True;
      Log('Selected 2: ' + WizardSelectedComponents(False));

      if IsSelected ('vst3_64') then
      begin
        Log('Not Skipping');
        Result := False;
      end
  end

end;

function GetDir(Param: String) : String;
begin
  if (Param = 'VST3_64') then
    Result := Vst3_64DirPage.values[0]
end;

function UpdateReadyMemo(Space, NewLine, MemoUserInfoInfo, MemoDirInfo, MemoTypeInfo,
  MemoComponentsInfo, MemoGroupInfo, MemoTasksInfo: String): String;
var
  S: String;
begin
  { Fill the 'Ready Memo' with the normal settings and the custom settings }
  S := '';
  S := S + MemoTypeInfo + NewLine + NewLine;
  S := S + MemoComponentsInfo + NewLine + NewLine;
  S := S + 'Destination Location:' + NewLine;

  if IsSelected('vst3_64') then
    S := S + Space +  GetDir('VST3_64') + ' (VST3 64-bit)' + NewLine;

  Result := S;
end;
