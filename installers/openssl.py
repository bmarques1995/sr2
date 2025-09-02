import subprocess
import sys
from package_helpers import append_msvc_compiler_location, clone_and_checkout, run, append_paths
import platform
import os

def main():
    build_mode = sys.argv[1]
    install_prefix = sys.argv[2]
    module_destination = sys.argv[3]
    
    os_name = platform.system().lower()

    final_build_mode = build_mode.lower()
    package_output_dir = "openssl"
    commit_hash_release = "aea7aaf2abb04789f5868cbabec406ea43aa84bf"
    openssl_dir = append_paths(module_destination, "modules", package_output_dir)

    if os_name == "windows":
        vs_compiler = sys.argv[4]
        append_msvc_compiler_location(vs_compiler)

    clone_and_checkout(repo="https://github.com/openssl/openssl.git", destination=openssl_dir, commit_hash=commit_hash_release, branch="openssl-3.5")
    if os_name == "windows":
        run(f'perl ./Configure VC-WIN64A --{final_build_mode} '
            f'--prefix={install_prefix} --openssldir={install_prefix}/openssl -no-shared '
            f'--with-zlib-lib={install_prefix}/lib --with-zlib-include={install_prefix}/include '
            f'--with-brotli-include={install_prefix}/include --with-brotli-lib={install_prefix}/lib '
            f'--with-zstd-lib={install_prefix}/lib --with-zstd-include={install_prefix}/include', cwd=openssl_dir)
        run(f'nmake', cwd=openssl_dir)
        run(f'nmake install', cwd=openssl_dir)
        run(f'git clean -dfx', cwd=openssl_dir)
    elif os_name in ["linux", "darwin", "freebsd"]:
        run(f'./config --{final_build_mode} '
            f'--prefix={install_prefix} --openssldir={install_prefix}/openssl -fPIC -no-shared --libdir=lib '
            f'--with-zlib-lib={install_prefix}/lib --with-zlib-include={install_prefix}/include '
            f'--with-brotli-include={install_prefix}/include --with-brotli-lib={install_prefix}/lib '
            f'--with-zstd-lib={install_prefix}/lib --with-zstd-include={install_prefix}/include', cwd=openssl_dir)
        run(f'make -j {int(os.cpu_count()/2)}', cwd=openssl_dir)
        run(f'make install_sw install_ssldirs', cwd=openssl_dir)
        run(f'git clean -dfx', cwd=openssl_dir)

if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError as e:
        print(f"Build or install failed: {e}", file=sys.stderr)
        sys.exit(1)
