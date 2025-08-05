$runTests = $false

foreach ($arg in $args) {
    if ($arg -eq "-t" -or $arg -eq "--test") {
        $runTests = $true
    }
}

Write-Host "Building & Testing with NumPy support"
Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue
pip install -r requirements.txt
pip install .[numpy]
Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue

if ($runTests) {
    Write-Host "Running tests..."

    if (-not (Get-Command repycl -ErrorAction SilentlyContinue)) {
        Write-Host "ERROR: reStructuredPython's command line interpreter was not found."
        Write-Host "ERROR: You can find more installation methods at:"
        Write-Host "ERROR: https://github.com/sharktide/reStructuredPython"
        Write-Host "ERROR: https://reStructuredPython.readthedocs.io"
        Write-Host "ERROR: https://reStructuredPython.rf.gd"
        Write-Host "ERROR: Make sure your Python Scripts directory is in your PATH."
        Write-Host "ERROR: Example: C:\Users\YourName\AppData\Local\Programs\Python\PythonXXX\Scripts"
        exit 1
    }

    repycl runtests.repy
}

Write-Host "Building & Testing without NumPy support"
pip install .

if ($runTests) {
    Write-Host "Running tests..."

    if (-not (Get-Command repycl -ErrorAction SilentlyContinue)) {
        Write-Host "ERROR: reStructuredPython's command line interpreter was not found."
        Write-Host "ERROR: You can find more installation methods at:"
        Write-Host "ERROR: https://github.com/sharktide/reStructuredPython"
        Write-Host "ERROR: https://reStructuredPython.readthedocs.io"
        Write-Host "ERROR: https://reStructuredPython.rf.gd"
        Write-Host "ERROR: Make sure your Python Scripts directory is in your PATH."
        Write-Host "ERROR: Example: C:\Users\YourName\AppData\Local\Programs\Python\PythonXXX\Scripts"
        exit 1
    }

    repycl runtests.repy
}
