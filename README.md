# better-rasterizer
Rewriting my old incredibly slow and bad rasterization code

![Screenshot_20210726_143146](https://user-images.githubusercontent.com/73869536/127062028-b623bba3-cbdc-4be2-aeab-f8796d453065.png)

# Building
You need [vcpkg](https://github.com/microsoft/vcpkg) to build this project.
```
git clone https://github.com/longwatermelon/rasterizer
cd rasterizer
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
make
cd .. && build/rasterizer # So that the rasterizer can find the facet files
```
