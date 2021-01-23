git clone https://github.com/microsoft/vcpkg
.\\vcpkg\\bootstrap-vcpkg.bat
.\\vcpkg\\vcpkg install freetype:x64-windows
.\\vcpkg\\vcpkg install glew:x64-windows
.\\vcpkg\\vcpkg install glfw3:x64-windows
.\\vcpkg\\vcpkg install sfml:x64-windows
.\\vcpkg\\vcpkg install glm:x64-windows
cmake ../src