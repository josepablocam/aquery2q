# Color coding
# Reset
NO_COLOR='\033[0m'       # Text Reset

# Regular Colors
RED='\033[0;31m'          # Red
GREEN='\033[0;32m'        # Green

inquire() {
  printf "$GREEN $1 (y/n)? $NO_COLOR\n"
  read answer
  if echo "$answer" | grep -iq "^y" ;then
      return 0
  else
      return 1
  fi
  }
  
warn() {
  printf "$RED $1 $NO_COLOR\n"
}  


# check if has gcc48 and right R version
# if so, we're set and can exit
HAS_GCC48=$(command -v gcc48)
HAS_R3=$(command -v R > /dev/null && R --version | grep "version 3.*" | cut -c 1)

if [ ! -z $HAS_GCC48 ] && [ ! -z $HAS_R3 ]
  then
    echo "All components needed are available."
    exit 0
fi    
  

warn "You are missing packages, we'll try to install using homebrew"

# Check if we already have homebrew installed
# if not prompt user
command -v brew >/dev/null 2>&1 || {
 if ! inquire "Can I install homebrew for you?";
   then
     warn "Not installing. You are responsible for packages"
     exit 1
 fi

 # Install homebrew
 ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
}

# Install missing gcc48 compiler
if [ -z $HAS_GCC48 ] && inquire "Can I install gcc48 for you?"
  then
    # ran into pkg-config issues, so adding as fix
    brew install pkg-config
    # c
    brew tap homebrew/versions
    brew install gcc48
    # symlink brew name to the format followed in cims
    ln -s /usr/local/bin/gcc-4.8 /usr/local/bin/gcc48
fi

# Install missing R version
if [ -z $HAS_R3 ] && inquire "Can I install latest R for you?"
  then
    # xquartz needed for R (and user might not have xcode)
    brew tap Caskroom/cask
    brew install Caskroom/cask/xquartz
    # actual R installation
    brew tap homebrew/science
    brew install r
fi

# Make sure the path has the necessary paths
export PATH=$PATH:/usr/local/bin/




