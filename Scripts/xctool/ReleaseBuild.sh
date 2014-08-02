#!/bin/sh
SCHEME=Factory
PROJECT=Factory.xcodeproj
CONFIG=Release
SDK=macosx

xctool \
-project $PROJECT \
-scheme $SCHEME \
-configuration $CONFIG \
-sdk $SDK \
SYMROOT=Build \





