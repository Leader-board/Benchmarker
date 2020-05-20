# c++
sudo apt-get update
sudo apt install build-essential
# net core
wget https://packages.microsoft.com/config/ubuntu/19.10/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
sudo dpkg -i packages-microsoft-prod.deb
sudo apt-get update
sudo apt-get install apt-transport-https
sudo apt-get update
sudo apt-get install dotnet-sdk-3.1
sudo apt-get update
sudo apt-get install dotnet-runtime-3.1
# pypy3
sudo add-apt-repository ppa:pypy/ppa
sudo apt update
sudo apt install pypy3
# java
sudo apt update
sudo apt install default-jdk
# mono C#
sudo apt install gnupg ca-certificates
sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
echo "deb https://download.mono-project.com/repo/ubuntu stable-bionic main" | sudo tee /etc/apt/sources.list.d/mono-official-stable.list
sudo apt update
sudo apt install mono-devel
# final
sudo apt update
sudo apt-get -y upgrade