
rem forfiles /M *.bat /C "cmd /c echo @path"
forfiles /S /M *.db /C "cmd /c del @path"
forfiles /S /M ipch /C "cmd /c rd /q /s @path"
forfiles /S /M debug /C "cmd /c rd /q /s @path"
forfiles /S /M release /C "cmd /c rd /q /s @path"
