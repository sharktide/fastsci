# from setuptools import setup, Extension
# from glob import glob

# core_sources = glob("src/fastsci/core/*.c") + glob("src/fastsci/core/*.cpp")
# bindings_sources = glob("src/fastsci/bindings/*c") + glob("src/fastsci/core/*.cpp")
# include_dirs = [
#     "src/fastsci/include"
# ]

# setup(
#     name="fastsci",
#     version="1.0.0",
#     ext_modules=[
#         Extension("fastsci.core", sources=bindings_sources + core_sources, include_dirs=include_dirs, language="c++")
#     ],
#     packages=["fastsci"],
#     package_dir={"": "src"},
# )
from setuptools import setup, Extension
import sys
import os
import glob

base_dir = "src/fastsci"

def collect_sources():
    return (
        glob.glob(os.path.join(base_dir, "**", "*.c"), recursive=True) +
        glob.glob(os.path.join(base_dir, "**", "*.cpp"), recursive=True) +
        glob.glob(os.path.join(base_dir, "**", "*.cc"), recursive=True) +
        glob.glob(os.path.join(base_dir, "**", "*.cxx"), recursive=True)
    )

def collect_include_dirs():
    source_files = collect_sources()
    dirs = {os.path.dirname(path) for path in source_files}
    return sorted(dirs)

fastsci_core = Extension(
    name="fastsci.core",
    sources=collect_sources(),
    include_dirs=collect_include_dirs(),
    language="c++",
    extra_compile_args=["/std:c++17"] if os.name == "nt" else ["-std=c++17"]
)

setup(
    name="fastsci",
    version="0.1.0",
    description="High Preformance Scientific Computing",
    packages=["fastsci", "fastsci.constructors"],
    ext_modules=[fastsci_core],
    zip_safe=False
)
