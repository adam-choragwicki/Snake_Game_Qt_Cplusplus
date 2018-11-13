@echo on

if not exist "executable_windows" (
    powershell -Command "(New-Object System.Net.WebClient).DownloadFile('https://github.com/adam-choragwicki/Snake_Game_Qt_Cplusplus/releases/latest/download/executable_windows.zip', '.\executable_windows.zip')"
    powershell -Command "Expand-Archive -Path 'executable_windows.zip' -DestinationPath '.'"
    del "executable_windows.zip"
)

executable_windows\Snake.exe
