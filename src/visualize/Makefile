.PHONY: clean
all: a2q install
	
a2q: 
	cd ../; make;
	
install:
	Rscript install_packages.R
	cd osx_qserver; make; 
		
