import subprocess
import sys
from package_helpers import clone_and_checkout, append_paths, run
import platform

def main():
    build_mode = sys.argv[1]
    install_prefix = sys.argv[2]
    module_destination = sys.argv[3]

    os_name = platform.system().lower()

    package_output_dir = "libarchive"
    commit_hash_release = "9525f90ca4bd14c7b335e2f8c84a4607b0af6bdf"
    archive_dir = append_paths(module_destination, "modules", package_output_dir)
    build_dir = append_paths(module_destination, "dependencies", os_name, package_output_dir)
    archive_cmake_dir = archive_dir

    clone_and_checkout("https://github.com/libarchive/libarchive.git", destination=archive_dir, commit_hash=commit_hash_release)
    #clone_and_checkout("https://github.com/bmarques1995/libarchive.git", destination=archive_dir)

    if os_name == "windows":
        run(f'cmake -S "{archive_cmake_dir}" -B "{build_dir}" '
            f'-DCMAKE_INSTALL_PREFIX="{install_prefix}" '
            f'-DCMAKE_PREFIX_PATH="{install_prefix}" '
            f'-DENABLE_TEST=OFF '
            f'-DENABLE_TAR=OFF '
            f'-DENABLE_CAT=OFF '
            f'-DENABLE_CPIO=OFF '
            f'-DBUILD_SHARED_LIBS=OFF')
        run(f'cmake --build "{build_dir}" --config {build_mode} --target install')
    elif os_name in ["linux", "darwin", "freebsd"]:
        run(f'cmake -S "{archive_cmake_dir}" -B "{build_dir}" '
            f'-DCMAKE_BUILD_TYPE="{build_mode}" '
            f'-DCMAKE_INSTALL_PREFIX="{install_prefix}" '
            f'-DCMAKE_PREFIX_PATH="{install_prefix}" '
            f'-DCMAKE_INSTALL_LIBDIR=lib '
            f'-DENABLE_TEST=OFF '
            f'-DENABLE_TAR=OFF '
            f'-DENABLE_CAT=OFF '
            f'-DENABLE_CPIO=OFF '
            f'-DBUILD_SHARED_LIBS=OFF')
        run(f'cmake --build "{build_dir}" --target install')

if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError as e:
        print(f"Error while running command: {e}", file=sys.stderr)
        sys.exit(1)
