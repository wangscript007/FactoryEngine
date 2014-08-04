#!/bin/sh
SCHEME=FactoryEngine
PROJECT=FactoryEngine.xcodeproj
CONFIG=Release
SDK=macosx

xctool \
-project $PROJECT \
-scheme $SCHEME \
-configuration $CONFIG \
-sdk $SDK \
SYMROOT=Build \





