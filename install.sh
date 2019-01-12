#!/bin/bash

PROJECT_ROOT=$(pwd)
BUILD_DIR=$PROJECT_ROOT/build
DIST_DIR=$PROJECT_ROOT/dist
CLEAN_INSTALL="false"

if [ ! -d "$DIST_DIR" ]; then
	echo "Creating Dist Directory"
	mkdir $DIST_DIR
fi

if [ ! -z $1 ] && [ "$1" = "clean" ]; then
	echo "Preparing Clean Install"
	CLEAN_INSTALL="true"
fi

if [ ! -d "$BUILD_DIR" ]; then
	mkdir $BUILD_DIR
	CLEAN_INSTALL="true"
fi

pushd $BUILD_DIR

if [ "$CLEAN_INSTALL" = "true" ]; then
	rm -rf $BUILD_DIR/* $DIST_DIR/*
	cmake ..
fi

make

if [ -f $DIST_DIR/poli ]; then
  echo "Removing old executable file"
	rm $DIST_DIR/poli
fi

touch $DIST_DIR/poli
chmod +x $DIST_DIR/poli
printf "#!/bin/bash\n\n./bin/poli" > $DIST_DIR/poli

popd 
