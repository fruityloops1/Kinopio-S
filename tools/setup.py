#!/usr/bin/env python3

import argparse
import hashlib
from pathlib import Path
import subprocess
from typing import Optional
from common import setup_common as setup
from enum import Enum

TARGET_PATH = setup.get_target_path()
TARGET_ELF_PATH = setup.get_target_elf_path()

class Version(Enum):
    VER_130 = "1.3"

def prepare_executable(original_nso: Optional[Path]):
    COMPRESSED_V10_HASH = "7a4289f6d8c0685c48cdc9219f49bfbed7a8662f84e812cb20773b65dec04e71"
    UNCOMPRESSED_V10_HASH = "8727d87007234d482d9bb81a8b2125639e1254fb07cd1731836fd359c74720c2"

    # The uncompressed v1.0 main NSO.
    TARGET_HASH = UNCOMPRESSED_V10_HASH

    if TARGET_PATH.is_file() and hashlib.sha256(TARGET_PATH.read_bytes()).hexdigest() == TARGET_HASH and TARGET_ELF_PATH.is_file():
        print(">>> NSO is already set up")
        return

    if not original_nso.is_file():
        setup.fail(f"{original_nso} is not a file")

    nso_data = original_nso.read_bytes()
    nso_hash = hashlib.sha256(nso_data).hexdigest()

    if nso_hash == UNCOMPRESSED_V10_HASH:
        print(">>> found uncompressed 1.3 NSO")
        TARGET_PATH.write_bytes(nso_data)

    elif nso_hash == COMPRESSED_V10_HASH:
        print(">>> found compressed 1.3 NSO")
        setup._decompress_nso(original_nso, TARGET_PATH)

    else:
        setup.fail(f"unknown executable: {nso_hash}")

    if not TARGET_PATH.is_file():
        setup.fail("internal error while preparing executable (missing NSO); please report")
    if hashlib.sha256(TARGET_PATH.read_bytes()).hexdigest() != TARGET_HASH:
        setup.fail("internal error while preparing executable (wrong NSO hash); please report")

    setup._convert_nso_to_elf(TARGET_PATH)

    if not TARGET_ELF_PATH.is_file():
        setup.fail("internal error while preparing executable (missing ELF); please report")

def create_build_dir(ver):
    if(ver != Version.VER_130): return # TODO remove this when multiple versions should be built
    build_dir = setup.ROOT / "build" # ("build-"+ver.value)
    if build_dir.is_dir():
        print(">>> build directory already exists: nothing to do")
        return

    subprocess.check_call(
        ("cmake -GNinja -DCMAKE_CXX_FLAGS=-D"+ver.name+" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=toolchain/ToolchainNX64.cmake -DCMAKE_CXX_COMPILER_LAUNCHER=ccache -B "+str(build_dir)).split(" "))
    print(">>> created build directory") 

def main():
    parser = argparse.ArgumentParser(
        "setup.py", description="Set up the Captain Toad: Treasure Tracker decompilation project")
    parser.add_argument("original_nso", type=Path,
                        help="Path to the original NSO (1.0, compressed or not)", nargs="?")
    args = parser.parse_args()

    setup.install_viking()
    prepare_executable(args.original_nso)
    setup.set_up_compiler("4.0.1")
    print("Please download and extract clang-3.9.1 manually, until it has been properly added to the setup chain.")
    create_build_dir(Version.VER_130)


if __name__ == "__main__":
    main()
