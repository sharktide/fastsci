@echo off
SETLOCAL ENABLEDELAYEDEXPANSION

SET runTests=false

:parseArgs
IF "%~1"=="" GOTO afterArgs
IF "%~1"=="-t" SET runTests=true
IF "%~1"=="--test" SET runTests=true
SHIFT
GOTO parseArgs

:afterArgs

echo Building & Testing with NumPy support
rmdir build
pip install -r requirements.txt
pip install .[numpy]
rmdir build
IF "!runTests!"=="true" (
    echo Running tests...

    where repycl >nul 2>nul
    IF ERRORLEVEL 1 (
        echo ERROR: reStructuredPython's command line interpreter was not found.
        echo ERROR: You can find more installation methods at
        echo ERROR: https://github.com/sharktide/reStructuredPython
        echo ERROR: https://reStructuredPython.readthedocs.io
        echo ERROR: https://reStructuredPython.rf.gd
        echo ERROR: Make sure your Python Scripts directory is in your PATH.
        echo ERRORL Example: C:\Users\YourName\AppData\Local\Programs\Python\PythonXXX\Scripts
        GOTO end
    )

    repycl runtests.repy
)

echo Building & Testing without NumPy support

pip install .
IF "!runTests!"=="true" (
    echo Running tests...

    where repycl >nul 2>nul
    IF ERRORLEVEL 1 (
        echo ERROR: reStructuredPython's command line interpreter was not found.
        echo ERROR: You can find more installation methods at
        echo ERROR: https://github.com/sharktide/reStructuredPython
        echo ERROR: https://reStructuredPython.readthedocs.io
        echo ERROR: https://reStructuredPython.rf.gd
        echo ERROR: Make sure your Python Scripts directory is in your PATH.
        echo ERRORL Example: C:\Users\YourName\AppData\Local\Programs\Python\PythonXXX\Scripts
        GOTO end
    )

    repycl runtests.repy
)

:end
ENDLOCAL
