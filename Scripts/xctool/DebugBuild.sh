#!/bin/sh
SCHEME=FactoryEngine
PROJECT=FactoryEngine.xcodeproj
CONFIG=Debug
SDK=macosx

xctool \
-project $PROJECT \
-scheme $SCHEME \
-configuration $CONFIG \
-sdk $SDK \
SYMROOT=Build \





