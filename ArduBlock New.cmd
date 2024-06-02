@echo off


set "serverFilePath1=http://ardublock.ru/new/arduino_blocs.js"
set "localFilePath1=www\blocs&generateurs\arduino_blocs.js"
powershell -Command "& { Invoke-WebRequest '%serverFilePath1%' -OutFile '%localFilePath1%' }"
if exist "%localFilePath1%" (
    echo 1.arduino_blocs.js OK 
) else (
    echo Ошибка код 1.
    pause
    exit /b
)

set "serverFilePath1=http://ardublock.ru/new/arduino_generateurs_cpp.js"
set "localFilePath1=www\blocs&generateurs\arduino_generateurs_cpp.js"
powershell -Command "& { Invoke-WebRequest '%serverFilePath1%' -OutFile '%localFilePath1%' }"
if exist "%localFilePath1%" (
    echo 2.arduino_generateurs_cpp.js OK 
) else (
    echo Ошибка код 2.
    pause
    exit /b
)

set "serverFilePath1=http://ardublock.ru/new/blockly_blocs.js"
set "localFilePath1=www\blocs&generateurs\blockly_blocs.js"
powershell -Command "& { Invoke-WebRequest '%serverFilePath1%' -OutFile '%localFilePath1%' }"
if exist "%localFilePath1%" (
    echo 3.blockly_blocs.js OK 
) else (
    echo Ошибка код 3.
    pause
    exit /b
)

set "serverFilePath1=http://ardublock.ru/new/blockly_generateurs_cpp.js"
set "localFilePath1=www\blocs&generateurs\blockly_generateurs_cpp.js"
powershell -Command "& { Invoke-WebRequest '%serverFilePath1%' -OutFile '%localFilePath1%' }"
if exist "%localFilePath1%" (
    echo 4.blockly_generateurs_cpp.js OK 
) else (
    echo Ошибка код 4.
    pause
    exit /b
)

set "serverFilePath1=http://ardublock.ru/new/blocklino.js"
set "localFilePath1=www\js\blocklino.js"
powershell -Command "& { Invoke-WebRequest '%serverFilePath1%' -OutFile '%localFilePath1%' }"
if exist "%localFilePath1%" (
    echo 5.blocklino.js OK 
) else (
    echo Ошибка код 5.
    pause
    exit /b
)

set "serverFilePath1=http://ardublock.ru/new/boards.js"
set "localFilePath1=www\js\boards.js"
powershell -Command "& { Invoke-WebRequest '%serverFilePath1%' -OutFile '%localFilePath1%' }"
if exist "%localFilePath1%" (
    echo 6.boards.js OK 
) else (
    echo Ошибка код 6.
    pause
    exit /b
)

set "serverFilePath1=http://ardublock.ru/new/msg_en.js"
set "localFilePath1=www\lang\msg_en.js"
powershell -Command "& { Invoke-WebRequest '%serverFilePath1%' -OutFile '%localFilePath1%' }"
if exist "%localFilePath1%" (
    echo 7.msg_en.js OK 
) else (
    echo Ошибка код 7.
    pause
    exit /b
)

set "serverFilePath1=http://ardublock.ru/new/msg_ru.js"
set "localFilePath1=www\lang\msg_ru.js"
powershell -Command "& { Invoke-WebRequest '%serverFilePath1%' -OutFile '%localFilePath1%' }"
if exist "%localFilePath1%" (
    echo 8.msg_ru.js OK 
) else (
    echo Ошибка код 8.
    pause
    exit /b
)

set "serverFilePath1=http://ardublock.ru/new/toolbox_arduino_all.xml"
set "localFilePath1=www\toolbox\toolbox_arduino_all.xml"
powershell -Command "& { Invoke-WebRequest '%serverFilePath1%' -OutFile '%localFilePath1%' }"
if exist "%localFilePath1%" (
    echo 9.toolbox_arduino_all.xml OK 
) else (
    echo Ошибка код 9.
    pause
    exit /b
)

set "serverFilePath1=http://ardublock.ru/new/toolbox_arduino_all-esp32.xml"
set "localFilePath1=www\toolbox\toolbox_arduino_all-esp32.xml"
powershell -Command "& { Invoke-WebRequest '%serverFilePath1%' -OutFile '%localFilePath1%' }"
if exist "%localFilePath1%" (
    echo 10.toolbox_arduino_all-esp32.xm OK 
) else (
    echo Ошибка код 10.
    pause
    exit /b
)

set "serverFilePath1=http://ardublock.ru/new/toolbox_esp826601.xml"
set "localFilePath1=www\toolbox\toolbox_esp826601.xml"
powershell -Command "& { Invoke-WebRequest '%serverFilePath1%' -OutFile '%localFilePath1%' }"
if exist "%localFilePath1%" (
    echo 11.toolbox_esp826601.xml OK 
) else (
    echo Ошибка код 11.
    pause
    exit /b
)

set "serverFilePath1=http://ardublock.ru/new/toolbox_esp826612.xml"
set "localFilePath1=www\toolbox\toolbox_esp826612.xml"
powershell -Command "& { Invoke-WebRequest '%serverFilePath1%' -OutFile '%localFilePath1%' }"
if exist "%localFilePath1%" (
    echo 12.toolbox_esp826612.xml OK 
) else (
    echo Ошибка код 12.
    pause
    exit /b
)

set "serverFilePath1=http://ardublock.ru/new/toolbox_leo32u4.xml"
set "localFilePath1=www\toolbox\toolbox_leo32u4.xml"
powershell -Command "& { Invoke-WebRequest '%serverFilePath1%' -OutFile '%localFilePath1%' }"
if exist "%localFilePath1%" (
    echo 13.toolbox_leo32u4.xml OK 
) else (
    echo Ошибка код 13.
    pause
    exit /b
)

set "serverFilePath1=http://ardublock.ru/new/index.html"
set "localFilePath1=www\index.html"
powershell -Command "& { Invoke-WebRequest '%serverFilePath1%' -OutFile '%localFilePath1%' }"
if exist "%localFilePath1%" (
    echo 14.index.html OK 
) else (
    echo Ошибка код 14.
    pause
    exit /b
)

set "serverFilePath1=http://ardublock.ru/new/in.html"
set "localFilePath1=www\in.html"
powershell -Command "& { Invoke-WebRequest '%serverFilePath1%' -OutFile '%localFilePath1%' }"
if exist "%localFilePath1%" (
    echo 15.in.html OK 
) else (
    echo Ошибка код 15.
    pause
    exit /b
)

@echo off
timeout /t 2 /nobreak >nul
start /B ArduBlock.exe
exit 