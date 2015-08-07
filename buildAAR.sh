 
cd tess-two
ndk-build clean
./gradlew clean assembleRelease
cp ./build/outputs/aar/tess-two-release.aar ../../aar/tess-two-release/tess-two-release-.aar
ndk-build
