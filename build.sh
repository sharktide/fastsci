runTests=false

for arg in "$@"; do
  if [[ "$arg" == "-t" || "$arg" == "--test" ]]; then
    runTests=true
  fi
done

echo "Building & Testing with NumPy support"
rm -rf build
pip install -r requirements.txt || exit 1
pip install .[numpy] || exit 1
rm -rf build

if [ "$runTests" = true ]; then
  echo "Running tests..."

  if ! command -v repycl &> /dev/null; then
    echo "ERROR: reStructuredPython's command line interpreter was not found."
    echo "ERROR: You can find more installation methods at:"
    echo "ERROR: https://github.com/sharktide/reStructuredPython"
    echo "ERROR: https://reStructuredPython.readthedocs.io"
    echo "ERROR: https://reStructuredPython.rf.gd"
    echo "ERROR: Make sure your Python Scripts directory is in your PATH."
    echo "ERROR: Example: /home/yourname/.local/bin or /usr/local/bin"
    exit 1
  fi

  repycl runtests.repy
fi

echo "Building & Testing without NumPy support"
pip install . || exit 1

if [ "$runTests" = true ]; then
  echo "Running tests..."

  if ! command -v repycl &> /dev/null; then
    echo "ERROR: reStructuredPython's command line interpreter was not found."
    echo "ERROR: You can find more installation methods at:"
    echo "ERROR: https://github.com/sharktide/reStructuredPython"
    echo "ERROR: https://reStructuredPython.readthedocs.io"
    echo "ERROR: https://reStructuredPython.rf.gd"
    echo "ERROR: Make sure your Python Scripts directory is in your PATH."
    echo "ERROR: Example: /home/yourname/.local/bin or /usr/local/bin"
    exit 1
  fi

  repycl runtests.repy
fi
