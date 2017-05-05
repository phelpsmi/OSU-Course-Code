A1writeup.dvi: A1writeup.tex
	pdflatex A1writeup.tex

A1writeup.ps: A1writeup.dvi
	dvips -Ppdf -G0 A1writeup.dvi
	
A1writeup.pdf: A1writeup.ps
	ps2pdf A1writeup.ps

PDF: A1writeup.pdf
	xpdf A1writeup.pdf

all: pdf

clean:
	rm -f *.pdf *.ps *.dvi *.out *.log *.aux *.bbl *.blg *.pyg

.PHONY: all show clean ps pdf showps

