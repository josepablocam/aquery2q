.PHONY: clean
all: a2q install
	
a2q: 
	cd ../; make;
	
install:
	./install_brew.sh;
	mkdir -p Rdeps; Rscript install_packages.R
	cd osx_qserver; make; 
		
