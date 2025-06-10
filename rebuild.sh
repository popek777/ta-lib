#/bin/bash

build_type='RelWithDebInfo'

build_dir=build/$build_type

rm -rf $build_dir
mkdir -p $build_dir

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=$build_type -B$build_dir

pushd $build_dir

make -j 12

popd > /dev/null
rm compile_commands.json
ln -s $build_dir/compile_commands.json compile_commands.json
