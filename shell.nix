let
   pkgs = import <nixpkgs> {};
in pkgs.stdenv.mkDerivation rec {
  name = "crender";
  buildInputs = [ pkgs.pkg-config pkgs.SDL2 pkgs.stb pkgs.clang-tools pkgs.gdb ];
  shellHook = ''
  export STB_HEADER_PATH=${pkgs.stb}/include/stb/
  '';
}
