let
   pkgs = import <nixpkgs> {};
in pkgs.stdenv.mkDerivation rec {
  name = "crender";
  buildInputs = [ pkgs.pkg-config pkgs.SDL2 pkgs.clang-tools pkgs.gdb ];
  shellHook = ''
  '';
}
