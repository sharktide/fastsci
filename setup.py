from setuptools import setup, Extension, find_packages
import os

core_path = "src/fastsci/core"

def discover_sources(module_dir):
    manifest = os.path.join(module_dir, "sources.txt")
    if not os.path.exists(manifest):
        return None  # Skip if no sources.txt
    
    with open(manifest, "r") as f:
        files = [line.strip() for line in f if line.strip()]
    
    return [os.path.join(module_dir, fname) for fname in files]

def discover_extensions(core_path):
    extensions = []
    for subdir in os.listdir(core_path):
        full_path = os.path.join(core_path, subdir)
        if not os.path.isdir(full_path):
            continue

        sources = discover_sources(full_path)
        if not sources:
            continue

        include_dirs = list({os.path.dirname(s) for s in sources})
        extensions.append(
            Extension(
                name=f"fastsci.core.{subdir}",
                sources=sources,
                include_dirs=include_dirs,
                language="c++",
                extra_compile_args=["/std:c++17"] if os.name == "nt" else ["-std=c++17"]
            )
        )
    return extensions

def discover_packages(base="src"):
    return [
        pkg.replace(os.sep, ".")
        for pkg in find_packages(base)
    ]

setup(
    name="fastsci",
    version="0.1.0",
    description="High Performance Scientific Computing",
    packages=discover_packages("src"),
    package_dir={"": "src"},
    ext_modules=discover_extensions(core_path),
    zip_safe=False
)
