.PHONY: clean
all: a2q install
	
a2q: 
	cd ../; make;
	
install:
	./install_brew.sh # check if we have something to install packages with
	mkdir -p Rdeps; cd R/; Rscript install_packages.R # install R dependencies
	mkdir -p data; cd R/; Rscript sp500_data.R # download sp500 data
	cp js/mode-aquery.js Rdeps/shinyAce/www/ace/ # copy syntax highlighting file for code viz
	cd osx_qserver; make; # make R-q interface
