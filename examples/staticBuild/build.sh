#!/bin/bash -xe
SRC_DIR="/home/malloy/pubgit/4160fall-2017/projects/3/soln"

NAME="$(basename "$SRC_DIR")"

TMP_DIR="tmp"
BLD_DIR="build"
IMG_DIR="image"

rm -rf "$TMP_DIR"
mkdir -p "$TMP_DIR"
rm -rf "$BLD_DIR"
mkdir -p "$BLD_DIR"
rm -rf "$IMG_DIR"
mkdir -p "$IMG_DIR"

cp -r "$SRC_DIR" "$TMP_DIR"/"$NAME"

pushd "$TMP_DIR"
find . -type d -name ".git" -exec rm -rf '{}' ';' -prune
popd

mkdir -p "$IMG_DIR"/usr/bin
mkdir -p "$IMG_DIR"/usr/share
mkdir -p "$IMG_DIR"/usr/share/metainfo


cp -r "$TMP_DIR"/"$NAME" "$IMG_DIR"/usr/share/"$NAME"
cp -r "$TMP_DIR"/"$NAME" "$BLD_DIR"/"$NAME"

pushd "$BLD_DIR"/"$NAME"
make
EXE="$(find . -maxdepth 1 -type f -perm -u+x | head -n1)"
popd

cat >"$IMG_DIR"/AppRun <<EOF
#!/bin/sh
IMG="\$(dirname "\$(readlink -f "\$0")")"

export PATH="\$IMG"/usr/bin/:"\$IMG"/usr/sbin/:"\$IMG"/usr/games/:"\$IMG"/bin/:"\$IMG"/sbin/:"\$PATH"
export LD_LIBRARY_PATH="\$IMG"/usr/lib/:"\$IMG"/usr/lib/i386-linux-gnu/:"\$IMG"/usr/lib/x86_64-linux-gnu/:"\$IMG"/usr/lib32/:"\$IMG"/usr/lib64/:"\$IMG"/lib/:"\$IMG"/lib/i386-linux-gnu/:"\$IMG"/lib/x86_64-linux-gnu/:"\$IMG"/lib32/:"\$IMG"/lib64/:"\$LD_LIBRARY_PATH"
export XDG_DATA_DIRS="\$IMG"/usr/share/:"\$XDG_DATA_DIRS"

cd "\$IMG"/usr/share/"$NAME"

exec "\$IMG"/usr/bin/"$NAME" "\$@"
EOF
chmod +x "$IMG_DIR"/AppRun

ICON="$(find . -maxdepth 1 -type f -name '*.png' | head -n1)"
cp "$ICON" "$IMG_DIR"/"$NAME".png

cat >"$IMG_DIR"/"$NAME".desktop <<EOF
[Desktop Entry]
Name=$NAME
Exec=$NAME
Icon=$NAME
Type=Application
Categories=Game;
EOF

cp "$BLD_DIR"/"$NAME"/"$EXE" "$IMG_DIR"/usr/bin/"$NAME"

cat >"$IMG_DIR"/usr/share/metainfo/"$NAME".appdata.xml <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<component type="desktop">
  <id>$NAME.desktop</id>
  <name>$NAME</name>
  <developer_name>CPSC 4160</developer_name>
  <description>
    <p>
      A game developed for Dr. Brian Malloy's 2D Game Engine class.
    </p>
  </description>
  <metadata_license>CC0-1.0</metadata_license>
  <project_license>CC0-1.0</project_license>
  <url type="homepage">https://people.cs.clemson.edu/~malloy/</url>
  <update_contact>malloy@cs.clemson.edu</update_contact>
</component>
EOF

for lib in $(ldd "$IMG_DIR"/usr/bin/"$NAME" | grep -E '=>\s/' | awk '{ print $3 }' | sed -e 's#^/##'); do
  mkdir -p "$IMG_DIR"/"$(dirname "$lib")"
  cp /"$lib" "$IMG_DIR"/"$lib"
done

rm -f appimagetool-x86_64.AppImage
wget "https://github.com/AppImage/AppImageKit/releases/download/continuous/appimagetool-x86_64.AppImage"
chmod +x appimagetool-x86_64.AppImage

./appimagetool-x86_64.AppImage "$IMG_DIR"
