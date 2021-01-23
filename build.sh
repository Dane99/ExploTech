git clone https://github.com/microsoft/vcpkg
.\vcpkg\bootstrap-vcpkg.bat

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac

if [ "${machine}" == "Linux" ]; then
    # GNU/Linux platform

elif [ "${machine}" == "Mac" ]; then
    # Mac OS X platform  

elif [ "${machine}" == "Cygwin" ||  "${machine}" == "MinGw" ]; then
    # Do something under 32 bits Windows NT platform
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then
    # Do something under 64 bits Windows NT platform
fi