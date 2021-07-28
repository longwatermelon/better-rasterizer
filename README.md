# better-rasterizer
Rewriting my old incredibly slow and bad rasterization code

![image](https://user-images.githubusercontent.com/73869536/127395423-a8321d16-cd89-475e-8a49-581099c598a2.png)

# Building
You need [vcpkg](https://github.com/microsoft/vcpkg) to build this project.
```
git clone https://github.com/longwatermelon/better-rasterizer
cd rasterizer
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
make
cd .. && build/rasterizer # So that the rasterizer can find the facet files
```
