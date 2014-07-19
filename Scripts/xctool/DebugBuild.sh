#!/bin/sh
SCHEME=Factory
WORKSPACE=project.xcworkspace
CONFIG=Debug
SDK=macosx

pwd

xctool \
-workspace $WORKSPACE \
-scheme $SCHEME \
-configuration $CONFIG \
-sdk $SDK \
archive \
-archivePath build_outpu